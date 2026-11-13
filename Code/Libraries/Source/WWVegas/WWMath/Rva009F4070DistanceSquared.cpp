// flags: region default (reverse/retail_inventory/flag_regions.csv)
#include "Coord2DBase.h"
class Rva009F4070PositionProvider {
public:
 virtual void slot0();
 virtual const Coord2DBase *position();
};
float Rva009F4070DistanceSquared(const Coord2DBase *coord2DBase,
 Rva009F4070PositionProvider *provider)
{
 const Coord2DBase *b = provider->position();
 float dy = b->y - coord2DBase->y;
 float dx = b->x - coord2DBase->x;
 return dx * dx + dy * dy;
}
