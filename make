g++ -O2 -I. \
    bip32.cpp \
    bip39.cpp \
    crypto/sha256*.cpp \
    crypto/sha512.cpp \
    crypto/hmac_sha512.cpp \
    crypto/pkcs5_pbkdf2_hmac_sha512.cpp \
    main.cpp \
    util.cpp \
    -l:libbtc.a \
    -o hdderive
