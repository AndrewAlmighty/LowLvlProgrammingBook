#include "image_rot.h"

#include <stdio.h>
#include <malloc.h>

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

struct pixel
{
	uint8_t b,r,g;
};

enum read_status from_bmp(FILE *in, struct image* const read)
{
	uint32_t offset;
	fread(&(read -> header), sizeof(uint8_t), 54, in);
	
	fseek(in, 10, SEEK_SET);
	fread(&offset, sizeof(uint32_t), 1, in);
	
	//set the file pointer to width and height fields in bmp header. The first one is width.
	fseek(in, 18, SEEK_SET);
	fread(&(read -> width), sizeof(uint32_t), 1, in);
	fread(&(read -> height), sizeof(uint32_t), 1, in);	
	
	size_t readed = 0;
	read -> row_size = (4 - ((read -> width * 3 ) % 4)) + (read -> width) * sizeof(struct pixel);
	
	//Copy the pixel table	
	fseek(in, offset, SEEK_SET);
	read -> data = malloc(sizeof(struct pixel) * ((read -> width) * (read -> height) * 3));
	uint32_t i;
	for(i = 0; i <= read -> height; i++)
		readed += fread((read -> data) + (read -> row_size * i) , sizeof(struct pixel), read -> row_size, in);
						
	return READ_OK;
}

enum write_status to_bmp(FILE* out, struct image const* img)
{
	fwrite(&(img -> header), sizeof(uint8_t), 54, out);
	uint32_t i;
	for(i = 0; i <= img -> height; i++)	
		fwrite(((img -> data) + (img -> row_size * i)), sizeof(struct pixel), img -> row_size, out);	

	return WRITE_OK;
}

struct image rotate(struct image const source)
{
	struct image new_img;
	new_img.width = source.height;		
	new_img.height = source.width;
	
	return new_img;
}

struct image deserialize(const char *name)
{
	struct image img;
	FILE *file = fopen(name, "rb");
	if(file == NULL)
	{
		puts("ZLY PLIK");
		return img;
	}
	
	from_bmp(file, &img);	
	fclose(file);	
	return img;
}

void serialize(const char *name, struct image const * img)
{
	FILE* file;
	
	if(*name == '\0')
		file = fopen("rotated_image.bmp", "wb");
	
	else
		file = fopen(name, "wb");
	
	to_bmp(file, img);
	fclose(file);
}


