// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/ocls /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
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

// FILE: SpawnBehavior.cpp ////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, January 2002
// Desc:   Update will create and monitor a group of spawned units and replace as needed
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "Common/GameState.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Player.h"
#include "Common/Xfer.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/SpawnBehavior.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameClient/Drawable.h" //selection logic
#include "GameClient/InGameUI.h" // selection logic
#include "GameLogic/ExperienceTracker.h" //veterancy logic
#include "GameLogic/Module/StealthUpdate.h"


#define NONE_SPAWNED_YET (0xffffffff)


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif



#define SPAWN_DELAY_MIN_FRAMES (16) // about as rapidly as you'd expect people to successively exit through the same door
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// SpawnBehavior::onDie is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_onDie.cpp (0x0045F7B5).

//-------------------------------------------------------------------------------------------------
// SpawnBehavior::update is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_update.cpp (0x004602F4).

// ------------------------------------------------------------------------------------------------
// ?maySpawnSelfTaskAI@SpawnBehavior@@ present-unmatched
Bool SpawnBehavior::maySpawnSelfTaskAI( Real maxSelfTaskersRatio )
{
	if ( m_spawnCount == 0)
		return FALSE;
	if ( maxSelfTaskersRatio == 0)
		return FALSE;

	
	//if my last attack command was from player or script, I need to forbid my spawn from disobeying that command
	//otherwise (since my attack state was autoacquired my ny own ai), let them deviate by the ratio specified.
	Object* obj = getObject();
	if ( ! obj )
		return FALSE;
	AIUpdateInterface *ai = obj->getAI();
	if ( ! ai )
		return FALSE;
	
	CommandSourceType lastAttackCommandSource = ai->getLastCommandSource();
	

	if ( lastAttackCommandSource != CMD_FROM_AI )
		return FALSE;
	

	Real curSelfTaskersRatio = (Real)m_selfTaskingSpawnCount / (Real)m_spawnCount;

	return ( curSelfTaskersRatio < maxSelfTaskersRatio );
}

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ?orderSlavesDisabledUntil@SpawnBehavior@@ present-unmatched
void SpawnBehavior::orderSlavesDisabledUntil( DisabledType type, UnsignedInt frame )
{
	for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it )
	{
		Object *obj = TheGameLogic->findObjectByID( *it );
		if( obj )
		{
			AIUpdateInterface *ai = obj->getAI();
			if( ai )
			{
				ai->aiIdle( CMD_FROM_AI );
			}
			obj->setDisabledUntil( type, frame );
		}
	}
}

// ------------------------------------------------------------------------------------------------
// ?orderSlavesToClearDisabled@SpawnBehavior@@ present-unmatched
void SpawnBehavior::orderSlavesToClearDisabled( DisabledType type )
{
	for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it )
	{
		Object *obj = TheGameLogic->findObjectByID( *it );
		if( obj )
		{
			obj->clearDisabled( type );
		}
	}
}

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ?giveSlavesStealthUpgrade@SpawnBehavior@@ present-unmatched
void SpawnBehavior::giveSlavesStealthUpgrade( Bool grantStealth )
{
	for( objectIDListIterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it )
	{
		Object *obj = TheGameLogic->findObjectByID( *it );
		if( obj )
		{
			obj->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_CAN_STEALTH ), grantStealth );
		}
	}
}

// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
class OrphanData
{

public:

	OrphanData( void );

	const ThingTemplate *m_matchTemplate;
	Object *m_source;
	Object *m_closest;
	Real m_closestDistSq;

};

#define BIG_DISTANCE 99999999.9f
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?OrphanData::OrphanData present-unmatched
OrphanData::OrphanData( void )
{

	m_matchTemplate = NULL;
	m_source = NULL;
	m_closest = NULL;
	m_closestDistSq = BIG_DISTANCE;

}

// ------------------------------------------------------------------------------------------------
static void findClosestOrphan( Object *obj, void *userData )
{
	OrphanData *orphanData = (OrphanData *)userData;

	// if template doesn't match do nothing
	if( obj->getTemplate()->isEquivalentTo( orphanData->m_matchTemplate ) == FALSE )
		return;

	// this object must be orphaned
	if( obj->getProducerID() != INVALID_ID )
		return;

	// is this the closest one so far
	Real distSq = ThePartitionManager->getDistanceSquared( orphanData->m_source, obj, FROM_CENTER_2D );
	if( distSq < orphanData->m_closestDistSq )
	{
	
		orphanData->m_closest = obj;
		orphanData->m_closestDistSq = distSq;

	}  // end if
			
}  // findClosestOrphan

// ------------------------------------------------------------------------------------------------
// ?reclaimOrphanSpawn@SpawnBehavior@@ present-unmatched
Object *SpawnBehavior::reclaimOrphanSpawn( void )
{
	Player *player = getObject()->getControllingPlayer();
	const SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();

	//
	// iterate all the objects my controlling player has and look for any orphaned things
	// that we would normally spawn, if found we'll just make it our own
	//
	// EVEN MORE NEW AND DIFFERENT
	// This block scans the list for matchTemplates 
	//

	OrphanData orphanData;
	AsciiString prevName = "";
	for (std::vector<AsciiString>::const_iterator tempName = md->m_spawnTemplateNameData.begin();
			tempName != md->m_spawnTemplateNameData.end(); 
			++tempName)
	{
		if (prevName.compare(*tempName)) // the list may have redundancy, this will skip some of it
			continue;
		orphanData.m_matchTemplate = TheThingFactory->findTemplate( *tempName );;
		orphanData.m_source = getObject();
		orphanData.m_closest = NULL;
		orphanData.m_closestDistSq = BIG_DISTANCE;
		player->iterateObjects( findClosestOrphan, &orphanData );
		prevName = *tempName;
	}

	return orphanData.m_closest;
}

//-------------------------------------------------------------------------------------------------
// SpawnBehavior::createSpawn is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_createSpawn.cpp (0x0045FA57).

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ?stopSpawning@SpawnBehavior@@ present-unmatched
void SpawnBehavior::stopSpawning()
{
	m_active = FALSE;
}

//-------------------------------------------------------------------------------------------------
// ?startSpawning@SpawnBehavior@@ present-unmatched
void SpawnBehavior::startSpawning()
{
	m_active = TRUE;
}

//-------------------------------------------------------------------------------------------------
/** When I become damaged */
// ------------------------------------------------------------------------------------------------
// SpawnBehavior::onDamage is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_onDamage.cpp (0x0045FDF3).

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?shouldTryToSpawn@SpawnBehavior@@ present-unmatched
Bool SpawnBehavior::shouldTryToSpawn()
{
	const SpawnBehaviorModuleData *modData = getSpawnBehaviorModuleData();

	// Not if we are turned off
	if( !m_active )
		return FALSE;
	if( getObject()->getStatusBits().test( OBJECT_STATUS_RECONSTRUCTING ) && modData->m_isOneShotData )
	{
		// If we are a Hole rebuild, not only should we not, but we should never ask again.
		stopSpawning();
		return FALSE;
	}
	// Not if we are under construction or being sold
	if( getObject()->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || getObject()->testStatus(OBJECT_STATUS_SOLD) )
		return FALSE;
	// Not if we are civilian controlled
	if( getObject()->isNeutralControlled() )
		return FALSE;

	return TRUE;
}

//********************************************************************
//* This function allows various object states to be either inherited
//* from the spawner to the spawn, or vice versa
//* Selection is distributed across all spawn and spawner at once
//* Health for the spawner is calc'd by aggregating the sum of all
//*   spawn health, and dividing by optimal health of full population
//*   (that is, the max spawn, SpawnBehaviorModuleData::m_spawnNumberData)
//*   at full health.
//* Veterancy is sucked out of any unit that has any and put into the 
//* Spawner, scaled by 1/SpawnBehaviorModuleData::m_spawnNumberData;
//* The HealthBoxPosition (maybe to include moodicon, vet icon) is calc'd
//* as an average position of all the spawn.
//********************************************************************

// SpawnBehavior::computeAggregateStates is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_computeAggregateStates.cpp (0x0045FE9A).

//-------------------------------------------------------------------------------------------------
// ?areAllSlavesStealthed@SpawnBehavior@@ present-unmatched
Bool SpawnBehavior::areAllSlavesStealthed() const
{
	Object *currentSpawn;

	for( std::list<ObjectID>::const_iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		currentSpawn = TheGameLogic->findObjectByID( (*iter) );
		if( currentSpawn )
		{
      const StealthUpdate *stealthUpdate = currentSpawn->getStealth();
			if( !stealthUpdate || !stealthUpdate->allowedToStealth( currentSpawn ) )
			{
				return FALSE;
			}
		}
	}

	return TRUE; //0 or more spawns are ALL stealthed... I suppose if you have NO spawns, then they are considered stealthed ;)
}

//-------------------------------------------------------------------------------------------------
// ?revealSlaves@SpawnBehavior@@ present-unmatched
void SpawnBehavior::revealSlaves()
{
	Object *currentSpawn;

	for( objectIDListIterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		currentSpawn = TheGameLogic->findObjectByID( (*iter) );
		if( currentSpawn )
		{
			StealthUpdate *stealthUpdate = currentSpawn->getStealth();
			if( stealthUpdate )
			{
				stealthUpdate->markAsDetected();
			}
		}
	}
}


// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SpawnBehavior@@ present-unmatched
void SpawnBehavior::crc( Xfer *xfer )
{

	// extend base class
	BehaviorModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?SpawnBehaviorFindAnchor@@YAXXZ present-unmatched
void SpawnBehaviorFindAnchor()
{
	std::list<ObjectID> lst;
	ObjectID v = (ObjectID)0;
	volatile std::list<ObjectID>::iterator it = std::find(lst.begin(), lst.end(), v);
	(void)it;
}
