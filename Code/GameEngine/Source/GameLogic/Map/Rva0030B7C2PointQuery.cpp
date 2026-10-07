// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native30B7C2..30B812 RET: a caller-cleaned two-argument bounds precheck
// before the point/polygon worker30B5AF (native233B RET). The shape-return
// declaration reuses the verified35B provider30B6E3. Original names unknown.
struct Region2D {
 Region2D(const Region2D &);
 float x_min, y_min, x_max, y_max;
};
struct Rva0030B7C2Point { float x,y; };
class Rva0030B719Shape { public: Region2D rva0030B6E3(); };
bool rva0030B5AF(const Rva0030B7C2Point *, Rva0030B719Shape *);
bool rva0030B7C2(const Rva0030B7C2Point *point, Rva0030B719Shape *shape)
{
 Region2D bounds = shape->rva0030B6E3();
 if (bounds.x_min > point->x || bounds.y_min > point->y ||
     point->x > bounds.x_max || point->y > bounds.y_max)
  return false;
 return rva0030B5AF(point,shape);
}
