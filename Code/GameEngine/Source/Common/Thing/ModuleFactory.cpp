// cl: /Ireference/shims/bfme2_drawable_flash /Ireference/shims/modulefactory_tagctor /Ireference/shims/aiupdatelayout /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/modulefactory /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/Thing/ModuleFactory.cpp); this unit had no counterpart under Code/.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
// Retail calls _mbscpy through the import thunk at 0x00629176.
#include <mbstring.h>
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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

// FILE: ModuleFactory.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2001
// Desc:	 TheModuleFactory is where we actually instance modules for objects
//				 and drawbles.  Those modules are things such as an UpdateModule
//			   or DamageModule or DrawModule etc.
//	
//				 TheModuleFactory will contain a list of ModuleTemplates, when we
//				 request a new module, we will look for that template in our
//				 list and create it
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
// Use the existing range-destruction provider while direct string members
// inline their buffer release, as in GrantScienceUpgradeModuleData retail.
namespace _STL { template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *); }
// Local copy of the consumed ZH DamageModule view, Open-BFME-1
// 0bf534ea7ccde110c456edb9cd2dd5dae823c953 inputs/reference/GeneralsMD.
// Preserve its classes and layout; use the existing 16-byte zero-object owner.
// The original include guard prevents later module headers redefining this view.
#ifndef __DamageModule_H_
#define __DamageModule_H_

#include "Common/Module.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Module/BehaviorModule.h"

extern const int g_emptyFieldParseTable[4];

enum BodyDamageType;

//-------------------------------------------------------------------------------------------------
/** OBJECT DAMAGE MODULE base class */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class DamageModuleInterface
{

public:

	virtual void onDamage( DamageInfo *damageInfo ) = 0;	///< damage callback
	virtual void onHealing( DamageInfo *damageInfo ) = 0;	///< healing callback
	virtual void onBodyDamageStateChange( const DamageInfo* damageInfo,
																				BodyDamageType oldState,
																				BodyDamageType newState) = 0;  ///< state change callback

};

//-------------------------------------------------------------------------------------------------
class DamageModuleData : public BehaviorModuleData
{
public:
//	DamageTypeFlags m_damageTypes;

	DamageModuleData()
//		: m_damageTypes(DAMAGE_TYPE_FLAGS_ALL)
	{
	}

	static void buildFieldParse(MultiIniFieldParse& p)
	{
    BehaviorModuleData::buildFieldParse(p);

    p.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable));
	}
};

//-------------------------------------------------------------------------------------------------
class DamageModule : public BehaviorModule, public DamageModuleInterface
{

	MEMORY_POOL_GLUE_ABC( DamageModule )
	MAKE_STANDARD_MODULE_MACRO_ABC( DamageModule )
	MAKE_STANDARD_MODULE_DATA_MACRO_ABC( DamageModule, DamageModuleData )

public:

	DamageModule( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype defined by MemoryPoolObject

	// module methods
	static Int getInterfaceMask() { return MODULEINTERFACE_DAMAGE; }

	// BehaviorModule
	virtual DamageModuleInterface* getDamage() { return this; }

	// damage module callbacks
	virtual void onDamage( DamageInfo *damageInfo ) = 0;	///< damage callback
	virtual void onHealing( DamageInfo *damageInfo ) = 0;	///< healing callback
	virtual void onBodyDamageStateChange( const DamageInfo* damageInfo,
																				BodyDamageType oldState,
																				BodyDamageType newState) = 0;  ///< state change callback

protected:

};
inline DamageModule::DamageModule( Thing *thing, const ModuleData* moduleData ) : BehaviorModule( thing, moduleData ) { }
// ?DamageModule::~DamageModule present-unmatched
inline DamageModule::~DamageModule() { }
//-------------------------------------------------------------------------------------------------

#endif


#include "Common/Module.h"
#include "Common/ModuleFactory.h"
#include "Common/NameKeyGenerator.h"

// behavior includes
#include "GameLogic/Module/AutoHealBehavior.h"
#include "GameLogic/Module/GrantStealthBehavior.h"
#include "GameLogic/Module/NeutronBlastBehavior.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeScaffoldBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"
#include "GameLogic/Module/CountermeasuresBehavior.h"
#include "GameLogic/Module/DumbProjectileBehavior.h"
#include "GameLogic/Module/InstantDeathBehavior.h"
#include "GameLogic/Module/SlowDeathBehavior.h"
#include "GameLogic/Module/HelicopterSlowDeathUpdate.h"
#include "GameLogic/Module/NeutronMissileSlowDeathUpdate.h"
#include "GameLogic/Module/CaveContain.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Module/OverchargeBehavior.h"
#include "GameLogic/Module/HealContain.h"
#include "GameLogic/Module/GarrisonContain.h"
#include "GameLogic/Module/InternetHackContain.h"
#include "GameLogic/Module/RailedTransportContain.h"
#include "GameLogic/Module/RiderChangeContain.h"
#include "GameLogic/Module/TransportContain.h"
#include "GameLogic/Module/MobNexusContain.h"
#include "GameLogic/Module/TunnelContain.h"
#include "GameLogic/Module/OverlordContain.h"
#include "GameLogic/Module/HelixContain.h"
#include "GameLogic/Module/ParachuteContain.h"
#ifdef ALLOW_SURRENDER
#include "GameLogic/Module/POWTruckBehavior.h"
#include "GameLogic/Module/PrisonBehavior.h"
#include "GameLogic/Module/PropagandaCenterBehavior.h"
#endif 
#include "GameLogic/Module/PropagandaTowerBehavior.h"
#include "GameLogic/Module/BunkerBusterBehavior.h"
#include "GameLogic/Module/FireWeaponWhenDamagedBehavior.h"
#include "GameLogic/Module/FireWeaponWhenDeadBehavior.h"
#include "GameLogic/Module/GenerateMinefieldBehavior.h"
#include "GameLogic/Module/ParkingPlaceBehavior.h"
#include "GameLogic/Module/FlightDeckBehavior.h"
#include "GameLogic/Module/PoisonedBehavior.h"
#include "GameLogic/Module/RebuildHoleBehavior.h"
#include "GameLogic/Module/SupplyWarehouseCripplingBehavior.h"
#include "GameLogic/Module/TechBuildingBehavior.h"
#include "GameLogic/Module/MinefieldBehavior.h"
#include "GameLogic/Module/BattleBusSlowDeathBehavior.h"
#include "GameLogic/Module/JetSlowDeathBehavior.h"

// die includes
#include "GameLogic/Module/CreateCrateDie.h"
#include "GameLogic/Module/CreateObjectDie.h"
#include "GameLogic/Module/CrushDie.h"
#include "GameLogic/Module/DamDie.h"
#include "GameLogic/Module/DestroyDie.h"
#include "GameLogic/Module/EjectPilotDie.h"
#include "GameLogic/Module/FXListDie.h"
#include "GameLogic/Module/RebuildHoleExposeDie.h"
#include "GameLogic/Module/SpecialPowerCompletionDie.h"
#include "GameLogic/Module/UpgradeDie.h"
#include "GameLogic/Module/KeepObjectDie.h"

// logic update includes
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/AnimationSteeringUpdate.h"
#include "GameLogic/Module/AssistedTargetingUpdate.h"
#include "GameLogic/Module/BaseRegenerateUpdate.h"
#include "GameLogic/Module/BoneFXUpdate.h"
#include "GameLogic/Module/ChinookAIUpdate.h"
#include "GameLogic/Module/DefaultProductionExitUpdate.h"
#include "GameLogic/Module/DeletionUpdate.h"
#include "GameLogic/Module/SmartBombTargetHomingUpdate.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/DozerAIUpdate.h"
#include "GameLogic/Module/DynamicGeometryInfoUpdate.h"
#include "GameLogic/Module/DynamicShroudClearingRangeUpdate.h"
#include "GameLogic/Module/EnemyNearUpdate.h"
#include "GameLogic/Module/FireSpreadUpdate.h"
#include "GameLogic/Module/FirestormDynamicGeometryInfoUpdate.h"
#include "GameLogic/Module/FireWeaponUpdate.h"
#include "GameLogic/Module/FlammableUpdate.h"
#include "GameLogic/Module/FloatUpdate.h"
#include "GameLogic/Module/TensileFormationUpdate.h"
#include "GameLogic/Module/HackInternetAIUpdate.h"
#include "GameLogic/Module/DeployStyleAIUpdate.h"
#include "GameLogic/Module/AssaultTransportAIUpdate.h"
#include "GameLogic/Module/HeightDieUpdate.h"
#include "GameLogic/Module/HordeUpdate.h"
#include "GameLogic/Module/JetAIUpdate.h"
#include "GameLogic/Module/LaserUpdate.h"
#include "GameLogic/Module/PointDefenseLaserUpdate.h"
#include "GameLogic/Module/CleanupHazardUpdate.h"
#include "GameLogic/Module/AutoFindHealingUpdate.h"
#include "GameLogic/Module/CommandButtonHuntUpdate.h"
#include "GameLogic/Module/PilotFindVehicleUpdate.h"
#include "GameLogic/Module/DemoTrapUpdate.h"
#include "GameLogic/Module/ParticleUplinkCannonUpdate.h"
#include "GameLogic/Module/SpectreGunshipUpdate.h"
#include "GameLogic/Module/SpectreGunshipDeploymentUpdate.h"
#include "GameLogic/Module/BaikonurLaunchPower.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/Module/LifetimeUpdate.h"
#include "GameLogic/Module/RadiusDecalUpdate.h"
#include "GameLogic/Module/AutoDepositUpdate.h"
#include "GameLogic/Module/MissileAIUpdate.h"
#include "GameLogic/Module/NeutronMissileUpdate.h"
#include "GameLogic/Module/OCLUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#ifdef ALLOW_SURRENDER
#include "GameLogic/Module/POWTruckAIUpdate.h"
#endif
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/ProjectileStreamUpdate.h"
#include "GameLogic/Module/ProneUpdate.h"
#include "GameLogic/Module/QueueProductionExitUpdate.h"
#include "GameLogic/Module/RadarUpdate.h"
#include "GameLogic/Module/RepairDockUpdate.h"
#ifdef ALLOW_SURRENDER
#include "GameLogic/Module/PrisonDockUpdate.h"
#endif
#include "GameLogic/Module/RailedTransportDockUpdate.h"
#include "GameLogic/Module/RailedTransportAIUpdate.h"
#include "GameLogic/Module/RailroadGuideAIUpdate.h"
// Zero Hour's SlavedUpdate.h and SpawnBehavior.h define their rates as compile-time
// constants; this unit takes BFME 2's dynamic ones below, so the Zero Hour names stand aside.
#define SLAVED_UPDATE_RATE ZH_SLAVED_UPDATE_RATE_CONSTANT
#include "GameLogic/Module/SlavedUpdate.h"
#undef SLAVED_UPDATE_RATE
#include "GameLogic/Module/MobMemberSlavedUpdate.h"
#include "GameLogic/Module/SpecialAbilityUpdate.h"
#include "GameLogic/Module/MissileLauncherBuildingUpdate.h"
#include "GameLogic/Module/StealthDetectorUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/SpawnPointProductionExitUpdate.h"
#define SPAWN_UPDATE_RATE ZH_SPAWN_UPDATE_RATE_CONSTANT
#include "GameLogic/Module/SpawnBehavior.h"
#undef SPAWN_UPDATE_RATE
// Retail's ModuleFactory run (LINK-236): the Drawable.h copy 0x007ADCF8 (its static right
// after TheModuleFactory; Zero Hour's Drawable.h, reached through the module headers, takes
// the BFME 2 constant from the bfme2_drawable_flash shim on this unit's include path),
// SPAWN_UPDATE_RATE 0x007ADD08, four header masks, then SLAVED_UPDATE_RATE 0x007ADD72.
#include "../../../Include/GameLogic/Module/SpawnUpdateRate.h"
#include "../../../Include/GameLogic/Module/SlavedUpdateRate.h"
#include "GameLogic/Module/SpyVisionUpdate.h"
#include "GameLogic/Module/StickyBombUpdate.h"
#include "GameLogic/Module/FireOCLAfterWeaponCooldownUpdate.h"
#include "GameLogic/Module/HijackerUpdate.h"
#include "GameLogic/Module/StructureCollapseUpdate.h"
#include "GameLogic/Module/StructureToppleUpdate.h"
#include "GameLogic/Module/SupplyCenterDockUpdate.h"
#include "GameLogic/Module/SupplyCenterProductionExitUpdate.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/ToppleUpdate.h"
#include "GameLogic/Module/TransportAIUpdate.h"
#include "GameLogic/Module/WanderAIUpdate.h"
#include "GameLogic/Module/WaveGuideUpdate.h"
#include "GameLogic/Module/WeaponBonusUpdate.h"
#include "GameLogic/Module/WorkerAIUpdate.h"
#include "GameLogic/Module/PowerPlantUpdate.h"
#include "GameLogic/Module/CheckpointUpdate.h"
#include "GameLogic/Module/EMPUpdate.h"

// upgrade includes
#include "GameLogic/Module/ActiveShroudUpgrade.h"
#include "GameLogic/Module/ArmorUpgrade.h"
#include "GameLogic/Module/CommandSetUpgrade.h"
#include "GameLogic/Module/GrantScienceUpgrade.h"
#include "GameLogic/Module/PassengersFireUpgrade.h"
#include "GameLogic/Module/LocomotorSetUpgrade.h"
#include "GameLogic/Module/ObjectCreationUpgrade.h"
#include "GameLogic/Module/RadarUpgrade.h"
#include "GameLogic/Module/PowerPlantUpgrade.h"
#include "GameLogic/Module/ReplaceObjectUpgrade.h"
#include "GameLogic/Module/ModelConditionUpgrade.h"
#include "GameLogic/Module/StatusBitsUpgrade.h"
#include "GameLogic/Module/SubObjectsUpgrade.h"
#include "GameLogic/Module/StealthUpgrade.h"
#include "GameLogic/Module/UnpauseSpecialPowerUpgrade.h"
#include "GameLogic/Module/WeaponBonusUpgrade.h"
#include "GameLogic/Module/WeaponSetUpgrade.h"
#include "GameLogic/Module/WeaponBonusUpgrade.h"
#include "GameLogic/Module/CostModifierUpgrade.h"
#include "GameLogic/Module/ExperienceScalarUpgrade.h"
#include "GameLogic/Module/MaxHealthUpgrade.h"

// create includes
#include "GameLogic/Module/LockWeaponCreate.h"
#include "GameLogic/Module/SupplyCenterCreate.h"
#include "GameLogic/Module/SupplyWarehouseCreate.h"
#include "GameLogic/Module/GrantUpgradeCreate.h"
#include "GameLogic/Module/PreorderCreate.h"
#include "GameLogic/Module/SpecialPowerCreate.h"
#include "GameLogic/Module/VeterancyGainCreate.h"

// damage includes
#include "GameLogic/Module/BoneFXDamage.h"
// BFME 2's table, from retail's at 0x007F2A80: each mask spans 0x154 bytes, and it adds the subobject
// lists at +0xFD4 that Zero Hour's has no fields for. Only this table reads the fields here.
struct Bfme2DamageMask { char m_bytes[0x154]; };
struct Bfme2DamageFXEntry { char m_bytes[0x1C]; };
struct Bfme2SubObjectList { char m_bytes[0xC]; };

class TransitionDamageFXModuleData : public DamageModuleData
{
public:
	static void parseFXList( INI *ini, void *instance, void *store, const void *userData );
	static void parseObjectCreationList( INI *ini, void *instance, void *store, const void *userData );
	static void parseParticleSystem( INI *ini, void *instance, void *store, const void *userData );
	static void NeighborIDSubobjectNameDataAppend( INI *ini, void *instance, void *store, const void *userData );

	static void buildFieldParse(MultiIniFieldParse& p)
	{
		DamageModuleData::buildFieldParse(p);

		static const FieldParse dataFieldParse[] =
		{
			{ "DamageFXTypes", INI::parseDamageTypeFlags, NULL, offsetof( TransitionDamageFXModuleData, m_damageFXTypes ) },
			{ "DamageOCLTypes", INI::parseDamageTypeFlags, NULL, offsetof( TransitionDamageFXModuleData, m_damageOCLTypes ) },
			{ "DamageParticleTypes", INI::parseDamageTypeFlags, NULL, offsetof( TransitionDamageFXModuleData, m_damageParticleTypes ) },
			{ "DamagedFXList1", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][0] ) },
			{ "DamagedFXList2", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][1] ) },
			{ "DamagedFXList3", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][2] ) },
			{ "DamagedFXList4", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][3] ) },
			{ "DamagedFXList5", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][4] ) },
			{ "DamagedFXList6", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][5] ) },
			{ "DamagedFXList7", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][6] ) },
			{ "DamagedFXList8", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][7] ) },
			{ "DamagedFXList9", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][8] ) },
			{ "DamagedFXList10", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][9] ) },
			{ "DamagedFXList11", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][10] ) },
			{ "DamagedFXList12", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[0][11] ) },
			{ "ReallyDamagedFXList1", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][0] ) },
			{ "ReallyDamagedFXList2", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][1] ) },
			{ "ReallyDamagedFXList3", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][2] ) },
			{ "ReallyDamagedFXList4", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][3] ) },
			{ "ReallyDamagedFXList5", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][4] ) },
			{ "ReallyDamagedFXList6", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][5] ) },
			{ "ReallyDamagedFXList7", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][6] ) },
			{ "ReallyDamagedFXList8", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][7] ) },
			{ "ReallyDamagedFXList9", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][8] ) },
			{ "ReallyDamagedFXList10", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][9] ) },
			{ "ReallyDamagedFXList11", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][10] ) },
			{ "ReallyDamagedFXList12", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[1][11] ) },
			{ "RubbleFXList1", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][0] ) },
			{ "RubbleFXList2", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][1] ) },
			{ "RubbleFXList3", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][2] ) },
			{ "RubbleFXList4", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][3] ) },
			{ "RubbleFXList5", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][4] ) },
			{ "RubbleFXList6", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][5] ) },
			{ "RubbleFXList7", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][6] ) },
			{ "RubbleFXList8", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][7] ) },
			{ "RubbleFXList9", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][8] ) },
			{ "RubbleFXList10", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][9] ) },
			{ "RubbleFXList11", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][10] ) },
			{ "RubbleFXList12", TransitionDamageFXModuleData::parseFXList, NULL, offsetof( TransitionDamageFXModuleData, m_fxList[2][11] ) },
			{ "DamagedOCL1", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][0] ) },
			{ "DamagedOCL2", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][1] ) },
			{ "DamagedOCL3", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][2] ) },
			{ "DamagedOCL4", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][3] ) },
			{ "DamagedOCL5", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][4] ) },
			{ "DamagedOCL6", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][5] ) },
			{ "DamagedOCL7", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][6] ) },
			{ "DamagedOCL8", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][7] ) },
			{ "DamagedOCL9", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][8] ) },
			{ "DamagedOCL10", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][9] ) },
			{ "DamagedOCL11", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][10] ) },
			{ "DamagedOCL12", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[0][11] ) },
			{ "ReallyDamagedOCL1", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][0] ) },
			{ "ReallyDamagedOCL2", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][1] ) },
			{ "ReallyDamagedOCL3", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][2] ) },
			{ "ReallyDamagedOCL4", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][3] ) },
			{ "ReallyDamagedOCL5", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][4] ) },
			{ "ReallyDamagedOCL6", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][5] ) },
			{ "ReallyDamagedOCL7", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][6] ) },
			{ "ReallyDamagedOCL8", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][7] ) },
			{ "ReallyDamagedOCL9", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][8] ) },
			{ "ReallyDamagedOCL10", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][9] ) },
			{ "ReallyDamagedOCL11", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][10] ) },
			{ "ReallyDamagedOCL12", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[1][11] ) },
			{ "RubbleOCL1", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][0] ) },
			{ "RubbleOCL2", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][1] ) },
			{ "RubbleOCL3", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][2] ) },
			{ "RubbleOCL4", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][3] ) },
			{ "RubbleOCL5", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][4] ) },
			{ "RubbleOCL6", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][5] ) },
			{ "RubbleOCL7", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][6] ) },
			{ "RubbleOCL8", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][7] ) },
			{ "RubbleOCL9", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][8] ) },
			{ "RubbleOCL10", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][9] ) },
			{ "RubbleOCL11", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][10] ) },
			{ "RubbleOCL12", TransitionDamageFXModuleData::parseObjectCreationList, NULL, offsetof( TransitionDamageFXModuleData, m_OCL[2][11] ) },
			{ "DamagedParticleSystem1", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][0] ) },
			{ "DamagedParticleSystem2", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][1] ) },
			{ "DamagedParticleSystem3", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][2] ) },
			{ "DamagedParticleSystem4", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][3] ) },
			{ "DamagedParticleSystem5", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][4] ) },
			{ "DamagedParticleSystem6", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][5] ) },
			{ "DamagedParticleSystem7", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][6] ) },
			{ "DamagedParticleSystem8", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][7] ) },
			{ "DamagedParticleSystem9", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][8] ) },
			{ "DamagedParticleSystem10", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][9] ) },
			{ "DamagedParticleSystem11", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][10] ) },
			{ "DamagedParticleSystem12", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[0][11] ) },
			{ "ReallyDamagedParticleSystem1", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][0] ) },
			{ "ReallyDamagedParticleSystem2", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][1] ) },
			{ "ReallyDamagedParticleSystem3", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][2] ) },
			{ "ReallyDamagedParticleSystem4", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][3] ) },
			{ "ReallyDamagedParticleSystem5", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][4] ) },
			{ "ReallyDamagedParticleSystem6", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][5] ) },
			{ "ReallyDamagedParticleSystem7", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][6] ) },
			{ "ReallyDamagedParticleSystem8", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][7] ) },
			{ "ReallyDamagedParticleSystem9", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][8] ) },
			{ "ReallyDamagedParticleSystem10", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][9] ) },
			{ "ReallyDamagedParticleSystem11", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][10] ) },
			{ "ReallyDamagedParticleSystem12", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[1][11] ) },
			{ "RubbleParticleSystem1", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][0] ) },
			{ "RubbleParticleSystem2", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][1] ) },
			{ "RubbleParticleSystem3", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][2] ) },
			{ "RubbleParticleSystem4", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][3] ) },
			{ "RubbleParticleSystem5", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][4] ) },
			{ "RubbleParticleSystem6", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][5] ) },
			{ "RubbleParticleSystem7", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][6] ) },
			{ "RubbleParticleSystem8", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][7] ) },
			{ "RubbleParticleSystem9", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][8] ) },
			{ "RubbleParticleSystem10", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][9] ) },
			{ "RubbleParticleSystem11", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][10] ) },
			{ "RubbleParticleSystem12", TransitionDamageFXModuleData::parseParticleSystem, NULL, offsetof( TransitionDamageFXModuleData, m_particleSystem[2][11] ) },
			{ "RubbleNeighbor", TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend, NULL, offsetof( TransitionDamageFXModuleData, m_rubbleNeighbors ) },
			{ "PristineShowSubObject", INI::parseAsciiStringVectorAppend, NULL, offsetof( TransitionDamageFXModuleData, m_pristineShow ) },
			{ "PristineHideSubObject", INI::parseAsciiStringVectorAppend, NULL, offsetof( TransitionDamageFXModuleData, m_pristineHide ) },
			{ "DamagedShowSubObject", INI::parseAsciiStringVectorAppend, NULL, offsetof( TransitionDamageFXModuleData, m_damagedShow ) },
			{ "DamagedHideSubObject", INI::parseAsciiStringVectorAppend, NULL, offsetof( TransitionDamageFXModuleData, m_damagedHide ) },
			{ "ReallyDamagedShowSubObject", INI::parseAsciiStringVectorAppend, NULL, offsetof( TransitionDamageFXModuleData, m_reallyDamagedShow ) },
			{ "ReallyDamagedHideSubObject", INI::parseAsciiStringVectorAppend, NULL, offsetof( TransitionDamageFXModuleData, m_reallyDamagedHide ) },
			{ "RubbleShowSubObject", INI::parseAsciiStringVectorAppend, NULL, offsetof( TransitionDamageFXModuleData, m_rubbleShow ) },
			{ "RubbleHideSubObject", INI::parseAsciiStringVectorAppend, NULL, offsetof( TransitionDamageFXModuleData, m_rubbleHide ) },
			{ 0, 0, 0, 0 }
		};
		p.add(dataFieldParse);
	}

	Bfme2DamageMask m_damageFXTypes;
	Bfme2DamageFXEntry m_fxList[3][12];
	Bfme2DamageMask m_damageOCLTypes;
	Bfme2DamageFXEntry m_OCL[3][12];
	Bfme2DamageMask m_damageParticleTypes;
	Bfme2DamageFXEntry m_particleSystem[3][12];
	Bfme2SubObjectList m_pristineHide;
	Bfme2SubObjectList m_damagedHide;
	Bfme2SubObjectList m_reallyDamagedHide;
	Bfme2SubObjectList m_rubbleHide;
	Bfme2SubObjectList m_pristineShow;
	Bfme2SubObjectList m_damagedShow;
	Bfme2SubObjectList m_reallyDamagedShow;
	Bfme2SubObjectList m_rubbleShow;
	Bfme2SubObjectList m_rubbleNeighbors;
};

// collide includes
#include "GameLogic/Module/FireWeaponCollide.h"
#include "GameLogic/Module/SquishCollide.h"

#include "GameLogic/Module/ConvertToCarBombCrateCollide.h"
#include "GameLogic/Module/ConvertToHijackedVehicleCrateCollide.h"
#include "GameLogic/Module/HealCrateCollide.h"
#include "GameLogic/Module/MoneyCrateCollide.h"
#include "GameLogic/Module/SabotageCommandCenterCrateCollide.h"
#include "GameLogic/Module/SabotageFakeBuildingCrateCollide.h"
#include "GameLogic/Module/SabotageInternetCenterCrateCollide.h"
#include "GameLogic/Module/SabotageMilitaryFactoryCrateCollide.h"
#include "GameLogic/Module/SabotagePowerPlantCrateCollide.h"
#include "GameLogic/Module/SabotageSuperweaponCrateCollide.h"
#include "GameLogic/Module/SabotageSupplyCenterCrateCollide.h"
#include "GameLogic/Module/SabotageSupplyDropzoneCrateCollide.h"
#include "GameLogic/Module/ShroudCrateCollide.h"
#include "GameLogic/Module/VeterancyCrateCollide.h"

// BFME 2's crate data, from retail's field tables at 0x007EFAF4 and 0x007EFC28. Its base runs to
// +0x5C, past Zero Hour's; only these tables read the fields here.
class Bfme2CrateCollideModuleData : public CrateCollideModuleData
{
	char m_bfme2Fields[0x5C - sizeof(CrateCollideModuleData)];
};

class UnitCrateCollideModuleData : public Bfme2CrateCollideModuleData
{
public:
	UnsignedInt m_unitCount;
	AsciiString m_unitType;

	static void buildFieldParse(MultiIniFieldParse& p)
	{
		CrateCollideModuleData::buildFieldParse(p);

		static const FieldParse dataFieldParse[] =
		{
			{ "UnitCount",	INI::parseUnsignedInt,	NULL, offsetof( UnitCrateCollideModuleData, m_unitCount ) },
			{ "UnitName",		INI::parseAsciiString,	NULL, offsetof( UnitCrateCollideModuleData, m_unitType ) },
			{ 0, 0, 0, 0 }
		};
		p.add(dataFieldParse);
	}
};

class SalvageCrateCollideModuleData : public Bfme2CrateCollideModuleData
{
public:
	Real m_porterChance;
	Real m_bannerChance;
	Real m_levelUpChance;
	Real m_levelUpRadius;
	Real m_resourceChance;
	Int m_minResource;
	Int m_maxResource;
	AsciiString m_upgrade;
	Bool m_allowAIPickup;

	static void buildFieldParse(MultiIniFieldParse& p)
	{
		CrateCollideModuleData::buildFieldParse(p);

		static const FieldParse dataFieldParse[] =
		{
			{ "PorterChance",		INI::parsePercentToReal,	NULL, offsetof( SalvageCrateCollideModuleData, m_porterChance ) },
			{ "BannerChance",		INI::parsePercentToReal,	NULL, offsetof( SalvageCrateCollideModuleData, m_bannerChance ) },
			{ "LevelUpChance",	INI::parsePercentToReal,	NULL, offsetof( SalvageCrateCollideModuleData, m_levelUpChance ) },
			{ "LevelUpRadius",	INI::parsePercentToReal,	NULL, offsetof( SalvageCrateCollideModuleData, m_levelUpRadius ) },
			{ "ResourceChance",	INI::parsePercentToReal,	NULL, offsetof( SalvageCrateCollideModuleData, m_resourceChance ) },
			{ "Upgrade",				INI::parseAsciiString,		NULL, offsetof( SalvageCrateCollideModuleData, m_upgrade ) },
			{ "MinResource",		INI::parseInt,						NULL, offsetof( SalvageCrateCollideModuleData, m_minResource ) },
			{ "MaxResource",		INI::parseInt,						NULL, offsetof( SalvageCrateCollideModuleData, m_maxResource ) },
			{ "AllowAIPickup",	INI::parseBool,						NULL, offsetof( SalvageCrateCollideModuleData, m_allowAIPickup ) },
			{ 0, 0, 0, 0 }
		};
		p.add(dataFieldParse);
	}
};

// body includes
#include "GameLogic/Module/InactiveBody.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Module/HighlanderBody.h"
#include "GameLogic/Module/ImmortalBody.h"
#include "GameLogic/Module/StructureBody.h"
#include "GameLogic/Module/HiveStructureBody.h"
#include "GameLogic/Module/UndeadBody.h"

// contain includes
// (none)

// special power modules
#include "GameLogic/Module/CashHackSpecialPower.h"
#include "GameLogic/Module/DefectorSpecialPower.h"
#ifdef ALLOW_DEMORALIZE
#include "GameLogic/Module/DemoralizeSpecialPower.h"
#endif
#include "GameLogic/Module/OCLSpecialPower.h"
#include "GameLogic/Module/SpecialAbility.h"
#include "GameLogic/Module/SpyVisionSpecialPower.h"
#include "GameLogic/Module/CashBountyPower.h"
#include "GameLogic/Module/CleanupAreaPower.h"
#include "GameLogic/Module/FireWeaponPower.h"

// destroy includes
// (none)

// client update includes
#include "GameClient/Module/AnimatedParticleSysBoneClientUpdate.h"
#include "GameClient/Module/SwayClientUpdate.h"
#include "GameClient/Module/BeaconClientUpdate.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> void _STLP_alloc_proxy<char *, char, allocator<char> >::deallocate(char *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UAngleFXInfo@@@_STL@@QBEXPAUAngleFXInfo@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct AngleFXInfo;
namespace _STL { template <> void allocator<AngleFXInfo>::deallocate(AngleFXInfo *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?erase@?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@QAEPAUAngleFXInfo@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct AngleFXInfo;
namespace _STL { template <> AngleFXInfo * vector<AngleFXInfo,allocator<AngleFXInfo> >::erase(AngleFXInfo *,AngleFXInfo *); }
// Inline allocator cleanup without emitting an unused external copy.
namespace _STL {
template <> vector<AngleFXInfo, allocator<AngleFXInfo> >::~vector();
template <> __declspec(dllimport) __forceinline
void allocator<AngleFXInfo>::deallocate(AngleFXInfo *p, size_t count) const
{ if (p != 0) __sgi_alloc::deallocate((void *)p, count * sizeof(value_type)); }
// Clearing destroys the elements and retains the allocated storage.
template <> __declspec(dllimport) __forceinline
void vector<AngleFXInfo, allocator<AngleFXInfo> >::clear()
{
    _Destroy(this->_M_start, this->_M_finish);
    this->_M_finish = this->_M_start;
}
}
// Suppress this TU's non-retail copy of ??$max@I@_STL@@YAABIABI0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &); }

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
template <> FXBoneInfo *vector<FXBoneInfo, allocator<FXBoneInfo> >::erase(FXBoneInfo *, FXBoneInfo *);
}

// The no-hint insertion is owned by stlport_modulefactory_map_insert_unique.cpp.
struct ModuleFactoryInsertAccess : ModuleFactory {
    typedef ModuleTemplate Value;
};
typedef _STL::pair<const NameKeyType, ModuleFactoryInsertAccess::Value> ModuleFactoryInsertValue;
typedef _STL::_Rb_tree<NameKeyType, ModuleFactoryInsertValue, _STL::_Select1st<ModuleFactoryInsertValue>, _STL::less<NameKeyType>, _STL::allocator<ModuleFactoryInsertValue> > ModuleFactoryInsertTree;
template <> _STL::pair<ModuleFactoryInsertTree::iterator, bool>
ModuleFactoryInsertTree::insert_unique(const ModuleFactoryInsertValue &);

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
ModuleFactory *TheModuleFactory = NULL;  ///< the module factory singleton

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?ModuleFactory::ModuleFactory present-unmatched
ModuleFactory::ModuleFactory( void )
{
	m_moduleTemplateMap.clear();
	m_moduleDataList.clear();
	
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?ModuleFactory::~ModuleFactory present-unmatched
ModuleFactory::~ModuleFactory( void )
{
	m_moduleTemplateMap.clear();

	for (ModuleDataList::iterator i = m_moduleDataList.begin(); i != m_moduleDataList.end(); ++i)
	{
		const ModuleData* data = *i;
		delete data;
	}
	m_moduleDataList.clear();

}

//-------------------------------------------------------------------------------------------------
/** Initialize the module factory.  Any class that needs to be attached
	* to objects or drawables as modules needs to add a template
	* for that class here */
//-------------------------------------------------------------------------------------------------
// The retail initializer is in ModuleFactoryInit.cpp. These reference headers
// also own matched inline bodies (factories, ModuleData constructors and
// destructors, buildFieldParse) which disappear if no TU takes the factory
// addresses. Take only the factories whose inline bodies reach this unit's
// rows: taking every factory emitted Zero Hour inline copies proven not
// retail's ahead of their owners in link order, which held those owners'
// units out of the link. UpgradeModule's data factory is the one its
// subclasses inherit. The CreateCrateDie, CrushDie and crate-collide data
// factories also emitted this view's ModuleData constructors, proven not
// retail's ahead of their owners; only the field parsers whose rows live here
// are taken. CaveContain's data factory emitted its ModuleData constructor and
// the Zero Hour OpenContainModuleData destructor, neither retail's, ahead of
// their owners; its deleting dtor and dtor rows live in
// ContainModuleDeletingDtors.cpp and CaveContainModuleDataFriendNew.cpp. The
// SpawnBehavior and StructureBody data factories did the same (their ctor and
// dtor copies, and StructureBody's ActiveBodyModuleData dtor); their deleting
// dtors are emitted by FamilyDeletingDtors.cpp. UpgradeModule and
// TransitionDamageFX contribute only their field parsers, and
// StructureCollapseUpdate nothing: no row here needs its data factory, which
// emitted a non-retail dtor copy. This compiler anchor is not a recovered
// retail function.
#define BFME_EMIT_MODULE_INSTANCE(cls) *instances++ = &cls::friend_newModuleInstance
#define BFME_EMIT_MODULE_DATA(cls) *data++ = &cls::friend_newModuleData
// ?bfmeEmitModuleFactoryInlines absent-from-retail
void bfmeEmitModuleFactoryInlines(NewModuleProc *instances, NewModuleDataProc *data,
	BuildMultiIniFieldProc *parsers)
{
	BFME_EMIT_MODULE_INSTANCE( BridgeTowerBehavior );
	BFME_EMIT_MODULE_INSTANCE( InstantDeathBehavior );
	BFME_EMIT_MODULE_INSTANCE( DestroyDie );
	BFME_EMIT_MODULE_INSTANCE( CrushDie );
	BFME_EMIT_MODULE_INSTANCE( CreateCrateDie );
	*parsers++ = &CreateCrateDieModuleData::buildFieldParse;
	BFME_EMIT_MODULE_INSTANCE( CreateObjectDie );
	BFME_EMIT_MODULE_INSTANCE( SpecialPowerCompletionDie );
	BFME_EMIT_MODULE_INSTANCE( RebuildHoleExposeDie );
	BFME_EMIT_MODULE_INSTANCE( KeepObjectDie );
	BFME_EMIT_MODULE_INSTANCE( StealthDetectorUpdate );
	BFME_EMIT_MODULE_INSTANCE( LaserUpdate );
	BFME_EMIT_MODULE_INSTANCE( OCLUpdate );
	BFME_EMIT_MODULE_DATA( StructureToppleUpdate );
	// GrantScienceUpgrade's data factory would call a buildFieldParse no unit
	// defines; a local object emits the same vftable, ??_G and ??1 rows.
	{ GrantScienceUpgradeModuleData grantScienceUpgradeData; }
	BFME_EMIT_MODULE_INSTANCE( LockWeaponCreate );
	BFME_EMIT_MODULE_INSTANCE( PreorderCreate );
	BFME_EMIT_MODULE_INSTANCE( SupplyWarehouseCreate );
	BFME_EMIT_MODULE_INSTANCE( SpecialPowerCreate );
	BFME_EMIT_MODULE_INSTANCE( GrantUpgradeCreate );
	*parsers++ = &TransitionDamageFXModuleData::buildFieldParse;
	BFME_EMIT_MODULE_INSTANCE( FireWeaponCollide );
	BFME_EMIT_MODULE_INSTANCE( SquishCollide );
	*parsers++ = &UnitCrateCollideModuleData::buildFieldParse;
	*parsers++ = &SalvageCrateCollideModuleData::buildFieldParse;
	BFME_EMIT_MODULE_INSTANCE( InactiveBody );
	BFME_EMIT_MODULE_INSTANCE( AnimatedParticleSysBoneClientUpdate );
	BFME_EMIT_MODULE_INSTANCE( BeaconClientUpdate );
}
#undef BFME_EMIT_MODULE_INSTANCE
#undef BFME_EMIT_MODULE_DATA


//-------------------------------------------------------------------------------------------------
ModuleData* ModuleFactory::newModuleDataFromINI(INI* ini, const AsciiString& name, ModuleType type,
																								const AsciiString& moduleTag)
{
	if (name.isEmpty())
		return NULL;

	const ModuleTemplate* moduleTemplate = findModuleTemplate(name, type);
	if (moduleTemplate)
	{
		ModuleData* md = (*moduleTemplate->m_createDataProc)(ini);
		md->setModuleTagNameKey( NAMEKEY( moduleTag ) );
		m_moduleDataList.push_back(md);
		return md;
	}

	return NULL;
}

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/*static*/ NameKeyType ModuleFactory::makeDecoratedNameKey(const AsciiString& name, ModuleType type)
{
	char tmp[256];
	tmp[0] = '0' + (int)type;
	_mbscpy(reinterpret_cast<unsigned char *>(&tmp[1]), reinterpret_cast<const unsigned char *>(name.str()));
	return TheNameKeyGenerator->nameToKey(tmp);
}

//-------------------------------------------------------------------------------------------------
const ModuleFactory::ModuleTemplate* ModuleFactory::findModuleTemplate(const AsciiString& name, ModuleType type)
{
	NameKeyType namekey = makeDecoratedNameKey(name, type);

  ModuleTemplateMap::const_iterator it = m_moduleTemplateMap.find(namekey);
  if (it == m_moduleTemplateMap.end()) 
	{
		DEBUG_CRASH(( "Module name '%s' not found\n", name.str() ));
		return NULL;
	}
	else
	{
		return &(*it).second;
	}
}

//-------------------------------------------------------------------------------------------------
/** Allocate a new acton class istance given the name */
//-------------------------------------------------------------------------------------------------
Module *ModuleFactory::newModule( Thing *thing, const AsciiString& name, const ModuleData* moduleData, ModuleType type )
{
	// sanity
	if( name.isEmpty() )
	{
		DEBUG_CRASH(("attempting to create module with empty name\n"));
		return NULL;
	}
	const ModuleTemplate* mt = findModuleTemplate(name, type);
	if (mt)
	{
		Module* mod = (*mt->m_createProc)( thing, moduleData );

#ifdef _DEBUG
		if (type == MODULETYPE_BEHAVIOR)
		{
			BehaviorModule* bm = (BehaviorModule*)mod;

			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_BODY)) != 0) == (bm->getBody() != NULL), 
				("getInterfaceMask bad for MODULE_BODY (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_COLLIDE)) != 0) == (bm->getCollide() != NULL), 
				("getInterfaceMask bad for MODULE_COLLIDE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_CONTAIN)) != 0) == (bm->getContain() != NULL), 
				("getInterfaceMask bad for MODULE_CONTAIN (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_CREATE)) != 0) == (bm->getCreate() != NULL), 
				("getInterfaceMask bad for MODULE_CREATE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_DAMAGE)) != 0) == (bm->getDamage() != NULL), 
				("getInterfaceMask bad for MODULE_DAMAGE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_DESTROY)) != 0) == (bm->getDestroy() != NULL), 
				("getInterfaceMask bad for MODULE_DESTROY (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_DIE)) != 0) == (bm->getDie() != NULL), 
				("getInterfaceMask bad for MODULE_DIE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_SPECIAL_POWER)) != 0) == (bm->getSpecialPower() != NULL), 
				("getInterfaceMask bad for MODULE_SPECIAL_POWER (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_UPDATE)) != 0) == (bm->getUpdate() != NULL), 
				("getInterfaceMask bad for MODULE_UPDATE (%s)\n",name.str()));
			DEBUG_ASSERTCRASH(
				((mt->m_whichInterfaces & (MODULEINTERFACE_UPGRADE)) != 0) == (bm->getUpgrade() != NULL), 
				("getInterfaceMask bad for MODULE_UPGRADE (%s)\n",name.str()));
		}
#endif

		return mod;
	}

	return NULL;

}  // end newModule

//-------------------------------------------------------------------------------------------------
/** Add a module template to our list of templates */
//-------------------------------------------------------------------------------------------------
// ?ModuleFactory::addModuleInternal present-unmatched
void ModuleFactory::addModuleInternal( NewModuleProc proc, NewModuleDataProc dataproc, ModuleType type, const AsciiString& name, Int whichIntf )
{
	NameKeyType namekey = makeDecoratedNameKey(name, type);
	ModuleTemplate& mtm = m_moduleTemplateMap[namekey];	// this creates it if it does not exist already
	mtm.m_createProc = proc;
	mtm.m_createDataProc = dataproc;
	mtm.m_whichInterfaces = whichIntf;
}

//-------------------------------------------------------------------------------------------------
// ?ModuleFactory::crc present-unmatched
void ModuleFactory::crc( Xfer *xfer )
{
	for (ModuleDataList::iterator mdIt = m_moduleDataList.begin(); mdIt != m_moduleDataList.end(); ++mdIt)
	{
		((ModuleData *)(*mdIt))->crc(xfer);
	}
}

//-------------------------------------------------------------------------------------------------
// ?ModuleFactory::xfer present-unmatched
void ModuleFactory::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	for (ModuleDataList::iterator mdIt = m_moduleDataList.begin(); mdIt != m_moduleDataList.end(); ++mdIt)
	{
		((ModuleData *)(*mdIt))->xfer(xfer);
	}
}

//-------------------------------------------------------------------------------------------------
// ?ModuleFactory::loadPostProcess present-unmatched
void ModuleFactory::loadPostProcess( void )
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?push_back@?$vector@UHordeBannerSlot@@V?$allocator@UHordeBannerSlot@@@_STL@@@_STL@@QAEXABUHordeBannerSlot@@@Z=?push_back@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@QAEXABQBVModuleData@@@Z")
#pragma comment(linker, "/alternatename:?push_back@GateOpenBehaviorList@@QAEXABQAX@Z=?push_back@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@QAEXABQBVModuleData@@@Z")

// Keep this unit's independently rowed FXBoneInfo assignment when the
// vector erase is supplied by its retail owner instead of this header copy.
template FXBoneInfo *_STL::__copy<FXBoneInfo *, FXBoneInfo *, int>(FXBoneInfo *, FXBoneInfo *, FXBoneInfo *, const _STL::random_access_iterator_tag &, int *);

// This unit must keep the rowed ??_GAutoDepositUpdateModuleData (0x0025528B) and
// ??_GStructureToppleUpdateModuleData (0x00257B5E) deleting destructors (and the
// ??0?$list@UupgradePair / FXBoneInfo clear side rows) without emitting its own
// non-retail ??0/??1 module-data COMDATs, which would win link order ahead of
// retail's byte-owned copies (AutoDepositUpdateModuleDataCtor/Dtor.cpp,
// StructureToppleUpdateModuleDataCtor/Dtor.cpp). The tag constructors below
// emit the vftables and the deleting destructors; the default constructors and
// destructors stay declared only (the pattern of
// Code/GameEngine/Source/Common/FamilyDeletingDtors_muse-4f8a.cpp). The bodies
// mirror the headers' inline default constructors so their side emissions stay.
// ?<AutoDepositUpdateModuleData::AutoDepositUpdateModuleData> absent-from-retail
AutoDepositUpdateModuleData::AutoDepositUpdateModuleData( EmitVtableTag * )
{
	m_depositFrame = 0;
	m_depositAmount = 0;
	m_initialCaptureBonus = 0;
	m_isActualMoney = TRUE;
	m_upgradeBoost.clear();
}

// ?<StructureToppleUpdateModuleData::StructureToppleUpdateModuleData> absent-from-retail
StructureToppleUpdateModuleData::StructureToppleUpdateModuleData( EmitVtableTag * )
{
	m_minToppleDelay = 0;
	m_maxToppleDelay = 0;
	m_minToppleBurstDelay = 0;
	m_maxToppleBurstDelay = 0;
	m_structuralIntegrity = 0.1f;
	m_structuralDecay = 0.0f;
	m_damageFXTypes.clear();
	m_damageFXTypes.flip();
	m_toppleStartFXList = NULL;
	m_toppleDelayFXList = NULL;
	m_toppleDoneFXList = NULL;
	m_toppleFXList = NULL;
	m_crushingFXList = NULL;
	m_crushingWeaponName.set("");
	for (int i = 0; i < ST_PHASE_COUNT; ++i)
	{
		// init to one, so that if these are omitted, we choose exactly one of each.
		m_oclCount[i] = 1;
	}
	fxbones.clear();
	angleFX.clear();
}
