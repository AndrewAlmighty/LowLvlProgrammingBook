#ifndef _IMAGE_ROT_H_
#define _IMAGE_ROT_H_

#include <stdint.h>

struct pixel;

struct image
{
	uint32_t width, height, row_size;
	uint8_t header[54];
	struct pixel* data;
};

struct image rotate(struct image const source);
struct image deserialize(const char *name);
void serialize(const char *name, struct image const * img);

#endif