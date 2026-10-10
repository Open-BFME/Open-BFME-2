// ?BuildGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
//
// Pathfinder::BuildGroundPath: retail 0x002EF908..0x002EFB3A (562 bytes;
// ret 0x10). WorldBuilder twin 0x00D4F370 (pathfinder.cpp asserts at lines
// 7315..7316) names it; Zero Hour's buildGroundPath supplies the spine:
// allocate a Path (operator new 0x28 and the rowed Path::Path 0x00363DC8),
// prepend the cells (rowed PrependCells 0x002EE1C7) and ground-optimize it
// with the path diameter (rowed Path::rva00363FA4). BFME 2 then smooths each
// interior corner as the WB twin does: the sum of the incoming and outgoing
// segments is normalized (rowed Coord3D::Normalize 0x00005A70) and scaled
// by twice TheAI's AI data +0xA0 value; the point is pushed sideways by the
// sign of the 2D cross product and adjusted by the rowed
// AdjustGroundPathPosition 0x002EDFBD and the node moves half way there.
// The WB twin's debug-only overlay drawing and SetDebugPath are absent from
// retail. Coordinates go through a TU-local Coord3D adapter with member-wise
// copies as the WB twin's Coord3D methods; the halving is written per
// component with the y and z halves held in the direction as retail's
// register use shows.
#include "Lib/Coord3D.h"
typedef int Int;typedef bool Bool;
class PathfindCell;
struct AIData {char pad00[0xA0];float m_a0;};
class AI {public:const AIData *getAiData() const {return m_aiData;}private:char pad00[0x18];const AIData *m_aiData;};
extern AI *TheAI;
struct PathGroundNode {PathGroundNode *next,*previous,*nextOptimized;Coord3D pos;int layer;};
class Path {public:Path();void rva00363FA4(Int);void *vtable;PathGroundNode *first,*last;char padC[0x28-0xC];};
class Pathfinder {public:Path *BuildGroundPath(const Coord3D *,PathfindCell *,Bool,Int);void PrependCells(Path *,const Coord3D *,PathfindCell *,Bool);Int AdjustGroundPathPosition(const Coord3D *,Coord3D *);};
static __forceinline void copyCoord3D(Coord3D *d,const Coord3D *s){d->x=s->x;d->y=s->y;d->z=s->z;}
static __forceinline void subCoord3D(Coord3D *d,const Coord3D *s){d->x-=s->x;d->y-=s->y;d->z-=s->z;}
struct PathGroundCoord : Coord3D {
PathGroundCoord() {}
PathGroundCoord(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
PathGroundCoord(const PathGroundCoord &v) { x=v.x; y=v.y; z=v.z; }
void Sub(const Coord3D *v) { x-=v->x; y-=v->y; z-=v->z; }
void Add(const Coord3D *v) { x+=v->x; y+=v->y; z+=v->z; }
void Set(const Coord3D &v) { Coord3D::operator=(v); }
};
Path *Pathfinder::BuildGroundPath(const Coord3D *fromPos, PathfindCell *goalCell, Bool center, Int pathDiameter)
{
Path *path = new Path;
PrependCells(path, fromPos, goalCell, center);
path->rva00363FA4(pathDiameter);
Bool havePrev = false;
PathGroundCoord prevPos;
for (PathGroundNode *node = path->first; node; node = node->nextOptimized) {
PathGroundNode *next = node->nextOptimized;
if (!next) break;
PathGroundCoord curPos(node->pos);
if (havePrev) {
PathGroundCoord v1(node->pos);
v1.Sub(&prevPos);
PathGroundCoord v2(next->pos);
v2.Sub(&node->pos);
float cross = v1.x * v2.y - v1.y * v2.x;
Coord3D dir;
copyCoord3D(&dir, &v1);
dir.x += v2.x;
dir.y += v2.y;
dir.z = 0;
dir.Normalize();
float r = 2.0f * TheAI->getAiData()->m_a0;
dir.x *= r;
dir.y *= r;
PathGroundCoord newPos(node->pos);
if (cross < 0) {
newPos.x += -dir.y;
newPos.y += dir.x;
} else {
newPos.x += dir.y;
newPos.y += -dir.x;
}
AdjustGroundPathPosition(&node->pos, &newPos);
dir = newPos;
subCoord3D(&dir, &node->pos);
newPos.Set(node->pos);
newPos.x += dir.x * 0.5f;
dir.y *= 0.5f;
newPos.y += dir.y;
dir.z *= 0.5f;
newPos.z += dir.z;
node->pos = newPos;
}
havePrev = true;
prevPos = curPos;
}
return path;
}
