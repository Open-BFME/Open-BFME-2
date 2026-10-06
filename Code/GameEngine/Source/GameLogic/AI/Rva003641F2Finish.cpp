// cl: /GX /DNDEBUG /MD
//
// ?rva003641F2@Path@@QBE?AUCoord3D@@XZ @0x003641F2 (124B).
// Path last-valid-waypoint position, by-value Coord3D return (BFME1 donor
// PathGetLastValidWaypointPosition, 0x003FE330 in lotrbfme.exe).  The BFME2
// ABI is the hidden-return form: this+0x10 scan start, this+0x4 head, node
// +0x4 previous, +0xc position, +0x20 waypoint id, TerrainLogic slot +0x8c.
// Retail prologue is push ebp / mov ebp,esp / sub esp,0x10 / and [ebp-4],0:
// an RVO guard for the returned Coord3D, whose destructor is declared but not
// defined (BV11 /GX trial reproduces all 124 bytes exactly).  The zero
// fallback is the POD-shaped local so no trivial-local destructor call is
// emitted; the guard itself is the only zeroed 4-byte frame slot.

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &other) { x = other.x; y = other.y; z = other.z; }
	~Coord3D();
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

class Waypoint;

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34();
	virtual Waypoint *getWaypointByID(int waypointID);
};

extern TerrainLogic *TheTerrainLogic;

class Path
{
public:
	Coord3D rva003641F2(void) const;

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

struct Coord3DPod { float x, y, z; };

Coord3D Path::rva003641F2(void) const
{
	PathNode *sel = m_unknown10;
	Waypoint *waypoint = 0;
	while (sel != 0) {
		int wp = sel->m_waypointID;
		if (wp == 0x7fffffff)
			break;
		waypoint = TheTerrainLogic->getWaypointByID(wp);
		if (waypoint != 0)
			break;
		sel = sel->m_previous;
	}
	const Coord3D *src;
	Coord3DPod zero;
	if (sel != 0)
		src = &sel->m_position;
	else if (m_path != 0)
		src = &m_path->m_position;
	else {
		zero.x = 0.0f;
		zero.y = 0.0f;
		zero.z = 0.0f;
		src = (const Coord3D *)&zero;
	}
	return *src;
}
