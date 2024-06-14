#include "firefly.h"
#include "firefly.cpp"

WASM_EXPORT("boot")
void boot()
{
    Point a;
    a.x = 10;
    a.y = 10;
    Point b;
    b.x = 20;
    b.y = 20;
    LineStyle s;
    s.color = BLACK;
    DrawLine(a, b, s);
}
