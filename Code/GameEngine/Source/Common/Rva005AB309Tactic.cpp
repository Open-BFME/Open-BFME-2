// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// The "ReturnTheRing" skirmish-AI tactic (vtable 0x00872284; ctor 0x005AB3BE
// in Rva004ECECDTacticCtors.cpp, dtor 0x005AB309 and ??_G in
// Rva005DCC24Derived.cpp, slot 9 in Rva004ECECDTacticCreate.cpp). Base chain,
// all address-derived: Rva005DCC24 (ctor 0x005DCC0A) over AITacticOffensive over
// the AITactic.cpp object AITactic. Layout: +0x58 int, +0x5C the ring
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

#include "../../../Libraries/Include/Lib/Coord3D.h"

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

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual void initializeTeamTemplate();
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	Team *rva004ECECD(int index);
	unsigned char rva004ED169();
	void teamGarrisonObject(int index, Object *target);
	void rva004ED372(const Coord3D *point);
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x24 - 0x11];
	Player *m_owner;		// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIReturnTheRingTactic : public AITacticOffensive
{
public:
	virtual ~AIReturnTheRingTactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	bool findRingBearer();
	bool buildReturnTeam();
	Object *findClosestFortress();
	bool garrisonFortress();
	void moveToFortress();
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

bool AIReturnTheRingTactic::canRun(void *)
{
	if (!aiData(m_owner)->rva002C7196(AIReturnTheRingTactic_IsRunning)
		&& findRingBearer())
		return true;
	return false;
}

void AIReturnTheRingTactic::cleanUp()
{
	if (m_created)
		aiData(m_owner)->rva002C717E(AIReturnTheRingTactic_IsRunning, 0);
}

void AIReturnTheRingTactic::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	AITactic::xfer(xfer);
	*xfer == m_58;
	XferObjectID(xfer, &m_holder);
	XferObjectID(xfer, &m_target);
	*xfer == m_reached;
	*xfer == m_created;
}

Object *AIReturnTheRingTactic::findClosestFortress()
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

bool AIReturnTheRingTactic::garrisonFortress()
{
	Object *target = TheGameLogic->findObjectByID(m_target);
	if (!target || (target->m_438 & 1))
		target = findClosestFortress();
	if (target) {
		teamGarrisonObject(0, target);
		return true;
	}
	return false;
}

void AIReturnTheRingTactic::moveToFortress()
{
	Object *obj = findClosestFortress();
	if (obj) {
		m_target = obj->getID();
		rva004ED372(obj->getPosition());
	} else {
		Rva004EBF4B *record = (Rva004EBF4B *)g_00DFEEF8->rva002A8AB1(m_owner);
		rva004ED372(&record->rva004EBF4B());
	}
}

void AIReturnTheRingTactic::update()
{
	if (m_running && rva004ED169()) {
		if (m_reached)
			end(0, 0);
		else if (garrisonFortress())
			m_reached = true;
	}
}

void AIReturnTheRingTactic::run()
{
	if (!aiData(m_owner)->rva002C7196(AIReturnTheRingTactic_IsRunning)) {
		Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
		if (buildReturnTeam()) {
			record->rva002C717E(AIReturnTheRingTactic_IsRunning, 1);
			moveToFortress();
			m_created = true;
		}
	}
	if (!m_created)
		end(0, 0);
}
