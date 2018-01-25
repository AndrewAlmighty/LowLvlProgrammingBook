#include "linkedlist.h"
#include <string.h>

struct list* list_create(const int n)
{
	struct list* ptr = (struct list*) malloc (sizeof(struct list));
	ptr -> number = n;
	ptr -> next = NULL;
	return ptr;
}

void list_add_front(const int number, struct list** pptr)
{
	struct list *ptr = list_create(number);
	ptr -> next = *pptr;
	*pptr = ptr;	
}

void list_add_back(const int number, struct list** pptr)
{
	if(*pptr == NULL)
		*pptr = list_create(number);
	
	else
	{
		struct list *ptr = *pptr;
	
		while(ptr -> next != NULL)
			ptr = ptr -> next;
	
		ptr -> next = list_create(number);
	}
}

void list_free(struct list** list)
{
	void *ptr = NULL;
	
	while(*list)
	{
		ptr = (*list) -> next;
		free(*list);
		*list = ptr;
	}
	
	*list = NULL;
}

size_t list_length(struct list** list)
{
	size_t size = 0;
	struct list *ptr = *list;
	while(ptr)
	{
		size += 1;	
		ptr = ptr -> next;
	}
	
	return size;
}

struct list* list_node_at(struct list** list, const size_t index)
{
	struct list *ptr = *list;
	int i;
	for(i = 0; i < index; i++)
	{
		if(ptr -> next == NULL)
			return NULL;
		
		else
			ptr = ptr -> next;
	}
	
	return ptr;
}

int list_sum (struct list** list)
{
	struct list *ptr = *list;
	int sum = 0;
	while(ptr)
	{
		sum += ptr -> number;	
		ptr = ptr -> next;
	}	
	
	return sum;	
}

int list_get(struct list* ptr, const size_t index)
{
	int i;
	for(i = 0; i < index; i++)
	{
		if(ptr)
			ptr = ptr -> next;
		
		else
			return 0;
	}
	
	return ptr -> number;
}

void list_show(struct list* ptr)
{
	while(ptr != NULL)
	{
		printf("%d -", ptr -> number);
		ptr = ptr -> next;
	}
}

void foreach(struct list* lptr, void (*fptr)(int*))
{	
	while(lptr)
	{
		fptr( &(lptr -> number));	
		lptr = lptr -> next;
	}
}

struct list* map(struct list* lptr, void (*fptr)(int*))
{
	struct list* newList = NULL;
	
	while(lptr)
	{
		list_add_back(lptr -> number, &newList);
	 	lptr = lptr -> next;
	}
	
	foreach(newList, fptr);
	
	return newList;
}

void map_mut(struct list* lptr, void (*fptr)(int*))
{
	foreach(lptr, fptr);
}

int foldl(int b_ac, void(*fptr)(int*, int*), struct list* list)
{
	int ac = b_ac;
	
	while(list)
	{
		fptr(&(list -> number), &ac);
		list = list -> next;
	}
	
	return ac;
}

struct list* iterate(int num, int len, void (*fptr)(int*))
{
	struct list* newList = NULL;
	struct list* lptr = NULL;
	int i, j;
	
	for(i = 0; i < len; i++)
	{	
		list_add_back(num, &newList);
		lptr = list_node_at(&newList, i);
		
		for(j = 0; j < i; j++)
		{
			fptr( &(lptr -> number));	
		}
	}
	
	return newList;
}

bool save(struct list* lst, const char* filename)
{
	FILE *file = fopen(filename, "w");
	
	if(!file)
		return false;
	
	while(lst)		
	{
		fprintf(file, "%d", lst -> number);
		fputc(';', file);		
		lst = lst -> next;		
	}
	
	fclose(file);
	
	return true;
}

bool load(struct list** lst, const char* filename)
{
	FILE *file = fopen(filename, "r");
	
	if(!file)
		return false;
	
	int num;
	
	while(fscanf(file, "%d", &num) == 1)
	{
		fgetc(file);		
		list_add_back(num, &(*lst));
	}
	
	fclose(file);
	return true;
}

bool serialize(struct list* lst, const char* filename)
{
	FILE *file = fopen(filename, "wb");
	
	if(!file)
		return false;
	
	struct list *ptr = lst;
	
	while(ptr)
	{
		fwrite(&(ptr -> number), sizeof(int), 1, file);
		ptr = ptr -> next;
	}
	
	fclose(file);		
	return true;
}

bool deserialize(struct list** lst, const char* filename)
{
	FILE *file = fopen(filename, "rb");
	
	if(!file)
		return false;
	
	int num;
	
	while(fread(&num, sizeof(int), 1, file) != 0)
		list_add_back(num, &(*lst));
	
	fclose(file);
	return true;
}
