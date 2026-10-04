// cl: /O1 /MD /GX /arch:SSE
//
// AoE special-power picker slots (the picker class whose 0x005EE816 and
// 0x005EE8DD live in AISPecialPowerTargetAoE.cpp; retail file unknown).
//
//   0x005D75BE  slot 4 of vftable 0x00C75D9C: the first object the +0x28
//               finder (0x005EEA20) yields for the caster's player; when an
//               alive object allied (flags 4) to the caster of kind 194
//               stands within 500 of it, place the power at the nearest such
//               (0x005EE8DD); otherwise false when 0x005D7558 holds, else the
//               fallback 0x005D7D93
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
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

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00C1A25C, allow 0x002610F2: accept what has any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
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
struct Rva005D75BEMask
{
	Rva005D75BEMask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
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

class Rva005EEA20
{
public:
	Object *rva005EEA20(Player *player, bool a, bool b);	// 0x005EEA20
};

// The AoE special-power target picker (AISPecialPowerTargetAoE.cpp holds
// 0x005EE816 and 0x005EE8DD).
class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *source);	// 0x005EE8DD
	bool rva005D7558(Object *source);			// 0x005D7558
	bool rva005D7D93(Object *source);			// 0x005D7D93
	bool rva005D75BE(Object *source);
private:
	char m_pad00[0x28];
	Rva005EEA20 m_finder;	// +0x28
};

bool Rva005EE816::rva005D75BE(Object *source)
{
	Object *target = m_finder.rva005EEA20(source->getControllingPlayer(), true, true);
	if (target) {
		Rva005D75BEMask mask;
		mask.set(194);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(target->getPosition(), 500.0f, 0,
			Rva0026119DFilter().link(Rva00261409Filter(source->getControllingPlayer(), true, 4)
				.link(&Rva003959FA(*(BfmeFixedStorage0004543D *)&mask))), 1);
		Object *hit = hits.next();
		if (hit)
			return rva005EE8DD(hit->getPosition(), source);
	}
	return rva005D7558(source) ? false : rva005D7D93(source);
}
