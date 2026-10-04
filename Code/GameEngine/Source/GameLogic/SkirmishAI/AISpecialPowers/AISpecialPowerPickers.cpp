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
//   0x005D874A  slot 6 of vftable 0x00C76168: while the caster has a
//               victim (0x0058AE1E), clear the +0x1C target id (0x005EEDB5)
//               and walk the alive objects allied (flags 4) to the caster
//               within the +0x10 radius, taking the first one, then the
//               first whose +0x254 module slot 5 value is below the
//               target's; true when a target is held (0x005EEDE6)
//   0x005D9F97  slot 6 of vftable 0x00C76494: while the caster has a
//               victim and its +0x254 slot-5 value is below 0.7, count the
//               alive objects within the +0x14 radius that pass the
//               relationship filter (flags 6): non-enemies of the caster
//               against enemies whose +0x264 +0x24 count is at most 1 and
//               whose +0x04 +0x11C bit 0x10 is clear; true when the
//               enemies outnumber the rest
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

// The module at Object +0x254: slot 5 returns a float 0x005D874A compares.
class Rva005D874AModule
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual float rva005D874AValue() const;	// slot 5
};

enum Relationship
{
	ENEMIES,
	NEUTRAL,
	ALLIES
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;	// 0x00268D71
};

// What Object +0x264 points at: 0x005D9F97 reads the int at +0x24.
struct Rva005D9F97Count
{
	char m_pad00[0x24];
	int m_24;
};

// What Object +0x04 points at: 0x005D9F97 tests bit 0x10 of +0x11C.
struct Rva005D9F97Info
{
	char m_pad000[0x11C];
	unsigned char m_11C;
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	Relationship getRelationship(const Object *that) const;	// 0x0028D156
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	Rva005D9F97Info *m_04;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x254 - 0x44];
	Rva005D874AModule *m_254;	// +0x254
	AIUpdateInterface *m_258;	// +0x258
	char m_pad25C[0x264 - 0x25C];
	Rva005D9F97Count *m_264;	// +0x264
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

// Retail tests only AL after this call; the row 0x0058AE1E returns the
// victim test as an int.
bool __stdcall Rva0058AE1EHasVictim(Object *obj);	// 0x0058AE1E

// The picker 0x005D874A runs on: +0x10 a radius, +0x1C a target object id
// that 0x005EEDB5 stores (null clears it) and 0x005EEDE6 resolves.
class Rva005EEDB5Picker
{
public:
	void rva005EEDB5(Object *obj);		// 0x005EEDB5
	Object *rva005EEDE6() const;		// 0x005EEDE6
	float getRadius() const { return m_10; }
	bool rva005D874A(Object *source);
private:
	char m_pad00[0x10];
	float m_10;		// +0x10
	char m_pad14[0x08];
	int m_1C;		// +0x1C
};

bool Rva005EEDB5Picker::rva005D874A(Object *source)
{
	if (Rva0058AE1EHasVictim(source)) {
		rva005EEDB5(0);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(source->getPosition(), getRadius(), 0,
			Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 4)), 1);
		Object *obj;
		while ((obj = hits.next()) != 0) {
			if (!rva005EEDE6()) {
				rva005EEDB5(obj);
				continue;
			}
			Rva005D874AModule *mine = obj->m_254;
			Rva005D874AModule *theirs = rva005EEDE6()->m_254;
			if (mine->rva005D874AValue() < theirs->rva005D874AValue()) {
				rva005EEDB5(obj);
				break;
			}
		}
	}
	if (rva005EEDE6())
		return true;
	return false;
}

// The picker 0x005D9F97 runs on (ctor 0x005DA0D0): +0x14 a radius.
class Rva005DA0D0
{
public:
	float getRadius() const { return m_14; }
	bool rva005D9F97(Object *source);
private:
	char m_pad00[0x14];
	float m_14;		// +0x14
};

bool Rva005DA0D0::rva005D9F97(Object *source)
{
	if (source->m_258->getCurrentVictim() && source->m_254->rva005D874AValue() < 0.7f) {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(source->getPosition(), getRadius(), 0,
			Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 6)), 1);
		unsigned int friends = 0;
		unsigned int enemies = 0;
		for (Object *obj = hits.next(); obj; obj = hits.next()) {
			if (source->getRelationship(obj) == ENEMIES) {
				if (obj->m_264->m_24 <= 1) {
					Rva005D9F97Info *info = obj->m_04;
					if (!(info->m_11C & 0x10))
						enemies++;
				}
			} else
				friends++;
		}
		if (enemies > friends)
			return true;
	}
	return false;
}
