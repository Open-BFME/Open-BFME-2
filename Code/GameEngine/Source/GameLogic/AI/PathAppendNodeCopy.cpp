// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 PathNode position/layer constructor, transferred from the exact
// BFME1 reconstruction
// (Code/GameEngine/Source/GameLogic/AI/PathAppendNodeCopy.cpp).
// Retail BFME2 keeps the same layout: links at +0x0/+0x4/+0x8, position at
// +0xC, layer at +0x18, optimize flag at +0x1C, waypoint ID at +0x20.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D
{
	Coord3D &operator=(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Real x;
	Real y;
	Real z;
};

class PathNode
{
public:
	PathNode(const Coord3D *position, PathfindLayerEnum layer);

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_waypointID;
};

// ??0PathNode@@QAE@PBUCoord3D@@W4PathfindLayerEnum@@@Z
PathNode::PathNode(const Coord3D *position, PathfindLayerEnum layer)
{
	m_next = 0;
	m_previous = 0;
	m_nextOptimized = 0;
	m_position = *position;
	m_layer = layer;
	m_canOptimize = false;
	m_waypointID = 0x7fffffff;
}
