// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
// Split from Rva005AB309Tactic.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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

// Rva005AB309Tactic.cpp owns the retail key at VA 0x00E06410,
// its startup/atexit functions, and the startup counter/name-list data.
extern AsciiString AIReturnTheRingTactic_IsRunning;

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/Coord3DBase.h"

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

#include "../../Include/Common/BfmeXfer.h"

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


#include "../../Include/Common/TeamBFME2.h"

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
extern Rva002A8F24 *TheSkirmishAIManager;

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
	return TheSkirmishAIManager->rva002A8AB1(owner);
}








void AIReturnTheRingTactic::run()
{
	if (!aiData(m_owner)->rva002C7196(AIReturnTheRingTactic_IsRunning)) {
		Rva002A8AB1Record *record = TheSkirmishAIManager->rva002A8AB1(m_owner);
		if (buildReturnTeam()) {
			record->rva002C717E(AIReturnTheRingTactic_IsRunning, 1);
			moveToFortress();
			m_created = true;
		}
	}
	if (!m_created)
		end(0, 0);
}
