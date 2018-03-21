#include <stdio.h>
#include <string.h>

//This function prints info how to use this program. If *opt == 1 - asked for help. Else if *opt == 2, wrong parameters 
void print_help(const int opt)
{
	if(opt == 1)
		puts("Usage: imageRotator [OPTIONS]\nRotates BMP image of any resolution to 90 degrees clockwise\n-h, --help, shows help\n-s, source file name\n-n, name of new, rotated file\n");
	
	else if(opt == 2)
		puts("Invalid options!\nTry imageRotator -h or --help for more information");
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
		print_help(2);
		return 0;
	}
	   
	  
	return 0;
}