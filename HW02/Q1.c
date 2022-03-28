// Defines
#define _CRT_SECURE_NO_WARNINGS		// Trust mode
#define TNL 30						// Temporary Name Length
#define HYL 6						// Heberew Year Length

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked list structures
typedef struct Worker			// Worker structure definition
{
	unsigned long id;			// ID number
	char* name;					// First name
	unsigned long salary;		// Salary
	union Year					// Year type: [Heberew / Foreign]
	{
		char Hyear[HYL];		// Heberew year type option
		unsigned long Fyear;	// Foreign year type option
	}Year;
}Worker;						// Definition

typedef struct WorkerList		// WorkerList structure definition
{
	Worker* data;				// Data that contains the items of Woker structure
	struct WorkerList* next;	// Pointer to the next item
} WorkerList;					// Definition

// Functions signatures
Worker* CreateWorker(unsigned long id, char* name, unsigned long salary, char Hyear[], char Fyear, int Ytype);		// Create Worker
void PrintWorker(Worker* head, int Ytype);																			// Print Worker
WorkerList* addWorker(WorkerList* head, Worker* w);																	// Add Worker
int indexL(WorkerList* head, long unsigned id);																		// Index Finder (loop version)
int indexR(WorkerList* head, long unsigned id);																		// Index Finder (recursive version)
WorkerList* deleteWorstWorker(WorkerList* head);																	// Delete Worst Worker
void update_worker(WorkerList* head, float percent);																// Update Worker
WorkerList* reverse(WorkerList* head);																				// Reverst Workers
void freeWorkers(WorkerList* head);																					// Free Workers

// Main function
void main()
{
	// Starting variables
	WorkerList* head = NULL;

	// Add worker and Create worker
	head = addWorker(head, CreateWorker(123456789, "Eyal", 10000, "tspb", 2010, 1));		// First worker
	head = addWorker(head, CreateWorker(456789123, "Ben", 7000, "tspa", 2016, 1));			// Second worker
	head = addWorker(head, CreateWorker(789123456, "Orel", 13000, "tspg", 2020, 0));		// Third worker
	head = addWorker(head, CreateWorker(321654987, "Lior", 8000, "tspb", 2012, 0));			// Fourth worker

	// Print Worker
	WorkerList* check = head;		// Running worker pointer
	int Ytype;						// Year type [H / F]
	do
	{
		printf("Enter a year type: 0 for heberew, 1 for foreign.\nYour choice: ");		// Instructions
		fseek(stdin, 0, SEEK_END);														// Buffer cleaning
		scanf("%d", &Ytype);															// Year type input
		if ((Ytype != 0) && (Ytype != 1)) { puts("Invalid format. Try again."); }		// If the year type is not in the right format
	} while ((Ytype != 0) && (Ytype != 1));												// Right format condition
	printf("\n");

	while (check)						// While the running pointer is still in the list
	{
		PrintWorker(check, Ytype);		// Print the current worker
		check = check->next;			// Advance the pointer to the next worker
	}
	printf("\n");
	
	// Index finder (loop format)
	int id;														// Temporary id variable to put in the funcion
	int index;													// Temporary index variable for the switch function
	printf("Enter an ID to find the index of the worker: ");	// Instructions
	scanf("%ld", &id);											// ID input
	index = indexL(head, id);									// Index finder (loop version) function
	switch (index)
	{
		case -1: puts("The ID was not found in the workers list"); break;	//  If the ID was not found in the list
		default: printf("The index of the worker: %d", index); break;		// If the ID was found in the list, print the index
	}
	printf("\n");

	// Index finder (recursive format)
	printf("Enter an ID to find the index of the worker: ");			// Instructions
	scanf("%ld", &id);													// ID input
	index = indexR(head, id);											// Index finder (recursive format) function
	switch (index)
	{
	case -1: puts("The ID was not found in the workers list"); break;	// If the ID was not found in the list
	default: printf("The index of the worker: %d", index); break;		// If the ID was found in the list, printf the index
	}
	printf("\n");

	// Deleting the worst worker
	deleteWorstWorker(head);
	
	// Updating the workers' salary
	float percent;														// Temporary variable for the percent multiplication
	printf("Enter a percent to multiply the workers salary by: ");		// Instructions
	scanf("%f", &percent);												// Percent input
	update_worker(head, percent);										// Salary updating function

	// Reversing the workers list
	reverse(head);

	// Releasing all the workers
	freeWorkers(head);
}

// Worker creation function [MANUAL VERSION]
Worker* CreateWorker(unsigned long id, char* name, unsigned long salary, char Hyear[], char Fyear, int Ytype)
{
	// Memory allocation and faliure condition
	Worker* temp = (Worker*)malloc(sizeof(Worker));									// Temp creation
	if (!temp) { puts("Malloc failure [CreateWorker >> temp malloc]"); exit (1); }	// Temp malloc faliure
	
	// Function actions
	temp->id = id;																				// ID input
	temp->name = (char*)malloc((strlen(name) + 1) * sizeof(char));								// Name length correction
	if (!temp->name) { puts("Malloc faliure[CreateWorker >> temp->name malloc]"); exit(1); };	// Name malloc faliure
	strcpy(temp->name, name);																	// Name input
	temp->salary = salary;																		// Salary input																		// Year type input
	if (Ytype == 0)																				// Heberew year input
	{
		strcpy(temp->Year.Hyear, Hyear);														// Set the start year in heberew format
	}
	else if (Ytype == 1)																		// Foreign year input
	{
		temp->Year.Fyear = Fyear;																// Set the start year in foreign format
	}
	else
	{
		puts("Error [CreateWorker >> Ytype was neither '0' nor '1'"); exit(1);					// Error in the year type format
	}
	return temp;																				// Return temp as the head
}


// Worker printing function
void PrintWorker(Worker* head, int Ytype)
{
	// Function actions
	puts("Worker details:");
	switch (Ytype)
	{
		case 0: printf("ID: %ld\nName: %s\nSalary: %ld\nStart year: %s\n", head->id, head->name, head->salary, head->Year.Hyear); break;	// Heberew format printing
		case 1: printf("ID: %ld\nName: %s\nSalary: %ld\nStart year: %ld\n", head->id, head->name, head->salary, head->Year.Fyear); break;	// Foreign format printing
		default: puts("Error: Printworker_switch value was neither 0 nor 1"); break;														// Error condition
	}
	printf("\n");
}

// Worker adding function
WorkerList* addWorker(WorkerList* head, Worker* w)
{
	// Empty list condition [1/2]
	if (head == NULL)
	{
		head = (WorkerList*)malloc(sizeof(WorkerList));								// Head creation
		if (!head) { puts("Malloc faliure [addWorker >> head malloc]"); exit(1); }	// Head malloc faliure
		head->data = w;																// Head->data input
		head->next = NULL;															// Head->next input
		return head;																// Returning the head as is
	}

	// Existing list condition [2/2]
	WorkerList* temp = (WorkerList*)malloc(sizeof(WorkerList));						// Temp creation
	if (!temp) { puts("Malloc faliure [addWorker >> temp malloc]"); exit(1); }		// Temp malloc faliure
	temp->data = w;																	// Temp data input

	// Assisting variables for condition [2/2]
	WorkerList* curr = head;						// Current position index
	WorkerList* prev = NULL;						// Previous position index

	// Lowest salary condition [2/2/1]
	if (temp->data->salary <= curr->data->salary)	// If the temp's salary is the lowest in the list
	{
		temp->next = head;							// Chain temp->next to the head
		return temp;								// Return the temp as the head
	}

	// General salary condition [2/2/2]
	while ((curr != NULL) && (curr->data->salary <= temp->data->salary))	// If the temp's salary is not the lowest in the list
	{
		prev = curr;			// Point the previous index to the current index
		curr = curr->next;		// Point the current index to the next index
	}
	if (curr == NULL)			// If the temp's salary is the highest in the list
	{
		temp->next = NULL;		// Point the temp's next to NULL
		prev->next = temp;		// Point the prev's next to temp
	}
	else                        // If the temp's salary is in the middle of the list
	{
		temp->next = curr;		// Point the temp's next to the curr's index
		prev->next = temp;		// Point the prev's next to the temp's index
	}
	return head;				// Return the original head as is
}

// Worker index function [loop version]
int indexL(WorkerList* head, long unsigned id)
{
	WorkerList* curr = head;							// Current creation
	int dex = 1;										// Current index
	while ((curr != NULL) && (curr->data->id != id))	// While current exists, and it's data is not equal to the id
	{
		curr = curr->next;								// Point current to the next worker
		dex++;											// Add 1 to the index
	}
	if (curr == NULL) { return -1; }					// If the id doesn't appear in the workers list - return -1
	return dex;											// Return the index of the worker
}

// Worker index function [recursive version]
int indexR(WorkerList* head, long unsigned id)
{
	static int dex = 1;				// Index variable

	// Ending condition [1/2] - id not found in the list
	if (head == NULL)				// If the pointer made it to the end of the list
	{
		dex = 1;					// Static int zeroise
		return -1;					// Return -1 as the id was not found
	}

	// Ending condition [2/2] - id found in the list
	if (head->data->id == id)		// If the id was found
	{
		int newdex = dex;			// Index variable that replaces the static one in order to zeroise it
		dex = 1;					// Static int zeroise
		return newdex;				// Return the index
	}
	dex++;							// Add 1 to the index
	indexR(head->next, id);			// Advance the pointer to the next worker
}

// Worst worker deleting function
WorkerList* deleteWorstWorker(WorkerList* head)
{
	// Empty list condition [1/3]
	if (head == NULL) { return head; }		// If the list doesn't exist, return the head as is (NULL)

	// 1 item list condition [2/3]
	if (head->next == NULL)					// If the next item from the start doesn't exist
	{
		free(head->data->name);				// Free the name
		free(head->data);					// Free the data
		free(head);							// Free the head
		return head;						// Return the head as is (NULL)
	}

	// Variables for condition [3/3]
	WorkerList* curr = head;				// Current index
	WorkerList* prev = NULL;				// Previous index
	WorkerList* worst = curr;				// Worst worker index
	WorkerList* worstPrev = NULL;			// Index to the previous item of the worst worker

	// Existing list condition [3/3]
	while (curr != NULL)								// While the pointer didn't each the end of the list
	{
		prev = curr;									// Point prev to curr
		curr = curr->next;								// Point curr to curr next
		if (curr->data->salary < worst->data->salary)	// If the curr's salary is smaller than the worst's one
		{												// Connect worst to the list
			worst = curr;								// Point worst to curr
			worst->next = curr->next;					// Point worst's next to curr's next
			worstPrev = prev;							// Point worst's prev to prev
			worstPrev->next = prev->next;				// Point worst's prev's->next to prev's next in order to connect the two flanks
		}
	}
	free(worst->data->name);				// Free worst's name
	free(worst->data);						// Free worst's data
	free(worst);							// Free worst itself
	return head;							// Return the head of the list as is
}

// Salary raise function
void update_worker(WorkerList* head, float percent)
{
	// Empty list condition
	if (head == NULL) { return; }						// If the list is empty, Return to main function

	// Existing list condition
	WorkerList* ptr = head;								// Pointer creation
	while (ptr != NULL)									// While the pointer didn't reach the end of the list
	{
		ptr->data->salary *= ((percent / 100) + 1);		// Multiply the ptr's salary by percent%
		ptr = ptr->next;								// Point to the next item
	}
	return;												// Return to main function
}

// list reversing function
WorkerList* reverse(WorkerList* head)
{
	WorkerList* prev = NULL;		// Previous index
	WorkerList* curr = head;		// Current index
	WorkerList* next = NULL;		// Next index

	while (curr != NULL)			// While curr is inside the list
	{
		next = curr->next;			// Point next to curr->next
		curr->next = prev;			// Point curr->next to prev
		prev = curr;				// Point prev to curr
		curr = next;				// Point curr to next
	}
	return prev;					// Return the prev as the new head
}

// Memory free function
void freeWorkers(WorkerList* head)
{
	// Empty list condition [1/2]
	if (head == NULL) { return; }			// If the list is empty, return to main function

	// Existing list condition [2/2]
	WorkerList* curr = head;				// Current index
	WorkerList* prev = NULL;				// Previous index
	while (curr != NULL)					// While the current index is inside the list
	{
		curr = curr->next;					// Point curr to curr->next
		prev = curr;						// Point prev to curr
		free(prev->data->name);				// Free prev's name
		free(prev->data);					// Free prev's data
		free(prev);							// Free prev itself
	}
	return;									// Return to main function
}