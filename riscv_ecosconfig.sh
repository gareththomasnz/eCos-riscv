#!/bin/sh
TOPDIR=$(realpath $(dirname $0))/ecos-3.0
BLDDIR=$TOPDIR/../Configs/kernel_riscv_build
TOOLDIR=$TOPDIR/tools

ECOSTOOL=$TOOLDIR/bin/ecosconfig
CONFIG_ECC=$TOPDIR/../Configs/kernel_riscv.ecc
REPO_DIR=$TOPDIR/packages 
INST_DIR=$TOPDIR/../Configs/kernel_riscv_install

rm -rf $BLDDIR
mkdir -p $BLDDIR && cd $BLDDIR
$ECOSTOOL --config=$CONFIG_ECC --srcdir=$REPO_DIR --prefix=$INST_DIR tree

#riscv32-unknown-elf-gcc -nostartfiles -Ttarget.ld -o image.elf vectors.o libtarget.a helloc.o

#riscv32-unknown-elf-objdump -x -s -w -D vectors.o > vectors.dump
#riscv32-unknown-elf-objdump -x -s -w -D libtarget.a > libtarget.dump
#riscv32-unknown-elf-objdump -x -s -w -D image.elf > image.dump