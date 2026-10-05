// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva002E909F@Rva002E909F@@QAE_NPBUCoord3D@@HHHPBVObject@@@Z retail 0x002E909F 203 bytes.
// Pathfinder layer check over INV-scaled cell with Object-gated second lookup via 0x002E6DC4.
// Evidence: 11 unclaimed callers; callees rowed getCell 0x002E6D62 Rva002E6E8AGet 0x002E6E8A Object 0x0028AC62 0x0028AFBB 0x002E6DC4; LINK chain from 0x002E9042; flags from next 0x002E9B31.
extern "C" float INV;

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum PathfindLayerEnum
{
	PF_LAYER_0 = 0
};

class PathfindCell
{
public:
	char _00[4];
	void *m_04;
	char _08[4];
	int m_0C;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
};

int __cdecl Rva002E6E8AGet(int v);

class Object
{
public:
	bool rva0028AC62() const;
	bool rva0028AFBB() const;
	char _00[4];
	void *m_04;
};

struct Rva002E909FInner
{
	char _00[0x56C];
	int m_56C;
	char _570[0x634 - 0x570];
	unsigned char m_634;
};

class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a, void *b);
};

struct Rva002E6DC4P1
{
	unsigned int m_0;
	unsigned char m_4;
	unsigned char m_5;
	char _pad6[2];
	int m_8;
	unsigned char m_C;
};

class Rva002E909F
{
public:
	bool rva002E909F(const Coord3D *pos, int layer, int a3, const Object *obj);
};

bool Rva002E909F::rva002E909F(const Coord3D *pos, int layer, int a3, const Object *obj)
{
	int ix = (int)(pos->x * INV);
	int iy = (int)(pos->y * INV);
	Pathfinder *pf = (Pathfinder *)this;
	PathfindCell *cell = pf->getCell((PathfindLayerEnum)layer, ix, iy);
	if (cell == 0)
		return false;
	if ((unsigned char)Rva002E6E8AGet(layer) != 0)
	{
		if ((((unsigned int)cell->m_0C >> 4) & 0x3F) != (unsigned int)layer)
			return false;
	}
	Rva002E909FInner *inner = (Rva002E909FInner *)obj->m_04;
	int v56c = inner->m_56C;
	unsigned char b634 = inner->m_634;
	bool b1 = obj->rva0028AC62();
	Rva002E6DC4P1 local;
	local.m_0 = (unsigned int)a3;
	local.m_4 = (unsigned char)(b634 == 0);
	bool b2 = obj->rva0028AFBB();
	local.m_5 = (unsigned char)b2;
	local.m_8 = v56c - 1;
	local.m_C = (unsigned char)b1;
	PathfindCell *cell2 = pf->getCell((PathfindLayerEnum)layer, ix, iy);
	return ((Rva002E6DC4 *)this)->rva002E6DC4(&local, cell2);
}
