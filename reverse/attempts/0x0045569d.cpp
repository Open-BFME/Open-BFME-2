// ?construct@FoundationAIUpdate@@UAEPAVObject@@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@H_N@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX
//
// ?construct@FoundationAIUpdate@@UAEPAVObject@@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@H_N@Z
// retail 0x0045569D, 1174 bytes (ret 0x18): slot 7 of the +0x20 interface
// vtable 0x00C1A690, the call the rowed slot 4 0x00456134 makes with its
// template, position, angle, owner, 0 and its last argument.
//
// Target evidence: the body builds the template on the foundation through
// TheThingFactory->newObject on the owner's +0x2EC team with an empty status
// mask, makes the foundation object its producer and gives it the orientation
// and position (teleportTo around setOrientation), as ZH's dozer construct
// does. A foundation whose CastleMemberBehavior module (two cached name keys,
// the rowed NameKeyGenerator::nameToKey) names a valid item refuses unless
// the flag is set. KindOf 0xA3 templates face away from the keep the member
// module names (+0x14; unless the castle module of +0x18 has its module data
// flag +0x74), through the rowed atan2 adapter and normalizeAngle, plus the
// template angle +0x4D0; KindOf 0x69 templates add that angle to the
// foundation's own. Without the flag a KindOf 0x69 (not 0x68) template
// starts as ZH's under-construction structure: zero construction percent
// (+0x280), status 2, model conditions 67 set and 68/69 cleared and one hit
// point (body +0x254, vslots 4 and 32). The module data's +0x0C mode sets
// model condition 340 or 341 and is sent with the object as Lua event 16.
// After onStructureCreated (0x002AA559) a flagged build clears model
// condition 69, marks construction complete (-1) and enters the pathfind
// map; the member module ids are copied from the foundation's, an unflagged
// build pays the cost (pinned 0x0033A69A, rowed withdrawal 0x003B0CB3 and
// stats 0x0039BAD2) and keeps it at +0x324; the foundation's +0x45C value
// and +0x284 upgrade bits pass to the new object. The method name follows
// WorldBuilder's FoundationAIUpdate::construct; the slot's other names are
// by address.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define NULL 0
#define TRUE true
#define FALSE false

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ModuleData;
class Team;
class Player;
class Object;

class Matrix3D
{
public:
	Real Get_Z_Rotation() const;
};

class Module
{
public:
	virtual void m00();
	const ModuleData *getModuleData() const { return m_moduleData; }
private:
	const ModuleData *m_moduleData; // +0x04
};

// The CastleMemberBehavior module: keep and castle ids.
class BfmeItemE63 : public Module
{
public:
	Bool checkValid();
	unsigned char m_pad08[0x14 - 0x08];
	ObjectID m_keepID; // +0x14
	ObjectID m_castleID; // +0x18
};

class CastleBehaviorModuleData
{
public:
	unsigned char m_pad00[0x74];
	Bool m_flag74; // +0x74
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

class Drawable
{
public:
	void rva00274176(Bool value);
};

// The shared empty body 0x000B3FD0, called on the drawable.
class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class BodyModuleInterface
{
public:
	virtual void i00(); virtual void i01(); virtual void i02(); virtual void i03();
	virtual Real getHealth(Int unused); // +0x10
	virtual void i05(); virtual void i06(); virtual void i07();
	virtual void i08(); virtual void i09(); virtual void i10(); virtual void i11();
	virtual void i12(); virtual void i13(); virtual void i14(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
	virtual void i20(); virtual void i21(); virtual void i22(); virtual void i23();
	virtual void i24(); virtual void i25(); virtual void i26(); virtual void i27();
	virtual void i28(); virtual void i29(); virtual void i30(); virtual void i31();
	virtual void setHealthDelta(Real delta); // +0x80
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(Int t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
	Int rva0033A69A(const Player *player, Int builder, Int a3) const;
	Real getPlacementAngle() const { return m_placementAngle; }
private:
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[6]; // +0x108
	unsigned char m_pad120[0x4D0 - 0x120];
	Real m_placementAngle; // +0x4D0
};

// Rowed bit-set helpers over the 19-word model condition flags.
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int unused, unsigned bit1, unsigned bit2);
	unsigned m_words[19];
};

class Rva0028F59A
{
public:
	Rva0028F59A(int unused, int bit);
	unsigned m_words[19];
};

struct CreateMask
{
	UnsignedInt m_bits[4];
};

class ModelConditionFlags
{
public:
	UnsignedInt test(Int bit) const { return m_words[bit >> 5] & (1U << (bit & 31)); }
	void set(Int bit) { m_words[bit >> 5] |= 1U << (bit & 31); }
	void clear(Int bit) { m_words[bit >> 5] &= ~(1U << (bit & 31)); }
private:
	UnsignedInt m_words[19];
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

class Dict;

namespace _STL
{
template <int _Nw> struct _Base_bitset
{
	void _M_do_or(const _Base_bitset<_Nw> &__x);
	unsigned long _M_w[_Nw];
};
}
typedef _STL::_Base_bitset<32> UpgradeMaskType;

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
	Drawable *getDrawable() const;
	void setOrientation(Real angle);
private:
	void *m_vptr;
	const ThingTemplate *m_template; // +0x04
	Matrix3D m_transform; // +0x08
	unsigned char m_pad009[0x38 - 0x09];
	Coord3D m_position; // +0x38
};

class Object : public Thing
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Module *findModule(NameKeyType key) const;
	Bool isFoundationLocked() const { return (m_status94 & 1) != 0; }
	void rva0028BAC0();
	void setProducer(Object *obj);
	void setStatus(ObjectStatusTypes bit, Bool set);
	void rva0028CFB2(const int *set, const int *clear);
	void rva0028AE6D();
	void teleportTo(const Coord3D *pos, Bool flag);
	void rva0028DCC4();
	void rva00293E64(Dict *dict);
	void updateUpgradeModules();
	__forceinline void setModelConditionState(Int bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(Int bit)
	{
		if (m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.clear(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad044[0x94 - 0x44];
	unsigned char m_status94; // +0x94
	unsigned char m_pad095[0x10C - 0x95];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	BodyModuleInterface *m_body; // +0x254
	unsigned char m_pad258[0x280 - 0x258];
public:
	Real m_constructionPercent; // +0x280
	UpgradeMaskType m_upgrades; // +0x284
	unsigned char m_pad304[0x324 - 0x304];
	Real m_buildCost; // +0x324
	unsigned char m_pad328[0x45C - 0x328];
	Int m_value45C; // +0x45C
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

class Rva0039B795;
struct Rva0039BAD2Input;

class Rva0039BAD2
{
public:
	void rva0039BAD2(Rva0039BAD2Input *what, Int cost);
};

class Rva0039B795 : public Rva0039BAD2
{
};

class Rva003B0D7C
{
public:
	UnsignedInt rva003B0CB3(UnsignedInt amount, Rva0039B795 *stats, Bool flag);
};

class Player
{
public:
	Rva003B0D7C *getMoney() { return &m_money; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
	Rva0039B795 *getStats() { return &m_stats; }
	void onStructureCreated(Object *builder, Object *structure);
private:
	unsigned char m_pad000[0x90];
	Rva003B0D7C m_money; // +0x90
	unsigned char m_pad091[0x2EC - 0x91];
	Team *m_defaultTeam; // +0x2EC
	unsigned char m_pad2F0[0x3BC - 0x2F0];
	Rva0039B795 m_stats; // +0x3BC
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *statusBits, Bool flag);
};
extern ThingFactory *TheThingFactory;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void rva0023D0C2(Object *obj, Int value);
};
extern GameLogic *TheGameLogic;

double Rva000422A0Atan2(Real y, Real x);
Real normalizeAngle(Real angle);

extern "C" void *__cdecl memset(void *dst, int value, unsigned int size);

// BFME 2's delayed Lua event list (rowed ctor 0x000B6D8B and dtor 0x000B6DD2).
struct BfmeDispatchDelayedLuaEvent
{
	void *m_vtable;
	Real m_number;
	unsigned char m_boolean;
	UnsignedInt m_objectID;
	UnsignedInt m_string;
	UnsignedInt m_type;
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	BfmeDispatchDelayedLuaEvent m_events[3];
};

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class FoundationAIUpdateModuleData
{
public:
	unsigned char m_pad00[0x0C];
	Int m_mode; // +0x0C
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

struct BehaviorModuleInterface { virtual void f0C(); };
struct UpdateModuleInterface { virtual void f10(); };

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class Rva00C1A690Iface
{
public:
	virtual void gap0(); virtual void gap1(); virtual void gap2(); virtual void gap3();
	virtual void gap4(); virtual void gap5(); virtual void gap6();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle,
		Player *owningPlayer, Int unused, Bool isRebuild) = 0;
};

class FoundationAIUpdate : public UpdateModule, public Rva00C1A690Iface
{
public:
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle,
		Player *owningPlayer, Int unused, Bool isRebuild);
	const FoundationAIUpdateModuleData *getFoundationAIUpdateModuleData() const
	{
		return (const FoundationAIUpdateModuleData *)m_moduleData;
	}
};

#define KINDOF_A3 0xA3
#define KINDOF_68 0x68
#define KINDOF_69 0x69
#define KINDOF_3C 0x3C

//-------------------------------------------------------------------------------------------------
Object *FoundationAIUpdate::construct(const ThingTemplate *what, const Coord3D *pos, Real angle,
	Player *owningPlayer, Int unused, Bool isRebuild)
{
	const FoundationAIUpdateModuleData *md = getFoundationAIUpdateModuleData();
	if (what == NULL || pos == NULL || owningPlayer == NULL)
		return NULL;

	Object *foundation = getObject();
	if (foundation->isFoundationLocked())
		return NULL;

	static NameKeyType memberKey = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
	BfmeItemE63 *member = (BfmeItemE63 *)foundation->findModule(memberKey);
	if (!isRebuild && member && member->m_keepID && member->checkValid())
		return NULL;

	CreateMask statusBits;
	memset(&statusBits, 0, sizeof(statusBits));
	Object *obj = TheThingFactory->newObject(what, owningPlayer->getDefaultTeam(), &statusBits, false);
	obj->rva0028BAC0();
	Real orientation = angle;
	obj->setProducer(foundation);

	if (obj->getTemplate()->isKindOf(KINDOF_A3))
	{
		static NameKeyType memberKey2 = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
		BfmeItemE63 *member2 = (BfmeItemE63 *)foundation->findModule(memberKey2);
		if (member2)
		{
			GameLogic *logic = TheGameLogic;
			Object *keep = logic->findObjectByID(member2->m_keepID);
			if (keep)
			{
				Object *castle = logic->findObjectByID(member2->m_castleID);
				Module *castleModule;
				if (castle == NULL
					|| (castleModule = castle->findModule(CastleBehavior::rva0003955DA())) == NULL
					|| !((const CastleBehaviorModuleData *)castleModule->getModuleData())->m_flag74)
				{
					Coord3D delta;
					delta.x = foundation->getPosition()->x;
					delta.y = foundation->getPosition()->y;
					delta.x -= keep->getPosition()->x;
					delta.y -= keep->getPosition()->y;
					orientation = normalizeAngle((Real)Rva000422A0Atan2(delta.y, delta.x));
					orientation = obj->getTemplate()->getPlacementAngle() + orientation;
				}
			}
		}
	}
	else if (obj->getTemplate()->isKindOf(KINDOF_69))
	{
		orientation = obj->getTemplate()->getPlacementAngle();
		orientation = foundation->getTransformMatrix()->Get_Z_Rotation() + orientation;
	}

	if (!isRebuild && obj->getTemplate()->isKindOf(KINDOF_69) && !obj->getTemplate()->isKindOf(KINDOF_68))
	{
		obj->m_constructionPercent = 0.0f;
		obj->setStatus(OBJECT_STATUS_UNDER_CONSTRUCTION, TRUE);
		Rva001E4912 clearBits;
		obj->rva0028CFB2((const int *)&Rva0028F59A(0, 67), (const int *)clearBits.rva001E4912(0, 68, 69));
		BodyModuleInterface *body = obj->getBodyModule();
		body->setHealthDelta(1.0f - body->getHealth(0));
	}

	if (md->m_mode)
	{
		switch (md->m_mode)
		{
		case 1:
			obj->setModelConditionState(340);
			break;
		case 2:
			obj->setModelConditionState(341);
			break;
		}
	}

	obj->getDrawable()->rva00274176(TRUE);
	obj->teleportTo(pos, FALSE);
	obj->setOrientation(orientation);
	obj->teleportTo(pos, FALSE);
	Drawable *draw = obj->getDrawable();
	if (draw)
		((Rva000B3FD0 *)draw)->rva000B3FD0();
	obj->rva0028DCC4();

	if (md->m_mode)
	{
		BfmeDelayedLuaEventList list;
		list.m_events[0].m_number = (Real)md->m_mode;
		list.m_events[0].m_type = 1;
		reinterpret_cast<BfmeObjectEventDispatch *>(TheLuaScriptEngine)->rva003360D2(16, obj, &list);
	}

	owningPlayer->onStructureCreated(getObject(), obj);

	if (isRebuild)
	{
		obj->clearModelConditionState(69);
		obj->m_constructionPercent = -1.0f;
		TheAI->pathfinder()->AddObjectToPathfindMap(obj);
	}

	obj->rva00293E64(NULL);
	if (!obj->getTemplate()->isKindOf(KINDOF_3C))
		TheAI->pathfinder()->AddObjectToPathfindMap(obj);

	BfmeItemE63 *newMember = (BfmeItemE63 *)obj->findModule(memberKey);
	BfmeItemE63 *oldMember = (BfmeItemE63 *)getObject()->findModule(memberKey);
	if (newMember && oldMember)
	{
		newMember->m_keepID = oldMember->m_keepID;
		newMember->m_castleID = oldMember->m_castleID;
		if (!isRebuild)
		{
			UnsignedInt cost = what->rva0033A69A(owningPlayer, (Int)getObject(), -1);
			owningPlayer->getMoney()->rva003B0CB3(cost, owningPlayer->getStats(), true);
			owningPlayer->getStats()->rva0039BAD2((Rva0039BAD2Input *)what, cost);
			obj->m_buildCost = (Real)cost;
		}
	}

	Object *self = getObject();
	if (self && self->m_value45C)
		TheGameLogic->rva0023D0C2(obj, self->m_value45C);
	obj->m_upgrades._M_do_or(self->m_upgrades);
	obj->updateUpgradeModules();

	if (isRebuild)
		((Rva0028CBFD *)obj)->rva0028CBFD();

	return obj;
}
