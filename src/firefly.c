#include "firefly_bindings.h"
#include <stdint.h>
#include <stdbool.h>

// -- CALLBACKS -- //

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

/// @brief An angle in radians where τ (2π) is the full circle.
Angle Radians(float a)
{
    struct Angle r = {a};
    return r;
};

/// @brief An angle in degrees where 360.0 is the full circle.
Angle Degrees(float a)
{
    struct Angle r = {a * (float)3.14159265358979323846 / (float)180.0};
    return r;
};

/// @brief A pointer to a color in the color palette.
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
typedef Color Color;

/// @brief Style of a shape.
struct Style
{
    Color fill_color;
    Color stroke_color;
    int32_t stroke_width;
};
typedef Style Style;

/// @brief The same as Style but without a fill color (only stroke color and width).
struct LineStyle
{
    Color color;
    int32_t width;
};
typedef LineStyle LineStyle;

/// @brief The RGB value of a color in the palette.
struct RGB
{
    int8_t r;
    int8_t g;
    int8_t b;
};
typedef RGB RGB;

/// @brief Fill the whole frame with the given color.
void ClearScreen(Color c)
{
    ffb_clearScreen(c);
}

/// @brief Set a color value in the palette.
void SetColor(Color c, RGB v)
{
    ffb_setColor(c, v.r, v.g, v.b);
}

/// @brief Set a single point (1 pixel is scaling is 1) on the frame.
void DrawPoint(Point p, Color c)
{
    ffb_drawPoint(p.x, p.y, c);
}

/// @brief Draw a straight line from point a to point b.
void DrawLine(Point a, Point b, LineStyle s)
{
    ffb_drawLine(a.x, a.y, b.x, b.y, s.color, s.width);
}

/// @brief Draw a rectangle filling the given bounding box.
void DrawRect(Point p, Size b, Style s)
{
    ffb_drawRect(p.x, p.y, b.width, b.height, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw a rectangle with rounded corners.
void DrawRoundedRect(Point p, Size b, Size c, Style s)
{
    ffb_drawRoundedRect(p.x, p.y, b.width, b.height, c.width, c.height, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw a circle with the given diameter.
void DrawCircle(Point p, int32_t d, Style s)
{
    ffb_drawCircle(p.x, p.y, d, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw an ellipse (oval).
void DrawEllipse(Point p, Size b, Style s)
{
    ffb_drawEllipse(p.x, p.y, b.width, b.height, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw a triangle.
void DrawTriangle(Point a, Point b, Point c, Style s)
{
    ffb_drawTriangle(a.x, a.y, b.x, b.y, c.x, c.y, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw an arc.
void DrawArc(Point p, int32_t d, Angle start, Angle sweep, Style s)
{
    ffb_drawArc(p.x, p.y, d, start.a, sweep.a, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw a sector.
void DrawSector(Point p, int32_t d, Angle start, Angle sweep, Style s)
{
    ffb_drawSector(p.x, p.y, d, start.a, sweep.a, s.fill_color, s.stroke_color, s.stroke_width);
}

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

Pad ReadPad(Player player)
{
    int32_t raw = ffb_readPad(player.index);
    Pad pad;
    if (raw == 0xffff)
    {
        pad.x = 0;
        pad.y = 0;
        pad.touched = false;
    }
    else
    {
        pad.x = raw >> 16;
        pad.y = raw;
        pad.touched = true;
    }
    return pad;
}

Buttons ReadButtons(Player player)
{
    int32_t raw = ffb_readButtons(player.index);
    Buttons buttons;
    buttons.a = (raw & 0b1) != 0;
    buttons.b = (raw & 0b10) != 0;
    buttons.x = (raw & 0b100) != 0;
    buttons.y = (raw & 0b1000) != 0;
    buttons.menu = (raw & 0b10000) != 0;
    return buttons;
}
