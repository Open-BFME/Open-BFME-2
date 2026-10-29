// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/weapon_outofline /Ireference/shims/zh_outofline /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Weapon.cpp); this unit had no counterpart under Code/.
// Retail imports only _strcmpi (stub 0x00629A2A calls msvcr71's); BFME2's
// stricmp spelling resolves there, not to the _stricmp alias.
#define stricmp _strcmpi
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
static void parsePerVetLevelAsciiString( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ )
{
	AsciiString* asciiString = (AsciiString*)store;
	VeterancyLevel v = (VeterancyLevel)INI::scanIndexList(ini->getNextToken(), TheVeterancyNames);
	asciiString[v] = ini->getNextAsciiString();
}

//-------------------------------------------------------------------------------------------------
static void parseAllVetLevelsAsciiString( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ )
{
	AsciiString* asciiString = (AsciiString*)store;
	AsciiString a = ini->getNextAsciiString();
	for (Int i = LEVEL_FIRST; i <= LEVEL_LAST; ++i)
		asciiString[i] = a;
}

//-------------------------------------------------------------------------------------------------
// The FXList and PSys vet-level parsers live in WeaponParseVetLevels.cpp (member
// scanIndexList form); declared here for the field table below.
void parsePerVetLevelFXList( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ );
void parseAllVetLevelsFXList( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ );
void parsePerVetLevelPSys( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ );
void parseAllVetLevelsPSys( INI* ini, void* /*instance*/, void * store, const void* /*userData*/ );

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
WeaponStore *TheWeaponStore = NULL;					///< the weapon store definition


///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
const FieldParse WeaponTemplate::TheWeaponTemplateFieldParseTable[] = 
{

	{ "PrimaryDamage",						INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_primaryDamage) },		
	{ "PrimaryDamageRadius",			INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_primaryDamageRadius) },		
	{ "SecondaryDamage",					INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_secondaryDamage) },		
	{ "SecondaryDamageRadius",		INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_secondaryDamageRadius) },		
	{ "ShockWaveAmount",					INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_shockWaveAmount) },		
	{ "ShockWaveRadius",					INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_shockWaveRadius) },		
	{ "ShockWaveTaperOff",				INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_shockWaveTaperOff) },		
	{ "AttackRange",							INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_attackRange) },		
	{ "MinimumAttackRange",				INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_minimumAttackRange) },		
	{ "RequestAssistRange",				INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_requestAssistRange) },		
	{ "AcceptableAimDelta",				INI::parseAngleReal,										NULL,							offsetof(WeaponTemplate, m_aimDelta) },		
	{ "ScatterRadius",						INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_scatterRadius) },		
	{ "ScatterTargetScalar",			INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_scatterTargetScalar) },		
	{ "ScatterRadiusVsInfantry",	INI::parseReal,													NULL,							offsetof( WeaponTemplate, m_infantryInaccuracyDist ) },
	{ "DamageType",								DamageTypeFlags::parseSingleBitFromINI,	NULL,							offsetof(WeaponTemplate, m_damageType) },		
	{ "DamageStatusType",					ObjectStatusMaskType::parseSingleBitFromINI,	NULL,				offsetof(WeaponTemplate, m_damageStatusType) },		
	{ "DeathType",								INI::parseIndexList,										TheDeathNames,		offsetof(WeaponTemplate, m_deathType) },		
	{ "WeaponSpeed",							INI::parseVelocityReal,									NULL,							offsetof(WeaponTemplate, m_weaponSpeed) },		
	{ "MinWeaponSpeed",						INI::parseVelocityReal,									NULL,							offsetof(WeaponTemplate, m_minWeaponSpeed) },		
	{ "ScaleWeaponSpeed",					INI::parseBool,													NULL,							offsetof(WeaponTemplate, m_isScaleWeaponSpeed) },		
	{ "WeaponRecoil",							INI::parseAngleReal,										NULL,							offsetof(WeaponTemplate, m_weaponRecoil) },		
	{ "MinTargetPitch",						INI::parseAngleReal,										NULL,							offsetof(WeaponTemplate, m_minTargetPitch) },		
	{ "MaxTargetPitch",						INI::parseAngleReal,										NULL,							offsetof(WeaponTemplate, m_maxTargetPitch) },		
	{ "RadiusDamageAngle",				INI::parseAngleReal,										NULL,							offsetof(WeaponTemplate, m_radiusDamageAngle) },		
	{ "ProjectileObject",					INI::parseAsciiString,									NULL,							offsetof(WeaponTemplate, m_projectileName) },		
	{ "FireSound",								INI::parseAudioEventRTS,								NULL,							offsetof(WeaponTemplate, m_fireSound) },		
	{ "FireSoundLoopTime",				INI::parseDurationUnsignedInt,					NULL,							offsetof(WeaponTemplate, m_fireSoundLoopTime) },		
	{ "FireFX",											parseAllVetLevelsFXList,							NULL,							offsetof(WeaponTemplate, m_fireFXs) },		
	{ "ProjectileDetonationFX",			parseAllVetLevelsFXList,							NULL,							offsetof(WeaponTemplate, m_projectileDetonateFXs) },		
	{ "FireOCL",										parseAllVetLevelsAsciiString,					NULL,							offsetof(WeaponTemplate, m_fireOCLNames) },		
	{ "ProjectileDetonationOCL",		parseAllVetLevelsAsciiString,					NULL,							offsetof(WeaponTemplate, m_projectileDetonationOCLNames) },		
	{ "ProjectileExhaust",					parseAllVetLevelsPSys,								NULL,							offsetof(WeaponTemplate, m_projectileExhausts) },		
	{ "VeterancyFireFX",										parsePerVetLevelFXList,				NULL,							offsetof(WeaponTemplate, m_fireFXs) },		
	{ "VeterancyProjectileDetonationFX",		parsePerVetLevelFXList,				NULL,							offsetof(WeaponTemplate, m_projectileDetonateFXs) },		
	{ "VeterancyFireOCL",										parsePerVetLevelAsciiString,	NULL,							offsetof(WeaponTemplate, m_fireOCLNames) },		
	{ "VeterancyProjectileDetonationOCL",		parsePerVetLevelAsciiString,	NULL,							offsetof(WeaponTemplate, m_projectileDetonationOCLNames) },		
	{ "VeterancyProjectileExhaust",					parsePerVetLevelPSys,					NULL,							offsetof(WeaponTemplate, m_projectileExhausts) },		
	{ "ClipSize",									INI::parseInt,													NULL,							offsetof(WeaponTemplate, m_clipSize) },		
	{ "ContinuousFireOne",				INI::parseInt,													NULL,							offsetof(WeaponTemplate, m_continuousFireOneShotsNeeded) },		
	{ "ContinuousFireTwo",				INI::parseInt,													NULL,							offsetof(WeaponTemplate, m_continuousFireTwoShotsNeeded) },		
	{ "ContinuousFireCoast",			INI::parseDurationUnsignedInt,					NULL,							offsetof(WeaponTemplate, m_continuousFireCoastFrames) },		
 	{ "AutoReloadWhenIdle",				INI::parseDurationUnsignedInt,					NULL,							offsetof(WeaponTemplate, m_autoReloadWhenIdleFrames) },		
	{ "ClipReloadTime",						INI::parseDurationUnsignedInt,					NULL,							offsetof(WeaponTemplate, m_clipReloadTime) },		
	{ "DelayBetweenShots",				WeaponTemplate::parseShotDelay,					NULL,							0 },
	{ "ShotsPerBarrel",						INI::parseInt,													NULL,							offsetof(WeaponTemplate, m_shotsPerBarrel) },
	{ "DamageDealtAtSelfPosition",INI::parseBool,													NULL,							offsetof(WeaponTemplate, m_damageDealtAtSelfPosition) },		
	{ "RadiusDamageAffects",			INI::parseBitString32,	TheWeaponAffectsMaskNames,				offsetof(WeaponTemplate, m_affectsMask) },		
	{ "ProjectileCollidesWith",		INI::parseBitString32,	TheWeaponCollideMaskNames,				offsetof(WeaponTemplate, m_collideMask) },		
	{ "AntiAirborneVehicle",			INI::parseBitInInt32,										(void*)WEAPON_ANTI_AIRBORNE_VEHICLE,	offsetof(WeaponTemplate, m_antiMask) },		
	{ "AntiGround",								INI::parseBitInInt32,										(void*)WEAPON_ANTI_GROUND,						offsetof(WeaponTemplate, m_antiMask) },		
	{ "AntiProjectile",						INI::parseBitInInt32,										(void*)WEAPON_ANTI_PROJECTILE,				offsetof(WeaponTemplate, m_antiMask) },		
	{ "AntiSmallMissile",					INI::parseBitInInt32,										(void*)WEAPON_ANTI_SMALL_MISSILE,			offsetof(WeaponTemplate, m_antiMask) },
	{ "AntiMine",									INI::parseBitInInt32,										(void*)WEAPON_ANTI_MINE,							offsetof(WeaponTemplate, m_antiMask) },
	{ "AntiParachute",						INI::parseBitInInt32,										(void*)WEAPON_ANTI_PARACHUTE,					offsetof(WeaponTemplate, m_antiMask) },
	{ "AntiAirborneInfantry",			INI::parseBitInInt32,										(void*)WEAPON_ANTI_AIRBORNE_INFANTRY, offsetof(WeaponTemplate, m_antiMask) },
	{ "AntiBallisticMissile",			INI::parseBitInInt32,										(void*)WEAPON_ANTI_BALLISTIC_MISSILE, offsetof(WeaponTemplate, m_antiMask) },
	{ "AutoReloadsClip",					INI::parseIndexList,										TheWeaponReloadNames,							offsetof(WeaponTemplate, m_reloadType) },		
	{ "ProjectileStreamName",			INI::parseAsciiString,									NULL,							offsetof(WeaponTemplate, m_projectileStreamName) },
	{ "LaserName",								INI::parseAsciiString,									NULL,							offsetof(WeaponTemplate, m_laserName) },
	{ "LaserBoneName",						INI::parseAsciiString,									NULL,							offsetof(WeaponTemplate, m_laserBoneName) },
	{ "WeaponBonus",							WeaponTemplate::parseWeaponBonusSet,		NULL,							0 },		
	{ "HistoricBonusTime",				INI::parseDurationUnsignedInt,					NULL,							offsetof(WeaponTemplate, m_historicBonusTime) },		
	{ "HistoricBonusRadius",			INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_historicBonusRadius) },		
	{ "HistoricBonusCount",				INI::parseInt,													NULL,							offsetof(WeaponTemplate, m_historicBonusCount) },		
	{ "HistoricBonusWeapon",			INI::parseWeaponTemplate,								NULL,							offsetof(WeaponTemplate, m_historicBonusWeapon) },		
	{ "LeechRangeWeapon",					INI::parseBool,													NULL,							offsetof(WeaponTemplate, m_leechRangeWeapon) },
	{ "ScatterTarget",						WeaponTemplate::parseScatterTarget,			NULL,							0 },		
	{ "CapableOfFollowingWaypoints", INI::parseBool,											NULL,							offsetof(WeaponTemplate, m_capableOfFollowingWaypoint) },
	{ "ShowsAmmoPips",						INI::parseBool,													NULL,							offsetof(WeaponTemplate, m_isShowsAmmoPips) },
	{ "AllowAttackGarrisonedBldgs", INI::parseBool,												NULL,							offsetof(WeaponTemplate, m_allowAttackGarrisonedBldgs) },
	{ "PlayFXWhenStealthed",			INI::parseBool,													NULL,							offsetof(WeaponTemplate, m_playFXWhenStealthed) },
	{ "PreAttackDelay",						INI::parseDurationUnsignedInt,					NULL,							offsetof( WeaponTemplate, m_preAttackDelay ) },
	{ "PreAttackType",						INI::parseIndexList,										TheWeaponPrefireNames, offsetof(WeaponTemplate, m_prefireType) },		
	{ "ContinueAttackRange",			INI::parseReal,													NULL,							offsetof(WeaponTemplate, m_continueAttackRange) },
	{ "SuspendFXDelay",						INI::parseDurationUnsignedInt,					NULL,							offsetof(WeaponTemplate, m_suspendFXDelay) },		
	{ "MissileCallsOnDie",			INI::parseBool,													NULL,							offsetof(WeaponTemplate, m_dieOnDetonate) },
	{ NULL,												NULL,																		NULL,							0 }  // keep this last

};

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------

// WeaponTemplate::WeaponTemplate(): dropped so this TU stops emitting the non-retail
// ??0WeaponTemplate@@QAE@XZ copy that came first in link order ahead of retail's rowed
// owner (0x002CD169, Rva002CD169Ctor.cpp), whose REL32 pin this TU's callers bind to.

//-------------------------------------------------------------------------------------------------
// ??1WeaponTemplate@@ present-unmatched
WeaponTemplate::~WeaponTemplate()
{
	if (m_nextTemplate) {
		m_nextTemplate->deleteInstance();
	}

	// delete any extra-bonus that's present
	if (m_extraBonus)
		m_extraBonus->deleteInstance();
}

// ------------------------------------------------------------------------------------------------
// ?reset@WeaponTemplate@@ present-unmatched
void WeaponTemplate::reset( void )
{
	m_historicDamage.clear();
}  // end reset

//-------------------------------------------------------------------------------------------------
/*static*/ void WeaponTemplate::parseWeaponBonusSet( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	WeaponTemplate* self = (WeaponTemplate*)instance;

	if (!self->m_extraBonus)
		self->m_extraBonus = newInstance(WeaponBonusSet);

	self->m_extraBonus->parseWeaponBonusSet(ini);
}

//-------------------------------------------------------------------------------------------------
// WeaponTemplate::parseScatterTarget: defined in WeaponTemplateParseScatterTarget.cpp
// (its row's unit, BFME 2 layout).

//-------------------------------------------------------------------------------------------------
// WeaponTemplate::parseShotDelay is defined in WeaponParseShotDelayClip.cpp.

//-------------------------------------------------------------------------------------------------
// ?postProcessLoad@WeaponTemplate@@ present-unmatched
void WeaponTemplate::postProcessLoad()
{
	if (!TheThingFactory)
	{
		DEBUG_CRASH(("you must call this after TheThingFactory is inited"));
		return;
	}
	
	if (m_projectileName.isEmpty())
	{
		m_projectileTmpl = NULL;
	}
	else
	{
		m_projectileTmpl = TheThingFactory->findTemplate(m_projectileName);
		DEBUG_ASSERTCRASH(m_projectileTmpl, ("projectile %s not found!",m_projectileName.str()));
	}

	for (Int i = LEVEL_FIRST; i <= LEVEL_LAST; ++i)
	{
		// And the OCL if there is one
		if (m_fireOCLNames[i].isEmpty())
		{
			m_fireOCLs[i] = NULL;
		}
		else
		{
			m_fireOCLs[i] = TheObjectCreationListStore->findObjectCreationList(m_fireOCLNames[i].str() );
			DEBUG_ASSERTCRASH(m_fireOCLs[i], ("OCL %s not found in a weapon!",m_fireOCLNames[i].str()));
		}
		m_fireOCLNames[i].clear();

		// And the other OCL if there is one
		if (m_projectileDetonationOCLNames[i].isEmpty() )
		{
			m_projectileDetonationOCLs[i] = NULL;
		}
		else
		{
			m_projectileDetonationOCLs[i] = TheObjectCreationListStore->findObjectCreationList(m_projectileDetonationOCLNames[i].str() );
			DEBUG_ASSERTCRASH(m_projectileDetonationOCLs[i], ("OCL %s not found in a weapon!",m_projectileDetonationOCLNames[i].str()));
		}
		m_projectileDetonationOCLNames[i].clear();
	}

}  // end postProcessLoad

//-------------------------------------------------------------------------------------------------
// ?getAttackRange@WeaponTemplate@@ present-unmatched
Real WeaponTemplate::getAttackRange(const WeaponBonus& bonus) const 
{
#ifdef RATIONALIZE_ATTACK_RANGE
	// Note - undersize by 1/4 of a pathfind cell, so that the goal is not teetering on the edge
	// of firing range.  jba.
	const Real UNDERSIZE = PATHFIND_CELL_SIZE_F*0.25f;
	Real r = m_attackRange * bonus.getField(WeaponBonus::RANGE) - UNDERSIZE; 
	if (r < 0.0f) r = 0.0f;
	return r;
#else
// fudge this a little to account for pathfinding roundoff & such
	const Real ATTACK_RANGE_FUDGE = 1.05f;
	return m_attackRange * bonus.getField(WeaponBonus::RANGE) * ATTACK_RANGE_FUDGE; 
#endif
}

//-------------------------------------------------------------------------------------------------
// WeaponTemplate::getMinimumAttackRange: defined in WeaponTemplateMinimumRange.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// ?getUnmodifiedAttackRange@WeaponTemplate@@ present-unmatched
Real WeaponTemplate::getUnmodifiedAttackRange() const
{
	return m_attackRange;
}

//-------------------------------------------------------------------------------------------------
// ?getDelayBetweenShots@WeaponTemplate@@ present-unmatched
Int WeaponTemplate::getDelayBetweenShots(const WeaponBonus& bonus) const 
{
	// yes, divide, not multiply; the larger the rate-of-fire bonus, the shorter
	// we want the delay time to be.
	Int delayToUse;
	if( m_minDelayBetweenShots == m_maxDelayBetweenShots )
		delayToUse = m_minDelayBetweenShots; // Random number thing doesn't like this case
	else
		delayToUse = GameLogicRandomValue( m_minDelayBetweenShots, m_maxDelayBetweenShots );

	Real bonusROF = bonus.getField(WeaponBonus::RATE_OF_FIRE);
	//CRCDEBUG_LOG(("WeaponTemplate::getDelayBetweenShots() - min:%d max:%d val:%d, bonusROF=%g/%8.8X\n",
		//m_minDelayBetweenShots, m_maxDelayBetweenShots, delayToUse, bonusROF, AS_INT(bonusROF)));

	return REAL_TO_INT_FLOOR(delayToUse / bonusROF); 
}

//-------------------------------------------------------------------------------------------------
// WeaponTemplate::getClipReloadTime: defined in WeaponTemplateClipReloadTime.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// ?getPreAttackDelay@WeaponTemplate@@ present-unmatched
Int WeaponTemplate::getPreAttackDelay( const WeaponBonus& bonus ) const
{
	return m_preAttackDelay * bonus.getField( WeaponBonus::PRE_ATTACK ); 
}

//-------------------------------------------------------------------------------------------------
// ?getPrimaryDamage@WeaponTemplate@@ present-unmatched
Real WeaponTemplate::getPrimaryDamage(const WeaponBonus& bonus) const 
{
	return m_primaryDamage * bonus.getField(WeaponBonus::DAMAGE); 
}

//-------------------------------------------------------------------------------------------------
// ?getPrimaryDamageRadius@WeaponTemplate@@ present-unmatched
Real WeaponTemplate::getPrimaryDamageRadius(const WeaponBonus& bonus) const 
{
	return m_primaryDamageRadius * bonus.getField(WeaponBonus::RADIUS); 
}

//-------------------------------------------------------------------------------------------------
// ?getSecondaryDamage@WeaponTemplate@@ present-unmatched
Real WeaponTemplate::getSecondaryDamage(const WeaponBonus& bonus) const 
{
	return m_secondaryDamage * bonus.getField(WeaponBonus::DAMAGE); 
}

//-------------------------------------------------------------------------------------------------
// ?getSecondaryDamageRadius@WeaponTemplate@@ present-unmatched
Real WeaponTemplate::getSecondaryDamageRadius(const WeaponBonus& bonus) const 
{
	return m_secondaryDamageRadius * bonus.getField(WeaponBonus::RADIUS); 
}

//-------------------------------------------------------------------------------------------------
Bool WeaponTemplate::isContactWeapon() const
{
	// BFME 2 retail: the call from privateAttackPosition (0x0026DC3F) lands on the shared
	// xor al,al / ret false-predicate stub at 0x0047A699 (rowed here as an ICF twin), so the Zero Hour
	// attack-range test (PATHFIND_CELL_SIZE_F cutoff) is gone.
	return false;
}

//-------------------------------------------------------------------------------------------------
// ?estimateWeaponTemplateDamage@WeaponTemplate@@ present-unmatched
Real WeaponTemplate::estimateWeaponTemplateDamage(
	const Object *sourceObj, 
	const Object *victimObj, 
	const Coord3D* victimPos, 
	const WeaponBonus& bonus
) const
{
	if (sourceObj == NULL || (victimObj == NULL && victimPos == NULL))
	{
		DEBUG_CRASH(("bad args to estimate"));
		return 0.0f;
	}

	DamageType damageType = getDamageType();
	DeathType deathType = getDeathType();

	if (victimObj && victimObj->isKindOf(KINDOF_SHRUBBERY))
	{
		if (deathType == DEATH_BURNED)
		{
			// this is just a nonzero value, to ensure we can target shrubbery with flame weapons, regardless...
			return 1.0f;
		}
		else
		{
			return 0.0f;
		}
	}

  
  // hmm.. must be shooting a firebase or such, if there is noone home to take the bullet, return 0!
  if ( victimObj->isKindOf( KINDOF_STRUCTURE) && damageType == DAMAGE_SNIPER )
  {
    if ( victimObj->getContain() )
    {
      if ( victimObj->getContain()->getContainCount() == 0 )
        return 0.0f;
    }
  }




	if (damageType == DAMAGE_SURRENDER || m_allowAttackGarrisonedBldgs)
	{
		ContainModuleInterface* contain = victimObj->getContain();
		if( contain && contain->getContainCount() > 0 && contain->isGarrisonable() && !contain->isImmuneToClearBuildingAttacks() )
		{
			// this is just a nonzero value, to ensure we can target garrisoned things with surrender weapons, regardless...
			return 1.0f;
		}
	}

	if( victimObj )
	{
		if( damageType == DAMAGE_DISARM )
		{
			if( victimObj->isKindOf( KINDOF_MINE ) || victimObj->isKindOf( KINDOF_BOOBY_TRAP ) || victimObj->isKindOf( KINDOF_DEMOTRAP ) )
			{
				// this is just a nonzero value, to ensure we can target mines with disarm weapons, regardless...
				return 1.0f;
			}
			return 0.0f;
		}
		if( damageType == DAMAGE_DEPLOY && !victimObj->isAirborneTarget() )
		{
			return 1.0f;
		}
	}

	//@todo Kris need to examine the DAMAGE_HACK type for damage estimation purposes.
	//Likely this damage type will have threat implications that won't properly be dealt with until resolved.

//	const Coord3D* sourcePos = sourceObj->getPosition();
	if (victimPos == NULL)
	{
		victimPos = victimObj->getPosition();
	}

	Real damageAmount = getPrimaryDamage(bonus);
	if (victimObj == NULL)
	{
		return damageAmount;
	}
	else
	{
		DamageInfoInput damageInfo;
		damageInfo.m_damageType = damageType;
		damageInfo.m_deathType = deathType;
		damageInfo.m_sourceID = sourceObj->getID();
		damageInfo.m_amount = damageAmount;
		return victimObj->estimateDamage(damageInfo);
	}
}

// The collide-with body lives under WeaponTemplateShouldProjectileCollideWith.cpp
// (retail row); this TU keeps only the class declaration so callers bind the
// kept copy and this unit emits no competing COMDAT.


//-------------------------------------------------------------------------------------------------
UnsignedInt WeaponTemplate::fireWeaponTemplate
(
	const Object *sourceObj, 
	WeaponSlotType wslot, 
	Int specificBarrelToUse, 
	Object *victimObj, 
	const Coord3D* victimPos, 
	const WeaponBonus& bonus,
	Bool isProjectileDetonation,
	Bool ignoreRanges,
	Weapon *firingWeapon,
	ObjectID* projectileID,
	Bool inflictDamage
) const
{

	//-extraLogging 
	#if (defined(_DEBUG) || defined(_INTERNAL))
		AsciiString targetStr;
		if( TheGlobalData->m_extraLogging )
		{
			if( victimObj )
				targetStr.format( "%s", victimObj->getTemplate()->getName().str() );
			else if( victimPos )
				targetStr.format( "%d,%d,%d", victimPos->x, victimPos->y, victimPos->z );
			else
				targetStr.format( "SELF." );

			DEBUG_LOG( ("%d - WeaponTemplate::fireWeaponTemplate() begin - %s attacking %s - ", 
				TheGameLogic->getFrame(), sourceObj->getTemplate()->getName().str(), targetStr.str() ) );
		}
	#endif
	//end -extraLogging 

	//CRCDEBUG_LOG(("WeaponTemplate::fireWeaponTemplate() from %s\n", DescribeObject(sourceObj).str()));
	DEBUG_ASSERTCRASH(specificBarrelToUse >= 0, ("specificBarrelToUse should no longer be -1\n"));

	if (sourceObj == NULL || (victimObj == NULL && victimPos == NULL))
	{
		//-extraLogging 
		#if (defined(_DEBUG) || defined(_INTERNAL))
			if( TheGlobalData->m_extraLogging )
				DEBUG_LOG( ("FAIL 1 (sourceObj %d == NULL || (victimObj %d == NULL && victimPos %d == NULL)\n", sourceObj != 0, victimObj != 0, victimPos != 0) );
		#endif
		//end -extraLogging 

		return 0;
	}

	DEBUG_ASSERTCRASH((m_primaryDamage > 0)  ||  (victimObj == NULL), ("You can't really shoot a zero damage weapon at an Object.") );

	ObjectID sourceID = sourceObj->getID();
	const Coord3D* sourcePos = sourceObj->getPosition();

	Real distSqr;
	ObjectID victimID;
	TBridgeAttackInfo info;
	Coord3D victimPosStorage;
	if (victimObj)
	{
		DEBUG_ASSERTLOG(sourceObj != victimObj, ("*** firing weapon at self -- is this really what you want?\n"));
		victimPos = victimObj->getPosition();
		victimID = victimObj->getID();

		Coord3D sneakyOffset;
		const AIUpdateInterface* ai = victimObj->getAI();
		if (ai != NULL && ai->getSneakyTargetingOffset(&sneakyOffset))
		{
			victimPosStorage = *victimPos;
			victimPosStorage.x += sneakyOffset.x;
			victimPosStorage.y += sneakyOffset.y;
			victimPosStorage.z += sneakyOffset.z;

			victimPos = &victimPosStorage;
			// for a sneaky offset, we always target a position rather than an object
			victimObj = NULL;
			victimID = INVALID_ID;
			distSqr = ThePartitionManager->getDistanceSquared(sourceObj, victimPos, ATTACK_RANGE_CALC_TYPE);
		}
		else
		{
			if (victimObj->isKindOf(KINDOF_BRIDGE)) 
			{
				// Bridges are kind of oddball - they have 2 target points at either end.
				TheTerrainLogic->getBridgeAttackPoints(victimObj, &info);
				distSqr = ThePartitionManager->getDistanceSquared( sourceObj, &info.attackPoint1, ATTACK_RANGE_CALC_TYPE );
				victimPos = &info.attackPoint1;
 				Real distSqr2 = ThePartitionManager->getDistanceSquared( sourceObj, &info.attackPoint2, ATTACK_RANGE_CALC_TYPE );
				if (distSqr > distSqr2) 
				{
					// Try the other one.
					distSqr = distSqr2;
					victimPos = &info.attackPoint2;
				}
			}	
			else 
			{
				distSqr = ThePartitionManager->getDistanceSquared(sourceObj, victimObj, ATTACK_RANGE_CALC_TYPE);
			}
		}
	}
	else
	{
		victimID = INVALID_ID;
		distSqr = ThePartitionManager->getDistanceSquared(sourceObj, victimPos, ATTACK_RANGE_CALC_TYPE);
	}

//	DEBUG_LOG(("WeaponTemplate::fireWeaponTemplate: firing weapon %s (source=%s, victim=%s)\n",
//		m_name.str(),sourceObj->getTemplate()->getName().str(),victimObj?victimObj->getTemplate()->getName().str():"NULL"));

	//Only perform this check if the weapon isn't a leech range weapon (which can have unlimited range!)
	if( !ignoreRanges && !isLeechRangeWeapon() )
	{
		Real attackRangeSqr = sqr(getAttackRange(bonus));
		if (distSqr > attackRangeSqr)
		{
			//DEBUG_ASSERTCRASH(distSqr < 5*5 || distSqr < attackRangeSqr*1.2f, ("*** victim is out of range (%f vs %f) of this weapon -- why did we attempt to fire?\n",sqrtf(distSqr),sqrtf(attackRangeSqr)));
			
			//-extraLogging 
			#if (defined(_DEBUG) || defined(_INTERNAL))
				if( TheGlobalData->m_extraLogging )
					DEBUG_LOG( ("FAIL 2 (distSqr %.2f > attackRangeSqr %.2f)\n", distSqr, attackRangeSqr ) );
			#endif
			//end -extraLogging 

			return 0;
		}
	}

	if (!ignoreRanges)
	{
		Real minAttackRangeSqr = sqr(getMinimumAttackRange());
#ifdef RATIONALIZE_ATTACK_RANGE
		if (distSqr < minAttackRangeSqr && !isProjectileDetonation)
#else
		if (distSqr < minAttackRangeSqr-0.5f && !isProjectileDetonation)
#endif
		{
			DEBUG_ASSERTCRASH(distSqr > minAttackRangeSqr*0.8f, ("*** victim is closer than min attack range (%f vs %f) of this weapon -- why did we attempt to fire?\n",sqrtf(distSqr),sqrtf(minAttackRangeSqr)));

			//-extraLogging 
			#if (defined(_DEBUG) || defined(_INTERNAL))
				if( TheGlobalData->m_extraLogging )
					DEBUG_LOG( ("FAIL 3 (distSqr %.2f< minAttackRangeSqr %.2f - 0.5f && !isProjectileDetonation %d)\n", distSqr, minAttackRangeSqr, isProjectileDetonation ) );
			#endif
			//end -extraLogging 

			return 0;
		}
	}

	// call this even if FXList is null, because this also handles stuff like Gun Barrel Recoil
	if (sourceObj && sourceObj->getDrawable())
	{
		Coord3D targetPos;
		if( victimObj )
		{
			victimObj->getGeometryInfo().getCenterPosition( *victimObj->getPosition(), targetPos );
		}
		else
		{
			targetPos.set( victimPos );
		}
		Real reAngle = getWeaponRecoilAmount();
		Real reDir = reAngle != 0.0f ? (atan2(victimPos->y - sourcePos->y, victimPos->x - sourcePos->x)) : 0.0f;
		VeterancyLevel v = sourceObj->getVeterancyLevel();
		const FXList* fx = isProjectileDetonation ? getProjectileDetonateFX(v) : getFireFX(v);
		
		if ( TheGameLogic->getFrame() < firingWeapon->getSuspendFXFrame() )
			fx = NULL;

		Bool handled;
		
		if(!sourceObj->isLocallyControlled()									// if user watching is not controller and
			&&  sourceObj->testStatus(OBJECT_STATUS_STEALTHED)	// if unit is stealthed (like a Pathfinder)
			&& !sourceObj->testStatus(OBJECT_STATUS_DETECTED)		// but not detected...
			&& !sourceObj->testStatus(OBJECT_STATUS_DISGUISED)  // and not disguised...
			&& !sourceObj->isKindOf(KINDOF_MINE)								// and not a mine (which always do the FX, even if hidden)...
			&& !isPlayFXWhenStealthed()													// and not a weapon marked to playwhenstealthed
			)
		{
			handled = TRUE;		// then let's just pretend like we did the fx by returning true
		}
		else
		{
			handled = sourceObj->getDrawable()->handleWeaponFireFX(wslot, 
																															specificBarrelToUse, 
																															fx, 
																															getWeaponSpeed(), 
																															reAngle, 
																															reDir, 
																															&targetPos,
																															getPrimaryDamageRadius(bonus)
																															);
		}

		if (handled == false && fx != NULL)
		{
			// bah. just play it at the drawable's pos.
			//DEBUG_LOG(("*** WeaponFireFX not fully handled by the client\n"));
			const Coord3D* where = isContactWeapon() ? &targetPos : sourceObj->getDrawable()->getPosition();
			FXList::doFXPos(fx, where, sourceObj->getDrawable()->getTransformMatrix(), getWeaponSpeed(), &targetPos, getPrimaryDamageRadius(bonus));
		}
	}

	// Now do the FireOCL if there is one
	if( sourceObj )
	{
		VeterancyLevel v = sourceObj->getVeterancyLevel();
		const ObjectCreationList *oclToUse = isProjectileDetonation ? getProjectileDetonationOCL(v) : getFireOCL(v);
		if( oclToUse )
			ObjectCreationList::create( oclToUse, sourceObj, NULL );
	}

	Coord3D projectileDestination = *victimPos; //Need to copy this, as we have a pointer to their actual position
	Real scatterRadius = 0.0f;
	if( m_scatterRadius > 0.0f || m_infantryInaccuracyDist > 0.0f && victimObj && victimObj->isKindOf( KINDOF_INFANTRY ) )
	{
		// This weapon scatters, so clear the victimObj, as we are no longer shooting it directly,
		// and find a random point within the radius to shoot at as victimPos
		scatterRadius = m_scatterRadius;

		// if it's an object, aim at the center, not the ground part (srj)
		PathfindLayerEnum targetLayer = LAYER_GROUND;
		if( victimObj )
		{
			if( victimObj->isKindOf( KINDOF_STRUCTURE ) )
			{
				victimObj->getGeometryInfo().getCenterPosition(*victimObj->getPosition(), projectileDestination);
			}
			if( m_infantryInaccuracyDist > 0.0f && victimObj->isKindOf( KINDOF_INFANTRY ) )
			{
				//If we are firing a weapon that is considered inaccurate against infantry, then add it to
				//the scatter radius!
				scatterRadius += m_infantryInaccuracyDist;
			}
			targetLayer = victimObj->getLayer();
		}

		//victimObj = NULL; // his position is already in victimPos, if he existed

		//Randomize the scatter radius (sometimes it can be more accurate than others)
		scatterRadius = GameLogicRandomValueReal( 0, scatterRadius );
		Real scatterAngleRadian = GameLogicRandomValueReal( 0, 2*PI );

		Coord3D firingOffset;
		firingOffset.zero();
		firingOffset.x = scatterRadius * Cos( scatterAngleRadian );
		firingOffset.y = scatterRadius * Sin( scatterAngleRadian );

		projectileDestination.x += firingOffset.x;
		projectileDestination.y += firingOffset.y;

		//What's suddenly become crucially important is to FIRE at the ground at this location!!!
		//If we aim for the center point of our target and miss, the shot will go much farther than
		//we expect!
		// srj sez: we should actually fire at the layer the victim is on, if possible, in case it is on a bridge...
		projectileDestination.z = TheTerrainLogic->getLayerHeight( projectileDestination.x, projectileDestination.y, targetLayer );
	}

	if (getProjectileTemplate() == NULL || isProjectileDetonation)
	{
		// see if we need to be called back at a later point to deal the damage.
		Coord3D v;
		v.x = victimPos->x - sourcePos->x;
		v.y = victimPos->y - sourcePos->y;
		v.z = victimPos->z - sourcePos->z;
		// don't round the result; we WANT a fractional-frame-delay in this case.
		Real delayInFrames = (v.length() / getWeaponSpeed());

		ObjectID damageID = getDamageDealtAtSelfPosition() ? INVALID_ID : victimID;

		if( firingWeapon->isLaser() )
		{
			if( scatterRadius <= getPrimaryDamageRadius( bonus ) || scatterRadius <= getSecondaryDamageRadius( bonus ) )
			{
				//The laser is close enough to damage the object, so just hit it directly. Some victim objects
				//adjust the laser's position to prevent it from hitting the ground.
				if( victimObj )
				{
					projectileDestination.set( victimObj->getPosition() );
				}
				firingWeapon->createLaser( sourceObj, victimObj, &projectileDestination );
			}
			else
			{
				//We are missing our intended target, so now we want to aim at the ground at the projectile offset.
				damageID = INVALID_ID;
				firingWeapon->createLaser( sourceObj, NULL, &projectileDestination );
			}
			if( inflictDamage )
			{
				dealDamageInternal( sourceID, damageID, &projectileDestination, bonus, isProjectileDetonation );
			}
			return TheGameLogic->getFrame();
		}

		const Coord3D* damagePos = getDamageDealtAtSelfPosition() ? sourcePos : victimPos;
		if (delayInFrames < 1.0f)
		{
			// go ahead and do it now
			//DEBUG_LOG(("WeaponTemplate::fireWeaponTemplate: firing weapon immediately!\n"));
			if( inflictDamage )
			{
				dealDamageInternal(sourceID, damageID, damagePos, bonus, isProjectileDetonation);
			}

			//-extraLogging 
			#if (defined(_DEBUG) || defined(_INTERNAL))
				if( TheGlobalData->m_extraLogging )
					DEBUG_LOG( ("EARLY 4 (delayed damage applied now)\n") );
			#endif
			//end -extraLogging 


			return TheGameLogic->getFrame();
		}
		else
		{
			UnsignedInt when = 0;
			if( TheWeaponStore && inflictDamage )
			{
				UnsignedInt delayInWholeFrames = REAL_TO_INT_CEIL(delayInFrames);
				when = TheGameLogic->getFrame() + delayInWholeFrames;
				//DEBUG_LOG(("WeaponTemplate::fireWeaponTemplate: firing weapon in %d frames (= %d)!\n", delayInWholeFrames,when));
				TheWeaponStore->setDelayedDamage(this, damagePos, when, sourceID, damageID, bonus);
			}

			//-extraLogging 
			#if (defined(_DEBUG) || defined(_INTERNAL))
				if( TheGlobalData->m_extraLogging )
					DEBUG_LOG( ("EARLY 5 (delaying damage applied until frame %d)\n", when ) );
			#endif
			//end -extraLogging 


			return when;
		}
	}
	else	// must be a projectile
	{
		Player *owningPlayer = sourceObj->getControllingPlayer(); //Need to know so missiles don't collide with firer
		Object *projectile = TheThingFactory->newObject( getProjectileTemplate(), owningPlayer->getDefaultTeam() );
		projectile->setProducer(sourceObj);
		
		//If the player has battle plans (America Strategy Center), then apply those bonuses
		//to this object if applicable. Internally it validates certain kinds of objects.
		//When projectiles are created, weapon bonuses such as damage may get applied.
		if( owningPlayer->getNumBattlePlansActive() > 0 )
		{
			owningPlayer->applyBattlePlanBonusesForObject( projectile );
		}


		//Store the project ID in the object as the last projectile fired!
		if (projectileID)
			*projectileID = projectile->getID();

		// Notify special power tracking
		SpecialPowerCompletionDie *die = sourceObj->findSpecialPowerCompletionDie();
		if (die)
		{
			die->notifyScriptEngine();
			die = projectile->findSpecialPowerCompletionDie();
			if (die)
			{
				die->setCreator(INVALID_ID);
			}
		}
		else
		{
			die = projectile->findSpecialPowerCompletionDie();
			if (die)
			{
				die->setCreator(sourceObj->getID());
			}
		}

		firingWeapon->newProjectileFired( sourceObj, projectile, victimObj, victimPos );//The actual logic weapon needs to know this was created. 

		ProjectileUpdateInterface* pui = NULL;
		for (BehaviorModule** u = projectile->getBehaviorModules(); *u; ++u)
		{
			if ((pui = (*u)->getProjectileUpdateInterface()) != NULL)
				break;
		}
		if (pui)
		{
			VeterancyLevel v = sourceObj->getVeterancyLevel();
			if( scatterRadius > 0.0f )
			{
				//With a scatter radius, don't follow the victim (overriding the intent).
				pui->projectileLaunchAtObjectOrPosition( NULL, &projectileDestination, sourceObj, wslot, specificBarrelToUse, this, m_projectileExhausts[v] );
			}
			else
			{
				pui->projectileLaunchAtObjectOrPosition(victimObj, &projectileDestination, sourceObj, wslot, specificBarrelToUse, this, m_projectileExhausts[v]);
			}
		}
		else
		{
			//DEBUG_CRASH(("Projectiles should implement ProjectileUpdateInterface!\n"));
			// actually, this is ok, for things like Firestorm.... (srj)
			projectile->setPosition(&projectileDestination);
		}

		//If we're launching a missile at a unit with valid countermeasures, then communicate it
		if( projectile->isKindOf( KINDOF_SMALL_MISSILE ) && victimObj && victimObj->hasCountermeasures() )
		{
			const AIUpdateInterface *ai = victimObj->getAI();
			//Only allow jets not currently supersonic to launch countermeasures
			if( ai && ai->getCurLocomotorSetType() != LOCOMOTORSET_SUPERSONIC )
			{
				//This function will determine now whether or not the fired projectile will be diverted to
				//an available decoy flare.
				victimObj->reportMissileForCountermeasures( projectile );
			}
			
		}
		//-extraLogging 
		#if (defined(_DEBUG) || defined(_INTERNAL))
			if( TheGlobalData->m_extraLogging )
				DEBUG_LOG( ("DONE\n") );
		#endif
		//end -extraLogging 

		return 0;
	}
}

//-------------------------------------------------------------------------------------------------
// ?trimOldHistoricDamage@WeaponTemplate@@ present-unmatched
void WeaponTemplate::trimOldHistoricDamage() const
{
	UnsignedInt expirationDate = TheGameLogic->getFrame() - TheGlobalData->m_historicDamageLimit;
	while (m_historicDamage.size() > 0)
	{
		HistoricWeaponDamageInfo& historicWeaponDamageInfo = m_historicDamage.front();
		if (historicWeaponDamageInfo.frame <= expirationDate)
		{
			m_historicDamage.pop_front();
			continue;
		}
		else
		{
			// since they are in strict chronological order,
			// stop as soon as we get to a nonexpired one
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------
static Bool is2DDistSquaredLessThan(const Coord3D& a, const Coord3D& b, Real distSqr)
{
	Real da = sqr(a.x - b.x) + sqr(a.y - b.y);
	return da <= distSqr;
}

//-------------------------------------------------------------------------------------------------
// ?dealDamageInternal@WeaponTemplate@@ present-unmatched
void WeaponTemplate::dealDamageInternal(ObjectID sourceID, ObjectID victimID, const Coord3D *pos, const WeaponBonus& bonus, Bool isProjectileDetonation) const
{
	if (sourceID == 0)	// must have a source
		return;

	if (victimID == 0 && pos == NULL)	// must have some sort of destination
		return;

	Object *source = TheGameLogic->findObjectByID(sourceID);	// might be null...

	//
	/** @todo We need to rewrite the historic stuff ... if you fire 5 missiles, and the 5th,
	// one creates a firestorm ... and then half a second later another volley of 5 missiles
	// come in, the second wave of 5 missiles would all do a historic weapon, making 5 more
	// firestorms (CBD) */
	//

	trimOldHistoricDamage();

	if( m_historicBonusCount > 0 && m_historicBonusWeapon != this )
	{
		Real radSqr = m_historicBonusRadius * m_historicBonusRadius;
		Int count = 0;
		UnsignedInt frameNow = TheGameLogic->getFrame();
		UnsignedInt oldestThatWillCount = frameNow - m_historicBonusTime; // Anything before this frame is "more than two seconds ago" eg
		for( HistoricWeaponDamageList::const_iterator it = m_historicDamage.begin(); it != m_historicDamage.end(); ++it )
		{
			if( it->frame >= oldestThatWillCount && 
					is2DDistSquaredLessThan( *pos, it->location, radSqr ) )
			{
				// This one is close enough in time and distance, so count it. This is tracked by template since it applies
				// across units, so don't try to clear historicDamage on success in here.
				++count;
			}
		}
		
		if( count >= m_historicBonusCount - 1 )	// minus 1 since we include ourselves implicitly
		{
		  TheWeaponStore->createAndFireTempWeapon(m_historicBonusWeapon, source, pos);

			/** @todo E3 hack! Clear the list for now to make sure we don't have multiple firestorms
				* remove this when the branches merge back into one.  What is causing the
				* multiple firestorms, who is to say ... this is a plug, not a fix! */
			m_historicDamage.clear();

		}
		else
		{
			
			// add AFTER checking for historic stuff
			m_historicDamage.push_back( HistoricWeaponDamageInfo(frameNow, *pos) );

		}  // end else

	} // if historic bonuses

//DEBUG_LOG(("WeaponTemplate::dealDamageInternal: dealing damage %s at frame %d\n",m_name.str(),TheGameLogic->getFrame()));

	// if there's a specific victim, use it's pos (overriding the value passed in)
	Object *primaryVictim = victimID ? TheGameLogic->findObjectByID(victimID) : NULL;	// might be null...
	if (primaryVictim)
	{
		pos = primaryVictim->getPosition();
	}

	DamageType damageType = getDamageType();
	DeathType deathType = getDeathType();
	ObjectStatusTypes damageStatusType = getDamageStatusType();
	if (getProjectileTemplate() == NULL || isProjectileDetonation)
	{
		SimpleObjectIterator *iter;
		Object *curVictim;
		Real curVictimDistSqr;

		Real primaryRadius = getPrimaryDamageRadius(bonus);
		Real secondaryRadius = getSecondaryDamageRadius(bonus);
		Real primaryDamage = getPrimaryDamage(bonus);
		Real secondaryDamage = getSecondaryDamage(bonus);
		Int affects = getAffectsMask();

		DEBUG_ASSERTCRASH(secondaryRadius >= primaryRadius || secondaryRadius == 0.0f, ("secondary radius should be >= primary radius (or zero)\n"));

		Real primaryRadiusSqr = sqr(primaryRadius);
		Real radius = max(primaryRadius, secondaryRadius);
		if (radius > 0.0f)
		{
			iter = ThePartitionManager->iterateObjectsInRange(pos, radius, DAMAGE_RANGE_CALC_TYPE);
			curVictim = iter->firstWithNumeric(&curVictimDistSqr);
		} 
		else
		{
			//DEBUG_ASSERTCRASH(primaryVictim != NULL, ("weapons without radii should always pass in specific victims"));
			// check against victimID rather than primaryVictim, since we may have targeted a legitimate victim
			// that got killed before the damage was dealt... (srj)
			//DEBUG_ASSERTCRASH(victimID != 0, ("weapons without radii should always pass in specific victims"));
			iter = NULL;
			curVictim = primaryVictim;
			curVictimDistSqr = 0.0f;

			if( affects & WEAPON_KILLS_SELF )
			{
				DamageInfo damageInfo;
				damageInfo.in.m_damageType = damageType;
				damageInfo.in.m_deathType = deathType;
				damageInfo.in.m_sourceID = sourceID;
				damageInfo.in.m_sourcePlayerMask = 0;
				damageInfo.in.m_damageStatusType = damageStatusType;
				damageInfo.in.m_amount = HUGE_DAMAGE_AMOUNT;
				source->attemptDamage( &damageInfo );
				return;
			}
		}
		MemoryPoolObjectHolder hold(iter);

		for (; curVictim != NULL; curVictim = iter ? iter->nextWithNumeric(&curVictimDistSqr) : NULL)
		{
			Bool killSelf = false;
			if (source != NULL)
			{
				// anytime something is designated as the "primary victim" (ie, the direct target
				// of the weapon), we ignore all the "affects" flags.
				if (curVictim != primaryVictim)
				{

					if( (affects & WEAPON_KILLS_SELF) && source == curVictim )
					{
						killSelf = true;
					}
					else
					{
					
						// should object ever be allowed to damage themselves? methinks not...
						// exception: a few weapons allow this (eg, for suicide bombers).
						if( (affects & WEAPON_AFFECTS_SELF) == 0 )
						{
							// Remember that source is a missile for some units, and they don't want to injure them'selves' either
							if( source == curVictim || source->getProducerID() == curVictim->getID() )
							{
								//DEBUG_LOG(("skipping damage done to SELF...\n"));
								continue;
							}
						}

						if( affects & WEAPON_DOESNT_AFFECT_SIMILAR )
						{
							//This means we probably are affecting allies, but don't want to kill nearby members that are the same type as us.
							//A good example are a group of terrorists blowing themselves up. We don't want to cause a domino effect that kills
							//all of them.
							if( source->getTemplate()->isEquivalentTo(curVictim->getTemplate()) && source->getRelationship( curVictim ) == ALLIES )
							{
								continue;
							}
						}

						if ((affects & WEAPON_DOESNT_AFFECT_AIRBORNE) != 0 && curVictim->isSignificantlyAboveTerrain())
						{
							continue;
						}

						/*
							The idea here is: if its our ally(/enemies), AND it's not the direct target, AND the weapon doesn't
							do radius-damage to allies(/enemies)... skip it. 
						*/
						Relationship r = curVictim->getRelationship(source);
						Int requiredMask;
						if (r == ALLIES) 
							requiredMask = WEAPON_AFFECTS_ALLIES;
						else if (r == ENEMIES) 
							requiredMask = WEAPON_AFFECTS_ENEMIES;
						else /* r == NEUTRAL */
							requiredMask = WEAPON_AFFECTS_NEUTRALS;

						if( !(affects & requiredMask) )
						{
							//Skip if we aren't affected by this weapon.
							continue;
						}
					}
				}
			}

			DamageInfo damageInfo;
			damageInfo.in.m_damageType = damageType;
			damageInfo.in.m_deathType = deathType;
			damageInfo.in.m_sourceID = sourceID;
			damageInfo.in.m_sourcePlayerMask = 0;
			damageInfo.in.m_damageStatusType = damageStatusType;
			
			Coord3D damageDirection;
			damageDirection.zero();
			if( curVictim && source )
			{
				damageDirection.set( curVictim->getPosition() );
				damageDirection.sub( source->getPosition() );
			}

			Real allowedAngle = getRadiusDamageAngle();
			if( allowedAngle < PI )
			{
				if( curVictim == NULL  ||  source == NULL )
					continue; // We are directional damage, but can't figure out our direction.  Just bail.
				
				// People can only be hit in a cone oriented as the firer is oriented
				Vector3 sourceVector = source->getTransformMatrix()->Get_X_Vector();
				Vector3 damageVector(damageDirection.x, damageDirection.y, damageDirection.z);
				sourceVector.Normalize();
				damageVector.Normalize();

				// These are now normalized, so the dot productis actually the Cos of the angle they form
				// A smaller Cos would mean a more obtuse angle
				if( Vector3::Dot_Product(sourceVector, damageVector) < Cos(allowedAngle) )
					continue;// Too far to the side, can't hurt them.
			}

			// Grab the vector between the source object causing the damage and the victim in order that we can
			// simulate a shockwave pushing objects around
			damageInfo.in.m_shockWaveAmount = m_shockWaveAmount;
			if (damageInfo.in.m_shockWaveAmount > 0.0f)
			{
				// Calculate the vector of the shockwave
				Coord3D shockWaveVector = damageDirection;

				// Guard against zero vector. Make vector stright up if that is the case
				if (fabs(shockWaveVector.x) < WWMATH_EPSILON && 
						fabs(shockWaveVector.y) < WWMATH_EPSILON && 
						fabs(shockWaveVector.z) < WWMATH_EPSILON)
				{
					shockWaveVector.z = 1.0f;
				}

				// Populate the damge information with the shockwave information
				damageInfo.in.m_shockWaveVector = shockWaveVector;
				damageInfo.in.m_shockWaveRadius = m_shockWaveRadius;
				damageInfo.in.m_shockWaveTaperOff = m_shockWaveTaperOff;
			}

      if (source && source->getControllingPlayer()) {
				damageInfo.in.m_sourcePlayerMask = source->getControllingPlayer()->getPlayerMask();
			}
			// note, don't bother with damage multipliers here... 
			// that's handled internally by the attemptDamage() method.
			damageInfo.in.m_amount = (curVictimDistSqr <= primaryRadiusSqr) ? primaryDamage : secondaryDamage;

			if( killSelf )
			{
				//Deal enough damage to kill yourself. I thought about getting the current health and applying
				//enough unresistable damage to die... however it's possible that we have different types of
				//deaths based on damage type and/or the possibility to resist certain damage types and
				//surviving -- so instead, I'm blindly inflicting a very high value of the intended damage type.
				damageInfo.in.m_amount = HUGE_DAMAGE_AMOUNT;
				//BodyModuleInterface* body = curVictim->getBodyModule();
				//if( body )
				//{
				//	Real curVictimHealth = curVictim->getBodyModule()->getHealth();
				//	damageInfo.in.m_amount = __max( damageInfo.in.m_amount, curVictimHealth );
				//}
			}

			// if the damage-dealer is a projectile, designate the damage as done by its launcher, not the projectile.
			// this is much more useful for the AI...
			if (source && source->isKindOf(KINDOF_PROJECTILE))
			{
				for (BehaviorModule** behaviorModule = source->getBehaviorModules(); *behaviorModule; ++behaviorModule)
				{
					ProjectileUpdateInterface* pui = (*behaviorModule)->getProjectileUpdateInterface();
					if (pui != NULL)
					{
						damageInfo.in.m_sourceID = pui->projectileGetLauncherID();
						break;
					}
				}
			}

			curVictim->attemptDamage(&damageInfo);
			//DEBUG_ASSERTLOG(damageInfo.out.m_noEffect, ("WeaponTemplate::dealDamageInternal: dealt to %s %08lx: attempted %f, actual %f (%f)\n",
			//	curVictim->getTemplate()->getName().str(),curVictim,
			//	damageInfo.in.m_amount, damageInfo.out.m_actualDamageDealt, damageInfo.out.m_actualDamageClipped));
		}
	}
	else
	{
		DEBUG_CRASH(("projectile weapons should never get dealDamage called directly\n"));
	}
}

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
void WeaponStore::createAndFireTempWeapon(const WeaponTemplate* wt, const Object *source, Object *target)
{
	//CRCDEBUG_LOG(("WeaponStore::createAndFireTempWeapon() for %s\n", DescribeObject(source)));
	if (wt == NULL)
		return;
	Weapon* weapon = TheWeaponStore->allocateNewWeapon(wt, PRIMARY_WEAPON);
	weapon->loadAmmoNow(source);
	weapon->fireWeapon(source, target);
	weapon->deleteInstance();
}

//-------------------------------------------------------------------------------------------------
const WeaponTemplate *WeaponStore::findWeaponTemplate( AsciiString name ) const 
{ 
	if (stricmp(name.str(), "None") == 0)
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
// ?update@WeaponStore@@ present-unmatched
void WeaponStore::update()
{
	for (std::list<WeaponDelayedDamageInfo>::iterator ddi = m_weaponDDI.begin(); ddi != m_weaponDDI.end(); )
	{
		UnsignedInt curFrame = TheGameLogic->getFrame();
		if (curFrame >= ddi->m_delayDamageFrame)
		{
			// we never do projectile-detonation-damage via this code path.
			const isProjectileDetonation = false;
			ddi->m_delayedWeapon->dealDamageInternal(ddi->m_delaySourceID, ddi->m_delayIntendedVictimID, &ddi->m_delayDamagePos, ddi->m_bonus, isProjectileDetonation);
			ddi = m_weaponDDI.erase(ddi);
		}
		else
		{
			++ddi;
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?deleteAllDelayedDamage@WeaponStore@@ present-unmatched
void WeaponStore::deleteAllDelayedDamage()
{
	m_weaponDDI.clear();
}

// ------------------------------------------------------------------------------------------------
// WeaponStore::resetWeaponTemplates is rowed in its home unit; this copy was a duplicate definition.

//-------------------------------------------------------------------------------------------------
// WeaponStore::reset is rowed in its home unit; this copy was a duplicate definition.

//-------------------------------------------------------------------------------------------------
// ?setDelayedDamage@WeaponStore@@ present-unmatched
void WeaponStore::setDelayedDamage(const WeaponTemplate *weapon, const Coord3D* pos, UnsignedInt whichFrame, ObjectID sourceID, ObjectID victimID, const WeaponBonus& bonus)
{
	WeaponDelayedDamageInfo wi;
	wi.m_delayedWeapon = weapon;
	wi.m_delayDamagePos = *pos;
	wi.m_delayDamageFrame = whichFrame;
	wi.m_delaySourceID = sourceID;
	wi.m_delayIntendedVictimID = victimID;
	wi.m_bonus = bonus;
	m_weaponDDI.push_back(wi);
}

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
Weapon::Weapon(const Weapon& that)
{
	// Weapons lose all ammo when copied.
	this->m_template = that.m_template;
	this->m_wslot = that.m_wslot;
	this->m_status = OUT_OF_AMMO;
	this->m_ammoInClip = 0;
	this->m_whenPreAttackFinished = 0;
	this->m_whenLastReloadStarted = 0;
	this->m_whenWeCanFireAgain = 0;
	this->m_projectileStreamID = INVALID_ID;
	this->m_leechWeaponRangeActive = false;
	this->m_pitchLimited = (m_template->getMinTargetPitch() > -PI || m_template->getMaxTargetPitch() < PI);
	this->m_maxShotCount = NO_MAX_SHOTS_LIMIT;
	this->m_curBarrel = 0;
	this->m_numShotsForCurBarrel = m_template->getShotsPerBarrel();
	this->m_lastFireFrame = 0;
	this->m_suspendFXFrame = that.getSuspendFXFrame();
}

//-------------------------------------------------------------------------------------------------
// ??4Weapon@@QAEAAV0@ABV0@@Z present-unmatched
Weapon& Weapon::operator=(const Weapon& that)
{
	if (this != &that)
	{
		// Weapons lose all ammo when copied.
		this->m_template = that.m_template;
		this->m_wslot = that.m_wslot;
		this->m_status = OUT_OF_AMMO;
		this->m_ammoInClip = 0;
		this->m_whenPreAttackFinished = 0;
		this->m_whenLastReloadStarted = 0;
		this->m_whenWeCanFireAgain = 0;
		this->m_leechWeaponRangeActive = false;
		this->m_pitchLimited = (m_template->getMinTargetPitch() > -PI || m_template->getMaxTargetPitch() < PI);
		this->m_maxShotCount = NO_MAX_SHOTS_LIMIT;
		this->m_curBarrel = 0;
		this->m_lastFireFrame = 0;
		this->m_suspendFXFrame = that.getSuspendFXFrame();
		this->m_numShotsForCurBarrel = m_template->getShotsPerBarrel();
		this->m_projectileStreamID = INVALID_ID;
	}
	return *this;
}

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
// ?onWeaponBonusChange@Weapon@@ present-unmatched
void Weapon::onWeaponBonusChange(const Object *source)
{
	// We are concerned with our reload times being off if our ROF just changed.

	WeaponBonus bonus;
	computeBonus(source, 0, bonus); // The middle arg is for projectiles to inherit damage bonus from launcher

	Int newDelay;
	Bool needUpdate = FALSE;

	if( getStatus() == RELOADING_CLIP )
	{
		newDelay = m_template->getClipReloadTime(bonus);
		needUpdate = TRUE;
	}
	else if( getStatus() == BETWEEN_FIRING_SHOTS )
	{
		newDelay = m_template->getDelayBetweenShots(bonus);
		needUpdate = TRUE;
	}

	if( needUpdate )
	{
		m_whenLastReloadStarted = TheGameLogic->getFrame();
		m_whenWeCanFireAgain = m_whenLastReloadStarted + newDelay;	
		
		if (source->isReloadTimeShared())
		{	
			for (Int wt = 0; wt<WEAPONSLOT_COUNT; wt++)
			{
				Weapon *weapon = source->getWeaponInWeaponSlot((WeaponSlotType)wt);
				if (weapon)
				{
					weapon->setPossibleNextShotFrame(m_whenWeCanFireAgain);
					weapon->setStatus(RELOADING_CLIP);
				}
			}
		}
	}
}

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
// ?isGoalPosWithinAttackRange@Weapon@@ present-unmatched
Bool Weapon::isGoalPosWithinAttackRange(const Object *source, const Coord3D* goalPos, const Object *target, const Coord3D* targetPos)	const
{
	Real distSqr;
	// Note - undersize by 1/4 of a pathfind cell, so that the goal is not teetering on the edge
	// of firing range.  jba.
	// Note 2 - even with RATIONALIZE_ATTACK_RANGE, we still need to subtract 1/4 of a pathfind cell, 
	// otherwise if it teters on the edge, attacks can fail.  jba. 
	Real attackRangeSqr = sqr(getAttackRange(source)-(PATHFIND_CELL_SIZE_F*0.25f));

	if (target != NULL)
	{
		if (target->isKindOf(KINDOF_BRIDGE))
		{
			// Special case - bridges have two attackable points at either end.
			TBridgeAttackInfo info;
			TheTerrainLogic->getBridgeAttackPoints(target, &info);
			distSqr = ThePartitionManager->getGoalDistanceSquared( source, goalPos, &info.attackPoint1, ATTACK_RANGE_CALC_TYPE );
			if (distSqr>attackRangeSqr) 
			{
				// Try the other one.
				distSqr = ThePartitionManager->getGoalDistanceSquared( source, goalPos, &info.attackPoint2, ATTACK_RANGE_CALC_TYPE );
			}
		}	
		else 
		{
			distSqr = ThePartitionManager->getGoalDistanceSquared( source, goalPos, target, ATTACK_RANGE_CALC_TYPE );
		}
	}
	else
	{
		distSqr = ThePartitionManager->getGoalDistanceSquared( source, goalPos, targetPos, ATTACK_RANGE_CALC_TYPE );
	}

	// Note - oversize by 1/4 of a pathfind cell, so that the goal is not teetering on the edge
	// of firing range.  jba.
	// Note 2 - even with RATIONALIZE_ATTACK_RANGE, we still need to add 1/4 of a pathfind cell, 
	// otherwise if it teters on the edge, attacks can fail.  jba. 
	Real minAttackRangeSqr = sqr(m_template->getMinimumAttackRange()+(PATHFIND_CELL_SIZE_F*0.25f));
#ifdef RATIONALIZE_ATTACK_RANGE
	if (distSqr < minAttackRangeSqr)
#else
	if (distSqr < minAttackRangeSqr-0.5f)
#endif
	{
		return false;
	}
	return (distSqr <= attackRangeSqr);
}

//-------------------------------------------------------------------------------------------------
// Weapon::getPercentReadyToFire is defined with its retail-matched body in Code/GameEngine/Source/Common/Rva002CCE53Finish.cpp (0x002CCE53).

//-------------------------------------------------------------------------------------------------
// Weapon::getAttackRange is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Weapon_Weapon_getAttackRange.cpp (0x002C9BF8).

//-------------------------------------------------------------------------------------------------
// Weapon::getAttackDistance is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/PartitionManager_Rva002C9C37.cpp (0x002C9C37).

//-------------------------------------------------------------------------------------------------
// ?estimateWeaponDamage@Weapon@@ present-unmatched
Real Weapon::estimateWeaponDamage(const Object *sourceObj, const Object *victimObj, const Coord3D* victimPos)
{
	if (!m_template)
		return 0.0f;

	// if the weapon is just reloading, it's ok. if it's out of ammo
	// (and won't autoreload), then we aren't gonna do any damage.
	if (getStatus() == OUT_OF_AMMO && !m_template->getAutoReloadsClip())
		return 0.0f;

	WeaponBonus bonus;
	computeBonus(sourceObj, 0, bonus);

	return m_template->estimateWeaponTemplateDamage(sourceObj, victimObj, victimPos, bonus);
}

//-------------------------------------------------------------------------------------------------
// ?newProjectileFired@Weapon@@ present-unmatched
void Weapon::newProjectileFired(const Object *sourceObj, const Object *projectile, const Object *victimObj, const Coord3D *victimPos )
{
	// If I have a stream, I need to tell it about this new guy
	if( m_template->getProjectileStreamName().isEmpty() )
		return; // nope, no streak logic to do

	Object* projectileStream = TheGameLogic->findObjectByID(m_projectileStreamID);
	if( projectileStream == NULL )
	{
		m_projectileStreamID = INVALID_ID;	// reset, since it might have been "valid" but deleted out from under us
		const ThingTemplate* pst = TheThingFactory->findTemplate(m_template->getProjectileStreamName());
		projectileStream = TheThingFactory->newObject( pst, sourceObj->getControllingPlayer()->getDefaultTeam() );
		if( projectileStream == NULL )
			return;
		m_projectileStreamID = projectileStream->getID();
	}

	//Check for projectile stream update
	static NameKeyType key_ProjectileStreamUpdate = NAMEKEY("ProjectileStreamUpdate");
	ProjectileStreamUpdate* update = (ProjectileStreamUpdate*)projectileStream->findUpdateModule(key_ProjectileStreamUpdate);
	if( update )
	{
		update->setPosition( sourceObj->getPosition() );
		update->addProjectile( sourceObj->getID(), projectile->getID(), victimObj ? victimObj->getID() : INVALID_ID, victimPos );
		return;
	}

}

//-------------------------------------------------------------------------------------------------
// ?createLaser@Weapon@@ present-unmatched
void Weapon::createLaser( const Object *sourceObj, const Object *victimObj, const Coord3D *victimPos )
{
	const ThingTemplate* pst = TheThingFactory->findTemplate(m_template->getLaserName());
	if( !pst )
	{
		DEBUG_CRASH( ("Weapon::createLaser(). %s could not find template for its laser %s.", 
			sourceObj->getTemplate()->getName().str(), m_template->getLaserName().str() ) );
		return;
	}
	Object* laser = TheThingFactory->newObject( pst, sourceObj->getControllingPlayer()->getDefaultTeam() );
	if( laser == NULL )
		return;

	// Give it a good basis in reality to ensure it can draw when on screen.
	laser->setPosition(sourceObj->getPosition());
	
	//Check for laser update
	Drawable *draw = laser->getDrawable();
	if( draw )
	{
		static NameKeyType key_LaserUpdate = NAMEKEY( "LaserUpdate" );
		LaserUpdate *update = (LaserUpdate*)draw->findClientUpdateModule( key_LaserUpdate );
		if( update )
		{
			Coord3D pos = *victimPos;
			if( victimObj && !victimObj->isKindOf( KINDOF_PROJECTILE ) && !victimObj->isAirborneTarget() )
			{
				//Targets are positioned on the ground, so raise the beam up so we're not shooting their feet.
				//Projectiles are a different story, target their exact position.
				pos.z += 10.0f;
			}
			update->initLaser( sourceObj, victimObj, sourceObj->getPosition(), &pos, m_template->getLaserBoneName() );
		}
	}
}

//-------------------------------------------------------------------------------------------------
// return true if we auto-reloaded our clip after firing.
//DECLARE_PERF_TIMER(fireWeapon)
// ?privateFireWeapon@Weapon@@ present-unmatched
Bool Weapon::privateFireWeapon(
	const Object *sourceObj, 
	Object *victimObj, 
	const Coord3D* victimPos, 
	Bool isProjectileDetonation, 
	Bool ignoreRanges, 
	WeaponBonusConditionFlags extraBonusFlags,
	ObjectID* projectileID,
	Bool inflictDamage
)
{
	//CRCDEBUG_LOG(("Weapon::privateFireWeapon() for %s\n", DescribeObject(sourceObj).str()));
	//USE_PERF_TIMER(fireWeapon)
	if (projectileID)
		*projectileID = INVALID_ID;

	if (!m_template)
		return false;

	// If we are a networked weapon, tell everyone nearby they might want to get in on this shot
	if( m_template->getRequestAssistRange()  &&  victimObj )
		processRequestAssistance( sourceObj, victimObj );

	//For weapon templates that have the leech range weapon flag set, it essentially grants 
	//the weapon unlimited range for the remainder of the attack. While it's triggered here 
	//it's the AIAttackState machine that actually uses and resets this value.
	//This makes the ASSUMPTION that it is IMPOSSIBLE TO FIRE A WEAPON WITHOUT BEING IN AN AIATTACKSTATE
	//
	// @todo srj -- this isn't a universally true assertion! eg, FireWeaponDie lets you do this easily.
	//
	if( m_template->isLeechRangeWeapon() )
	{
		setLeechRangeActive( TRUE );
	}

	//Special case damge type overrides requiring special handling.
	switch( m_template->getDamageType() )
	{
		case DAMAGE_DEPLOY:
		{
			const AIUpdateInterface *ai = sourceObj->getAI();
			if( ai )
			{
				const AssaultTransportAIInterface *atInterface = ai->getAssaultTransportAIInterface();
				if( atInterface )
				{
					atInterface->beginAssault( victimObj );
				}
			}
			break;
		}

		case DAMAGE_DISARM:
		{
			if (sourceObj && victimObj)
			{
				Bool found = false;
				for (BehaviorModule** bmi = victimObj->getBehaviorModules(); *bmi; ++bmi)
				{
					LandMineInterface* lmi = (*bmi)->getLandMineInterface();
					if (lmi)
					{
						VeterancyLevel v = sourceObj->getVeterancyLevel();
						FXList::doFXPos(m_template->getFireFX(v), victimObj->getPosition(), victimObj->getTransformMatrix(), 0, victimObj->getPosition(), 0);
						lmi->disarm();
						found = true;
						break;
					}
				}

				// it's a mine, but doesn't have LandMineInterface...
				if( !found && victimObj->isKindOf( KINDOF_MINE ) || victimObj->isKindOf( KINDOF_BOOBY_TRAP ) || victimObj->isKindOf( KINDOF_DEMOTRAP ) )
				{
					VeterancyLevel v = sourceObj->getVeterancyLevel();
					FXList::doFXPos(m_template->getFireFX(v), victimObj->getPosition(), victimObj->getTransformMatrix(), 0, victimObj->getPosition(), 0);
					TheGameLogic->destroyObject( victimObj );// douse this thing before somebody gets hurt!
					found = true;
				}

				if( found )
				{
					sourceObj->getControllingPlayer()->getAcademyStats()->recordMineCleared();
				}
			}

			--m_maxShotCount;
			--m_ammoInClip;	// so we can use the delay between shots on the mine clearing weapon
			if (m_ammoInClip <= 0 && m_template->getAutoReloadsClip())
			{
				reloadAmmo(sourceObj);
				return TRUE;	// reloaded
			}
			else
			{
				return FALSE;	// did not reload
			}
		}

		case DAMAGE_HACK:
		{
			//We're using a hacker unit to hack a target. Hacking has various effects and
			//instead of inflicting damage, we are waiting for a period of time until the hack takes effect.
			//return FALSE;
		}	
	}

	WeaponBonus bonus;
	computeBonus(sourceObj, extraBonusFlags, bonus);

	DEBUG_ASSERTCRASH(getStatus() != OUT_OF_AMMO, ("Hmm, firing weapon that is OUT_OF_AMMO"));
	DEBUG_ASSERTCRASH(getStatus() == READY_TO_FIRE, ("Hmm, Weapon is firing more often than should be possible"));
	DEBUG_ASSERTCRASH(m_ammoInClip > 0, ("Hmm, firing an empty weapon"));

	if (getStatus() != READY_TO_FIRE)
		return false;

	UnsignedInt now = TheGameLogic->getFrame();
	Bool reloaded = false;
	if (m_ammoInClip > 0)
	{
		Int barrelCount = sourceObj->getDrawable()->getBarrelCount(m_wslot);
		if (m_curBarrel >= barrelCount)
		{
			m_curBarrel = 0;
			m_numShotsForCurBarrel = m_template->getShotsPerBarrel();
		}

		if( m_scatterTargetsUnused.size() )
		{
			// If I have a set scatter pattern, I need to offset the target by a random pick from that pattern
			if( victimObj )
			{
				victimPos = victimObj->getPosition();
				victimObj = NULL;
			}
			Coord3D targetPos = *victimPos; // need to copy, as this pointer is actually inside somebody potentially
			Int randomPick = GameLogicRandomValue( 0, m_scatterTargetsUnused.size() - 1 );
			Int targetIndex = m_scatterTargetsUnused[randomPick];

			Real scatterTargetScalar = getScatterTargetScalar();// essentially a radius, but operates only on this scatterTarget table
			Coord2D scatterOffset = m_template->getScatterTargetsVector().at( targetIndex );

			scatterOffset.x *= scatterTargetScalar;
			scatterOffset.y *= scatterTargetScalar;

			targetPos.x += scatterOffset.x;
			targetPos.y += scatterOffset.y;

			targetPos.z = TheTerrainLogic->getGroundHeight(targetPos.x, targetPos.y);

			// To erase from a vector, put the last on the one you used and pop the back.
			m_scatterTargetsUnused[randomPick] = m_scatterTargetsUnused.back();
			m_scatterTargetsUnused.pop_back();
			m_template->fireWeaponTemplate(sourceObj, m_wslot, m_curBarrel, victimObj, &targetPos, bonus, isProjectileDetonation, ignoreRanges, this, projectileID, inflictDamage );
		}
		else
		{
			m_template->fireWeaponTemplate(sourceObj, m_wslot, m_curBarrel, victimObj, victimPos, bonus, isProjectileDetonation, ignoreRanges, this, projectileID, inflictDamage );
		}
		
		m_lastFireFrame = now;
		--m_ammoInClip;
		--m_maxShotCount;
		--m_numShotsForCurBarrel;
		if (m_numShotsForCurBarrel <= 0)
		{
			++m_curBarrel;
			m_numShotsForCurBarrel = m_template->getShotsPerBarrel();
		}

		if (m_ammoInClip <= 0)
		{
			if (m_template->getAutoReloadsClip())
			{
				reloadAmmo(sourceObj);
				reloaded = true;
			}
			else
			{
				m_status = OUT_OF_AMMO;
				m_whenWeCanFireAgain = 0x7fffffff;
				//CRCDEBUG_LOG(("Just set m_whenWeCanFireAgain to %d in Weapon::privateFireWeapon 1\n", m_whenWeCanFireAgain));
			}
		}
		else
		{
			m_status = BETWEEN_FIRING_SHOTS;
			//CRCDEBUG_LOG(("Weapon::privateFireWeapon() just set m_status to BETWEEN_FIRING_SHOTS\n"));
			Int delay = m_template->getDelayBetweenShots(bonus);
			m_whenLastReloadStarted = now;
			m_whenWeCanFireAgain = now + delay;
			//CRCDEBUG_LOG(("Just set m_whenWeCanFireAgain to %d (delay is %d) in Weapon::privateFireWeapon\n", m_whenWeCanFireAgain, delay));
			
			// if we are sharing reload times
			// go through other weapons in weapon set
			// set their m_whenWeCanFireAgain to this guy's delay
			// set their m_status to this guy's status

			if ( sourceObj->isReloadTimeShared() )
			{	
				for (Int wt = 0; wt<WEAPONSLOT_COUNT; wt++)
				{
					Weapon *weapon = sourceObj->getWeaponInWeaponSlot((WeaponSlotType)wt);
					if (weapon)
					{
						weapon->setPossibleNextShotFrame(m_whenWeCanFireAgain);
						//CRCDEBUG_LOG(("Just set m_whenWeCanFireAgain to %d in Weapon::privateFireWeapon 3\n", m_whenWeCanFireAgain));
						weapon->setStatus(BETWEEN_FIRING_SHOTS);
					}
				}
			}
 
		}
	}
 
	return reloaded;
}


//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Bool Weapon::fireWeapon(const Object *source, Object *target, ObjectID* projectileID)
{
	//CRCDEBUG_LOG(("Weapon::fireWeapon() for %s at %s\n", DescribeObject(source).str(), DescribeObject(target).str()));
	return privateFireWeapon( source, target, NULL, false, false, 0, projectileID, TRUE );
}

//-------------------------------------------------------------------------------------------------
// return true if we auto-reloaded our clip after firing.
Bool Weapon::fireWeapon(const Object *source, const Coord3D* pos, ObjectID* projectileID)
{
	//CRCDEBUG_LOG(("Weapon::fireWeapon() for %s\n", DescribeObject(source).str()));
	return privateFireWeapon( source, NULL, pos, false, false, 0, projectileID, TRUE );
}

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
// ?getPrimaryDamageRadius@Weapon@@ present-unmatched
Real Weapon::getPrimaryDamageRadius(const Object *source) const
{
	WeaponBonus bonus;
	computeBonus(source, 0, bonus);
	return m_template->getPrimaryDamageRadius(bonus);
}

//-------------------------------------------------------------------------------------------------
// ?isDamageWeapon@Weapon@@ present-unmatched
Bool Weapon::isDamageWeapon() const
{
	//These damage types are special attacks that don't do damage directly, even
	//if they can indirectly. These are here to prevent the UI from allowing the
	//user to mouseover a target and think it can attack it using these types.
	switch( m_template->getDamageType() )
	{
		case DAMAGE_DEPLOY:
			//Kris @todo
			//Evaluate a better way to handle this weapon type... doesn't fit being a damage weapon.
			//May want to check if cargo can attack!
			return TRUE;

		case DAMAGE_DISARM:
			return TRUE;	// hmm, can only "damage" mines, but still...

		case DAMAGE_HACK:
			return FALSE;
	}
	
	//Use no bonus
	WeaponBonus whoCares;
	if( m_template->getPrimaryDamage( whoCares ) > 0.0f || m_template->getSecondaryDamage( whoCares ) > 0.0f )
	{
		return TRUE;
	}

	return FALSE;
}

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
Bool Weapon::isClearFiringLineOfSightTerrain(const Object* source, const Object* victim) const
{
	Coord3D origin;
	origin = *source->getPosition();
	//CRCDEBUG_LOG(("Weapon::isClearFiringLineOfSightTerrain(Object) for %s\n", DescribeObject(source).str()));
	//DUMPCOORD3D(&origin);
	getFiringLineOfSightOrigin(source, origin);
	Coord3D victimPos;
	victim->getGeometryInfo().getCenterPosition( *victim->getPosition(), victimPos );
	//CRCDEBUG_LOG(("Weapon::isClearFiringLineOfSightTerrain() - victimPos is (%g,%g,%g) (%X,%X,%X)\n",
	//	victimPos.x, victimPos.y, victimPos.z,
	//	AS_INT(victimPos.x),AS_INT(victimPos.y),AS_INT(victimPos.z)));
	return ThePartitionManager->isClearLineOfSightTerrain(NULL, origin, NULL, victimPos);
}

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
// variants below ask the terrain directly. Retail builds them for size (frame
// pointer, rep-style copies, an out-of-line getFiringLineOfSightOrigin) inside
// this otherwise /O2 unit, and the goal variant copies goalPos through SSE
// registers, which is what /Op ("p") produces.
#pragma optimize("t", off)
#pragma optimize("s", on)
Bool Weapon::isClearFiringLineOfSightTerrain(const Object* source, const Coord3D& victimPos) const
{
	Coord3D origin;
	origin = *source->getPosition();
	//CRCDEBUG_LOG(("Weapon::isClearFiringLineOfSightTerrain(Coord3D) for %s\n", DescribeObject(source).str()));
	//DUMPCOORD3D(&origin);
	getFiringLineOfSightOrigin(source, origin);
	return ((const BfmeTerrainLogicLOSView *)TheTerrainLogic)->isClearLineOfSight(origin, victimPos);
}
#pragma optimize("", on)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** Determine whether if source was at goalPos whether it would have clear line of sight. */
Bool Weapon::isClearGoalFiringLineOfSightTerrain(const Object* source, const Coord3D& goalPos, const Object* victim) const
{
	Coord3D origin=goalPos;
	//CRCDEBUG_LOG(("Weapon::isClearGoalFiringLineOfSightTerrain(Object) for %s\n", DescribeObject(source).str()));
	//DUMPCOORD3D(&origin);
	getFiringLineOfSightOrigin(source, origin);
	Coord3D victimPos;
	victim->getGeometryInfo().getCenterPosition( *victim->getPosition(), victimPos );
	return ThePartitionManager->isClearLineOfSightTerrain(NULL, origin, NULL, victimPos);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** Determine whether if source was at goalPos whether it would have clear line of sight. */
#pragma optimize("t", off)
#pragma optimize("sp", on)
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
#pragma optimize("", on)

//-------------------------------------------------------------------------------------------------
//Kris: Patch 1.01 - November 10, 2003
//This function was added to transfer key weapon stats for Jarmen Kell to and from the bike for
//the sniper attack, so he can share the stats.
//-------------------------------------------------------------------------------------------------
// ?transferNextShotStatsFrom@Weapon@@ present-unmatched
void Weapon::transferNextShotStatsFrom( const Weapon &weapon ) 
{ 
	m_whenWeCanFireAgain = weapon.getPossibleNextShotFrame();
	m_whenLastReloadStarted = weapon.getLastReloadStartedFrame();
	m_status = weapon.getStatus();
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?crc@Weapon@@ present-unmatched
void Weapon::crc( Xfer *xfer )
{
#ifdef DEBUG_CRC
	AsciiString logString;
	AsciiString tmp;
	Bool doLogging = g_logObjectCRCs;
	if (doLogging)
	{
		tmp.format("CRC of weapon %s: ", m_template->getName().str());
		logString.concat(tmp);
	}
#endif DEBUG_CRC

	AsciiString tmplName = m_template->getName();
	xfer->xferAsciiString(&tmplName);

	// slot
	xfer->xferUser( &m_wslot, sizeof( WeaponSlotType ) );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_wslot %d ", m_wslot);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// status
	/*
	xfer->xferUser( &m_status, sizeof( WeaponStatus ) );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_status %d ", m_status);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC
	*/

	// ammo
	xfer->xferUnsignedInt( &m_ammoInClip );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_ammoInClip %d ", m_ammoInClip);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// when can fire again
	xfer->xferUnsignedInt( &m_whenWeCanFireAgain );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_whenWeCanFireAgain %d ", m_whenWeCanFireAgain);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// when pre attack finished
	xfer->xferUnsignedInt( &m_whenPreAttackFinished );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_whenPreAttackFinished %d ", m_whenPreAttackFinished);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// when last reload started
	xfer->xferUnsignedInt( &m_whenLastReloadStarted );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_whenLastReloadStarted %d ", m_whenLastReloadStarted);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// last fire frame
	xfer->xferUnsignedInt( &m_lastFireFrame );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_lastFireFrame %d ", m_lastFireFrame);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// projectile stream object
	xfer->xferObjectID( &m_projectileStreamID );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("projectileStreamID %d ", m_projectileStreamID);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// laser object (defunct)
	ObjectID laserIDUnused = INVALID_ID;
	xfer->xferObjectID( &laserIDUnused );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("laserID %d ", laserIDUnused);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// max shot count
	xfer->xferInt( &m_maxShotCount );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_maxShotCount %d ", m_maxShotCount);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// current barrel
	xfer->xferInt( &m_curBarrel );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_curBarrel %d ", m_curBarrel);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// num shots for current barrel
	xfer->xferInt( &m_numShotsForCurBarrel );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_numShotsForCurBarrel %d ", m_numShotsForCurBarrel);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// scatter targets unused
	UnsignedShort scatterCount = m_scatterTargetsUnused.size();
	xfer->xferUnsignedShort( &scatterCount );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("scatterCount %d ", scatterCount);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	Int intData;

	std::vector< Int >::const_iterator it;

	for( it = m_scatterTargetsUnused.begin(); it != m_scatterTargetsUnused.end(); ++it )
	{

		intData = *it;
		xfer->xferInt( &intData );
#ifdef DEBUG_CRC
		if (doLogging)
		{
			tmp.format("%d ", intData);
			logString.concat(tmp);
		}
#endif // DEBUG_CRC

	}  // end for, it

	// pitch limited
	xfer->xferBool( &m_pitchLimited );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_pitchLimited %d ", m_pitchLimited);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC

	// leech weapon range active
	xfer->xferBool( &m_leechWeaponRangeActive );
#ifdef DEBUG_CRC
	if (doLogging)
	{
		tmp.format("m_leechWeaponRangeActive %d ", m_leechWeaponRangeActive);
		logString.concat(tmp);
	}
#endif // DEBUG_CRC


#ifdef DEBUG_CRC
	if (doLogging)
	{
		CRCDEBUG_LOG(("%s\n", logString.str()));
	}
#endif // DEBUG_CRC

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@Weapon@@ present-unmatched
void Weapon::loadPostProcess( void )
{
	if( m_projectileStreamID != INVALID_ID )
	{
		Object* projectileStream = TheGameLogic->findObjectByID( m_projectileStreamID );
		if( projectileStream == NULL )
		{
			m_projectileStreamID = INVALID_ID;
		}
	}
}

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

//-------------------------------------------------------------------------------------------------
// WeaponBonusSet::appendBonuses: defined in WeaponBonusAppend.cpp (its row's unit).
