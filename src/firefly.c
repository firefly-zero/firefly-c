#include "firefly.h"
#include "firefly_bindings.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/// @brief An angle in radians where τ(2π) is the full circle.
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

// -- GRAPHICS -- //

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

void DrawImage(Image i, Point p)
{
    ffb_drawImage((int)i.head, i.size, p.x, p.y);
}

void DrawSubImage(SubImage s, Point p)
{
    ffb_drawSubImage((int)s.image.head, s.image.size, p.x, p.y, s.point.x, s.point.y, s.size.width, s.size.height);
}

// -- INPUT -- //

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

// -- FS -- //

size_t GetFileSize(char *path)
{
    size_t pathLen = strlen(path);
    return ffb_getFileSize((int)path, pathLen);
}

File LoadFile(char *path, Buffer buf)
{
    size_t pathLen = strlen(path);
    int32_t size = ffb_loadFile((int)path, pathLen, (int)buf.head, buf.size);
    File file;
    file.size = size;
    file.head = buf.head;
    return file;
}

void DumpFile(char *path, File f)
{
    size_t pathLen = strlen(path);
    ffb_dumpFile((int)path, pathLen, (int)f.head, f.size);
}

void RemoveFile(char *path)
{
    size_t pathLen = strlen(path);
    ffb_removeFile((int)path, pathLen);
}

// -- NET -- //

Peer GetMe()
{
    return ffb_getMe();
}

Peers GetPeers()
{
    Peers peers;
    peers.online = ffb_getPeers();
    return peers;
}

bool IsOnline(Peers peers, Peer peer)
{
    return ((peers.online >> peer) & 1) != 0;
}

// -- MISC -- //

void LogDebug(char *msg)
{
    size_t msgLen = strlen(msg);
    ffb_logDebug((int)msg, msgLen);
}

void LogError(char *msg)
{
    size_t msgLen = strlen(msg);
    ffb_logError((int)msg, msgLen);
}

void SetSeed(uintptr_t seed)
{
    ffb_setSeed(seed);
}

uintptr_t GetRandom()
{
    return ffb_getRandom();
}

Buffer GetName(Buffer buf)
{
    int32_t size = ffb_getName((int)buf.head, buf.size);
    File name;
    name.size = size;
    name.head = buf.head;
    return name;
}

void Restart()
{
    ffb_restart();
}

void Quit()
{
    ffb_quit();
}

// -- AUDIO -- //

AudioNode AddSine(AudioNode parent, double freq, double phase)
{
    AudioNode node;
    node.id = ffba_addSine(parent.id, freq, phase);
    return node;
}

AudioNode AddSquare(AudioNode parent, double freq, double phase)
{
    AudioNode node;
    node.id = ffba_addSquare(parent.id, freq, phase);
    return node;
}

AudioNode AddSawtooth(AudioNode parent, double freq, double phase)
{
    AudioNode node;
    node.id = ffba_addSawtooth(parent.id, freq, phase);
    return node;
}

AudioNode AddTriangle(AudioNode parent, double freq, double phase)
{
    AudioNode node;
    node.id = ffba_addTriangle(parent.id, freq, phase);
    return node;
}

AudioNode AddNoise(AudioNode parent, int32_t seed)
{
    AudioNode node;
    node.id = ffba_addNoise(parent.id, seed);
    return node;
}

AudioNode AddEmpty(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addEmpty(parent.id);
    return node;
}

AudioNode AddZero(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addZero(parent.id);
    return node;
}

AudioNode AddFile(AudioNode parent, char *path)
{
    size_t pathLen = strlen(path);
    AudioNode node;
    node.id = ffba_addFile(parent.id, (int)path, pathLen);
    return node;
}

AudioNode AddMix(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addMix(parent.id);
    return node;
}

AudioNode AddAllForOne(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addAllForOne(parent.id);
    return node;
}

AudioNode AddGain(AudioNode parent, double lvl)
{
    AudioNode node;
    node.id = ffba_addGain(parent.id, lvl);
    return node;
}

AudioNode AddLoop(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addLoop(parent.id);
    return node;
}

AudioNode AddConcat(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addConcat(parent.id);
    return node;
}

AudioNode AddPan(AudioNode parent, double lvl)
{
    AudioNode node;
    node.id = ffba_addPan(parent.id, lvl);
    return node;
}

AudioNode AddMute(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addMute(parent.id);
    return node;
}

AudioNode AddPause(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addPause(parent.id);
    return node;
}

AudioNode AddTrackPosition(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addTrackPosition(parent.id);
    return node;
}

AudioNode AddLowPass(AudioNode parent, double freq, double q)
{
    AudioNode node;
    node.id = ffba_addLowPass(parent.id, freq, q);
    return node;
}

AudioNode AddHighPass(AudioNode parent, double freq, double q)
{
    AudioNode node;
    node.id = ffba_addHighPass(parent.id, freq, q);
    return node;
}

AudioNode AddTakeLeft(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addTakeLeft(parent.id);
    return node;
}

AudioNode AddTakeRight(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addTakeRight(parent.id);
    return node;
}

AudioNode AddSwap(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addSwap(parent.id);
    return node;
}

AudioNode AddClip(AudioNode parent, double low, double high)
{
    AudioNode node;
    node.id = ffba_addClip(parent.id, low, high);
    return node;
}

void AudioReset(AudioNode node)
{
    ffba_reset(node.id);
}

void AudioResetAll(AudioNode node)
{
    ffba_resetAll(node.id);
}

void AudioClear(AudioNode node)
{
    ffba_clear(node.id);
}
