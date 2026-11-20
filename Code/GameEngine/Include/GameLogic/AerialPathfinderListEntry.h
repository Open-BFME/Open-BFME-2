// The native map query at 0x00375AF7 reads the polygon and height at
// node offsets +8 and +0xC. Preserve the observed field load order.
#pragma once

class PolygonTrigger;
struct Rva00375AF7Entry
{
    PolygonTrigger *volatile shape;
    volatile float height;
};
