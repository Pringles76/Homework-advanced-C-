#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int comparison(char s1[], char s2[]);

void main()
{
	// Variables
	char string1[30];
	char string2[30];

	// Instructions and input
	printf("Enter two strings.\n");
	printf("String 1: ");
	gets(string1);
	printf("String 2: ");
	gets(string2);

	// Function checking
	int x = comparison(string1, string2);
	switch (x)
	{
		case -1: printf("The first string is first in the order.\n"); break;
		case 0: printf("The two strings are a complete match.\n"); break;
		case 1: printf("The second string is the first in the order.\n"); break;
		case 2: printf("Error #1 - the strings do not exist.\n"); break;
		default: printf("An unknown error has occured in the function.\n"); break;
	}
}

int comparison(char s1[], char s2[])
{
	static int c = 0; // Position counter
	
	// Error and match ending conditions
	if ((s1[c] == '\0') && (s2[c] == '\0'))
	{
		// Error ending condition
		if (c == 0)
		{
			return 2;
		}

		// Match ending condition
		else
		{
			return 0;
		}
	}

	// String 1 ending condition
	if ((s1[c] > s2[c]) || ((s2[c] == '\0') && (s1[c] != '\0')))
	{
		return 1;
	}

	// String 2 ending condition
	if ((s1[c] < s2[c]) || (s1[c] == '\0') && (s2[c] != '\0'))
	{
		return -1;
	}

	// General progression
	if ((s1[c] == s2[c]) && (s1[c] != '\0') && (s2[c] != '\0'))
	{
		c++;
		return comparison(s1, s2);
	}
}