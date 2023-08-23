// Copyright (c) 2023 barrystyle
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <bip32.h>
#include <btc/bip32.h>
#include <btc/utils.h>

bool ecc_started{false};

extern "C" {
    void btc_ecc_start();
    void btc_ecc_stop();
}

int main()
{
    if (!ecc_started) {
        btc_ecc_start();
        ecc_started = true;
    }

    std::vector<std::string> p2khlist;
    std::string entropy = "8c97b7d89adb8bd86c9fa562704ce40ef645627acacf877a9164ecd6125616a5";
    int entropy_len = entropy.size() / 2;
    int entropy_bitlen = entropy_len * 8;
    std::string path = "m/44'/0'/0'/0/";

    entropy_to_p2kh(entropy, entropy_bitlen, path, 0, 20, p2khlist);

    printf("entropy: %s bitlen: %d\n", entropy.c_str(), entropy_bitlen);
    for (int i=0; i<p2khlist.size(); i++) {
        printf("%s%d - %s\n", path.c_str(), i, p2khlist[i].c_str());
    }

    return 1;
}
