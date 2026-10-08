// cl: /DBFME_ASCII_DTOR_DECL /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// The "StructureCreep" skirmish-AI tactic (vtable 0x008722EC; ctor 0x005AB91D
// in Rva004ECECDTacticCtors.cpp, slot 9 0x005AB9AF in
// Rva004ECECDTacticCreate.cpp). Base chain, all address-derived: Rva005DCC24
// (ctor 0x005DCC0A, dtor 0x005DCC24) over AITacticOffensive over the AITactic.cpp
// object AITactic. Layout: +0x58 an ObjectID, +0x5C, +0x64, +0x68
// counters, +0x60 the owned build order (Rva00573B23, 0x40 bytes), +0x6C the
// index of the structure name last picked from the owner's list.
//
//   0x005AB7C4  the owner record's site with the given id
//   0x005AB7E5  dtor: abandon (0x0055ADBA) and ::delete the build order
//   0x005AB993  scalar deleting dtor (slot 0)
//   0x005ABC81  slot 2: clear the running key and schedule the next run
//               5 * frames on; hand the built structure (+0x58) to the
//               controller's default team and the owner's list
//   0x005AB843  slot 5: xfer: the AITactic's, the id, the counters, whether
//               there is an order and the order itself (restarted on load
//               when it had not begun)
//   0x005AB9EE  whether the object's template name is one of the owner's
//               creep structure names (record +0x160, +0x98 vector)
//   0x005ABA59  the next creep structure name: a random one first, then
//               round-robin
//   0x005AC0B5  whether a structure of this name may go up at the +0x68
//               site: true when no alive allied kind-7 object is within
//               twice its radius, or fewer than three of them are creep
//               structures and the name is a kind-8 template or not yet
//               among theirs
//   0x005ABEA2  last to first over the owner record's +0x164 sites below
//               state 2: a site with more than 15 live allied objects of
//               kind 3 or 90 that are not kind 7 within its radius becomes
//               the creep target (+0x68)
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <string.h>
#include <set>
#include <vector>
#include "ascii_string.h"

extern int g_Va00DBA4E4;

// This unit's statics (0x00E06418..0x00E06428, built in this order by
// 0x007B458D, 0x007B45A8, 0x007B45C1, 0x007B45CE and 0x007B45D9).
// Retail's initializer calls AsciiString's out-of-line const char * ctor
// (0x0000654A) rather than expanding it, so inline expansion is off here.
#pragma inline_depth(0)
AsciiString AIStructureCreep_IsRunning("AIStructureCreep_IsRunning");
#pragma inline_depth()
float g_00E0641C = g_Va00DBA4E4 * 30.0f;
int g_00E06420 = g_Va00DBA4E4 * 2;
int g_00E06424 = g_Va00DBA4E4;
int g_00E06428 = g_Va00DBA4E4 * 5;

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
struct Coord3DBase;

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

struct Rva005AB7E5Template
{
	char m_pad00[0x64];
	AsciiString m_name;	// +0x64
};

class Player;
class Team;

struct Coord3D;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);			// 0x001E8A38
	void aiMoveToPosition(const Coord3D *point, int source);	// move to the point
};

struct Rva005AB7E5AI
{
	char m_pad00[0x20];
	AICommandInterface m_commands;	// +0x20
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void setTeam(Team *team);
	char m_pad000[4];
	Rva005AB7E5Template *m_04;	// +0x04
	char m_pad008[0x38 - 8];
	float m_pos[3];			// +0x38
	char m_pad044[0x258 - 0x44];
	Rva005AB7E5AI *m_ai;		// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_438;		// +0x438
};

class Player
{
public:
	char m_pad000[0x2EC];
	Team *m_defaultTeam;		// +0x2EC
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

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	~Coord3D() {}
};

class Rva004EBF4B
{
public:
	Coord3D rva004EBF4B();
};

class AIDozerManager
{
public:
	void rva00599825(int id);
	void *rva00599870(const Coord3D &point, int a);
};

class Rva00596389
{
public:
	int rva00596394() const;
};

struct Rva005AB7E5Objects
{
	char m_pad00[0x0C];
	Rva00596389 *m_0C;		// +0x0C
};

struct Rva005AB7E5NameList
{
	unsigned int size() const { return m_end - m_begin; }
	bool empty() const { return m_begin == m_end; }
	AsciiString &operator[](unsigned int i) { return m_begin[i]; }
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct Rva005AB7E5Names
{
	char m_pad00[0x98];
	Rva005AB7E5NameList m_names;	// +0x98
};


// BFME2's partition filters (Open-BFME-1 carries the same shape): a vptr, the
// +0x04 link to the next filter of a chain, then each filter's own members.
// Rva000421C8 is the base (ctor 0x000421C8, vftable 0x00BC26E0); the inline
// destructors only restore that vftable, as retail does at every scope exit.
class Object;
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

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva005ABEA2Mask
{
	Rva005ABEA2Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit);	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00C1A268, allow 0x0026115D: reject objects satisfying the
// set/clear masks (ZH's PartitionFilterRejectByKindOf).
class PartitionFilterRejectByKindOf : public Rva000421C8
{
public:
	PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b);
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
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

struct Rva005ABEA2Hit
{
	Object *m_object;
	float m_distance;
};

struct Rva005ABEA2Payload
{
	Rva005ABEA2Hit *m_begin;
	Rva005ABEA2Hit *m_end;
	Rva005ABEA2Hit *m_capacity;
	Rva005ABEA2Hit *m_current;
	int m_references;
};

struct Rva005AC0B5Template
{
	char m_pad000[0x108];
	unsigned int m_108;	// +0x108
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);	// the thing template by name
};
// Use the ledger-defined factory view at DFF000; avoid a second
// external spelling of the same factory pointer.
extern Rva002D06CA *TheThingFactory;

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	Rva005ABEA2Payload *m_value;
	~BfmeWideResult();	// 0x0004AA28
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

struct Rva005ABEA2Site
{
	unsigned int m_id;	// +0x00
	Coord3D m_pos;		// +0x04
	unsigned int m_10;	// +0x10
	float m_radius;		// +0x14
};

// The owner record's +0x164 list of candidate sites.
class Rva002C5FE8
{
public:
	void *rva002C5FE8(int id);		// the site with this id
	void rva002C60A9(unsigned int id);	// drop and free the site with this id
	char m_pad00[0x20];
	Rva005ABEA2Site **m_begin;	// +0x20
	Rva005ABEA2Site **m_end;	// +0x24
};

struct Rva002A8AB1Record
{
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
	char m_pad000[0x140];
	AIDozerManager m_140;		// +0x140
	char m_pad141[0x160 - 0x141];
	Rva005AB7E5Names *m_160;	// +0x160
	Rva002C5FE8 *m_164;	// +0x164
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Rva00506FE9Hit
{
public:
	void rva0055ADBA(void *owner);
};

class Rva004E9378
{
public:
	bool rva004E9378();	// the order has finished
};

class Rva00573B23
{
public:
	Rva00573B23();
	virtual ~Rva00573B23();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5();
	virtual void start(void *owner, int a);
	virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
	virtual void v11();
	virtual void xfer(Xfer *xfer, void *owner);
	float m_radius;		// +0x04
	ObjectID m_08;		// +0x08
	AsciiString m_name;	// +0x0C
	int m_status;		// +0x10
	char m_pad14[0x20 - 0x14];
	bool m_20;		// +0x20
	bool m_21;		// +0x21
	char m_pad22[0x28 - 0x22];
	bool m_28;		// +0x28
	char m_pad29[0x40 - 0x29];
};

struct Rva00573A00
{
	void rva00573A00(const Coord3D *p);
};

class AITactic
{
public:
	virtual ~AITactic();
	virtual void cleanUp();
	virtual void initializeTeamTemplate();
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void v8();
	virtual AITactic *create();
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	char m_pad04[0x24 - 4];
	Player *m_owner;		// +0x24
	char m_pad28[0x58 - 0x28];
};

class Rva005DCC24 : public AITacticOffensive
{
public:
	virtual ~Rva005DCC24();
};

class AIStructureCreepTactic : public Rva005DCC24
{
public:
	virtual ~AIStructureCreepTactic();
	virtual void cleanUp();
	virtual void xfer(Xfer *xfer);
	bool findBestInterestZone();
	AsciiString getBuildTemplateName();
	bool rva005ABCFE(Coord3DBase *out, const AsciiString &name);
	bool validateTemplateName(const AsciiString &name);
	bool isOffensiveBuilding(Object *obj);
	bool rva005AC294();
	void moveDozerAway();
	virtual void update();
private:
	ObjectID m_58;		// +0x58
	unsigned int m_5C;	// +0x5C
	Rva00573B23 *m_order;	// +0x60
	unsigned int m_64;	// +0x64
	unsigned int m_68;	// +0x68
	int m_next;		// +0x6C
	unsigned int m_70;	// +0x70 frame of the next site scan
	unsigned int m_74;	// +0x74 frame of the next move order
	bool m_78;		// +0x78 done
	bool m_running;		// +0x79
	unsigned int m_nextRun;	// +0x7C
};

AIStructureCreepTactic::~AIStructureCreepTactic()
{
	if (m_order) {
		((Rva00506FE9Hit *)m_order)->rva0055ADBA(m_owner);
		::delete m_order;
		m_order = 0;
	}
}

void AIStructureCreepTactic::xfer(Xfer *xfer)
{
	AITactic::xfer(xfer);
	XferObjectID(xfer, &m_58);
	*xfer == m_5C;
	*xfer == m_64;
	*xfer == m_68;
	bool hasOrder = m_order != 0;
	*xfer == hasOrder;
	if (hasOrder) {
		if (xfer->IsStoring()) {
			m_order->xfer(xfer, m_owner);
		} else if (xfer->IsLoading()) {
			m_order = new Rva00573B23;
			m_order->xfer(xfer, m_owner);
			if (m_order->m_status == 0)
				m_order->start(m_owner, 1);
		}
	}
}

bool AIStructureCreepTactic::isOffensiveBuilding(Object *obj)
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	for (unsigned int i = 0; i < record->m_160->m_names.size(); ++i) {
		const AsciiString &name = obj->m_04->m_name;
		if (record->m_160->m_names[i].compare(name) == 0)
			return true;
	}
	return false;
}

AsciiString AIStructureCreepTactic::getBuildTemplateName()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	if (m_next == -1) {
		m_next = GetGameLogicRandomValue(0, record->m_160->m_names.size() - 1,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\TargetlessTactics\\AIStructureCreepTactic.cpp",
			368);
	} else if ((unsigned int)++m_next >= record->m_160->m_names.size()) {
		m_next = 0;
	}
	return record->m_160->m_names[m_next];
}

void AIStructureCreepTactic::cleanUp()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(m_owner);
	if (m_running) {
		record->rva002C717E(AIStructureCreep_IsRunning, 0);
		m_nextRun = TheGameLogic->getFrame() + g_00E06428;
	}
	Object *obj = TheGameLogic->findObjectByID(m_58);
	if (obj && !(obj->m_438 & 1)) {
		obj->setTeam(obj->getControllingPlayer()->m_defaultTeam);
		record->m_140.rva00599825(m_58);
	}
}

bool AIStructureCreepTactic::findBestInterestZone()
{
	Rva002C5FE8 *sites = g_00DFEEF8->rva002A8AB1(m_owner)->m_164;
	if (sites->m_begin != sites->m_end) {
		for (int i = (int)(sites->m_end - sites->m_begin) - 1; i >= 0; --i) {
			Rva005ABEA2Site *site = sites->m_begin[i];
			if (site->m_10 >= 2)
				continue;
			Rva005ABEA2Mask mask;
			mask.set(3);
			mask.set(90);
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&site->m_pos,
				site->m_radius, 0,
				Rva0026119DFilter().link(&Rva00261409Filter(m_owner, true, 2))
					->link(&Rva003959FA(*(BfmeFixedStorage0004543D *)&mask))
					->link(&PartitionFilterRejectByKindOf(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
						*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)), 0);
			if ((unsigned int)(hits.m_value->m_end - hits.m_value->m_begin) > 15) {
				m_68 = site->m_id;
				return true;
			}
		}
	}
	return false;
}

// The base filter's slot 2 is the trivial virtual retail shares across 68
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

Rva005ABEA2Site *getMyZone(Player *owner, int id)
{
	Rva002C5FE8 *sites = g_00DFEEF8->rva002A8AB1(owner)->m_164;
	return (Rva005ABEA2Site *)sites->rva002C5FE8(id);
}
bool AIStructureCreepTactic::validateTemplateName(const AsciiString &name)
{
	Player *owner = m_owner;
	Rva005ABEA2Site *site = getMyZone(owner, m_68);
	Rva005ABEA2Mask mustBeSet;
	Rva005ABEA2Mask mustBeClear;
	mustBeSet.set(7);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&site->m_pos,
		site->m_radius * 2.0f, 0,
		Rva0026119DFilter().link(&Rva00261409Filter(m_owner, true, 2))
			->link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&mustBeSet,
				*(BfmeFixedStorage0004543D *)&mustBeClear)), 0);
	if (hits.m_value->m_end - hits.m_value->m_begin == 0)
		return true;
	_STL::vector<Object *> objects;
	_STL::set<AsciiString> names;
	Object *obj;
	while ((obj = hits.next()) != 0) {
		if (isOffensiveBuilding(obj)) {
			objects.push_back(obj);
			Rva005AB7E5Template *tmpl = obj->m_04;
			names.insert(tmpl->m_name);
		}
	}
	if (objects.size() < 3) {
		Rva005AC0B5Template *tmpl = (Rva005AC0B5Template *)TheThingFactory->rva002D06CA(&name);
		if (tmpl->m_108 & 8)
			return true;
		if (names.find(name) == names.end())
			return true;
	}
	return false;
}
