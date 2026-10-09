// ?ExamineNeighboringCellsForSidewaysAttack@Pathfinder@@QAEHPAVObject@@PBUCoord3D@@@Z
// partial score=0.95 date=2026-10-10
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// NEAR (helper draft, not landed): ?ExamineNeighboringCellsForSidewaysAttack@Pathfinder@@QAEHPAVPathfindCell@@PBUICoord2D@@HABVLocomotorSet@@_N3HABU3@PAVObject@@H@Z
// retail 0x002F8B00..0x002F8E2D (813 bytes). WB twin 0xD66060 Pathfinder::ExamineNeighboringCellsForSidewaysAttack.
// Best: compiled 816 bytes, ratio 0.95; only stack layout differs: retail keeps goalNdx in the
// targetWorld slot (-0x24, frame 0x2C) while this draft gives goalNdx its own slot (frame 0x34),
// which shifts delta to -0x34 and the Add argument scheduling by one store.
// dir.x stored early / dir.y stored after the Sub call is what gives retail's forwarding of Sin into [ebp+0x10].
// Pins needed: ?Rva001040AESub@@YA?AVCoord2D@@V1@ABV1@@Z=0x001040AE ?Rva0007DEC8Add@@YA?AVCoord2D@@V1@ABV1@@Z=0x0007DEC8
//   ?Rva002E7917@Pathfinder@@QAE?AUICoord2D@@_NPBUCoord3D@@@Z=0x002E7917 ?rva002F83F5@Pathfinder@@QAEHPAVPathfindCell@@0ABVLocomotorSet@@_N2HABUICoord2D@@PAVObject@@H@Z=0x002F83F5
#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0,
	PATHFIND_LAYER_GROUND = 1
};
struct ICoord2D { Int x,y; };
class LocomotorSet;
class Object
{
public:
	char m_pad00[0x44];
	float m_orientation;				// +0x44
	float getOrientation() const { return m_orientation; }
};
struct In002E6BA1 { Int x,y; };
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,Int,In002E6BA1 *);
class Rva002E6AF3 { public: Int get() const; };
class Rva002E6B06 { public: Int rva002E6B06(); };
struct PathfinderGroundInfo { Int x,y; Int parent; void *parentWaypoint; };
class PathfindCell
{
public:
	void ReleaseInfo();
	float rva0052DD75(float facing, Int count, float weight);
	__forceinline void allocateInfo(In002E6BA1 *pos) {
		if(!m_pathInfo) { if(!TheMixFileInfoPool)Rva0052DBCDInit();m_pathInfo=(PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool,(Int)this,pos); }
		else m_pathInfo->parentWaypoint=0;
	}
	Int getXIndex() const { return m_pathInfo->x; }
	Int getYIndex() const { return m_pathInfo->y; }
	PathfinderGroundInfo *m_pathInfo;
};
inline float sqr(float v) { return v * v; }
// class-gate: allow Coord2D retail passes Coord2D by value through the 0x001040AE and 0x0007DEC8 helpers with an argument-area save (user copy ctor and dtor make BFME 2's Coord2D non-POD); the canonical plain Coord2D has neither
class Coord2D
{
public:
	Coord2D() {}
	Coord2D(const Coord2D &that) : x(that.x), y(that.y) {}
	Coord2D(float ix, float iy) : x(ix), y(iy) {}
	Coord2D(Int ix, Int iy) : x((float)ix), y((float)iy) {}
	~Coord2D() {}
	float dot(const Coord2D &c) const { return y * c.y + x * c.x; }
	Coord2D &operator*=(float s) { x *= s; y *= s; return *this; }
	Coord2D &operator-=(const Coord2D &c) { x -= c.x; y -= c.y; return *this; }
	Coord2D &operator+=(const Coord2D &c) { x += c.x; y += c.y; return *this; }
	__forceinline float GetLengthEstimate() const { return fabs(x) > fabs(y) ? fabs(x) + fabs(y) * 0.25f : fabs(y) + fabs(x) * 0.25f; }
	__forceinline float GetLength() const { return (float)sqrt(x * x + sqr(y)); }
	__forceinline void Normalize() { float inv = 1.0f / GetLength(); x *= inv; y *= inv; }
	float x;
	float y;
};
float Sin(float x);
float Cos(float x);
Coord2D Rva001040AESub(Coord2D a, const Coord2D &b);
Coord2D Rva0007DEC8Add(Coord2D a, const Coord2D &b);

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	ICoord2D Rva002E7917(bool center, const Coord3D *pos);
	Int rva002F83F5(PathfindCell *parentCell, PathfindCell *goalCell, const LocomotorSet &locomotorSet, Bool isHuman, Bool centerInCell, Int radius, const ICoord2D &startCellNdx, Object *obj, Int attackDistance);
	Int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *parentCell, const ICoord2D *targetNdx, Int offset, const LocomotorSet &locomotorSet, Bool isHuman, Bool centerInCell, Int radius, const ICoord2D &startCellNdx, Object *obj, Int attackDistance);
};

Int Pathfinder::ExamineNeighboringCellsForSidewaysAttack(PathfindCell *parentCell, const ICoord2D *targetNdx, Int offset, const LocomotorSet &locomotorSet, Bool isHuman, Bool centerInCell, Int radius, const ICoord2D &startCellNdx, Object *obj, Int attackDistance)
{
	ICoord2D goalNdx;
	Int distSqr = (parentCell->getXIndex() - targetNdx->x) * (parentCell->getXIndex() - targetNdx->x) + (parentCell->getYIndex() - targetNdx->y) * (parentCell->getYIndex() - targetNdx->y);
	if (distSqr * 5 * 5 < (offset + attackDistance) * (offset + attackDistance)) {
		float angle = parentCell->rva0052DD75(obj->getOrientation(), 10, 0.5f);
		Coord2D parentWorld(parentCell->getXIndex() * 10, parentCell->getYIndex() * 10);
		float s = Sin(angle);
		Coord2D dir;
		dir.x = Cos(angle);
		Coord2D targetWorld(targetNdx->x * 10, targetNdx->y * 10);
		if (centerInCell) {
			parentWorld.x += 5.0f;
			parentWorld.y += 5.0f;
		}
		Coord2D delta = Rva001040AESub(targetWorld, parentWorld);
		dir.y = s;
		float dot = dir.dot(delta);
		dir *= dot;
		Coord2D p = Rva0007DEC8Add(parentWorld, dir);
		p -= targetWorld;
		if (p.GetLengthEstimate() < 0.0001f) {
			p.x = dir.y;
			p.y = -dir.x;
		}
		p.Normalize();
		p *= (float)offset;
		p += targetWorld;
		goalNdx = Rva002E7917(centerInCell, (const Coord3D *)&p);
	} else {
		goalNdx = *targetNdx;
	}
	PathfindCell *goalCell = getCell(PATHFIND_LAYER_GROUND, goalNdx.x, goalNdx.y);
	if (!goalCell) {
		return 0;
	}
	Bool hadInfo = goalCell->m_pathInfo != 0;
	if (!hadInfo) {
		goalCell->allocateInfo((In002E6BA1 *)&goalNdx);
	}
	Int count = rva002F83F5(parentCell, goalCell, locomotorSet, isHuman, centerInCell, radius, startCellNdx, obj, attackDistance);
	if (!hadInfo) {
		if (!(unsigned char)((Rva002E6AF3 *)goalCell)->get() && !(unsigned char)((Rva002E6B06 *)goalCell)->rva002E6B06()) {
			goalCell->ReleaseInfo();
		}
	}
	return count;
}
