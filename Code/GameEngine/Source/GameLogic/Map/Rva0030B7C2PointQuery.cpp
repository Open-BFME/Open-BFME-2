// cl: /O1 /Oy- /arch:SSE /G6 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
// Native30B7C2..30B812 RET: a caller-cleaned two-argument bounds precheck
// before the point/polygon worker30B5AF (native233B RET). The shape-return
// declaration reuses the verified35B provider30B6E3. Original names unknown.
struct Region2D {
 Region2D(const Region2D &);
 float x_min, y_min, x_max, y_max;
};
struct Rva0030B7C2Point { float x,y; };
struct Rva0030D111Point : Coord2D {
 Rva0030D111Point() {}
 Rva0030D111Point(const Rva0030D111Point &r) { x=r.x;y=r.y; }
};
void Rva0030B343Swap(Rva0030D111Point &,Rva0030D111Point &);
class Rva0030B719Shape {
public:
 Region2D rva0030B6E3();
 _STL::vector<Rva0030D111Point> m_points;
 Region2D m_bounds;
 float m_innerRadius,m_radius;
 bool m_dirty;
};
bool rva0030B5AF(const Rva0030B7C2Point *, Rva0030B719Shape *);
bool rva0030B7C2(const Rva0030B7C2Point *point, Rva0030B719Shape *shape)
{
 Region2D bounds = shape->rva0030B6E3();
 if (bounds.x_min > point->x || bounds.y_min > point->y ||
     point->x > bounds.x_max || point->y > bounds.y_max)
  return false;
 return rva0030B5AF(point,shape);
}

// Native30B5AF..30B698 RET: crossing parity over the vector at shape+0.
// WB bf7a20 independently agrees on the ordered edge tests and previous
// index, including the half-open y range. Original owner/name remain opaque.
// Use the independently rowed swap's exact point type and copy constructor.
bool rva0030B5AF(const Rva0030B7C2Point *point,Rva0030B719Shape *shape)
{
 const Rva0030D111Point *points=shape->m_points.begin();
 int n=shape->m_points.end()-points;
 bool inside=false;
 for(int i=0;i<n;++i) {
  Rva0030D111Point a(points[i]);
  Rva0030D111Point b(points[i>0?i-1:n-1]);
  if(a.y == b.y)continue;
  if(point->x > a.x && point->x > b.x)continue;
  if(a.y > b.y)Rva0030B343Swap(a,b);
  if(point->y > b.y || a.y >= point->y)continue;
  float dy=b.y-a.y;
  float lhs=(point->y-a.y)*(b.x-a.x);
  float rhs=(point->x-a.x)*dy;
  if(lhs>=rhs)inside=!inside;
 }
 return inside;
}
