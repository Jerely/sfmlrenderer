#pragma once
#include "types.h"
#include <cmath>
#include "color.h"
#include <cstdio>
#include <SFML/Graphics.hpp>

extern const int WIDTH;
extern const int HEIGHT;

void displayBitmap(sf::RenderWindow& window, uint8_t* bitmap);

inline void setPixel(uint8_t* bitmap, uint32_t x, uint32_t y, Color color) {
	const uint32_t pixPos = x + y * WIDTH;
	if (pixPos < HEIGHT * WIDTH) {
		((uint32_t*)bitmap)[x+y*WIDTH] = color.toU32();
	}
}

void plotLineLow(int x0, int y0, int x1, int y1, uint8_t* bitmap);
void plotLineHigh(int x0, int y0, int x1, int y1, uint8_t* bitmap);
void plotLine(int x0, int y0, int x1, int y1, uint8_t* bitmap);

inline void plotLine(float fx0, float fy0, float fx1, float fy1, uint8_t* bitmap) {
    int x0 = (int) round((fx0+1.0f) * 0.5f * (WIDTH-1));
    int x1 = (int) round((fx1+1.0f) * 0.5f * (WIDTH-1));
    int y0 = (int) round((1.0f-(fy0+1.0f)*0.5f) * (HEIGHT-1));
    int y1 = (int) round((1.0f-(fy1+1.0f)*0.5f) * (HEIGHT-1));
    plotLine(x0, y0, x1, y1, bitmap);
    //printf("Float : p0(%.2f, %.2f), p1(%.2f, %.2f) ; Int : p0(%d, %d), p1(%d, %d)\n", fx0, fy0, fx1, fy1, x0, y0, x1, y1);
    //displayBitmap(*pWindow, bitmap);
}
