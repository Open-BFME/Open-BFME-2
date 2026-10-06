// flags: region default (reverse/retail_inventory/flag_regions.csv)
struct Coord2DBase { float x; float y; };
class Rva009F4070PositionProvider {
public:
 virtual void slot0();
 virtual const Coord2DBase *position();
};
float Rva009F4070DistanceSquared(const Coord2DBase *a,
 Rva009F4070PositionProvider *provider)
{
 const Coord2DBase *b = provider->position();
 float dy = b->y - a->y;
 float dx = b->x - a->x;
 return dx * dx + dy * dy;
}
