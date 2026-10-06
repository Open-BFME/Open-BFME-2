// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?SetLastNodePortal@Path@@QAEXH@Z @0x00363B24 (17B).
// Leaf Path tail waypoint setter via tail +0x8 and waypoint +0x20.
// Evidence: Path layout from PathCtor 0x00363DC8 and PathRva00363DF9
// (tail +8 waypoint +20); callers need tail waypoint set; /O1 int-only.

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
	void SetLastNodePortal(int id);

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

void Path::SetLastNodePortal(int id)
{
	PathNode *tail = m_pathTail;
	if (tail == 0) {
		return;
	}
	tail->m_waypointID = id;
}
