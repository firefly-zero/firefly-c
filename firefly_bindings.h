// A private header with runtime bindings for Firefly Zero.
// Don't use it directly. Everything defined here has a friendly wrapper.

#pragma once

#include <stdint.h>

#define WASM_IMPORT(MOD, NAME) __attribute__((import_module(MOD), import_name(NAME)))

WASM_IMPORT("graphics", "draw_line")
void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color, int32_t stroke_width);
