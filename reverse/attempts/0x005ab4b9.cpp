// ?rva005AB4B9@Rva005AB309@@QAE_NXZ
// partial score=0.92 date=2026-10-04
// cl: /O1 /MD /GX /DNDEBUG /arch:SSE /Ireference/shims/bfme2_ascii
//
// The "ReturnTheRing" skirmish-AI tactic (vtable 0x00872284; ctor 0x005AB3BE
// in Rva004ECECDTacticCtors.cpp, dtor 0x005AB309 and ??_G in
// Rva005DCC24Derived.cpp, slot 9 in Rva004ECECDTacticCreate.cpp). Base chain,
// all address-derived: Rva005DCC24 (ctor 0x005DCC0A) over Rva005DC73C over
// the AITactic.cpp object Rva004ECECD. Layout: +0x58 int, +0x5C the ring
// holder's id (found by 0x005AB45B), +0x60 the escort target's id, +0x64
// "escort reached", +0x65 "team created". The owner's TheSkirmishAIManager
// record keeps this unit's AIReturnTheRingTactic_IsRunning key (global
// AsciiString 0x00E06410, built by 0x007B4548, released by 0x007B9630).
//
//   0x005AB6A5  slot 1: not running yet and a ring holder is found
//   0x005AB314  slot 2: clear the key when this tactic set it
//   0x005AB354  slot 5: xfer, version 1
//   0x005AB751  slot 6: create the ring team (0x005AB4B9), set the key and
//               send it off (0x005AB6DC); without a team, stop
//   0x005AB71D  slot 7: while running, on 0x004ED169 stop once the escort
//               was reached, else try to reach it (0x005AB66A)
//   0x005AB5B7  the owner's object of kind +0x120 bit 2 nearest the team
//   0x005AB66A  attack the +0x60 target, or the nearest one when it is gone
//   0x005AB6DC  head for the nearest such object (remembering it in +0x60),
//               or the owner's base
#include "ascii_string.h"

// Retail's initializer calls AsciiString's out-of-line const char * ctor
// (0x0000654A) rather than expanding it, so inline expansion is off here.
#pragma inline_depth(0)
AsciiString AIReturnTheRingTactic_IsRunning("AIReturnTheRingTactic_IsRunning");
#pragma inline_depth()

extern int g_009BA4E8;

// Half of g_009BA4E8, computed at startup (0x007B457D); no retail code reads
// it back.
int g_00E06414 = g_009BA4E8 / 2;

// .data 0x009BC1B8: a NULL-terminated name list {"TARGETLESS", NULL}. The
// ring-team creation here (0x005AB4B9) and two sibling tactics (0x004ED955,
// 0x005ABAF6) push its first entry into a team-name format (0x00C62A08);
// no code reads past it. The NULL-terminated lists that follow it in .data
// (NONE/HOLD/KILL/SPAWN, ...) are separate tables nothing here references.
const char *g_009BC1B8[] = { "TARGETLESS", 0 };

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
};

// BFME2's Xfer: operator== overloads, grouped by cl at the first overload
// slot in reverse declaration order (Rva004E0513Xfer.cpp has the same view).
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *id);

struct Rva005AB309Thing
{
	char m_pad000[0x120];
	unsigned char m_120;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	void rva00298AE4(class Team *team);
	char m_pad000[4];
	Rva005AB309Thing *m_04;		// +0x04
	char m_pad008[0x38 - 8];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;			// +0x74
	char m_pad078[0x438 - 0x78];
	unsigned char m_438;		// +0x438
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Team
{
public:
	void rva0039E5B9(Coord3D *out);
	char m_pad00[0x5d];
	unsigned char m_5d;	// +0x5d
	unsigned char m_5e;	// +0x5e
};

struct Rva003A2FD4Proto
{
	char m_pad00[0x2cc];
	int m_2cc;			// +0x2cc
	char m_pad2D0[0x31c - 0x2cc - 4];
	unsigned char m_31c;	// +0x31c
};

class TeamFactory
{
public:
	Rva003A2FD4Proto *rva003A2FD4(const AsciiString &name, void *ownerData, int a, unsigned int b);
	class Team *rva003A3DBE(Rva003A2FD4Proto *proto, int a);
};
extern TeamFactory *TheTeamFactory;

extern const char g_Rva0107301CEmptyString[];
extern const char *g_00DBC1B8;

struct Rva005059A1Unit;
class Rva00506909Item
{
public:
	void rva004ED6D2(Rva005059A1Unit *team);
};

class Rva004EBF4B
{
public:
	Coord3D rva004EBF4B();
};

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
};

struct Rva005AB309IDs
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

struct Rva005AB309Holder
{
	char m_pad00[8];
	Rva005C4AD1LeaField *m_08;	// +0x08
};

class Player;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva004ECECD
{
public:
	virtual ~Rva004ECECD();
	virtual bool appliesTo(void *request);
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual Rva004ECECD *create();
	Team *rva004ECECD(int index);
	unsigned char rva004ED169();
	void rva004ED2ED(int index, Object *target);
	void rva004ED372(const Coord3D *point);
	void rva004ED748(int a, int b);
};

class Rva005DC73C : public Rva004ECECD
{
public:
	virtual ~Rva005DC73C();
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x24 - 0x11];
	Player *m_owner;		// +0x24
	char m_pad28[4];		// +0x28
	void *m_2c;			// +0x2c
	unsigned int m_30;		// +0x30
	char m_pad34[0x58 - 0x34];
};

class Rva005AB309 : public Rva005DC73C
{
public:
	virtual ~Rva005AB309();
	virtual bool appliesTo(void *request);
	virtual void v2();
	virtual void xfer(Xfer *xfer);
	virtual void v6();
	virtual void v7();
	bool rva005AB45B();
	bool rva005AB4B9();
	Object *rva005AB5B7();
	bool rva005AB66A();
	void rva005AB6DC();
private:
	unsigned int m_58;	// +0x58
	ObjectID m_holder;	// +0x5C
	ObjectID m_target;	// +0x60
	bool m_reached;		// +0x64
	bool m_created;		// +0x65
};

// The owner's TheSkirmishAIManager record; retail loads the owner before
// the record call's own arguments wherever this form is used.
static inline Rva002A8AB1Record *aiData(Player *owner)
{
	return g_00DFEEF8->rva002A8AB1(owner);
}

bool Rva005AB309::appliesTo(void *)
{
	if (!aiData(m_owner)->rva002C7196(AIReturnTheRingTactic_IsRunning)
		&& rva005AB45B())
		return true;
	return false;
}

void Rva005AB309::v2()
{
	if (m_created)
		aiData(m_owner)->rva002C717E(AIReturnTheRingTactic_IsRunning, 0);
}

void Rva005AB309::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	Rva004ECECD::xfer(xfer);
	*xfer == m_58;
	XferObjectID(xfer, &m_holder);
	XferObjectID(xfer, &m_target);
	*xfer == m_reached;
	*xfer == m_created;
}

Object *Rva005AB309::rva005AB5B7()
{
	Rva005AB309Holder *holder = (Rva005AB309Holder *)g_00DFEEF8->rva002A8F24(m_owner);
	Rva005C4AD1LeaField *field = holder->m_08;
	Coord3D center;
	float best = 0.0f;
	Object *nearest = 0;
	rva004ECECD(0)->rva0039E5B9(&center);
	Rva005AB309IDs *ids = (Rva005AB309IDs *)field->get();
	ObjectID *end = ids->m_end;
	for (ObjectID *it = ids->m_begin; it != end; ++it) {
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj && !(obj->m_438 & 1) && (obj->m_04->m_120 & 4)) {
			float dx = obj->getPosition()->x - center.x;
			float dy = obj->getPosition()->y - center.y;
			float dist = dy * dy + dx * dx;
			if (!nearest || best > dist) {
				nearest = obj;
				best = dist;
			}
		}
	}
	return nearest;
}

bool Rva005AB309::rva005AB66A()
{
	Object *target = TheGameLogic->findObjectByID(m_target);
	if (!target || (target->m_438 & 1))
		target = rva005AB5B7();
	if (target) {
		rva004ED2ED(0, target);
		return true;
	}
	return false;
}

void Rva005AB309::rva005AB6DC()
{
	Object *obj = rva005AB5B7();
	if (obj) {
		m_target = obj->getID();
		rva004ED372(obj->getPosition());
	} else {
		Rva004EBF4B *record = (Rva004EBF4B *)g_00DFEEF8->rva002A8AB1(m_owner);
		rva004ED372(&record->rva004EBF4B());
	}
}

void Rva005AB309::v7()
{
	if (m_running && rva004ED169()) {
		if (m_reached)
			rva004ED748(0, 0);
		else if (rva005AB66A())
			m_reached = true;
	}
}

void Rva005AB309::v6()
{
	if (!aiData(m_owner)->rva002C7196(AIReturnTheRingTactic_IsRunning)) {
		Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
		if (rva005AB4B9()) {
			record->rva002C717E(AIReturnTheRingTactic_IsRunning, 1);
			rva005AB6DC();
			m_created = true;
		}
	}
	if (!m_created)
		rva004ED748(0, 0);
}

// ?rva005AB4B9@Rva005AB309@@QAE_NXZ @0x005AB4B9 254B: create ring team from
// TARGETLESS list via TeamFactory proto; evidence rowed findObjectByID
// format releaseBuffer, pins rva003A2FD4 rva003A3DBE rva004ED6D2 rva00298AE4,
// globals TheGameLogic TheTeamFactory g_00DBC1B8 empty g_Rva0107301CEmptyString,
// caller 0x005AB788, offsets +0x24 +0x2c +0x30 +0x58 +0x5c +0x438.
bool Rva005AB309::rva005AB4B9()
{
	Object *obj = TheGameLogic->findObjectByID(m_holder);
	if (obj == 0 || (obj->m_438 & 1))
		return false;
	AsciiString tmp;
	void *sidePtr = m_2c;
	unsigned int tag = m_30;
	const char *side = sidePtr ? (const char *)sidePtr + 8 : g_Rva0107301CEmptyString;
	tmp.format("%s_%s_%u_%u", g_00DBC1B8, side, tag, 0);
	void *ownerData = (char *)m_owner + 0x4c;
	Rva003A2FD4Proto *proto = TheTeamFactory->rva003A2FD4(tmp, ownerData, -1, m_30);
	if (proto == 0)
		return false;
	proto->m_31c = 0;
	proto->m_2cc = 4;
	m_58 = 1;
	Team *team = TheTeamFactory->rva003A3DBE(proto, 0);
	((Rva00506909Item *)this)->rva004ED6D2((Rva005059A1Unit *)team);
	obj->rva00298AE4(team);
	if (team->m_5d == 0) {
		team->m_5e = 1;
		team->m_5d = 1;
	}
	return true;
}
