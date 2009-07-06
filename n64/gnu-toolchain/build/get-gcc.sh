#!/bin/sh
#http://ftp.gnu.org/gnu/gcc/gcc-4.4.0/gcc-core-4.4.0.tar.gz
BV="gcc-4.4.0"
BB="${BV}-obj"
if [ -d "${BB}" ]
then
    echo "GCC object directory already exists, skipping..."
	exit 0
fi
if [ ! -d "${BV}" ]
then
    wget -O - "http://ftp.gnu.org/gnu/gcc/gcc-4.4.0/gcc-core-4.4.0.tar.gz" | tar -xzf -
fi
mkdir -p "${BB}"
cd "${BB}"
../"${BV}"/configure --prefix="${1}" --target=mips --disable-werror --enable-languages=c --disable-threads --disable-multilib --disable-libssp --with-newlib --with-abi=32 --with-arch=vr4300 --with-tune=vr4300 --with-float=hard
nice -n 5 make
sudo PATH="${PATH}" make install

