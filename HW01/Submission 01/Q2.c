#define _CRT_SECURE_NO_WARNINGS
#define N 5
#include <stdio.h>

int path_exists(int mat[][N], int rowdex, int coldex, int rows, int cols);

void main()
{
	// Variables
	int matrix[N][N] = { 0 };	// Coordinations map [NXN]
	int rows = N - 1;			// Rows number
	int cols = N - 1;			// Coloumns number
	int rowdex = 0;				// Vertical position
	int coldex = 0;				// Horizontal position

	// Instructions and input
	printf("Enter ones or zeroes for the %dX%d matrix.\n\n", N, N);
	for (int i = 0; i < N; i++)
	{
		printf("For row #%d: ", i);
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &matrix[i][j]);
		}
	}
	printf("\n");

	// Function checking
	int x = path_exists(matrix, rowdex, coldex, rows, cols);
	switch (x)
	{
	case 0: printf("The path does not exist\n"); break;
	case 1: printf("The path exists\n"); break;
	case 2: printf("Error #1 - The index exceeded the maps borders.\n"); break;
	default: printf("Error #2 - The result of the function was neither 0 or 1.\n"); break;
	}
}


int path_exists(int mat[][N], int rowdex, int coldex, int rows, int cols)
{
	// Success sign
	static int trigger = 0;

	// Success condition
	if ((rows == 0) && (cols == 0) || (trigger == 1))
	{
		trigger = 1;
		return trigger;
	}

	// Starting and ending faliure conditions
	if ((mat[rowdex][coldex] == 0) || (mat[N - 1][N - 1] == 0))
	{
		return 0;
	}

	// Border faliure condition
	if (rowdex > N - 1 || coldex > N - 1)
	{
		return 2;
	}

	// General progression

	// Diagonal step
	if ((mat[rowdex + 1][coldex + 1] == 1) && ((rows > 0) && (cols > 0)))
	{
		path_exists(mat, rowdex + 1, coldex + 1, rows - 1, cols - 1);
	}

	// Right step
	if ((mat[rowdex][coldex + 1] == 1) && ((cols > 0)))
	{
		path_exists(mat, rowdex, coldex + 1, rows, cols - 1);
	}

	// Down step
	if ((mat[rowdex + 1][coldex] == 1) && ((rows > 0)))
	{
		path_exists(mat, rowdex + 1, coldex, rows - 1, cols);
	}

	// General faliur condition
	return trigger;
}