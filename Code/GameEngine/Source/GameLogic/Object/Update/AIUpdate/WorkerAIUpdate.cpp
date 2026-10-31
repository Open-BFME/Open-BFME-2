// cl: /Ireference/shims/bfme2_workeraiupdate /Ireference/shims/aiupdatelayout /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate.cpp); this unit had no counterpart under Code/.
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

// FILE: WorkerAIUpdate.cpp ///////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, June 2002
// Desc:   A Worker is a unit that is both a Dozer and a Supply Truck.
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/Team.h"
#include "Common/StateMachine.h"
#include "Common/BuildAssistant.h"
#include "Common/GameState.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Player.h"
#include "Common/Money.h"
#include "Common/Radar.h"
#include "Common/RandomValue.h"
#include "Common/GlobalData.h"
#include "Common/ResourceGatheringManager.h"
#include "Common/Upgrade.h"

#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"
#include "GameClient/InGameUI.h"

#include "GameLogic/AIPathfind.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"
#include "GameLogic/Module/CreateModule.h"
#include "GameLogic/Module/SupplyTruckAIUpdate.h"
#include "GameLogic/Module/SupplyCenterDockUpdate.h"
#include "GameLogic/Module/SupplyWarehouseDockUpdate.h"
#include "GameLogic/Module/WorkerAIUpdate.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned long _Base_bitset<4>::_S_maskbit(unsigned int); }
// bfme link decl-only end


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


// FORWARD DECLARATIONS ///////////////////////////////////////////////////////////////////////////
enum
{
	AS_DOZER,				///< When not actively Gathering, or when actively building, I am a dozer
	AS_SUPPLY_TRUCK	///< When told explicitly by player or other object, I become a supply truck
};


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_ctor_Thunk.cpp
// WorkerAIUpdate::WorkerAIUpdate is rowed in WorkerAIUpdateCtor.cpp; the Zero Hour copy here
// was a non-retail second definition. Two header-inline virtuals rowed here were emitted
// only through its vtable; direct calls keep them emitted.
// ?bfmeAnchorWorkerAIUpdateInlineRows absent-from-retail
void bfmeAnchorWorkerAIUpdateInlineRows(WorkerAIUpdate *worker, DozerBuildSubTask task, Bool on)
{
	worker->WorkerAIUpdate::setBuildSubTask(task);
	worker->WorkerAIUpdate::setForceWantingState(on);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// WorkerAIUpdate's destructor is rowed with BFME2's body in WorkerAIUpdateDtor.cpp;
// the Zero Hour copy here was a second definition.

//-------------------------------------------------------------------------------------------------
// One instruction away, and the instruction is the class. With the three offsets
// below corrected by views -- the supply machine at WorkerAIUpdate+0xE0 against
// the vendored +0xCC, its current state at StateMachine+0x1C against +0x20, and
// the state's id at State+0x04 against +0x08 -- the whole body matches except the
// very first read: retail is `mov eax,[ecx+0xe0]` and this tree emits
// `mov eax,[ecx-0x124]`. That is -0x204 + 0xE0: MSVC enters this override with
// the SupplyTruckAIInterface sub-object, which the vendored
// `WorkerAIUpdate : AIUpdateInterface, DozerAIInterface, SupplyTruckAIInterface,
// WorkerAIInterface` puts at +0x204, and folds the adjustment into the
// displacement. Retail enters it with the object itself, so BFME declares that
// interface first. No cast reaches a this-adjustment; this is a header change.
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_isCurrentlyFerryingSupplies_Thunk.cpp
// ?isCurrentlyFerryingSupplies@WorkerAIUpdate@@UBE_NXZ present-unmatched
Bool WorkerAIUpdate::isCurrentlyFerryingSupplies() const
{
	if (m_supplyTruckStateMachine)
	{
		switch (m_supplyTruckStateMachine->getCurrentStateID())
		{
			case ST_IDLE:
			case ST_BUSY:
			case ST_REGROUPING:
				return false;
			case ST_WANTING:
			case ST_DOCKING:
				return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
// ?isAvailableForSupplying@WorkerAIUpdate@@UBE_NXZ present-unmatched
Bool WorkerAIUpdate::isAvailableForSupplying() const 
{ 
	return true;
}

// ------------------------------------------------------------------------------------------------
// ?getRepairHealthPerSecond@WorkerAIUpdate@@UBEMXZ present-unmatched
Real WorkerAIUpdate::getRepairHealthPerSecond( void ) const
{
	return getWorkerAIUpdateModuleData()->m_repairHealthPercentPerSecond;
}
// ------------------------------------------------------------------------------------------------
// ?getBoredTime@WorkerAIUpdate@@UBEMXZ present-unmatched
Real WorkerAIUpdate::getBoredTime( void ) const
{
	return getWorkerAIUpdateModuleData()->m_boredTime;
}
// ------------------------------------------------------------------------------------------------
// ?getBoredRange@WorkerAIUpdate@@UBEMXZ present-unmatched
Real WorkerAIUpdate::getBoredRange( void ) const
{
	return getWorkerAIUpdateModuleData()->m_boredRange;
}

// ------------------------------------------------------------------------------------------------
// WorkerAIUpdate::createMachines is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateCtor.cpp (0x004A9ED5).

//-------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// ?getActionDelayForDock@WorkerAIUpdate@@ present-unmatched
UnsignedInt WorkerAIUpdate::getActionDelayForDock( Object *dock )
{
	// BFME's AIUpdate module-data pointer is at retail this-0x340.  The
	// ZH-shaped module header exposes the same fields through a shorter base;
	// this source-level displacement combines with the multiple-inheritance
	// this adjustment to emit the retail slot without changing that header.
	// Decide whether to use my Center or Warehouse delay time
	static const NameKeyType key_warehouseUpdate = NAMEKEY("SupplyWarehouseDockUpdate");
	SupplyWarehouseDockUpdate *warehouseModule = (SupplyWarehouseDockUpdate*) dock->findUpdateModule( key_warehouseUpdate );
	if (warehouseModule) {
		// The source class view is 0x204 bytes past BFME's retail layout; this -0x13c
		// therefore emits the retail module-data load at adjusted-this - 0x340.
		const char *moduleData = *reinterpret_cast<const char * const *>(reinterpret_cast<const char *>(this) - 0x13c);
		return *reinterpret_cast<const UnsignedInt *>(moduleData + 0x78);
	}
	static const NameKeyType key_centerUpdate = NAMEKEY("SupplyCenterDockUpdate");
	SupplyCenterDockUpdate *centerModule = (SupplyCenterDockUpdate*) dock->findUpdateModule( key_centerUpdate );
	if (centerModule) {
		const char *moduleData = *reinterpret_cast<const char * const *>(reinterpret_cast<const char *>(this) - 0x13c);
		return *reinterpret_cast<const UnsignedInt *>(moduleData + 0x74);
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?getWarehouseScanDistance@WorkerAIUpdate@@UBEMXZ present-unmatched
Real WorkerAIUpdate::getWarehouseScanDistance() const
{
	// Ai players get larger scan range.  jba.
	if (getObject()->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER) {
		return 2 * getWorkerAIUpdateModuleData()->m_warehouseScanDistance;
	}
	return getWorkerAIUpdateModuleData()->m_warehouseScanDistance;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME 2's Object private status byte (+0x438); bit 0 is effectively-dead.
struct BfmeWorkerPrivateStatus { unsigned char m_unreconstructed_000[ 0x438 ]; unsigned char m_privateStatus; };
// Only the slot positions matter in these views: the interface gained
// entries rather than being reordered (DozerAIUpdate.cpp spells the same).
template <Int N>
class BfmeWorkerSlots : public BfmeWorkerSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <>
class BfmeWorkerSlots<0>
{
};
class BfmeWorkerTaskSlots : public BfmeWorkerSlots<7>
{
public:
	virtual ObjectID getTaskTarget( DozerTask task ) = 0;		///< +0x1C
	virtual void unusedSlot8() = 0;
	virtual DozerTask getCurrentTask( void ) = 0;			///< +0x24
	virtual void unusedSlot10() = 0;
	virtual void unusedSlot11() = 0;
	virtual void unusedSlot12() = 0;
	virtual void cancelTask( DozerTask task ) = 0;			///< +0x34
};
class BfmeWorkerCommandSourceSlots : public BfmeWorkerSlots<143>
{
public:
	virtual CommandSourceType getLastCommandSource( void ) = 0;	///< +0x23C
};
class BfmeWorkerMachine : public BfmeWorkerSlots<4>
{
public:
	virtual void updateStateMachine( void ) = 0;			///< +0x10
	struct CurrentState { void *m_vtable; StateID m_id; };
	StateID getCurrentStateID( void ) const { return m_currentState ? m_currentState->m_id : INVALID_STATE_ID; }
	CurrentState *m_currentState;					///< +0x04
};
// BFME 2's module fields: the dozer task interface (+0x3E4), a byte at
// +0x3CC that suspends the worker, and the worker, dozer and supply truck
// machines (+0x4C0/+0x4C4/+0x4C8).
struct BfmeWorkerUpdateFields
{
	unsigned char m_unreconstructed_000[ 0x3cc ];
	Bool m_suspended;						///< +0x3CC
	unsigned char m_unreconstructed_3cd[ 0x3e4 - 0x3cd ];
	unsigned char m_taskInterface[ 4 ];				///< +0x3E4, a BfmeWorkerTaskSlots
	unsigned char m_unreconstructed_3e8[ 0x4c0 - 0x3e8 ];
	BfmeWorkerMachine *m_workerMachine;				///< +0x4C0
	BfmeWorkerMachine *m_dozerMachine;				///< +0x4C4
	BfmeWorkerMachine *m_supplyTruckStateMachine;			///< +0x4C8
};
#define WORKER_FIELDS ((BfmeWorkerUpdateFields *)this)
#define WORKER_TASKS ((BfmeWorkerTaskSlots *)WORKER_FIELDS->m_taskInterface)
// Retail 0x004AA92B (222B), update-interface slot 0 (this = module +0x10):
// Zero Hour's WorkerAIUpdate::update; BFME 2 also stops while the +0x3CC
// byte is set, tests the worker machine before reading its state and no
// longer raises the mine-clearing weapon set flag.
UpdateSleepTime WorkerAIUpdate::update( void )
{

	//
	// NOTE: Any changes to DozerAIUpdate::* you probably want to reflect and copy into
	// WorkerAIUPdate:* as well ... sigh
	//

	//
	// now that we're really executing we have all the necessary object modules in place to
	// correctly create a state machine and set the default state
	//
	// create all the machines if they don't yet exist
	createMachines();

	// extend the normal AI system
	AIUpdateInterface::update();

	// do nothing if we're dead
	if( ((const BfmeWorkerPrivateStatus *)getObject())->m_privateStatus & 1 )	// isEffectivelyDead, inline in retail
		return UPDATE_SLEEP_NONE;
	if( WORKER_FIELDS->m_suspended )
		return UPDATE_SLEEP_NONE;

	// run our own state machine, and the appropriate sub machine
	WORKER_FIELDS->m_workerMachine->updateStateMachine();

	if( WORKER_FIELDS->m_workerMachine )
	{
		if( WORKER_FIELDS->m_workerMachine->getCurrentStateID() == AS_DOZER )
		{

			// get and validate our current task
			DozerTask currentTask = WORKER_TASKS->getCurrentTask();
			if( currentTask != DOZER_TASK_INVALID )
			{
				ObjectID taskTarget = WORKER_TASKS->getTaskTarget( currentTask );
				Object *targetObject = TheGameLogic->findObjectByID( taskTarget );
				Bool invalidTask = FALSE;

				// validate the task and the target
				if( currentTask == DOZER_TASK_REPAIR &&
						TheActionManager->canRepairObject( getObject(), targetObject,
							((BfmeWorkerCommandSourceSlots *)this)->getLastCommandSource() ) == FALSE )
					invalidTask = TRUE;

				// cancel the task if it's now invalid
				if( invalidTask == TRUE )
					WORKER_TASKS->cancelTask( currentTask );

			}  // end if

			// update dozer behavior
			WORKER_FIELDS->m_dozerMachine->updateStateMachine();

		}  // end if
		else
		{
			WORKER_FIELDS->m_supplyTruckStateMachine->updateStateMachine();
		}
	}
	return UPDATE_SLEEP_NONE;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** The entry point of a construct command to the Dozer */
//-------------------------------------------------------------------------------------------------
// WorkerAIUpdate::construct: Zero Hour copy removed; the BFME 2 construction path is rowed in WorkerAIUpdateCtor.cpp.

// ------------------------------------------------------------------------------------------------
/** We just exited from a supply truck task and are now idle, we should go back to Dozer idle
		mode */
// ------------------------------------------------------------------------------------------------
// ?exitingSupplyTruckState@WorkerAIUpdate@@UAEXXZ present-unmatched
void WorkerAIUpdate::exitingSupplyTruckState()
{
	if( m_workerMachine->getCurrentStateID() == AS_SUPPLY_TRUCK )
	{
 		// We've been given a Dozer specific order that the Supply Truck machine doesn't recognize
 		// as BUSY (because this command also recognizes its own busy and is likewise waiting).
 		// Explicitly slap it upside the head.
 		if( getObject()->getAIUpdateInterface() )
 		{
 			getObject()->getAIUpdateInterface()->aiIdle(CMD_FROM_AI);
 		}
 		m_workerMachine->setState( AS_DOZER );
 		// To clarify, I leave supply truck mode when I notice I am doing something not supply
 		// truck related.  When given a construct command, I wait to do anything until I notice
 		// I'm not busy.  Both states are being polite, so I must force the switch.
	}
}
  

// ------------------------------------------------------------------------------------------------
/** Given our current task and repair target, can we accept this as a new repair target */
// ------------------------------------------------------------------------------------------------
// BFME 2's KINDOF_BRIDGE_TOWER test as retail inlines it here: bit 24 of the
// KindOf dword at +0x108 of the Object's raw template pointer (Thing +0x04),
// without the override walk Zero Hour's isKindOf takes. Retail tests the
// masked dword itself (mask hoisted into a register for both tests), so the
// helper answers the masked bits rather than a bool, which MSVC would narrow
// to a byte test.
static inline UnsignedInt workerIsBridgeTower( const Object *obj )
{
	const UnsignedInt *kindOf = (const UnsignedInt *)( *(const char * const *)((const char *)obj + 0x04) + 0x100 );
	return kindOf[ 2 ] & 0x1000000;
}

Bool WorkerAIUpdate::canAcceptNewRepair( Object *obj )
{

	// sanity
	if( obj == NULL )
		return FALSE;

	// if we're not repairing right now, we don't have any accept restrictions
	if( getCurrentTask() != DOZER_TASK_REPAIR )
		return TRUE;

	// get current repair target
	Object *currentRepair = TheGameLogic->findObjectByID( m_task[ DOZER_TASK_REPAIR ].m_targetObjectID );

	if( currentRepair )
	{

		// check for same object
		if( currentRepair == obj )
			return FALSE;

		// check for repairing any tower on the same bridge
		if( workerIsBridgeTower( currentRepair ) && workerIsBridgeTower( obj ) )
		{
			BridgeTowerBehaviorInterface *currentTowerInterface = NULL;
			BridgeTowerBehaviorInterface *newTowerInterface = NULL;

			currentTowerInterface = BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject( currentRepair );
			newTowerInterface = BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject( obj );

			// sanity
			if( currentTowerInterface == NULL || newTowerInterface == NULL )
			{

				DEBUG_CRASH(( "Unable to find bridge tower interface on object\n" ));
				return FALSE;

			}  // end if

			// if they are part of the same bridge, ignore this repair command
			if( currentTowerInterface->getBridgeID() == newTowerInterface->getBridgeID() )
				return FALSE;

		}  // end if

	}  // end if, currentRepair object exists

	// all is well
	return TRUE;

}  // end canAcceptNewRepair

//----------------------------------------------------------------------------------------
// ?privateIdle@WorkerAIUpdate@@MAEXW4CommandSourceType@@@Z present-unmatched
void WorkerAIUpdate::privateIdle(CommandSourceType cmdSource)
{
// Leaving this commented out to show that although the regular supply truck does this, the
	// worker's dozer brain will get completely screwed.

	// If the user gives a stop command, I have to turn off autopilot
//	if( cmdSource == CMD_FROM_PLAYER )
//		setForceBusyState(TRUE);
	
	AIUpdateInterface::privateIdle(cmdSource);
}

//----------------------------------------------------------------------------------------
// ?privateDock@WorkerAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z present-unmatched
void WorkerAIUpdate::privateDock( Object *dock, CommandSourceType cmdSource )
{
	AIUpdateInterface::privateDock( dock, cmdSource );

	// If this is a command from a player, I will remember this as my favorite dock to override
	// ResourceManager searches.
	if ((cmdSource == CMD_FROM_PLAYER) && dock)
	{
		// Please note, there is not a separate Warehouse and Center memory by Design.  Because
		// we lack a UI way to click Warehouse and drag to center to set up a specific path, the
		// practical realization has been made that you do not want separate memory.
		m_preferredDock = dock->getID();
	}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// WorkerAIUpdate::privateRepair is defined with its retail body in DozerAIUpdate.cpp.
// The Worker primary table at VA 0x00C54190 binds slot 44 to that body.


// ------------------------------------------------------------------------------------------------
/** Resume construction on a building */
// ------------------------------------------------------------------------------------------------
// ?privateResumeConstruction@WorkerAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z present-unmatched
void WorkerAIUpdate::privateResumeConstruction( Object *obj, CommandSourceType cmdSource )
{

	// sanity
	if( obj == NULL )
		return;

	// make sure we can resume construction on this
	if( TheActionManager->canResumeConstructionOf( getObject(), obj, cmdSource ) == FALSE )
		return;

	// start the new task for construction
	newTask( DOZER_TASK_BUILD, obj );

}  // end privateResumeConstruction

//-------------------------------------------------------------------------------------------------
/** Issue and order to the dozer */
//-------------------------------------------------------------------------------------------------
// WorkerAIUpdate::newTask is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateCtor.cpp (0x004AADB1).

//-------------------------------------------------------------------------------------------------
/** Cancel a task and reset the dozer behavior state machine so that it can 
	* re-evaluate what it wants to do if it was working on the task being
	* cancelled */
//-------------------------------------------------------------------------------------------------
// ?cancelTask@WorkerAIUpdate@@UAEXW4DozerTask@@@Z present-unmatched
void WorkerAIUpdate::cancelTask( DozerTask task )
{

	// clear the order
	internalCancelTask( task );

	// reset the machine to we can re-evaluate what we want to do
	m_dozerMachine->resetToDefaultState();

} 

//-------------------------------------------------------------------------------------------------
/** Is there a given task waiting to be done */
//-------------------------------------------------------------------------------------------------
Bool WorkerAIUpdate::isTaskPending( DozerTask task )
{

	// sanity
	DEBUG_ASSERTCRASH( task >= 0 && task < DOZER_NUM_TASKS, ("Illegal dozer task '%d'\n", task) );

	return m_task[ task ].m_targetObjectID != 0 ? TRUE : FALSE;
		
}  

//-------------------------------------------------------------------------------------------------
/** Is there any task pending */
//-------------------------------------------------------------------------------------------------
// ?isAnyTaskPending@WorkerAIUpdate@@ present-unmatched
Bool WorkerAIUpdate::isAnyTaskPending( void )
{
	
	for( Int i = 0; i < DOZER_NUM_TASKS; i++ )
		if( isTaskPending( (DozerTask)i ) )
			return TRUE;

	return FALSE;

} 

//-------------------------------------------------------------------------------------------------
/** Get the target object of a given task */
//-------------------------------------------------------------------------------------------------
ObjectID WorkerAIUpdate::getTaskTarget( DozerTask task )
{

	// sanity
	DEBUG_ASSERTCRASH( task >= 0 && task < DOZER_NUM_TASKS, ("Illegal dozer task '%d'\n", task) );

	return m_task[ task ].m_targetObjectID;

} 

//-------------------------------------------------------------------------------------------------
/** Set a task as successfully completed */
//-------------------------------------------------------------------------------------------------
void WorkerAIUpdate::internalTaskComplete( DozerTask task )
{

	// sanity
	DEBUG_ASSERTCRASH( task >= 0 && task < DOZER_NUM_TASKS, ("Illegal dozer task '%d'\n", task) );

	// call the single method that gets called for completing and canceling tasks
	internalTaskCompleteOrCancelled( task );

	// remove the info for this task
	m_task[ task ].m_targetObjectID = INVALID_ID;
	m_task[ task ].m_taskOrderFrame = 0;

	// remove dock point info for this task
	for( Int i = 0; i < DOZER_NUM_DOCK_POINTS; i++ )
		m_dockPoint[ task ][ i ].valid = FALSE;

} 

//-------------------------------------------------------------------------------------------------
/** Clear a task from the Dozer for consideration, we can use this when a goal object becomes
	* invalid/destroyed etc. */
//-------------------------------------------------------------------------------------------------
// WorkerAIUpdate::internalCancelTask is implemented with its target-matched
// body in WorkerAIUpdateCtor.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// WorkerAIUpdate::internalTaskCompleteOrCancelled is implemented with its target-matched
// body in WorkerAIUpdateCtor.cpp.

//-------------------------------------------------------------------------------------------------
/** If we were building something, kill the active-construction flag on it */
//-------------------------------------------------------------------------------------------------
// WorkerAIUpdate::onDelete is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateCtor.cpp (0x004AAB0B).

//-------------------------------------------------------------------------------------------------
/** Get the most recently issued task */
//-------------------------------------------------------------------------------------------------
DozerTask WorkerAIUpdate::getMostRecentCommand( void )
{
	Int i;
	DozerTask mostRecentTask = DOZER_TASK_INVALID;
	UnsignedInt mostRecentFrame = 0;

	for( i = 0; i < DOZER_NUM_TASKS; i++ )
	{
		if( isTaskPending( (DozerTask)i ) )
		{
			if( m_task[ i ].m_taskOrderFrame > mostRecentFrame )
			{
				mostRecentTask = (DozerTask)i;
				mostRecentFrame = m_task[ i ].m_taskOrderFrame;
			} 
		}  
	} 
	return mostRecentTask;			
} 

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
const Coord3D* WorkerAIUpdate::getDockPoint( DozerTask task, DozerDockPoint point )
{

	// sanity
	if( task < 0 || task >= DOZER_NUM_TASKS )
		return NULL;

	// sanity
	if( point < 0 || point >= DOZER_NUM_DOCK_POINTS )
		return NULL;

	// if the point has been set (is valid) then return it
	if( m_dockPoint[ task ][ point ].valid )
		return &m_dockPoint[ task ][ point ].location;

	// no valid point has been set for this dock point on this task
	return NULL;

}  // end getDockPoint

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// SupplyTruck stuff

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// WorkerAIUpdate::loseOneBox: retail's body is the row at 0x004A98AC
// (WorkerAIUpdateCtor.cpp); this unit only declares it, so its vtable binds there.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// WorkerAIUpdate::isSupplyTruckBrainActiveAndBusy is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateCtor.cpp (0x004A98D6).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?resetSupplyTruckBrain@WorkerAIUpdate@@QAEXXZ present-unmatched
void WorkerAIUpdate::resetSupplyTruckBrain()
{
	m_supplyTruckStateMachine->resetToDefaultState();
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?resetDozerBrain@WorkerAIUpdate@@QAEXXZ present-unmatched
void WorkerAIUpdate::resetDozerBrain()
{
	m_dozerMachine->resetToDefaultState();
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Worker's master state machine, that controls Dozerness or Supplytruckness
class ActAsDozerState :  public State
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(ActAsDozerState, "ActAsDozerState")		
protected:
	// snapshot interface STUBBED.
	virtual void crc( Xfer *xfer ){};
	virtual void xfer( Xfer *xfer ){};
	virtual void loadPostProcess(){};

public:
	ActAsDozerState( StateMachine *machine ) :State( machine, "ActAsDozerState" ){}
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	virtual StateReturnType onExit();
};
EMPTY_DTOR(ActAsDozerState)

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
class ActAsSupplyTruckState :  public State
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(ActAsSupplyTruckState, "ActAsSupplyTruckState")		
protected:
	// snapshot interface STUBBED.
	virtual void crc( Xfer *xfer ){};
	virtual void xfer( Xfer *xfer ){};
	virtual void loadPostProcess(){};

public:
	ActAsSupplyTruckState( StateMachine *machine ) :State( machine, "ActAsSupplyTruckState" ){}
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
	virtual StateReturnType onExit();
};
EMPTY_DTOR(ActAsSupplyTruckState)

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0WorkerStateMachine@@QAE@PAVObject@@@Z
// Body in WorkerAIUpdate_WorkerStateMachine.asm (exact 387B retail).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// WorkerStateMachine::~WorkerStateMachine: Zero Hour copy removed (it emitted non-retail vftables).

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// WorkerStateMachine::crc: Zero Hour copy removed.

// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ?xfer@WorkerStateMachine@@MAEXPAVXfer@@@Z present-unmatched
void WorkerStateMachine::xfer( Xfer *xfer )
{
	XferVersion cv = 1;	
	XferVersion v = cv; 
	xfer->xferVersion( &v, cv );

	StateMachine::xfer(xfer);
}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@WorkerStateMachine@@MAEXXZ present-unmatched
void WorkerStateMachine::loadPostProcess( void )
{
	StateMachine::loadPostProcess();
}  // end loadPostProcess

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?onEnter@ActAsDozerState@@ present-unmatched
StateReturnType ActAsDozerState::onEnter()
{
	return STATE_CONTINUE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?update@ActAsDozerState@@ present-unmatched
StateReturnType ActAsDozerState::update()
{
	return STATE_CONTINUE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?onExit@ActAsDozerState@@UAE?AW4StateReturnType@@XZ present-unmatched
StateReturnType ActAsDozerState::onExit()
{
	Object *owner = getMachineOwner();
	WorkerAIUpdate *update = (WorkerAIUpdate*)owner->getAIUpdateInterface();
	if( !update )
	{
		return STATE_FAILURE;
	}

	update->resetDozerBrain();

	return STATE_CONTINUE;
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?onEnter@ActAsSupplyTruckState@@ present-unmatched
StateReturnType ActAsSupplyTruckState::onEnter()
{
	return STATE_CONTINUE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?update@ActAsSupplyTruckState@@ present-unmatched
StateReturnType ActAsSupplyTruckState::update()
{
	return STATE_CONTINUE;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?onExit@ActAsSupplyTruckState@@UAE?AW4StateReturnType@@XZ present-unmatched
StateReturnType ActAsSupplyTruckState::onExit()
{
	Object *owner = getMachineOwner();
	WorkerAIUpdate *update = (WorkerAIUpdate*)owner->getAIUpdateInterface();
	if( !update )
	{
		return STATE_FAILURE;
	}

	update->resetSupplyTruckBrain();

	return STATE_CONTINUE;
}

// ------------------------------------------------------------------------------------------------
/** Create the bridge scaffolding if necessary for the bridge that is attached to this tower */
// ------------------------------------------------------------------------------------------------
// ?createBridgeScaffolding@WorkerAIUpdate@@UAEXPAVObject@@@Z present-unmatched
void WorkerAIUpdate::createBridgeScaffolding( Object *bridgeTower )
{

	// sanity
	if( bridgeTower == NULL )
		return;

	// get the bridge behavior interface from the bridge object that this tower is a part of
	BridgeTowerBehaviorInterface *btbi = BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject( bridgeTower );
	if( btbi == NULL )
		return;
	Object *bridgeObject = TheGameLogic->findObjectByID( btbi->getBridgeID() );
	if( bridgeObject == NULL )
		return;
	BridgeBehaviorInterface *bbi = BridgeBehavior::getBridgeBehaviorInterfaceFromObject( bridgeObject );
	if( bbi == NULL )
		return;

	// tell the bridge to create scaffolding if necessary
	bbi->createScaffolding();

}  // end createBridgeScaffolding

// ------------------------------------------------------------------------------------------------
/** Remove the bridge scaffolding from the bridge object that is attached to this tower */
// ------------------------------------------------------------------------------------------------
// ?removeBridgeScaffolding@WorkerAIUpdate@@UAEXPAVObject@@@Z present-unmatched
void WorkerAIUpdate::removeBridgeScaffolding( Object *bridgeTower )
{

	// sanity
	if( bridgeTower == NULL )
		return;

	// get the bridge behavior interface from the bridge object that this tower is a part of
	BridgeTowerBehaviorInterface *btbi = BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject( bridgeTower );
	if( btbi == NULL )
		return;
	Object *bridgeObject = TheGameLogic->findObjectByID( btbi->getBridgeID() );
	if( bridgeObject == NULL )
		return;
	BridgeBehaviorInterface *bbi = BridgeBehavior::getBridgeBehaviorInterfaceFromObject( bridgeObject );
	if( bbi == NULL )
		return;

	// tell the bridge to end any scaffolding from repairing
	bbi->removeScaffolding();

}  // end removeBridgeScaffolding

//------------------------------------------------------------------------------------------------
// WorkerAIUpdate::startBuildingSound: Zero Hour copy removed.

//------------------------------------------------------------------------------------------------
// WorkerAIUpdate::finishBuildingSound: Zero Hour copy removed.

//------------------------------------------------------------------------------------------------
// WorkerAIUpdate::getUpgradedSupplyBoost: Zero Hour copy removed.


// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@WorkerAIUpdate@@MAEXPAVXfer@@@Z present-unmatched
void WorkerAIUpdate::crc( Xfer *xfer )
{
	// extend base class
	AIUpdateInterface::crc(xfer);
}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// WorkerAIUpdate::xfer is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateXfer.cpp (0x004AA1DB).

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
