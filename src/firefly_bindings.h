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
uintptr_t ffb_removeFile(uintptr_t pathPtr, uintptr_t pathLen);

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
