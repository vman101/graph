#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ENABLE_GRAPHICS
#include "graph"
#include "math"

#define WIDTH	800
#define HEIGHT	600

u32 pixels[WIDTH * HEIGHT];

void test_draw_lines(u32 *pixels, u32 width, u32 height);
void test_fill_rect(u32 *pixels, u32 width, u32 height);
void test_fill(u32 *pixels, u32 width, u32 height);

void test_draw_lines(u32 *pixels, u32 width, u32 height)
{
	g_fill(pixels, width, height, BKG_COLOR);
	g_draw_line(pixels, width, height, (float) width * 0.5f, (float) height * 0.25f, (float) width * 0.25f, (float) height * 0.75f, 0x2020FF20);
	g_draw_line(pixels, width, height, (float) width * 0.25f, (float) height * 0.75f, (float) width * 0.75f, (float) height * 0.75f, 0x2020FF20);
	g_draw_line(pixels, width, height, (float) width * 0.75f, (float) height * 0.75f, (float) width * 0.5f, (float) height * 0.25f, 0x2020FF20);
}

int main()
{
	char *filepath = "img.ppm";
	g_fill(pixels, WIDTH, HEIGHT, 0xff202020);
	g_fill_triangle(pixels, WIDTH, HEIGHT, 500, 90, 300, 15, 70, 430, 0xFF2020FF);
	g_save_to_ppm(pixels, WIDTH, HEIGHT, filepath);
	printf("File saved!\n");
	return (0);
}
