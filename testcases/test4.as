        lw      0       1       cou1   
        lw      0       2       cou2     
        lw      0       3       none 
        lw      0       4       add1   
        lw      0       5       add2   
        lw      0       6       zero    result
loop1   beq     0       1       out1
loop2   beq     0       2       out2
        add     2       3       2       count--
        add     6       5       6
        beq     0       0       loop2
out2    noop
        add     1       3       1       count--
        add     6       4       6
        beq     0       0       loop1
out1    noop
        halt
cou1    .fill   10
cou2    .fill   4
none    .fill   -1
add1    .fill   5
add2    .fill   1
zero    .fill   0
