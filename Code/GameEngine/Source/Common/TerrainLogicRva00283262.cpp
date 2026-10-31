// cl: /ICode/Libraries/Include /DNDEBUG /MD /EHs
// ?rva00283262@TerrainLogic@@QAEXPBUCoord3D@@M@Z @0x00283262 221B
// Evidence: same-this TerrainLogic rva00282CFB pin plus ThePartitionManager iterateObjectsInRange pin 0x00625610 with float radius via fld fstp plus BitSet 0x00045411 and holder 0x0004584D plus GameLogic destroyObject
#include "Lib/Coord3D.h"

struct BfmePointFC
{
	float x, y;
};

class BfmeTaintManager
{
public:
	void bfmeApplyCircleWorld(const BfmePointFC *point, float radius,
		int amount, bool absolute, int mode);
};

#include "GameLogicObjectLookupView.h"
class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos;
};

extern GameLogic *TheGameLogic;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	Rva000421C8 *link(Rva000421C8 *next); // 0x00625790
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next; // +0x04
};

struct BfmeWideResult
{
	~BfmeWideResult();
	Object *next();	// 0x00045623
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int a, Rva000421C8 *filter, int b);
};
extern PartitionManager *ThePartitionManager;
extern BfmeTaintManager *TheTaintManager;

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

struct Rva00045411BitSet
{
public:
	Rva00045411BitSet(int unused, int bit) throw(); // 0x00045411
	unsigned int m_bits[7]; // +0x00
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
	void rva00283262(const Coord3D *a, float radius);
};

// 0x0027F1DD, rowed as BfmeThingCME::rva0027F1DD (Rva0027F1DDRetire.cpp).
class BfmeThingCME
{
public:
	void rva0027F1DD(Coord3D *position, float radius);
};

void TerrainLogic::rva00283262(const Coord3D *a, float radius)
{
	if (a == 0)
		return;
	if (TheTaintManager == 0)
		return;
	if (ThePartitionManager == 0)
		return;
	if (TheGameLogic == 0)
		return;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(a, radius, 0,
		&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x98), *reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE)), 1);
	for (Object *other = hits.next(); other != 0; other = hits.next()) {
		rva00282CFB(&other->m_pos, radius, (unsigned int)-1);
		TheGameLogic->destroyObject(other);
	}
	rva00282CFB(a, radius, (unsigned int)-1);
}

// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f clean source lead:
// game/GameEngine/Source/GameLogic/Map/TerrainArea001ACCC0.cpp,
// clearOne001AC3D0. Target facts: RET 12; mode is the final word, kind bit
// is 175, the two masks are 28 bytes, and the visual callback is slot 23.
// The native callback constructs its 12-byte value directly on the outgoing
// stack. Its original parameter type and method spelling remain unresolved.
struct TerrainPoint00282CFB
{
	float x, y, z;
	TerrainPoint00282CFB(float a, float b, float c) : x(a), y(b), z(c) {}
	TerrainPoint00282CFB(const TerrainPoint00282CFB &p) : x(p.x), y(p.y), z(p.z) {}
};

class AsciiString;
class ChunkInputStream;
class Rva002834C4;
class G00DFF080Obj
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4(const AsciiString &filename, ChunkInputStream *pStrm, Rva002834C4 *a,
		Rva002834C4 *b, Rva002834C4 *c); // +0x10
	virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(void *p); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
	virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
	virtual void rva00282CFBNotify(TerrainPoint00282CFB point, float radius);
};

extern G00DFF080Obj *TheTerrainVisual;

void TerrainLogic::rva00282CFB(const Coord3D *pos, float radius, unsigned int mode)
{
	if (pos == 0 || TheTaintManager == 0 || ThePartitionManager == 0 || TheGameLogic == 0)
		return;
	((BfmeTaintManager *)TheTaintManager)->bfmeApplyCircleWorld(
		(const BfmePointFC *)pos, radius, 128, true, mode);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos, radius, 0,
		&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 175),
			*reinterpret_cast<const BfmeFixedStorage0004543D *>(&KINDOFMASK_NONE)), 1);
	for (Object *other = hits.next(); other != 0; other = hits.next())
		TheGameLogic->destroyObject(other);
	((BfmeThingCME *)this)->rva0027F1DD((Coord3D *)pos, radius);
	if (TheTerrainVisual)
		TheTerrainVisual->rva00282CFBNotify(TerrainPoint00282CFB(pos->x, pos->y, pos->z), radius);
}
