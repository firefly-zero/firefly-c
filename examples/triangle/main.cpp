#include "../../src/firefly.c"

BOOT void boot()
{
    ClearScreen(WHITE);
    DrawTriangle(
        Point{30, 10},
        Point{20, 30},
        Point{40, 30},
        Style{fill_color : BLACK, stroke_color : RED, stroke_width : 2});
}
