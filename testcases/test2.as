        lw      0       0       zero
        lw      0       1       zero            load reg1 with 0 for result
        lw      0       3       zero            each loop +1
        lw      0       4       count           load reg4 with 10
        lw      0       5       zero            check
        lw      0       6       none
        lw      0       7       one
loop    beq     4       3       done
        beq     0       5       even            reg1 (zero) == reg5 (check) (+ -)
odd     lw      0       2       two             load reg2 with 2
        add     1       2       1
        add     4       6       4               1 - 1 = 0   
        beq     0       0       once
even    lw      0       2       three           load reg2 with 2
        add     1       2       1
        add     4       6       4               0 + 1 = 1
once    add     3       7       3
        beq     0       0       loop
done    halt
zero    .fill   0
none    .fill   -1
one     .fill   1
count   .fill   20
two     .fill   2
three   .fill   3
