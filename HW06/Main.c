#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int pack4Chars2Int(char c1, char c2, char c3, char c4);
int checkEvenPairity(short input);

void main()
{
	// Instructions and input for function 1
	char a, b, c, d;
	printf("Enter 4 chars for the function 1: ");
	scanf("%c %c %c %c", &a, &b, &c, &d);
	printf("\nVariables before:\na: %b\nb: %b\nc: %b\nd: %d\n", a, b, c, d);

	// Function 1 activation
	int value1 = pack4Chars2Int(a, b, c, d);
	printf("\nVariable after:\nint: %b", value1);

	// Instruction and input for function 2
	int n;
	printf("\n Enter an integer for function 2: ");
	scanf("%d", &n);

	// Function 2 activation
	int value2 = checkEvenPairity(n);
	switch (value2)
	{
	case 0: printf("\nThe number of bits is uneven\n"); break;
	case 1: printf("\nThe number of bits is even\n"); break;
	default: printf("\nAn unknown error has occured\n"); break;
	}
}

int pack4Chars2Int(char c1, char c2, char c3, char c4)
{
	// Variables
	int toReturn = 0;
	int temp = 0;
	int whole = 32;
	int shift = 8;

	// C1 insertion
	temp |= c1;
	temp <<= (whole - shift);
	toReturn |= temp;

	// Variables initialization
	shift += 8;
	temp = 0;

	// C2 insertion
	temp |= c2;
	temp <<= (whole - shift);
	toReturn |= temp;

	// Variables initialization
	shift += 8;
	temp = 0;

	// C3 insertion
	temp |= c3;
	temp <<= (whole - shift);
	toReturn |= temp;

	// C4 insertion
	toReturn |= c4;

	return toReturn;
}

int checkEvenPairity(short input)
{
	// Variables
	short mask = 1;
	int counter = 0;

	// Function loop
	while (mask != 0)
	{
		// ones checking
		if ((input & mask) != 0)
		{
			counter++;
		}

		// Variables advancement
		mask <<= 1;
	}

	// Even / odd checking
	if ((counter % 2) == 0)
	{
		return 1;	// even
	}
	else
	{
		return 0;	// odd
	}
}