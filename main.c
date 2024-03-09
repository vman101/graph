#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define WIDTH 80
#define HEIGHT 80

#define defer(value) do { result = (value); goto defer; } while (0)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

int draw_pixels(u32 *pixels, u32 width, u32 height, char *filepath)
{
	int result = 0;
	FILE *fp = fopen(filepath, "wb");

	fprintf(fp, "P6\n# %s\n%u %u\n255\n", filepath, width, height);
	if(ferror(fp)) defer(errno);
	for (u32 i = 0; i < width*height; ++i)
	{
		u32 pixel = pixels[i];
		u8 bytes[3] = {
			(pixel>>(8*0))&0xFF,
			(pixel>>(8*1))&0xFF,
			(pixel>>(8*2))&0xFF,
		};
		fwrite(bytes, sizeof(bytes), 1, fp);
		if(ferror(fp)) defer(errno);
	}

defer:
	if (fp) fclose(fp);
	return (result);
}

int main()
{
	char *filepath = "img.ppm";
	u32 pixels[WIDTH*HEIGHT];
	for (int i = 0; i < HEIGHT*WIDTH; i++)
	{
			pixels[i] = 0xFF0FF000;
	}
	draw_pixels(pixels, WIDTH, HEIGHT, filepath);
	return (0);
}
