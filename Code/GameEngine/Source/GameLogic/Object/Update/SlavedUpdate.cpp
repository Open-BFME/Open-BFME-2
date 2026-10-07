// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Update/SlavedUpdate.cpp); this unit had no counterpart under Code/.
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

// FILE: SlavedUpdate.cpp /////////////////////////////////////////////////////////////////////////
// Author: Matt Campbell, March 2002
// Updated: Kris Morness, July 2002 -- Add support for advanced scout drone abilities
// Desc:  Slaved unit(s) remain close to their master. Used by scout drones, and used by stinger
//        soldiers that are close to a stinger site. It's important to note that any slaved units
//				can use any or all features, some of which are specialized.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "Common/Team.h"
#include "Common/MiscAudio.h"
#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/SlavedUpdate.h"
#include "GameLogic/Weapon.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define STRAY_MULTIPLIER 2.0f // Multiplier from stating diestance from tunnel, to max distance from
const Real CLOSE_ENOUGH = 15;				// Our moveTo commands and pathfinding can't handle people in the way, so quit trying to hump someone on your spot
const Real CLOSE_ENOUGH_SQR = (CLOSE_ENOUGH * CLOSE_ENOUGH);

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ?SlavedUpdate::~SlavedUpdate present-unmatched
SlavedUpdate::~SlavedUpdate( void )
{
} 

//-------------------------------------------------------------------------------------------------
// ?SlavedUpdate::onObjectCreated present-unmatched
void SlavedUpdate::onObjectCreated()
{
	const SlavedUpdateModuleData* data = getSlavedUpdateModuleData();

	if( data->m_repairRatePerSecond > 0.0f )
	{
		//If this object can repair, pack it up at init.
		getObject()->setModelConditionState( MODELCONDITION_PACKING );
	}
}

//-------------------------------------------------------------------------------------------------
// SlavedUpdate::onEnslave is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateRepair.cpp (0x004A1BFD).

//-------------------------------------------------------------------------------------------------
// ?SlavedUpdate::onSlaverDie present-unmatched
void SlavedUpdate::onSlaverDie( const DamageInfo *info )
{
	stopSlavedEffects();
}

//-------------------------------------------------------------------------------------------------
// ?SlavedUpdate::onSlaverDamage present-unmatched
void SlavedUpdate::onSlaverDamage( const DamageInfo *info )
{
	// Only slaves with a ProneUpdate will even care.
	AIUpdateInterface *ai = getObject()->getAIUpdateInterface();
	if( ai )
		ai->aiGoProne( info, CMD_FROM_AI );
}


//-------------------------------------------------------------------------------------------------
// ?SlavedUpdate::update present-unmatched
UpdateSleepTime SlavedUpdate::update( void )
{
/// @todo srj use SLEEPY_UPDATE here
	if( m_framesToWait > 0 )
	{
		m_framesToWait--;
	}
	if( m_repairState == REPAIRSTATE_NONE )
	{
		if( m_framesToWait > 0 )
		{
			return UPDATE_SLEEP_NONE;
		}
		m_framesToWait = SLAVED_UPDATE_RATE;
	}

	if( m_slaver == INVALID_ID )
		return UPDATE_SLEEP_NONE;

	const SlavedUpdateModuleData* data = getSlavedUpdateModuleData();
	Object *me = getObject();
	if( !me )
	{
		return UPDATE_SLEEP_NONE;
	}
	AIUpdateInterface *myAI = me->getAIUpdateInterface();
	if( !myAI )
	{
		return UPDATE_SLEEP_NONE;
	}
	Locomotor *locomotor = myAI->getCurLocomotor();
	if( !locomotor )
	{
		return UPDATE_SLEEP_NONE;
	}

	Object *master = TheGameLogic->findObjectByID( m_slaver );
	if( !master || master->isEffectivelyDead() || master->isDisabledByType( DISABLED_UNMANNED ) )
	{
		stopSlavedEffects();
		
		//Killing is lame.
		//me->kill();

		//Let's disable the drone so it crashes instead!
		//Added special case code in physics falling to ensure death.
		me->setDisabled( DISABLED_UNMANNED );
    if ( me->getAI() )
      me->getAI()->aiIdle( CMD_FROM_AI);

		return UPDATE_SLEEP_NONE;
	}
	else 
	{
		Team *masterTeam = master->getTeam();
		Team *myTeam     = me->getTeam();
		if ( masterTeam->getRelationship( myTeam ) != ALLIES )
		{//slaver must have been hijacked or something..	// we will join his team
			me->defect( masterTeam, 0 );
		}

    


	}
	
	if (data->m_stayOnSameLayerAsMaster)
		me->setLayer(master->getLayer());
	
	//Clear the drone spotting bonus to the master. Up to the drone
	//to satisfy the conditions to set it again for the next update.
	master->clearWeaponBonusCondition( WEAPONBONUSCONDITION_DRONE_SPOTTING );
	
	//Get my master's AI. If he is attacking something, grant him a range bonus,
	//and I'll fly over the target.
	Object *target = NULL;
	AIUpdateInterface *masterAI = master->getAIUpdateInterface();
	if( masterAI )
	{
		target = masterAI->getCurrentVictim(); 
	}

	//Calculate the health percentage of the master -- there are two places we care.
	//NOTE: Health percentage will always be 100 should the drone be incapable of
	//repairing.
	Int healthPercentage = 100;
	if( data->m_repairRatePerSecond > 0.0f )
	{
		BodyModuleInterface *body = master->getBodyModule();
		if( body )
		{
			Real health = body->getHealth();
			Real maxHealth = body->getMaxHealth();
			healthPercentage = (Int)(health / maxHealth * 100.0f);
		}
	}
		
	//Determine whether or not we need to go back to the master to repair him
	if( healthPercentage <= data->m_repairWhenHealthBelowPercentage )
	{
		//1ST PRIORITY: Go to the master's position to repair him because he needs it.
		doRepairLogic();
		return UPDATE_SLEEP_NONE;
	}

	if( data->m_attackRange )
	{
		//2ND PRIORITY: Go to the master's current victim (as close as wander distance allows)
		if( target )
		{
			//At this point, we officially are in an attack mode! Now, simply 
			endRepair();
			doAttackLogic( target );
			return UPDATE_SLEEP_NONE;
		}
	}

	if( data->m_scoutRange )
	{
		//3RD PRIORITY: Hover above master's current move destination (as close as wander distance
		//allows).
		if( masterAI->getPath() )
		{
			const Coord3D *masterDest = masterAI->getPath()->getLastNode()->getPosition();

			//Check to see if master is close to the goal position.
			Real distSqr = ThePartitionManager->getDistanceSquared( master, masterDest, FROM_BOUNDINGSPHERE_2D );
			if( distSqr > (data->m_guardMaxRange * 0.5f) * (data->m_guardMaxRange * 0.5f) )
			{
				//If the master's distance to destination is more than half of the guarding range of the slave,
				//then order the slave to scout it.
				endRepair();
				doScoutLogic( masterDest );
				return UPDATE_SLEEP_NONE;
			}
		}
	}

	//NOTE: Health percentage will always be 100 should the drone be incapable of
	//repairing.
	if( healthPercentage < 100 )
	{
		//3RD PRIORITY: Go to the master's position to repair him (because we're idle)
		doRepairLogic();
		return UPDATE_SLEEP_NONE;
	}

	// update our "pinned" location based on where our master is
	Coord3D pinnedPosition = *master->getPosition();
	pinnedPosition.x += m_guardPointOffset.x;
	pinnedPosition.y += m_guardPointOffset.y;
	m_guardPointOffset.z = TheTerrainLogic->getGroundHeight( pinnedPosition.x, pinnedPosition.y );

	if( data->m_guardMaxRange )
	{
		//3RD PRIORITY: Guard the master's area.
		if( myAI->isIdle() && ThePartitionManager->getDistanceSquared(me, &pinnedPosition, FROM_CENTER_3D) > CLOSE_ENOUGH_SQR )
		{
			//I'm idle and too far away.
			endRepair();
			doGuardLogic( &pinnedPosition );
		}
		else if( ThePartitionManager->getDistanceSquared( me, master, FROM_CENTER_3D ) > sqr(STRAY_MULTIPLIER * data->m_guardMaxRange ) )
		{
			//I'm too far away, no matter what I'm doing.
			endRepair();
			doGuardLogic( &pinnedPosition );
		}
	}
	return UPDATE_SLEEP_NONE;
}

//-------------------------------------------------------------------------------------------------
// We are ordered to attempt to get as close as possible to my master's target.
//-------------------------------------------------------------------------------------------------
// SlavedUpdate::doAttackLogic is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateRepair.cpp (0x004A1C77).

//-------------------------------------------------------------------------------------------------
// We are ordered to attempt to get as close as possible to my master's movement destination point.
//-------------------------------------------------------------------------------------------------
// SlavedUpdate::doScoutLogic is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateRepair.cpp (0x004A1E3B).

//-------------------------------------------------------------------------------------------------
// We are ordered to attempt to get as close as possible to my master's position.
//-------------------------------------------------------------------------------------------------
// ?SlavedUpdate::doGuardLogic present-unmatched
void SlavedUpdate::doGuardLogic( Coord3D *pinnedPosition )
{
	const SlavedUpdateModuleData* data = getSlavedUpdateModuleData();
	Object *me = getObject();

	if( data->m_guardWanderRange )
	{
		// recalc where we want to be if we wander around
		Real randomDirection = GameLogicRandomValue( 0, 2*PI );
		m_guardPointOffset.zero();
		m_guardPointOffset.x += data->m_guardMaxRange * Cos( randomDirection );
		m_guardPointOffset.y += data->m_guardMaxRange * Sin( randomDirection );

		pinnedPosition->x += m_guardPointOffset.x;
		pinnedPosition->y += m_guardPointOffset.y;
		m_guardPointOffset.z = TheTerrainLogic->getGroundHeight( pinnedPosition->x, pinnedPosition->y );
	}
	AIUpdateInterface *ai = me->getAIUpdateInterface();
	if( ai )
	{
		ai->aiMoveToPosition( pinnedPosition, CMD_FROM_AI );
	}
}

//-------------------------------------------------------------------------------------------------
// We are ordered to repair our master
//-------------------------------------------------------------------------------------------------
// SlavedUpdate::doRepairLogic is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateRepair.cpp (0x004A24D3).

//-------------------------------------------------------------------------------------------------
// SlavedUpdate::endRepair is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateRepair.cpp (0x004A1C10).

//-------------------------------------------------------------------------------------------------
// SlavedUpdate::setRepairModelConditionStates is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateRepair.cpp (0x004A197D).

//-------------------------------------------------------------------------------------------------
// SlavedUpdate::setRepairState is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateRepair.cpp (0x004A2258).

//-------------------------------------------------------------------------------------------------
// SlavedUpdate::moveToNewRepairSpot is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateMoveToNewRepairSpot.cpp (0x004A2144).

//-------------------------------------------------------------------------------------------------
// ?SlavedUpdate::startSlavedEffects present-unmatched
void SlavedUpdate::startSlavedEffects( const Object *slaver )
{
	if( slaver == NULL )
		return;

	m_slaver = slaver->getID();
	const SlavedUpdateModuleData* data = getSlavedUpdateModuleData();

	// Decide where our pinned stray point is
	Real randomDirection = GameLogicRandomValue( 0, 2*PI );
	m_guardPointOffset.zero();
	m_guardPointOffset.x += data->m_guardMaxRange * Cos( randomDirection );
	m_guardPointOffset.y += data->m_guardMaxRange * Sin( randomDirection );
	
	// mark selves as not selectable
	getObject()->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_UNSELECTABLE ) );


  if ( slaver->testStatus( OBJECT_STATUS_STEALTHED ) )
  {
    StealthUpdate *myStealth = getObject()->getStealth();
    if ( myStealth )
    {
      myStealth->receiveGrant( true );
      // note to anyone... once stealth is granted to this drone(or such) 
      // let its own stealthupdate govern the allowedtostealth cases
    }
  }


}

//-------------------------------------------------------------------------------------------------
// ?SlavedUpdate::stopSlavedEffects present-unmatched
void SlavedUpdate::stopSlavedEffects()
{
	m_slaver = INVALID_ID;
	m_guardPointOffset.zero();

	/// @todo Just a thought.  Our Status bits on objects really need to be reference counts so you don't clear someone else's flag
	getObject()->clearStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_UNSELECTABLE ) );
	getObject()->clearDisabled( DISABLED_HELD );
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?SlavedUpdate::crc present-unmatched
void SlavedUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?SlavedUpdate::xfer present-unmatched
void SlavedUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// slaver
	xfer->xferObjectID( &m_slaver );

	// guard point offset
	xfer->xferCoord3D( &m_guardPointOffset);

	// frames to wait
	xfer->xferInt( &m_framesToWait );

	// repair state
	xfer->xferUser( &m_repairState, sizeof( RepairStates ) );

	// repairing
	xfer->xferBool( &m_repairing );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?SlavedUpdate::loadPostProcess present-unmatched
void SlavedUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess

