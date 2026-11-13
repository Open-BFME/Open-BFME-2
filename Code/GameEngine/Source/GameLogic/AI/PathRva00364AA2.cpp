// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /ICode/Libraries/Include/Lib

// Path corner rounding at a middle node (WB twin 0x00F221B0, pathfinder_path.cpp):
// offsets both legs by the radius, intersects them and appends the arc points.
// WWMath's lineseg.h, the angle helper, appendNode and the PathNode ctor stay visible.

class Rva00065964ObjectPool
{
public:
	void *rva002635C2() throw();
};

// g_pathNodePool: defined in PathDtor.cpp (VA 0xe01e94).
extern Rva00065964ObjectPool g_pathNodePool;

#include <new.h>
#include "vector3.h"
#include "Coord2D.h"
#include "vector2.h"
#define COORD3D_VIEW_DTOR
#define COORD3D_VIEW_INLINE
#include "Coord3DCtorView.h"

#include "lineseg.h"

#include "../../../Include/Common/Rva00363B4BVector.h"
float ACos(float);
inline __declspec(noinline) float rva00363B4BAngle(const Rva00363B4BVector *a, const Rva00363B4BVector *b)
{
    float dot = a->z * b->z + a->y * b->y + a->x * b->x;
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    if (dot >= 0.99f) return 0.0f;
    return ACos(dot);
}

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

#include "../../../Include/GameLogic/PathNode.h"

// Copies the position member-wise through an inline call, as the home's Coord3D operator= does.
inline __declspec(noinline) PathNode::PathNode(const Coord3D *position, PathfindLayerEnum layer) throw()
{
	m_next = 0;
	m_prev = 0;
	m_nextOpti = 0;
	m_pos.set(position);
	m_layer = layer;
	m_canOptimize = false;
	m_portalID = 0x7fffffff;
}

class Path
{
	void *m_unknown00;
	PathNode *m_head04;
	PathNode *m_pathTail;
	bool m_isOptimized;

public:

	inline __declspec(noinline) void appendNode(const Coord3D *pos, PathfindLayerEnum layer, int waypointID)
	{
		if (m_isOptimized && m_pathTail)
		{
			if (pos->x == m_pathTail->m_pos.x && pos->y == m_pathTail->m_pos.y)
				return;
		}
		void *mem = g_pathNodePool.rva002635C2();
		PathNode *node = mem ? new (mem) PathNode(pos, layer) : 0;
		node->m_portalID = waypointID;
		PathNode *tail = m_pathTail;
		if (tail)
		{
			tail->m_next = node;
			node->m_prev = tail;
		}
		if (m_isOptimized && m_pathTail)
			m_pathTail->m_nextOpti = node;
		m_pathTail = node;
		if (m_head04 == 0)
			m_head04 = node;
	}
	void rva003649B1(const PathNode *node);
	int rva003641AE(float angle, float radius);
	void rva00364AA2(PathNode *prev, PathNode *cur, PathNode *next, float radius);
};

// Normal copies expire after the angle query; tail locals use a sibling scope.
void Path::rva00364AA2(PathNode *prev, PathNode *cur, PathNode *next, float radius)
{
	Coord3D prevPos(*prev->getPosition());
	Coord3D curPos(*cur->getPosition());
	Coord3D nextPos(*next->getPosition());
	prevPos.z=curPos.z;
	nextPos.z=curPos.z;
	LineSegClass seg1(Vector3(prevPos.x, prevPos.y, 0), Vector3(curPos.x, curPos.y, 0));
	LineSegClass seg2(Vector3(curPos.x, curPos.y, 0), Vector3(nextPos.x, nextPos.y, 0));
	float minLen = seg1.Get_Length();
	if (minLen > seg2.Get_Length())
		minLen = seg2.Get_Length();
	if (radius > minLen * 0.75f)
		radius = minLen * 0.75f;
	Vector2 a, b, c, d;
	bool turnLeft;
	if (Vector3::Cross_Product_Z(seg1.Get_Dir(), seg2.Get_Dir()) < 0.0f) {
		a.Set(prevPos.x, prevPos.y);
		b.Set(curPos.x, curPos.y);
		c = b;
		d.Set(nextPos.x, nextPos.y);
		turnLeft = true;
	} else {
		d.Set(prevPos.x, prevPos.y);
		c.Set(curPos.x, curPos.y);
		b = c;
		a.Set(nextPos.x, nextPos.y);
		turnLeft = false;
		seg1.Set(Vector3(a.X, a.Y, 0), Vector3(b.X, b.Y, 0));
		seg2.Set(Vector3(c.X, c.Y, 0), Vector3(d.X, d.Y, 0));
	}
	float angle = rva00363B4BAngle((const Rva00363B4BVector *)&seg1.Get_Dir(), (const Rva00363B4BVector *)&seg2.Get_Dir());
	if (angle < 0.7225663304328919)
		radius *= 1.75f;
	if (cur->m_portalID != 0x7fffffff || angle > 1.7278761f) {
		rva003649B1(cur);
		return;
	}
	Vector3 v1 = radius * seg1.Get_Dir();
	Vector3 v2 = radius * seg2.Get_Dir();
	v1.Rotate_Z(-1.5707963705062866f);
	v2.Rotate_Z(-1.5707963705062866f);
	Vector3 p0 = Vector3(a.X, a.Y, 0) + v1;
	Vector3 p1 = Vector3(b.X, b.Y, 0) + v1;
	LineSegClass off1(p0, p1);
	p0 = Vector3(c.X, c.Y, 0) + v2;
	p1 = Vector3(d.X, d.Y, 0) + v2;
	LineSegClass off2(p0, p1);
	Vector3 center;
	Vector3 other;
	float fraction;
	float arc;
	{
		Vector3 n1 = v1;
		Vector3 n2 = v2;
		n1.Normalize();
		n2.Normalize();
		arc = rva00363B4BAngle((const Rva00363B4BVector *)&n1, (const Rva00363B4BVector *)&n2);
	}
	{
		int count = rva003641AE(arc, radius);
		if (count < 2) {
			rva003649B1(cur);
			return;
		}
		float step = arc / count;
		if (!off1.Find_Intersection(off2, &center, &fraction, &other, &fraction))
			return;
		Coord3D pt;
		if (turnLeft) {
			Vector3 q = center - v1;
			pt.set(q.X, q.Y, curPos.z);
			appendNode(&pt, cur->getLayer(), 0x7fffffff);
			v1 *= -1.0f;
			for (int i = 1; i < count; ++i) {
				q = center + v1;
				v1.Rotate_Z(-step);
				pt.set(q.X, q.Y, curPos.z);
				appendNode(&pt, cur->getLayer(), 0x7fffffff);
			}
			Vector3 t = center - v2;
			pt.set(t.X, t.Y, curPos.z);
			appendNode(&pt, cur->getLayer(), 0x7fffffff);
			cur->setPosition(&pt);
		} else {
			Vector3 q = center - v2;
			pt.set(q.X, q.Y, curPos.z);
			appendNode(&pt, cur->getLayer(), 0x7fffffff);
			v2 *= -1.0f;
			for (int i = 1; i < count; ++i) {
				v2.Rotate_Z(step);
				q = center + v2;
				pt.set(q.X, q.Y, curPos.z);
				appendNode(&pt, cur->getLayer(), 0x7fffffff);
			}
			Vector3 t = center - v1;
			pt.set(t.X, t.Y, curPos.z);
			appendNode(&pt, cur->getLayer(), 0x7fffffff);
			cur->setPosition(&pt);
		}
	}
}
