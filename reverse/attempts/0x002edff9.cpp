// ?rva002EDFF9@Pathfinder@@QAE_NPAVObject@@PAUCoord3D@@@Z
// partial score=0.94 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva002EDFF9@Pathfinder@@QAE_NPAVObject@@PAUCoord3D@@@Z @0x002EDFF9 462B
// Pathfinder reachability sweep called by WallUpgradeUpdate scan 0x004AB70A.
// Splits object extent via rowed Rva002EBCD6Split, resolves cell via pinned
// rva002EBC14, layer via pinned TerrainLogic::getLayerForDestination, rect via
// rowed rva002EBC7F, copies 12B to out, then nested cell walk via rowed
// Pathfinder::getCell plus rowed Object::rva0028AFBB; false on blocked cell.
struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	int x;
	int y;
};

struct Rva002EBC7FPair
{
	int x;
	int y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_ONE = 1
};

struct ObjectInfo
{
	unsigned char m_pad00[0x109];
	unsigned char m_b109; // +0x109
	unsigned char m_pad10A[0x114 - 0x10A];
	int m_flags114; // +0x114 (bytes 0x114..0x117)
};

struct KindHolder
{
	char m_pad00[0x74];
	int m_kind74; // +0x74
};

class Object
{
public:
	bool rva0028AFBB() const;
public:
	void *m_vtbl; // +0
	ObjectInfo *m_info04; // +4
	char m_pad08[0x74 - 8];
	int m_kind74; // +0x74
	char m_pad78[0x274 - 0x78];
	KindHolder *m_kind274; // +0x274
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

struct ListNode
{
	ListNode *m_next; // +0
	char m_pad04[4]; // +4..+7
	Object *m_obj08; // +8
};

struct CellHead
{
	char m_pad00[0x14];
	ListNode *m_list14; // +0x14
	char m_pad18[0x20 - 0x14 - 4];
	ListNode *m_list20; // +0x20
};

class PathfindCell
{
public:
	CellHead *m_head00; // +0
	char m_pad04[8]; // +4..+0xB
	unsigned int m_flags0C; // +0xC
};

class Pathfinder
{
public:
	bool rva002EDFF9(Object *obj, Coord3D *out);
	PathfindCell *getCell(PathfindLayerEnum layer, int cellX, int cellY);
};

void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest);
ICoord2D *__cdecl rva002EBC14(ICoord2D *out, void *obj, const Coord3D *pos);
void *__cdecl rva002EBC7F(void *a1, void *a2, Rva002EBC7FPair *a3, int a4);

bool Pathfinder::rva002EDFF9(Object *obj, Coord3D *out)
{
	int rest;
	int half;
	Rva002EBCD6Split(obj, &half, &rest);
	ICoord2D pair;
	rva002EBC14(&pair, obj, out);
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, out);
	Coord3D tmp;
	Coord3D *p = (Coord3D *)rva002EBC7F(&tmp, obj, (Rva002EBC7FPair *)&pair, layer);
	*out = *p;
	int kind = 0;
	if (obj->m_kind274)
		kind = obj->m_kind274->m_kind74;
	int xStart = pair.x - half;
	int xEnd = pair.x + rest;
	if (xStart >= xEnd)
		return true;
	int yStart = pair.y - half;
	int yEnd = pair.y + rest;
	int y;
	for (; xStart < xEnd; ++xStart)
	{
		y = yStart;
		for (; y < yEnd; ++y)
		{
			PathfindCell *cell = getCell(layer, xStart, y);
			if (!cell)
				return false;
			if ((cell->m_flags0C & 0xF) == 5)
				return false;
			unsigned int f = cell->m_flags0C;
			unsigned int shifted = f >> 0x12;
			if ((shifted & 1) == 1)
			{
				if (obj->rva0028AFBB())
					return false;
			}
			if ((cell->m_flags0C & 0xF) == 4)
				return false;
			if ((cell->m_flags0C & 0xF) == 5)
				return false;
			if ((cell->m_flags0C & 0xF) == 6)
				return false;
			CellHead *head = cell->m_head00;
			ListNode *l1 = head ? head->m_list20 : 0;
			for (ListNode *n = l1; n; n = n->m_next)
				{
					Object *other = n->m_obj08;
					if (other == obj)
						continue;
					if (other->m_kind74 == kind)
						continue;
					int oflags = obj->m_info04->m_flags114;
					if ((oflags & 0x2000) == 0)
					{
						unsigned char b = ((unsigned char *)&other->m_info04->m_flags114)[1];
						if ((b & 0x20) != 0)
							continue;
					}
					if ((oflags & 0x20000000) == 0)
						return false;
					if ((other->m_info04->m_b109 & 1) == 0)
						return false;
				}
			ListNode *l2 = head ? head->m_list14 : 0;
			for (ListNode *n = l2; n; n = n->m_next)
			{
				Object *other = n->m_obj08;
				if (other == obj)
					continue;
				ObjectInfo *oi = other->m_info04;
				if ((oi->m_flags114 & 0x2000) != 0)
				{
					if ((obj->m_info04->m_flags114 & 0x2000) == 0)
						continue;
				}
				if ((oi->m_b109 & 1) == 0)
					return false;
				unsigned char b = ((unsigned char *)&obj->m_info04->m_flags114)[3];
				if ((b & 0x20) == 0)
					return false;
			}
		}
	}
	return true;
}
