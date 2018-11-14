// Simpletron.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define READ 10
#define WRITE 11

#define LOAD 20
#define STORE 21

#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

#define MEMSIZE 100
#define UPLIMIT	9999		
#define LOWLIMIT -9999
#define SENTINEL -99999	

void Welcome(void);
void dump(const int[], int, int);

int main()
{
	int memory[MEMSIZE] = { 0 };

	int accumulator;		
	int operationCode;		
	int operand;			
	int instructionCounter;	
	int instructionRegister;

	Welcome();

	for (instructionCounter = 0; instructionCounter < MEMSIZE; instructionCounter++) {
		
		printf_s("%.2d ? ",instructionCounter);
		scanf_s("%d", &memory[instructionCounter]);

		//判斷是否為結束指令
		if (memory[instructionCounter] == SENTINEL) 
		{
			memory[instructionCounter] = 0;
			break;
		}

		//輸入大於9999或小於-9999,顯示錯誤並重新輸入
		while (memory[instructionCounter] > UPLIMIT || memory[instructionCounter] < LOWLIMIT)
		{
			printf_s("*** Unknown instruction ***\n");
			printf_s("*** Enter again or exit ***\n");
			printf_s("%.2d ? ", instructionCounter);
			scanf_s("%d", &memory[instructionCounter]);
		}
	}

	printf_s("*** Program loading completed ***\n");
	printf_s("*** Program execution begins  ***\n\n");

	//初始化變數
	accumulator = 0;
	operationCode = 0;
	operand = 0;
	instructionCounter = 0;
	instructionRegister = 0;

	for (instructionCounter ; instructionCounter < MEMSIZE; instructionCounter++)
	{

		instructionRegister = memory[instructionCounter];

		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;

		switch (operationCode)
		{
		case READ:
			printf_s("Enter a number between %d and %d : ", LOWLIMIT, UPLIMIT);
			scanf_s("%d", &memory[operand]);
			while (memory[operand] < LOWLIMIT || memory[operand] > UPLIMIT)
			{
				printf_s("*** Out of memory ***\n");
				printf_s("again sent a number : ");
				scanf_s("%d", &memory[operand]);
			}
			break;

		case WRITE:
			printf_s("Result : %d \n", memory[operand]);
			break;

		case LOAD:
			accumulator = memory[operand];
			break;

		case STORE:
			memory[operand] = accumulator;
			break;

		case ADD:
			accumulator += memory[operand];
			if (accumulator < LOWLIMIT || accumulator > UPLIMIT) {
				printf_s("*** Out of accumulator limit ***\n");
				printf_s("*** Simpletron execution abnormally terminated ***\n");
				dump(memory, accumulator, instructionCounter);
				instructionCounter = MEMSIZE;
			}
			break;

		case SUBTRACT:
			accumulator -= memory[operand];
			if (accumulator < LOWLIMIT || accumulator > UPLIMIT) {
				printf_s("*** Out of accumulator limit ***\n");
				printf_s("*** Simpletron execution abnormally terminated ***\n");
				dump(memory, accumulator, instructionCounter);
				instructionCounter = MEMSIZE;
			}
			break;

		case DIVIDE:
			accumulator /= memory[operand];
			if (accumulator < LOWLIMIT || accumulator > UPLIMIT) {
				printf_s("*** Out of accumulator limit ***\n");
				printf_s("*** Simpletron execution abnormally terminated ***\n");
				dump(memory, accumulator, instructionCounter);
				instructionCounter = MEMSIZE;
			}
			break;

		case MULTIPLY:
			accumulator *= memory[operand];
			if (accumulator < LOWLIMIT || accumulator > UPLIMIT) {
				printf_s("*** Out of accumulator limit ***\n");
				printf_s("*** Simpletron execution abnormally terminated ***\n");
				dump(memory, accumulator, instructionCounter);
				instructionCounter = MEMSIZE;
			}
			break;

		case BRANCH:
			instructionCounter = operand;
			break;

		case BRANCHNEG:
			if (accumulator < 0)
			{
				instructionCounter = operand;
			}
			break;

		case BRANCHZERO:
			if (accumulator == 0)
			{
				instructionCounter = operand;
			}
			break;

		case HALT:
			printf_s("*** Simpletron execution terminated ***\n\n");
			dump(memory, accumulator, instructionCounter);
			instructionCounter = MEMSIZE;
			break;
			
		default:
			break;
		}

	}
	system("pause");

}

void Welcome(void) {


	printf_s(
	    "*** ---------Welcome to Simpletron!---------- ***\n"
		"*** Please enter your program one instruction ***\n"
		"*** (or data word) at a time. I will type the ***\n"
		"*** location number and a question mark (?) . ***\n"
		"*** You then type the word for that location. ***\n"
		"*** Type the sentinel -99999 to stop entering ***\n"
		"*** your program. ----------------------------***\n\n");

}

void dump(const int memory[], int accumulator, int instructionCounter) {

	int i, j;

	printf_s("REGISTERS:\n");
	printf_s("accumulator \t\t%c%.4d\n", accumulator < 0 ? '-' : '+', accumulator);
	printf_s("instructionCounter \t%3c%.2d\n", ' ', instructionCounter);
	printf_s("instructionRegister \t%c%.4d\n", memory[instructionCounter] < 0 ? '-' : '+', memory[instructionCounter]);
	printf_s("operationCode \t\t%3c%.2d\n", ' ', memory[instructionCounter] / 100);
	printf_s("operand \t\t%3c%.2d\n\n", ' ', memory[instructionCounter] % 100);

	
	printf_s("MEMORY : \n");

	
	printf_s("%3c", ' ');

	for (i = 0; i < 10; i++)
		printf_s("%5d ", i);

	printf_s("\n");

	for (i = 0; i < MEMSIZE; i += 10) {
		printf_s("%.2d", i);

		for (j = i; j < i + 10; j++)
			printf_s(" %c%.4d", memory[j] < 0 ? '-' : '+', memory[j] < 0 ? -memory[j] : memory[j]);

		printf_s("\n");
	}

	printf_s("\n");
}


