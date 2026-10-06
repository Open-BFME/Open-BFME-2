// cl: /DNDEBUG /MD
//
// ?PeekPastClimbPortal@Path@@QAEPAUCoord3D@@PAU2@@Z @0x00363DF9 (199B).
// Unlock Path position-out via head +0x4 and selected node +0x10 with
// optimized links +0x8 and waypoint guard +0x20. Evidence: neighbours
// PathCtor 0x00363DC8 and PathRva003649B1 prove Path/PathNode layout and
// /O1 /arch:SSE flags; EAX holds out at every retail exit so the body
// returns Coord3D*; single shared out tail needs single-exit tmp form.

struct Coord3D
{
	float x;
	float y;
	float z;
};

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
