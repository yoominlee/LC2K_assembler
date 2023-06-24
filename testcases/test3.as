        lw      0       0       num1
        lw      0       1       num2
        nor     0       0       2
        nor     1       1       3
        nor     2       3       4
        sw      5       4       0
        sw      6       0       0
        sw      7       1       0
        halt
num1    .fill   175
num2    .fill   11
