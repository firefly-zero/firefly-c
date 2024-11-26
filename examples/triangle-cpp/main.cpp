#include "../../src/firefly.c"

BOOT void boot()
{
    clear_screen(WHITE);
    draw_triangle(
        {60, 10}, {40, 40}, {80, 40},
        {
            .fill_color = LIGHT_GRAY,
            .stroke_color = DARK_BLUE,
            .stroke_width = 1,
        });
}
