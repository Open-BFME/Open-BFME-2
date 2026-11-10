// cl: /Ireference/shims/aiupdatelayout /Ireference/shims/bfme2_locomotor_flags44 /Ireference/shims/bfme_pathfinder_get_cell_link /Ireference/shims/zh_outofline /Ireference/shims/updatemodule_ctor /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to change nothing else in this unit, but if a function added later that builds
#include "../../../../../../reference/shims/bfme_namekey_inline_link/namekey_inline_link.h"  // NAMEKEY inline-only link view
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma comment(linker, "/alternatename:??1BehaviorModuleData@@QAE@XZ=??1BehaviorModuleData@@UAE@XZ")

// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp); this unit had no counterpart under Code/.
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

// AIUpdate.cpp //
// Implementation of generic AI mechanisms
// Author: Michael S. Booth, 2001-2002
// Subsequently : John Ahlquist 2002 and a cast of thousands.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#define DEFINE_LOCOMOTORSET_NAMES					// for TheLocomotorSetNames[]
#define DEFINE_AUTOACQUIRE_NAMES
#include "Common/ActionManager.h"
#include "Common/GameState.h"
#include "Common/CRCDebug.h"
#include "Common/GlobalData.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/Team.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/PerfTimer.h"
#include "Common/UnitTimings.h"
#include "Common/Xfer.h"
#include "Common/XferCRC.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"  // useful for printing quick debug strings when we need to
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Locomotor.h"
#define isInAttackState __declspec(dllimport) __forceinline isInAttackState
#define lock __declspec(dllimport) __forceinline lock
#include "Common/StateMachine.h" // Suppress unused legacy helpers before AIUpdate.h reads it.
#undef lock
#undef isInAttackState
#define setFinalPosition __declspec(dllimport) __forceinline setFinalPosition
#include "GameLogic/Module/AIUpdate.h"
#undef setFinalPosition
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/ProneUpdate.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/HackInternetAIUpdate.h"
#include "GameLogic/Module/HordeUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/TurretAI.h"
#include "GameLogic/Weapon.h"
#include "Common/Radar.h"									// For TheRadar
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<LocomotorSetType, pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > >, _Select1st<pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > > >, less<LocomotorSetType>, allocator<pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > > > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<LocomotorSetType, pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > >, _Select1st<pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > > >, less<LocomotorSetType>, allocator<pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > > > >::_M_erase(_Rb_tree_node<pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > > > *); }
namespace _STL { template <> void _Rb_tree<LocomotorSetType, pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > >, _Select1st<pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > > >, less<LocomotorSetType>, allocator<pair<LocomotorSetType const, vector<LocomotorTemplate const *, allocator<LocomotorTemplate const *> > > > >::clear(); }
// bfme link decl-only end
// BFME 2's Object keeps its behavior list at +0x244 (the matched
// Object::findModule 0x0028B6D6 walks it there), its contain module at +0x250
// and its body module at +0x254; this tree's Zero Hour Object.h has +0x18C,
// +0x190 and +0x194. This unit reads them through these functions instead of
// the header's inline getters, whose Zero Hour copies would otherwise come
// early in link order and displace every BFME 2 unit's copy (retail has no
// out-of-line Object getter: the 7-byte bodies at 0x00313E8C/93/9A are
// GameWindow text-colour getters).
static BehaviorModule **getRetailBehaviorModules( const Object *obj ) { return *(BehaviorModule ** const *)((const char *)obj + 0x244); }
static ContainModuleInterface *getRetailContain( const Object *obj ) { return *(ContainModuleInterface * const *)((const char *)obj + 0x250); }
static BodyModuleInterface *getRetailBodyModule( const Object *obj ) { return *(BodyModuleInterface * const *)((const char *)obj + 0x254); }
// Reuse the verified Coord3D push-back specialization at2CE7DC.
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D&); }


// Reuse the verified retail container providers. Native callers use the
// out-of-line map subscript and folded pointer-vector erase/append bodies;
// suppress local default copies that the census proves differ from them.
typedef _STL::vector<const LocomotorTemplate *> BfmeRetailLocomotorVector;
typedef _STL::map<LocomotorSetType, BfmeRetailLocomotorVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeRetailLocomotorVector> > > BfmeRetailLocomotorMap;
typedef _STL::pair<const LocomotorSetType, BfmeRetailLocomotorVector> BfmeRetailLocomotorPair;
namespace _STL { template<> BfmeRetailLocomotorVector& BfmeRetailLocomotorMap::operator[](const LocomotorSetType&);
template<> BfmeRetailLocomotorVector::iterator BfmeRetailLocomotorVector::erase(iterator, iterator);
template<> void BfmeRetailLocomotorVector::push_back(const value_type&);
template<> void BfmeRetailLocomotorVector::clear();
template<> void _Destroy<BfmeRetailLocomotorPair>(BfmeRetailLocomotorPair*); }
// Every use of the locomotor tree's node allocate is inlined here; the /G7
// out-of-line copy this unit would also emit is not retail's (that one is
// ThingTemplateConstructor.cpp's). Import-inline: same inline body, no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<BfmeRetailLocomotorPair> *
allocator<_Rb_tree_node<BfmeRetailLocomotorPair> >::allocate(size_type __n, const void *) const
{
    return __n != 0 ? (_Rb_tree_node<BfmeRetailLocomotorPair> *)allocator<char>::allocate(
        __n * sizeof(_Rb_tree_node<BfmeRetailLocomotorPair>), 0) : 0;
}
}

#define SLEEPY_AI

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
// AIUpdateModuleData::AIUpdateModuleData is rowed in AIUpdateModuleDataCtor.cpp; the
// Zero Hour copy here duplicated it. Its member map's default ctor stays rowed here.
template LocomotorTemplateMap::map();

//-------------------------------------------------------------------------------------------------
// AIUpdateModuleData::~AIUpdateModuleData: defined in AIUpdateModuleDataDtor.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
// ?findLocomotorTemplateVector@AIUpdateModuleData@@ present-unmatched
const LocomotorTemplateVector* AIUpdateModuleData::findLocomotorTemplateVector(LocomotorSetType t) const
{
	if (m_locomotorTemplates.empty())
		return NULL;

  LocomotorTemplateMap::const_iterator it = m_locomotorTemplates.find(t);
  if (it == m_locomotorTemplates.end()) 
	{
		return NULL;
	}
	else
	{
		return &(*it).second;
	}
}

//-------------------------------------------------------------------------------------------------
/*static*/ void AIUpdateModuleData::buildFieldParse(MultiIniFieldParse& multiIniFieldParse) 
{
  ModuleData::buildFieldParse(multiIniFieldParse);

	static const FieldParse dataFieldParse[] = 
	{
		{ "Turret",											AIUpdateModuleData::parseTurret,	NULL, offsetof(AIUpdateModuleData, m_turretData[0]) },
		{ "AltTurret",									AIUpdateModuleData::parseTurret,	NULL, offsetof(AIUpdateModuleData, m_turretData[1]) },
		{ "AutoAcquireEnemiesWhenIdle", INI::parseBitString32, TheAutoAcquireEnemiesNames, offsetof(AIUpdateModuleData, m_autoAcquireEnemiesWhenIdle) },
		{ "MoodAttackCheckRate",				INI::parseDurationUnsignedInt,		NULL, offsetof(AIUpdateModuleData, m_moodAttackCheckRate) },
#ifdef ALLOW_SURRENDER
		{ "SurrenderDuration",					INI::parseDurationUnsignedInt,		NULL, offsetof(AIUpdateModuleData, m_surrenderDuration) },
#endif
    { "ForbidPlayerCommands",				INI::parseBool,										NULL, offsetof(AIUpdateModuleData, m_forbidPlayerCommands) },
    { "TurretsLinked",							INI::parseBool,										NULL, offsetof( AIUpdateModuleData, m_turretsLinked ) },
		{ 0, 0, 0, 0 }
	};
  multiIniFieldParse.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
// AIUpdateModuleData::parseTurret: defined in AIUpdateModuleDataParseTurret.cpp
// (its row's unit; BFME 2 throws INIException and uses plain new).

//-------------------------------------------------------------------------------------------------
// AIUpdateModuleData::parseLocomotorSet: defined in AIUpdateParseLocomotorSet.cpp
// (its row's unit, 0x0026E699); this Zero Hour copy was a second definition.
// Its use of vector<const LocomotorTemplate*>::empty is this unit's row, so
// instantiate that member here.
template bool _STL::vector<const LocomotorTemplate *>::empty() const;

//-------------------------------------------------------------------------------------------------
// subclasses may want to override this, to use a subclass of AIStateMachine.
// AIUpdateInterface::makeStateMachine is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x00262513).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The BFME2 constructor is defined and byte-verified in
// AIUpdate/AIUpdateInterfaceCtor.cpp (0x0026E9BD, 984 bytes).
// This reference constructor has a different layout and must not emit a second owner.

#ifdef ALLOW_SURRENDER
//=============================================================================
// Object::setSurrendered, and related methods ================================
//=============================================================================
#endif

//=============================================================================
/* Called by the pathfinder when it processes the pathfind queue.  Basically, it's our turn
to call use the PathfindServicesInterface to do a pathfind operation.  This shouldn't be called
(and in fact is very hard to do because PathfindServicesInterace is private to the pathfinder)
except by the pathfinder during pathfind queue processing.  jba */
//-------------------------------------------------------------------------------------------------

/* Requests a path to be found.  Note that if it is possible to do it without having to use the 
pathfinder (air units just move point to point) it generates the path immediately.  Otherwise the path
will be processed when we get to the front of the pathfind queue. jba */
//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::requestPath is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface.cpp (0x0026893F).

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::requestAttackPath is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_requestAttackPath.cpp (0x00263A39).

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::requestApproachPath is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_requestApproachPath.cpp (0x00263B33).

//-------------------------------------------------------------------------------------------------
// Requests a safe path away from the repulsor.
// AIUpdateInterface::requestSafePath is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_requestSafePath.cpp (0x00263EA2).

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::setPathFromWaypoint is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_setPathFromWaypoint.cpp (0x0026569F).

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::onObjectCreated is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x002625C8).

//-------------------------------------------------------------------------------------------------
// ??1AIUpdateInterface@@MAE@XZ is rowed in its own unit; this copy collided with it.

//=============================================================================
// AIUpdateInterface::setTurretTargetObject: defined in AIUpdateInterface_setTurretTargetObject.cpp (its row's unit).
//=============================================================================

//=============================================================================
// AIUpdateInterface::setTurretTargetPosition: defined in AIUpdateInterface_setTurretTargetPosition.cpp (its row's unit).
//=============================================================================
// AIUpdateInterface::setTurretEnabled: defined in AIUpdateInterface_setTurretEnabled.cpp (its row's unit).
//=============================================================================
// AIUpdateInterface::recenterTurret: defined in AIUpdateInterface_recenterTurret.cpp (its row's unit).
//=============================================================================
// AIUpdateInterface::isTurretEnabled is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_isTurretEnabled.cpp (0x00262683).

//=============================================================================
// AIUpdateInterface::isTurretInNaturalPosition: defined in AIUpdateInterface_isTurretInNaturalPosition.cpp (its row's unit).
//=============================================================================
// AIUpdateInterface::isWeaponSlotOnTurretAndAimingAtTarget: defined in AIUpdateInterface_isWeaponSlotOnTurretAndAimingAtTarget.cpp (its row's unit).
//=============================================================================
// AIUpdateInterface::getTurretRotAndPitch: defined in AIUpdateInterface_getTurretRotAndPitch.cpp (its row's unit).
//=============================================================================
// AIUpdateInterface::getTurretTurnRate is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_getTurretTurnRate.cpp (0x00262730).

//=============================================================================
// AIUpdateInterface::getWhichTurretForCurWeapon: defined in AIUpdateInterface_getWhichTurretForCurWeapon.cpp (its row's unit).
//=============================================================================
// AIUpdateInterface::getWhichTurretForWeaponSlot is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_getWhichTurretForWeaponSlot.cpp (0x0026278A).

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
// this should only be called by load/save, or by chooseLocomotorSet.
// it does no sanity checking; it just jams it in.
//-------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
// AIUpdateInterface::checkForCrateToPickup is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_checkForCrateToPickup_Rva00268B79.cpp (0x00268B79).

#ifdef ALLOW_SURRENDER
//-------------------------------------------------------------------------------------------------
#endif

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::setQueueForPathTime is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_setQueueForPathTime.cpp (0x0026282A).

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::wakeUpNow: defined in AIUpdateInterface_wakeUpNow.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * The "main loop" of the AI subsystem
 */
DECLARE_PERF_TIMER(AIUpdateInterface_update)
// AIUpdateInterface::update is rowed at 0x0026E267 in
// AIUpdate/AIUpdateInterfaceUpdate.cpp; the Zero Hour body is not kept here.


// queueWaypoint is defined in AIUpdateInterfaceQueueWaypoint.cpp using the
// verified BFME 2 queue layout; this reference unit calls that provider.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::markAsDead is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_wakeUpNow.cpp (0x0026296D).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * See if we can do a quick path without pathfinding.
 */
// AIUpdateInterface::canComputeQuickPath is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface.cpp (0x00262A64).

//-------------------------------------------------------------------------------------------------
/**
 * Create a quick path.  (Just places the start & end point as the path). jba.
 */

//-------------------------------------------------------------------------------------------------
/**
 * Invoke the pathfinder to compute a path to the desired location.
 */

//-------------------------------------------------------------------------------------------------
/**
 * Invoke the pathfinder to compute a path to attack the current victim.
 */

//-------------------------------------------------------------------------------------------------
/**
 * Destroy the current path, and set it to NULL
 */
// AIUpdateInterface::destroyPath: defined in GameLogicDestroyObject.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * This is used by the jetai to set a specific path.
 */
// AIUpdateInterface::friend_setPath: defined in AIUpdateInterface_friendSetPath.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
/**
 * This is used by the guard tunnel network state to set a target object.
 */
// AIUpdateInterface::friend_setGoalObject: defined in AIUpdateInterface_rva00262B0F.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Is there a path at all that exists from us to the destination location */
//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::isPathAvailable: defined in AIUpdateInterface_isPathAvailable.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Is there a path (computed using the less accurate but quick method )
	* at all that exists from us to the destination location */
//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::isQuickPathAvailable: defined in AIUpdate/AIUpdateInterface_isQuickPathAvailable.cpp (its row's unit).


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
DECLARE_PERF_TIMER(doLocomotor)
/**
 * Compute drive forces
 */

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::setLocomotorGoalPositionOnPath: defined in AIUpdateInterface_setLocomotorGoalPositionExplicit.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::setLocomotorGoalPositionExplicit: defined in AIUpdateInterface_setLocomotorGoalPositionExplicit.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::setLocomotorGoalOrientation: defined in AIUpdateInterface_setLocomotorGoalPositionExplicit.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::isDoingGroundMovement is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026731C).

//-------------------------------------------------------------------------------------------------
/** Some aircraft (comanche in particular, which hover) shouldn't stack destinations.
Others, like missles, should stack destinations.  AdjustDestination in pathfinder unstacks
destinations, and this routine identifies non-ground units that should unstack. */

// AIUpdateInterface::isAircraftThatAdjustsDestination: defined in AIUpdateInterface_isAircraftThatAdjustsDestination.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
// ?joinTeam@AIUpdateInterface@@UAEXXZ is rowed in its own unit; this copy collided with it.  // end joinTeam

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::aiDoCommand is rowed at 0x002673F6 (2308B) from
// AIUpdateInterfaceAiDoCommand.cpp; this unit's duplicate 1588B
// definition displaced it in link order (S on 12 units), so only the
// declaration (from the shared header) remains and calls resolve there.

//-------------------------------------------------------------------------------------------------
// AI Command Interface implementation for AIUpdateInterface
//

//-------------------------------------------------------------------------------------------------
/**
 * Move to given object
 */
// AIUpdateInterface::privateMoveToObject is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026472F).

//----------------------------------------------------------------------------------------
// Face a specified object -- succeed when facing
//----------------------------------------------------------------------------------------
// AIUpdateInterface::privateFaceObject is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x002645B9).

//----------------------------------------------------------------------------------------
// Face a specified position -- succeed when facing
//----------------------------------------------------------------------------------------
// AIUpdateInterface::privateFacePosition is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x00267D65).

//----------------------------------------------------------------------------------------
// Rappel into target and devastate contents (if not empty).
// If target is null, rappel to ground.
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
/**
 * Move to given position(s)
 * If transportExits, transport returns and deletes itself.
 */
// AIUpdateInterface::privateMoveToAndEvacuate is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026B6B2).

//----------------------------------------------------------------------------------------
/**
 * Move to given position(s)
 * If transportExits, transport returns and deletes itself.
 */
// AIUpdateInterface::privateMoveToAndEvacuateAndExit is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026B720).

//----------------------------------------------------------------------------------------
/**
 * Enter idle state.
 */
// AIUpdateInterface::privateIdle is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026D5FB).

//----------------------------------------------------------------------------------------
// ?isIdle@AIUpdateInterface@@ present-unmatched
Bool AIUpdateInterface::isIdle() const
{
	const AIStateMachine *state = getStateMachine();
	if( state->getCurrentStateID() == AI_IDLE )
	{
		return TRUE;
	}
	return state->isInIdleState();
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//Definition of busy -- when explicitly in the busy state. Moving or attacking is not considered busy!
//----------------------------------------------------------------------------------------
// AIUpdateInterface::isBusy is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_rva00262BEC.cpp (0x00262B39).

//----------------------------------------------------------------------------------------
// AIUpdateInterface::isClearingMines is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x00264656).

//----------------------------------------------------------------------------------------
/**
 * Take the shortest path towards pos in order to tighten up a formation
 */
// AIUpdateInterface::privateTightenToPosition is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x00267DAD).
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
/**
 * Is this moving out of the way of another unit.
 */
// AIUpdateInterface::isMoving is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceIsMoving.cpp (0x00264688).

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
/**
 * Start following the path from the given point
 */
// AIUpdateInterface::privateFollowWaypointPath is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026B8E5).

//----------------------------------------------------------------------------------------
/**
 * Start following the path from the given point
 */
// AIUpdateInterface::privateFollowWaypointPathExact is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate_AIUpdateInterface_privateFollowWaypointPathAsTeamExact.cpp (0x0026B987).

//----------------------------------------------------------------------------------------
/**
 * Start following the path from the given point
 */
// AIUpdateInterface::privateFollowWaypointPathAsTeam is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate_AIUpdateInterface_privateFollowWaypointPathAsTeam.cpp (0x0026B9E2).

//----------------------------------------------------------------------------------------
/**
 * Start following the path from the given point
 */
// AIUpdateInterface::privateFollowWaypointPathAsTeamExact is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate_AIUpdateInterface_privateFollowWaypointPathAsTeamExact.cpp (0x0026BA33).

//----------------------------------------------------------------------------------------
// AIUpdateInterface::privateFollowPathAppend is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026E074).

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
/**
 * Attack given object
 */
// AIUpdateInterface::privateAttackObject (0x0026BCD2) is rowed in AIUpdateInterfaceAttackObjectCommands.cpp; a second definition here would not link.

//-----------------------------------------------------------------------------------------
// AIUpdateInterface::privateForceAttackObject (0x0026BEE6) is rowed in AIUpdateInterfaceAttackObjectCommands.cpp; a second definition here would not link.

//-----------------------------------------------------------------------------------------
// AIUpdateInterface::privateGuardRetaliate: defined in AIUpdate/AIUpdateInterface_privateGuardRetaliate.cpp (its row's unit).

//----------------------------------------------------------------------------------------
/**
 * Attack the given team
 */
// AIUpdateInterface::privateAttackTeam is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026BFD9).

// The Zero Hour needToRotate, privateAttackMoveToPosition and the two-argument
// getTurretTargetObject (gone: no retail row; their Path::computePointOnPath,
// PartitionManager::getRelativeAngle2D, setGoalPositionClipped and Zero Hour
// TurretAI::friend_getTurretTarget callees have no BFME 2 definer) were this
// unit's only users of the rowed header inlines OVERRIDE<LocomotorTemplate>::
// operator-> (0x0035C95F) and Weapon::setMaxShotCount (0x00661D50); compile
// anchors, not retail data claims, keep them emitted.
extern const LocomotorTemplate *(OVERRIDE<LocomotorTemplate>::*const _bfmeInlineAnchorLocomotorTemplateOverride)() const =
    &OVERRIDE<LocomotorTemplate>::operator->;
extern void (Weapon::*const _bfmeInlineAnchorWeaponSetMaxShotCount)(Int) =
    &Weapon::setMaxShotCount;


//----------------------------------------------------------------------------------------
/**
 * Attack move to the given location
 */

//----------------------------------------------------------------------------------------
/**
 * Attack move down a given waypoint path. If asTeam is TRUE, do so as a team.
 */
// AIUpdateInterface::privateAttackFollowWaypointPath is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026C150).


//----------------------------------------------------------------------------------------
/**
 * Begin "seek and destroy"
 */
// AIUpdateInterface::privateHunt is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x002646E9).

//----------------------------------------------------------------------------------------
/**
 * Begin "seek and destroy"
 */
// AIUpdateInterface::privateAttackArea is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026C1CE).

//----------------------------------------------------------------------------------------
#ifdef ALLOW_SURRENDER
//----------------------------------------------------------------------------------------
#endif

#ifdef ALLOW_SURRENDER
//----------------------------------------------------------------------------------------
#endif

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
/**
 * Get healed at the heal depot
 */
// AIUpdateInterface::privateGetHealed is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026DD89).

//----------------------------------------------------------------------------------------
/**
 * Get repaired at the repair depot
 */
// AIUpdateInterface::privateGetRepaired is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026DDBB).

//----------------------------------------------------------------------------------------
/**
 * Enter the given object
 */
// AIUpdateInterface::privateEnter is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x00264775).

//----------------------------------------------------------------------------------------
/**
 * Dock with the given object
 */
// AIUpdateInterface::privateDock is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate_AIUpdateInterface_privateDock.cpp (0x0026481B).

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
/**
 * Get out of whatever it is inside of this frame
 */
// AIUpdateInterface::privateExitInstantly is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026488B).


//----------------------------------------------------------------------------------------
/**
 * Get out of whatever it is inside of
 */
// AIUpdateInterface::doQuickExit is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x00262F19).

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
///< life altering state change, if this AI can do it
#pragma optimize("s", on)
void AIUpdateInterface::privateGoProne( const DamageInfo *damageInfo, CommandSourceType )
{
	static NameKeyType proneModuleKey = TheNameKeyGenerator->nameToKey( "ProneUpdate" );
	ProneUpdate *proneModule = (ProneUpdate *)getObject()->findUpdateModule( proneModuleKey );

	if( proneModule )
		proneModule->goProne( damageInfo );
}
#pragma optimize("", on)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * Guard the given spot
 */
// AIUpdateInterface::privateGuardPosition is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateGuardPosition.cpp (0x00264BC2).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
 * Guard the given spot
 */
// AIUpdateInterface::privateGuardObject is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateGuardObject.cpp (0x00264D0E).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// if we are attacking "fromID", stop that and attack "toID" instead
// AIUpdateInterface::transferAttack is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate_AIUpdateInterface_transferAttack.cpp (0x00268CDC).

//----------------------------------------------------------------------------------------------------------
/**
 * Indicate who we are attacking.
 */
// AIUpdateInterface::setCurrentVictim: defined in AIUpdateInterface_setCurrentVictim.cpp (its row's unit).
/**
 * Who is our current victim?
 */
// AIUpdateInterface::getCurrentVictim: defined in AIUpdateInterface_getCurrentVictim.cpp (its row's unit).
// if we are attacking a position (and NOT an object), return it. otherwise return null.

/**
 * Get the current behavior modifier state	
 */

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::ignoreObstacle: defined in AIUpdateInterfaceIgnoreObstacle.cpp (its row's unit).
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::getIgnoredObstacleID: defined in AIUpdateInterfaceIgnoreObstacle.cpp (its row's
// unit at retail 0x0006E009). This TU's ZH-layout view reads +0x154, retail reads +0x164, so the
// local copy lost the COMDAT and S-blocked consumers; the home copy emits retail's bytes.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::getEnterTarget is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x00264EF2).

//-------------------------------------------------------------------------------------------------
void AIUpdateInterface::setLastCommandSource( CommandSourceType source )
{
	m_lastCommandSource = source; 
}

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::getMoodMatrixValue is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_getMoodMatrixActionAdjustment.cpp (0x00264F5E).

//-------------------------------------------------------------------------------------------------
// AIUpdateInterface::getMoodMatrixActionAdjustment is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_getMoodMatrixActionAdjustment.cpp (0x00264FF8).

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
/**
 * Return the next object that our mood suggests we should attack.
 */

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
#ifdef ALLOW_DEMORALIZE
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
#endif

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// AIUpdateInterface::privateCommandButton is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x0026DE77).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// AIUpdateInterface::privateCommandButtonPosition is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x00267E8E).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// AIUpdateInterface::loadPostProcess is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp (0x002686A4).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
