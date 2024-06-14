#include "firefly.h"
#include "firefly.cpp"

WASM_EXPORT("boot")
void boot()
{
    LineStyle s;
    s.color = BLACK;
    DrawLine(Point(10, 10), Point(20, 20), s);
}
