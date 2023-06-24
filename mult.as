	    lw		0		0		zero		load reg0 with zero 0
		lw		0		1		zero		load reg1 with zero 0 for result adding
		lw      0       2       mcand       load reg2 with mcand 32766
	    lw      0       3       mplier      load reg3 with mplier 12328
        lw      0       4       mask		load reg4(for nor) with mask 1
		lw      0       5       count       16. not 32
	    lw      0       7       mask       	register for calculating mask
	    lw	    0       6       zero	    
		beq		2		0		done		stop when mcand = 0 (doesn't change so before loop)
		beq     3       5       done        stop when mplier = 0
loop	beq     0       5       done        count == 0 -> break
	    nor     3       3       6           reg6 = ~(mplier | 0 or mplier)
	    nor     4       4       7           reg7 = ~(reg4 | 0 or reg4)
	    nor     6       7       6           reg6 = ~(reg6 | reg7)
	    beq     0       6       noadd       if zero == reg6  -> noadd
	    add     1       2       1           reg1(result) = reg1 + reg2(shifted mcand)
		noop                                update registers(2:mcand << 1, 4: mask << 1, 5:loop_count --)
noadd   add     2       2       2           mcand = mcand + mcand == mcand x 2 == mcand << 1
	    add     4       4       4           reg4 = reg4 + reg4 == reg4 x 2 == reg4 << 1
		lw		0		7		none
	    add     5       7       5           reg5 = reg5 + reg7 == reg5 -= 1
        noop
	    beq     0       0       loop       
done	halt
		noop
zero	.fill	0
mcand   .fill	32766
mplier  .fill	12328
count   .fill	16
mask 	.fill	1
none	.fill	-1
