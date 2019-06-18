#include <asm.h>

.code16
.globl start
start:
  cli

xorw    %ax,%ax
xorw    %ax,%ds
xorw    %ax,%es
xorw    %ax,%ss