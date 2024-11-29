/// @file
/// @brief The function definitions for Firefly Zero C SDK.

#include "firefly.h"
#include "firefly_bindings.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/// @brief An angle in radians where τ(2π) is the full circle.
Angle radians(float a)
{
    struct Angle r = {a};
    return r;
};

/// @brief An angle in degrees where 360.0 is the full circle.
Angle degrees(float a)
{
    struct Angle r = {a * (float)3.14159265358979323846 / (float)180.0};
    return r;
};

/// @brief Time in the number of samples.
AudioTime samples(int32_t s)
{
    struct AudioTime t = {s};
    return t;
}

/// @brief Time in seconds.
AudioTime seconds(int32_t s)
{
    struct AudioTime t = {s * SAMPLE_RATE};
    return t;
}

/// @brief Time in miliseconds.
AudioTime miliseconds(int32_t s)
{
    struct AudioTime t = {s * SAMPLE_RATE / 1000};
    return t;
}

/// @brief Convert Pad to DPad.
DPad pad_to_dpad(Pad pad)
{
    DPad dpad = {
        .left = pad.x <= -100,
        .right = pad.x >= 100,
        .up = pad.y <= -100,
        .down = pad.y >= 100};
    return dpad;
}

// -- GRAPHICS -- //

/// @brief Fill the whole frame with the given color.
void clear_screen(Color c)
{
    _ffb_clear_screen(c);
}

/// @brief Set a color value in the palette.
void set_color(Color c, RGB v)
{
    _ffb_set_color(c, v.r, v.g, v.b);
}

/// @brief Set a single point (1 pixel is scaling is 1) on the frame.
void draw_point(Point p, Color c)
{
    _ffb_draw_point(p.x, p.y, c);
}

/// @brief Draw a straight line from point a to point b.
void draw_line(Point a, Point b, LineStyle s)
{
    _ffb_draw_line(a.x, a.y, b.x, b.y, s.color, s.width);
}

/// @brief Draw a rectangle filling the given bounding box.
void draw_rect(Point p, Size b, Style s)
{
    _ffb_draw_rect(p.x, p.y, b.width, b.height, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw a rectangle with rounded corners.
void draw_rounded_rect(Point p, Size b, Size c, Style s)
{
    _ffb_draw_rounded_rect(p.x, p.y, b.width, b.height, c.width, c.height, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw a circle with the given diameter.
void draw_circle(Point p, int32_t d, Style s)
{
    _ffb_draw_circle(p.x, p.y, d, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw an ellipse (oval).
void draw_ellipse(Point p, Size b, Style s)
{
    _ffb_draw_ellipse(p.x, p.y, b.width, b.height, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw a triangle.
void draw_triangle(Point a, Point b, Point c, Style s)
{
    _ffb_draw_triangle(a.x, a.y, b.x, b.y, c.x, c.y, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw an arc.
void draw_arc(Point p, int32_t d, Angle start, Angle sweep, Style s)
{
    _ffb_draw_arc(p.x, p.y, d, start.a, sweep.a, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw a sector.
void draw_sector(Point p, int32_t d, Angle start, Angle sweep, Style s)
{
    _ffb_draw_sector(p.x, p.y, d, start.a, sweep.a, s.fill_color, s.stroke_color, s.stroke_width);
}

/// @brief Draw an image.
void draw_image(Image i, Point p)
{
    _ffb_draw_image((int)i.head, i.size, p.x, p.y);
}

/// @brief Draw an image subregion.
void draw_sub_image(SubImage s, Point p)
{
    _ffb_draw_sub_image((int)s.image.head, s.image.size, p.x, p.y, s.point.x, s.point.y, s.size.width, s.size.height);
}

/// @brief Set the target image for all subsequent drawing operations.
void set_canvas(Canvas c)
{
    _ffb_set_canvas((int)c.head, c.size);
}

/// @brief Make all subsequent drawing operations target the screen instead of a canvas.
/// @details Cancels the effect of [set_canvas].
void unset_canvas()
{
    _ffb_unset_canvas();
}

// -- INPUT -- //

/// @brief Read touchpad state: if it's pressed and where.
Pad read_pad(Peer peer)
{
    int32_t raw = _ffb_read_pad(peer);
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
Buttons read_buttons(Peer peer)
{
    int32_t raw = _ffb_read_buttons(peer);
    Buttons buttons = {
        .s = (raw & 0b1) != 0,
        .e = (raw & 0b10) != 0,
        .w = (raw & 0b100) != 0,
        .n = (raw & 0b1000) != 0,
        .menu = (raw & 0b10000) != 0};
    return buttons;
}

// -- FS -- //

/// @brief Get size (in bytes) of the given file.
/// @details Useful for dynamically allocating Buffer
/// of the right size for [load_file].
size_t get_file_size(char *path)
{
    size_t pathLen = strlen(path);
    return _ffb_get_file_size((int)path, pathLen);
}

/// @brief Read file from the given path into the given buffer.
/// @details The resulting File uses the same memory as the given
/// Buffer but has its size adjusted to the file size.
File load_file(char *path, Buffer buf)
{
    size_t pathLen = strlen(path);
    int32_t size = _ffb_load_file((int)path, pathLen, (int)buf.head, buf.size);
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
void dump_file(char *path, File f)
{
    size_t pathLen = strlen(path);
    _ffb_dump_file((int)path, pathLen, (int)f.head, f.size);
}

/// @brief Delete a file created using dump_file().
/// @details Files in ROM cannot be deleted.
void remove_file(char *path)
{
    size_t pathLen = strlen(path);
    _ffb_remove_file((int)path, pathLen);
}

// -- NET -- //

/// @brief Get the Peer corresponding to the current device.
Peer get_me()
{
    return _ffb_get_me();
}

/// @brief Get a mapping of peers currently online.
Peers get_peers()
{
    Peers peers;
    peers.online = _ffb_get_peers();
    return peers;
}

/// @brief Check if the given Peer is online.
/// @details Accepts the bitmap of Peers returned by get_peers().
/// The Peer can be obtained by a for loop from 0 to 31.
bool is_online(Peers peers, Peer peer)
{
    return ((peers.online >> peer) & 1) != 0;
}

// -- MISC -- //

/// @brief Write a debug message.
void log_debug(char *msg)
{
    size_t msgLen = strlen(msg);
    _ffb_log_debug((int)msg, msgLen);
}

/// @brief Write an error message.
void log_error(char *msg)
{
    size_t msgLen = strlen(msg);
    _ffb_log_error((int)msg, msgLen);
}

/// @brief Set the random seed. Useful for testing.
void set_seed(uintptr_t seed)
{
    _ffb_set_seed(seed);
}

/// @brief Get a random integer.
uintptr_t get_random()
{
    return _ffb_get_random();
}

/// @brief Write device name into the given Buffer.
/// @details The buffer size must be at least 16 bytes.
Buffer get_name(Buffer buf)
{
    int32_t size = _ffb_get_name((int)buf.head, buf.size);
    File name = {
        .size = size,
        .head = buf.head};
    return name;
}

/// @brief Ask the runtime to restart the app after the current update iteration.
void restart()
{
    _ffb_restart();
}

/// @brief Ask the runtime to exit the app after the current update iteration.
void quit()
{
    _ffb_quit();
}

// -- STATS -- //

Progress add_progress(Peer p, Badge b, int16_t v)
{
    uint32_t r = _ffb_add_progress(p, b, v);
    Progress progress = {
        .done = r >> 16,
        .goal = r};
    return progress;
}

Progress get_progress(Peer p, Badge b)
{
    return add_progress(p, b, 0);
}

Score add_score(Peer p, Board b, Score v)
{
    return _ffb_add_score(p, b, v);
}

Score get_score(Peer p, Board b)
{
    return add_score(p, b, 0);
}

// -- AUDIO -- //

/// @brief Add sine AudioNode as a child node for the given node.
AudioNode add_sine(AudioNode parent, float freq, float phase)
{
    AudioNode node;
    node.id = _ffba_add_sine(parent.id, freq, phase);
    return node;
}

/// @brief Add square AudioNode as a child node for the given node.
AudioNode add_square(AudioNode parent, float freq, float phase)
{
    AudioNode node;
    node.id = _ffba_add_square(parent.id, freq, phase);
    return node;
}

/// @brief Add sawtooth AudioNode as a child node for the given node.
AudioNode add_sawtooth(AudioNode parent, float freq, float phase)
{
    AudioNode node;
    node.id = _ffba_add_sawtooth(parent.id, freq, phase);
    return node;
}

/// @brief Add triangle AudioNode as a child node for the given node.
AudioNode add_triangle(AudioNode parent, float freq, float phase)
{
    AudioNode node;
    node.id = _ffba_add_triangle(parent.id, freq, phase);
    return node;
}

/// @brief Add noise AudioNode as a child node for the given node.
AudioNode add_noise(AudioNode parent, int32_t seed)
{
    AudioNode node;
    node.id = _ffba_add_noise(parent.id, seed);
    return node;
}

/// @brief Add empty AudioNode as a child node for the given node.
AudioNode add_empty(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_empty(parent.id);
    return node;
}

/// @brief Add zero AudioNode as a child node for the given node.
AudioNode add_zero(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_zero(parent.id);
    return node;
}

/// @brief Add file AudioNode as a child node for the given node.
AudioNode add_file(AudioNode parent, char *path)
{
    size_t pathLen = strlen(path);
    AudioNode node;
    node.id = _ffba_add_file(parent.id, (int)path, pathLen);
    return node;
}

/// @brief Add mix AudioNode as a child node for the given node.
AudioNode add_mix(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_mix(parent.id);
    return node;
}

/// @brief Add allforone AudioNode as a child node for the given node.
AudioNode add_all_for_one(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_all_for_one(parent.id);
    return node;
}

/// @brief Add gain AudioNode as a child node for the given node.
AudioNode add_gain(AudioNode parent, float lvl)
{
    AudioNode node;
    node.id = _ffba_add_gain(parent.id, lvl);
    return node;
}

/// @brief Add loop AudioNode as a child node for the given node.
AudioNode add_loop(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_loop(parent.id);
    return node;
}

/// @brief Add concat AudioNode as a child node for the given node.
AudioNode add_concat(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_concat(parent.id);
    return node;
}

/// @brief Add pan AudioNode as a child node for the given node.
AudioNode add_pan(AudioNode parent, float lvl)
{
    AudioNode node;
    node.id = _ffba_add_pan(parent.id, lvl);
    return node;
}

/// @brief Add mute AudioNode as a child node for the given node.
AudioNode add_mute(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_mute(parent.id);
    return node;
}

/// @brief Add pause AudioNode as a child node for the given node.
AudioNode add_pause(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_pause(parent.id);
    return node;
}

/// @brief Add trackposition AudioNode as a child node for the given node.
AudioNode add_track_position(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_track_position(parent.id);
    return node;
}

/// @brief Add lowpass AudioNode as a child node for the given node.
AudioNode add_low_pass(AudioNode parent, float freq, float q)
{
    AudioNode node;
    node.id = _ffba_add_low_pass(parent.id, freq, q);
    return node;
}

/// @brief Add highpass AudioNode as a child node for the given node.
AudioNode add_high_pass(AudioNode parent, float freq, float q)
{
    AudioNode node;
    node.id = _ffba_add_high_pass(parent.id, freq, q);
    return node;
}

/// @brief Add takeleft AudioNode as a child node for the given node.
AudioNode add_take_left(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_take_left(parent.id);
    return node;
}

/// @brief Add takeright AudioNode as a child node for the given node.
AudioNode add_take_right(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_take_right(parent.id);
    return node;
}

/// @brief Add swap AudioNode as a child node for the given node.
AudioNode add_swap(AudioNode parent)
{
    AudioNode node;
    node.id = _ffba_add_swap(parent.id);
    return node;
}

/// @brief Add clip AudioNode as a child node for the given node.
AudioNode add_clip(AudioNode parent, float low, float high)
{
    AudioNode node;
    node.id = _ffba_add_clip(parent.id, low, high);
    return node;
}

/// @brief Reset the state of the given AudioNode.
void audio_reset(AudioNode node)
{
    _ffba_reset(node.id);
}

/// @brief Reset the state of the given AudioNode and all its child nodes.
void audio_reset_all(AudioNode node)
{
    _ffba_reset_all(node.id);
}

/// @brief Remove all child nodes from the given AudioNode.
void audio_clear(AudioNode node)
{
    _ffba_clear(node.id);
}

/// @brief Modulate an audio node's parameter using a LinearModulator.
void mod_linear(AudioNode node, ModParam param, LinearModulator mod)
{
    _ffba_mod_linear(node.id, param, mod.start, mod.end, mod.start_at.samples, mod.end_at.samples);
}

/// @brief Modulate an audio node's parameter using a HoldModulator.
void mod_hold(AudioNode node, ModParam param, HoldModulator mod)
{
    _ffba_mod_hold(node.id, param, mod.before, mod.after, mod.time.samples);
}

/// @brief Modulate an audio node's parameter using a SineModulator.
void mod_sine(AudioNode node, ModParam param, SineModulator mod)
{
    _ffba_mod_sine(node.id, param, mod.freq, mod.low, mod.high);
}
