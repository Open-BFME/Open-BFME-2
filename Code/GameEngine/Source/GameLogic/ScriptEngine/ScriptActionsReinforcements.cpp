// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I. /D_STLP_NO_EXCEPTIONS
// stlport
// Native003C7BBB..003C82EA; WB FFC440 independently identifies this action,
// team composition fields and branch sequence. ZH ScriptActions.cpp at
// BFME1 cee35b7d8 supplies reinforcement creation/partitioning semantics.
// BFME2 template offsets, kind7 test, seven unit entries, upgrade/rank calls,
// transport movement and full321-byte PartitionSolver are target evidence.
// All1839 bytes and call bindings verified. Visible iterator49/advance32 and
// GameLogic lookup37/hash47 independently reproduce the existing providers.
// Trivial eight-byte vector storage uses established BfmeE8 providers; no
// original target template spelling is asserted for those folded routines.
// Fieldwise Coord3D copy retains value semantics and native SSE scheduling.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include <stdlib.h>
#include <string.h>
#include "ascii_string.h"
#include <vector>
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
enum SolutionType { PREFER_FAST_SOLUTION = 0 };
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

struct BfmeE8 { int a, b; };

#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::_M_insert_overflow(BfmeE8 *, BfmeE8 const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(BfmeE8 const &); }
// bfme link decl-only end
typedef _STL::vector<_STL::pair<ObjectID, unsigned int> > EntriesVec;
typedef _STL::vector<BfmeE8> SolutionVec;
namespace _STL {
template <> void vector<BfmeE8,allocator<BfmeE8> >::_M_insert_overflow(BfmeE8 *,const BfmeE8 &,const __false_type &,size_t,bool);
}


static __forceinline void pushPartitionEntry(SolutionVec &entries, const _STL::pair<ObjectID, unsigned int> &value) {
 reinterpret_cast<SolutionVec &>(entries).push_back(reinterpret_cast<const BfmeE8 &>(value));
}

class PartitionSolver
{
public:
	PartitionSolver(const EntriesVec &elements, const EntriesVec &spaces, SolutionType solveHow);
	~PartitionSolver();
	void solve();
	const _STL::vector<_STL::pair<ObjectID, ObjectID> > &getSolution() const;
private:
	unsigned char m_pad[0x38];
};

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *tmpl) const;
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }
private:
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n();
	CONTAIN_SLOT(0) CONTAIN_SLOT(1) CONTAIN_SLOT(2) CONTAIN_SLOT(3) CONTAIN_SLOT(4)
	CONTAIN_SLOT(5) CONTAIN_SLOT(6) CONTAIN_SLOT(7) CONTAIN_SLOT(8) CONTAIN_SLOT(9)
	CONTAIN_SLOT(10) CONTAIN_SLOT(11) CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14)
	CONTAIN_SLOT(15) CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23) CONTAIN_SLOT(24)
	CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	virtual unsigned int getContainMax() const; // 0x70
	CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31) CONTAIN_SLOT(32) CONTAIN_SLOT(33)
	CONTAIN_SLOT(34) CONTAIN_SLOT(35) CONTAIN_SLOT(36) CONTAIN_SLOT(37)
	virtual bool isValidContainerFor(const class Object *obj, bool checkCapacity, bool flag) const; // 0x98
	virtual void addToContain(class Object *obj); // 0x9C
#undef CONTAIN_SLOT
};

class LocomotorSet;
class Object;
class Pathfinder
{
public:
	bool AdjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
};

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource);
	void aiMoveToAndEvacuateAndExit(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands;
	unsigned char m_pad21[0x1CC - 0x21];
	LocomotorSet &getLocomotorSet() { return *(LocomotorSet *)m_locomotorSet; }
	unsigned char m_locomotorSet[4];
};

class Thing
{
public:
	virtual ~Thing();
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
};

class Rva00294759
{
public:
	void rva00294759(int level);
};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail { public: unsigned char m_carrier[4]; };
class BfmeObjectDlinkBase { public: Object *dlink_next_TeamMemberList() const;
 const ThingTemplate *m_template;
 unsigned char m_pad08[0x38-8];
 Coord3D m_position;
 unsigned char m_pad44[0x68-0x44];
};
class Object : public Thing, public BfmeObjectDlinkBase, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_objectID; }
	float getMajorRadius() const { return m_majorRadius; }
	__forceinline bool isKindOf(int t) const { return m_template->isKindOf(t); }
	__forceinline bool isDisabledByType(int t) const { return (m_disabledMask[t >> 3] & (1 << (t & 7))) != 0; }
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
	void rva0028FC18();
	int getTransportSlotCount();
	void rva00293275(AsciiString upgrades);
	void rva0028ACDC(int pos);

	unsigned char m_pad70[4];
	ObjectID m_objectID;
	unsigned char m_pad78[0xB8 - 0x78];
	float m_majorRadius;
	unsigned char m_padBC[0x1C8 - 0xBC];
	unsigned char m_disabledMask[4];
	unsigned char m_pad1CC[0x250 - 0x1CC];
	ContainModuleInterface *m_contain;
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc next):m_cur(cur),m_next(next) {}
	__declspec(noinline) void advance() { if(m_cur) m_cur=(m_cur->*m_next)(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	GetNextFunc m_next;
};

class AIGroup;
class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void getTeamAsAIGroup(AIGroup *group);
	void setActive()
	{
		if (!m_active) {
			m_created = true;
			m_active = true;
		}
	}
private:
	unsigned char m_pad[0x38];
	Object *m_head;
	unsigned char m_pad3C[0x5D-0x3C];
	bool m_active;
	bool m_created;
};

inline __declspec(noinline) DLINK_ITERATOR<Object> Team::iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head,&Object::dlink_next_TeamMemberList); }
class TeamFactory
{
public:
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

struct TCreateUnitsInfo
{
	int minUnits, maxUnits, experienceLevel;
	AsciiString upgradeList, unitThingName;
	char unknown14[4];
};

class TeamTemplateInfo
{
public:
	char vtable[4];
	TCreateUnitsInfo m_unitsInfo[7];
	int m_numUnitsInfo;
	unsigned char m_padB0[0x100 - 0xB0];
	AsciiString m_transportUnitType;
	AsciiString m_startReinforceWaypoint;
	bool m_teamStartsFull;
	bool m_transportsExit;
};

class TeamPrototype
{
public:
	const AsciiString &getOwnerName() const { return m_owner; }
	__declspec(dllimport) __forceinline const AsciiString &getName() const { return m_name; }
	__declspec(dllimport) __forceinline const TeamTemplateInfo *getTemplateInfo() const { return &m_teamTemplate; }
private:
	unsigned char m_pad00[0x10];
	AsciiString m_owner;
	AsciiString m_name;
	unsigned char m_pad18[0x12C - 0x18];
	TeamTemplateInfo m_teamTemplate;
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
private:
	unsigned char m_pad00[0x0C];
	Coord3D m_location;
};

class TerrainLogic
{
public:
#define TERRAIN_SLOT(n) virtual void slot##n();
	TERRAIN_SLOT(0) TERRAIN_SLOT(1) TERRAIN_SLOT(2) TERRAIN_SLOT(3) TERRAIN_SLOT(4) TERRAIN_SLOT(5)
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const; // 0x18
	TERRAIN_SLOT(7) TERRAIN_SLOT(8) TERRAIN_SLOT(9) TERRAIN_SLOT(10) TERRAIN_SLOT(11)
	TERRAIN_SLOT(12) TERRAIN_SLOT(13) TERRAIN_SLOT(14) TERRAIN_SLOT(15)
	TERRAIN_SLOT(16) TERRAIN_SLOT(17) TERRAIN_SLOT(18) TERRAIN_SLOT(19)
	TERRAIN_SLOT(20) TERRAIN_SLOT(21) TERRAIN_SLOT(22) TERRAIN_SLOT(23)
	TERRAIN_SLOT(24) TERRAIN_SLOT(25) TERRAIN_SLOT(26) TERRAIN_SLOT(27)
	TERRAIN_SLOT(28) TERRAIN_SLOT(29) TERRAIN_SLOT(30) TERRAIN_SLOT(31)
	TERRAIN_SLOT(32) TERRAIN_SLOT(33)
#undef TERRAIN_SLOT
	virtual Waypoint *getWaypointByName(const AsciiString &name); // 0x88
};
extern TerrainLogic *TheTerrainLogic;

struct CreateMask { unsigned int m_bits[4]; };

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID flag);
};
extern ThingFactory *TheThingFactory;


extern GameLogic *TheGameLogic;

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};

class AIGroup
{
public:
	void groupMoveToPosition(Rva00372571Params *params, int source);
};

class AI
{
public:
	AIGroup *createGroup();
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

// KindOf bit 7 (template +0x108 & 0x80) and bit 21 (+0x10A & 0x20, the
// transport test of Zero Hour's team-starts-full pass); disabled bit 3 at +0x1C8.
enum { KINDOF_BIT7 = 7, KINDOF_TRANSPORT = 21, DISABLED_HELD = 3 };


// Storage and traversal from native _M_find2888D4 and pinned STLport reference.
struct ReinforcementObjectLookupNode { ReinforcementObjectLookupNode *next; ObjectID key; Object *object; };
struct ReinforcementObjectLookupBuckets {
 ReinforcementObjectLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 ReinforcementObjectLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct ReinforcementObjectLookupMap { unsigned char hashEqual[4]; ReinforcementObjectLookupBuckets buckets; };
inline __declspec(noinline) ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 ReinforcementObjectLookupMap *map=(ReinforcementObjectLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 ReinforcementObjectLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}

inline __declspec(noinline) Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}



void ScriptActions::doCreateReinforcements(const AsciiString &team, const AsciiString &waypoint, bool useUnit)
{
	TeamPrototype *theTeamProto = TheScriptEngine->rva003570D1(team);
	Coord3D destination;
	bool needToMoveToDestination = false;
	bool adjustToPathable = false;
	if (useUnit) {
		Object *unit = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(waypoint);
		if (!unit)
			return;
		destination = *unit->getPosition();
		if (unit->isKindOf(KINDOF_BIT7))
			adjustToPathable = true;
	} else {
		Waypoint *way = TheTerrainLogic->getWaypointByName(waypoint);
		if (!way)
			return;
		destination = *way->getLocation();
	}
	if (!theTeamProto)
		return;

	const TeamTemplateInfo *pInfo = theTeamProto->getTemplateInfo();
	Coord3D origin;
	origin.x = destination.x;
	origin.y = destination.y;
	origin.z = destination.z;
	Waypoint *way = TheTerrainLogic->getWaypointByName(pInfo->m_startReinforceWaypoint);
	if (way) {
		origin = *way->getLocation();
		if (origin.x != destination.x || origin.y != destination.y)
			needToMoveToDestination = true;
	}

	Team *theTeam = TheTeamFactory->createInactiveTeam(theTeamProto->getOwnerName(), theTeamProto->getName());
	if (!theTeam)
		return;

	const ThingTemplate *transportTemplate = 0;
	Object *transport = 0;
	if (!pInfo->m_transportUnitType.isEmpty()) {
		transportTemplate = TheThingFactory->findTemplate(pInfo->m_transportUnitType);
		if (transportTemplate) {
			CreateMask mask;
			memset(&mask, 0, sizeof(mask));
			transport = TheThingFactory->newObject(transportTemplate, theTeam, &mask, (ObjectID)0);
			if (transport) {
				transport->setPosition(&origin);
				transport->setOrientation(0.0f);
				transport->rva0028FC18();
			}
		}
	}

	int transportCount = 1;
	int i, j;
	for (i = 0; i < pInfo->m_numUnitsInfo; i++) {
		const ThingTemplate *unitTemplate = TheThingFactory->findTemplate(pInfo->m_unitsInfo[i].unitThingName);
		Coord3D pos;
		pos.x = origin.x;
		pos.y = origin.y;
		pos.z = origin.z;
		if (unitTemplate && theTeam) {
			Object *obj = 0;
			for (j = 0; j < pInfo->m_unitsInfo[i].maxUnits; j++) {
				CreateMask mask;
				memset(&mask, 0, sizeof(mask));
				obj = TheThingFactory->newObject(unitTemplate, theTeam, &mask, (ObjectID)0);
				if (obj) {
					pos.x = origin.x + 2.25 * j * obj->getMajorRadius();
					if (adjustToPathable && !needToMoveToDestination) {
						AIUpdateInterface *ai = obj->getAIUpdateInterface();
						if (ai) {
							TheAI->pathfinder()->AdjustDestination(obj, ai->getLocomotorSet(), &pos, 0);
							obj->rva0028ACDC((int)&pos);
						}
					}
					pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
					obj->setPosition(&pos);
					obj->setOrientation(0.0f);
					obj->rva0028FC18();
					obj->rva00293275(pInfo->m_unitsInfo[i].upgradeList);
					((Rva00294759 *)obj)->rva00294759(pInfo->m_unitsInfo[i].experienceLevel);
				}
			}
			if (obj)
				pos.y += 2 * obj->getMajorRadius();
		}
		origin.y = pos.y;
	}

	origin = destination;
	if (pInfo->m_teamStartsFull) {
		SolutionVec vecOfUnits;
		SolutionVec vecOfTransports;
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *obj = iter.cur();
			if (obj == transport)
				continue;
			if (obj->isKindOf(KINDOF_TRANSPORT)) {
				ContainModuleInterface *contain = obj->getContain();
				if (contain)
					pushPartitionEntry(vecOfTransports, _STL::pair<ObjectID, unsigned int>(obj->getID(), contain->getContainMax()));
			} else {
				int slots = obj->getTransportSlotCount();
				if (slots == 0)
					slots = 8388607;	// 0x7FFFFF, a slot cap (decimal so link_debt does not read it as an image address)
				pushPartitionEntry(vecOfUnits, _STL::pair<ObjectID, unsigned int>(obj->getID(), slots));
			}
		}
		PartitionSolver partition(reinterpret_cast<const EntriesVec &>(vecOfUnits), reinterpret_cast<const EntriesVec &>(vecOfTransports), PREFER_FAST_SOLUTION);
		partition.solve();
		SolutionVec solution = reinterpret_cast<const SolutionVec &>(partition.getSolution());
		unsigned int count = solution.size();
		for (unsigned int k = 0; k < count; ++k) {
			Object *unit = TheGameLogic->findObjectByID((ObjectID)solution[k].a);
			Object *trans = TheGameLogic->findObjectByID((ObjectID)solution[k].b);
			if (!unit || !trans)
				continue;
			ContainModuleInterface *contain = trans->getContain();
			if (contain)
				contain->addToContain(unit);
		}
	}

	if (transport) {
		ContainModuleInterface *contain = transport->getContain();
		if (contain) {
			for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
				Object *obj = iter.cur();
				_ReadWriteBarrier();
				if (!obj)
					continue;
				if (transport && obj->getTemplate()->isEquivalentTo(transport->getTemplate()))
					continue;
				if (obj->getContainedBy())
					continue;
				Coord3D pos; pos.x=origin.x; pos.y=origin.y; pos.z=origin.z;
				pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);
				if (transport)
					pos.x += transportCount * transport->getMajorRadius();
				if (contain->isValidContainerFor(obj, false, false)) {
					if (!contain->isValidContainerFor(obj, true, false)) {
						CreateMask mask;
						memset(&mask, 0, sizeof(mask));
						transport = TheThingFactory->newObject(transportTemplate, theTeam, &mask, (ObjectID)0);
						if (transport) {
							transportCount++;
							transport->setPosition(&pos);
							transport->setOrientation(0.0f);
							contain = transport->getContain();
							transport->rva0028FC18();
						}
					}
					contain->addToContain(obj);
				}
			}
		}
	}

	if (transport) {
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
			Object *obj = iter.cur();
			_ReadWriteBarrier();
			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (obj->getTemplate()->isEquivalentTo(transport->getTemplate())) {
				if (pInfo->m_transportsExit) {
					if (ai)
						ai->m_commands.aiMoveToAndEvacuateAndExit(&destination, CMD_FROM_SCRIPT);
				} else {
					if (ai)
						ai->m_commands.aiMoveToAndEvacuate(&destination, CMD_FROM_SCRIPT);
				}
			} else if (!obj->isDisabledByType(DISABLED_HELD)) {
				if (ai)
					ai->m_commands.aiMoveToPosition(&destination, CMD_FROM_SCRIPT);
			}
		}
	} else {
		theTeam->setActive();
		if (needToMoveToDestination) {
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup) {
				theTeam->getTeamAsAIGroup(theGroup);
				Rva00372571Params params;
				params.m_14 = -1;
				params.m_pos = &destination;
				params.m_04 = false;
				params.m_08 = 0;
				params.m_0C = 0;
				params.m_10 = 0;
				params.m_18 = 0;
				params.m_1C = false;
				theGroup->groupMoveToPosition(&params, CMD_FROM_SCRIPT);
			}
		}
	}
}
