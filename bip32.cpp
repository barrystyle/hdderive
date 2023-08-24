// Copyright (c) 2023 barrystyle
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <btc/bip32.h>
#include <btc/utils.h>
#include <string.h>
#include <string>

#include <bip39.h>
#include <util.h>

void get_bip32_btckey(std::string& seed, std::string& path, int start, int last, std::vector<std::string>& p2khlist)
{
    btc_hdnode node, node2;
    char str[512], path_[20];
    uint8_t private_key[32], chain_code[32];

    memset(str, 0, sizeof(str));
    memset(path_, 0, sizeof(path_));

    /* init m */
    btc_hdnode_from_seed(utils_hex_to_uint8(seed.c_str()), seed.size() / 2, &node);
    memcpy(private_key, node.private_key, 32);
    memcpy(chain_code, node.chain_code, 32);

    /* derive for path */
    p2khlist.clear();
    std::string p2kh_address;
    for (int i = start; i < last; i++) {
        sprintf(path_, "%s%d", path.c_str(), i);
        btc_hd_generate_key(&node2, path_, private_key, chain_code, false);
        btc_hdnode_get_p2pkh_address(&node2, &btc_chainparams_main, str, sizeof(str));
        p2kh_address = std::string(str);
        p2khlist.push_back(p2kh_address);
    }
}

void entropy_to_p2kh(std::string& entropy, int bitlen, std::string& path, int start, int last, std::vector<std::string>& p2khlist)
{
    // entropy-hex to entropy-bin
    unsigned char entropy_bin[32];
    std::vector<uint8_t> entropy_;

    binlify(entropy_bin, entropy.c_str());
    for (int i = 0; i < bitlen / 8; i++) {
        entropy_.push_back(entropy_bin[i]);
    }

    // entropy-bin to mnemonic
    char bip39seed[512];
    std::vector<uint8_t> seed;
    memset(bip39seed, 0, sizeof(bip39seed));

    // bip39seed from mnemonic
    std::string mnemonic = CMnemonic::FromData(entropy_, bitlen / 8);
    CMnemonic::ToSeed(mnemonic, std::string(""), seed);
    for (int i = 0; i < seed.size(); i++) {
        sprintf(bip39seed + (i * 2), "%02hhx", seed[i]);
    }
    std::string seed_ = std::string(bip39seed);

    // derive p2kh from bip39seed
    get_bip32_btckey(seed_, path, start, last, p2khlist);
}
