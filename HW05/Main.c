// Standart header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Current assignment header files
#include "BST.h"
#include "TreePrintLibrary.h"

void main()
{
	// Initialization check [1/6]
	BST T1;
	initBST(&T1);

	// Insertion check [2/6]
	insertBST(&T1, 5);
	insertBST(&T1, 2);
	insertBST(&T1, 8);
	insertBST(&T1, 1);
	insertBST(&T1, 4);
	insertBST(&T1, 9);
	//insertBST(&T1, 5);
	//insertBST(&T1, 5);
	//insertBST(&T1, 8);
	//insertBST(&T1, 9);
	//insertBST(&T1, 8);
	//insertBST(&T1, 9);

	// Printing check [3/6]
	printTreeInorder(&T1);
	print_ascii_tree(T1.root);
	printf("\n");

	// Index finding check [5/6]
	int I = findIndexNFromLast(&T1, 4);
	printf("The element in index 4 from last is: %d\n\n", I);

	// Same hight check [6/6]
	int S = sameHeightLeaves(&T1);
	if (S == 1)
	{
		puts("All leaves are the same height.");
	}
	else
	{
		puts("Not all leaves are the same height.");
	}

	// Destruction check [4/6]
	destroyBST(&T1);
}