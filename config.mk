
WARN=-Wall -Wextra -Wno-unused-function -Wno-unused-parameter

# freestanding using any recent clang build
# CC=clang
# CFLAGS=--target=riscv64 -march=rv64gcv_zba_zbb_zbs -O3 ${WARN} -nostdlib -fno-builtin -ffreestanding
#CFLAGS=--target=riscv32 -march=rv32gc_zve32f_zba_zbb_zbs -O3 ${WARN} -nostdlib -fno-builtin -ffreestanding

# full cross compilation toolchain
CC=/opt/riscv/bin/riscv64-unknown-linux-gnu-gcc
CFLAGS=-march=rv64gcv -O3 -static ${WARN}

# native build
#CC=cc
#CFLAGS=-march=rv64gcv -O3 ${WARN}
