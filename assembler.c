/* Assembler code fragment for LC-2K */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000
#define LABLELENGTH 7 // \n

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);
int findLabel(char *label);

int pc; int prog_length;
char tmp_lableName[MAXLINELENGTH][LABLELENGTH];

int main(int argc, char *argv[]) 
{
	char *inFileString, *outFileString;
	FILE *inFilePtr, *outFilePtr;
	char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH], 
			 arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

	if (argc != 3) {
		printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",
				argv[0]);
		exit(1);
	}

	inFileString = argv[1];
	outFileString = argv[2];

	inFilePtr = fopen(inFileString, "r");
	if (inFilePtr == NULL) {
		printf("error in opening %s\n", inFileString);
		exit(1);
	}
	outFilePtr = fopen(outFileString, "w");
	if (outFilePtr == NULL) {
		printf("error in opening %s\n", outFileString);
		exit(1);
	}

	/* TODO: Phase-1 label calculation */

	rewind(inFilePtr); // file의 시작점으로 file ptr를 rewind. 

	// ====================== FIRST PASS ======================

	// struct Lable labelPass1[MAXLINELENGTH];

	// int count = 0;
	pc = 0;
	prog_length = pc;
	while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)){
		// pc ++;
		// printf("ooooooo   \n");
		// count ++;
		// int is_in_table = findLabel(labl);
		// char labName[LABLELENGTH] = {0};
		// strncpy(labName[0], label, sizeof(label));
		// printf("%s",labName);printf("       ");printf("%d \n", findLabel(label));
		if((strcmp(label,"")) && (findLabel(label) != -1)){ // tmp_lableName[]에 이미 있는 label인 경우
			printf("error in label(duplicated).\n");
			exit(1); // ERROR #2 duplicated labels
		}

		if (strcmp(label,"")){ // label이 무언가 있는 경우에만 append
			// printf("label to table %s \n",label);
			strcpy(tmp_lableName[pc], label); // 각 줄의 라벨을 tmp_lableName 넣기. index와 instruction line 동일
		}
		// printf("--- %d \n", prog_length);
		// for(int j = 0; j <= prog_length+1; j++) { // tmp_lableName 잘 들어갔나 확인
		// 	// printf("%c \n", label[j]);
		// 	printf("%d : %s \n", j, tmp_lableName[j]);
		// }
		// printf("---\n");
		
		prog_length = pc;
		pc++;
	}
	rewind(inFilePtr);

	// ====================== SECOND PASS ======================

	/* TODO: Phase-2 generate machine codes to outfile */

	/* after doing a readAndParse, you may want to do the following to test the opcode */
		 	// <hex연산 check>
			// int hex0 = 0x0111; // 0000 0001 0010 0001
			// int hex1 = 0x00A0; // 0000 0000 0010 0000
			// int hex2 = hex0 | hex1;
			// printf("%04X | %04X = %04X \n",hex0, hex1, hex2);
			// hex2 = hex0 & hex1;
			// printf("%04X & %04X = %04X \n",hex0, hex1, hex2);

			// <binary check>
			// int tmpbinary = 0b00001100010000010000000000111001;
			// printf("%b \n", tmpbinary);
			// int obinary = binary | tmpbinary;
			// printf("%b \n", obinary);
			// obinary = binary & tmpbinary;
			// printf("%b \n", obinary);
	pc = 0;
	while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)){
		// char binary[32] ={0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
		// int hex_num = 0x00000000;
		int binary = 0b00000000000000000000000000000000;

		// int tbinary = 0b00000000000000000000000000011000;
		// int binary[32] ={1};
		// int binary = 10;
		// printf("d: %d\n",binary|tbinary);
		// printf("x: %X\n",binary|tbinary);
		// // printf("c: %c\n",binary|tbinary);
		// // printf("s: %s\n",binary|tbinary);

		// select type and 
		int typeCase = 0;
		// binary[24]=0;binary[23]=0;binary[22]=0;
		if (!strcmp(opcode, "add")){typeCase=1; 		binary = 0b00000000000000000000000000000000;}			// R-type
		else if (!strcmp(opcode, "nor")){typeCase=1; 	binary = 0b00000000010000000000000000000000;}		// R-type
		else if (!strcmp(opcode, "lw")){typeCase=2; 	binary = 0b00000000100000000000000000000000;}		// I-type	
		else if (!strcmp(opcode, "sw")){typeCase=2; 	binary = 0b00000000110000000000000000000000;}		// I-type
		else if (!strcmp(opcode, "beq")){typeCase=2; 	binary = 0b00000001000000000000000000000000;}		// I-type
		else if (!strcmp(opcode, "jalr")){typeCase=3; 	binary = 0b00000001010000000000000000000000;}		// J-type
		else if (!strcmp(opcode, "halt")){typeCase=4; 	binary = 0b00000001100000000000000000000000;}		// J-type
		else if (!strcmp(opcode, "noop")){typeCase=4; 	binary = 0b00000001110000000000000000000000;}		// O-type
		else if (!strcmp(opcode, ".fill")){typeCase=5; 	binary = 0b00000000000000000000000000000000;}		// O-type
		else{
			/* wrong opcode!! */
			printf("error in opcode.\n");
			// printf("%d", pc);
			exit(1); // ERROR #4 wrong opcode
		}

		int temp = 0b00000000000000000000000000000000; // 32bits
		switch (typeCase)
		{
		case 1: // R-type
			if (isNumber(arg0)!=1 | isNumber(arg1)!=1 |isNumber(arg2)!=1){ // isNumber 숫자면 1 return. 셋중 하나라도 숫자가 아니면 에러.
				printf("error in R-type. Register is not number \n");
				exit(1); // ERROR #5 non-integer register argument
			}
			if (atoi(arg0) < 0 | atoi(arg0) > 7 | atoi(arg1) < 0 | atoi(arg1) > 7 | atoi(arg2) < 0 | atoi(arg2) > 7){
				printf("error in R-type. Register outside the range 0-7 \n");
				exit(1); // ERROR #6 Register outside the range [0-7]
			}
			temp = temp | (atoi(arg0) << 19) | (atoi(arg1) << 16) | atoi(arg2);
			break;
		case 2: // I-type
			if (isNumber(arg0)!=1 | isNumber(arg1)!=1){ // isNumber 숫자면 1 return. 셋중 하나라도 숫자가 아니면 에러.
				printf("error in I-type. Register is not number\n");
				exit(1); // ERROR #5 non-integer register argument
			}
			if (atoi(arg0) < 0 | atoi(arg0) > 7 | atoi(arg1) < 0 | atoi(arg1) > 7){
				printf("error in I-type. Register outside the range 0-7 \n");
				exit(1); // ERROR #6 Register outside the range [0-7]
			}
			//!! arg2가 빈칸인 경우 exit(1)? 
			if (isNumber(arg2)!=1){				// symbolic address 
				if(findLabel(arg2)==-1){		// 저장된 값 없음
					printf("error in I-type. Wrong label\n");
					// printf("%d",pc);
					// printf(label);printf("\n");
					// printf(arg0);printf("\n");
					// printf(arg1);printf("\n");
					// printf(arg2);printf("\n");
					exit(1); // ERROR #1 undefined labels
				}else{
					int tempAdd = findLabel(arg2);
					if (tempAdd > 0xFFFF){
						printf("error in offsetField. Too big\n");
						exit(1); // ERROR #3 offsetField bigger than 16bits
					}
					if(!strcmp(opcode, "beq")){ // I-type중에서 beq면 상대주소 계산
						tempAdd -= (pc + 1);
						tempAdd = tempAdd & 0x0000FFFF;
						// printf("symbolic beq \n");
						// printf("%d   -  ( %d + 1)\n", tempAdd, pc);
					}temp = temp | (atoi(arg0) << 19) | (atoi(arg1) << 16) | tempAdd;
				}
			}
			else{								// numeric address
				if (atoi(arg2) < -32768 || atoi(arg2) > 32767){
					printf("error in offsetField. Too big\n");
					exit(1); // ERROR #3 offsetField bigger than 16bits
				}				
				temp = temp | (atoi(arg0) << 19) | (atoi(arg1) << 16) | atoi(arg2); 
			}
			
			break;
		case 3: // J-type
			if (isNumber(arg0)!=1 | isNumber(arg1)!=1){ // isNumber 숫자면 1 return. 셋중 하나라도 숫자가 아니면 에러.
				printf("error in J-type. Arg0 or arg1 is not number\n");
				exit(1); // ERROR #5 non-integer register argument
			}
			if (atoi(arg0) < 0 | atoi(arg0) > 7 | atoi(arg1) < 0 | atoi(arg1) > 7){
				printf("error in J-type. Register outside the range 0-7 \n");
				exit(1); // ERROR #6 Register outside the range [0-7]
			}
			temp = temp | (atoi(arg0) << 19) | (atoi(arg1) << 16);
			break;
		case 4: // O-type
			/* code */
			break;
		case 5: // .fill
			if (isNumber(arg0)!=1){			// symbolic 변환
				if(findLabel(arg0)==-1){
					printf("error in .fill. Wrong label\n");
					exit(1); // ERROR #1 undefined labels
				}else{
					int tempAdd = findLabel(arg0);
					temp = temp | tempAdd;
				}
			}
			else{							// numeric
				temp = temp | atoi(arg0); 
			}
			break;
		// 다섯 케이스 이외의 opcode는 위에서 error 처리 완료
		}
		binary = binary | temp;

		// printf(binary);

		/* -- 파일 쓰기 전 각 줄 확인용 -- */
		// printf("d: %d      ",binary);
		// printf("x: %X\n",binary);

		fprintf(outFilePtr, "%d \n",binary);
		// fprintf(outFilePtr, "\n");
		/*
		label:  / op: lw / a0: 0 / a1: 1 / a2: five10
		label:  / op: lw / a0: 1 / a1: 2 / a2: 310   start
		label: start / op: add / a0: 1 / a1: 2 / a2: 110
		label:  / op: beq / a0: 0 / a1: 1 / a2: 210
		label:  / op: beq / a0: 0 / a1: 0 / a2: start10
		label:  / op: noop / a0:  / a1:  / a2: 10   done
		label: done / op: halt / a0: end / a1: of / a2: program10   five
		label: five / op: .fill / a0: 5 / a1:  / a2: 10   neg1
		label: neg1 / op: .fill / a0: -1 / a1:  / a2: 10   stAddr
		label: stAddr / op: .fill / a0: start / a1: will / a2: contain
		*/
		pc ++;
	}
	if (inFilePtr) {
		fclose(inFilePtr);
	}
	if (outFilePtr) {
		fclose(outFilePtr);
	}
	return(0);
}

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
		char *arg1, char *arg2)
{
	char line[MAXLINELENGTH];
	char *ptr = line;

	/* delete prior values */
	label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

	/* read the line from the assembly-language file */ 			// fgets 통해서 '\W' 기준 혹은 MAXLINELENGTH-1 개의 문자열 기준으로 문자열 판단해서 가져옴
	if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) { 			// (parameter) 1: 파일에서 가져온 문자열 저장할 변수, 2: 한번에 가지고 올 문자열의 길이, 3: 파일의 file pointer
		/* reached end of file */ 									// 파일끝까지 갔는데 읽을 것이 없는 경우 null 포인터 반환
		return(0);
	}
	// printf(line);

	/* check for line too long (by looking for a \n) */
	if (strchr(line, '\n') == NULL) {
		/* line too long */
		printf("error: line too long\n");
		exit(1);
	}

	/* is there a label? */
	ptr = line;
	if (sscanf(ptr, "%[^\t\n\r ]", label)) {
		/* successfully read label; advance pointer over the label */
		ptr += strlen(label);
		// printf("%d", strlen(label));
	}

	/*
	 * Parse the rest of the line.  Would be nice to have real regular
	 * expressions, but scanf will suffice.
	 */
	sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%"
			"[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]", opcode, arg0, arg1, arg2);
	// printf("%d   ", pc);
	// printf(arg2);printf("\n");
	// for (int i = 0; i < strlen(label); i++)
	// {
		// tmp_lableName[pc][0] = label;
	// }
	// printf(typeid(label).name());
	
	

	return(1);
}

int isNumber(char *string)
{
	/* return 1 if string is a number */
	int i;
	return( (sscanf(string, "%d", &i)) == 1);
}

int findLabel(char *label){
	for (int i = 0; i <= prog_length; i++){
		// printf(tmp_lableName[i]);printf("   ++   \n");
		if (!strcmp(tmp_lableName[i], label)){
			// printf("found label in %d \n",i);

			// printf("%c\n",*label);
			// if(i==4){
			// 	printf("===check===\n");
			// 	printf("%c\n",*tmp_lableName[i]);
			// 	printf("%c\n",*tmp_lableName[i+8]);
			// 	printf("%c\n",*tmp_lableName[i+10]);
			// 	printf("%c\n",*tmp_lableName[i+12]);
			// 	printf("%c\n",*tmp_lableName[i+14]);
			// }
			return i; // !! (해결-pc ++ 반복문 안에 2개 있었음... )
		}
	}
	return -1;
}
