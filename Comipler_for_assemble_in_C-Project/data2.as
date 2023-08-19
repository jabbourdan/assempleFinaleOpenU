.entry LENGTH
    .extern W
MAIN: mov @r9,LENGTH
LOOP: jmp L1
prn -5
bne W
sub @r1, @r4
    bne L3
L1: inc K
    .entry LOOP
jmp W,,
END: stop
"STR: .string "abcdef"
LENGTH: .data 6,10000,15,
K: .data 22
    .extern L3
