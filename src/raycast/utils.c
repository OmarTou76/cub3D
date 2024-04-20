#include "cub3D.h"

uint32_t	convert_rgba_to_argb(uint32_t rgba)
{
	uint8_t red = (rgba >> 24) & 0xFF;   // Extract red
	uint8_t green = (rgba >> 16) & 0xFF; // Extract green
	uint8_t blue = (rgba >> 8) & 0xFF;   // Extract blue
	uint8_t alpha = rgba & 0xFF;         // Extract alpha
	return ((alpha << 24) | (blue << 16) | (green << 8) | red);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}