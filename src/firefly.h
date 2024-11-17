#pragma once

#include "firefly_bindings.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/// @brief Mark a "boot" callback function.
#define BOOT __attribute__((export_name("boot")))
/// @brief Mark an "update" callback function.
#define UPDATE __attribute__((export_name("update")))
/// @brief Mark a "render_line" callback function.
#define RENDER_LINE __attribute__((export_name("render_line")))

/// @brief Screen width.
#define WIDTH 240
/// @brief Screen height.
#define HEIGHT 160

// -- GRAPHICS -- //

/// @brief A point on the screen.
///
/// @details Typically, the upper-left corner of a bounding box of a shape.
struct Point
{
    int32_t x;
    int32_t y;
};
typedef struct Point Point;

/// @brief Size of a bounding box for a shape.
///
/// @details The width and height must be positive.
struct Size
{
    int32_t width;
    int32_t height;
};
typedef struct Size Size;

/// @brief An angle between two vectors.
///
/// @details Used by DrawArc and DrawSector.
/// Must be constructed using Radians or Degrees function.
struct Angle
{
    float a;
};
typedef struct Angle Angle;

/// @brief A pointer to a color in the color palette.
enum Color
{
    NONE = 0,
    BLACK = 1,
    PURPLE = 2,
    RED = 3,
    ORANGE = 4,
    YELLOW = 5,
    LIGHT_GREEN = 6,
    GREEN = 7,
    DARK_GREEN = 8,
    DARK_BLUE = 9,
    BLUE = 10,
    LIGHT_BLUE = 11,
    CYAN = 12,
    WHITE = 13,
    LIGHT_GRAY = 14,
    GRAY = 15,
    DARK_GRAY = 16,
};
typedef enum Color Color;

/// @brief Style of a shape.
struct Style
{
    Color fill_color;
    Color stroke_color;
    int32_t stroke_width;
};
typedef struct Style Style;

/// @brief The same as Style but without a fill color (only stroke color and width).
struct LineStyle
{
    Color color;
    int32_t width;
};
typedef struct LineStyle LineStyle;

/// @brief The RGB value of a color in the palette.
struct RGB
{
    int8_t r;
    int8_t g;
    int8_t b;
};
typedef struct RGB RGB;

void ClearScreen(Color c);
void SetColor(Color c, RGB v);
void DrawPoint(Point p, Color c);
void DrawLine(Point a, Point b, LineStyle s);
void DrawRect(Point p, Size b, Style s);
void DrawRoundedRect(Point p, Size b, Size c, Style s);
void DrawCircle(Point p, int32_t d, Style s);
void DrawEllipse(Point p, Size b, Style s);
void DrawTriangle(Point a, Point b, Point c, Style s);
void DrawArc(Point p, int32_t d, Angle start, Angle sweep, Style s);
void DrawSector(Point p, int32_t d, Angle start, Angle sweep, Style s);

// -- INPUT -- //

struct Pad
{
    int16_t x;
    int16_t y;
    bool touched;
};
typedef struct Pad Pad;

struct Buttons
{
    bool a;
    bool b;
    bool x;
    bool y;
    bool menu;
};
typedef struct Buttons Buttons;

struct Player
{
    uint8_t index;
};
typedef struct Player Player;

Pad ReadPad(Player player);
Buttons ReadButtons(Player player);

// -- FS -- //

int GetFileSize(char *path);
int LoadFile(char *path, char *buf);
