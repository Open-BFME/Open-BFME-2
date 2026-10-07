// ?rva0030B7C2@@YA_NPBURva0030B7C2Point@@PAVRva0030B719Shape@@@Z
// partial score=0.88 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
// Native 0030B7C2..0030B812: reject a point outside the shape's refreshed
// bounds, then call the polygon crossing test at 0030B5AF. The existing
// row at 0030B6E3 proves the bounds getter ABI. ZH PolygonTrigger::pointInTrigger
// is a semantic lead; its integer coordinates differ from these target floats,
// so neither the original shape nor function name is claimed here.
struct Region2D
{
 Region2D(const Region2D &that);
 float x_min, y_min, x_max, y_max;
};
struct Rva0030B7C2Point { float x, y; };
class Rva0030B719Shape
{
public:
 Region2D rva0030B6E3();
};
bool rva0030B5AF(const Rva0030B7C2Point *point, Rva0030B719Shape *shape);

bool rva0030B7C2(const Rva0030B7C2Point *point, Rva0030B719Shape *shape)
{
 Region2D bounds = shape->rva0030B6E3();
 if (bounds.x_min > point->x) goto outside;
 if (bounds.y_min > point->y) goto outside;
 if (point->x > bounds.x_max) goto outside;
 if (point->y > bounds.y_max) goto outside;
 return rva0030B5AF(point, shape);
outside:
 return false;
}
