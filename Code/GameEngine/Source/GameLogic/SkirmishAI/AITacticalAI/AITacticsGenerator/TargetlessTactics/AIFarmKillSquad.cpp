// cl: /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// The "FarmKillSquad" skirmish-AI tactic (vtable 0x00872474; ctor 0x005ACF38
// in Rva004ECECDTacticCtors.cpp, dtor 0x005ACCE4 and ??_G, slot 9 0x005ACFAB
// in Rva004ECECDTacticCreate.cpp). Base chain, all address-derived:
// Rva005DCC24 over AITacticOffensive over the AITactic.cpp object AITactic.
// Layout: +0x58 and +0x5C object ids, +0x60 "farm" (the ctor's one-in-five
// roll). The owner's TheSkirmishAIManager record keeps
// AIFarmKillSquad_IsRunning and AIFarmKillSquad_FrameNextRun.
//
//   0x005ACCEF  slot 1 canRun (the slot the sibling tactics' rowed canRun bodies
//               fill): farming or the record's +0x16C positive; not running,
//               the next run is due and 0x002C6ACB answers
//   0x005ACD51  slot 2: clear the running key and schedule the next run a
//               random 30..120 seconds on
//   0x005ACEC8  slot 5: xfer, version 1: the AITactic's, then both ids
//   0x005ACDD2  the distance between two points
//   0x005ACE15  (not here yet) the distance from a point to the line through two others
//   0x005AD152  the player's first tracked object whose template has +0x120
//               bit 2 (the base building the squad farms around)
//   0x005AD5DD  slot 7 update (the slot the sibling tactics' rowed update bodies
//               fill): stop when 0x005ACDA9 answers; while the +0x58 target is
//               kept (0x004ED169 says not to retarget) only forget it once it is
//               gone; otherwise, with a farm finder and the owner's record base,
//               attack the farm target 0x005AD404 or the production target
//               0x005AD243 (a game-logic roll, line 135, picks when both exist),
//               and stop when there is neither
#include <vector>
#include "ascii_string.h"

static inline float sqr(float x)
{
	return x * x;
}

extern int g_Va00DBA4E4;

// This unit's statics, built in this order (0x007B461B, 0x007B4636,
// 0x007B4651, 0x007B4662, 0x007B4670).
// Retail's initializer calls AsciiString's out-of-line const char * ctor
// (0x0000654A) rather than expanding it, so inline expansion is off here.
#pragma inline_depth(0)
AsciiString AIFarmKillSquad_IsRunning("AIFarmKillSquad_IsRunning");
AsciiString AIFarmKillSquad_FrameNextRun("AIFarmKillSquad_FrameNextRun");
#pragma inline_depth()
float g_00E06434 = sqr(1100.0f);
int g_00E06438 = g_Va00DBA4E4 * 30;
int g_00E0643C = g_Va00DBA4E4 * 120;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	float length() const;
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

struct Rva005ACCE4Template
{
	char m_pad000[0x108];
	unsigned char m_108;
	char m_pad109[0x10E - 0x109];
	unsigned char m_10E;
	char m_pad10F[0x120 - 0x10F];
	unsigned char m_120;
};

class Object
{
public:
	char m_pad000[4];
	Rva005ACCE4Template *m_04;	// +0x04
	char m_pad008[0x38 - 8];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_id;			// +0x74
	char m_pad078[0x438 - 0x78];
	unsigned char m_438;		// +0x438
};

template <class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	void rva0039E5B9(Coord3D *center);
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned int getFrame() const { return m_40; }
	char m_pad000[0x40];
	unsigned int m_40;		// +0x40
};
extern GameLogic *TheGameLogic;

class Pathfinder
{
public:
	bool rva002F4B33(Object *from, const Coord3D *fromPos, Object *to, int flags);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;	// +0x10
};
extern AI *TheAI;

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

struct Rva005ACCE4Holder
{
	char m_pad00[8];
	Rva005C4AD1LeaField *m_08;	// +0x08
};

class Player;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
	void *rva002C6ACB();
	char m_pad000[0x16C];
	int m_16C;			// +0x16C
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

struct Rva005ACCE4Flags
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned int m_10;
};

struct Rva005ACCE4Team
{
	char m_pad000[0x21C];
	int m_21C;			// +0x21C
	char m_pad220[0x2D0 - 0x220];
	int m_2D0;			// +0x2D0
	int m_2D4;			// +0x2D4
	char m_pad2D8[0x2FC - 0x2D8];
	Rva005ACCE4Flags m_flags;	// +0x2FC
};

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *unit);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, int count);
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	Team *rva004ECECD(int index);
	bool rva005ACDA9();
	unsigned char rva004ED169();
	void teamAttackObject(int a, Object *target);
	void end(int a, int b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x24 - 4];
	void *m_owner;			// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIFarmKillSquad : public AITacticOffensive
{
public:
	virtual ~AIFarmKillSquad();
	virtual bool canRun(void *unit);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, int count);
	virtual void xfer(Xfer *xfer);
	virtual void update();
	float rva005ACDD2(const Coord3D *a, const Coord3D *b);
	Object *getFarmFinder();
	float rva005ACE15(const Coord3D *point, const Coord3D *from, const Coord3D *to);
	Object *findEnemyFortress(Player *player);
	Object *findProductionTarget(void *player);
	Object *findFarmTarget(void *player);
private:
	ObjectID m_58;		// +0x58
	ObjectID m_5C;		// +0x5C
	bool m_farm;		// +0x60
};

bool AIFarmKillSquad::canRun(void *)
{
	void *owner = m_owner;
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(owner);
	if (!m_farm && record->m_16C <= 0)
		return false;
	int running = record->rva002C7196(AIFarmKillSquad_IsRunning);
	unsigned int next = record->rva002C7196(AIFarmKillSquad_FrameNextRun);
	if (!running && next <= TheGameLogic->getFrame() && record->rva002C6ACB())
		return true;
	return false;
}

void AIFarmKillSquad::cleanUp()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	record->rva002C717E(AIFarmKillSquad_IsRunning, 0);
	record->rva002C717E(AIFarmKillSquad_FrameNextRun, TheGameLogic->getFrame()
		+ GetGameLogicRandomValue(g_00E06438, g_00E0643C,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIFarmKillSquad.cpp",
			337));
}

float AIFarmKillSquad::rva005ACDD2(const Coord3D *a, const Coord3D *b)
{
	Coord3D d;
	d.x = a->x;
	d.y = a->y;
	d.z = a->z;
	d.x -= b->x;
	d.y -= b->y;
	d.z -= b->z;
	return d.length();
}

void AIFarmKillSquad::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	AITactic::xfer(xfer);
	XferObjectID(xfer, &m_58);
	XferObjectID(xfer, &m_5C);
}

bool AIFarmKillSquad::initializeTeamTemplate(void *unit, int count)
{
	Rva005ACCE4Team *team = (Rva005ACCE4Team *)unit;
	AITactic::initializeTeamTemplate(unit, count);
	Rva005ACCE4Flags *flags = &team->m_flags;
	flags->m_08 |= 0x04000000;
	flags->m_10 |= 0x20;
	flags->m_00 |= 0x800;
	team->m_21C = 30;
	if (g_00DFEEF8->rva002A8AB1(m_owner)->m_16C == 0)
		team->m_2D4 = 1;
	else
		team->m_2D4 = 2;
	team->m_2D0 = GetGameLogicRandomValue(team->m_2D4, 3,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIFarmKillSquad.cpp",
		371);
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	record->rva002C717E(AIFarmKillSquad_IsRunning, 1);
	return true;
}

Object *AIFarmKillSquad::getFarmFinder()
{
	Object *target = TheGameLogic->findObjectByID(m_5C);
	if (!target) {
		Team *team = rva004ECECD(0);
		if (team) {
			for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
				if (target)
					break;
				Object *member = iter.cur();
				if (!(member->m_438 & 1) && (member->m_04->m_108 & 8))
					target = member;
			}
		}
	}
	return target;
}

Object *AIFarmKillSquad::findEnemyFortress(Player *player)
{
	Object *found = 0;
	_STL::vector<ObjectID> *ids = (_STL::vector<ObjectID> *)((Rva005ACCE4Holder *)g_00DFEEF8->rva002A8F24(player))->m_08->get();
	ObjectID *end = ids->end();
	for (ObjectID *it = ids->begin(); it != end; ++it) {
		if (found)
			break;
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj && (obj->m_04->m_120 & 4))
			found = obj;
	}
	return found;
}

void AIFarmKillSquad::update()
{
	if (rva005ACDA9()) {
		end(1, 0);
		return;
	}
	if (m_58 != 0 && !rva004ED169()) {
		if (!TheGameLogic->findObjectByID(m_58))
			m_58 = INVALID_ID;
		return;
	}
	if (getFarmFinder()) {
		void *player = g_00DFEEF8->rva002A8AB1(m_owner)->rva002C6ACB();
		if (player) {
			Object *target = 0;
			Object *farm = findFarmTarget(player);
			Object *prod = findProductionTarget(player);
			if (farm) {
				if (prod) {
					if (GetGameLogicRandomValue(0, 2,
							"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIFarmKillSquad.cpp",
							135) == 0)
						target = farm;
					else
						target = prod;
				} else {
					target = farm;
				}
			} else if (prod) {
				target = prod;
			} else {
				end(1, 0);
			}
			if (target) {
				m_58 = target->m_id;
				teamAttackObject(0, target);
			}
		} else {
			end(1, 0);
		}
	} else {
		end(1, 0);
	}
}
