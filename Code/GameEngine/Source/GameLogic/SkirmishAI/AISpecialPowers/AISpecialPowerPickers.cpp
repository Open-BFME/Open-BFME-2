// cl: /MD /GX
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
//   0x005D9E12  slot 6 of vftables 0x00C76300, 0x00C76440 and 0x00C76464:
//               0x005D874A's scan over the +0x10 radius after slot 7 resets,
//               keeping only objects of the +0x20 kinds that slot 8 accepts
//               for the caster, and the lowest slot-5 value among them
//   0x005DA37A  slot 6 of vftable 0x00C764EC: with a victim, true below 0.4
//               outright; below 0.7, true when the enemies slot 7 accepts
//               outnumber the non-enemies slot 8 accepts among the alive
//               objects within 50 that pass the relationship filter (flags 6)
//   0x005D8C4C, 0x005D8F0F, 0x005D9721 and 0x005D91D2: corner scans (the
//               square of the picker radius round the source, as in
//               AISPecialPowerTargetAoE.cpp) counting what the filter
//               passes and keeping the corner 0x005EE8DD accepts
//   0x005DA109  slot 6 of vftable 0x00C764BC: a target within 200 with
//               kinds 7 and 49 that no ally of kind 3 or 90 guards
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after the out-of-line ctor, else after allow
// (slot 1).
extern "C" void *memset(void *dst, int value, unsigned int size) throw();

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
	Rva003959FA(const BfmeFixedStorage0004543D &mask) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
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
	Coord3D() {}
	Coord3D(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
	~Coord3D() {}
	void normalize();	// 0x000035B6
	void scale(float s)
	{
		x *= s;
		y *= s;
		z *= s;
	}
	void add(const Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}
	float x;
	float y;
	float z;
};

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva005D75BEMask
{
	Rva005D75BEMask() { memset(this, 0, sizeof(*this)); }
	void clear() { memset(this, 0, sizeof(*this)); }
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
	char m_pad000[0x118];
	unsigned char m_118;	// +0x118 (0x005D91D2 tests bit 0x20)
	char m_pad119[0x11C - 0x119];
	unsigned char m_11C;
};

template <int NUMBITS>
class BitFlags
{
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

enum KindOfType
{
	KINDOF_70 = 0x70
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<116> &mask) const;	// 0x0030ADC7
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	bool isKindOf(KindOfType kind) const;	// 0x0006F039
	Object *rva002931F5(bool flag);	// 0x002931F5
	Relationship getRelationship(const Object *that) const;	// 0x0028D156
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	Rva005D9F97Info *m_04;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x80 - 0x44];
	int m_80;		// +0x80
	char m_pad084[0x254 - 0x84];
	Rva005D874AModule *m_254;	// +0x254
	AIUpdateInterface *m_258;	// +0x258
	char m_pad25C[0x264 - 0x25C];
	Rva005D9F97Count *m_264;	// +0x264
	char m_pad268[0x274 - 0x268];
	int m_274;			// +0x274
};

struct BfmeWideResult
{
	BfmeWideResult &operator=(const BfmeWideResult &other);	// 0x0041D5D0
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
	unsigned rva005D8C4C(Object *source);
	unsigned rva005D8F0F(Object *source);
	unsigned rva005D9721(Object *source);
	unsigned rva005D91D2(Object *source);
private:
	char m_pad00[0x10];
	float m_10;		// +0x10
	float m_14;		// +0x14
	char m_pad18[0x28 - 0x18];
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

// 0x005D8C4C: the corner of the square of the +0x10 radius (200 when unset) round
// the source under which the most alive objects allied to the source's player
// (flags 4) stand that are their own 0x002931F5 or have no +0x274, as long
// as 0x005EE8DD accepts it there; returns that count.
unsigned Rva005EE816::rva005D8C4C(Object *source)
{
	Coord3D origin;
	origin.x = source->getPosition()->x;
	origin.y = source->getPosition()->y;
	origin.z = source->getPosition()->z;
	float radius = m_10;
	if (radius <= 0.0f)
		radius = 200.0f;
	Coord3D corners[4];
	corners[0] = Coord3D(1.0f, 1.0f, 0.0f);
	corners[0].normalize();
	corners[0].scale(radius);
	corners[1] = Coord3D(-corners[0].x, corners[0].y, 0.0f);
	corners[2] = Coord3D(-corners[0].x, -corners[0].y, 0.0f);
	corners[3] = Coord3D(corners[0].x, -corners[0].y, 0.0f);
	unsigned best = 0;
	for (int i = 0; i < 4; ++i) {
		corners[i].add(&origin);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&corners[i], radius, 0,
			Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 4)), 1);
		unsigned count = 0;
		for (Object *obj = hits.next(); obj; obj = hits.next())
			if (obj == obj->rva002931F5(false) || obj->m_274 == 0)
				++count;
		if (count > best && rva005EE8DD(&corners[i], source))
			best = count;
	}
	return best;
}

// 0x005D8F0F: the corner of the square of the +0x10 radius (200 when unset) round
// the source under which the most alive objects neutral to the source's player
// (flags 2) stand that are their own 0x002931F5 or have no +0x274, as long
// as 0x005EE8DD accepts it there; returns that count.
unsigned Rva005EE816::rva005D8F0F(Object *source)
{
	Coord3D origin;
	origin.x = source->getPosition()->x;
	origin.y = source->getPosition()->y;
	origin.z = source->getPosition()->z;
	float radius = m_10;
	if (radius <= 0.0f)
		radius = 200.0f;
	Coord3D corners[4];
	corners[0] = Coord3D(1.0f, 1.0f, 0.0f);
	corners[0].normalize();
	corners[0].scale(radius);
	corners[1] = Coord3D(-corners[0].x, corners[0].y, 0.0f);
	corners[2] = Coord3D(-corners[0].x, -corners[0].y, 0.0f);
	corners[3] = Coord3D(corners[0].x, -corners[0].y, 0.0f);
	unsigned best = 0;
	for (int i = 0; i < 4; ++i) {
		corners[i].add(&origin);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&corners[i], radius, 0,
			Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 2)), 1);
		unsigned count = 0;
		for (Object *obj = hits.next(); obj; obj = hits.next())
			if (obj == obj->rva002931F5(false) || obj->m_274 == 0)
				++count;
		if (count > best && rva005EE8DD(&corners[i], source))
			best = count;
	}
	return best;
}

// 0x005D9721: the corner of the square of the +0x10 radius (200 when unset) round
// the source under which the most alive objects allied to the source's player
// (flags 4) stand that are their own 0x002931F5 or have no +0x274, as long
// as 0x005EE8DD accepts it there; returns that count.
unsigned Rva005EE816::rva005D9721(Object *source)
{
	Coord3D origin;
	origin.x = source->getPosition()->x;
	origin.y = source->getPosition()->y;
	origin.z = source->getPosition()->z;
	float radius = m_10;
	if (radius <= 0.0f)
		radius = 200.0f;
	Coord3D corners[4];
	corners[0] = Coord3D(1.0f, 1.0f, 0.0f);
	corners[0].normalize();
	corners[0].scale(radius);
	corners[1] = Coord3D(-corners[0].x, corners[0].y, 0.0f);
	corners[2] = Coord3D(-corners[0].x, -corners[0].y, 0.0f);
	corners[3] = Coord3D(corners[0].x, -corners[0].y, 0.0f);
	unsigned best = 0;
	for (int i = 0; i < 4; ++i) {
		corners[i].add(&origin);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&corners[i], radius, 0,
			Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 4)), 1);
		unsigned count = 0;
		for (Object *obj = hits.next(); obj; obj = hits.next())
			if (obj == obj->rva002931F5(false) || obj->m_274 == 0)
				++count;
		if (count > best && rva005EE8DD(&corners[i], source))
			best = count;
	}
	return best;
}

// 0x005D91D2: the same corner scan over the +0x14 radius, counting the
// alive objects neutral to the source's player (flags 2) whose +0x04 data has
// bit 0x20 of +0x118 set.
unsigned Rva005EE816::rva005D91D2(Object *source)
{
	const Coord3D *sp = source->getPosition();
	Coord3D origin;
	origin.x = sp->x;
	origin.y = sp->y;
	origin.z = sp->z;
	float radius = m_14;
	Coord3D corners[4];
	corners[0] = Coord3D(1.0f, 1.0f, 0.0f);
	corners[0].normalize();
	corners[0].scale(radius);
	corners[1] = Coord3D(-corners[0].x, corners[0].y, 0.0f);
	corners[2] = Coord3D(-corners[0].x, -corners[0].y, 0.0f);
	corners[3] = Coord3D(corners[0].x, -corners[0].y, 0.0f);
	unsigned best = 0;
	for (int i = 0; i < 4; ++i) {
		corners[i].x += origin.x;
		corners[i].y += origin.y;
		corners[i].z += origin.z;
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&corners[i], radius, 0,
			Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 2)), 1);
		unsigned count = 0;
		for (Object *obj = hits.next(); obj; obj = hits.next())
			if (obj->m_04->m_118 & 0x20)
				++count;
		if (count > best && rva005EE8DD(&corners[i], source))
			best = count;
	}
	return best;
}

// Retail tests only AL after this call; the row 0x0058AE1E returns the
// victim test as an int.
bool __stdcall Rva0058AE1EHasVictim(Object *obj);	// 0x0058AE1E

// The picker 0x005D874A and 0x005D9E12 run on: +0x10 a radius, +0x1C a
// target object id that 0x005EEDB5 stores (null clears it) and 0x005EEDE6
// resolves. Retail's classes derive from Rva005EEDAA (whose dtor 0x005EEDAA
// precedes both accessors): 0x005D874A's vftable belongs to Rva005D8723,
// 0x005D9E12 sits in three sibling vftables; this view flattens them.
class Rva005EEDB5Picker
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void rva005D9E12Reset();				// slot 7
	virtual bool rva005D9E12Accept(Object *source, Object *obj);	// slot 8
	void rva005EEDB5(Object *obj);		// 0x005EEDB5
	Object *rva005EEDE6() const;		// 0x005EEDE6
	float getRadius() const { return m_10; }
	bool rva005D874A(Object *source);
	bool rva005D9E12(Object *source);
	bool rva005DA109(Object *source);
private:
	char m_pad04[0x0C];
	float m_10;		// +0x10
	char m_pad14[0x08];
	int m_1C;		// +0x1C
	BitFlags<116> m_20;	// +0x20
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

// The picker 0x005D9F97 runs on: +0x14 a radius. Retail's class is
// Rva005D9F70 (vftable 0x00C76494, slot 0 its deleting dtor); this view's
// name is address-derived only.
class AISpecialPowerElendil
{
public:
	float getRadius() const { return m_14; }
	// Slot 6 of 0x00C76494, as shouldActivate is in every special power's
	// 7-slot vftable: virtual, with the vptr at +0.
	virtual bool shouldActivate(Object *source);
private:
	char m_pad04[0x10];
	float m_14;		// +0x14
};

bool AISpecialPowerElendil::shouldActivate(Object *source)
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

bool Rva005EEDB5Picker::rva005D9E12(Object *source)
{
	if (Rva0058AE1EHasVictim(source)) {
		rva005EEDB5(0);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(source->getPosition(), getRadius(), 0,
			Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 4)), 1);
		rva005D9E12Reset();
		for (Object *obj = hits.next(); obj; obj = hits.next()) {
			if (!obj->isAnyKindOf(m_20) || !rva005D9E12Accept(source, obj))
				continue;
			if (!rva005EEDE6()) {
				rva005EEDB5(obj);
				continue;
			}
			Rva005D874AModule *mine = obj->m_254;
			Rva005D874AModule *theirs = rva005EEDE6()->m_254;
			if (mine->rva005D874AValue() < theirs->rva005D874AValue())
				rva005EEDB5(obj);
		}
	}
	if (rva005EEDE6())
		return true;
	return false;
}

// 0x005DA109: slot 6 of vftable 0x00C764BC (Rva005DA0E2): unless the
// source is of kind 0x70 or its victim has a +0x80, the first alive object
// within 200 of the source that passes the relationship filter (flags 0xC),
// has kinds 7 and 49 and no +0x80 becomes the target when no alive object
// allied (flags 4) to the source of kind 3 or 90 stands within 200 of it.
bool Rva005EEDB5Picker::rva005DA109(Object *source)
{
	if (!source->isKindOf(KINDOF_70)
		&& (!source->m_258->getCurrentVictim() || source->m_258->getCurrentVictim()->m_80 == 0)) {
		Rva005D75BEMask kinds;
		Rva005D75BEMask none;
		kinds.set(7);
		kinds.set(49);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(source->getPosition(), 200.0f, 0,
			Rva0026119DFilter().link(Rva00261409Filter(source->getControllingPlayer(), true, 0xC)
				.link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&kinds, *(BfmeFixedStorage0004543D *)&none))), 0);
		Object *target = 0;
		for (Object *obj = hits.next(); obj; obj = hits.next()) {
			if (target)
				break;
			if (obj->m_80 == 0)
				target = obj;
		}
		if (target) {
			kinds.clear();
			kinds.set(3);
			kinds.set(90);
			hits = ThePartitionManager->iterateObjectsInRange(target->getPosition(), 200.0f, 0,
				Rva0026119DFilter().link(Rva00261409Filter(source->getControllingPlayer(), true, 4)
					.link(&Rva003959FA(*(BfmeFixedStorage0004543D *)&kinds))), 0);
			if (!hits.next()) {
				rva005EEDB5(target);
				return true;
			}
		}
	}
	return false;
}

// The picker behind vftable 0x00C764EC (slot 0 0x005DA35E, Rva005DA353's
// deleting dtor); slots 7 and 8 are both 0x005CB9FA there.
class AISpecialPowerSelfBuff
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual bool shouldActivate(Object *source);
	virtual bool rva005DA37AEnemy(Object *obj);	// slot 7
	virtual bool rva005DA37AOther(Object *obj);	// slot 8
};

bool AISpecialPowerSelfBuff::shouldActivate(Object *source)
{
	if (source->m_258->getCurrentVictim()) {
		if (source->m_254->rva005D874AValue() < 0.4f)
			return true;
		if (source->m_254->rva005D874AValue() < 0.7f) {
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(source->getPosition(), 50.0f, 0,
				Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 6)), 1);
			unsigned int others = 0;
			unsigned int enemies = 0;
			for (Object *obj = hits.next(); obj; obj = hits.next()) {
				if (source->getRelationship(obj) == ENEMIES) {
					if (rva005DA37AEnemy(obj))
						enemies++;
				} else if (rva005DA37AOther(obj))
					others++;
			}
			if (enemies > others)
				return true;
		}
	}
	return false;
}
