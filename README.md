# LC2K_assembler
A program which is an assembler to to take an assembly-language program and produce the corresponding machine language.
(instruction set and instruction format of the LC-2K. Not MIPS!!)

## ASSEMBLER
take an assembly-language program and translate it into machine language.
### assembler.c
Main file that converts .as file to .mc file.

### spec.as
Example of assembler input

### spec.mc.correct
Example of assembler output   
(correct answer for spec.ac)

### testcases directory
Test cases to validate any LC-2K assembler.   
5 normal case, 5 error case

## MULTIPLIER
An assembly-language program to multiply two numbers.   
Input the numbers by reading memory locations called mcand and mplier.   
The result stored in register 1.   

### mult.as
Multiplier. (Input of the assembler.)

### mult.mc
Output of putting mult.as to the assembler.
