// ?update@AutoHealBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.86 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
//
// BANKED NEAR MISS (update 0x0045280B, 1342 B): compiles 1356 B, frame 0x9c vs
// retail 0x98, 181 byte diffs. Needs GameLogicObjectLookupView.h extended with
//   char pad44[0x9A - 0x44]; bool m_drawIconUI; char pad9B[0xB4 - 0x9B];
//   bool getDrawIconUI() const { return m_drawIconUI; }
// The helpers (Check/ShouldHeal/CollectContained/checkForAutoHeal) are rowed
// in AutoHealBehaviorPlayerScan.cpp; landing update means moving it there.
// Open: (1) retail calls horde slot 95 (+0x17C) before slot 98 (+0x188) and
// spills slot95 to [ebp-0x24]; a direct pair of virtual calls evaluates the
// higher slot first and every 95-first form swaps horde/other registers;
// (2) dead spill of horde to [ebp-0x34]; (3) bonus at -0x30 vs -0x38 and
// filterB -0x3c vs -0x34; (4) icon block esi/edi swapped (retail esi =
// collection). Fixed: cmp eax,edi via the named Int healAmount local, setCoord
// arg order, ~_List_base throw(), function-scope bonus slot order.
//
// AutoHealBehavior::update and the file-static helpers retail places ahead
// of it (0x00452496..0x00452D49), the stretch BFME 1's AutoHealBehavior.cpp
// (reference/open-bfme-1 AutoHealBehavior_playerScan.cpp, retail 0x001EEDE0)
// compiles to. BFME 2 adds the contained-units path, the horde respawn pass
// and a separate in-combat test, and passes the scan data's 28-byte kind-of
// mask. The static helpers are not address-taken, so VC7.1 gives them its
// private register convention (the object in ESI for the combat test; the
// candidate in EBX and the scan data in EDI for the eligibility test); they
// stay in this unit with their callers for that reason.
//
// Layout facts are the target's: the module data offsets come from the rowed
// AutoHealBehaviorModuleData ctor and its field parse table, the behavior's
// from the rowed ctor (0x00452592) and onDamage (0x0045266B). Names follow
// the BFME 1 donor and Zero Hour where the body agrees with them.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
#define NULL 0
#define TRUE 1
#define FALSE 0

#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"
#include "PartitionRangeQueryCallView.h"
#include "ascii_string.h"

#include <string.h>

class Thing;
class ModuleData;
class Matrix3D;
class FXList;

extern GameLogic *TheGameLogic;
extern Int g_Va00DBA4E4; // logic frames per second

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2
};

// KindOf bits by the retail name table at 0x00DBBE18.
enum KindOfType
{
	KINDOF_HORDE = 0x6D
};

// The 28-byte kind-of mask; its default ctor clears it through memset.
template <int N> class BitFlags
{
public:
	BitFlags() { memset(m_bits, 0, sizeof(m_bits)); }
private:
	UnsignedInt m_bits[7];
};
typedef BitFlags<69> KindOfMaskType;

// STLport list<Object*> as this unit uses it: the base ctor, clear, base
// dtor and push_back are retail's out-of-line instantiations (0x001EB984,
// 0x001EB130, 0x001EB769, 0x001EC03C).
namespace _STL
{
template <class T> struct _List_node
{
	_List_node *_M_next;
	_List_node *_M_prev;
	T _M_data;
};

template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A> class _List_base
{
public:
	_List_base(const A &a);
	~_List_base() throw();
	void clear();
protected:
	_List_node<T> *_M_node;
};

template <class T, class A = allocator<T> > class list : public _List_base<T, A>
{
public:
	struct iterator
	{
		_List_node<T> *_M_node;
		T &operator*() const { return _M_node->_M_data; }
		iterator &operator++() { _M_node = _M_node->_M_next; return *this; }
		bool operator!=(const iterator &that) const { return _M_node != that._M_node; }
	};

	explicit list(const A &a = A()) : _List_base<T, A>(a) {}
	iterator begin() { iterator it; it._M_node = this->_M_node->_M_next; return it; }
	iterator end() { iterator it; it._M_node = this->_M_node; return it; }
	void push_back(const T &x);
};
}

class Object;
typedef _STL::list<Object *> ObjectPointerList;

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }
private:
	char m_pad00[0x108];
	unsigned char m_kindof[32]; // +0x108
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline Bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	Bool isAnyKindOf(const KindOfMaskType &anyKindOf) const;
	const Coord3D *getPosition() const { return &m_pos; }
	const Matrix3D *getTransformMatrix() const { return (const Matrix3D *)m_transform; }
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	char m_transform[0x30]; // +0x08
	Coord3D m_pos; // +0x38
	Real m_angle; // +0x44
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage();
	virtual void attemptHealing();
	virtual void estimateDamage();
	virtual void i03();
	virtual Real getHealth() const; // +0x10
	virtual Real getHealthRatio() const; // +0x14
	virtual Real getMaxHealth() const; // +0x18
	virtual void i07();
	virtual void i08();
	virtual void i09();
	virtual void i10();
	virtual void i11();
	virtual void i12();
	virtual void i13();
	virtual void i14();
	virtual void i15();
	virtual UnsignedInt getLastDamageTimestamp() const; // +0x40
};

// The 16-byte record the contain interface's slot 44 returns by value; bit
// 29 of its second word suppresses the per-unit heal FX.
struct ContainHealRecord
{
	UnsignedInt m_word0;
	UnsignedInt m_bits0 : 29;
	UnsignedInt m_noHealFX : 1;
	UnsignedInt m_bits30 : 2;
	UnsignedInt m_word2;
	UnsignedInt m_word3;
};

typedef void (*ContainIterateFunc)(Object *obj, void *userData);

template <int N> class AutoHealSlots : public AutoHealSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class AutoHealSlots<0>
{
};

// Object +0x250: slot 44 is the record above, slot 68 Zero Hour's
// iterateContained.
class ContainModuleInterface : public AutoHealSlots<44>
{
public:
	virtual ContainHealRecord rvaSlot44(Int unused); // +0xB0
	virtual void gap45();
	virtual void gap46();
	virtual void gap47();
	virtual void gap48();
	virtual void gap49();
	virtual void gap50();
	virtual void gap51();
	virtual void gap52();
	virtual void gap53();
	virtual void gap54();
	virtual void gap55();
	virtual void gap56();
	virtual void gap57();
	virtual void gap58();
	virtual void gap59();
	virtual void gap60();
	virtual void gap61();
	virtual void gap62();
	virtual void gap63();
	virtual void gap64();
	virtual void gap65();
	virtual void gap66();
	virtual void gap67();
	virtual void iterateContained(ContainIterateFunc func, void *userData, Bool reverse); // +0x110
};

// What Object::rva0028C197 returns for a horde: slot 95 against slot 98
// gates the respawn, slot 99 spawns a member at the given transform.
class HordeRespawnInterface : public AutoHealSlots<95>
{
public:
	virtual UnsignedInt rvaSlot95(); // +0x17C
	virtual void gap96();
	virtual void gap97();
	virtual UnsignedInt rvaSlot98(); // +0x188
	virtual Object *rvaSlot99(const Matrix3D *transform); // +0x18C

	// Retail calls slot 95 before slot 98; a direct pair of virtual calls
	// evaluates the higher slot first, an inline non-virtual reader does not.
	UnsignedInt getSlot95() { return rvaSlot95(); }
};

class Player
{
public:
	Int iterateObjects(Int (*func)(Object *, void *), void *userData) const;
};

class Object : public Thing
{
public:
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Bool isOffMap() const { return (m_privateStatus & 8) != 0; }
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
	// The attribute-modifier bonus query (0x13 is the heal amount).
	Bool rva0028C149(Int attribute, Real *value, Int arg);
	void *rva0028C197() const;
	void updateShroudNow();
private:
	char m_pad48[0xA8 - 0x48];
	GeometryInfo m_geometryInfo; // +0xA8
	char m_padA9[0x250 - 0xA9];
	ContainModuleInterface *m_contain; // +0x250
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy; // +0x274
	char m_pad278[0x438 - 0x278];
	unsigned char m_privateStatus; // +0x438
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary = NULL);
};

class Anim2DTemplate;

class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};
extern Anim2DCollection *TheAnim2DCollection;

enum WorldAnimationOptions
{
	WORLD_ANIM_NO_OPTIONS = 0x00,
	WORLD_ANIM_FADE_ON_EXPIRE = 0x01
};

class InGameUI
{
public:
	void addWorldAnimation(Anim2DTemplate *animTemplate, const Coord3D *pos,
		WorldAnimationOptions options, Real durationInSeconds, Real zRisePerSecond);
};
extern InGameUI *TheInGameUI;

class GlobalData
{
public:
	char m_pad00[0x128];
	AsciiString m_getHealedAnimationName; // +0x128
	Real m_getHealedAnimationDisplayTimeInSeconds; // +0x12C
	Real m_getHealedAnimationZRisePerSecond; // +0x130
};
extern GlobalData *TheGlobalData;

extern PartitionManager *ThePartitionManager;

// BFME 2's partition filters (the view AITNGuardScan.cpp documents).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next); // 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFBC90 (Zero Hour's PartitionFilterRelationship): the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// vftable 0x00BFAD10: not effectively dead (Zero Hour's PartitionFilterAlive).
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC (Zero Hour's PartitionFilterSameMapStatus).
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

enum
{
	ALLOW_ALLIES = 1 << 2
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	Object *getObject() const { return m_object; }
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

// +0x20: slot 0 reads the upgrade-executed byte.
class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const;
private:
	Bool m_upgradeExecuted; // +0x04
};

class DamageInfo;

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
};

class AutoHealBehaviorModuleData
{
public:
	char m_pad00[0x118];
	Bool m_initiallyActive; // +0x118 StartsActive
	Bool m_buttonTriggered; // +0x119
	Bool m_singleBurst; // +0x11A
	Int m_healingAmount; // +0x11C
	UnsignedInt m_healingDelay; // +0x120
	UnsignedInt m_startHealingDelay; // +0x124
	Int m_radius; // +0x128
	Bool m_affectsWholePlayer; // +0x12C
	Bool m_affectsContained; // +0x12D
	Bool m_healOnlyIfNotUnderAttack; // +0x12E
	Bool m_healOnlyIfNotInCombat; // +0x12F
	KindOfMaskType m_kindOf; // +0x130
	Bool m_healOnlyOthers; // +0x14C
	const FXList *m_unitHealPulseFX; // +0x150
	Bool m_nonStackable; // +0x154
	Bool m_respawnNearbyHordeMembers; // +0x155
	const FXList *m_respawnFXList; // +0x158
	UnsignedInt m_respawnMinimumDelay; // +0x15C
};

class AutoHealBehavior : public UpdateModule, public UpgradeMux, public DamageModuleInterface
{
public:
	virtual UpdateSleepTime update();
	// Zero Hour's pulseHealObject with BFME 2's FX flag.
	void rva004526C6(Object *obj, Bool playFX);
	Bool isUpgradeActive() const { return isAlreadyUpgraded(); }
	const AutoHealBehaviorModuleData *getAutoHealBehaviorModuleData() const
	{
		return (const AutoHealBehaviorModuleData *)m_moduleData;
	}
private:
	UnsignedInt m_soonestHealFrame; // +0x2C
	Bool m_stopped; // +0x30
	UnsignedInt m_lastRespawnFrame; // +0x34
};

// The scan data checkForAutoHeal and the radius scan hand the eligibility test.
struct AutoHealPlayerScanHelper
{
	KindOfMaskType m_kindOfToTest; // +0x00
	Object *m_theHealer; // +0x1C
	ObjectPointerList *m_objectList; // +0x20
	Bool m_healOnlyIfNotUnderAttack; // +0x24
	Bool m_healOnlyIfNotInCombat; // +0x25
	Bool m_healOnlyOthers; // +0x26
};

// ?Rva00452496Check@@YA_NPAVObject@@@Z @0x00452496
// True while obj's AI has a victim, or obj sits in a horde whose AI has one.
static Bool Rva00452496Check(Object *obj)
{
	if (!obj)
		return false;
	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (ai && ai->getCurrentVictim() != 0)
		return true;
	Object *container = obj->getContainedBy();
	return container
		&& container->isKindOf(KINDOF_HORDE)
		&& container->getAIUpdateInterface() != 0
		&& container->getAIUpdateInterface()->getCurrentVictim() != 0;
}

// ?Rva004524E5ShouldHeal@@YA_NPAVObject@@PBUAutoHealPlayerScanHelper@@@Z @0x004524E5
// BFME 1's eligibility test (0x001EE670) with the in-combat test split out.
static Bool Rva004524E5ShouldHeal(Object *testObj, const AutoHealPlayerScanHelper *helper)
{
	if (helper->m_healOnlyOthers && testObj == helper->m_theHealer)
		return false;

	Object *healer = helper->m_theHealer;
	if (healer)
	{
		if (helper->m_healOnlyIfNotInCombat && Rva00452496Check(healer))
			return false;

		// Damaged within the last second (BFME 1 waits five frames).
		if (helper->m_healOnlyIfNotUnderAttack)
		{
			BodyModuleInterface *body = helper->m_theHealer->getBodyModule();
			UnsignedInt now = TheGameLogic->getFrame();
			if (body->getLastDamageTimestamp() < now)
			{
				body = helper->m_theHealer->getBodyModule();
				now = TheGameLogic->getFrame();
				if (body->getLastDamageTimestamp() + g_Va00DBA4E4 > now)
					return false;
			}
		}
	}

	if (testObj->isEffectivelyDead())
		return false;
	if (testObj->isOffMap())
		return false;
	if (!testObj->isAnyKindOf(helper->m_kindOfToTest))
		return false;

	BodyModuleInterface *body = testObj->getBodyModule();
	if (body->getHealth() >= body->getMaxHealth())
		return false;
	return true;
}

// ?Rva00452795CollectContained@@YAXPAVObject@@PAX@Z @0x00452795
// Gathers the hurt units of a container, descending into hordes.
static void Rva00452795CollectContained(Object *obj, void *userData)
{
	if (obj->isKindOf(KINDOF_HORDE))
		obj->getContain()->iterateContained(Rva00452795CollectContained, userData, true);
	else if (obj->getBodyModule()->getHealthRatio() < 1.0f)
		((ObjectPointerList *)userData)->push_back(obj);
}

// ?checkForAutoHeal@@YAHPAVObject@@PAX@Z @0x004527E5
static Int checkForAutoHeal(Object *testObj, void *userData)
{
	AutoHealPlayerScanHelper *helper = (AutoHealPlayerScanHelper *)userData;
	if (Rva004524E5ShouldHeal(testObj, helper))
		helper->m_objectList->push_back(testObj);
	return 1;
}

// ?update@AutoHealBehavior@@UAE?AW4UpdateSleepTime@@XZ @0x0045280B
static inline void setCoord(Coord3D *c, Real x, Real y, Real z)
{
	c->x = x;
	c->y = y;
	c->z = z;
}

static inline Int calcHealAmount(Object *obj, const AutoHealBehaviorModuleData *d)
{
	Real bonus;
	obj->rva0028C149(0x13, &bonus, 0);
	return (Int)((Real)d->m_healingAmount + bonus);
}

UpdateSleepTime AutoHealBehavior::update()
{
	Real bonus;
	if (m_stopped)
		return UPDATE_SLEEP_FOREVER;

	const AutoHealBehaviorModuleData *d = getAutoHealBehaviorModuleData();
	Object *obj = getObject();

	if (!isUpgradeActive() || obj->isEffectivelyDead())
		return UPDATE_SLEEP_FOREVER;

	if (d->m_healOnlyIfNotInCombat && Rva00452496Check(obj))
	{
		UnsignedInt delay = d->m_startHealingDelay;
		if (delay > 0)
			return (UpdateSleepTime)delay;
		return (UpdateSleepTime)g_Va00DBA4E4;
	}

	obj->rva0028C149(0x13, &bonus, 0);
	Int healAmount = (Int)((Real)d->m_healingAmount + bonus);
	if (healAmount <= 0)
		return UPDATE_SLEEP_NONE;

	if (d->m_affectsWholePlayer)
	{
		ObjectPointerList objectsToHeal;
		Player *owningPlayer = getObject()->getControllingPlayer();
		if (owningPlayer)
		{
			AutoHealPlayerScanHelper helper;
			helper.m_kindOfToTest = d->m_kindOf;
			helper.m_objectList = &objectsToHeal;
			helper.m_theHealer = getObject();
			helper.m_healOnlyIfNotUnderAttack = d->m_healOnlyIfNotUnderAttack;
			helper.m_healOnlyIfNotInCombat = d->m_healOnlyIfNotInCombat;
			helper.m_healOnlyOthers = d->m_healOnlyOthers;
			owningPlayer->iterateObjects(checkForAutoHeal, &helper);

			for (ObjectPointerList::iterator it = objectsToHeal.begin(); it != objectsToHeal.end(); ++it)
				rva004526C6(*it, true);
			objectsToHeal.clear();
		}
		return (UpdateSleepTime)d->m_healingDelay;
	}
	else if (d->m_affectsContained)
	{
		ContainModuleInterface *contain = obj->getContain();
		if (!contain && obj->getContainedBy())
			contain = obj->getContainedBy()->getContain();
		if (contain)
		{
			ObjectPointerList objectsToHeal;
			contain->iterateContained(Rva00452795CollectContained, &objectsToHeal, true);
			Bool playFX = !contain->rvaSlot44(0).m_noHealFX;
			for (ObjectPointerList::iterator it = objectsToHeal.begin(); it != objectsToHeal.end(); ++it)
				rva004526C6(*it, playFX);
		}
	}
	else if (d->m_radius == 0)
	{
		BodyModuleInterface *body = obj->getBodyModule();
		if (body->getHealth() < body->getMaxHealth())
		{
			rva004526C6(obj, true);
			return (UpdateSleepTime)d->m_healingDelay;
		}
		return UPDATE_SLEEP_FOREVER;
	}
	else
	{
		Bool respawnReady = TheGameLogic->getFrame() >= d->m_respawnMinimumDelay + m_lastRespawnFrame;

		BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(obj->getPosition(),
			(Real)d->m_radius, 0,
			Rva00260EB1Filter(obj, ALLOW_ALLIES, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))),
			0);

		Object *other;
		while ((other = iter.next()) != NULL)
		{
			if (other->isAnyKindOf(d->m_kindOf))
			{
				BodyModuleInterface *body = other->getBodyModule();
				if (body->getHealth() < body->getMaxHealth())
				{
					AutoHealPlayerScanHelper helper;
					helper.m_kindOfToTest = d->m_kindOf;
					helper.m_objectList = NULL;
					helper.m_theHealer = getObject();
					helper.m_healOnlyIfNotUnderAttack = d->m_healOnlyIfNotUnderAttack;
					helper.m_healOnlyIfNotInCombat = d->m_healOnlyIfNotInCombat;
					helper.m_healOnlyOthers = d->m_healOnlyOthers;
					if (Rva004524E5ShouldHeal(other, &helper))
					{
						rva004526C6(other, true);

						Anim2DCollection *collection;
						if (d->m_singleBurst && TheGameLogic->getDrawIconUI() && (collection = TheAnim2DCollection) != NULL)
						{
							const AsciiString &animName = TheGlobalData->m_getHealedAnimationName;
							if (!((const StringBase<char> *)&animName)->isEmpty())
							{
								Anim2DTemplate *animTemplate = collection->findTemplate(animName);
								if (animTemplate)
								{
									Coord3D iconPosition;
									setCoord(&iconPosition, other->getPosition()->x, other->getPosition()->y,
										other->getPosition()->z + other->getGeometryInfo().getMaxHeightAbovePosition());
									TheInGameUI->addWorldAnimation(animTemplate, &iconPosition, WORLD_ANIM_FADE_ON_EXPIRE,
										TheGlobalData->m_getHealedAnimationDisplayTimeInSeconds,
										TheGlobalData->m_getHealedAnimationZRisePerSecond);
								}
							}
						}
					}
				}
			}

			if (respawnReady && d->m_respawnNearbyHordeMembers && other->isKindOf(KINDOF_HORDE)
				&& !other->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
			{
				HordeRespawnInterface *horde = (HordeRespawnInterface *)other->rva0028C197();
				if (horde && horde->rvaSlot98() < horde->rvaSlot95())
				{
					Object *member = horde->rvaSlot99(other->getTransformMatrix());
					if (member)
					{
						member->updateShroudNow();
						if (d->m_respawnFXList)
							FXList::doFXObj(d->m_respawnFXList, member, NULL);
					}
				}
			}
		}

		if (respawnReady)
			m_lastRespawnFrame = TheGameLogic->getFrame();
	}

	return d->m_singleBurst ? UPDATE_SLEEP_FOREVER : (UpdateSleepTime)d->m_healingDelay;
}
