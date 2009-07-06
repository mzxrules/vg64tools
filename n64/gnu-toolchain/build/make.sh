#!/bin/sh
DEST="/usr/mips"
sh get-binutils.sh "${DEST}"
export PATH=${DEST}/bin:${PATH}
sh get-gcc.sh "${DEST}"
sh get-newlib.sh "${DEST}"
echo Finished.
