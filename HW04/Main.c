#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define MAXCOUNT 1023

#include <stdlib.h>
#include <crtdbg.h> //uncomment this block to check for heap memory allocation leaks.
// Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct StudentCourseGrade
{
	char courseName[35];
	int grade;
}StudentCourseGrade;

typedef struct Student
{
	char name[35];
	StudentCourseGrade* grades; //dynamic array of courses
	int numberOfCourses;
}Student;


//Part A
void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
int countPipes(const char* lineBuffer, int maxCount);
char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents);
void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor);
void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents);

//Part B
Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents);
void writeToBinFile(const char* fileName, Student* students, int numberOfStudents);
Student* readFromBinFile(const char* fileName);

int main()
{
	// function 1 checking
	/*char string[] = "Hello|world|";
	int max = 100;
	printf("%d", countPipes(string, max));*/

	// function 2 checking
	/*char filename[] = "studentList.txt";
	int numberOfStudents = 0;
	int* coursesPerStudent = NULL;
	countStudentsAndCourses("studentList.txt", &coursesPerStudent, &numberOfStudents);
	printf("%d\n", numberOfStudents);
	for (int i = 0; i < numberOfStudents; i++)
	{
		printf("%d\n", coursesPerStudent[i]);
	}*/

	// function 3 checking
	char filename[] = "studentList.txt";
	int numberOfStudents = 0;
	int* coursesPerStudent = NULL;
	makeStudentArrayFromFile(filename, &coursesPerStudent, &numberOfStudents);


	// function 4 checking



	// function 5 checking



	// function 6 checking




	////Part A
	//int* coursesPerStudent = NULL;
	//int numberOfStudents = 0;
	//char*** students = makeStudentArrayFromFile("studentList.txt", &coursesPerStudent, &numberOfStudents);
	//factorGivenCourse(students, coursesPerStudent, numberOfStudents, "Advanced Topics in C", +5);
	//printStudentArray(students, coursesPerStudent, numberOfStudents);
	////studentsToFile(students, coursesPerStudent, numberOfStudents); //this frees all memory. Part B fails if this line runs. uncomment for testing (and comment out Part B)
	//
	////Part B
	//Student* transformedStudents = transformStudentArray(students, coursesPerStudent, numberOfStudents);
	//writeToBinFile("students.bin", transformedStudents, numberOfStudents);
	//Student* testReadStudents = readFromBinFile("students.bin");

	////add code to free all arrays of struct Student


	_CrtDumpMemoryLeaks(); //uncomment this block to check for heap memory allocation leaks.
	// Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019

	return 0;
}

// ****************************** Text Part ****************************** //

void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
	// Variables
	char container[MAXCOUNT];	// Buffer
	int lineC = 0;				// Line counter. To be used as numbers of students

	// File opening
	FILE* file = fopen(fileName, "rt");
	if (file == NULL)
	{
		puts("Error: Function count students and courses >> file opening error.");
		exit(1);
	}

	// Student counting
	while (fgets(container, MAXCOUNT, file))
	{
		lineC++;
	}
	fseek(file, 0, SEEK_SET);

	// Number of students value assigning
	*numberOfStudents = lineC;

	// Temporary array to be used as courses per student
	int* array = (int*)malloc(lineC * (sizeof(int)));
	if (array == NULL)
	{
		puts("Error: Function count students and courses >> memory allocation faliure.");
		exit(1);
	}
	else
	{
		*coursesPerStudent = array;
	}

	// Number of courses for each student assigning
	for (int i = 0; i < lineC; i++)
	{
		fgets(container, MAXCOUNT, file);
		array[i] = countPipes(container, MAXCOUNT);
	}

	// File closing
	fclose(file);
}

int countPipes(const char* lineBuffer, int maxCount)
{
	// Variables
	int pipeC = 0;				// scanned pipes counter
	int charC = 0;				// scanned chars coutner
	char* Sptr = lineBuffer;	// scanned char pointer

	while ((*Sptr != '\0') && (charC <= maxCount))
	{
		// Pipe counts
		Sptr = strchr(Sptr, '|');

		// case 1: no pipes found
		if (Sptr == NULL)
		{
			return pipeC;
		}
		// Case 2: pipe found
		else
		{
			pipeC++;
			Sptr++;
		}
		charC++;
	}
	// Pipe counts returning from case 2
	return pipeC;
}

char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
	// Variables
	char*** array;				// 3D array to be used as the returning triple pointer
	char container[MAXCOUNT];	// Buffer to be used for lines read from the file
	char* Sptr1 = container;	// String pointer to be used for the third dimention memory allocation [starting position]
	char* Sptr2 = container;	// String pointer to be used for the third dimention memory allocation [ending position]

	// File opening
	FILE* file = fopen(fileName, "rt");
	if (file == NULL)
	{
		puts("Error: Function count students and courses >> file opening error.");
		exit(1);
	}

	// Data recieving from previous functions
	countStudentsAndCourses(fileName, coursesPerStudent, numberOfStudents);

	// First dimention memory allocation [as the number of the students]
	array = (char***)malloc((*numberOfStudents) * (sizeof(char**)));
	if (array == NULL)
	{
		puts("Error: function make student array from file >> first dimention memory allocation faliure.");
		exit(1);
	}

	// Second dimention memory allocation [as the number of the courses per student X2, plus one more for the student's name]
	for (int i = 0, j = 0; i < *numberOfStudents; i++)
	{
		array[i] = (char**)malloc((1 + (*coursesPerStudent[i]) * 2) * sizeof(char*));
		if (array[i] == NULL)
		{
			puts("Error: function make student array from file >> second dimention memory allocation faliure.");
			exit(1);
		}

		// Third dimention block >>> memory allocation [as the string length per token]
		fgets(container, MAXCOUNT, file);

		// Student name catching from file and memory allocation		
		Sptr2 = strtok(Sptr1, '|');
		array[i][j] = (char*)malloc((strlen(Sptr1) + 1) * sizeof(char));
		if (array[i][j] == NULL)
		{
			puts("Error: function make student array from file >> third dimention memory allocation faliure.");
			exit(1);
		}
		array[i][j] = Sptr1;

		// Variables advance for the course name catching
		Sptr1 = (Sptr2 + 1);
		j++;

		// Course name and course grade catching from file
		while (j < (1 + (*coursesPerStudent[i]) * 2))
		{

			// Course name catching from file and memory allocation
			Sptr2 = strtok(Sptr1, ',');
			array[i][j] = (char*)malloc((strlen(Sptr2) + 1) * sizeof(char));
			if (array[i][j] == NULL)
			{
				puts("Error: function make student array from file >> third dimention memory allocation faliure.");
				exit(1);
			}
			array[i][j] = Sptr1;

			// Variables advance for the course grade catching
			Sptr1 = (Sptr2 + 1);
			j++;

			// Course grade catching from file and memory allocation
			Sptr2 = strtok(Sptr1, '|');
			array[i][j] = (char*)malloc((strlen(Sptr1) + 1) * sizeof(char));
			if (array[i][j] == NULL)
			{
				puts("Error: function make student array from file >> third dimention memory allocation faliure.");
				exit(1);
			}
			array[i][j] = Sptr1;

			// Variable advance for the next inner loop / for exiting the inner loop
			Sptr1 = (Sptr2 + 1);	// This could leak from the line. Is this ok? The loop is checked by j. In the worst case, add an if that checks if j still meets the terms before advancing the Sptr.
			j++;
		}
		// Column variable initialization for the next outer loop
		j = 0;
	}
	fseek(file, 0, SEEK_SET);

	// File closing
	fclose(file);
}

void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor)
{
	//add code here
}

void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents)
{
	for (int i = 0; i < numberOfStudents; i++)
	{
		printf("name: %s\n*********\n", students[i][0]);
		for (int j = 1; j <= 2 * coursesPerStudent[i]; j += 2)
		{
			printf("course: %s\n", students[i][j]);
			printf("grade: %s\n", students[i][j + 1]);
		}
		printf("\n");
	}
}

void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents)
{
	//add code here
}

// ****************************** Binary Part ****************************** //

void writeToBinFile(const char* fileName, Student* students, int numberOfStudents)
{
	//add code here
}

Student* readFromBinFile(const char* fileName)
{
	//add code here
}

Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents)
{
	//add code here
}
