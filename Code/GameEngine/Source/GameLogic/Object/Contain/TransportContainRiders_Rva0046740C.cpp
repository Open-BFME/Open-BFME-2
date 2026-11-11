// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
// platformsdk
// stlport
// Split from TransportContainRiders.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
#include <windows.h>

#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"

typedef ContainmentList IntList;

namespace _STL
{
template<> _List_base<Rva0036ADF9Element, allocator<Rva0036ADF9Element> >::~_List_base();
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

#include "../../../../Include/Common/ThingTemplate.h"

class AIUpdateInterface;

// The 28-byte kind-of mask.
template <int N> class BitFlags
{
public:
	Bool any() const;
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
#include "../../../../Include/Common/Rva0028B7AELeaGetter.h"

#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"


#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// WWMath's Matrix3D * Vector3 and Get_Translation.
static inline Vector3 operator*(const Matrix3D &A, const Vector3 &a)
{
	return Vector3(
		(A.Row[0].X * a.X + A.Row[0].Y * a.Y + A.Row[0].Z * a.Z + A.Row[0].W),
		(A.Row[1].X * a.X + A.Row[1].Y * a.Y + A.Row[1].Z * a.Z + A.Row[1].W),
		(A.Row[2].X * a.X + A.Row[2].Y * a.Y + A.Row[2].Z * a.Z + A.Row[2].W));
}

static inline Vector3 getTranslation(const Matrix3D &matrix3D)
{
	return Vector3(matrix3D.Row[0].W, matrix3D.Row[1].W, matrix3D.Row[2].W);
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
	__declspec(dllimport) __forceinline Bool isKindOf(KindOfType t) const { return ((getTemplate()->m_kindof[t >> 5] & (1U << (t & 31))) != 0); }
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
	__declspec(dllimport) __forceinline unsigned int testMask(unsigned int mask) const { return m_words[0] & mask; }
	void setMask(unsigned int mask) { m_words[0] |= mask; }
	unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 0x1f); }
	// Object::setModelConditionState indexes unsigned (`shr`), as BitFlags does.
	unsigned int test(unsigned int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void set(unsigned int bit) { m_words[bit >> 5] |= 1U << (bit & 0x1f); }
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
#include "../../../../Include/Common/Rva003909FAObj.h"

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
	__forceinline void setRiderModelConditionMask(UnsignedInt mask)
	{
		if (!m_conditionFlags.testMask(mask))
		{
			m_conditionFlags.setMask(mask);
			rva0028AE6D();
		}
	}
	__forceinline void setModelConditionState(ModelConditionFlagType c)
	{
		if (!m_conditionFlags.test((unsigned int)c))
		{
			m_conditionFlags.set((unsigned int)c);
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

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

// The pair OpenContain hands its list reader (see OpenContainRva00464286.cpp).
#include "../../../../Include/GameLogic/Module/TransportContainModuleData.h"

// OpenContain's ContainModuleInterface at +0x20.
#include "../../../../Include/GameLogic/Module/ContainModule.h"

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




// ?rva0046740C@TransportContain@@MAEXXZ @0x0046740C
// Throws every passenger out at ThrowOutPassengersVelocity (taken into the
// transport's frame) with ThrowOutPassengersLandingWarhead.
void TransportContain::rva0046740C()
{
	UnsignedInt count = getContainCount(0);
	if (count > 0)
	{
		const TransportContainModuleData *transportContainModuleData = getTransportContainModuleData();
		Object *me = getObject();
		const Matrix3D *mtx = me->getTransformMatrix();
		Coord3D velocity;
		velocity.x = 0.0f;
		velocity.y = 0.0f;
		velocity.z = 0.0f;
		Vector3 in(transportContainModuleData->m_throwOutPassengersVelocity.x, transportContainModuleData->m_throwOutPassengersVelocity.y, transportContainModuleData->m_throwOutPassengersVelocity.z);
		Vector3 v = *mtx * in;
		v -= getTranslation(*mtx);
		setCoord(&velocity, v.X, v.Y, v.Z);
		for (UnsignedInt i = 0; i < count; ++i)
		{
			Object *rider = slot79(0);
			PhysicsBehavior *physics = rider->getPhysics();
			if (physics)
			{
				((Rva003909FAObj *)physics)->consume(&velocity, (int)me, (int)transportContainModuleData->m_throwOutPassengersLandingWarhead);
				physics->rva00390629(TRUE);
				rider->setModelConditionState(BFME_MODELCONDITION_7F);
			}
		}
	}
}

// Secondary contain interface receiver, as shown by the -0x1C module-data
// and -0x18 owner loads. Retail calls slot 60 before checking the three
// 28-byte rider-kind masks, then sets owner condition 18, 19 or 20. These
// offsets and the control flow are target facts; the hook's name is unknown.
