// cl: /O1 /Oy- /arch:SSE /G7 /MD
// Native30D111..30D241: polygon containment over vslot0 count, vslot1
// point lookup and vslot3 bounds. WB bd7a80 supports purpose; original
// shape owner remains unresolved. Native bounds/edge tests, SSE and full
// extent establish behavior. Point-swap30B343..30B378 is a distinct out-of-line
// helper; its copying constructor and aggregate assignment emit native53B.
#include "../../../Libraries/Include/Lib/Coord2D.h"
class Rva0007E016 { public:int rva0007E016(int,int); };
class Rva0007E02A { public:void *rva0007E02A(void *); };
class Rva0030D111Shape { public:virtual int count(); };
struct Rva0030D111Point : Coord2D {
 Rva0030D111Point() {}
 Rva0030D111Point(const Rva0030D111Point &r) { x=r.x;y=r.y; }
};
__declspec(noinline) void Rva0030B343Swap(Rva0030D111Point &a,Rva0030D111Point &b) {
 Rva0030D111Point t(a);a=b;b=t;
}
struct Rva0030D111Region {float x0,y0,x1,y1;};
bool Rva0030D111Contains(Rva0030D111Shape *shape,const Coord2D *point) {
 Rva0030D111Region bounds;
 reinterpret_cast<Rva0007E02A*>(shape)->rva0007E02A(&bounds);
 if(!(bounds.x0 > point->x || bounds.y0 > point->y || point->x > bounds.x1 || point->y > bounds.y1)) {
 int n=shape->count();bool inside=false;
 for(int i=0;i<n;++i) {
  Rva0030D111Point a,b;
  reinterpret_cast<Rva0007E016*>(shape)->rva0007E016(reinterpret_cast<int>(&a),i);
  reinterpret_cast<Rva0007E016*>(shape)->rva0007E016(reinterpret_cast<int>(&b),i>0?i-1:n-1);
  if(a.y == b.y)continue;
  if(point->x > a.x && point->x > b.x)continue;
  if(a.y > b.y)Rva0030B343Swap(a,b);
  if(point->y > b.y || a.y >= point->y)continue;
  float dy=b.y-a.y;
  float lhs=(point->y-a.y)*(b.x-a.x);
  float rhs=(point->x-a.x)*dy;
  if(lhs>=rhs) inside=!inside;
 }
 return inside;
 }
 return false;
}
