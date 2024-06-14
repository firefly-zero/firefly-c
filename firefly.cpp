#include "firefly_bindings.h"
#include <stdint.h>

#define WASM_EXPORT(NAME) __attribute__((export_name(NAME)))
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

struct Angle
{
    float a;
};

Angle Radians(float a)
{
    return Angle{a};
};

Angle Degrees(float a)
{
    return Angle{a * (float)3.14159265358979323846 / (float)180.0};
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

void ClearScreen(Color c)
{
    clearScreen(c);
}

void SetColor(Color c, RGB v)
{
    setColor(c, v.r, v.g, v.b);
}

void DrawPoint(Point p, Color c)
{
    drawPoint(p.x, p.y, c);
}

void DrawLine(Point a, Point b, LineStyle s)
{
    drawLine(a.x, a.y, b.x, b.y, s.color, s.width);
}

void DrawRect(Point p, Size b, Style s)
{
    drawRect(p.x, p.y, b.width, b.height, s.fill_color, s.stroke_color, s.stroke_width);
}

void DrawRoundedRect(Point p, Size b, Size c, Style s)
{
    drawRoundedRect(p.x, p.y, b.width, b.height, c.width, c.height, s.fill_color, s.stroke_color, s.stroke_width);
}

void DrawCircle(Point p, int32_t d, Style s)
{
    drawCircle(p.x, p.y, d, s.fill_color, s.stroke_color, s.stroke_width);
}

void DrawEllipse(Point p, Size b, Style s)
{
    drawEllipse(p.x, p.y, b.width, b.height, s.fill_color, s.stroke_color, s.stroke_width);
}

void DrawTriangle(Point a, Point b, Point c, Style s)
{
    drawTriangle(a.x, a.y, b.x, b.y, c.x, c.y, s.fill_color, s.stroke_color, s.stroke_width);
}

void DrawArc(Point p, int32_t d, Angle start, Angle sweep, Style s)
{
    drawArc(p.x, p.y, d, start.a, sweep.a, s.fill_color, s.stroke_color, s.stroke_width);
}

void DrawSector(Point p, int32_t d, Angle start, Angle sweep, Style s)
{
    drawSector(p.x, p.y, d, start.a, sweep.a, s.fill_color, s.stroke_color, s.stroke_width);
}
