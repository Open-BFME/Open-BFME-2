// cl: /O1 /MD /GX /arch:SSE
//
//   0x004388E3  true when the third argument's +0x1C mask
//               meets the object's +0x284 mask, an alive object of kind 94
//               lies within 50 of the position (the partition filter chain
//               AIStructureCreepTactic.cpp documents), or TheTerrainLogic's
//               0x0027F108 finds something within 50 of it
//   0x004389AE  the same test, taken only when the third argument's +0x9C or +0x00
//               bit 0 is set (both REL32 in 0x004D990E with ECX the
//               TheGameLogic +0x178 member)

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);	// 0x00406F9C
private:
	unsigned m_data[32];
};

class Object
{
public:
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	char m_pad000[0x284];
	unsigned m_284[32];		// +0x284
	char m_pad304[0x438 - 0x304];
	unsigned char m_438;		// +0x438
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

class TerrainLogic
{
public:
	void *rva0027F108(const Coord3D *pos, float radius, bool flag, int unused);	// 0x0027F108
};
extern TerrainLogic *TheTerrainLogic;

struct Rva004388E3Template
{
	unsigned char m_00;		// +0x00 bit 0
	char m_pad01[0x1C - 0x01];
	Rva00406F9C m_1C;		// +0x1C
	unsigned char m_9C;		// +0x9C bit 0
};

class Rva004389AE
{
public:
	bool rva004388E3(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl);
	bool rva004389AE(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl);
};

bool Rva004389AE::rva004388E3(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl)
{
	if (tmpl->m_1C.rva00406F9C(obj->m_284))
		return true;

	Object *other = ThePartitionManager->getClosestObject(pos, 50.0f, 0,
		Rva0026119DFilter().link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 94),
			*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)));
	if (other && !other->isEffectivelyDead())
		return true;

	return TheTerrainLogic->rva0027F108(pos, 50.0f, true, 0) ? true : false;
}

bool Rva004389AE::rva004389AE(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl)
{
	if (((tmpl->m_9C & 1) || (tmpl->m_00 & 1)) && rva004388E3(obj, pos, tmpl))
		return true;
	return false;
}
