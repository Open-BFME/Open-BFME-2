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
//   0x0043912F  whether an object other than this one, alive, passing
//               0x002614DF and 0x0026118B, of the TheGlobalData +0xEB4
//               object filter for the object's player and relationship 4
//               (the third argument's +0x9C bit 1) or 1 to it lies within its
//               template radius times the third argument's +0x14 scale of the
//               position (searched within this +0x10 times that scale, 3D
//               distance); its ID goes to the fourth argument when given

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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C17F08, allow 0x0026118B: no members of its own.
class Rva0026118BFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

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

class ThingTemplate
{
public:
	char m_pad00[0x10];
	float m_10;			// +0x10 the radius
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_74;			// +0x74 the ID
	char m_pad078[0x284 - 0x78];
	unsigned m_284[32];		// +0x284
	char m_pad304[0x438 - 0x304];
	unsigned char m_438;		// +0x438
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
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
	char m_pad01[0x14 - 0x01];
	float m_14;			// +0x14 the scale
	char m_pad18[0x1C - 0x18];
	Rva00406F9C m_1C;		// +0x1C
	unsigned char m_9C;		// +0x9C bits 0 and 1
};


class GlobalData
{
public:
	char m_pad000[0xEB4];
	int m_EB4;		// +0xEB4 what the 0x002614EC filter compares
};
extern GlobalData *TheGlobalData;

class Rva004389AE
{
public:
	bool rva004388E3(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl);
	bool rva004389AE(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl);
	bool rva0043912F(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl, ObjectID *out);
private:
	char m_pad00[0x10];
	float m_10;		// +0x10 the scale
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

bool Rva004389AE::rva0043912F(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl, ObjectID *out)
{
	int flags = (tmpl->m_9C & 2) ? 4 : 1;
	Rva002614DFFilter notThis(obj);
	Rva0026119DFilter alive;
	Rva0026118BFilter third;
	Rva002611BFFilter notSelf(obj);
	Rva002614ECFilter same(&TheGlobalData->m_EB4, obj->getControllingPlayer(), true);
	Rva00260EB1Filter relationship(obj, flags, true);
	notThis.link(&alive);
	notThis.link(&third);
	notThis.link(&notSelf);
	notThis.link(&same);
	notThis.link(&relationship);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos,
		m_10 * tmpl->m_14, 2, &notThis, 0);
	Object *other;
	while ((other = hits.next()) != 0) {
		float r = other->m_template->m_10 * tmpl->m_14;
		float dx = pos->x - other->m_pos.x;
		float dy = pos->y - other->m_pos.y;
		float dz = pos->z - other->m_pos.z;
		if (dx * dx + dy * dy + dz * dz < r * r) {
			if (out)
				*out = other->m_74;
			return true;
		}
	}
	return false;
}
