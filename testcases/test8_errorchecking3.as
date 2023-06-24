        lw      0       1       aaa
        lw      0       2       65536
        beq     0       2       jum
        jalr    1       3
jum     noop
        add     1       1       1
        add     1       1       1
        add     1       1       1
        sw      7       1       0
        halt
aaa     .fill   10
bbb     .fill   0
