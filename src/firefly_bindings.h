// A private header with runtime bindings for Firefly Zero.
// Don't use it directly. Everything defined here has a friendly wrapper.

#pragma once

#include <stdint.h>

#define WASM_IMPORT(MOD, NAME) __attribute__((import_module(MOD), import_name(NAME)))

// -- GRAPHICS -- //

WASM_IMPORT("graphics", "clear_screen")
void ffb_clearScreen(int32_t c);

WASM_IMPORT("graphics", "set_color")
void ffb_setColor(int32_t c, int32_t r, int32_t g, int32_t b);

WASM_IMPORT("graphics", "draw_point")
void ffb_drawPoint(int32_t x, int32_t y, int32_t c);

WASM_IMPORT("graphics", "draw_line")
void ffb_drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color, int32_t stroke_width);

WASM_IMPORT("graphics", "draw_rect")
void ffb_drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_rounded_rect")
void ffb_drawRoundedRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t cw, int32_t ch, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_circle")
void ffb_drawCircle(int32_t x, int32_t y, int32_t d, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_ellipse")
void ffb_drawEllipse(int32_t x, int32_t y, int32_t w, int32_t h, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_triangle")
void ffb_drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_arc")
void ffb_drawArc(int32_t x, int32_t y, int32_t d, float ast, float asw, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_sector")
void ffb_drawSector(int32_t x, int32_t y, int32_t d, float ast, float asw, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_text")
void ffb_drawText(uintptr_t textPtr, int32_t textLen, uintptr_t fontPtr, int32_t fontLen, int32_t x, int32_t y, int32_t color);

WASM_IMPORT("graphics", "draw_image")
void ffb_drawImage(uintptr_t ptr, int32_t len, int32_t x, int32_t y);

WASM_IMPORT("graphics", "draw_sub_image")
void ffb_drawSubImage(uintptr_t ptr, uintptr_t len, int32_t x, int32_t y, int32_t subX, int32_t subY, int32_t subWidth, int32_t subHeight);

WASM_IMPORT("graphics", "set_canvas")
void ffb_setCanvas(uintptr_t ptr, uintptr_t len);

WASM_IMPORT("graphics", "unset_canvas")
void ffb_unsetCanvas();

// -- INPUT -- //

WASM_IMPORT("input", "read_pad")
int32_t ffb_readPad(int32_t player);

WASM_IMPORT("input", "read_buttons")
int32_t ffb_readButtons(int32_t player);

// -- FS -- //

WASM_IMPORT("fs", "get_file_size")
int32_t ffb_getFileSize(uintptr_t pathPtr, uintptr_t pathLen);

WASM_IMPORT("fs", "load_file")
uintptr_t ffb_loadFile(uintptr_t pathPtr, uintptr_t pathLen, uintptr_t bufPtr, uintptr_t bufLen);

WASM_IMPORT("fs", "dump_file")
uintptr_t ffb_dumpFile(uintptr_t pathPtr, uintptr_t pathLen, uintptr_t bufPtr, uintptr_t bufLen);

WASM_IMPORT("fs", "remove_file")
void ffb_removeFile(uintptr_t pathPtr, uintptr_t pathLen);

// -- NET -- //

WASM_IMPORT("misc", "get_me")
int32_t ffb_getMe();

WASM_IMPORT("misc", "get_peers")
int32_t ffb_getPeers();

// -- STATS -- //

WASM_IMPORT("misc", "add_progress")
uintptr_t ffb_addProgress(uintptr_t peerID, uintptr_t badgeID, int32_t val);

WASM_IMPORT("misc", "add_score")
int32_t ffb_addScore(uintptr_t peerID, uintptr_t badgeID, int32_t val);

// -- MISC -- //

WASM_IMPORT("misc", "log_debug")
void ffb_logDebug(uintptr_t ptr, uintptr_t len);

WASM_IMPORT("misc", "log_error")
void ffb_logError(uintptr_t ptr, uintptr_t len);

WASM_IMPORT("misc", "set_seed")
void ffb_setSeed(uintptr_t seed);

WASM_IMPORT("misc", "get_random")
uintptr_t ffb_getRandom();

WASM_IMPORT("misc", "get_name")
uintptr_t ffb_getName(uintptr_t ptr, uintptr_t len);

WASM_IMPORT("misc", "restart")
void ffb_restart();

WASM_IMPORT("misc", "quit")
void ffb_quit();

// -- AUDIO -- //

// sources (aka generators)

WASM_IMPORT("audio", "add_sine")
uintptr_t ffba_addSine(uintptr_t parentID, double freq, double phase);

WASM_IMPORT("audio", "add_square")
uintptr_t ffba_addSquare(uintptr_t parentID, double freq, double phase);

WASM_IMPORT("audio", "add_sawtooth")
uintptr_t ffba_addSawtooth(uintptr_t parentID, double freq, double phase);

WASM_IMPORT("audio", "add_triangle")
uintptr_t ffba_addTriangle(uintptr_t parentID, double freq, double phase);

WASM_IMPORT("audio", "add_noise")
uintptr_t ffba_addNoise(uintptr_t parentID, int32_t seed);

WASM_IMPORT("audio", "add_empty")
uintptr_t ffba_addEmpty(uintptr_t parentID);

WASM_IMPORT("audio", "add_zero")
uintptr_t ffba_addZero(uintptr_t parentID);

WASM_IMPORT("audio", "add_file")
uintptr_t ffba_addFile(uintptr_t parentID, uintptr_t ptr, uintptr_t len);

// nodes

WASM_IMPORT("audio", "add_mix")
uintptr_t ffba_addMix(uintptr_t parentID);

WASM_IMPORT("audio", "add_all_for_one")
uintptr_t ffba_addAllForOne(uintptr_t parentID);

WASM_IMPORT("audio", "add_gain")
uintptr_t ffba_addGain(uintptr_t parentID, double lvl);

WASM_IMPORT("audio", "add_loop")
uintptr_t ffba_addLoop(uintptr_t parentID);

WASM_IMPORT("audio", "add_concat")
uintptr_t ffba_addConcat(uintptr_t parentID);

WASM_IMPORT("audio", "add_pan")
uintptr_t ffba_addPan(uintptr_t parentID, double lvl);

WASM_IMPORT("audio", "add_mute")
uintptr_t ffba_addMute(uintptr_t parentID);

WASM_IMPORT("audio", "add_pause")
uintptr_t ffba_addPause(uintptr_t parentID);

WASM_IMPORT("audio", "add_track_position")
uintptr_t ffba_addTrackPosition(uintptr_t parentID);

WASM_IMPORT("audio", "add_low_pass")
uintptr_t ffba_addLowPass(uintptr_t parentID, double freq, double q);

WASM_IMPORT("audio", "add_high_pass")
uintptr_t ffba_addHighPass(uintptr_t parentID, double freq, double q);

WASM_IMPORT("audio", "add_take_left")
uintptr_t ffba_addTakeLeft(uintptr_t parentID);

WASM_IMPORT("audio", "add_take_right")
uintptr_t ffba_addTakeRight(uintptr_t parentID);

WASM_IMPORT("audio", "add_swap")
uintptr_t ffba_addSwap(uintptr_t parentID);

WASM_IMPORT("audio", "add_clip")
uintptr_t ffba_addClip(uintptr_t parentID, double low, double high);

// modulators

WASM_IMPORT("audio", "mod_linear")
void ffba_modLinear(uintptr_t nodeID, uintptr_t param, double aStart, double aEnd, uintptr_t startAt, uintptr_t endAt);

WASM_IMPORT("audio", "mod_hold")
void ffba_modHold(uintptr_t nodeID, uintptr_t param, double v1, double v2, uintptr_t time);

WASM_IMPORT("audio", "mod_sine")
void ffba_modSine(uintptr_t nodeID, uintptr_t param, double freq, double low, double high);

WASM_IMPORT("audio", "reset")
void ffba_reset(uintptr_t nodeID);

WASM_IMPORT("audio", "reset_all")
void ffba_resetAll(uintptr_t nodeID);

WASM_IMPORT("audio", "clear")
void ffba_clear(uintptr_t nodeID);
