// cl: /Ireference/shims/bfme2_drawable_flash /Ireference/shims/bfme2_dozer /Ireference/shims/partitionfilterzh /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp); this unit had no counterpart under Code/.
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

// FILE: DozerAIUpdate.cpp ////////////////////////////////////////////////////////////////////////
// Author: Colin Day, February 2002
// Desc:   Dozer AI behavior
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ActionManager.h"
#include "Common/Team.h"
#include "Common/StateMachine.h"
#include "Common/BuildAssistant.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Player.h"
#include "Common/Money.h"
#include "Common/Radar.h"
#include "Common/RandomValue.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/Xfer.h"
#include "vector3.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PartitionFilterZh.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/BridgeBehavior.h"
#include "GameLogic/Module/BridgeTowerBehavior.h"
#include "GameLogic/Module/CreateModule.h"
#include "GameLogic/Module/DozerAIUpdate.h"
#include "GameLogic/Module/WorkerAIUpdate.h"
#include "GameClient/InGameUI.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned long _Base_bitset<4>::_S_maskbit(unsigned int); }
// bfme link decl-only end


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// Zero Hour's dozer action/primary state machines and their states were removed:
// those unrowed copies referenced Zero Hour's StateMachine ABI, which BFME 2
// does not have. The retail bodies this unit owns are rowed below.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
template <Int N>
class BfmeDozerSlots : public BfmeDozerSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeDozerSlots<0>
{
};



//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// LINK-DUP: ??0DozerAIUpdateModuleData@@QAE@XZ and
// ?buildFieldParse@DozerAIUpdateModuleData@@ owned by DozerAIUpdateModuleDataCtor.cpp;
// this file merely declares them via GameLogic/Module/DozerAIUpdate.h.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/AI/DozerAIUpdateCtorThunk.cpp
// ??0DozerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z present-unmatched
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1DozerAIUpdate@@ present-unmatched
// ------------------------------------------------------------------------------------------------
/** Create any sub machines we need to do all our behavior */
// ------------------------------------------------------------------------------------------------
// DozerAIUpdate::createMachines is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp (0x00488EFC).

// ------------------------------------------------------------------------------------------------
/** Create the bridge scaffolding if necessary for the bridge that is attached to this tower */
// ------------------------------------------------------------------------------------------------
void DozerAIUpdate::createBridgeScaffolding( Object *bridgeTower )
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
void DozerAIUpdate::removeBridgeScaffolding( Object *bridgeTower )
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

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME 2's Object private status byte (+0x438); bit 0 is effectively-dead.
struct BfmeDozerPrivateStatus { unsigned char m_unreconstructed_000[ 0x438 ]; unsigned char m_privateStatus; };
// BFME 2's dozer task interface (module +0x3E4) and state machine pointer
// (module +0x400) sit 0x1E8 bytes later than this unit's Zero Hour layout,
// and the slots it calls moved; these views spell the retail offsets.
class BfmeDozerTaskSlots : public BfmeDozerSlots<7>
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
class BfmeDozerCommandSourceSlots : public BfmeDozerSlots<143>
{
public:
	virtual CommandSourceType getLastCommandSource( void ) = 0;	///< +0x23C
};
class BfmeDozerMachineSlots : public BfmeDozerSlots<4>
{
public:
	virtual void updateStateMachine( void ) = 0;			///< +0x10
};
struct BfmeDozerUpdateFields
{
	unsigned char m_unreconstructed_000[ 0x3e4 ];
	unsigned char m_taskInterface[ 4 ];				///< +0x3E4, a BfmeDozerTaskSlots
	unsigned char m_unreconstructed_3e8[ 0x400 - 0x3e8 ];
	BfmeDozerMachineSlots *m_dozerMachine;			///< +0x400
};
#define DOZER_TASKS ((BfmeDozerTaskSlots *)((BfmeDozerUpdateFields *)this)->m_taskInterface)
#define DOZER_MACHINE (((BfmeDozerUpdateFields *)this)->m_dozerMachine)
// Retail 0x00489800 (149B), update-interface slot 0 (this = module +0x10):
// Zero Hour's DozerAIUpdate::update without its idle mine-clearing switch.
UpdateSleepTime DozerAIUpdate::update( void )
{
	// now that we're really executing we have all the necessary object modules in place to
	// correctly create a state machine and set the default state
	createMachines();

	// extend the normal AI system
	UpdateSleepTime result;
	result = AIUpdateInterface::update();

	// do nothing if we're dead
	if( ((const BfmeDozerPrivateStatus *)getObject())->m_privateStatus & 1 )	// isEffectivelyDead, inline in retail
		return UPDATE_SLEEP_NONE;


	// get and validate our current task
	DozerTask currentTask = DOZER_TASKS->getCurrentTask();
	if( currentTask != DOZER_TASK_INVALID )
	{
		ObjectID taskTarget = DOZER_TASKS->getTaskTarget( currentTask );
		Object *targetObject = TheGameLogic->findObjectByID( taskTarget );
		Bool invalidTask = FALSE;

		// validate the task and the target
		if( currentTask == DOZER_TASK_REPAIR &&
				TheActionManager->canRepairObject( getObject(), targetObject,
					((BfmeDozerCommandSourceSlots *)this)->getLastCommandSource() ) == FALSE )
			invalidTask = TRUE;

		// cancel the task if it's now invalid
		if( invalidTask == TRUE )
			DOZER_TASKS->cancelTask( currentTask );

	}  // end if

	// run our own state machine
	DOZER_MACHINE->updateStateMachine();

	return UPDATE_SLEEP_NONE;

}  // end update
#undef DOZER_TASKS
#undef DOZER_MACHINE

//-------------------------------------------------------------------------------------------------
/** The entry point of a construct command to the Dozer */
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Given our current task and repair target, can we accept this as a new repair target */
// ------------------------------------------------------------------------------------------------
// ?canAcceptNewRepair@DozerAIUpdate@@UAE_NPAVObject@@@Z
Bool DozerAIUpdate::canAcceptNewRepair( Object *obj )
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
		const unsigned int towerMask = 0x01000000;
		if( ( *(const unsigned int *)((const char *)*(const void **)((const char *)currentRepair + 4) + 0x108) & towerMask ) && 
				( *(const unsigned int *)((const char *)*(const void **)((const char *)obj + 4) + 0x108) & towerMask ) )
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

// Dozer's primary table at VA 0x00C4B848 binds slot 44 to this repair body.
// The DozerAIInterface subobject at +0x3E4 accepts and starts the repair task.
void DozerAIUpdate::privateRepair(Object *obj, CommandSourceType cmdSource)
{
	Object *dozer = *(Object **)((char *)this + 0x08);
	DozerAIInterface *self = (DozerAIInterface *)((char *)this + 0x3E4);
	if (self->canAcceptNewRepair(obj) == FALSE)
		return;
	if (TheActionManager->canRepairObject(dozer, obj, cmdSource) == FALSE)
		return;
	ObjectID currentRepairer = obj->getSoleHealingBenefactor();
	if (currentRepairer != INVALID_ID && currentRepairer != *(ObjectID *)((char *)dozer + 0x74))
		return;
	self->newTask(DOZER_TASK_REPAIR, obj);
}

// ?rva00488C48@Rva00488C48@@QBEMXZ, retail 0x00488C48 (72 bytes).
// The offsets and paired repair routine place this method on the +0x3E4
// DozerAIInterface view of an AIUpdate object; the final name stays
// address-derived. The two controlling-player calls and its +0x5C discriminator
// gate the AI multiplier applied to the host object's +0x6C value.
class Rva00488C48
{
public:
	Real rva00488C48() const;
};

// ?<Rva00488C48::rva00488C48> present-unmatched
Real Rva00488C48::rva00488C48() const
{
	Object **dozer = (Object **)((char *)this - 0x3DC);
	if ((*dozer)->getControllingPlayer() != 0 &&
		*(int *)((char *)(*dozer)->getControllingPlayer() + 0x5C) == 1)
	{
		Object *thing = *(Object **)((char *)this - 0x3E0);
		void *aiData = *(void **)((char *)TheAI + 0x18);
		return *(Real *)((char *)thing + 0x6C) * *(Real *)((char *)aiData + 0x88);
	}
	Object *thing = *(Object **)((char *)this - 0x3E0);
	return *(Real *)((char *)thing + 0x6C);
}

// ------------------------------------------------------------------------------------------------
/** Issue an order for the Worker to go repair the target 'obj' */
// ------------------------------------------------------------------------------------------------
void WorkerAIUpdate::privateRepair( Object *obj, CommandSourceType cmdSource )
{
	Object *dozer = *(Object **)((char *)this + 0x08);

	// sanity, if we can't repair the object then get out of there
	if( TheActionManager->canRepairObject( dozer, obj, cmdSource ) == FALSE )
		return;

	const ThingTemplate *thingTemplate = *(const ThingTemplate **)((char *)dozer + 4);
	if( ( ( *(const unsigned char *)((const char *)thingTemplate + 0x109) ) & 0x80 ) == 0 )
	{
		DozerAIInterface *self = (DozerAIInterface *)((char *)this + 0x3e4);
		// if we are already repairing this target do nothing
		if( self->canAcceptNewRepair( obj ) == FALSE )
			return;

		// if this object is already actively being repaired by another dozertype we won't also try to go repair it
		ObjectID currentRepairer = obj->getSoleHealingBenefactor();
		if( currentRepairer != INVALID_ID && currentRepairer != dozer->getID() )
			return;
	}

	DozerAIInterface *self = (DozerAIInterface *)((char *)this + 0x3e4);
	// start the new task
	self->newTask( DOZER_TASK_REPAIR, obj );

}  // end repair

// ------------------------------------------------------------------------------------------------
/** Resume construction on a building */
// ------------------------------------------------------------------------------------------------
// rowed in its own unit
  // end privateResumeConstruction

// DozerAIUpdate::findGoodBuildOrRepairPosition and findGoodBuildOrRepairPositionAndTarget:
// retail bodies rowed in DozerAIUpdateCtor.cpp (0x00489039, 0x00489913).

//-------------------------------------------------------------------------------------------------
/** Issue and order to the dozer */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate_newTask_Thunk.cpp
// DozerAIUpdate::newTask is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp (0x00489A07).

//-------------------------------------------------------------------------------------------------
/** Cancel a task and reset the dozer behavior state machine so that it can 
	* re-evaluate what it wants to do if it was working on the task being
	* cancelled */
//-------------------------------------------------------------------------------------------------
// DozerAIUpdate::cancelTask is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp (0x0048AE8A).

//-------------------------------------------------------------------------------------------------
/** Is there a given task waiting to be done */
//-------------------------------------------------------------------------------------------------
Bool DozerAIUpdate::isTaskPending( DozerTask task )
{

	// sanity
	DEBUG_ASSERTCRASH( task >= 0 && task < DOZER_NUM_TASKS, ("Illegal dozer task '%d'\n", task) );

	return m_task[ task ].m_targetObjectID != 0 ? TRUE : FALSE;
		
}  // end isTaskPending

//-------------------------------------------------------------------------------------------------
/** Is there any task pending */
//-------------------------------------------------------------------------------------------------
Bool DozerAIUpdate::isAnyTaskPending( void )
{
	
	for( Int i = 0; i < DOZER_NUM_TASKS; i++ )
		if( isTaskPending( (DozerTask)i ) )
			return TRUE;

	return FALSE;

}  // end isAnyTaskPending
//-------------------------------------------------------------------------------------------------
/** Get the target object of a given task */
//-------------------------------------------------------------------------------------------------
ObjectID DozerAIUpdate::getTaskTarget( DozerTask task )
{

	// sanity
	DEBUG_ASSERTCRASH( task >= 0 && task < DOZER_NUM_TASKS, ("Illegal dozer task '%d'\n", task) );

	return m_task[ task ].m_targetObjectID;

}  // end getTaskTarget

// BFME 2 keeps only 0x10 bytes of members between m_task and the dock point
// table (Zero Hour's inline AudioEventRTS m_buildingSound sits elsewhere), so
// retail addresses the dock points 0x28 bytes past m_task (+0x2C from the
// DozerAIInterface base) rather than at Zero Hour's m_dockPoint. Addressed raw
// here, like finishBuildingSound's handle.
#define BFME_DOZER_DOCK_POINT( task, i ) \
	( ( (DozerDockPointInfo *)( (char *)m_task + 0x28 ) )[ (task) * DOZER_NUM_DOCK_POINTS + (i) ] )

//-------------------------------------------------------------------------------------------------
/** Set a task as successfully completed */
//-------------------------------------------------------------------------------------------------
void DozerAIUpdate::internalTaskComplete( DozerTask task )
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
		BFME_DOZER_DOCK_POINT( task, i ).valid = FALSE;

}  // end internalTaskComplete

//-------------------------------------------------------------------------------------------------
/** Clear a task from the Dozer for consideration, we can use this when a goal object becomes
	* invalid/destroyed etc. */
//-------------------------------------------------------------------------------------------------
void DozerAIUpdate::internalCancelTask( DozerTask task )
{

	// sanity
	DEBUG_ASSERTCRASH( task >= 0 && task < DOZER_NUM_TASKS, ("Illegal dozer task '%d'\n", task) );

	// (BFME 2 retail has no range check here; WB keeps only the assert.)

	// call the single method that gets called for completing and canceling tasks
	internalTaskCompleteOrCancelled( task );

	// remove the info for this task
	m_task[ task ].m_targetObjectID = INVALID_ID;
	m_task[ task ].m_taskOrderFrame = 0;
	
	// remove dock point info for this task
	for( Int i = 0; i < DOZER_NUM_DOCK_POINTS; i++ )
		BFME_DOZER_DOCK_POINT( task, i ).valid = FALSE;
	
	// stop the dozer from moving: BFME 2's Object keeps its AI update at +0x258
	// and AIUpdateInterface its AICommandInterface base at +0x20; the module's
	// object sits 0x3DC before the DozerAIInterface base, i.e. 0x3E0 before
	// m_task (BFME 2's layout, addressed raw as in privateRepair)
	Object *dozer = *(Object **)((char *)m_task - 0x3e0);
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)dozer + 0x258);
	((AICommandInterface *)((char *)ai + 0x20))->aiIdle( CMD_FROM_AI );

}  // end internalCancelTask

// ------------------------------------------------------------------------------------------------
/** This method is called whenever a task is completed *OR* cancelled */
// ------------------------------------------------------------------------------------------------
// DozerAIUpdate::internalTaskCompleteOrCancelled is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp (0x00489647).

//-------------------------------------------------------------------------------------------------
/** If we were building something, kill the active-construction flag on it */
//-------------------------------------------------------------------------------------------------
// DozerAIUpdate::onDelete is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp (0x00489CA1).

//-------------------------------------------------------------------------------------------------
/** Get the most recently issued task */
//-------------------------------------------------------------------------------------------------
DozerTask DozerAIUpdate::getMostRecentCommand( void )
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

			}  // end if

		}  // end if

	}  // end for i

	return mostRecentTask;
			
}  // end getMostRecentCommand

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// DozerAIUpdate::getDockPoint is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp (0x00488BFA).

// ------------------------------------------------------------------------------------------------
// ?getRepairHealthPerSecond@DozerAIUpdate@@UBEMXZ present-unmatched
Real DozerAIUpdate::getRepairHealthPerSecond( void ) const
{
	return getDozerAIUpdateModuleData()->m_repairHealthPercentPerSecond;
}
// ------------------------------------------------------------------------------------------------
// ?getBoredTime@DozerAIUpdate@@UBEMXZ present-unmatched
Real DozerAIUpdate::getBoredTime( void ) const
{
	return getDozerAIUpdateModuleData()->m_boredTime;
}
// ------------------------------------------------------------------------------------------------
// ?getBoredRange@DozerAIUpdate@@UBEMXZ present-unmatched
Real DozerAIUpdate::getBoredRange( void ) const
{
	if (getObject()->getControllingPlayer() &&
		getObject()->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER) {
		return TheAI->getAiData()->m_aiDozerBoredRadiusModifier*getDozerAIUpdateModuleData()->m_boredRange;
	}
	return getDozerAIUpdateModuleData()->m_boredRange;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// DozerAIUpdate::aiDoCommand is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp (0x0048AF0B).

//------------------------------------------------------------------------------------------------
// DozerAIUpdate::startBuildingSound: Zero Hour copy removed.

//------------------------------------------------------------------------------------------------
// BFME 2's body is the 26-byte fold at 0x004550DE (rowed from DozerAIUpdateCtor.cpp:
// the dtor 0x00489EB7 calls it directly); this +0x2E4 copy is WorkerAIUpdate's 0x004A99F6.
// DozerAIUpdate::finishBuildingSound is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateCtor.cpp (0x004550DE).


// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/DozerAIUpdate_xferMethodThunk.cpp
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateXfer.cpp

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// BFME 2 phantom-structure members (no Zero Hour counterpart). Identities from
// WorldBuilder leads (reverse/wb_name_leads.csv), whose debug build asserts at
// DozerAIUpdate.cpp:2862/2869; retail supplies the bytes. The fields are read
// through retail-offset views, as the vendored layout differs.
//-------------------------------------------------------------------------------------------------
struct BfmeDozerPhantomFields
{
	unsigned char m_unreconstructed_000[ 0x8 ];
	Object *m_object;					///< retail this+0x08, the module's object
	unsigned char m_unreconstructed_00C[ 0x4a4 - 0xc ];
	ObjectID m_phantomStructureID;				///< retail this+0x4A4 (WB +0x4A8)
};

struct BfmePhantomObjectFields
{
	unsigned char m_unreconstructed_000[ 0x454 ];
	Bool m_flag454;						///< retail +0x454 (WB +0x468)
	unsigned char m_unreconstructed_455[ 0x4b0 - 0x455 ];
	Bool m_isInert;						///< retail +0x4B0 (WB +0x4C4)
};

// The player's rowed per-object unlock removal (0x002ACECC, placeholder name).
class Rva002ACECC
{
public:
	void rva002ACECC(Int id);				// 0x002ACECC
};

// DozerAIUpdate::makePhantomStructureInert, retail 0x00489DE3 (75 bytes):
// a phantom structure that still exists is marked effectively dead and
// inert; a stale id is dropped.
void DozerAIUpdate::makePhantomStructureInert()
{
	BfmeDozerPhantomFields *fields = (BfmeDozerPhantomFields *)this;
	if (fields->m_phantomStructureID == INVALID_ID)
		return;
	Object *phantomStructure = TheGameLogic->findObjectByID(fields->m_phantomStructureID);
	if (phantomStructure == NULL)
	{
		fields->m_phantomStructureID = INVALID_ID;
		return;
	}
	phantomStructure->setEffectivelyDead(true);
	if (((BfmePhantomObjectFields *)phantomStructure)->m_flag454)
		phantomStructure->rva0028BAC0();
	((BfmePhantomObjectFields *)phantomStructure)->m_isInert = true;
}

// DozerAIUpdate::makePhantomStructureNotInert, retail 0x00489E2E (99 bytes):
// the controlling player first drops the phantom's id through 0x002ACECC,
// then a phantom that still exists is revived; a stale id is dropped.
void DozerAIUpdate::makePhantomStructureNotInert()
{
	BfmeDozerPhantomFields *fields = (BfmeDozerPhantomFields *)this;
	if (fields->m_phantomStructureID == INVALID_ID)
		return;
	if (fields->m_object != NULL)
	{
		Player *player = fields->m_object->getControllingPlayer();
		if (player != NULL)
			((Rva002ACECC *)player)->rva002ACECC(fields->m_phantomStructureID);
	}
	Object *phantomStructure = TheGameLogic->findObjectByID(fields->m_phantomStructureID);
	if (phantomStructure == NULL)
	{
		fields->m_phantomStructureID = INVALID_ID;
		return;
	}
	((BfmePhantomObjectFields *)phantomStructure)->m_isInert = false;
	phantomStructure->rva0028DCC4();
	phantomStructure->setEffectivelyDead(false);
}
