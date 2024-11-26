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

// -- FS -- //

/// @brief A dynamically sized array.
/// @details SImilar to vector in C++.
/// The size of the array pointed to by `head` must be at least `size` bytes long.
struct Buffer
{
    size_t size;
    char *head;
};
typedef struct Buffer Buffer;
typedef struct Buffer File;
typedef struct Buffer Image;
typedef struct Buffer Canvas;

/// @brief A subregion of an [Image].
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
    uint32_t online;
};
typedef struct Peers Peers;

/// @brief An ID of a connected device in the multiplayer.
typedef int32_t Peer;

/// @brief A peer ID representing all peers at once.
const Peer COMBINED = 0xFF;

// -- AUDIO -- //

const int32_t SAMPLE_RATE = 44100;

/// @brief A node in the audio tree.
struct AudioNode
{
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
    AudioTime startAt;
    AudioTime endAt;
};
typedef struct LinearModulator LinearModulator;

/// @brief Hold envelope.
///
/// @details It looks like this: `⎽│⎺` or `⎺│⎽`.
///
/// The value before `time` is `before` and the value after `time` is `after`.
/// Equivalent to [LinearModulator] with `startAt` being equal to `endAt`.
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

Angle Radians(float a);
Angle Degrees(float a);

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
void DrawImage(Image img, Point p);
void DrawSubImage(SubImage s, Point p);
void SetCanvas(Canvas c);
void UnsetCanvas();

Pad ReadPad(Peer peer);
Buttons ReadButtons(Peer peer);

size_t GetFileSize(char *path);
File LoadFile(char *path, Buffer buf);
void DumpFile(char *path, File f);
void RemoveFile(char *path);

Peer GetMe();
Peers GetPeers();
bool IsOnline(Peers peers, Peer peer);

void LogDebug(char *msg);
void LogError(char *msg);
void SetSeed(uintptr_t seed);
uintptr_t GetRandom();
Buffer GetName(Buffer buf);
void Restart();
void Quit();

AudioNode AddSine(AudioNode parent, double freq, double phase);
AudioNode AddSquare(AudioNode parent, double freq, double phase);
AudioNode AddSawtooth(AudioNode parent, double freq, double phase);
AudioNode AddTriangle(AudioNode parent, double freq, double phase);
AudioNode AddNoise(AudioNode parent, int32_t seed);
AudioNode AddEmpty(AudioNode parent);
AudioNode AddZero(AudioNode parent);
AudioNode AddFile(AudioNode parent, char *path);
AudioNode AddMix(AudioNode parent);
AudioNode AddAllForOne(AudioNode parent);
AudioNode AddGain(AudioNode parent, double lvl);
AudioNode AddLoop(AudioNode parent);
AudioNode AddConcat(AudioNode parent);
AudioNode AddPan(AudioNode parent, double lvl);
AudioNode AddMute(AudioNode parent);
AudioNode AddPause(AudioNode parent);
AudioNode AddTrackPosition(AudioNode parent);
AudioNode AddLowPass(AudioNode parent, double freq, double q);
AudioNode AddHighPass(AudioNode parent, double freq, double q);
AudioNode AddTakeLeft(AudioNode parent);
AudioNode AddTakeRight(AudioNode parent);
AudioNode AddSwap(AudioNode parent);
AudioNode AddClip(AudioNode parent, double low, double high);

void AudioReset(AudioNode node);
void AudioResetAll(AudioNode node);
void AudioClear(AudioNode node);
