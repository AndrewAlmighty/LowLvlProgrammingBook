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
	//Get the header
	fread(&(read -> header), sizeof(uint8_t), 54, in);
	
	uint32_t offset;
	fseek(in, 10, SEEK_SET);
	fread(&offset, sizeof(uint32_t), 1, in);
	
	//set the file pointer to width and height fields in bmp header. The first one is width.
	fseek(in, 18, SEEK_SET);
	fread(&(read -> width), sizeof(uint32_t), 1, in);
	fread(&(read -> height), sizeof(uint32_t), 1, in);	
	
	//Copy the pixel table. We need to allocate memory, count the row_size and then read image.
	fseek(in, offset, SEEK_SET);
	read -> row_size = (4 - ((read -> width * 3 ) % 4)) + (read -> width) * sizeof(struct pixel);	//row size must be divisible by 4. If it's not, add number to make it divisible by 4.
	read -> data = malloc(read -> row_size * read -> height * 3);
	uint32_t i;
	for(i = 0; i <= read -> height; i++)
		fread((read -> data) + (read -> row_size * i) , sizeof(uint8_t), read -> row_size, in);
						
	return READ_OK;
}

enum write_status to_bmp(FILE* out, struct image const* img)
{
	//copy the header
	fwrite(&(img -> header), sizeof(uint8_t), 54, out);
	
	//set width and height
	fseek(out, 18, SEEK_SET);
	fwrite(&(img -> width), sizeof(uint32_t), 1, out);
	fwrite(&(img -> height), sizeof(uint32_t), 1, out);
	
	//copy the pixel table
	fseek(out, 54, SEEK_SET);
	uint32_t i;
	for(i = 0; i <= img -> height; i++)	
		fwrite(((img -> data) + (img -> row_size * i)), sizeof(uint8_t), img -> row_size, out);	

	return WRITE_OK;
}

struct image rotate(struct image const source)
{
	struct image new_img;
	
	//copy header and set new height and width value
	new_img.header[54] = source.header[54];
	new_img.width = source.height;		
	new_img.height = source.width;
	
	//rotate the image
	uint32_t i;
	for(i = 0; i < new_img.height; i++)
	{
			
	}
	
	return new_img;
}

struct image blurring(struct image const source)
{
	struct image new_img;
	
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
	free(img -> data);
}


