// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?pointInTrigger@PolygonTrigger@@QAE_NABVICoord3D@@@Z
// Retail boundary 0x002E3A13..0x002E3A39 (38B); target bytes copy x/y into a
// two-int local and call 0x00285B66 with that pointer and this+8. The ZH donor
// identifies the method's polygon-test role; its full ray-cast is not this body.

class ICoord3D
{
public:
    int x;
    int y;
    int z;
};

struct PlanarPoint
{
    int x;
    int y;
};

bool rva00285B66(const void *point, const void *region);

class PolygonTrigger
{
public:
    bool pointInTrigger(const ICoord3D &point);
};

bool PolygonTrigger::pointInTrigger(const ICoord3D &point)
{
    PlanarPoint planarPoint;
    planarPoint.x = point.x;
    planarPoint.y = point.y;
    const void *region = reinterpret_cast<const char *>(this) + 8;
    return rva00285B66(&planarPoint, region);
}
