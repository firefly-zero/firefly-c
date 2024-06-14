#include "firefly.h"

void DrawLine(Point a, Point b, LineStyle s)
{
    drawLine(a.x, a.y, b.x, b.y, s.color, s.width);
}
