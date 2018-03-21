#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "image_rot.h"

//This function prints info how to use this program. If *opt == 1 - asked for help. Else if *opt == 2, wrong parameters 
void print_help(const int opt)
{
	if(opt == 1)
		puts("Usage: imageRotator [OPTIONS]\nRotates BMP image of any resolution to 90 degrees clockwise\n\nArguments:\n-h, --help, shows help\n-s, source file name. Must be given!\n-d, name of new, rotated file");
	
	else if(opt == 2)
		puts("Invalid options!\nTry imageRotator -h or --help for more information");
}

//here we check user give the program a name of files.
bool check_name(int *i, const char* name)
{
	*i += 1;
	
	if(strcmp(name, "") == 0)
		return false;
	
	return true;
}

int main(int argc, char** argv)
{
	if(argc < 2)	
		print_help(2);
	
	else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
	{
	   	print_help(1);
		return 0;
	}
	
	else
	{		
		int i;				
		bool is_source = false;		
		char source_name[30], dest_name[30];		
		
		//Checking arguments ...
		for(i = 0; i < argc; i++)
		{
			if(strcmp(argv[i], "-s") == 0 && (i + 1 < argc))
			{				
				if(check_name(&i, argv[i + 1]) == 1)
				{
					is_source = true;
					strcpy(source_name, argv[i]);
				}
			}
			
			if(strcmp(argv[i], "-d") == 0 && (i + 1 < argc))
				if(check_name(&i, argv[i + 1]) == 1)
					strcpy(dest_name, argv[i]);
		}
		
		//if no source file is given we do nothing.
		if(is_source == false)
		{
			print_help(2);
			return 0;
		}
		
		//we start rotating the image
		run(source_name, dest_name);		
	}	   
	
	return 0;
}