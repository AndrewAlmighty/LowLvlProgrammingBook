#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "linkedlist.h"

void square(int *n)
{
	*n = (*n) * (*n);	
}

void cube(int *n)
{
	*n = (*n) * (*n) * (*n);	
}

void poweroftwo(int *n)
{
	*n *= 2;
}

void printNumber(int *n)
{
	printf("%d ", *n);
}

void printNumberNewLine(int *n)
{
	printf("%d\n", *n);
}

void sum(int *num, int* ac)
{
	*ac += *num;
}

void find_min(int *num, int* ac)
{
	if(*num < *ac)
		*ac = *num;
}

void find_max(int *num, int *ac)
{
	if(*num > *ac)
		*ac = *num;
}

int main(int argc, char** argv)
{
	struct list *linked_list = NULL;
	int number;
	
	puts("Initializing linked list ...\n");
	
	//TASK 1
	//number used temporary
	for(number = 1; number < argc; number++)
	{
		list_add_back(atoi(argv[number]), &linked_list);	
	}
	
	//TASK 3
	puts("Initializing done! Result:");
	foreach(linked_list, &printNumber);
	puts("\n");
	foreach(linked_list, &printNumberNewLine);
	
	//TASK 4
	{
		struct list *tempList = NULL;
		tempList = map(linked_list, &square);
		puts("\nTASK 4 - output squares and cubes of the nnumbers from the list\nSquares:");
		foreach(tempList, &printNumber);
		list_free(&tempList);
		puts("\nCubes:");
		tempList = map(linked_list, &cube);
		foreach(tempList, &printNumber);
		list_free(&tempList);
		puts("\n");
	}
	
	//TASK 5
	puts("TASK 5 - FOLDL - SUM / MIN/ MAX\n");
	printf("SUM OF ELEMENTS: %d\n", foldl(0, &sum, linked_list));
	printf("MIN EL OF THE LIST: %d\n", foldl(INT_MAX, &find_min, linked_list));
	printf("MAX EL OF THE LIST: %d\n", foldl(INT_MIN, &find_max, linked_list));
		
	//TASK 7
	{
		struct list *tempList = NULL;
		tempList = iterate(1, 10, &poweroftwo);
		puts("\nTASK 7 - ITERATE - 10 values of power of 2\nLIST:");
		foreach(tempList, &printNumber);
		list_free(&tempList);
		puts("\n");
	}
	
	//TASK 8 - SAVE THE LIST TO FILE!
	puts("TASK 8 - SAVE THE LIST AND CLEAN THE LIST!");
	
	if(save(linked_list, "./linkedlist.txt") == true)
	{
		puts("The list has been saved and cleaned!\nThe list now:");
		list_free(&linked_list);
		foreach(linked_list, &printNumber);
	}
	
	else
		puts("ERROR! LIST CANNOT BE SAVED!! LIST NOT FREED!\n");
	
	//TASK 9 - LOAD THE LIST FROM FILE!
	puts("\nTASK 9 - LOAD THE LIST FROM FILE!");
	
	if(load(&linked_list, "./linkedlist.txt") == true)
	{
		puts("The list has been loaded!\nThe list now:");
		foreach(linked_list, &printNumber);
	}
	
	else
		puts("ERROR! CANNOT LOAD FILE!");
	
	//TASK 10 - SAVE THE LIST TO BINARY FILE!
	puts("\n\nTASK 10 - SAVE LIST TO BINARY FILE AND CLEAR LIST!");
	
	if(serialize(linked_list,"./linkedlist.bin") == true)
	{
		puts("The list has been saved to binary file and cleaned!\nThe list now:");
		list_free(&linked_list);
		foreach(linked_list, &printNumber);
	}
	
	else
		puts("ERROR! CANNOT LOAD FILE!");
	
	//TASK 11 - LOAD THE LIST FROM BINARY FILE!
	puts("\nTASK 11 - LOAD THE LIST FROM BINARY FILE!");
		
	if(deserialize(&linked_list, "./linkedlist.bin") == true)
	{
		puts("The list has been loaded!\nThe list now:");
		foreach(linked_list, &printNumber);
		puts("\n");
	}
	
	else
		puts("ERROR! CANNOT LOAD FILE!");
	
	return 0;
}