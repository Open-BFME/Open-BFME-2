// cl: /FIzh_ascii.h /Ireference/shims/bfme2_drawable_flash /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/weapon_outofline /Ireference/shims/zh_outofline /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Weapon.cpp); this unit had no counterpart under Code/.
// Only its rowed bodies, TheWeaponStore and WeaponStore::findWeaponTemplate
// (InstantDeathBehavior.cpp calls it) remain. The unrowed Zero Hour field table,
// fireWeaponTemplate, privateFireWeapon/fireWeapon, the Weapon copy constructor
// (whose vtable named Zero Hour's crc/xfer/loadPostProcess) and the two
// object-victim line-of-sight overloads matched no retail body, no other object
// referenced them, and they made 24 references no object defines.
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

// FILE: Weapon.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Weapon descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <string.h>
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#define DEFINE_DEATH_NAMES
#define DEFINE_WEAPONBONUSCONDITION_NAMES
#define DEFINE_WEAPONBONUSFIELD_NAMES
#define DEFINE_WEAPONCOLLIDEMASK_NAMES
#define DEFINE_WEAPONAFFECTSMASK_NAMES
#define DEFINE_WEAPONRELOAD_NAMES
#define DEFINE_WEAPONPREFIRE_NAMES

#include "Common/CRC.h"
#include "Common/CRCDebug.h"
#include "Common/GameAudio.h"
#include "Common/GameState.h"
#include "Common/INI.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
 
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/InGameUI.h"
#include "GameClient/ParticleSys.h"

#include "GameLogic/Damage.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/LaserUpdate.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/SpecialPowerCompletionDie.h"
#include "GameLogic/Module/AssaultTransportAIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/AssistedTargetingUpdate.h"
#include "GameLogic/Module/ProjectileStreamUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/TerrainLogic.h"

#define RATIONALIZE_ATTACK_RANGE
#define ATTACK_RANGE_IS_2D

#ifdef ATTACK_RANGE_IS_2D
	const DistanceCalculationType ATTACK_RANGE_CALC_TYPE = FROM_BOUNDINGSPHERE_2D;
#else
	const DistanceCalculationType ATTACK_RANGE_CALC_TYPE = FROM_BOUNDINGSPHERE_3D;
#endif

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// damage is ALWAYS 3d
const DistanceCalculationType DAMAGE_RANGE_CALC_TYPE = FROM_BOUNDINGSPHERE_3D;

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
WeaponStore *TheWeaponStore = NULL;					///< the weapon store definition


///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------

// WeaponTemplate::WeaponTemplate(): dropped so this TU stops emitting the non-retail
// ??0WeaponTemplate@@QAE@XZ copy that came first in link order ahead of retail's rowed
// owner (0x002CD169, Rva002CD169Ctor.cpp), whose REL32 pin this TU's callers bind to.

//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// WeaponTemplate::parseScatterTarget: defined in WeaponTemplateParseScatterTarget.cpp
// (its row's unit, BFME 2 layout).

//-------------------------------------------------------------------------------------------------
// WeaponTemplate::parseShotDelay is defined in WeaponParseShotDelayClip.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// WeaponTemplate::getMinimumAttackRange: defined in WeaponTemplateMinimumRange.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// WeaponTemplate::getClipReloadTime: defined in WeaponTemplateClipReloadTime.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
Bool WeaponTemplate::isContactWeapon() const
{
	// BFME 2 retail: the call from privateAttackPosition (0x0026DC3F) lands on the shared
	// xor al,al / ret false-predicate stub at 0x0047A699 (rowed here as an ICF twin), so the Zero Hour
	// attack-range test (PATHFIND_CELL_SIZE_F cutoff) is gone.
	return false;
}

//-------------------------------------------------------------------------------------------------
// The collide-with body lives under WeaponTemplateShouldProjectileCollideWith.cpp
// (retail row); this TU keeps only the class declaration so callers bind the
// kept copy and this unit emits no competing COMDAT.


//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// WeaponStore::WeaponStore(): dropped so this TU stops emitting the non-retail
// ??0WeaponStore@@QAE@XZ copy that came first in link order ahead of retail's rowed
// owner (0x002CC20E, Rva002CC20ECtor.cpp), whose REL32 pin this TU's callers bind to.

//-------------------------------------------------------------------------------------------------
// Retail's complete destructor at 0x002CCD56 and deleting destructor at
// 0x002CD5E0 are byte-verified in Rva002CCD56Dtor.cpp. The Zero Hour body
// here emitted a different destructor and subsystem table; keep that owner
// until the split WeaponStore/Rva002CCD56 class views are reconciled.

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Owned by WeaponStoreCreateAndFireTempWeapon.cpp.

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const WeaponTemplate *WeaponStore::findWeaponTemplate( AsciiString name ) const 
{ 
	// Retail's comparison stub imports msvcr71's _strcmpi.
	if (_strcmpi(name.str(), "None") == 0)
		return NULL;
	const WeaponTemplate * wt = findWeaponTemplatePrivate( TheNameKeyGenerator->nameToKey( name ) );
	DEBUG_ASSERTCRASH(wt != NULL, ("Weapon %s not found!\n",name.str()));
	return wt;
}

//-------------------------------------------------------------------------------------------------
// WeaponStore::findWeaponTemplatePrivate is defined with its verified retail body
// in WeaponStoreNewOverride.cpp (0x002CADBE); keep one definition for the class.

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// WeaponStore::resetWeaponTemplates is rowed in its home unit; this copy was a duplicate definition.

//-------------------------------------------------------------------------------------------------
// WeaponStore::reset is rowed in its home unit; this copy was a duplicate definition.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// WeaponStore::postProcessLoad is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/WeaponStorePostProcessLoad.cpp (0x002CADFA).

//-------------------------------------------------------------------------------------------------
// WeaponStore::parseWeaponTemplateDefinition has its BFME 2 retail body in
// WeaponStoreNewOverride.cpp (0x002CE102).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Weapon::Weapon(const WeaponTemplate*, WeaponSlotType) lives in WeaponCtor.cpp
// (its row's unit); this file merely declares it via the Weapon header.

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Weapon::~Weapon: defined in WeaponDtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// Weapon::computeBonus: defined in WeaponComputeBonus.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// Weapon::loadAmmoNow: defined in WeaponLoadAmmoNow.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// Weapon::reloadAmmo: defined in WeaponReloadAmmo.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// Weapon::rebuildScatterTargets: defined in WeaponRebuildScatterTargets.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// Weapon::reloadWithBonus: defined in WeaponReloadWithBonus.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// clipToTerrainExtent: defined in WeaponComputeApproachTarget.cpp beside its one caller.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Weapon::computeApproachTarget: defined in WeaponComputeApproachTarget.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//Special case attack range calculate that fakes moving the object (to a garrisoned point) without
//actually moving the object. This is used to help determine if a garrisoned unit not yet 
//positioned can attack someone.
//-------------------------------------------------------------------------------------------------
// BFME2 range test is owned by WeaponRva002CB2D1Range.cpp.


//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Owned by Rva002C96D8Finish.cpp.

//-------------------------------------------------------------------------------------------------
// Owned by WeaponIsTooClose.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Weapon::getPercentReadyToFire is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva002CCE53Finish.cpp (0x002CCE53).

//-------------------------------------------------------------------------------------------------
// Weapon::getAttackRange is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Weapon_Weapon_getAttackRange.cpp (0x002C9BF8).

//-------------------------------------------------------------------------------------------------
// Weapon::getAttackDistance is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/PartitionManager_Rva002C9C37.cpp (0x002C9C37).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// return true if we auto-reloaded our clip after firing.
//DECLARE_PERF_TIMER(fireWeapon)


//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// return true if we auto-reloaded our clip after firing.

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//Currently, this function was added to allow a script to force fire a weapon,
//and immediately gain control of the weapon that was fired to give it special orders...
// Weapon::forceFireWeapon: defined in WeaponPrivateFireWrappers_O1.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// Weapon::getStatus: defined in WeaponGetStatus.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// Weapon::isWithinTargetPitch: defined in WeaponIsWithinTargetPitch.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// The assistance callback and its request data live with the verified caller
// in WeaponRva002C9DF5.cpp; BFME 2's callback returns int.
// Weapon::processRequestAssistance (0x002C9DF5) is defined with its retail body in WeaponRva002C9DF5.cpp.

//-------------------------------------------------------------------------------------------------
// Weapon::calcProjectileLaunchPosition (0x002C9E48) is defined with its retail body in WeaponProjectileLaunch.cpp.

//-------------------------------------------------------------------------------------------------
// Weapon::positionProjectileForLaunch (0x002CA753) is defined with its retail body in Weapon_positionProjectileForLaunch_Rva002CA753.cpp.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#pragma auto_inline(off)
void Weapon::getFiringLineOfSightOrigin(const Object* source, Coord3D& origin) const
{
	//GS 1-6-03
	// Sorry, but we have to simplify this.  If we take the actual projectile launch pos, then
	// that point can change. Take a Ranger with his gun on his shoulder.  His point is very high so 
	// he clears this check and transitions to attacking.  This puts his gun at waist level and
	// now he fails this check so he transitions back.  Our height won't change.
	origin.z += source->getGeometryInfo().getMaxHeightAbovePosition();

/*
	if (m_template->getProjectileTemplate() == NULL)
	{
		// note that we want to measure from the top of the collision
		// shape, not the bottom! (most objects have eyes a lot closer
		// to their head than their feet. if we have really odd critters
		// with eye-feet, we'll need to change this assumption.)
		origin.z += source->getGeometryInfo().getMaxHeightAbovePosition();
	}
	else
	{
		Matrix3D tmp(true);
		Coord3D launchPos = {0.0f, 0.0f, 0.0f};
		calcProjectileLaunchPosition(source, m_wslot, m_curBarrel, tmp, launchPos);
		origin.x += launchPos.x - source->getPosition()->x;
		origin.y += launchPos.y - source->getPosition()->y;
		origin.z += launchPos.z - source->getPosition()->z;
	}
*/
}
#pragma auto_inline(on)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME 2's TerrainLogic declares two more virtuals ahead of isClearLineOfSight
// than Zero Hour's header: retail calls it through slot 15 (0x3C) of
// TheTerrainLogic, and slot 15 of the W3DTerrainLogic vftable 0x00BC5890 is the
// rowed W3DTerrainLogic::isClearLineOfSight (0x00062C0F).
class BfmeTerrainLogicLOSView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual Bool isClearLineOfSight( const Coord3D& pos, const Coord3D& posOther ) const;
};

// BFME 2 dropped the victim-centre and NULL-object arguments: both Coord3D
// variants below ask the terrain directly.
Bool Weapon::isClearFiringLineOfSightTerrain(const Object* source, const Coord3D& victimPos) const
{
	Coord3D origin;
	origin = *source->getPosition();
	//CRCDEBUG_LOG(("Weapon::isClearFiringLineOfSightTerrain(Coord3D) for %s\n", DescribeObject(source).str()));
	//DUMPCOORD3D(&origin);
	getFiringLineOfSightOrigin(source, origin);
	return ((const BfmeTerrainLogicLOSView *)TheTerrainLogic)->isClearLineOfSight(origin, victimPos);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** Determine whether if source was at goalPos whether it would have clear line of sight. */

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** Determine whether if source was at goalPos whether it would have clear line of sight. */
Bool Weapon::isClearGoalFiringLineOfSightTerrain(const Object* source, const Coord3D& goalPos, const Coord3D& victimPos) const
{
	Coord3D origin;
	origin.x = goalPos.x;
	origin.y = goalPos.y;
	origin.z = goalPos.z;
	//CRCDEBUG_LOG(("Weapon::isClearGoalFiringLineOfSightTerrain(Coord3D) for %s\n", DescribeObject(source).str()));
	//DUMPCOORD3D(&origin);
	getFiringLineOfSightOrigin(source, origin);
	//CRCDEBUG_LOG(("Weapon::isClearFiringLineOfSightTerrain() - victimPos is (%g,%g,%g) (%X,%X,%X)\n",
	//	victimPos.x, victimPos.y, victimPos.z,
	//	AS_INT(victimPos.x),AS_INT(victimPos.y),AS_INT(victimPos.z)));
	return ((const BfmeTerrainLogicLOSView *)TheTerrainLogic)->isClearLineOfSight(origin, victimPos);
}

//-------------------------------------------------------------------------------------------------
//Kris: Patch 1.01 - November 10, 2003
//This function was added to transfer key weapon stats for Jarmen Kell to and from the bike for
//the sniper attack, so he can share the stats.
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// WeaponBonus::appendBonuses: defined in WeaponBonusAppend.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/*static*/ void WeaponBonusSet::parseWeaponBonusSet(INI* ini, void* /*instance*/, void* store, const void* /*userData*/)
{
	WeaponBonusSet* self = (WeaponBonusSet*)store;
	self->parseWeaponBonusSet(ini);
}

//-------------------------------------------------------------------------------------------------
/*static*/ void WeaponBonusSet::parseWeaponBonusSetPtr(INI* ini, void* /*instance*/, void* store, const void* /*userData*/)
{
	WeaponBonusSet** selfPtr = (WeaponBonusSet**)store;
	(*selfPtr)->parseWeaponBonusSet(ini);
}

//-------------------------------------------------------------------------------------------------
// WeaponBonusSet::parseWeaponBonusSet(INI*): the retail body is the 90-byte rowed
// 0x002C971E operation in WeaponBonusParse.cpp. This TU's inline select-any copy came
// first in link order and is not retail's; declared only here, so the two static
// wrappers above and WeaponTemplate::parseWeaponBonusSet above bind to retail's owner.
//
// That copy was also the only call site of the header inline WeaponBonus::setField,
// whose 18-byte row (0x002C8E40) this TU owns. Taking its address keeps this unit's
// select-any copy emitted; this pointer is not retail data.
void (WeaponBonus::*_bfmeInlineAnchor_WeaponBonusSetSetField)(WeaponBonus::Field, Real) = &WeaponBonus::setField;

// The header inline Weapon::setLeechRangeActive (10-byte row 0x002D95FE, no
// approved TU) was emitted here only through the dropped Zero Hour
// privateFireWeapon. Taking its address keeps this unit's select-any copy
// emitted; this pointer is not retail data.
void (Weapon::*_bfmeInlineAnchor_WeaponSetLeechRangeActive)(Bool) = &Weapon::setLeechRangeActive;

//-------------------------------------------------------------------------------------------------
// WeaponBonusSet::appendBonuses: defined in WeaponBonusAppend.cpp (its row's unit).
