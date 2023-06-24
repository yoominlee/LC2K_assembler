        lw      0       1       three    load reg1 with 3
        lw      0       2       two       load reg2 with 2
        lw      0       3       nfive       load reg3 with -5
        lw      0       4       result
        lw      0       6       one
        add     5       2       1       reg5 = 3 + 2
        add     5       4       3       reg5 = reg5 - 5
        beq     4       5       cor     
        noop
        halt                            
cor     add     7       5       6
        halt
three   .fill   3
two     .fill   2
nfive   .fill   -5 
result  .fill   0
one     .fill   1
