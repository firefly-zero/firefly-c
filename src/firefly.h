/// @file
/// @brief The type definitions and function declarations for Firefly Zero C SDK.

#pragma once

#include "firefly_bindings.h"
#include <stdbool.h>
#include <stdint.h>

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
    /// @brief The X coordinate, the number of pixels from the screen left.
    int32_t x;
    /// @brief The Y coordinate, the number of pixels from the screen top.
    int32_t y;
};
typedef struct Point Point;

/// @brief Size of a bounding box for a shape.
///
/// @details The width and height must be positive.
struct Size
{
    /// @brief The width of the bounding box, in pixels.
    int32_t width;
    /// @brief The height of the bounding box, in pixels.
    int32_t height;
};
typedef struct Size Size;

/// @brief An angle between two vectors.
///
/// @details Used by draw_arc and draw_sector.
/// Must be constructed using radians(x) or degrees(x) function.
struct Angle
{
    /// @private
    float a;
};
typedef struct Angle Angle;

/// @brief A pointer to a color in the color palette.
enum Color
{
    /// @brief No color (100% transparency).
    NONE = 0,
    /// @brief Black color: #1A1C2C.
    BLACK = 1,
    /// @brief Purple color: #5D275D.
    PURPLE = 2,
    /// @brief Red color: #B13E53.
    RED = 3,
    /// @brief Orange color: #EF7D57.
    ORANGE = 4,
    /// @brief Yellow color: #FFCD75.
    YELLOW = 5,
    /// @brief Light green color: #A7F070.
    LIGHT_GREEN = 6,
    /// @brief Green color: #38B764.
    GREEN = 7,
    /// @brief Dark green color: #257179.
    DARK_GREEN = 8,
    /// @brief Dark blue color: #29366F.
    DARK_BLUE = 9,
    /// @brief Blue color: #3B5DC9.
    BLUE = 10,
    /// @brief Light blue color: #41A6F6.
    LIGHT_BLUE = 11,
    /// @brief Cyan color: #73EFF7.
    CYAN = 12,
    /// @brief White color: #F4F4F4.
    WHITE = 13,
    /// @brief Light gray color: #94B0C2.
    LIGHT_GRAY = 14,
    /// @brief Gray color: #566C86.
    GRAY = 15,
    /// @brief Dark gray color: #333C57.
    DARK_GRAY = 16,
};
typedef enum Color Color;

/// @brief Style of a shape.
struct Style
{
    /// @brief The color to use to fill the shape.
    Color fill_color;
    /// @brief The color to use for the shape stroke.
    Color stroke_color;
    /// @brief The width of the shape stroke.
    /// @details If zero, a solid shape without a stroke will be drawn.
    int32_t stroke_width;
};
typedef struct Style Style;

/// @brief The same as Style but without a fill color (only stroke color and width).
struct LineStyle
{
    /// @brief The line color.
    Color color;
    /// @brief The line width, in pixels.
    int32_t width;
};
typedef struct LineStyle LineStyle;

/// @brief The RGB value of a color in the palette.
struct RGB
{
    /// @brief The red component.
    int8_t r;
    /// @brief The green component.
    int8_t g;
    /// @brief The blue component.
    int8_t b;
};
typedef struct RGB RGB;

// -- FS -- //

/// @brief A dynamically sized array.
/// @details Similar to vector in C++.
/// The size of the array pointed to by `head` must be at least `size` bytes long.
struct Buffer
{
    /// @brief The slice size, in bytes.
    size_t size;
    /// @brief The pointer to the first element of the underlying array.
    char *head;
};
typedef struct Buffer Buffer;
typedef struct Buffer File;
typedef struct Buffer Image;
typedef struct Buffer Canvas;

/// @brief A subregion of an Image.
struct SubImage
{
    /// @brief The original image.
    Image image;
    /// @brief The coordinates of the upper-left corner of the subregion.
    Point point;
    /// @brief The width and height of the subregion.
    Size size;
};
typedef struct SubImage SubImage;

// -- INPUT -- //

/// @brief Get if the touchpad is pressed, and if so, where.
struct Pad
{
    int16_t x;
    int16_t y;
    /// @brief If the touchpad is touched.
    bool touched;
};
typedef struct Pad Pad;

/// @brief Get which buttons are pressed.
/// @details The menu button is almost always handled by the runtime.
struct Buttons
{
    bool a;
    bool b;
    bool x;
    bool y;
    bool menu;
};
typedef struct Buttons Buttons;

// -- NET -- //

/// @brief The bitmap of peers currently online.
struct Peers
{
    /// @private
    uint32_t online;
};
typedef struct Peers Peers;

/// @brief An ID of a connected device in the multiplayer.
typedef int32_t Peer;

/// @brief A peer ID representing all peers at once.
#define COMBINED = 0xFF

// -- AUDIO -- //

/// @brief The sample rate of the audio engine.
#define SAMPLE_RATE 44100

/// @brief A node in the audio tree.
struct AudioNode
{
    /// @private
    uint32_t id;
};
typedef struct AudioNode AudioNode;

/// @brief A parameter of an audio node that can be modulated.
enum ModParam
{
    /// @brief Modulate oscillation frequency for a Sine wave node.
    Sine = 0,
    /// @brief Modulate oscillation frequency for a Square wave node.
    Square = 0,
    /// @brief Modulate oscillation frequency for a Sawtooth wave node.
    Sawtooth = 0,
    /// @brief Modulate oscillation frequency for a Triangle wave node.
    Triangle = 0,
    /// @brief Modulate the gain level for a Gain node.
    Gain = 0,
    /// @brief Modulate the pan value for a Pan node.
    /// @details The value is from 0. to 1.: 0. is only left, 1. is only right.
    Pan = 0,
    /// @brief Modulate the muted state for a Mute node.
    /// @details Below 0.5 is muted, above is unmuted.
    Mute = 0,
    /// @brief Modulate the paused state for a Pause node.
    /// @details Below 0.5 is paused, above is playing.
    Pause = 0,
    /// @brief Modulate the cut-off frequency of a LowPass node.
    LowPass = 0,
    /// @brief Modulate the cut-off frequency of a HighPass node.
    HighPass = 0,
    /// @brief Modulate the low cut amplitude of a Clip node and adjust the high amplitude to keep the gap.
    /// @details In other words, the difference between low and high cut points will stay the same.
    ClipBoth = 0,
    /// @brief Modulate the low cut amplitude of a Clip node.
    ClipLow = 1,
    /// @brief Modulate the high cut amplitude of a Clip node.
    ClipHigh = 2,
};
typedef enum ModParam ModParam;

/// @brief A time or duration used by audio modulators.
/// @details Must be constructed using samples(x), seconds(x), or miliseconds(x).
struct AudioTime
{
    uint32_t samples;
};
typedef struct AudioTime AudioTime;

/// @brief Linear (ramp up or down) envelope.
///
/// @details It looks like this: `⎽╱⎺` or `⎺╲⎽`.
///
/// The value before `start_at` is `start`, the value after `end_at` is `end`,
/// and the value between `start_at` and `end_at` changes linearly from `start` to `end`.
struct LinearModulator
{
    float start;
    float end;
    AudioTime start_at;
    AudioTime end_at;
};
typedef struct LinearModulator LinearModulator;

/// @brief Hold envelope.
///
/// @details It looks like this: `⎽│⎺` or `⎺│⎽`.
///
/// The value before `time` is `before` and the value after `time` is `after`.
/// Equivalent to LinearModulator with `start_at` being equal to `end_at`.
struct HoldModulator
{
    float before;
    float after;
    AudioTime time;
};
typedef struct HoldModulator HoldModulator;

/// @brief Sine wave low-frequency oscillator.
///
/// @details It looks like this: `∿`.
///
/// `low` is the lowest produced value, `high` is the highest.
struct SineModulator
{
    float freq;
    float low;
    float high;
};
typedef struct SineModulator SineModulator;

// -- FUNCTIONS -- //

Angle radians(float a);
Angle degrees(float a);
AudioTime samples(int32_t s);
AudioTime seconds(int32_t s);
AudioTime miliseconds(int32_t s);

void clear_screen(Color c);
void set_color(Color c, RGB v);
void draw_point(Point p, Color c);
void draw_line(Point a, Point b, LineStyle s);
void draw_rect(Point p, Size b, Style s);
void draw_rounded_rect(Point p, Size b, Size c, Style s);
void draw_circle(Point p, int32_t d, Style s);
void draw_ellipse(Point p, Size b, Style s);
void draw_triangle(Point a, Point b, Point c, Style s);
void draw_arc(Point p, int32_t d, Angle start, Angle sweep, Style s);
void draw_sector(Point p, int32_t d, Angle start, Angle sweep, Style s);
void draw_image(Image img, Point p);
void draw_sub_image(SubImage s, Point p);
void set_canvas(Canvas c);
void unset_canvas();

Pad read_pad(Peer peer);
Buttons read_buttons(Peer peer);

size_t get_file_size(char *path);
File load_file(char *path, Buffer buf);
void dump_file(char *path, File f);
void remove_file(char *path);

Peer get_me();
Peers get_peers();
bool is_online(Peers peers, Peer peer);

void log_debug(char *msg);
void log_error(char *msg);
void set_seed(uintptr_t seed);
uintptr_t get_random();
Buffer get_name(Buffer buf);
void restart();
void quit();

AudioNode add_sine(AudioNode parent, float freq, float phase);
AudioNode add_square(AudioNode parent, float freq, float phase);
AudioNode add_sawtooth(AudioNode parent, float freq, float phase);
AudioNode add_triangle(AudioNode parent, float freq, float phase);
AudioNode add_noise(AudioNode parent, int32_t seed);
AudioNode add_empty(AudioNode parent);
AudioNode add_zero(AudioNode parent);
AudioNode add_file(AudioNode parent, char *path);
AudioNode add_mix(AudioNode parent);
AudioNode add_all_for_one(AudioNode parent);
AudioNode add_gain(AudioNode parent, float lvl);
AudioNode add_loop(AudioNode parent);
AudioNode add_concat(AudioNode parent);
AudioNode add_pan(AudioNode parent, float lvl);
AudioNode add_mute(AudioNode parent);
AudioNode add_pause(AudioNode parent);
AudioNode add_track_position(AudioNode parent);
AudioNode add_low_pass(AudioNode parent, float freq, float q);
AudioNode add_high_pass(AudioNode parent, float freq, float q);
AudioNode add_take_left(AudioNode parent);
AudioNode add_take_right(AudioNode parent);
AudioNode add_swap(AudioNode parent);
AudioNode add_clip(AudioNode parent, float low, float high);

void mod_linear(AudioNode node, ModParam param, LinearModulator mod);
void mod_hold(AudioNode node, ModParam param, HoldModulator mod);
void mod_sine(AudioNode node, ModParam param, SineModulator mod);

void audio_reset(AudioNode node);
void audio_reset_all(AudioNode node);
void audio_clear(AudioNode node);
