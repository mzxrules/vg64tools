#!/bin/sh
BV="binutils-2.19.1"
BB="${BV}-obj"
if [ -d "${BB}" ]
then
    echo "binutils object directory already exists, skipping..."
	exit 0
fi
if [ ! -d "${BV}" ]
then
    wget -O - "http://ftp.gnu.org/gnu/binutils/${BV}.tar.gz" | tar -xzf -
fi
mkdir -p "${BB}"
cd "${BB}"
../"${BV}"/configure --prefix="${1}" --target=mips --disable-werror --with-arch=vr4300
nice -n 5 make
sudo PATH="${PATH}" make install

