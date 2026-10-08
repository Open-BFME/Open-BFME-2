// cl: /DNDEBUG /MD
//
// ?PeekPastClimbPortal@Path@@QAEPAUCoord3D@@PAU2@@Z @0x00363DF9 (199B).
// Unlock Path position-out via head +0x4 and selected node +0x10 with
// optimized links +0x8 and waypoint guard +0x20. Evidence: neighbours
// PathCtor 0x00363DC8 and PathRva003649B1 prove Path/PathNode layout and
// /O1 /arch:SSE flags; EAX holds out at every retail exit so the body
// returns Coord3D*; single shared out tail needs single-exit tmp form.

#include <math.h>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

class PathNode
{
public:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	int m_layer;
	bool m_canOptimize;
	int m_waypointID;
};

class Path
{
public:
	Coord3D *PeekPastClimbPortal(Coord3D *out);
	float computeFlightDistToGoal(const Coord3D *currentPosition, Coord3D &goalPosition);

private:
	void *m_unknown00;
	PathNode *m_path;
	PathNode *m_pathTail;
	bool m_isOptimized;
	bool m_unknown0D;
	PathNode *m_unknown10;
	float m_unknown14;
	float m_unknown18;
	float m_unknown1C;
	float m_unknown20;
	int m_unknown24;
};

Coord3D *Path::PeekPastClimbPortal(Coord3D *out)
{
	PathNode *head = m_path;
	if (head == 0) {
		out->x = 0.0f;
		out->y = 0.0f;
		out->z = 0.0f;
		return out;
	}
	PathNode *sel = m_unknown10;
	if (sel == 0) {
		out->x = head->m_position.x;
		out->y = head->m_position.y;
		out->z = head->m_position.z;
		return out;
	}
	PathNode *first = sel->m_nextOptimized;
	if (first == 0) {
		out->x = sel->m_position.x;
		out->y = sel->m_position.y;
		out->z = sel->m_position.z;
		return out;
	}
	Coord3D tmp;
	tmp.x = first->m_position.x;
	tmp.y = first->m_position.y;
	tmp.z = first->m_position.z;
	PathNode *next = first->m_nextOptimized;
	if (next != 0) {
		tmp = next->m_position;
		PathNode *third = next->m_nextOptimized;
		if (third != 0 && third->m_waypointID != 0x7fffffff) {
			tmp = third->m_position;
		}
	}
	out->x = tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
	return out;
}

// ?computeFlightDistToGoal@Path@@QAEMPBUCoord3D@@AAU2@@Z @0x00363EC0 (228B).
// Reference: Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe,
// game/GameEngine/Source/GameLogic/AI/PathComputeFlightDistToGoal.cpp;
// original purpose and const/reference signature from GeneralsMD AIPathfind.cpp.
// Target evidence: complete 228B boundary; head +4, optimized link +8 and
// Coord3D position +0xC; only call is real Coord2D::normalize at 0x0000378A.
// AIUpdateInterface's aircraft-distance branch at RVA 0x0026435E calls this
// body with the object's position and goal output (WB 0x00E4C2EA -> 0x00F1D960).
// WB's body is unnamed: the readable method name is carried from the reference.
float Path::computeFlightDistToGoal(const Coord3D *currentPosition,
	Coord3D &goalPosition)
{
	if (m_path == 0)
	{
		goalPosition.x = 0.0f;
		goalPosition.y = 0.0f;
		goalPosition.z = 0.0f;
		return 0.0f;
	}

	PathNode *curNode = m_path;
	PathNode *nextNode = curNode->m_nextOptimized;
	goalPosition = curNode->m_position;
	float distance = 0.0f;
	bool useNext = true;
	while (nextNode)
	{
		if (useNext)
			goalPosition = nextNode->m_position;

		Coord2D posToGoalVector;
		posToGoalVector.x = nextNode->m_position.x - currentPosition->x;
		posToGoalVector.y = nextNode->m_position.y - currentPosition->y;

		Coord2D pathVector;
		pathVector.x = nextNode->m_position.x - curNode->m_position.x;
		pathVector.y = nextNode->m_position.y - curNode->m_position.y;
		pathVector.normalize();

		float dotProduct = posToGoalVector.x * pathVector.x +
			posToGoalVector.y * pathVector.y;
		if (dotProduct >= 0.0f)
		{
			distance += dotProduct;
			useNext = false;
		}
		curNode = nextNode;
		nextNode = curNode->m_nextOptimized;
	}
	return distance;
}

// The authentic inline helper definitions must both be visible: with only
// normalize declared, cl schedules the current-position reload after node.x.
// Both emitted COMDATs independently equal their existing complete retail
// providers (71B at 0x0000378A and 53B at 0x00003755); no new alias or pin.
// ?normalize@Coord2D@@QAEXXZ present-unmatched
inline void Coord2D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        x /= len;
        y /= len;
    }
}

// ?length@Coord2D@@QBEMXZ present-unmatched
inline float Coord2D::length() const
{
    return (float)sqrt(x * x + y * y);
}
