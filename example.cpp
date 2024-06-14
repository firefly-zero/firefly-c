#include "firefly.cpp"

WASM_EXPORT("boot")
void boot()
{
    DrawLine(Point(10, 10), Point(20, 20), LineStyle{color : BLACK});
}
