#!/bin/bash
set -e
for NASM_HEADER in $@
do
    C_HEADER="${NASM_HEADER%%.inc}.h"
    if [ $C_HEADER -nt $NASM_HEADER ]; then
        sed 's/\/\*/;/' $C_HEADER | sed 's/\*\///' | sed 's/^#/%/' > $NASM_HEADER
    fi
done