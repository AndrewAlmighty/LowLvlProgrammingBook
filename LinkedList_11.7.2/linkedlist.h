#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <malloc.h>

struct list
{
	int number;
	struct list *next;
};

struct list* list_create(const int n);	//Creates a new node of list
void list_add_front(const int number, struct list** pptr);	//Addes a new element in front of the lsit
void list_add_back(const int number, struct list** pptr);	//Addes a new element in back of the list
void list_free(struct list** list);	//Frees the memory
size_t list_length(struct list** list);	//Returns the size of our list
struct list* list_node_at(struct list** list, const size_t index);	//returns an element of the list
int list_sum (struct list** list);	//returns a sum of all elements of the list
int list_get(struct list* list, const size_t index);	//returns an index of the list
void list_show(struct list* pptr);	//shows the whole list
void foreach(struct list* lptr, void (*fptr)(int*));	//Invoke a function on every element on the list
struct list* map(struct list* lptr, void (*fptr)(int*));	//Invoke a function on every element on the list and return a new list
void map_mut(struct list* lptr, void (*fptr)(int*));	//Invoke a function on the original list
int foldl(int b_ac, void(*fptr)(int*, int*), struct list* list);	//Invoke a function on list and returns an acumulator
struct list* iterate(int num, int len, void (*fptr)(int*));	//Invoke a function loop on every element of the list
bool save(struct list* lst, const char* filename); //write all elements of the list into a text file filename. Retyrn true if successful, otherwise return false
bool load(struct list** lst, const char* filename); //read all integers from a text file filename and write list into *lst. Return true if successful, otherwise return false
bool serialize(struct list* lst, const char* filename); //write all elements into binary file. Return true if success or return false if not.
bool deserialize(struct list** lst, const char* filename); //read all integers from binary file and write them to *lst. Return true if success, else return false.

#endif