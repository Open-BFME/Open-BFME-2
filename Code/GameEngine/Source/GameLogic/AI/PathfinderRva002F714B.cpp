// cl: /DNDEBUG /MD
//
// ?rva002F714B@Pathfinder@@QAEHPAVObject@@PBUCoord3D@@1@Z @0x002F714B 91B.
// Pathfinder helper that picks a layer then runs the Coord wrapper 0x002F6AE3.
// Evidence: calls rowed Object::rva0028B511 plus pinned
// TerrainLogic::getLayerForDestination plus rowed Rva002E7542 0x002E7542 plus
// rowed Rva002F6AE3 0x002F6AE3; caller pair 0x0049F119 0x004A0B79; chain from
// 0x002F6AE3; neighbours 0x002F6D22 and 0x002F95B7 share flags.

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_ONE = 1
};

struct Rva002F3F7DInfo
{
	char m_pad[4];
};

class Rva0006E009DwordField
{
public:
	int get() const;
};

class Object
{
public:
	int rva0028B511() const;
	char m_pad[0x258];
	Rva0006E009DwordField *m_ai;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Rva002E7542
{
public:
	void *rva002E7542(int a1, const Coord3D *a2, int a3);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
};

class Pathfinder
{
public:
	int rva002F714B(Object *obj, const Coord3D *a, const Coord3D *b);
	int rva002F6AE3(const Coord3D *startPos, const Coord3D *destPos, PathfindLayerEnum layer, Rva002F3F7DInfo *info);
};

int Pathfinder::rva002F714B(Object *obj, const Coord3D *a, const Coord3D *b)
{
	int layer = obj->rva0028B511();
	if (layer == 1)
		layer = TheTerrainLogic->getLayerForDestination(obj, b);
	int ignored = obj->m_ai->get();
	Rva002E7542 tmp;
	return rva002F6AE3(a, b, (PathfindLayerEnum)layer, (Rva002F3F7DInfo *)tmp.rva002E7542((int)obj, b, ignored));
}
