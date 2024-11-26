// A private header with runtime bindings for Firefly Zero.
// Don't use it directly. Everything defined here has a friendly wrapper.

#pragma once

#include <stdint.h>

#define WASM_IMPORT(MOD, NAME) __attribute__((import_module(MOD), import_name(NAME)))

// -- GRAPHICS -- //

WASM_IMPORT("graphics", "clear_screen")
void _ffb_clear_screen(int32_t c);

WASM_IMPORT("graphics", "set_color")
void _ffb_set_color(int32_t c, int32_t r, int32_t g, int32_t b);

WASM_IMPORT("graphics", "draw_point")
void _ffb_draw_point(int32_t x, int32_t y, int32_t c);

WASM_IMPORT("graphics", "draw_line")
void _ffb_draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t color, int32_t stroke_width);

WASM_IMPORT("graphics", "draw_rect")
void _ffb_draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_rounded_rect")
void _ffb_draw_rounded_rect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t cw, int32_t ch, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_circle")
void _ffb_draw_circle(int32_t x, int32_t y, int32_t d, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_ellipse")
void _ffb_draw_ellipse(int32_t x, int32_t y, int32_t w, int32_t h, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_triangle")
void _ffb_draw_triangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_arc")
void _ffb_draw_arc(int32_t x, int32_t y, int32_t d, float ast, float asw, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_sector")
void _ffb_draw_sector(int32_t x, int32_t y, int32_t d, float ast, float asw, int32_t fc, int32_t sc, int32_t sw);

WASM_IMPORT("graphics", "draw_text")
void _ffb_draw_text(uintptr_t textPtr, int32_t textLen, uintptr_t fontPtr, int32_t fontLen, int32_t x, int32_t y, int32_t color);

WASM_IMPORT("graphics", "draw_image")
void _ffb_draw_image(uintptr_t ptr, int32_t len, int32_t x, int32_t y);

WASM_IMPORT("graphics", "draw_sub_image")
void _ffb_draw_sub_image(uintptr_t ptr, uintptr_t len, int32_t x, int32_t y, int32_t subX, int32_t subY, int32_t subWidth, int32_t subHeight);

WASM_IMPORT("graphics", "set_canvas")
void _ffb_set_canvas(uintptr_t ptr, uintptr_t len);

WASM_IMPORT("graphics", "unset_canvas")
void _ffb_unset_canvas();

// -- INPUT -- //

WASM_IMPORT("input", "read_pad")
int32_t _ffb_read_pad(int32_t player);

WASM_IMPORT("input", "read_buttons")
int32_t _ffb_read_buttons(int32_t player);

// -- FS -- //

WASM_IMPORT("fs", "get_file_size")
int32_t _ffb_get_file_size(uintptr_t pathPtr, uintptr_t pathLen);

WASM_IMPORT("fs", "load_file")
uintptr_t _ffb_load_file(uintptr_t pathPtr, uintptr_t pathLen, uintptr_t bufPtr, uintptr_t bufLen);

WASM_IMPORT("fs", "dump_file")
uintptr_t _ffb_dump_file(uintptr_t pathPtr, uintptr_t pathLen, uintptr_t bufPtr, uintptr_t bufLen);

WASM_IMPORT("fs", "remove_file")
void _ffb_remove_file(uintptr_t pathPtr, uintptr_t pathLen);

// -- NET -- //

WASM_IMPORT("misc", "get_me")
int32_t _ffb_get_me();

WASM_IMPORT("misc", "get_peers")
int32_t _ffb_get_peers();

// -- STATS -- //

WASM_IMPORT("misc", "add_progress")
uintptr_t _ffb_add_progress(uintptr_t peerID, uintptr_t badgeID, int32_t val);

WASM_IMPORT("misc", "add_score")
int32_t _ffb_add_score(uintptr_t peerID, uintptr_t badgeID, int32_t val);

// -- MISC -- //

WASM_IMPORT("misc", "log_debug")
void _ffb_log_debug(uintptr_t ptr, uintptr_t len);

WASM_IMPORT("misc", "log_error")
void _ffb_log_error(uintptr_t ptr, uintptr_t len);

WASM_IMPORT("misc", "set_seed")
void _ffb_set_seed(uintptr_t seed);

WASM_IMPORT("misc", "get_random")
uintptr_t _ffb_get_random();

WASM_IMPORT("misc", "get_name")
uintptr_t _ffb_get_name(uintptr_t ptr, uintptr_t len);

WASM_IMPORT("misc", "restart")
void _ffb_restart();

WASM_IMPORT("misc", "quit")
void _ffb_quit();

// -- AUDIO -- //

// sources (aka generators)

WASM_IMPORT("audio", "add_sine")
uint32_t _ffba_add_sine(uint32_t parentID, float freq, float phase);

WASM_IMPORT("audio", "add_square")
uint32_t _ffba_add_square(uint32_t parentID, float freq, float phase);

WASM_IMPORT("audio", "add_sawtooth")
uint32_t _ffba_add_sawtooth(uint32_t parentID, float freq, float phase);

WASM_IMPORT("audio", "add_triangle")
uint32_t _ffba_add_triangle(uint32_t parentID, float freq, float phase);

WASM_IMPORT("audio", "add_noise")
uint32_t _ffba_add_noise(uint32_t parentID, int32_t seed);

WASM_IMPORT("audio", "add_empty")
uint32_t _ffba_add_empty(uint32_t parentID);

WASM_IMPORT("audio", "add_zero")
uint32_t _ffba_add_zero(uint32_t parentID);

WASM_IMPORT("audio", "add_file")
uint32_t _ffba_add_file(uint32_t parentID, uintptr_t ptr, uintptr_t len);

// nodes

WASM_IMPORT("audio", "add_mix")
uint32_t _ffba_add_mix(uint32_t parentID);

WASM_IMPORT("audio", "add_all_for_one")
uint32_t _ffba_add_all_for_one(uint32_t parentID);

WASM_IMPORT("audio", "add_gain")
uint32_t _ffba_add_gain(uint32_t parentID, float lvl);

WASM_IMPORT("audio", "add_loop")
uint32_t _ffba_add_loop(uint32_t parentID);

WASM_IMPORT("audio", "add_concat")
uint32_t _ffba_add_concat(uint32_t parentID);

WASM_IMPORT("audio", "add_pan")
uint32_t _ffba_add_pan(uint32_t parentID, float lvl);

WASM_IMPORT("audio", "add_mute")
uint32_t _ffba_add_mute(uint32_t parentID);

WASM_IMPORT("audio", "add_pause")
uint32_t _ffba_add_pause(uint32_t parentID);

WASM_IMPORT("audio", "add_track_position")
uint32_t _ffba_add_track_position(uint32_t parentID);

WASM_IMPORT("audio", "add_low_pass")
uint32_t _ffba_add_low_pass(uint32_t parentID, float freq, float q);

WASM_IMPORT("audio", "add_high_pass")
uint32_t _ffba_add_high_pass(uint32_t parentID, float freq, float q);

WASM_IMPORT("audio", "add_take_left")
uint32_t _ffba_add_take_left(uint32_t parentID);

WASM_IMPORT("audio", "add_take_right")
uint32_t _ffba_add_take_right(uint32_t parentID);

WASM_IMPORT("audio", "add_swap")
uint32_t _ffba_add_swap(uint32_t parentID);

WASM_IMPORT("audio", "add_clip")
uint32_t _ffba_add_clip(uint32_t parentID, float low, float high);

// modulators

WASM_IMPORT("audio", "mod_linear")
void _ffba_mod_linear(uint32_t nodeID, uint32_t param, float x_start, float x_end, uint32_t start_at, uint32_t end_at);

WASM_IMPORT("audio", "mod_hold")
void _ffba_mod_hold(uint32_t nodeID, uint32_t param, float before, float after, uint32_t time);

WASM_IMPORT("audio", "mod_sine")
void _ffba_mod_sine(uint32_t nodeID, uint32_t param, float freq, float low, float high);

WASM_IMPORT("audio", "reset")
void _ffba_reset(uint32_t nodeID);

WASM_IMPORT("audio", "reset_all")
void _ffba_reset_all(uint32_t nodeID);

WASM_IMPORT("audio", "clear")
void _ffba_clear(uint32_t nodeID);
