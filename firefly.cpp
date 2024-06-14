#include "firefly_bindings.h"
#include <stdint.h>

#define WASM_EXPORT(NAME) __attribute__((export_name(NAME)))
#define WIDTH 240
#define HEIGHT 160

struct Point
{
    int32_t x;
    int32_t y;

    Point(int32_t x_, int32_t y_)
    {
        x = x_;
        y = y_;
    }
};

struct Size
{
    int32_t width;
    int32_t height;

    Size(int32_t width_, int32_t height_)
    {
        width = width_;
        height = height_;
    }
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

void DrawLine(Point a, Point b, LineStyle s)
{
    drawLine(a.x, a.y, b.x, b.y, s.color, s.width);
}
