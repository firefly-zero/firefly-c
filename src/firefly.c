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

AudioTime Samples(int32_t s)
{
    struct AudioTime t = {s};
    return t;
}

AudioTime Seconds(int32_t s)
{
    struct AudioTime t = {s * SAMPLE_RATE};
    return t;
}

AudioTime Miliseconds(int32_t s)
{
    struct AudioTime t = {s * SAMPLE_RATE / 1000};
    return t;
}

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

/// @brief Draw an image.
void DrawImage(Image i, Point p)
{
    ffb_drawImage((int)i.head, i.size, p.x, p.y);
}

/// @brief Draw an image subregion.
void DrawSubImage(SubImage s, Point p)
{
    ffb_drawSubImage((int)s.image.head, s.image.size, p.x, p.y, s.point.x, s.point.y, s.size.width, s.size.height);
}

/// @brief Set the target image for all subsequent drawing operations.
void SetCanvas(Canvas c)
{
    ffb_setCanvas((int)c.head, c.size);
}

/// @brief Make all subsequent drawing operations target the screen instead of a canvas.
/// @details Cancels the effect of [SetCanvas].
void UnsetCanvas()
{
    ffb_unsetCanvas();
}

// -- INPUT -- //

/// @brief Read touchpad state: if it's pressed and where.
Pad ReadPad(Peer peer)
{
    int32_t raw = ffb_readPad(peer);
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

/// @brief Get pressed buttons.
Buttons ReadButtons(Peer peer)
{
    int32_t raw = ffb_readButtons(peer);
    Buttons buttons;
    buttons.a = (raw & 0b1) != 0;
    buttons.b = (raw & 0b10) != 0;
    buttons.x = (raw & 0b100) != 0;
    buttons.y = (raw & 0b1000) != 0;
    buttons.menu = (raw & 0b10000) != 0;
    return buttons;
}

// -- FS -- //

/// @brief Get size (in bytes) of the given file.
/// @details Useful for dynamically allocating [Buffer]
/// of the right size for [LoadFile].
size_t GetFileSize(char *path)
{
    size_t pathLen = strlen(path);
    return ffb_getFileSize((int)path, pathLen);
}

/// @brief Read file from the given path into the given buffer.
/// @details The resulting [File] uses the same memory as the given
/// [Buffer] but has its size adjusted to the file size.
File LoadFile(char *path, Buffer buf)
{
    size_t pathLen = strlen(path);
    int32_t size = ffb_loadFile((int)path, pathLen, (int)buf.head, buf.size);
    File file;
    if (buf.size < size)
    {
        size = buf.size;
    }
    file.size = size;
    file.head = buf.head;
    return file;
}

/// @brief Write the given content into the given path.
/// @details The created file can be loaded using [LoadFile]
/// but only in a singleplayer game.
void DumpFile(char *path, File f)
{
    size_t pathLen = strlen(path);
    ffb_dumpFile((int)path, pathLen, (int)f.head, f.size);
}

/// @brief Delete a file created using [DumpFile].
/// @details Files in ROM cannot be deleted.
void RemoveFile(char *path)
{
    size_t pathLen = strlen(path);
    ffb_removeFile((int)path, pathLen);
}

// -- NET -- //

/// @brief Get the [Peer] corresponding to the current device.
Peer GetMe()
{
    return ffb_getMe();
}

/// @brief Get a mapping of peers currently online.
Peers GetPeers()
{
    Peers peers;
    peers.online = ffb_getPeers();
    return peers;
}

/// @brief Check if the given [Peer] is online.
/// @details Accepts the bitmap of [Peers] returned by [GetPeers].
/// The [Peer] can be obtained by a for loop from 0 to 31.
bool IsOnline(Peers peers, Peer peer)
{
    return ((peers.online >> peer) & 1) != 0;
}

// -- MISC -- //

/// @brief Write a debug message.
void LogDebug(char *msg)
{
    size_t msgLen = strlen(msg);
    ffb_logDebug((int)msg, msgLen);
}

/// @brief Write an error message.
void LogError(char *msg)
{
    size_t msgLen = strlen(msg);
    ffb_logError((int)msg, msgLen);
}

/// @brief Set the random seed. Useful for testing.
void SetSeed(uintptr_t seed)
{
    ffb_setSeed(seed);
}

/// @brief Get a random integer.
uintptr_t GetRandom()
{
    return ffb_getRandom();
}

/// @brief Write device name into the given [Buffer].
/// @details The buffer size must be at least 16 bytes.
Buffer GetName(Buffer buf)
{
    int32_t size = ffb_getName((int)buf.head, buf.size);
    File name;
    name.size = size;
    name.head = buf.head;
    return name;
}

/// @brief Ask the runtime to restart the app after the current update iteration.
void Restart()
{
    ffb_restart();
}

/// @brief Ask the runtime to exit the app after the current update iteration.
void Quit()
{
    ffb_quit();
}

// -- AUDIO -- //

/// @brief Add sine [AudioNode] as a child node for the given node.
AudioNode AddSine(AudioNode parent, float freq, float phase)
{
    AudioNode node;
    node.id = ffba_addSine(parent.id, freq, phase);
    return node;
}

/// @brief Add square [AudioNode] as a child node for the given node.
AudioNode AddSquare(AudioNode parent, float freq, float phase)
{
    AudioNode node;
    node.id = ffba_addSquare(parent.id, freq, phase);
    return node;
}

/// @brief Add sawtooth [AudioNode] as a child node for the given node.
AudioNode AddSawtooth(AudioNode parent, float freq, float phase)
{
    AudioNode node;
    node.id = ffba_addSawtooth(parent.id, freq, phase);
    return node;
}

/// @brief Add triangle [AudioNode] as a child node for the given node.
AudioNode AddTriangle(AudioNode parent, float freq, float phase)
{
    AudioNode node;
    node.id = ffba_addTriangle(parent.id, freq, phase);
    return node;
}

/// @brief Add noise [AudioNode] as a child node for the given node.
AudioNode AddNoise(AudioNode parent, int32_t seed)
{
    AudioNode node;
    node.id = ffba_addNoise(parent.id, seed);
    return node;
}

/// @brief Add empty [AudioNode] as a child node for the given node.
AudioNode AddEmpty(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addEmpty(parent.id);
    return node;
}

/// @brief Add zero [AudioNode] as a child node for the given node.
AudioNode AddZero(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addZero(parent.id);
    return node;
}

/// @brief Add file [AudioNode] as a child node for the given node.
AudioNode AddFile(AudioNode parent, char *path)
{
    size_t pathLen = strlen(path);
    AudioNode node;
    node.id = ffba_addFile(parent.id, (int)path, pathLen);
    return node;
}

/// @brief Add mix [AudioNode] as a child node for the given node.
AudioNode AddMix(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addMix(parent.id);
    return node;
}

/// @brief Add allforone [AudioNode] as a child node for the given node.
AudioNode AddAllForOne(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addAllForOne(parent.id);
    return node;
}

/// @brief Add gain [AudioNode] as a child node for the given node.
AudioNode AddGain(AudioNode parent, float lvl)
{
    AudioNode node;
    node.id = ffba_addGain(parent.id, lvl);
    return node;
}

/// @brief Add loop [AudioNode] as a child node for the given node.
AudioNode AddLoop(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addLoop(parent.id);
    return node;
}

/// @brief Add concat [AudioNode] as a child node for the given node.
AudioNode AddConcat(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addConcat(parent.id);
    return node;
}

/// @brief Add pan [AudioNode] as a child node for the given node.
AudioNode AddPan(AudioNode parent, float lvl)
{
    AudioNode node;
    node.id = ffba_addPan(parent.id, lvl);
    return node;
}

/// @brief Add mute [AudioNode] as a child node for the given node.
AudioNode AddMute(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addMute(parent.id);
    return node;
}

/// @brief Add pause [AudioNode] as a child node for the given node.
AudioNode AddPause(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addPause(parent.id);
    return node;
}

/// @brief Add trackposition [AudioNode] as a child node for the given node.
AudioNode AddTrackPosition(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addTrackPosition(parent.id);
    return node;
}

/// @brief Add lowpass [AudioNode] as a child node for the given node.
AudioNode AddLowPass(AudioNode parent, float freq, float q)
{
    AudioNode node;
    node.id = ffba_addLowPass(parent.id, freq, q);
    return node;
}

/// @brief Add highpass [AudioNode] as a child node for the given node.
AudioNode AddHighPass(AudioNode parent, float freq, float q)
{
    AudioNode node;
    node.id = ffba_addHighPass(parent.id, freq, q);
    return node;
}

/// @brief Add takeleft [AudioNode] as a child node for the given node.
AudioNode AddTakeLeft(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addTakeLeft(parent.id);
    return node;
}

/// @brief Add takeright [AudioNode] as a child node for the given node.
AudioNode AddTakeRight(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addTakeRight(parent.id);
    return node;
}

/// @brief Add swap [AudioNode] as a child node for the given node.
AudioNode AddSwap(AudioNode parent)
{
    AudioNode node;
    node.id = ffba_addSwap(parent.id);
    return node;
}

/// @brief Add clip [AudioNode] as a child node for the given node.
AudioNode AddClip(AudioNode parent, float low, float high)
{
    AudioNode node;
    node.id = ffba_addClip(parent.id, low, high);
    return node;
}

/// @brief Reset the state of the given [AudioNode].
void AudioReset(AudioNode node)
{
    ffba_reset(node.id);
}

/// @brief Reset the state of the given [AudioNode] and all its child nodes.
void AudioResetAll(AudioNode node)
{
    ffba_resetAll(node.id);
}

/// @brief Remove all child nodes from the given [AudioNode].
void AudioClear(AudioNode node)
{
    ffba_clear(node.id);
}
