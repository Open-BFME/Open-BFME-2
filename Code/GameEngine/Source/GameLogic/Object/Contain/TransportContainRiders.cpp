// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
// stlport
//
// Zero Hour TransportContain's rider-exit pair as BFME 2 builds it. Both are
// TransportContain vtable 0x00844278 slots: killRidersWhoAreNotFreeToExit is
// slot 25 (OpenContain's empty hook, ZH order after addOrRemoveObjFromWorld)
// and calls isSpecificRiderFreeToExit through slot 27.
//
// Target facts: the module data at this+0x04 and the object at this+0x08;
// Object's AI at +0x258 with the current locomotor at AI+0x1F0 (as the rowed
// Object::isUsingAirborneLocomotor reads them); getAiFreeToExit at AI vtable
// +0x1A8; TerrainLogic::isUnderwater at TheTerrainLogic vtable +0x4C with
// BFME 2's fifth argument (the rowed Thing::getHeightAboveTerrainOrWater);
// the pathfinder at TheAI+0x10. Donor facts: names, FREE_TO_EXIT == 0 and
// m_destroyRidersWhoAreNotFreeToExit (here at module data +0x142). BFME 2
// adds the KindOf 0xBF water test before ZH's validMovementTerrain and
// iterates a copy of the contain list taken through the OpenContain pair
// helper 0x0046247D and list reader 0x0036AE51 (as OpenContain slot 18
// 0x00464286 does).
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
#define NULL 0
#define TRUE true
#define FALSE false

#include <list>

#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"

typedef _STL::list<int, _STL::allocator<int> > IntList;

namespace _STL
{
template<> _List_base<int, allocator<int> >::~_List_base();
}

extern GameLogic *TheGameLogic;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

enum AIFreeToExitType
{
	FREE_TO_EXIT = 0
};

enum KindOfType
{
	// Bit 7 of the KindOf byte at template+0x11F (see
	// AIUpdateInterfacePrivateCommands.cpp); its name is not evidenced.
	BFME_KINDOF_BF = 0xBF
};

class Locomotor;

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }
private:
	char m_pad00[0x108];
	unsigned char m_kindof[32]; // +0x108
};

class AIUpdateInterface;

// The 28-byte kind-of mask.
template <int N> class BitFlags
{
private:
	unsigned int m_bits[7];
};
typedef BitFlags<116> KindOfMaskType;
extern KindOfMaskType KINDOFMASK_NONE;

enum WeaponSetType
{
	// The two weapon sets BFME 2's transports grant by rider kind; ZH grants
	// WEAPONSET_PLAYER_UPGRADE from armed riders.
	BFME_WEAPONSET_4 = 4,
	BFME_WEAPONSET_5 = 5
};

// Object::getWeaponSetFlags (lea eax,[ecx+0x370]); the row keeps its
// address-derived name.
class Rva0028B7AELeaGetter
{
public:
	void *get() const;
};

class Matrix3D
{
public:
	Real Row[3][4];
};

class Vector3
{
public:
	Vector3() {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3 &operator-=(const Vector3 &v) { X -= v.X; Y -= v.Y; Z -= v.Z; return *this; }
	Real X;
	Real Y;
	Real Z;
};

// WWMath's Matrix3D * Vector3 and Get_Translation.
static inline Vector3 operator*(const Matrix3D &A, const Vector3 &a)
{
	return Vector3(
		(A.Row[0][0] * a.X + A.Row[0][1] * a.Y + A.Row[0][2] * a.Z + A.Row[0][3]),
		(A.Row[1][0] * a.X + A.Row[1][1] * a.Y + A.Row[1][2] * a.Z + A.Row[1][3]),
		(A.Row[2][0] * a.X + A.Row[2][1] * a.Y + A.Row[2][2] * a.Z + A.Row[2][3]));
}

static inline Vector3 getTranslation(const Matrix3D &A)
{
	return Vector3(A.Row[0][3], A.Row[1][3], A.Row[2][3]);
}

// Coord3D::set; its arguments are evaluated right to left.
static inline void setCoord(Coord3D *c, Real x, Real y, Real z)
{
	c->x = x;
	c->y = y;
	c->z = z;
}

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline Bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	Bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const;
	const Coord3D *getPosition() const { return &m_pos; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	Matrix3D m_transform; // +0x08
	Coord3D m_pos; // +0x38
	char m_pad44[0x48 - 0x44];
};

// Object's model-condition words at +0x10C.
class ModelConditionFlags
{
public:
	unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 0x1f); }
private:
	unsigned int m_words[4];
};

enum ModelConditionFlagType
{
	// Word 3 bit 31 of the Object's condition words; set on a thrown-out
	// passenger. Unnamed.
	BFME_MODELCONDITION_7F = 0x7F
};

class PhysicsBehavior
{
public:
	void rva00390629(Bool value); // Zero Hour's setAllowToFall
};

// PhysicsBehavior 0x003909FA keeps its address-derived pin name.
class Rva003909FAObj
{
public:
	void consume(void *force, int a, int b);
};

class Object : public Thing
{
public:
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Bool isUsingAirborneLocomotor() const;
	Int rva0028B511() const; // Zero Hour's getLayer
	void kill(DamageType damageType = DAMAGE_UNRESISTABLE, DeathType deathType = DEATH_NORMAL);
	const unsigned int *getWeaponSetFlags() const { return (const unsigned int *)((const Rva0028B7AELeaGetter *)this)->get(); }
	Bool testWeaponSetFlag(WeaponSetType wst) const { return ((*getWeaponSetFlags() >> wst) & 1) != 0; }
	void setWeaponSetFlag(WeaponSetType wst);
	void clearWeaponSetFlag(WeaponSetType wst);
	PhysicsBehavior *getPhysics() const { return m_physics; }
	void rva0028AE6D(); // the model-condition change notifier
	__forceinline void setModelConditionState(ModelConditionFlagType c)
	{
		if (!m_conditionFlags.test(c))
		{
			m_conditionFlags.set(c);
			rva0028AE6D();
		}
	}
private:
	char m_pad48[0x10C - 0x48];
	ModelConditionFlags m_conditionFlags; // +0x10C
	char m_pad11C[0x258 - 0x11C];
	AIUpdateInterface *m_ai; // +0x258
	PhysicsBehavior *m_physics; // +0x25C
};

template <int N> class RiderSlots : public RiderSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class RiderSlots<0>
{
};

class AIUpdateInterface : public RiderSlots<106>
{
public:
	virtual AIFreeToExitType getAiFreeToExit(const Object *exiter) const; // +0x1A8
	Locomotor *getCurLocomotor() const { return m_curLocomotor; }
private:
	char m_pad04[0x1F0 - 0x04];
	Locomotor *m_curLocomotor; // +0x1F0
};

class TerrainLogic : public RiderSlots<19>
{
public:
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ, Real *terrainZ, Int unused); // +0x4C
};
extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Bool validMovementTerrain(PathfindLayerEnum layer, const Locomotor *locomotor, const Coord3D *pos);
	Bool getClosestPointOnLand(const Coord3D *pos, Object *obj, Coord3D *result);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;

// The pair OpenContain hands its list reader (see OpenContainRva00464286.cpp).
struct Rva0046247DPair
{
	void *present;
	struct CopyValue *source;
};

class Rva0046247D
{
public:
	void *rva0046247D(Rva0046247DPair &result);
};

class Rva0036AE51ListView
{
public:
	IntList rva0036AE51();
};

class TransportContainModuleData
{
public:
	char m_pad00[0xB0];
	KindOfMaskType m_typeOneForWeaponSet; // +0xB0 TypeOneForWeaponSet
	KindOfMaskType m_typeTwoForWeaponSet; // +0xCC TypeTwoForWeaponSet
	char m_padE8[0x142 - 0xE8];
	Bool m_destroyRidersWhoAreNotFreeToExit; // +0x142
	char m_pad143[0x158 - 0x143];
	Coord3D m_throwOutPassengersVelocity; // +0x158 ThrowOutPassengersVelocity
	const void *m_throwOutPassengersLandingWarhead; // +0x164 ThrowOutPassengersLandingWarhead
};

template <int N> class ContainSlots : public ContainSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class ContainSlots<1>
{
public:
	virtual void gap(char (*)[1]);
};

// OpenContain's ContainModuleInterface at +0x20.
class ContainModuleInterface : public ContainSlots<69>
{
public:
	virtual unsigned int getContainCount(Int unused) const; // +0x114
	virtual void gap70();
	virtual void gap71();
	virtual void gap72();
	virtual void gap73();
	virtual void gap74();
	virtual void gap75();
	virtual void gap76();
	virtual void gap77();
	virtual void gap78();
	virtual Object *rvaSlot79(Int unused); // +0x13C, hands out the next rider
};

class TransportContainBase : public RiderSlots<25>
{
protected:
	const TransportContainModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x20 - 0x0C];
};

class TransportContain : public TransportContainBase, public ContainModuleInterface
{
public:
	Object *getObject() const { return m_object; }
	const TransportContainModuleData *getTransportContainModuleData() const { return m_moduleData; }
protected:
	virtual void killRidersWhoAreNotFreeToExit(); // +0x64
	virtual void rvaSlot26();
	virtual Bool isSpecificRiderFreeToExit(Object *obj); // +0x6C
	virtual void createPayload(); // +0x70
	virtual void rva0046740C(); // +0x74
	virtual void letRidersUpgradeWeaponSet(); // +0x78
};

// ?killRidersWhoAreNotFreeToExit@TransportContain@@MAEXXZ @0x00467F3B
void TransportContain::killRidersWhoAreNotFreeToExit()
{
	const TransportContainModuleData *d = getTransportContainModuleData();
	Rva0046247DPair pair;
	IntList riders = ((Rva0036AE51ListView *)((Rva0046247D *)this)->rva0046247D(pair))->rva0036AE51();
	IntList::iterator it = riders.begin();
	while (it != riders.end())
	{
		Object *obj = (Object *)*it++;
		if (!isSpecificRiderFreeToExit(obj))
		{
			if (d->m_destroyRidersWhoAreNotFreeToExit)
				TheGameLogic->destroyObject(obj);
			else
				obj->kill();
		}
	}
}

// ?isSpecificRiderFreeToExit@TransportContain@@MAE_NPAVObject@@@Z @0x004671AC
Bool TransportContain::isSpecificRiderFreeToExit(Object *specificObject)
{
	if (specificObject == NULL)
		return TRUE;	// I can, in general, exit people.

	Object *me = getObject();

	// this is present solely for some transports to override, so that they can land before
	// allowing people to exit...
	const AIUpdateInterface *ai = me->getAIUpdateInterface();
	if (ai && ai->getAiFreeToExit(specificObject) != FREE_TO_EXIT)
		return FALSE;

	// I can always kick people out if I am in the air, I know what I'm doing
	if (me->isUsingAirborneLocomotor())
		return TRUE;

	if (!specificObject->getAIUpdateInterface())
		return FALSE;

	const Locomotor *hisLocomotor = specificObject->getAIUpdateInterface()->getCurLocomotor();
	if (hisLocomotor == NULL)
		return FALSE;

	const Coord3D *pos = me->getPosition();
	Coord3D myPosition;
	myPosition.x = pos->x;
	myPosition.y = pos->y;
	myPosition.z = pos->z;
	if (me->isKindOf(BFME_KINDOF_BF) && TheTerrainLogic->isUnderwater(myPosition.x, myPosition.y, NULL, NULL, 0))
	{
		Coord3D landPosition;
		landPosition.x = myPosition.x;
		landPosition.y = myPosition.y;
		landPosition.z = myPosition.z;
		if (!TheAI->pathfinder()->getClosestPointOnLand(&myPosition, me, &landPosition))
			return FALSE;
	}
	// He can't get to this spot naturally, so I can't force him there.  (amphib transport)
	else if (!TheAI->pathfinder()->validMovementTerrain((PathfindLayerEnum)me->rva0028B511(), hisLocomotor, &myPosition))
		return FALSE;

	return TRUE;
}

// ?letRidersUpgradeWeaponSet@TransportContain@@MAEXXZ @0x0046760D
void TransportContain::letRidersUpgradeWeaponSet()
{
	Object *self = getObject();
	const TransportContainModuleData *d = getTransportContainModuleData();

	Rva0046247DPair riders;
	((Rva0046247D *)this)->rva0046247D(riders);
	Bool anyRiderA = FALSE;
	Bool anyRiderB = FALSE;
	for (IntList::iterator it = ((IntList *)riders.source)->begin(); it != ((IntList *)riders.source)->end(); ++it)
	{
		Object *rider = (Object *)*it;
		if (rider->isKindOfMulti(d->m_typeOneForWeaponSet, KINDOFMASK_NONE))
			anyRiderA = TRUE;
		else if (rider->isKindOfMulti(d->m_typeTwoForWeaponSet, KINDOFMASK_NONE))
			anyRiderB = TRUE;
	}

	if (anyRiderA)
	{
		if (!self->testWeaponSetFlag(BFME_WEAPONSET_4))
			self->setWeaponSetFlag(BFME_WEAPONSET_4);
	}
	else if (self->testWeaponSetFlag(BFME_WEAPONSET_4))
		self->clearWeaponSetFlag(BFME_WEAPONSET_4);

	if (anyRiderB)
	{
		if (!self->testWeaponSetFlag(BFME_WEAPONSET_5))
			self->setWeaponSetFlag(BFME_WEAPONSET_5);
	}
	else if (self->testWeaponSetFlag(BFME_WEAPONSET_5))
		self->clearWeaponSetFlag(BFME_WEAPONSET_5);
}

// ?rva0046740C@TransportContain@@MAEXXZ @0x0046740C
// Throws every passenger out at ThrowOutPassengersVelocity (taken into the
// transport's frame) with ThrowOutPassengersLandingWarhead.
void TransportContain::rva0046740C()
{
	UnsignedInt count = getContainCount(0);
	if (count > 0)
	{
		const TransportContainModuleData *d = getTransportContainModuleData();
		Object *me = getObject();
		const Matrix3D *mtx = me->getTransformMatrix();
		Coord3D velocity;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		velocity.z = 0.0f;
		Vector3 in(d->m_throwOutPassengersVelocity.x, d->m_throwOutPassengersVelocity.y, d->m_throwOutPassengersVelocity.z);
		Vector3 v = *mtx * in;
		v -= getTranslation(*mtx);
		setCoord(&velocity, v.X, v.Y, v.Z);
		for (UnsignedInt i = 0; i < count; ++i)
		{
			Object *rider = rvaSlot79(0);
			PhysicsBehavior *physics = rider->getPhysics();
			if (physics)
			{
				((Rva003909FAObj *)physics)->consume(&velocity, (int)me, (int)d->m_throwOutPassengersLandingWarhead);
				physics->rva00390629(TRUE);
				rider->setModelConditionState(BFME_MODELCONDITION_7F);
			}
		}
	}
}
