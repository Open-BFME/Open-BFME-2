// cl: /DNDEBUG /MD /EHs
// ?rva00283262@TerrainLogic@@QAEXPBUCoord3D@@M@Z @0x00283262 221B
// Evidence: same-this TerrainLogic rva00282CFB pin plus ThePartitionManager iterateObjectsInRange pin 0x00625610 with float radius via fld fstp plus BitSet 0x00045411 and holder 0x0004584D plus GameLogic destroyObject
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos38;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};
extern GameLogic *TheGameLogic;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);
	Rva000421C8 *m_next;
};
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct BfmeWideResult
{
	~BfmeWideResult();
	void *m_value;
};

class BfmeThingEOF
{
public:
	void *bfmeGoEOF();
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int a, Rva000421C8 *filter, int b);
};
extern PartitionManager *ThePartitionManager;
extern void *g_Va00DFE750;

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();
	unsigned m_bits[7];
};

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

class TerrainLogic
{
public:
	void rva00282CFB(const Coord3D *pos, float f, unsigned int x);
	void rva00283262(const Coord3D *a, float b);
};

void TerrainLogic::rva00283262(const Coord3D *a, float b)
{
	if (a == 0)
		return;
	if (g_Va00DFE750 == 0)
		return;
	if (ThePartitionManager == 0)
		return;
	if (TheGameLogic == 0)
		return;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(a, b, 0,
		&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x98), g_defaultStorage009FEFA4), 1);
	for (Object *other = (Object *)((BfmeThingEOF *)&hits)->bfmeGoEOF(); other != 0; other = (Object *)((BfmeThingEOF *)&hits)->bfmeGoEOF()) {
		rva00282CFB(&other->m_pos38, b, (unsigned int)-1);
		TheGameLogic->destroyObject(other);
	}
	rva00282CFB(a, b, (unsigned int)-1);
}
