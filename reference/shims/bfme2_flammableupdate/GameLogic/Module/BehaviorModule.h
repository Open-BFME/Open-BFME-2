// Verbatim copy of reference/shims/update_modules_bfme2/GameLogic/Module/BehaviorModule.h for the FlammableUpdate TU (changes marked "BFME 2:").
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

// FILE: BehaviorModule.h /////////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson
// Desc:	 
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// BFME shim (TU-scoped, reference/shims/zh_outofline): Zero Hour's GameLogic/Module/BehaviorModule.h, verbatim except
// that the definitions marked OUT OF LINE below are declarations only. Retail has one body
// for each (its ledger owner); this header's inline copies use Zero Hour's layout, so every
// unit that emitted one offered the link a second, non-retail body.

#ifndef __BehaviorModule_H_
#define __BehaviorModule_H_

#include "Common/GameType.h"
#include "Common/Module.h"

//-------------------------------------------------------------------------------------------------
class Team;
class ThingTemplate;

//-------------------------------------------------------------------------------------------------
class BodyModuleInterface;
class CollideModuleInterface;
class ContainModuleInterface;
class CreateModuleInterface;
class DamageModuleInterface;
class DestroyModuleInterface;
class DieModuleInterface;
class SpecialPowerModuleInterface;
class UpdateModuleInterface;
class UpgradeModuleInterface;

//-------------------------------------------------------------------------------------------------
class ParkingPlaceBehaviorInterface;
class RebuildHoleBehaviorInterface;
class BridgeBehaviorInterface;
class BridgeTowerBehaviorInterface;
class BridgeScaffoldBehaviorInterface;
class OverchargeBehaviorInterface;
class TransportPassengerInterface;
class CaveInterface;
class LandMineInterface;

class ProjectileUpdateInterface;
class AIUpdateInterface;
class ExitInterface;
class DockUpdateInterface;
class RailedTransportDockUpdateInterface;
class SpecialPowerUpdateInterface;
class SlavedUpdateInterface;
class SpawnBehaviorInterface;
class CountermeasuresBehaviorInterface;
class SlowDeathBehaviorInterface;
class PowerPlantUpdateInterface;
class ProductionUpdateInterface;
class HordeUpdateInterface;
class SpecialPowerTemplate;
class WeaponTemplate;
class DamageInfo;
class ParticleSystemTemplate;
class StealthUpdate;
class SpyVisionUpdate;


//-------------------------------------------------------------------------------------------------
class BehaviorModuleData : public ModuleData
{
public:
	BehaviorModuleData()
	{
	}

	static void buildFieldParse(MultiIniFieldParse& p) 
	{
    ModuleData::buildFieldParse(p);
	}
};

//-------------------------------------------------------------------------------------------------
class BehaviorModuleInterface
{
public:

	// BFME 2: the 47 slots of the registered interface (Code/GameEngine/Include/GameLogic/Module/
	// BehaviorModule.h; retail 0x00BEE900), names and signatures as it spells them. Zero Hour's
	// 34-slot order put getDie, getSpecialPower, getUpdate and getUpgrade one slot early.
	virtual BodyModuleInterface *getBody() = 0;			// 0
	virtual CollideModuleInterface *getCollide() = 0;			// 1
	virtual ContainModuleInterface *getContain() = 0;			// 2
	virtual CreateModuleInterface *getCreate() = 0;			// 3
	virtual DamageModuleInterface *getDamage() = 0;			// 4
	virtual void *slot05() = 0;			// 5
	virtual void *slot06() = 0;			// 6
	virtual DieModuleInterface *getDie() = 0;			// 7
	virtual SpecialPowerModuleInterface *getSpecialPower() = 0;			// 8
	virtual UpdateModuleInterface *getUpdate() = 0;			// 9
	virtual UpgradeModuleInterface *getUpgrade() = 0;			// 10
	virtual void *slot11() = 0;			// 11
	virtual void *slot12() = 0;			// 12
	virtual void *slot13() = 0;			// 13
	virtual void *slot14() = 0;			// 14
	virtual void *slot15() = 0;			// 15
	virtual void *slot16() = 0;			// 16
	virtual void *slot17() = 0;			// 17
	virtual void *slot18() = 0;			// 18
	virtual AIUpdateInterface *getAIUpdateInterface() = 0;			// 19
	virtual void *slot20() = 0;			// 20
	virtual void *slot21() = 0;			// 21
	virtual void *slot22() = 0;			// 22
	virtual void *slot23() = 0;			// 23
	virtual void *slot24() = 0;			// 24
	virtual void *slot25() = 0;			// 25
	virtual void *slot26() = 0;			// 26
	virtual void *slot27() = 0;			// 27
	virtual void *slot28() = 0;			// 28
	virtual void *slot29() = 0;			// 29
	virtual void *slot30() = 0;			// 30
	virtual void *slot31() = 0;			// 31
	virtual void *slot32() = 0;			// 32
	virtual void *slot33() = 0;			// 33
	virtual void *slot34() = 0;			// 34
	virtual void *slot35() = 0;			// 35
	virtual void *slot36() = 0;			// 36
	virtual void *slot37() = 0;			// 37
	virtual void *slot38() = 0;			// 38
	virtual void *slot39() = 0;			// 39
	virtual void *slot40() = 0;			// 40
	virtual void *slot41() = 0;			// 41
	virtual void *slot42() = 0;			// 42
	virtual void slot43(int) = 0;			// 43
	virtual void slot44() = 0;			// 44
	virtual void slot45(int) = 0;			// 45
	virtual void slot46(int) = 0;			// 46

};

//-------------------------------------------------------------------------------------------------
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{

	MEMORY_POOL_GLUE_ABC( BehaviorModule )

public:

	BehaviorModule( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype defined by MemoryPoolObject

	static Int getInterfaceMask() { return 0; }
	static ModuleType getModuleType() { return MODULETYPE_BEHAVIOR; }

	// BFME 2: the defaults of the registered interface (Code/GameEngine/Include/GameLogic/Module/
	// BehaviorModule.h; retail 0x00BEE900), names and signatures as it spells them. Zero Hour's
	// 34-slot order put getDie, getSpecialPower, getUpdate and getUpgrade one slot early.
	virtual BodyModuleInterface *getBody() { return NULL; }			// 0
	virtual CollideModuleInterface *getCollide() { return NULL; }			// 1
	virtual ContainModuleInterface *getContain() { return NULL; }			// 2
	virtual CreateModuleInterface *getCreate() { return NULL; }			// 3
	virtual DamageModuleInterface *getDamage() { return NULL; }			// 4
	virtual void *slot05() { return NULL; }			// 5
	virtual void *slot06() { return NULL; }			// 6
	virtual DieModuleInterface *getDie() { return NULL; }			// 7
	virtual SpecialPowerModuleInterface *getSpecialPower() { return NULL; }			// 8
	virtual UpdateModuleInterface *getUpdate() { return NULL; }			// 9
	virtual UpgradeModuleInterface *getUpgrade() { return NULL; }			// 10
	virtual void *slot11() { return NULL; }			// 11
	virtual void *slot12() { return NULL; }			// 12
	virtual void *slot13() { return NULL; }			// 13
	virtual void *slot14() { return NULL; }			// 14
	virtual void *slot15() { return NULL; }			// 15
	virtual void *slot16() { return NULL; }			// 16
	virtual void *slot17() { return NULL; }			// 17
	virtual void *slot18() { return NULL; }			// 18
	virtual AIUpdateInterface *getAIUpdateInterface() { return NULL; }			// 19
	virtual void *slot20() { return NULL; }			// 20
	virtual void *slot21() { return NULL; }			// 21
	virtual void *slot22() { return NULL; }			// 22
	virtual void *slot23() { return NULL; }			// 23
	virtual void *slot24() { return NULL; }			// 24
	virtual void *slot25() { return NULL; }			// 25
	virtual void *slot26() { return NULL; }			// 26
	virtual void *slot27() { return NULL; }			// 27
	virtual void *slot28() { return NULL; }			// 28
	virtual void *slot29() { return NULL; }			// 29
	virtual void *slot30() { return NULL; }			// 30
	virtual void *slot31() { return NULL; }			// 31
	virtual void *slot32() { return NULL; }			// 32
	virtual void *slot33() { return NULL; }			// 33
	virtual void *slot34() { return NULL; }			// 34
	virtual void *slot35() { return NULL; }			// 35
	virtual void *slot36() { return NULL; }			// 36
	virtual void *slot37() { return NULL; }			// 37
	virtual void *slot38() { return NULL; }			// 38
	virtual void *slot39() { return NULL; }			// 39
	virtual void *slot40() { return NULL; }			// 40
	virtual void *slot41() { return NULL; }			// 41
	virtual void *slot42() { return NULL; }			// 42
	virtual void slot43(int) { }			// 43
	virtual void slot44() { }			// 44
	virtual void slot45(int) { }			// 45
	virtual void slot46(int) { }			// 46

  virtual StealthUpdate* getStealth() { return NULL; }
	virtual SpyVisionUpdate* getSpyVisionUpdate() { return NULL; }

protected:

	// snapshot methods
	virtual const char *GetSnapshotName() const;
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

};
// OUT OF LINE: BehaviorModule::BehaviorModule (retail 0x00253330, CreateModule.cpp)
inline BehaviorModule::~BehaviorModule() { }


enum RunwayReservationType
{
	RESERVATION_TAKEOFF,
	RESERVATION_LANDING,
};

//-------------------------------------------------------------------------------------------------
class ParkingPlaceBehaviorInterface
{
public:
	struct PPInfo
	{
		Coord3D		parkingSpace; 
		Real			parkingOrientation;
		Coord3D		runwayPrep; 
		Coord3D		runwayStart;
		Coord3D		runwayEnd;
		Coord3D		runwayExit;
		Coord3D	  runwayLandingStart;
		Coord3D	  runwayLandingEnd;
		Coord3D		runwayApproach;
		Coord3D		hangarInternal;
		Real			runwayTakeoffDist;
		Real			hangarInternalOrient;
	};
	virtual Bool shouldReserveDoorWhenQueued(const ThingTemplate* thing) const = 0; 
	virtual Bool hasAvailableSpaceFor(const ThingTemplate* thing) const = 0; 
	virtual Bool hasReservedSpace(ObjectID id) const = 0; 
	virtual Int  getSpaceIndex( ObjectID id ) const = 0;
	virtual Bool reserveSpace(ObjectID id, Real parkingOffset, PPInfo* info) = 0;
	virtual void releaseSpace(ObjectID id) = 0; 
	virtual Bool reserveRunway(ObjectID id, Bool forLanding) = 0;
	virtual void calcPPInfo( ObjectID id, PPInfo *info ) = 0;
	virtual void releaseRunway(ObjectID id) = 0; 
	virtual Int getRunwayCount() const = 0;
	virtual ObjectID getRunwayReservation( Int r, RunwayReservationType type = RESERVATION_TAKEOFF ) = 0;
	virtual void transferRunwayReservationToNextInLineForTakeoff(ObjectID id) = 0;
	virtual Real getApproachHeight() const = 0;
	virtual Real getLandingDeckHeightOffset() const = 0;
	virtual void setHealee(Object* healee, Bool add) = 0;
	virtual void killAllParkedUnits() = 0;
	virtual void defectAllParkedUnits(Team* newTeam, UnsignedInt detectionTime) = 0;
	virtual Bool calcBestParkingAssignment( ObjectID id, Coord3D *pos, Int *oldIndex = NULL, Int *newIndex = NULL ) = 0;

	virtual const std::vector<Coord3D>* getTaxiLocations( ObjectID id ) const = 0;
	virtual const std::vector<Coord3D>* getCreationLocations( ObjectID id ) const = 0;
};

//-------------------------------------------------------------------------------------------------
class TransportPassengerInterface
{
public:
	virtual Bool tryToEvacuate( Bool exposeStealthedUnits ) = 0; ///< Will try to kick everybody out with game checks, and will return whether anyone made it
};

//-------------------------------------------------------------------------------------------------
class CaveInterface
{
public:
	virtual void tryToSetCaveIndex( Int newIndex ) = 0;	///< Called by script as an alternative to instancing separate objects.  'Try', because can fail.
	virtual void setOriginalTeam( Team *oldTeam ) = 0;	///< This is a distributed Garrison in terms of capturing, so when one node triggers the change, he needs to tell everyone, so anyone can do the un-change.
};

//-------------------------------------------------------------------------------------------------
class LandMineInterface
{
public:
	virtual void setScootParms(const Coord3D& start, const Coord3D& end) = 0;
	virtual void disarm() = 0;
};

//-------------------------------------------------------------------------------------------------

#endif
