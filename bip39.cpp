/**
 * Copyright (c) 2013-2014 Tomas Dzetkulic
 * Copyright (c) 2013-2014 Pavol Rusnak
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// Source:
// https://github.com/trezor/trezor-crypto

#include <bip39.h>
#include <bip39_english.h>
#include <crypto/pkcs5_pbkdf2_hmac_sha512.h>
#include <crypto/sha256.h>
#include <cstring>
#include <vector>

std::string CMnemonic::FromData(const std::vector<uint8_t>& data, int len)
{
    if (len % 4 || len < 16 || len > 32) {
        return std::string();
    }

    std::vector<uint8_t> checksum(32);
    CSHA256().Write(data.data(), len).Finalize(checksum.data());

    // data
    std::vector<uint8_t> bits(len);
    memcpy(bits.data(), data.data(), len);
    // checksum
    bits.push_back(checksum[0]);

    int mlen = len * 3 / 4;
    std::string mnemonic;

    int i, j, idx;
    for (i = 0; i < mlen; i++) {
        idx = 0;
        for (j = 0; j < 11; j++) {
            idx <<= 1;
            idx += (bits[(i * 11 + j) / 8] & (1 << (7 - ((i * 11 + j) % 8)))) > 0;
        }
        mnemonic.append(wordlist[idx]);
        if (i < mlen - 1) {
            mnemonic += ' ';
        }
    }

    return mnemonic;
}

bool CMnemonic::Check(std::string mnemonic)
{
    if (mnemonic.empty()) {
        return false;
    }

    uint32_t nWordCount{};

    for (size_t i = 0; i < mnemonic.size(); ++i) {
        if (mnemonic[i] == ' ') {
            nWordCount++;
        }
    }
    nWordCount++;
    // check number of words
    if (nWordCount != 12 && nWordCount != 18 && nWordCount != 24) {
        return false;
    }

    std::string ssCurrentWord;
    std::vector<uint8_t> bits(32 + 1);

    uint32_t nWordIndex, ki, nBitsCount{};

    for (size_t i = 0; i < mnemonic.size(); ++i)
    {
        ssCurrentWord = "";
        while (i + ssCurrentWord.size() < mnemonic.size() && mnemonic[i + ssCurrentWord.size()] != ' ') {
            if (ssCurrentWord.size() >= 9) {
                return false;
            }
            ssCurrentWord += mnemonic[i + ssCurrentWord.size()];
        }
        i += ssCurrentWord.size();
        nWordIndex = 0;
        for (;;) {
            if (!wordlist[nWordIndex]) { // word not found
                return false;
            }
            if (ssCurrentWord == wordlist[nWordIndex]) { // word found on index nWordIndex
                for (ki = 0; ki < 11; ki++) {
                    if (nWordIndex & (1 << (10 - ki))) {
                        bits[nBitsCount / 8] |= 1 << (7 - (nBitsCount % 8));
                    }
                    nBitsCount++;
                }
                break;
            }
            nWordIndex++;
        }
    }
    if (nBitsCount != nWordCount * 11) {
        return false;
    }
    bits[32] = bits[nWordCount * 4 / 3];
    CSHA256().Write(bits.data(), nWordCount * 4 / 3).Finalize(bits.data());

    bool fResult = 0;
    if (nWordCount == 12) {
        fResult = (bits[0] & 0xF0) == (bits[32] & 0xF0); // compare first 4 bits
    } else
    if (nWordCount == 18) {
        fResult = (bits[0] & 0xFC) == (bits[32] & 0xFC); // compare first 6 bits
    } else
    if (nWordCount == 24) {
        fResult = bits[0] == bits[32]; // compare 8 bits
    }

    return fResult;
}

void CMnemonic::ToSeed(std::string mnemonic, std::string passphrase, std::vector<uint8_t>& seedRet)
{
    std::string ssSalt = std::string("mnemonic") + passphrase;
    std::vector<uint8_t> vchSalt(ssSalt.begin(), ssSalt.begin() + strnlen(ssSalt.data(), 256));
    seedRet.resize(64);
    PKCS5_PBKDF2_HMAC_SHA512(mnemonic.c_str(), mnemonic.size(), vchSalt.data(), vchSalt.size(), 2048, 64, seedRet.data());
}
