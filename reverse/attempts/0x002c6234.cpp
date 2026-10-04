// ??0Rva002C6234@@QAE@PBUCoord3D@@MPAVPlayer@@@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD /GX /arch:SSE
#include <string.h>

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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags (ZH's PartitionFilterRelationship
// analogue), +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva002C6234Mask
{
	Rva002C6234Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

struct ThingTemplate
{
	char m_pad000[0x51C];
	float m_51C;		// +0x51C
};

class Object
{
public:
	bool isAnyKindOf(const Rva002C6234Mask &mask) const;	// 0x0030ADC7
	char m_pad000[4];
	const ThingTemplate *m_template;	// +0x04
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
};
extern PartitionManager *ThePartitionManager;

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
	char m_pad000[0x40];
	unsigned int m_frame;	// +0x40
};
extern GameLogic *TheGameLogic;

extern unsigned int g_Va00DFEFC8;

class Rva002C6234
{
public:
	Rva002C6234(const Coord3D *pos, float radius, Player *player);
private:
	unsigned int m_id;	// +0x00
	Coord3D m_pos;		// +0x04
	int m_10;		// +0x10
	float m_radius;		// +0x14
	float m_total;		// +0x18
	unsigned int m_frame;	// +0x1C
};

Rva002C6234::Rva002C6234(const Coord3D *pos, float radius, Player *player)
{
	m_id = ++g_Va00DFEFC8;
	m_pos.x = pos->x;
	m_pos.y = pos->y;
	m_pos.z = pos->z;
	m_radius = radius;
	m_10 = 0;
	m_total = 0.0f;
	m_frame = TheGameLogic->getFrame();
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos, radius, 0,
		Rva0026119DFilter().link(&Rva00261409Filter(player, true, 4)), 0);
	Rva002C6234Mask mask;
	mask.set(3);
	mask.set(90);
	Object *obj;
	while ((obj = hits.next()) != 0) {
		if (obj->isAnyKindOf(mask))
			m_total += obj->m_template->m_51C;
	}
}

