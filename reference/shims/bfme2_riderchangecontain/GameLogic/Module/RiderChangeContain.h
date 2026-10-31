// Copied from reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RiderChangeContain.h; each change is marked "// BFME 2:".
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

// FILE: RiderChangeContain.cpp //////////////////////////////////////////////////////////////////////
// Author: Kris Morness, May 2003
// Desc:   Contain module for the combat bike (transport that switches units).
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __RIDER_CHANGE_CONTAIN_H
#define __RIDER_CHANGE_CONTAIN_H

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "GameLogic/Module/TransportContain.h"

#define MAX_RIDERS 8 //***NOTE: If you change this, make sure you update the parsing section!

enum WeaponSetType;
enum ObjectStatusType;
enum LocomotorSetType;

struct RiderInfo
{
	// BFME 2: out of line, rows ??0RiderInfo@@QAE@XZ 0x0047E3A2 and ??1RiderInfo@@QAE@XZ 0x0047E3AC.
	RiderInfo();
	~RiderInfo();
	AsciiString m_templateName;
	WeaponSetType m_weaponSetFlag;
	ModelConditionFlagType m_modelConditionFlagType; 
	ObjectStatusType m_objectStatusType;
	AsciiString m_commandSet;
	LocomotorSetType m_locomotorSetType;
};

//-------------------------------------------------------------------------------------------------
// BFME 2: the base is SiegeEngineContainModuleData (ctor 0x0047EABC calls 0x0047C927, buildFieldParse
// 0x0047E477 chains 0x0047B9F5) and ends at +0x1B8, where parse table 0xDC9CA0 puts Rider1.
class SiegeEngineContainModuleData
{
public:
	SiegeEngineContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	virtual ~SiegeEngineContainModuleData();
	char m_pad04[0x98 - 0x04];
	// BFME 2: +0x98, read by getContainMax 0x0047E4EE.
	Int m_slotCapacity;
	char m_pad9C[0x1B8 - 0x9C];
};

//-------------------------------------------------------------------------------------------------
class RiderChangeContainModuleData : public SiegeEngineContainModuleData
{
public:
	
	RiderInfo m_riders[ MAX_RIDERS ];
	UnsignedInt m_scuttleFrames;
	ModelConditionFlagType m_scuttleState;
	// BFME 2: +0x280, "KillRiderWhenVehicleDies" in parse table 0xDC9CA0; size 0x284 per factory 0x0024BD63.
	Bool m_killRiderWhenVehicleDies;

	RiderChangeContainModuleData();
	// BFME 2: out of line, row ??1RiderChangeContainModuleData@@UAE@XZ 0x0047EB36.
	virtual ~RiderChangeContainModuleData();

	static void buildFieldParse(MultiIniFieldParse& p);
	static void parseRiderInfo( INI* ini, void *instance, void *store, const void* /*userData*/ );

};

//-------------------------------------------------------------------------------------------------
// BFME 2: the base is SiegeEngineContain (ctor 0x0047E268 calls 0x0047C21E; xfer 0x0047E357 chains
// 0x0047C322, its slot 3), 0x138 bytes per friend_new 0x0024BBB4.
class RiderChangeContainPrimary
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	const RiderChangeContainModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[ 0x20 - 0x0C ];
};

// BFME 2: the contain interface at +0x20, table 0x00847834: isValidContainerFor 0x0047E520 is slot 38,
// onContaining 0x0047E5D4 slot 39, onRemoving 0x0047E7CF slot 40; slots 27 and 28 hold 0x0047EA58 and
// 0x0047E4EE, and 0x0047EA58 calls through slots 41 and 71, 0x0047EA26 through slot 69.
class Rva0036AE51ListView;
class Rva0047BA69
{
public:
	bool rva0047BA69(Object *obj, int a2, int a3); // the base check, rowed under this address name
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual Object *rva0047EA58();
	virtual Int getContainMax( void ) const;
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual Bool isValidContainerFor( Object *obj, Bool checkCapacity, Bool testPath );
	virtual void onContaining( Object *obj, Bool wasSelected );
	virtual void onRemoving( Object *obj );
	virtual void removeFromContain( Object *obj, Bool exposeStealthUnits );
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual UnsignedInt getContainCount( Int ) const;
	virtual void slot70();
	virtual Rva0036AE51ListView getContainedItemsList();
	virtual const Object *friend_getRider() const;
};

class SiegeEngineContain : public RiderChangeContainPrimary, public Rva0047BA69
{
public:
	SiegeEngineContain(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void xfer( Xfer *xfer );
	char m_unrecovered24[ 0x138 - 0x24 ]; // +0x24
};

//-------------------------------------------------------------------------------------------------
class RiderChangeContain : public SiegeEngineContain
{

	// BFME 2: getModuleNameKey is its own row (0x0047E2E0), the destructor is ??1RiderChangeContain@@UAE@XZ
	// 0x0047E51B, and friend_new 0x0024BD28 and the module data factory 0x0024BD63 are rowed apart.
public:
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

public:

	RiderChangeContain( Thing *thing, const ModuleData* moduleData );
	virtual ~RiderChangeContain();

	// BFME 2: row ?isValidContainerFor@RiderChangeContain@@UAE_NPAVObject@@_N1@Z 0x0047E520.
	virtual Bool isValidContainerFor( Object *obj, Bool checkCapacity, Bool testPath );
	// BFME 2: row ?rva0047EA58@RiderChangeContain@@UAEPAVObject@@XZ 0x0047EA58.
	virtual Object *rva0047EA58();

	virtual void onCapture( Player *oldOwner, Player *newOwner ); // have to kick everyone out on capture.
	virtual void onContaining( Object *obj, Bool wasSelected );		///< object now contains 'obj'
	virtual void onRemoving( Object *obj );			///< object no longer contains 'obj'
	virtual UpdateSleepTime update();							///< called once per frame

	virtual Bool isRiderChangeContain() const { return TRUE; }
	virtual const Object *friend_getRider() const; 

	virtual Int getContainMax( void ) const;

	virtual Int getExtraSlotsInUse( void ) { return m_extraSlotsInUse; }///< Transports have the ability to carry guys how take up more than spot.

	virtual Bool isExitBusy() const;	///< Contain style exiters are getting the ability to space out exits, so ask this before reserveDoor as a kind of no-commitment check.
	virtual ExitDoorType reserveDoorForExit( const ThingTemplate* objType, Object *specificObject );
	virtual void unreserveDoorForExit( ExitDoorType exitDoor );
	virtual Bool isDisplayedOnControlBar() const {return TRUE;}///< Does this container display its contents on the ControlBar?

	virtual Bool getContainerPipsToShow( Int& numTotal, Int& numFull );

protected:

	// exists primarily for RiderChangeContain to override
	virtual void killRidersWhoAreNotFreeToExit();
	virtual Bool isSpecificRiderFreeToExit(Object* obj);
	virtual void createPayload();
	
private:

	Int m_extraSlotsInUse;
	UnsignedInt m_frameExitNotBusy;
	UnsignedInt m_scuttledOnFrame;

	Bool m_containing; //doesn't require xfer.

};

#endif // __RIDER_CHANGE_CONTAIN_H

