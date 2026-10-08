// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/bfmeobjectlayout /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?topple@Object@@QAEXPBUCoord3D@@MI@Z
// retail 0x0028CF37, 123 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameLogic/Object/Object.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
// stlport-range-errors: vendored (these rows match only with STLport's extern __stl_throw_* calls, which offset another shape difference; see inputs/reference/shims/stlport_bfme/stl/_range_errors.h)
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE Object.cpp ////////////////////////////////////////////////////////////////////////////////
// Simple base object
// Author: Michael S. Booth, October 2000
///////////////////////////////////////////////////////////////////////////////////////////////////
 
// INCLUDES /////////////////////////////////////////////////////////////////////////////////////// 
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:
#define DEFINE_WEAPONCONDITIONMAP
#include "Common/BitFlagsIO.h"
#include "Common/BuildAssistant.h"
#include "Common/Dict.h"
#include "Common/GameEngine.h"
#include "Common/GameState.h"
#include "Common/ModuleFactory.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Radar.h"
#include "Common/SpecialPower.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/WellKnownKeys.h"
#include "Common/Xfer.h"
#include "Common/XferCRC.h"
#include "Common/PerfTimer.h"

#include "GameClient/Anim2D.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
#include "GameClient/CommandXlat.h"

#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/FiringTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Locomotor.h"

#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/AutoHealBehavior.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/CollideModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/CountermeasuresBehavior.h"
#include "GameLogic/Module/CreateModule.h"
#include "GameLogic/Module/DamageModule.h"
#include "GameLogic/Module/DeletionUpdate.h"
#include "GameLogic/Module/DestroyModule.h"
#include "GameLogic/Module/DieModule.h"
#include "GameLogic/Module/DozerAIUpdate.h"
#include "GameLogic/Module/ObjectDefectionHelper.h"
#include "GameLogic/Module/ObjectRepulsorHelper.h"
#include "GameLogic/Module/ObjectSMCHelper.h"
#include "GameLogic/Module/ObjectWeaponStatusHelper.h"
#include "GameLogic/Module/OverchargeBehavior.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/PowerPlantUpgrade.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/RadarUpgrade.h"
#include "GameLogic/Module/RebuildHoleBehavior.h"
#include "GameLogic/Module/SpawnBehavior.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SpecialAbilityUpdate.h"
#include "GameLogic/Module/StatusDamageHelper.h"
#include "GameLogic/Module/StickyBombUpdate.h"
#include "GameLogic/Module/SubdualDamageHelper.h"
#include "GameLogic/Module/TempWeaponBonusHelper.h"
#include "GameLogic/Module/ToppleUpdate.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/UpgradeModule.h"

#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/WeaponSet.h"
#include "GameLogic/Module/RadarUpdate.h"
#include "GameLogic/Module/PowerPlantUpdate.h"

#include "Common/CRCDebug.h"
#include "Common/MiscAudio.h"
#include "Common/AudioEventInfo.h"
#include "Common/DynamicAudioEventInfo.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#ifdef DEBUG_OBJECT_ID_EXISTS
ObjectID TheObjectIDToDebug = INVALID_ID;
#endif

// ------------------------------------------------------------------------------------------------
static const ModelConditionFlags s_allWeaponFireFlags[WEAPONSLOT_COUNT] = 
{
	MAKE_MODELCONDITION_MASK5(
		MODELCONDITION_FIRING_A,
		MODELCONDITION_BETWEEN_FIRING_SHOTS_A,
		MODELCONDITION_RELOADING_A,
		MODELCONDITION_PREATTACK_A,
		MODELCONDITION_USING_WEAPON_A
	),
	MAKE_MODELCONDITION_MASK5(
		MODELCONDITION_FIRING_B,
		MODELCONDITION_BETWEEN_FIRING_SHOTS_B,
		MODELCONDITION_RELOADING_B,
		MODELCONDITION_PREATTACK_B,
		MODELCONDITION_USING_WEAPON_B
	),
	MAKE_MODELCONDITION_MASK5(
		MODELCONDITION_FIRING_C,
		MODELCONDITION_BETWEEN_FIRING_SHOTS_C,
		MODELCONDITION_RELOADING_C,
		MODELCONDITION_PREATTACK_C,
		MODELCONDITION_USING_WEAPON_C
	)
};

//-------------------------------------------------------------------------------------------------
extern void addIcon(const Coord3D *pos, Real width, Int numFramesDuration, RGBColor color);

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#ifdef DEBUG_LOGGING

#endif // DEBUG_LOGGING

  // end Object

// Retail Object::onContainedBy (0x001CB9F0) is implemented in ObjectOnContainedBy.cpp.

// Retail Object::onRemovedFrom (0x001CBAE0) is implemented in ObjectOnRemovedFrom.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME: m_contain sits at +0x1fc, ThingTemplate's transport-slot count is a
// signed byte at +0x491, and ContainModuleInterface's vtable puts
// isSpecialZeroSlotContainer at +0x0c and getContainedItemsList at +0x104.
// BFME also inlines Thing::getTemplate at the call site (one inlined level of
// Overridable::getFinalOverride).
class BFMEContainSlotShim
{
public:
	virtual void bfmeSlot00() = 0; virtual void bfmeSlot01() = 0; virtual void bfmeSlot02() = 0;
	virtual Bool isSpecialZeroSlotContainer() = 0;
	virtual void bfmeSlot04() = 0; virtual void bfmeSlot05() = 0; virtual void bfmeSlot06() = 0; virtual void bfmeSlot07() = 0; virtual void bfmeSlot08() = 0; virtual void bfmeSlot09() = 0;
	virtual void bfmeSlot10() = 0; virtual void bfmeSlot11() = 0; virtual void bfmeSlot12() = 0; virtual void bfmeSlot13() = 0; virtual void bfmeSlot14() = 0; virtual void bfmeSlot15() = 0;
	virtual void bfmeSlot16() = 0; virtual void bfmeSlot17() = 0; virtual void bfmeSlot18() = 0; virtual void bfmeSlot19() = 0; virtual void bfmeSlot20() = 0; virtual void bfmeSlot21() = 0;
	virtual void bfmeSlot22() = 0; virtual void bfmeSlot23() = 0; virtual void bfmeSlot24() = 0; virtual void bfmeSlot25() = 0; virtual void bfmeSlot26() = 0; virtual void bfmeSlot27() = 0;
	virtual void bfmeSlot28() = 0; virtual void bfmeSlot29() = 0; virtual void bfmeSlot30() = 0; virtual void bfmeSlot31() = 0; virtual void bfmeSlot32() = 0; virtual void bfmeSlot33() = 0;
	virtual void bfmeSlot34() = 0; virtual void bfmeSlot35() = 0; virtual void bfmeSlot36() = 0; virtual void bfmeSlot37() = 0; virtual void bfmeSlot38() = 0; virtual void bfmeSlot39() = 0;
	virtual void bfmeSlot40() = 0; virtual void bfmeSlot41() = 0; virtual void bfmeSlot42() = 0; virtual void bfmeSlot43() = 0; virtual void bfmeSlot44() = 0; virtual void bfmeSlot45() = 0;
	virtual void bfmeSlot46() = 0; virtual void bfmeSlot47() = 0; virtual void bfmeSlot48() = 0; virtual void bfmeSlot49() = 0; virtual void bfmeSlot50() = 0; virtual void bfmeSlot51() = 0;
	virtual void bfmeSlot52() = 0; virtual void bfmeSlot53() = 0; virtual void bfmeSlot54() = 0; virtual void bfmeSlot55() = 0; virtual void bfmeSlot56() = 0; virtual void bfmeSlot57() = 0;
	virtual void bfmeSlot58() = 0; virtual void bfmeSlot59() = 0; virtual void bfmeSlot60() = 0; virtual void bfmeSlot61() = 0; virtual void bfmeSlot62() = 0; virtual void bfmeSlot63() = 0;
	virtual void bfmeSlot64() = 0;
	virtual const ContainedItemsList *getContainedItemsList() = 0;
};

  // end onDestroy

// Retail Object::setGeometryInfo (0x001D5D20) is implemented in ObjectGeometry.cpp.

// Retail Object::setGeometryInfoZ (0x001BDF70) is implemented in ObjectGeometry.cpp.

// Retail Object::restoreOriginalTeam (0x001C4670) is implemented in ObjectTeamAndPlayer.cpp.

//=============================================================================
enum 
{
	BOOBY_TRAP_SCAN_RANGE = 25
};

// Retail Object::setStatus (0x0001366F) is implemented in ObjectSetStatusThunk.cpp.

// Retail Object::canCrushOrSquish (0x001C7600) is implemented in ObjectCanCrushOrSquish.cpp.

// BFME's ThingTemplate carries FOUR crush levels at +0x499..+0x49c, not two:
// a mounted pair that is used when the object's mounted-condition word at
// +0x128 has bit 11 set and the mounted level is not 0xff.
struct BfmeCrushLevels
{
	unsigned char m_unreconstructed_000[0x499];
	UnsignedByte m_crusherLevel;			///< retail this+0x499
	UnsignedByte m_crushableLevel;			///< retail this+0x49a
	UnsignedByte m_mountedCrusherLevel;		///< retail this+0x49b
	UnsignedByte m_mountedCrushableLevel;		///< retail this+0x49c
};

struct BfmeObjectCrushFields
{
	unsigned char m_unreconstructed_000[4];
	const Overridable *m_template;			///< retail this+0x04
	unsigned char m_unreconstructed_008[0x128 - 8];
	UnsignedInt m_mountedCondition;			///< retail this+0x128
};

static const BfmeCrushLevels *bfmeFinalCrushTemplate( const Object *obj )
{
	const Overridable *base =
		reinterpret_cast<const BfmeObjectCrushFields *>(obj)->m_template;
	if (base == NULL)
		return NULL;

	return reinterpret_cast<const BfmeCrushLevels *>( base->getFinalOverride() );
}

// ------------------------------------------------------------------------------------------------
/** Topple an object, if possible */
// ------------------------------------------------------------------------------------------------
void Object::topple( const Coord3D *toppleDirection, Real toppleSpeed, UnsignedInt options )
{
	static NameKeyType key_ToppleUpdate = NAMEKEY("ToppleUpdate");

	ToppleUpdate* toppleUpdate = (ToppleUpdate*)findModule(key_ToppleUpdate);
	if( toppleUpdate && toppleUpdate->isAbleToBeToppled() )
	{

		// apply the topple force
		toppleUpdate->applyTopplingForce( toppleDirection, toppleSpeed, options );

	}  // end if

}  // end topple

//=============================================================================
// ?setFiringConditionForCurrentWeapon@Object@@QBEXXZ is defined in
// Object_setFiringConditionForCurrentWeapon.cpp so the BFME 320-bit
// ModelConditionFlags ABI is kept separate from this ZH-layout TU.

// BFME builds a single-bit mask on the stack -- three dwords, where the
// reference ModelConditionFlags is four -- and hands it to an apply helper that
// is unnamed in the image, with the set flag false. Nothing is asked of the
// drawable.
struct BfmeModelConditionFlags
{
	BfmeModelConditionFlags() { memset( m_bits, 0, sizeof( m_bits ) ); }

	void set( ModelConditionFlagType bit )
	{
		m_bits[ (UnsignedInt)bit >> 5 ] |= 1 << ( (UnsignedInt)bit & 31 );
	}

	UnsignedInt m_bits[3];
};

class BfmeObjectFlagApply
{
public:
	void apply( const BfmeModelConditionFlags &flags, Bool set );	///< retail 0x001c7370
};

// Lorenzen has some interest in this, ask before deleting
//=============================================================================
//const ModelConditionFlags& Object::getModelConditionFlags() const
//{ 
//	if (m_drawable)
//	{
//		return m_drawable->getModelConditionFlags(); 
//	}
//	else
//	{
//		DEBUG_CRASH(("NULL Drawable at this point, you can't get modelconditionflags now."));
//		static ModelConditionFlags noFlags;
//		return noFlags;
//	}
//}

// BFME asks the weapon set nothing: the four weapon pointers, the slot in hand
// and the word that says whether there is a weapon at all are all read in
// place, at +0x08, +0x18 and +0x20 of the weapon set that starts at +0x264.
struct BfmeObjectWeaponFields
{
	UnsignedByte m_unreconstructed_000[0x26c];
	Weapon *m_weapons[4];				///< retail this+0x26c
	WeaponSlotType m_curWeapon;			///< retail this+0x27c
	UnsignedByte m_unreconstructed_280[4];
	void *m_hasWeapon;				///< retail this+0x284
};

// BFME reads the clip size from the weapon template at +0x4ac and asks for the
// remaining ammo out of line, with an argument the reference class does not
// have: whether a reloading clip counts as empty.
struct BfmeWeaponTemplateClip
{
	unsigned char m_unreconstructed_000[0x4ac];
	Int m_clipSize;					///< retail this+0x4ac
};

class BfmeAmmoPipWeapon
{
public:
	UnsignedInt getRemainingAmmo( Bool countReloadingAsEmpty ) const;	///< retail ILT 0x00046f10

	unsigned char m_unreconstructed_00[4];		///< the vtable pointer
	const BfmeWeaponTemplateClip *m_template;	///< retail this+0x04
};

 

// Retail Object::getRelationship (0x0004A719) is implemented in ObjectGetRelationshipThunk.cpp.

//-------------------------------------------------------------------------------------------------
inline Bool isPosDifferent(const Coord3D* a, const Coord3D* b)
{
	// this is necessary because PhysicsBehavior may generate tiny changes even when 
	// "standing still", due to roundoff errors. It's important that we only invalidate
	// the PartitionManager stuff when the pos/orientation really changes (for efficiency purposes)
	// so we must put in some cleverness...
	const Real THRESH = 0.01f;

	if (fabs(a->x - b->x) > THRESH)
		return true;

	if (fabs(a->y - b->y) > THRESH)
		return true;

	if (fabs(a->z - b->z) > THRESH)
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
inline Bool isAngleDifferent(Real a, Real b)
{
	// this is necessary because PhysicsBehavior may generate tiny changes even when 
	// "standing still", due to roundoff errors. It's important that we only invalidate
	// the PartitionManager stuff when the pos/orientation really changes (for efficiency purposes)
	// so we must put in some cleverness...

	const Real THRESH = 0.01f;	// in radians, this is approx 1/2 degree.

	if (fabs(a - b) > THRESH)
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
//DECLARE_PERF_TIMER(Object_reactToTransformChange)
// The retail callback uses primary vtable slot +18 before notifying containment.
// Keep this slot address-derived: the ZH partition-data branch is not present.
class Rva001CDC30Virtual
{
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual void slot18();
};
class Rva001BF150Object { public: void expire(); };
class Rva00132200Target { public: void rva00132200(const Matrix3D *); };
class Rva001C8D80Object { public: void invoke(); };

// Retail Object::attemptDamage (0x001D0490) is implemented in Object_attemptDamage_Thunk.cpp.

// BFME's DamageInfo is 0x5c bytes with its input half at the front -- source id
// at +0x08, damage type at +0x10, death type at +0x18, amount at +0x1c and the
// kill flag at +0x20 -- and its constructor is out of line, so the local needs
// no unwind funclet. The body module is at object+0x200 with getMaxHealth at
// vtable +0x18, and attemptDamage is the object's own virtual at vtable +0x34.
struct BFMEDamageInfoInput
{
	unsigned char m_unreconstructed_00[8];
	ObjectID m_sourceID;				///< +0x08
	unsigned char m_unreconstructed_0c[4];
	DamageType m_damageType;			///< +0x10
	unsigned char m_unreconstructed_14[4];
	DeathType m_deathType;				///< +0x18
	Real m_amount;					///< +0x1c
	Bool m_kill;					///< +0x20
};

struct BFMEDamageInfo
{
	BFMEDamageInfo();				///< retail ILT 0x0002c9d5

	BFMEDamageInfoInput in;
	unsigned char m_unreconstructed_24[0x5c - 0x24];
};

struct BFMEBodyMaxHealthShim
{
	virtual void bfmeSlot00() = 0;	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0;	virtual void bfmeSlot0C() = 0;
	virtual void bfmeSlot10() = 0;	virtual void bfmeSlot14() = 0;
	virtual Real getMaxHealth() const = 0;		///< vtable +0x18
};

struct BFMEObjectAttemptDamageShim
{
	virtual void bfmeSlot00() = 0;	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0;	virtual void bfmeSlot0C() = 0;
	virtual void bfmeSlot10() = 0;	virtual void bfmeSlot14() = 0;
	virtual void bfmeSlot18() = 0;	virtual void bfmeSlot1C() = 0;
	virtual void bfmeSlot20() = 0;	virtual void bfmeSlot24() = 0;
	virtual void bfmeSlot28() = 0;	virtual void bfmeSlot2C() = 0;
	virtual void bfmeSlot30() = 0;
	virtual void attemptDamage( BFMEDamageInfo *damageInfo ) = 0;	///< vtable +0x34
};

struct BFMEObjectBodyField
{
	unsigned char m_unreconstructed_000[0x200];
	BFMEBodyMaxHealthShim *m_body;			///< retail this+0x200
};

// attemptHealing is slot 1 (+0x04) of the body module's vtable, and BFME's
// healing damage type is 7 -- the reference enum's DAMAGE_HEALING is 10.
struct BFMEBodyAttemptHealingShim
{
	virtual void bfmeSlot00() = 0;
	virtual void attemptHealing( BFMEDamageInfo *damageInfo ) = 0;	///< vtable +0x04
};

  // end kill

// BFME's kind-of mask is six dwords where the reference BitFlags<KINDOF_COUNT>
// is four, and retail builds the faction-structure mask on the stack instead of
// reading the KINDOFMASK_FS global: bits 61, 62, 63, 64 and 134.
class BfmeKindOfMask
{
public:
	BfmeKindOfMask( Int idx1, Int idx2, Int idx3, Int idx4, Int idx5 )
	{
		m_bits.set( idx1 );
		m_bits.set( idx2 );
		m_bits.set( idx3 );
		m_bits.set( idx4 );
		m_bits.set( idx5 );
	}

private:
	std::bitset<192> m_bits;
};

//-------------------------------------------------------------------------------------------------
// ?isNonFactionStructure@Object@@QBE_NXZ is defined in
// Object_isNonFactionStructure.cpp so its BFME six-dword mask layout stays
// isolated from the other Object bodies in this ZH-layout translation unit.

// BFME: m_team at +0x23c (see isLocallyControlled) and the difficulty-bonus
// flag at +0x348. The applier is non-const in BFME where the reference Player.h
// declares it const, so it needs its own spelling.
struct BfmeObjectDifficultyFields
{
	UnsignedByte m_unreconstructed_000[0x23c];
	Team *m_team;					///< retail this+0x23c
	UnsignedByte m_unreconstructed_240[0x348 - 0x240];
	Bool m_isReceivingDifficultyBonus;		///< retail this+0x348
};

class BfmeDifficultyBonusPlayer
{
public:
	void friend_applyDifficultyBonusesForObject( Object *object, Bool receive );	///< retail ILT 0x0002278c
};

// Retail Object::setDisabledUntil (0x0003364A) is implemented in MoneyObjectThunks.cpp.

// Retail Object::checkDisabledStatus (0x001C5780) is implemented in ObjectCheckDisabledStatus.cpp.

// Retail Object::onCollide (0x001C8A80) is implemented in Object_onCollide.cpp.

// Retail Object::updateUpgradeModules (0x00027FCF) is implemented in ObjectUpdateUpgradeModulesThunk.cpp.

// Retail Object::didEnterOrExit (0x001C8BE0) is implemented in ObjectFields.cpp.

// Retail Object::didEnter (0x001C8C40) is implemented in ObjectFields.cpp.

// Retail Object::didExit (0x001C8CE0) is implemented in ObjectFields.cpp.

  // end getObjectExitInterface

//-------------------------------------------------------------------------------------------------
/** Checks the object against trigger areas when the position changes. */
//-------------------------------------------------------------------------------------------------
// Body in Object_setTriggerAreaFlagsForChangeInPosition.asm (exact 749B retail).

  // end setID

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME: m_privateStatus lives at +0x344. BFME's version drops the radar
// registration and the partition-cell maintenance pass, and calls
// Pathfinder::addObjectToPathfindMap OUT OF LINE (0x003D57F0, which forwards to
// classifyObjectFootprint with a third argument) where ZH inlines it -- so the
// call site goes through a TU-local shim to emit the REL32.
class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap( Object *obj );
};

//-------------------------------------------------------------------------------------------------
class BfmeMassSelectableUIResult;

class BfmeMassSelectableUIBase
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46();
};

class BfmeMassSelectableUI : public BfmeMassSelectableUIBase
{
public:
	virtual BfmeMassSelectableUIResult *slot47();
};

class BfmeMassSelectableUIResult
{
public:
	unsigned char m_pad00[0x10];
	int m_type;
};

// Retail Object::hasSpecialPower (0x001C9BD0) is implemented in ObjectFields.cpp.

//-------------------------------------------------------------------------------------------------
// Body in Object_onVeterancyLevelChanged.asm (exact 711B retail).

//-------------------------------------------------------------------------------------------------
/**
 * Returns true if object currently has some kind of attack capability
 */
extern void j_000261a2();
extern void j_00027836();
extern void j_0003251f();
extern void j_00035c4c();
extern void j_0003c8e9();
extern void j_00044201();

struct Rva001C9C10Call {};

template <int N> class Rva001C9C10Slots : public Rva001C9C10Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class Rva001C9C10Slots<0> {};

class Rva001C9C10Contain : public Rva001C9C10Slots<39>
{
public:
	virtual const _STL::bitset<116> *slot39(void **, Object *) = 0;
	virtual Bool slot40() = 0;
	virtual void slot41gap() = 0;
	virtual void slot42gap() = 0;
	virtual Bool slot43(Object *, Object *) = 0;
	virtual void slot44gap() = 0;
	virtual void slot45gap() = 0;
	virtual void slot46gap() = 0;
	virtual void slot47gap() = 0;
	virtual void slot48gap() = 0;
	virtual void slot49gap() = 0;
	virtual void slot50gap() = 0;
	virtual void slot51gap() = 0;
	virtual void slot52gap() = 0;
	virtual void slot53gap() = 0;
	virtual void slot54gap() = 0;
	virtual void slot55gap() = 0;
	virtual void slot56gap() = 0;
	virtual void slot57gap() = 0;
	virtual void slot58gap() = 0;
	virtual void slot59gap() = 0;
	virtual void slot60gap() = 0;
	virtual void slot61gap() = 0;
	virtual void slot62gap() = 0;
	virtual void slot63gap() = 0;
	virtual UnsignedInt slot64(Bool) = 0;
};

template <int N> class Rva001C9C10SpawnSlots : public Rva001C9C10SpawnSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class Rva001C9C10SpawnSlots<0> {};

class Rva001C9C10Spawn : public Rva001C9C10SpawnSlots<7>
{
public:
	virtual Bool slot7() = 0;
};

static __forceinline Bool routeIsKindOf(const Object *object, Int kind)
{
	typedef Bool (Rva001C9C10Call::*Call)(Int) const;
	union { void (*raw)(); Call member; } route;
	route.raw = j_0003251f;
	return (reinterpret_cast<Rva001C9C10Call *>(const_cast<Object *>(object))->*route.member)(kind);
}

static __forceinline Object *rva001C9C10Victim(const void *ai)
{
	typedef Object *(Rva001C9C10Call::*Call)() const;
	union { void (*raw)(); Call member; } route;
	route.raw = j_000261a2;
	return (reinterpret_cast<Rva001C9C10Call *>(const_cast<void *>(ai))->*route.member)();
}

static __forceinline Weapon *routeGetWeaponInWeaponSlot(const void *set, WeaponSlotType slot)
{
	typedef Weapon *(Rva001C9C10Call::*Call)(WeaponSlotType) const;
	union { void (*raw)(); Call member; } route;
	route.raw = j_0003c8e9;
	return (reinterpret_cast<Rva001C9C10Call *>(const_cast<void *>(set))->*route.member)(slot);
}

static __forceinline WhichTurretType rva001C9C10Turret(const void *ai, WeaponSlotType slot, Real *angle, Real *pitch)
{
	typedef WhichTurretType (Rva001C9C10Call::*Call)(WeaponSlotType, Real *, Real *) const;
	union { void (*raw)(); Call member; } route;
	route.raw = j_00035c4c;
	return (reinterpret_cast<Rva001C9C10Call *>(const_cast<void *>(ai))->*route.member)(slot, angle, pitch);
}

static __forceinline Bool rva001C9C10TurretOpen(const void *ai, Int turret)
{
	typedef Bool (Rva001C9C10Call::*Call)(Int) const;
	union { void (*raw)(); Call member; } route;
	route.raw = j_00027836;
	return (reinterpret_cast<Rva001C9C10Call *>(const_cast<void *>(ai))->*route.member)(turret);
}

static __forceinline Rva001C9C10Spawn *routeGetSpawnBehaviorInterface(const Object *object)
{
	typedef Rva001C9C10Spawn *(Rva001C9C10Call::*Call)() const;
	union { void (*raw)(); Call member; } route;
	route.raw = j_00044201;
	return (reinterpret_cast<Rva001C9C10Call *>(const_cast<Object *>(object))->*route.member)();
}

// Retail Object::maskObject (0x001BEFB0) is implemented in Object_maskObject.cpp.

//-------------------------------------------------------------------------------------------------
/*
 * returns true if the current locomotor is an airborne one
 */
// Three BFME offsets down one chain. Object::m_ai is at +0x204 where this
// tree puts it at +0x19c and AIUpdate's current locomotor at +0x1cc against
// +0x1b8; both are read once and reused, as retail does. The third is inside
// Locomotor: its m_template sits at +4 rather than +8, so rebasing the
// pointer by -4 lets the real getLegalSurfaces accessor compile retail's
// encoding instead of open-coding it here. The tail already agrees.
#define BFME_OBJ_AI(o)     (*(AIUpdateInterface *const *)((const char *)(o) + 0x204))
#define BFME_AI_CURLOCO(a) (*(Locomotor *const *)((const char *)(a) + 0x1cc))
#define BFME_LOCO(l)       ((const Locomotor *)((const char *)(l) - 4))

//-------------------------------------------------------------------------------------------------
//THIS FUNCTION BELONGS AT THE OBJECT LEVEL BECAUSE THERE IS AT LEAST ONE SPECIAL UNIT
//(ANGRY MOB) WHICH NEEDS LOGIC-SIDE POSITION CALC'S...
//IT WOULD PROBABLY BE WISE TO MOVE ALL THE HARD-CODED DEFAULTS BELOW
//INTO A NEW Drawable::getHealthBox..() WHICH USES GEOM0INFO, MODEL DATA, INI DATA, ETC.
// Object_getHealthBoxDimensions_Thunk.cpp contains the clean C++ body.

// Retail Object::friend_adjustPowerForPlayer (0x001C34D0) is implemented in ObjectFriendAdjustPower.cpp.

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

  // end crc

  // end xfer

  // end loadPostProcess

//-------------------------------------------------------------------------------------------------
/** Does this object have this upgrade */
// BFME's upgrade mask is a single word at UpgradeTemplate+0x20, not the
// reference class's BitFlags, and the test against it lives in a member the
// reference Object.h does not declare. Both are spelled here as views.
struct BfmeUpgradeTemplateMask
{
	UnsignedByte m_unreconstructed_00[0x20];
	UnsignedInt m_upgradeMask;			///< retail this+0x20
};

class BfmeUpgradeMaskTester
{
public:
	Bool hasUpgradeMask( UnsignedInt mask ) const;	///< retail 0x001c59c0
};

  // end hasUpgrade

// Retail Object::affectedByUpgrade (0x001C5A30) is implemented in ObjectUpgrades.cpp.

// Retail Object::giveUpgrade (0x001C9F70) is implemented in ObjectFields.cpp.

// Retail Object::removeUpgrade (0x001CA020) is implemented in ObjectFields.cpp.

// Retail Object::adjustModelConditionForWeaponStatus (0x000276D3) is implemented in ObjectAdjustModelConditionThunk.cpp.

// BFME's PartitionData::makeDirty takes no argument; the reference class
// declares Zero Hour's makeDirty(Bool), so the no-argument entry needs its own
// spelling.
class BfmeDirtyablePartitionData
{
public:
	void makeDirty();				///< retail 0x008f7b30
};

// BFME keeps the looking ranges past where the reference class puts them: the
// vision range at +0x194, the shroud-clearing range at +0x198, and a second
// shroud range at +0xbc that bit 2 of the status byte at +0x90 selects instead.
struct BfmeObjectVisionFields
{
	UnsignedByte m_unreconstructed_000[0x90];
	UnsignedByte m_statusFlags;			///< retail this+0x90
	UnsignedByte m_unreconstructed_091[0xbc - 0x91];
	Real m_altShroudClearingRange;			///< retail this+0xbc
	UnsignedByte m_unreconstructed_0c0[0x194 - 0xc0];
	Real m_visionRange;				///< retail this+0x194
	Real m_shroudClearingRange;			///< retail this+0x198
	UnsignedByte m_unreconstructed_19c[0x3b0 - 0x19c];
	BfmeDirtyablePartitionData *m_partitionData;	///< retail this+0x3b0
};

// BFME scales the stored vision range by a bonus it queries from a per-object
// source. Neither the source getter nor the query is declared by the reference
// Object.h, so both are spelled as views onto the retail entry points.
class BfmeVisionBonusSource
{
public:
	Bool bfmeGetBonus( Int which, Real *out );	///< retail ILT 0x000282d6
};

class BfmeVisionBonusHolder
{
public:
	BfmeVisionBonusSource *bfmeGetBonusSource() const;	///< retail ILT 0x000202ed
};

  

// Retail Object::getProductionUpdateInterface (0x001BF570) is implemented in ObjectFields.cpp.

// Retail Object::getDockUpdateInterface (0x001BF5B0) is implemented in ObjectFields.cpp.

  // end getSpawnBehaviorInterfaceFromObject

// Retail Object::getProjectileUpdateInterface (0x001BF630) is implemented in ObjectFields.cpp.

// Retail Object::findSpecialPowerWithOverridableDestinationActive (0x001BF6F0) is implemented in ObjectFields.cpp.

// ------------------------------------------------------------------------------------------------
// Search our special ability updates for a specific one.
// ------------------------------------------------------------------------------------------------
class BFMESpecialPowerUpdateInterface
{
public:
	virtual void slot00();
	virtual Bool isSpecialAbility();
};

class BFMEBehaviorSpecialPowerInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual BFMESpecialPowerUpdateInterface *getSpecialPowerUpdateInterface();
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// BFME Drawable::getPristineBonePositions is 6 stack args (ret 0x18); ZH is 5 (ret 0x14).
// Trailing Int is 0 at this call site. Local thiscall shape avoids Drawable.h blast radius.
struct BFMEDrawableBoneQuery {
	Int getPristineBonePositions(const char* boneNamePrefix, Int startIndex,
		Coord3D* positions, Matrix3D* transforms, Int maxBones, Int extra) const;
};

// BFME tries three sources in order and returns each by reference. The two
// object-side overrides are AsciiStrings at +0x328 and +0x32c, and "set" means
// a non-zero character count in the block header, not merely a non-null buffer.
struct BfmeAsciiStringHeader
{
	Int m_refCount;
	UnsignedShort m_length;				///< retail m_data+0x04
	UnsignedShort m_capacity;
};

struct BfmeObjectCommandSetFields
{
	UnsignedByte m_unreconstructed_000[4];
	const Overridable *m_template;			///< retail this+0x04
	UnsignedByte m_unreconstructed_008[0x328 - 8];
	BfmeAsciiStringHeader *m_commandSetFallback;	///< retail this+0x328
	BfmeAsciiStringHeader *m_commandSetOverride;	///< retail this+0x32c
};

//=============================================================================
// Object::defect, and related methods                                        =
//=============================================================================
class Rva00024D70AICommandCall
{
public:
	void invoke(int source);
};

// Retail calls cancelAndRefundAllProduction at vtable offset +0x34.
class BfmeDefectProductionUpdateCall
{
public:
#define BFME_DEFECT_PRODUCTION_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DEFECT_PRODUCTION_SLOT(00) BFME_DEFECT_PRODUCTION_SLOT(01)
	BFME_DEFECT_PRODUCTION_SLOT(02) BFME_DEFECT_PRODUCTION_SLOT(03)
	BFME_DEFECT_PRODUCTION_SLOT(04) BFME_DEFECT_PRODUCTION_SLOT(05)
	BFME_DEFECT_PRODUCTION_SLOT(06) BFME_DEFECT_PRODUCTION_SLOT(07)
	BFME_DEFECT_PRODUCTION_SLOT(08) BFME_DEFECT_PRODUCTION_SLOT(09)
	BFME_DEFECT_PRODUCTION_SLOT(10) BFME_DEFECT_PRODUCTION_SLOT(11)
	BFME_DEFECT_PRODUCTION_SLOT(12)
	virtual void cancelAndRefundAllProduction(void) = 0;
#undef BFME_DEFECT_PRODUCTION_SLOT
};

// The retail calls containment slots +0xBC and +0x94 for isKickOutOnCapture and removeAllContained.
class BfmeDefectContainModuleCall
{
public:
#define BFME_DEFECT_CONTAIN_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DEFECT_CONTAIN_SLOT(00) BFME_DEFECT_CONTAIN_SLOT(01)
	BFME_DEFECT_CONTAIN_SLOT(02) BFME_DEFECT_CONTAIN_SLOT(03)
	BFME_DEFECT_CONTAIN_SLOT(04) BFME_DEFECT_CONTAIN_SLOT(05)
	BFME_DEFECT_CONTAIN_SLOT(06) BFME_DEFECT_CONTAIN_SLOT(07)
	BFME_DEFECT_CONTAIN_SLOT(08) BFME_DEFECT_CONTAIN_SLOT(09)
	BFME_DEFECT_CONTAIN_SLOT(10) BFME_DEFECT_CONTAIN_SLOT(11)
	BFME_DEFECT_CONTAIN_SLOT(12) BFME_DEFECT_CONTAIN_SLOT(13)
	BFME_DEFECT_CONTAIN_SLOT(14) BFME_DEFECT_CONTAIN_SLOT(15)
	BFME_DEFECT_CONTAIN_SLOT(16) BFME_DEFECT_CONTAIN_SLOT(17)
	BFME_DEFECT_CONTAIN_SLOT(18) BFME_DEFECT_CONTAIN_SLOT(19)
	BFME_DEFECT_CONTAIN_SLOT(20) BFME_DEFECT_CONTAIN_SLOT(21)
	BFME_DEFECT_CONTAIN_SLOT(22) BFME_DEFECT_CONTAIN_SLOT(23)
	BFME_DEFECT_CONTAIN_SLOT(24) BFME_DEFECT_CONTAIN_SLOT(25)
	BFME_DEFECT_CONTAIN_SLOT(26) BFME_DEFECT_CONTAIN_SLOT(27)
	BFME_DEFECT_CONTAIN_SLOT(28) BFME_DEFECT_CONTAIN_SLOT(29)
	BFME_DEFECT_CONTAIN_SLOT(30) BFME_DEFECT_CONTAIN_SLOT(31)
	BFME_DEFECT_CONTAIN_SLOT(32) BFME_DEFECT_CONTAIN_SLOT(33)
	BFME_DEFECT_CONTAIN_SLOT(34) BFME_DEFECT_CONTAIN_SLOT(35)
	BFME_DEFECT_CONTAIN_SLOT(36)
	virtual void removeAllContained(Bool ejectAll) = 0;
	BFME_DEFECT_CONTAIN_SLOT(38) BFME_DEFECT_CONTAIN_SLOT(39)
	BFME_DEFECT_CONTAIN_SLOT(40) BFME_DEFECT_CONTAIN_SLOT(41)
	BFME_DEFECT_CONTAIN_SLOT(42) BFME_DEFECT_CONTAIN_SLOT(43)
	BFME_DEFECT_CONTAIN_SLOT(44) BFME_DEFECT_CONTAIN_SLOT(45)
	BFME_DEFECT_CONTAIN_SLOT(46)
	virtual Bool isKickOutOnCapture(void) = 0;
#undef BFME_DEFECT_CONTAIN_SLOT
};

// The retail calls Object slots +0x28 and +0x50 for getDrawable and setTeam.
class BfmeDefectObjectVtableView
{
public:
#define BFME_DEFECT_OBJECT_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DEFECT_OBJECT_SLOT(00) BFME_DEFECT_OBJECT_SLOT(01)
	BFME_DEFECT_OBJECT_SLOT(02) BFME_DEFECT_OBJECT_SLOT(03)
	BFME_DEFECT_OBJECT_SLOT(04) BFME_DEFECT_OBJECT_SLOT(05)
	BFME_DEFECT_OBJECT_SLOT(06) BFME_DEFECT_OBJECT_SLOT(07)
	BFME_DEFECT_OBJECT_SLOT(08) BFME_DEFECT_OBJECT_SLOT(09)
	virtual Drawable *getDrawable(void) = 0;
	BFME_DEFECT_OBJECT_SLOT(11) BFME_DEFECT_OBJECT_SLOT(12)
	BFME_DEFECT_OBJECT_SLOT(13) BFME_DEFECT_OBJECT_SLOT(14)
	BFME_DEFECT_OBJECT_SLOT(15) BFME_DEFECT_OBJECT_SLOT(16)
	BFME_DEFECT_OBJECT_SLOT(17) BFME_DEFECT_OBJECT_SLOT(18)
	BFME_DEFECT_OBJECT_SLOT(19)
	virtual void setTeam(Team *newTeam) = 0;
#undef BFME_DEFECT_OBJECT_SLOT
};

// The Zero Hour Object declaration supplies these member names. Retail instructions place them at the BFME offsets below.
class BfmeDefectObjectFields
{
public:
	void *m_vtable;
	unsigned char m_beforeID[0x74 - 0x04];
	UnsignedInt m_id;
	unsigned char m_beforeStatus[0x90 - 0x78];
	UnsignedInt m_status;
	unsigned char m_beforeDefectionHelper[0x1e4 - 0x94];
	ObjectDefectionHelper *m_defectionHelper;
	unsigned char m_beforeContain[0x1fc - 0x1e8];
	BfmeDefectContainModuleCall *m_contain;
	unsigned char m_beforeAI[0x204 - 0x200];
	AIUpdateInterface *m_ai;
	unsigned char m_beforeRadar[0x20c - 0x208];
	RadarObject *m_radarData;
	unsigned char m_beforeContainedBy[0x214 - 0x210];
	Object *m_containedBy;
	unsigned char m_beforeTeam[0x23c - 0x218];
	Team *m_team;
	unsigned char m_beforePartition[0x3b0 - 0x240];
	BfmeDirtyablePartitionData *m_partitionData;
};

class Rva0004067ECall
{
public:
	void invoke(int mode);
};

class BfmeAudioEventRTS
{
public:
	BfmeAudioEventRTS(const BfmeAudioEventRTS &other);
	~BfmeAudioEventRTS(void);
	void setObjectID(UnsignedInt objectID);
	void setPlayerIndex(int playerIndex);

private:
	unsigned char m_data[0x70];
};

struct Rva005A00B0MiscAudio
{
	unsigned char m_beforeDefectorTimerSound[0x230];
	BfmeAudioEventRTS m_defectorTimerTickSound;
};

// Retail uses audio slots +0x44 and +0x124 for addAudioEvent and getMiscAudio.
class Rva005A00B0AudioClient
{
public:
#define BFME_DEFECT_AUDIO_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DEFECT_AUDIO_SLOT(00) BFME_DEFECT_AUDIO_SLOT(01)
	BFME_DEFECT_AUDIO_SLOT(02) BFME_DEFECT_AUDIO_SLOT(03)
	BFME_DEFECT_AUDIO_SLOT(04) BFME_DEFECT_AUDIO_SLOT(05)
	BFME_DEFECT_AUDIO_SLOT(06) BFME_DEFECT_AUDIO_SLOT(07)
	BFME_DEFECT_AUDIO_SLOT(08) BFME_DEFECT_AUDIO_SLOT(09)
	BFME_DEFECT_AUDIO_SLOT(10) BFME_DEFECT_AUDIO_SLOT(11)
	BFME_DEFECT_AUDIO_SLOT(12) BFME_DEFECT_AUDIO_SLOT(13)
	BFME_DEFECT_AUDIO_SLOT(14) BFME_DEFECT_AUDIO_SLOT(15)
	BFME_DEFECT_AUDIO_SLOT(16)
	virtual UnsignedInt addAudioEvent(BfmeAudioEventRTS *event) = 0;
	BFME_DEFECT_AUDIO_SLOT(18) BFME_DEFECT_AUDIO_SLOT(19)
	BFME_DEFECT_AUDIO_SLOT(20) BFME_DEFECT_AUDIO_SLOT(21)
	BFME_DEFECT_AUDIO_SLOT(22) BFME_DEFECT_AUDIO_SLOT(23)
	BFME_DEFECT_AUDIO_SLOT(24) BFME_DEFECT_AUDIO_SLOT(25)
	BFME_DEFECT_AUDIO_SLOT(26) BFME_DEFECT_AUDIO_SLOT(27)
	BFME_DEFECT_AUDIO_SLOT(28) BFME_DEFECT_AUDIO_SLOT(29)
	BFME_DEFECT_AUDIO_SLOT(30) BFME_DEFECT_AUDIO_SLOT(31)
	BFME_DEFECT_AUDIO_SLOT(32) BFME_DEFECT_AUDIO_SLOT(33)
	BFME_DEFECT_AUDIO_SLOT(34) BFME_DEFECT_AUDIO_SLOT(35)
	BFME_DEFECT_AUDIO_SLOT(36) BFME_DEFECT_AUDIO_SLOT(37)
	BFME_DEFECT_AUDIO_SLOT(38) BFME_DEFECT_AUDIO_SLOT(39)
	BFME_DEFECT_AUDIO_SLOT(40) BFME_DEFECT_AUDIO_SLOT(41)
	BFME_DEFECT_AUDIO_SLOT(42) BFME_DEFECT_AUDIO_SLOT(43)
	BFME_DEFECT_AUDIO_SLOT(44) BFME_DEFECT_AUDIO_SLOT(45)
	BFME_DEFECT_AUDIO_SLOT(46) BFME_DEFECT_AUDIO_SLOT(47)
	BFME_DEFECT_AUDIO_SLOT(48) BFME_DEFECT_AUDIO_SLOT(49)
	BFME_DEFECT_AUDIO_SLOT(50) BFME_DEFECT_AUDIO_SLOT(51)
	BFME_DEFECT_AUDIO_SLOT(52) BFME_DEFECT_AUDIO_SLOT(53)
	BFME_DEFECT_AUDIO_SLOT(54) BFME_DEFECT_AUDIO_SLOT(55)
	BFME_DEFECT_AUDIO_SLOT(56) BFME_DEFECT_AUDIO_SLOT(57)
	BFME_DEFECT_AUDIO_SLOT(58) BFME_DEFECT_AUDIO_SLOT(59)
	BFME_DEFECT_AUDIO_SLOT(60) BFME_DEFECT_AUDIO_SLOT(61)
	BFME_DEFECT_AUDIO_SLOT(62) BFME_DEFECT_AUDIO_SLOT(63)
	BFME_DEFECT_AUDIO_SLOT(64) BFME_DEFECT_AUDIO_SLOT(65)
	BFME_DEFECT_AUDIO_SLOT(66) BFME_DEFECT_AUDIO_SLOT(67)
	BFME_DEFECT_AUDIO_SLOT(68) BFME_DEFECT_AUDIO_SLOT(69)
	BFME_DEFECT_AUDIO_SLOT(70) BFME_DEFECT_AUDIO_SLOT(71)
	BFME_DEFECT_AUDIO_SLOT(72)
	virtual Rva005A00B0MiscAudio *getMiscAudio(void) = 0;
#undef BFME_DEFECT_AUDIO_SLOT
};

// TheAudio (GameAudio.h, retail 0x012ED668) is the canonical spelling the
// linked build needs; Rva005A00B0AudioClient above is this TU's view of it.

// The __fastcall pointer puts the event in EDX and on the stack. The retail slot receives the event from the stack.
typedef UnsignedInt (__fastcall *Rva005A00B0AddAudioEventCall)(
	Rva005A00B0AudioClient *, BfmeAudioEventRTS *, BfmeAudioEventRTS *);
struct Rva005A00B0AudioClientVtable
{
	void *slots[17];
	Rva005A00B0AddAudioEventCall addAudioEvent;
};

// Retail Object::getRadarPriority (0x001CA4D0) is implemented in ObjectTemplateQueries.cpp.

// ------------------------------------------------------------------------------------------------

