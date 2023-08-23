## hdderive

Simple set of routines to derive HD addresses (BIP32/BIP39) from entropy.

This was quite an exercise in how BIP's are often not much more than a 'serving suggestion', not to mention being incredibly convoluted where a simple description would suffice.


### credits

Anyone is welcome to use the code as they please, as long as the copyrights remain intact.

* barrystyle
* Jonas Schnelli (libbtc library)
* Dash Core developers (bip39 functions)
* Bitcoin Core developers (hashing functions)


### building/dependencies

* libbtc (https://github.com/libbtc/libbtc/)

  recommended to apply PR#195 if using threading

```
git clone https://github.com/libbtc/libbtc
cd libbtc
wget https://github.com/libbtc/libbtc/pull/195.diff
patch -p1 < 195.diff
./autogen.sh
./configure
make install
```

* hdderive (this)

```
git clone https://github.com/barrystyle/hdderive
cd hdderive
./make
```


### usage

```
root@loderunner:~/hdderive# ./hdderive 
entropy: 8c97b7d89adb8bd86c9fa562704ce40ef645627acacf877a9164ecd6125616a5 bitlen: 256
m/44'/0'/0'/0/0 - 14gpRQ9W97CRYFYg2AMqJq7MG9QCXK2uSD
m/44'/0'/0'/0/1 - 1K2sG6FjJNa9jAPi3xuPwjoEuy5DVgjpUw
m/44'/0'/0'/0/2 - 1DcUwhx2d7ZiThGfQoj8r37EUgdQAPVxfc
m/44'/0'/0'/0/3 - 17TiCiDKMcp1JbUvCWuGzaZohDaCTdCCmR
m/44'/0'/0'/0/4 - 175PA57wf2sBWzoWYy6E9KM3HdAVujZNFS
m/44'/0'/0'/0/5 - 1FVHr9k8sSBEnzFppLxdUh6QtVHEANFE7k
m/44'/0'/0'/0/6 - 16w4PB6LsejMJvTf21iL4pTZJPExziZCFQ
m/44'/0'/0'/0/7 - 1CEDa3ctYbKAWi5UK6UNS4foegqJKPFTTk
m/44'/0'/0'/0/8 - 1J9yLnef5iignkVEoVRxvJpcgzjceMSsi1
m/44'/0'/0'/0/9 - 1DsbkLzuTnfh8WH6eG4Yk7hhbw4QCjxSwx
m/44'/0'/0'/0/10 - 12PrwkuKa1cWzj3x5RdU5u5VLdhuaA9XaQ
m/44'/0'/0'/0/11 - 1CJoKuX8A4da61iqsHfMiQc2iEdjtpkwGd
m/44'/0'/0'/0/12 - 1GFHCcyJAk4Np7ETRR4YGvKXsW3r9CyBZz
m/44'/0'/0'/0/13 - 1B8qBCAYNt39AF2MGVDXhTy1KpFG475bmP
m/44'/0'/0'/0/14 - 1A7xN5A9wX971CNp8KGkCMTxqeRm3j1vSx
m/44'/0'/0'/0/15 - 1EBNdZAMgqBuyi8PPrYV45REiNe2J3DAJP
m/44'/0'/0'/0/16 - 1AxTjEvQXgVrXudXdNDUvsewDLmcXWzAUi
m/44'/0'/0'/0/17 - 12S1XGkRvjt1SC3papzLWBDymdgJZ6RG6z
m/44'/0'/0'/0/18 - 1D3oczbrQuFzNVTveWrQUaqE6A7p7SL4RS
m/44'/0'/0'/0/19 - 1KhzMjDHP9aAmaufrX1w3NjXMKD7bKHHhJ
```


### verification

![result verification at https://iancoleman.io/bip39/](https://i.imgur.com/q9nNSgS.png)
