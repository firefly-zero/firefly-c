// A private header with runtime bindings for Firefly Zero.
// Don't use it directly. Everything defined here has a friendly wrapper.

#pragma once

#include <stdint.h>

#define WASM_IMPORT(MOD, NAME) __attribute__((import_module(MOD), import_name(NAME)))

WASM_IMPORT("graphics", "clear_screen")
void clearScreen(int32_t c);

WASM_IMPORT("graphics", "set_color")
void setColor(int32_t c, int32_t r, int32_t g, int32_t b);

WASM_IMPORT("graphics", "draw_point")
void drawPoint(int32_t x, int32_t y, int32_t c);

WASM_IMPORT("graphics", "draw_line")
void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color, int32_t stroke_width);

WASM_IMPORT("graphics", "draw_rect")
void drawRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_rounded_rect")
void drawRoundedRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t cw, int32_t ch, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_circle")
void drawCircle(int32_t x, int32_t y, int32_t d, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_ellipse")
void drawEllipse(int32_t x, int32_t y, int32_t w, int32_t h, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_triangle")
void drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_arc")
void drawArc(int32_t x, int32_t y, int32_t d, int32_t ast, int32_t asw, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_sector")
void drawSector(int32_t x, int32_t y, int32_t d, int32_t ast, int32_t asw, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_text")
void drawText(uintptr_t textPtr, int32_t textLen, uintptr_t fontPtr, int32_t fontLen, int32_t x, int32_t y, int32_t color);

WASM_IMPORT("graphics", "draw_image")
void drawImage(uintptr_t ptr, int32_t len, int32_t x, int32_t y);

WASM_IMPORT("graphics", "draw_sub_image")
void drawSubImage(uintptr_t ptr, uintptr_t len, int32_t x, int32_t y, int32_t subX, int32_t subY, int32_t subWidth, int32_t subHeight);
