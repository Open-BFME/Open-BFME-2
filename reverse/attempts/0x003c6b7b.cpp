// ?rva003C6B7B@ScriptActions@@QAEXPAVParameter@@00@Z
// partial score=0.88 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ScriptActions::rva003C6B7B, retail 0x003C6B7B, 468 bytes (called from the
// action dispatcher 0x003CA4BE at 0x003CE4C9). A BFME2 script action: for
// each alive object of KindOf bit 60 within the radius parameter of the
// named waypoint (BFME2's partition filter chain, the view
// AIStructureCreepTactic.cpp documents) that has a SiegeDockingBehavior
// module, the named team's members (one shared walk of the team list) of
// template KindOf bit 93, with a usable special power of type 0x2D and not
// status 0x40, are offered to the module's +0x20 interface (slot 3, by ID)
// and, while it accepts, aim that power (slot 11) at the object with 2.
#include "ascii_string.h"

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

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// The 224-bit KindOf mask; the (unused, bit) constructor is 0x00045411.
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(int unused, int bit) throw();	// 0x00045411
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
extern unsigned char g_00DFEFA4StoragePrototype[28];

struct Coord3D
{
	float x;
	float y;
	float z;
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

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

// SupplyWarehouseDockUpdate as this condition reads it.
enum ObjectID
{
	INVALID_ID = 0
};

class Module;

// The +0x20 interface of SiegeDockingBehavior: slot 3 takes an object ID.
class Rva003C6B7BDockInterface
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual bool slot3(ObjectID id);
};

class Module
{
public:
	virtual void moduleSlot();
	char m_pad04[0x20 - 0x04];
	Rva003C6B7BDockInterface m_20;	// +0x20
};

enum SpecialPowerType
{
	SPECIAL_RVA003C6B7B_45 = 0x2D
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA003C6B7B_64 = 0x40
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot0();
	virtual bool slot1();
	virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5();
	virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
	virtual void slot10();
	virtual void slot11(Object *target, int flags);
};

class ThingTemplate
{
public:
	char m_pad000[0x113];
	unsigned char m_113;	// +0x113 (bit 5 tested)
};

class Object
{
	friend class ScriptActions;
public:
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;	// 0x00290E22
	bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	ObjectID getID() const { return m_id; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x74 - 0x08];
	ObjectID m_id;		// +0x74
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
};

template<class OBJCLASS> class DLINK_ITERATOR
{
public:
	void advance();		// 0x00263526
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	unsigned char m_rest[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
	char m_pad00[0x0C];
	Coord3D m_location;	// +0x0C
};

class TerrainLogic
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
	virtual void _28()=0; virtual void _29()=0; virtual void _30()=0; virtual void _31()=0;
	virtual void _32()=0; virtual void _33()=0;
	virtual Waypoint *getWaypointByName(const AsciiString &name) = 0;
};
extern TerrainLogic *TheTerrainLogic;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;		// +0x0C
	AsciiString m_string;	// +0x10
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);	// 0x003584E9
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
public:
	void rva003C6B7B(Parameter *teamParm, Parameter *waypointParm, Parameter *radiusParm);
};

void ScriptActions::rva003C6B7B(Parameter *teamParm, Parameter *waypointParm, Parameter *radiusParm)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
	if (!team)
		return;
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	if (iter.done())
		return;
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointParm->getString());
	if (!way)
		return;
	Coord3D pos;
	pos.x = way->getLocation()->x;
	pos.y = way->getLocation()->y;
	pos.z = way->getLocation()->z;
	float radius = radiusParm->m_real;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&pos, radius, 0,
		Rva0004584D(BfmeFixedStorage0004543D(0, 0x3C), *(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
			.link(&Rva0026119DFilter()), 1);
	Object *obj;
	while ((obj = hits.next()) != 0) {
		static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
		Module *dock = obj->findModule(key);
		if (!dock)
			continue;
		for (; !iter.done(); iter.advance()) {
			Object *member = iter.cur();
			if (!(member->m_template->m_113 & 0x20))
				continue;
			SpecialPowerModuleInterface *power = member->findSpecialPowerModuleInterface(SPECIAL_RVA003C6B7B_45);
			if (!power)
				continue;
			if (!power->slot1())
				continue;
			if (member->testStatus(OBJECT_STATUS_RVA003C6B7B_64))
				continue;
			if (!dock->m_20.slot3(member->getID()))
				break;
			power->slot11(obj, 2);
		}
	}
}
