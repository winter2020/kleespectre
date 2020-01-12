cd /home/wgh/timingsyn_cache/bench/
cd hpn-ssh/
rm *.bc
rm *.ll
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm hash.c -o hash.bc
llvm-dis-6.0 hash.bc
cd ..
cd openssl/
rm *.bc
rm *.ll
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm des.c -o  des.bc
llvm-dis-6.0 des.bc
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm str2key.c -o str2key.bc
llvm-dis-6.0 str2key.bc
cd ..
cd tegra/
rm *.bc
rm *.ll
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm camellia_generic.c -o camellia.bc
llvm-dis-6.0 camellia.bc
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm salsa20_generic.c -o salsa20.bc
llvm-dis-6.0 salsa20.bc
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm seed.c -o  seed.bc
llvm-dis-6.0 seed.bc 
cd ..
cd tomcrypt/
rm *.bc
rm *.ll
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm aes.c -o  aes.bc
llvm-dis-6.0 aes.bc
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm base16_encode.c -o  encoder.bc
llvm-dis-6.0 encoder.bc
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm chacha20poly1305_memory.c -o  chacha20.bc
llvm-dis-6.0 chacha20.bc
clang-6.0 -g -c -O1 -Wno-everything -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -emit-llvm ocb3_init.c -o  ocb3.bc
llvm-dis-6.0 ocb3.bc
cd ..
