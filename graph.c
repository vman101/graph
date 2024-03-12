#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define WIDTH 800
#define HEIGHT 600

#define defer(value) do { result = (value); goto defer; } while (0)

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

inline void g_draw_pixel(u32 *pixels, u32 width, u32 height, u32 y, u32 x, u32 color);
void g_draw_rect(u32 *pixels, u32 width, u32 height, int x, int y, u32 w, u32 h, u32 color);
int g_save_to_ppm(u32 *pixels, u32 width, u32 height, char *filepath);
void g_fill(u32 *pixels, u32 width, u32 height, u32 color);

// Math
inline float m_sqrt(float num);
inline float m_inv_sqrt(float num);
inline float m_fabs(float num);
inline float m_pow(float num, int power);

int g_save_to_ppm(u32 *pixels, u32 width, u32 height, char *filepath)
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

void g_fill(u32 *pixels, u32 width, u32 height, u32 color)
{
	for (u32 i = 0; i < width * height; ++i)
		pixels[i] = color;
}

void g_draw_rect(u32 *pixels, u32 width, u32 height,
					 int x, int y, u32 w, u32 h, u32 color)
{
	for (u32 dy = 0; dy < h; ++dy)
	{
		int cy = y + (int) dy;
		if (cy >= 0 && cy < (int) height)
			for (u32 dx = 0; dx < w; ++dx)
			{
				int cx = x + (int) dx;
				if (cx >= 0 && cx < (int) width)
					pixels[cy * width + cx] = color;
			}
	}
}

void g_draw_line(u32 *pixels, u32 width, u32 height,
					 u32 x1, u32 y1, u32 x2, u32 y2,
					 u32 color)
{
	int dx = (int) x2 - (int) x1,
		dy = (int) y2 - (int) y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = (float) dx / steps;
    float yIncrement = (float) dy / steps;
    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++)
	{
        printf("(%d, %d)\n", (int) x, (int) y);
		g_draw_pixel(pixels, width, height, x, y, color);
        x += xIncrement;
        y += yIncrement;
    }
}

float m_pow(float num, int power)
{
	if (power < 0)
	{
		u32 count = -power;
		float res = num;
		for (u32 i = 0; i < count; ++i)
			res *= num;
		return (1 / res);
	}
	else if (power > 0)
	{
		float res = num;
		for (int i = 0; i < power; ++i)
			res *= num;
		return (res);
	}
	else if (power == 0)
		return (1);
	return (0);
}

float m_fabs(float num)
{
	if (num < 0)
		return (-num);
	return num;
}

float m_inv_sqrt(float num)
{
	float xhalf = 0.5f * num;
	int i = * (int *) &num;

	i = 0x5f3759df - (i >> 1);
	num = *(float *) &i;
	num = num * (1.5f - xhalf * num * num);
	return num;
}

float m_sqrt(float num)
{
	if (num > 0)
		return (m_inv_sqrt(num) * num);
	return (-1);
}

void g_draw_pixel(u32 *pixels, u32 width, u32 height, u32 x, u32 y, u32 color)
{
	if (y > 0 && y < height)
		if(x > 0 && x < width)
			pixels[y * width + x] = color;
}

int m_fact(int n)
{
	if (n = 0)
		return (1);
	return (n * m_fact(n - 1))
}

float m_sin(float n)
{
	float x;
	float fact = 9;

	while (fact)
	{

	}
}

int main()
{
	char *filepath = "img.ppm";
	u32 pixels[WIDTH * HEIGHT];
	g_fill(pixels, WIDTH, HEIGHT, 0xff202020);
	g_draw_line(pixels, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, 0x202020FF);
	g_save_to_ppm(pixels, WIDTH, HEIGHT, filepath);
	return (0);
}
