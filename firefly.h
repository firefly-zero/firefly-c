#pragma once

#include <stdint.h>

#define WASM_EXPORT(name) __attribute__((export_name(name)))
#define WASM_IMPORT(name) __attribute__((import_name(name)))

#define WIDTH 240
#define HEIGHT 160

struct Point
{
    int32_t x;
    int32_t y;
};

struct Size
{
    int32_t width;
    int32_t height;
};

enum Color
{
    NONE,
    BLACK,
    PURPLE,
    RED,
    ORANGE,
    YELLOW,
    LIGHT_GREEN,
    GREEN,
    DARK_GREEN,
    DARK_BLUE,
    BLUE,
    LIGHT_BLUE,
    CYAN,
    WHITE,
    LIGHT_GRAY,
    GRAY,
    DARK_GRAY,
};

struct Style
{
    Color fill_color;
    Color stroke_color;
    int32_t stroke_width;
};

struct LineStyle
{
    Color color;
    int32_t width;
};

struct RGB
{
    int8_t r;
    int8_t g;
    int8_t b;
};

WASM_IMPORT("line")
void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color, int32_t stroke_width);
