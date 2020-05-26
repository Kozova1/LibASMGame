getc r0
ld r1, 1
#loop
sub r0, r1
putc r0
ld rf, 030
subr rf, r0
biz brk
jmp loop
#brk
