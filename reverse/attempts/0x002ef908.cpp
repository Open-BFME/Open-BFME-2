// ?BuildGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
// partial score=0.9908842048 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Native2EF908..2EFB3A; WB BuildGroundPath; ZH buildGroundPath semantic spine.
#include "Lib/Coord3D.h"
typedef int Int;typedef bool Bool;
class Object;class PathfindCell;class AI;extern AI *TheAI;
struct PathGroundNode {PathGroundNode *next,*previous,*nextOptimized;Coord3D pos;int layer;};
class Path {public:Path();void rva00363FA4(Int);void *vtable;PathGroundNode *first,*last;char padC[0x28-0xC];};
class Pathfinder {public:Path *BuildGroundPath(const Coord3D *,PathfindCell *,Bool,Int);void PrependCells(Path *,const Coord3D *,PathfindCell *,Bool);Int AdjustGroundPathPosition(const Coord3D *,Coord3D *);};
static __forceinline void copyCoord3D(Coord3D *d,const Coord3D *s){d->x=s->x;d->y=s->y;d->z=s->z;}
struct PathGroundCoord : Coord3D {
PathGroundCoord() { x=y=z=-31313.13f; }
PathGroundCoord(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
PathGroundCoord(const PathGroundCoord &v) { x=v.x; y=v.y; z=v.z; }
void Sub(const Coord3D *v) { x-=v->x; y-=v->y; z-=v->z; }
void Add(const Coord3D *v) { x+=v->x; y+=v->y; z+=v->z; }
void Scale(float scale) { x*=scale; y*=scale; z*=scale; }
};
Path *Pathfinder::BuildGroundPath(const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Int pathDiameter)
{
Path *path = new Path;
PrependCells(path, fromPos, goalCell, center);
path->rva00363FA4(pathDiameter);
bool hasPrevious = false;
Coord3D previous;
for (PathGroundNode *node = path->first; node && node->nextOptimized; node = node->nextOptimized) {
const Coord3D *position = &node->pos;
PathGroundCoord saved(*position);
if (hasPrevious) {
PathGroundCoord a(*position);
a.Sub(&previous);
PathGroundCoord b(node->nextOptimized->pos);
b.Sub(position);
float cross = a.x * b.y - a.y * b.x;
Coord3D sum;
copyCoord3D(&sum, &a);
sum.x += b.x;
sum.y += b.y;
sum.z=0;
sum.Normalize();
float radius = *(float *)(*(char **)((char *)TheAI+0x18)+0xa0) * 2.0f;
sum.x *= radius;
sum.y *= radius;
Coord3D target;
copyCoord3D(&target, position);
if (cross < 0) {
target.x -= sum.y;
target.y += sum.x;
} else {
target.x += sum.y;
target.y -= sum.x;
}
AdjustGroundPathPosition(position, &target);
sum = target;
PathGroundCoord delta(sum);
delta.Sub(position);
target = *position;
target.x+=delta.x*0.5f;volatile float &yref=target.y;float yval=yref;yref=yval+delta.y*0.5f;volatile float &zref=target.z;float zval=zref;zref=zval+delta.z*0.5f;
node->pos = target;
}
hasPrevious = true;
previous = saved;
}
return path;
}
