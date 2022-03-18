#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int counter(int number, int divider);

void main()
{
	// Variables
	int number, divider;

	// Instructions and input
	printf("Enter a number: ");
	scanf("%d", &number);
	printf("Enter a divider: ");
	scanf("%d", &divider);


	// Solution
	int x = counter(number, divider);
	printf("The number of divides without remainders: %d\n", x);
}

int counter(int number, int divider)
{
	static int count = 0;

	// Ending condition
	if (number == 0)
	{
		return count;
	}

	// General progression
	int temp = number % 10;
	if (temp % divider == 0)
	{
		count++;
	}
	counter(number / 10, divider);
}