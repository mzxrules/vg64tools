#!/bin/sh
#ftp://sources.redhat.com/pub/newlib/newlib-1.17.0.tar.gz
BV="newlib-1.17.0"
BB="${BV}-obj"

if [ -d "${BB}" ]
then
    echo "newlib's object directory already exists, skipping..."
    exit 0
fi
if [ ! -d "${BV}" ]
then
    wget -O - "ftp://sources.redhat.com/pub/newlib/${BV}.tar.gz" | tar -xzf -
fi
mkdir -p "${BB}"
cd "${BB}"
export CFLAGS_FOR_TARGET="-Os -G 0"
../"${BV}"/configure --prefix="${1}" --target=mips --disable-multilib 
nice -n 5 make
sudo PATH="${PATH}" make install

