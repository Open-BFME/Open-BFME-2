// cl: /O1 /Oy- /arch:SSE /G7 /MD
// Native30D111..30D241: polygon containment over vslot0 count, vslot1
// point lookup and vslot3 bounds. WB bd7a80 supports purpose; original
// shape owner remains unresolved. Native bounds/edge tests, SSE and full
// extent establish behavior. Point-swap30B343..30B378 is a distinct out-of-line
// helper; its copying constructor and aggregate assignment emit native53B.
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>
class Rva0007E016 { public:int rva0007E016(int,int); };
class Rva0007E02A { public:void *rva0007E02A(void *); };
class Rva0030D111Shape { public:virtual int count(); virtual void pointLookup(); virtual int planeHeight(); };
struct Rva0030D111Point : Coord2D {
 Rva0030D111Point() {}
 Rva0030D111Point(const Rva0030D111Point &source) { x=source.x;y=source.y; }
};
__declspec(noinline) void swapPoints(Rva0030D111Point &a,Rva0030D111Point &b) {
 Rva0030D111Point t(a);a=b;b=t;
}
struct Rva0030D111Region {float x0,y0,x1,y1;};
bool Rva0030D111Contains(Rva0030D111Shape *shape,const Coord2D *point) {
 Rva0030D111Region bounds;
 reinterpret_cast<Rva0007E02A*>(shape)->rva0007E02A(&bounds);
 if(!(bounds.x0 > point->x || bounds.y0 > point->y || point->x > bounds.x1 || point->y > bounds.y1)) {
 int vertexCount=shape->count();bool inside=false;
 for(int i=0;i<vertexCount;++i) {
  Rva0030D111Point edgeStart,b;
  reinterpret_cast<Rva0007E016*>(shape)->rva0007E016(reinterpret_cast<int>(&edgeStart),i);
  reinterpret_cast<Rva0007E016*>(shape)->rva0007E016(reinterpret_cast<int>(&b),i>0?i-1:vertexCount-1);
  if(edgeStart.y == b.y)continue;
  if(point->x > edgeStart.x && point->x > b.x)continue;
  if(edgeStart.y > b.y)swapPoints(edgeStart,b);
  if(point->y > b.y || edgeStart.y >= point->y)continue;
  float dy=b.y-edgeStart.y;
  float lhs=(point->y-edgeStart.y)*(b.x-edgeStart.x);
  float rhs=(point->x-edgeStart.x)*dy;
  if(lhs>=rhs) inside=!inside;
 }
 return inside;
 }
 return false;
}

// Native30D241..30D346 cdecl: intersects a ray with the shape's horizontal
// plane (slot-2 integer height, normal 0,0,1), then checks the XY hit with the
// containment worker above and copies the hit out. The threshold compares the
// CRT fabs(double) result through a float local (retail fld dword 0.0001f pool
// literal; a double compare folds it to a qword). Scoping that local and the
// test result to a block keeps retail's SSE allocation for the hit point.
// Owner and names remain address-derived.
static inline float Rva0030D241Dot(const Coord3D &left,const Coord3D &right) {
 float x=left.x*right.x;
 float y=left.y*right.y;
 float xy=x+y;
 float z=left.z*right.z;
 return xy+z;
}
bool Rva0030D241Intersect(Rva0030D111Shape *shape,const Coord3D *origin,
                        const Coord3D *direction,Coord3D *output) {
 float planeD=0.0f-static_cast<float>(shape->planeHeight());
 Coord3D normal={0.0f,0.0f,1.0f};
 float denominator=Rva0030D241Dot(normal,*direction);
 bool parallel;
 { float absDenominator=fabs(static_cast<double>(denominator)); parallel=!(absDenominator>0.0001f); }
 if(!parallel) {
  float distance=(Rva0030D241Dot(normal,*origin)+planeD)/denominator;
  Coord3D intersection=*direction;
  float scale=0.0f-distance;
  intersection.x*=scale;intersection.y*=scale;intersection.z*=scale;
  intersection.x+=origin->x;intersection.y+=origin->y;intersection.z+=origin->z;
  Coord2D point;point.x=intersection.x;point.y=intersection.y;
  if(Rva0030D111Contains(shape,&point)) {*output=intersection;return true;}
 }
 return false;
}
