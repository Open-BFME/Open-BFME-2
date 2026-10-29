// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
// platformsdk
//
// AutoHealBehavior::update (0x0045280B) and the file-static helpers retail
// places ahead of it (0x00452496..0x0045280B): the stretch BFME 1's
// AutoHealBehavior.cpp (reference/open-bfme-1 AutoHealBehavior_playerScan.cpp,
// retail 0x001EEDE0) compiles to. BFME 2 adds the contained-units path, the
// horde respawn pass, splits the in-combat test out of the eligibility test
// and passes the scan data's 28-byte kind-of mask. The combat and eligibility
// tests are not address-taken, so VC7.1 gives them its private register
// convention (the object in ESI for the combat test; the candidate in EBX and
// the scan data in EDI for the eligibility test); they stay in one unit with
// their callers for that reason. The two callbacks are what update hands to
// Player::iterateObjects and ContainModuleInterface::iterateContained.
//
// Layout facts are the target's: Object +0x250/+0x254/+0x258/+0x274/+0x438
// as the rowed Object accessors read them, the body module slots as the rowed
// BodyModule vftables order them, the module data offsets from the rowed
// AutoHealBehaviorModuleData ctor and its field parse table, the behavior's
// from the rowed ctor (0x00452592) and onDamage (0x0045266B). Names follow
// the BFME 1 donor and Zero Hour where the body agrees with them.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include <windows.h>
#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"
#include "PartitionRangeQueryCallView.h"
#include "ascii_string.h"
#include <string.h>

// The AsciiString.cpp predicate (0x00001E2F), visible so update keeps the
// animation-name address and the collection in retail's registers across it.
template <typename CHAR>
bool StringBase<CHAR>::isEmpty() const throw()
{
	return m_data == 0 || m_data->length == 0;
}

class ModuleData;
class Matrix3D;
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond; // logic frames per second

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

// ObjectPointerList is the pooled list policy (header from the freelist at
// 0x00DB8FEC) the rowed ctor 0x001EB984, clear 0x001EB130, base dtor
// 0x001EB769 and list dtor 0x001EB940 implement; push_back is 0x001EC03C.
class Object;
class Rva001EB130Holder { public: void rva001EB130(); };
class Rva001EB769 { public: void rva001EB769() throw(); };
template <class T> class Rva001EB984PoolAllocator
{
public:
	Rva001EB984PoolAllocator() {}
};
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
};

template <class T, class A = allocator<T> > class list
{
public:
	void push_back(const T &x);
};

template <class T, class A> class _List_base;
template <> class _List_base<Object *, Rva001EB984PoolAllocator<Object *> >
{
public:
	_List_base(const Rva001EB984PoolAllocator<Object *> &a);
	~_List_base() throw(); // pinned 0x001EB769 body, emitted by HordeContainRva00475F61.cpp
	__declspec(dllimport) __forceinline void clear() { ((Rva001EB130Holder *)this)->rva001EB130(); }
protected:
	_List_node<Object *> *_M_node;
};

template <> class list<Object *, Rva001EB984PoolAllocator<Object *> >
	: public _List_base<Object *, Rva001EB984PoolAllocator<Object *> >
{
public:
	struct iterator
	{
		_List_node<Object *> *_M_node;
		Object *&operator*() const { return _M_node->_M_data; }
		iterator &operator++() { _M_node = _M_node->_M_next; return *this; }
		bool operator!=(const iterator &that) const { return _M_node != that._M_node; }
	};
	list(const Rva001EB984PoolAllocator<Object *> &a = Rva001EB984PoolAllocator<Object *>())
		: _List_base<Object *, Rva001EB984PoolAllocator<Object *> >(a) {}
	iterator begin() { iterator it; it._M_node = _M_node->_M_next; return it; }
	iterator end() { iterator it; it._M_node = _M_node; return it; }
	void push_back(Object *const &x); // pinned 0x001EC03C body, emitted by HordeContainRva00475F61.cpp
};
}

typedef _STL::list<Object *, Rva001EB984PoolAllocator<Object *> > ObjectPointerList;

class ThingTemplate
{
public:
	__declspec(dllimport) __forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }
private:
	char m_pad00[0x108];
	unsigned char m_kindof[32]; // +0x108
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	__declspec(dllimport) __forceinline Bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
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

// What Object::rva0028C197 returns for a horde: slot 95 is the member cap,
// slot 98 the member count, slot 99 spawns a member at the given transform.
class HordeRespawnInterface : public AutoHealSlots<95>
{
public:
	virtual UnsignedInt rvaSlot95(); // +0x17C
	virtual void gap96();
	virtual void gap97();
	virtual UnsignedInt rvaSlot98(); // +0x188
	virtual Object *rvaSlot99(const Matrix3D *transform); // +0x18C
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
	__declspec(dllimport) __forceinline Bool isOffMap() const { return (m_privateStatus & 8) != 0; }
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
class Anim2DCollection;
// The 0x002D752D lookup is owned by this existing call-only view.
struct Rva002D752DNode;
class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);
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
extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData
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

#include "../../../../Include/Common/ObjectModule.h"

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
	void pulseHealObject(Object *obj, Bool playFX);
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
				if (body->getLastDamageTimestamp() + BfmeLogicFramesPerSecond > now)
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
void Rva00452795CollectContained(Object *obj, void *userData)
{
	if (obj->isKindOf(KINDOF_HORDE))
		obj->getContain()->iterateContained(Rva00452795CollectContained, userData, true);
	else if (obj->getBodyModule()->getHealthRatio() < 1.0f)
		((ObjectPointerList *)userData)->push_back(obj);
}

// ?checkForAutoHeal@@YAHPAVObject@@PAX@Z @0x004527E5
Int checkForAutoHeal(Object *testObj, void *userData)
{
	AutoHealPlayerScanHelper *helper = (AutoHealPlayerScanHelper *)userData;
	if (Rva004524E5ShouldHeal(testObj, helper))
		helper->m_objectList->push_back(testObj);
	return 1;
}

// Coord3D::set as the icon block inlines it.
static inline void setCoord(Coord3D *c, Real x, Real y, Real z)
{
	c->x = x;
	c->y = y;
	c->z = z;
}

// ?update@AutoHealBehavior@@UAE?AW4UpdateSleepTime@@XZ @0x0045280B
// Zero Hour's update plus BFME 2's in-combat delay, heal bonus, contained
// units and horde respawn pass.
UpdateSleepTime AutoHealBehavior::update()
{
	if (m_stopped)
		return UPDATE_SLEEP_FOREVER;

	const AutoHealBehaviorModuleData *autoHealBehaviorModuleData = getAutoHealBehaviorModuleData();
	Object *obj = getObject();

	// do not heal if our status bit is not on.
	// do not heal if our status is effectively dead.  There ain't no coming back, man!
	if (!isUpgradeActive() || obj->isEffectivelyDead())
		return UPDATE_SLEEP_FOREVER;

//DEBUG_LOG(("doing auto heal %d\n",TheGameLogic->getFrame()));

	if (autoHealBehaviorModuleData->m_healOnlyIfNotInCombat && Rva00452496Check(obj))
	{
		UnsignedInt delay = autoHealBehaviorModuleData->m_startHealingDelay;
		if (delay > 0)
			return (UpdateSleepTime)delay;
		return (UpdateSleepTime)BfmeLogicFramesPerSecond;
	}

	Real bonus;
	obj->rva0028C149(0x13, &bonus, 0);
	Int healAmount = (Int)((Real)autoHealBehaviorModuleData->m_healingAmount + bonus);
	if (healAmount <= 0)
		return UPDATE_SLEEP_NONE;

	if (autoHealBehaviorModuleData->m_affectsWholePlayer)
	{
		// Even newer system, I can ignore radius and iterate objects on the owning player.  Faster than scanning range 10,000,000
		ObjectPointerList objectsToHeal;
		Player *owningPlayer = getObject()->getControllingPlayer();
		if (owningPlayer)
		{
			AutoHealPlayerScanHelper helper;
			helper.m_kindOfToTest = autoHealBehaviorModuleData->m_kindOf;
			helper.m_objectList = &objectsToHeal;
			helper.m_theHealer = getObject();
			helper.m_healOnlyIfNotUnderAttack = autoHealBehaviorModuleData->m_healOnlyIfNotUnderAttack;
			helper.m_healOnlyIfNotInCombat = autoHealBehaviorModuleData->m_healOnlyIfNotInCombat;
			helper.m_healOnlyOthers = autoHealBehaviorModuleData->m_healOnlyOthers;

			// Smack all objects with this function, and we will end up with a list of Objects deserving of pulseHealObject
			owningPlayer->iterateObjects(checkForAutoHeal, &helper);

			for (ObjectPointerList::iterator it = objectsToHeal.begin(); it != objectsToHeal.end(); ++it)
				pulseHealObject(*it, true);
			objectsToHeal.clear();
		}
		return (UpdateSleepTime)autoHealBehaviorModuleData->m_healingDelay;
	}
	else if (autoHealBehaviorModuleData->m_affectsContained)
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
				pulseHealObject(*it, playFX);
		}
	}
	else if (autoHealBehaviorModuleData->m_radius == 0)
	{
		//ORIGINAL SYSTEM -- JUST HEAL SELF!

		// do not heal if we are at max health already
		BodyModuleInterface *body = obj->getBodyModule();
		if (body->getHealth() < body->getMaxHealth())
		{
			pulseHealObject(obj, true);
			return (UpdateSleepTime)autoHealBehaviorModuleData->m_healingDelay;
		}
		// go to sleep forever -- we'll wake back up when we are damaged again
		return UPDATE_SLEEP_FOREVER;
	}
	else
	{
		//EXPANDED SYSTEM -- HEAL FRIENDLIES IN RADIUS
		Bool respawnReady = TheGameLogic->getFrame() >= autoHealBehaviorModuleData->m_respawnMinimumDelay + m_lastRespawnFrame;
		// setup scan filters
		// scan objects in our region
		BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(obj->getPosition(),
			(Real)autoHealBehaviorModuleData->m_radius, 0,
			Rva00260EB1Filter(obj, ALLOW_ALLIES, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))),
			0);
		Object *other;
		while ((other = iter.next()) != NULL)
		{
			if (other->isAnyKindOf(autoHealBehaviorModuleData->m_kindOf))
			{
				// do not heal if we are at max health already
				BodyModuleInterface *body = other->getBodyModule();
				if (body->getHealth() < body->getMaxHealth())
				{
					AutoHealPlayerScanHelper helper;
					helper.m_kindOfToTest = autoHealBehaviorModuleData->m_kindOf;
					helper.m_objectList = NULL;
					helper.m_theHealer = getObject();
					helper.m_healOnlyIfNotUnderAttack = autoHealBehaviorModuleData->m_healOnlyIfNotUnderAttack;
					helper.m_healOnlyIfNotInCombat = autoHealBehaviorModuleData->m_healOnlyIfNotInCombat;
					helper.m_healOnlyOthers = autoHealBehaviorModuleData->m_healOnlyOthers;
					if (Rva004524E5ShouldHeal(other, &helper))
					{
						pulseHealObject(other, true);

						if (autoHealBehaviorModuleData->m_singleBurst && TheGameLogic->getDrawIconUI())
						{
							if (TheAnim2DCollection)
							{
								const AsciiString &animName = TheGlobalData->m_getHealedAnimationName;
								if (!((const StringBase<char> *)&animName)->isEmpty())
								{
									Anim2DTemplate *animTemplate = (Anim2DTemplate *)((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&animName);

									if (animTemplate)
									{
										Coord3D iconPosition;
										setCoord(&iconPosition, other->getPosition()->x,
											other->getPosition()->y,
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
			}
			if (respawnReady && autoHealBehaviorModuleData->m_respawnNearbyHordeMembers && other->isKindOf(KINDOF_HORDE)
				&& !other->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
			{
				HordeRespawnInterface *horde = (HordeRespawnInterface *)other->rva0028C197();
				if (horde)
				{
					UnsignedInt cap = horde->rvaSlot95();
					UnsignedInt count = horde->rvaSlot98();
					if (count < cap)
					{
						Object *member = horde->rvaSlot99(other->getTransformMatrix());
						if (member)
						{
							member->updateShroudNow();
							if (autoHealBehaviorModuleData->m_respawnFXList)
								FXList::doFXObj(autoHealBehaviorModuleData->m_respawnFXList, member, NULL);
						}
					}
				}
			}
		}  // end for obj
		if (respawnReady)
			m_lastRespawnFrame = TheGameLogic->getFrame();
	}
	return autoHealBehaviorModuleData->m_singleBurst ? UPDATE_SLEEP_FOREVER : (UpdateSleepTime)autoHealBehaviorModuleData->m_healingDelay;
}
