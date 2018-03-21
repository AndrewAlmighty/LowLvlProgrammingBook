#include "image_rot.h"
#include <stdio.h>

enum read_status
{
	READ_OK = 0,
	READ_INVALID_SIGNATURE,
	READ_INVALID_BITS,
	READ_INVALID_HEADER
};

enum write_status
{
	WRITE_OK = 0,
	WRITE_ERROR
};

static int from_bmp(const char *name)
{
	//This function reads a file. Returns code if operation is completed or not.
	FILE * file = fopen(name, "rb");
	
	fclose(file);
	return READ_OK;
}

static int to_bmp(const char *name)
{
	FILE *file;
	
	if(strcmp(name, ""))
		file = fopen("rotated_image.bmp", "wb");
	
	else
		file = fopen(name, "wb");
	
	fclose(file);
	return WRITE_OK;
}

void run(const char * src_name, const char *dst_name)
{
	//This function is responsible for all job we do on the image.
	from_bmp(src_name);
	to_bmp(dst_name);
}

