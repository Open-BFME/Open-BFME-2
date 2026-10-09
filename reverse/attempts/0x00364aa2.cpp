// ?rva00364AA2@Path@@QAEXPAVPathNode@@00M@Z
// partial score=0.34 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /ICode/Libraries/Include/Lib
// NEAR (instruction ratio ~0.34): structural draft of retail 0x00364AA2 (2029
// bytes, thiscall ret 0x10) from WB twin 0xF221B0 (14881-byte debug body).
// Path corner rounding: two LineSegClass legs prev->cur->next, radius clamp to
// 0.75 of the shorter leg (x1.75 below 0.7225663 rad), node id +0x20 must be
// 0x7FFFFFFF and the turn at most 1.7278761 rad else 0x003649B1(cur); offset
// legs by the leg directions rotated -PI/2 then Find_Intersection gives the
// arc centre; arc points go through appendNode 0x002655E3 (layer +0x18 and
// 0x7FFFFFFF) and the last one becomes cur's position (movsd into cur+0xC).
// Differences left: retail frame 0x138 vs 0x16C here (stack packing and the
// copies of prev/next positions); scheduling of the vector temporaries.
// Callee 0x003641AE is called as a thiscall member (ecx=this loaded before the
// call) but its row is ?Rva003641AEClamp@@YGHMM@Z (stdcall free): it needs a
// thiscall pin such as ?rva003641AE@Path@@QAEHMM@Z.
#include "vector3.h"
#include "Coord2D.h"
#include "Coord3D.h"

class LineSegClass
{
public:
	LineSegClass(const Vector3 &p0, const Vector3 &p1);
	void Set(const Vector3 &p0, const Vector3 &p1);
	bool Find_Intersection(const LineSegClass &other_line, Vector3 *p1, float *fraction1, Vector3 *p2, float *fraction2) const;
	const Vector3 &Get_Dir(void) const { return Dir; }
	float Get_Length(void) const { return Length; }

	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	float Length;
};

struct Rva00363B4BVector { float x, y, z; };
float rva00363B4BAngle(const Rva00363B4BVector *a, const Rva00363B4BVector *b);

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

class PathNode
{
public:
	const Coord3D *getPosition(void) const { return &m_pos; }
	void setPosition(const Coord3D *pos) { m_pos = *pos; }
	PathfindLayerEnum getLayer(void) const { return m_layer; }

	char m_pad00[0x0C];
	Coord3D m_pos;
	PathfindLayerEnum m_layer;
	int m_1c;
	int m_id20;
};

class Path
{
public:
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int portal);
	void rva003649B1(const PathNode *node);
	int rva003641AE(float angle, float radius);
	void rva00364AA2(PathNode *prev, PathNode *cur, PathNode *next, float radius);
};
void Path::rva00364AA2(PathNode *prev, PathNode *cur, PathNode *next, float radius)
{
	Coord3D prevPos;
	prevPos.x = prev->getPosition()->x;
	prevPos.y = prev->getPosition()->y;
	Coord3D curPos;
	curPos.x = cur->getPosition()->x;
	curPos.y = cur->getPosition()->y;
	curPos.z = cur->getPosition()->z;
	Coord3D nextPos;
	nextPos.x = next->getPosition()->x;
	nextPos.y = next->getPosition()->y;
	LineSegClass seg1(Vector3(prevPos.x, prevPos.y, 0), Vector3(curPos.x, curPos.y, 0));
	LineSegClass seg2(Vector3(curPos.x, curPos.y, 0), Vector3(nextPos.x, nextPos.y, 0));
	float minLen = seg1.Get_Length();
	if (minLen > seg2.Get_Length())
		minLen = seg2.Get_Length();
	if (radius > minLen * 0.75f)
		radius = minLen * 0.75f;
	Coord2D a, d;
	bool turnLeft;
	if (Vector3::Cross_Product_Z(seg1.Get_Dir(), seg2.Get_Dir()) < 0.0f) {
		a.x = prevPos.x; a.y = prevPos.y;
		d.x = nextPos.x; d.y = nextPos.y;
		turnLeft = true;
	} else {
		d.x = prevPos.x; d.y = prevPos.y;
		a.x = nextPos.x; a.y = nextPos.y;
		turnLeft = false;
		seg1.Set(Vector3(a.x, a.y, 0), Vector3(curPos.x, curPos.y, 0));
		seg2.Set(Vector3(curPos.x, curPos.y, 0), Vector3(d.x, d.y, 0));
	}
	float angle = rva00363B4BAngle((const Rva00363B4BVector *)&seg1.Get_Dir(), (const Rva00363B4BVector *)&seg2.Get_Dir());
	if (angle < 0.7225663304328919)
		radius *= 1.75f;
	if (cur->m_id20 != 0x7fffffff || angle > 1.7278761f) {
		rva003649B1(cur);
		return;
	}
	Vector3 v1 = radius * seg1.Get_Dir();
	Vector3 v2 = radius * seg2.Get_Dir();
	v1.Rotate_Z(-1.5707963705062866f);
	v2.Rotate_Z(-1.5707963705062866f);
	LineSegClass off1(Vector3(a.x, a.y, 0) + v1, Vector3(curPos.x, curPos.y, 0) + v1);
	LineSegClass off2(Vector3(curPos.x, curPos.y, 0) + v2, Vector3(d.x, d.y, 0) + v2);
	Vector3 n1 = v1;
	n1.Normalize();
	Vector3 n2 = v2;
	n2.Normalize();
	float arc = rva00363B4BAngle((const Rva00363B4BVector *)&n1, (const Rva00363B4BVector *)&n2);
	int count = rva003641AE(arc, radius);
	if (count < 2) {
		rva003649B1(cur);
		return;
	}
	float step = arc / count;
	Vector3 center;
	Vector3 other;
	float fraction;
	if (!off1.Find_Intersection(off2, &center, &fraction, &other, &fraction))
		return;
	Coord3D pt;
	if (turnLeft) {
		pt.x = center.X - v1.X; pt.y = center.Y - v1.Y; pt.z = curPos.z;
		rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
		v1 *= -1.0f;
		for (int i = 1; i < count; ++i) {
			Vector3 q = center + v1;
			v1.Rotate_Z(-step);
			pt.x = q.X; pt.y = q.Y; pt.z = curPos.z;
			rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
		}
		pt.x = center.X - v2.X; pt.y = center.Y - v2.Y; pt.z = curPos.z;
		rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
		cur->setPosition(&pt);
	} else {
		pt.x = center.X - v2.X; pt.y = center.Y - v2.Y; pt.z = curPos.z;
		rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
		v2 *= -1.0f;
		for (int i = 1; i < count; ++i) {
			v2.Rotate_Z(step);
			Vector3 q = center + v2;
			pt.x = q.X; pt.y = q.Y; pt.z = curPos.z;
			rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
		}
		pt.x = center.X - v1.X; pt.y = center.Y - v1.Y; pt.z = curPos.z;
		rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
		cur->setPosition(&pt);
	}
}
