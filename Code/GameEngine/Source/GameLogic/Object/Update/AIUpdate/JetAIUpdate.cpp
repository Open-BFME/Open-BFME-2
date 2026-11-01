// cl: /Ireference/shims/aiupdatelayout /Ireference/shims/bfme2_locomotor_flags44 /Ireference/shims/partitionfilterzh /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/AIUpdate/JetAIUpdate.cpp); this unit had no counterpart under Code/.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// JetAIUpdate.cpp //////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#define DEFINE_LOCOMOTORSET_NAMES

#include "Common/ActionManager.h"
#include "Common/GlobalData.h"
#include "Common/MiscAudio.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameClient.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/CountermeasuresBehavior.h"
#include "GameLogic/Module/JetAIUpdate.h"
#include "GameLogic/Module/ParkingPlaceBehavior.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/PartitionFilterZh.h"

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

// Reuse the complete byte-verified Coord3D push-back provider at2CE7DC.
// Its declaration suppresses a second template body under this TU flags.
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D&); }

const Real BIGNUM = 99999.0f;

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
enum TaxiType
{
	FROM_HANGAR,
	FROM_PARKING,
	TO_PARKING
};

//-------------------------------------------------------------------------------------------------
enum JetAIStateType
{
	// note that these must be distinct (numerically) from AIStateType. ick.
	JETAISTATETYPE_FIRST = 1000,

	TAXI_FROM_HANGAR,
	TAKING_OFF_AWAIT_CLEARANCE,
	TAXI_TO_TAKEOFF,
	PAUSE_BEFORE_TAKEOFF,
	TAKING_OFF,
	LANDING_AWAIT_CLEARANCE,
	LANDING,
	TAXI_FROM_LANDING,
	ORIENT_FOR_PARKING_PLACE,
	RELOAD_AMMO,
	RETURNING_FOR_LANDING,
	RETURN_TO_DEAD_AIRFIELD,
	CIRCLING_DEAD_AIRFIELD,

	JETAISTATETYPE_LAST
};


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static ParkingPlaceBehaviorInterface* getPP(ObjectID id, Object** airfieldPP = NULL)
{
	if (airfieldPP)
		*airfieldPP = NULL;

	Object* airfield = TheGameLogic->findObjectByID( id );
	if (airfield == NULL || airfield->isEffectivelyDead() || !airfield->isKindOf(KINDOF_FS_AIRFIELD) || airfield->testStatus(OBJECT_STATUS_SOLD))
		return NULL;

	if (airfieldPP)
		*airfieldPP = airfield;

	ParkingPlaceBehaviorInterface* pp = NULL;
	for (BehaviorModule** i = getRetailBehaviorModules(airfield); *i; ++i)
	{
		if ((pp = (*i)->getParkingPlaceBehaviorInterface()) != NULL)
			break;
	}

	return pp;
}

//-------------------------------------------------------------------------------------------------
class PartitionFilterHasParkingPlace : public PartitionFilter
{
private:
	ObjectID m_id;
public:
	PartitionFilterHasParkingPlace(ObjectID id) : m_id(id) { }
protected:
#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterHasParkingPlace"; }
#endif
	virtual Bool allow(Object *objOther)
	{
		ParkingPlaceBehaviorInterface* pp = getPP(objOther->getID());
		if (pp != NULL && pp->reserveSpace(m_id, 0.0f, NULL))
			return true;
		return false;
	}
};

//-------------------------------------------------------------------------------------------------
static Object* findSuitableAirfield(Object* jet)
{
	PartitionFilterAcceptByKindOf					filterKind(MAKE_KINDOF_MASK(KINDOF_FS_AIRFIELD), KINDOFMASK_NONE);
	PartitionFilterRejectByObjectStatus		filterStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_UNDER_CONSTRUCTION ), OBJECT_STATUS_MASK_NONE );
	PartitionFilterRejectByObjectStatus		filterStatusTwo( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_SOLD ), OBJECT_STATUS_MASK_NONE ); // Independent to make it an OR
	PartitionFilterRelationship						filterTeam(jet, PartitionFilterRelationship::ALLOW_ALLIES);
	PartitionFilterAlive									filterAlive;
	PartitionFilterSameMapStatusZh					filterMapStatus(jet);
	PartitionFilterHasParkingPlace				filterPP(jet->getID());

	PartitionFilter *filters[16];
	Int numFilters = 0;
	filters[numFilters++] = &filterKind;
	filters[numFilters++] = &filterStatus;
	filters[numFilters++] = &filterStatusTwo;
	filters[numFilters++] = &filterTeam;
	filters[numFilters++] = &filterAlive;
	filters[numFilters++] = &filterPP;
	filters[numFilters++] = &filterMapStatus;
	filters[numFilters] = NULL;

	return ThePartitionManager->getClosestObject( jet, HUGE_DIST, FROM_CENTER_2D, filters );
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/*
	Success: we have runway clearance
	Failure: no runway clearance
*/
class JetAwaitingRunwayState : public State
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetAwaitingRunwayState, "JetAwaitingRunwayState")		
protected:
	// snapshot interface STUBBED.
	virtual void crc( Xfer *xfer ){};
	virtual void xfer( Xfer *xfer ){XferVersion cv = 1;	XferVersion v = cv; xfer->xferVersion( &v, cv );}
	virtual void loadPostProcess(){};
private:
	const Bool m_landing;

public:
	JetAwaitingRunwayState( StateMachine *machine, Bool landing ) : m_landing(landing), State( machine, "JetAwaitingRunwayState") { }

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;

		jetAI->friend_setTakeoffInProgress(!m_landing);
		jetAI->friend_setLandingInProgress(m_landing);
		jetAI->friend_setAllowCircling(true);
		return STATE_CONTINUE;
	}

	virtual StateReturnType update()
	{
		Object* jet = getMachineOwner();
		if (jet->isEffectivelyDead())
			return STATE_FAILURE;

		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;

		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
		if (pp == NULL)
		{
			// no producer? just skip this step.
			return STATE_SUCCESS;
		}

		// gotta reserve a space in order to reserve a runway
		if (!pp->reserveSpace(jet->getID(), jetAI->friend_getParkingOffset(), NULL))
		{
			DEBUG_ASSERTCRASH(m_landing, ("hmm, this should never happen for taking-off things"));
			return STATE_FAILURE;
		}
		
		if (pp->reserveRunway(jet->getID(), m_landing))
		{
			return STATE_SUCCESS;
		}
		else if( jet->testStatus( OBJECT_STATUS_DECK_HEIGHT_OFFSET ) && !m_landing )
		{
			//If we're trying to take off an aircraft carrier and fail to reserve a 
			//runway, it's because we need to be at the front of the carrier queue.
			//Therefore, we need to move forward whenever possible until we are in
			//the front.
			Coord3D bestPos;
			if( pp->calcBestParkingAssignment( jet->getID(), &bestPos ) )
			{
				jetAI->friend_setTaxiInProgress(true);
				jetAI->friend_setAllowAirLoco(false);
				jetAI->chooseLocomotorSet(LOCOMOTORSET_TAXIING);
				
				jetAI->destroyPath();
				Path *movePath;
				movePath = newInstance(Path);
				Coord3D pos = *jet->getPosition();
				movePath->prependNode( &pos, LAYER_GROUND );
				movePath->markOptimized();
				movePath->appendNode( &bestPos, LAYER_GROUND );

				TheAI->pathfinder()->setDebugPath(movePath);

				jetAI->friend_setPath( movePath );
				DEBUG_ASSERTCRASH(jetAI->getCurLocomotor(), ("no loco"));
				jetAI->getCurLocomotor()->setUsePreciseZPos(true);
				jetAI->getCurLocomotor()->setUltraAccurate(true);
				jetAI->getCurLocomotor()->setAllowInvalidPosition(true);
				jetAI->ignoreObstacleID(jet->getProducerID());
			}
		}

		// can't get a runway? gotta wait.
		jetAI->setLocomotorGoalNone();
		return STATE_CONTINUE;
	}

	virtual void onExit(StateExitType status)
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if (jetAI)
		{
			jetAI->friend_setTakeoffInProgress(false);
			jetAI->friend_setLandingInProgress(false);
			jetAI->friend_setAllowCircling(false);
		}
	}

};
EMPTY_DTOR(JetAwaitingRunwayState)

//-------------------------------------------------------------------------------------------------
/*
	Success: a new suitable airfield has appeared
	Failure: shouldn't normally happen
*/
class JetOrHeliCirclingDeadAirfieldState : public State
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetOrHeliCirclingDeadAirfieldState, "JetOrHeliCirclingDeadAirfieldState")		
protected:
	// snapshot interface	 STUBBED.
	// The state will check immediately after a load game, but I think that's ok.  jba.
	virtual void crc( Xfer *xfer ){};
	virtual void xfer( Xfer *xfer ){XferVersion cv = 1;	XferVersion v = cv; xfer->xferVersion( &v, cv );}
	virtual void loadPostProcess(){};

private:
	Int m_checkAirfield;

	enum
	{
		// only recheck for new airfields every second or so
		HOW_OFTEN_TO_CHECK = LOGICFRAMES_PER_SECOND
	};

public:
	JetOrHeliCirclingDeadAirfieldState( StateMachine *machine ) : 
		State( machine, "JetOrHeliCirclingDeadAirfieldState"),
		m_checkAirfield(0) { }

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
		{
			return STATE_FAILURE;
		}
		
		// obscure case: if the jet wasn't spawned, but just placed directly on the map,
		// it might not have an owning airfield, and it might be trying to return
		// simply due to being idle, not out of ammo. so check and don't die in that
		// case, but just punt back out to idle.
		if (!jetAI->isOutOfSpecialReloadAmmo() && jet->getProducerID() == INVALID_ID)
		{
			return STATE_FAILURE;
		}

		// just stay where we are.
		jetAI->setLocomotorGoalNone();

		m_checkAirfield = HOW_OFTEN_TO_CHECK;

		//Play the "low fuel" voice whenever the craft is circling above the airfield.
		AudioEventRTS soundToPlay = *jet->getTemplate()->getPerUnitSound( "VoiceLowFuel" );
		soundToPlay.setObjectID( jet->getID() );
		TheAudio->addAudioEvent( &soundToPlay );

		return STATE_CONTINUE;
	}

	virtual StateReturnType update()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
		{
			return STATE_FAILURE;
		}

		// just stay where we are.
		jetAI->setLocomotorGoalNone();
		
		Real damageRate = jetAI->friend_getOutOfAmmoDamagePerSecond();
		if (damageRate > 0)
		{
			// convert to damage/sec to damage/frame
			damageRate *= SECONDS_PER_LOGICFRAME_REAL;
			// since it's a percentage, multiply times the max health
			damageRate *= getRetailBodyModule(jet)->getMaxHealth();

			DamageInfo damageInfo;
			damageInfo.in.m_damageType = DAMAGE_UNRESISTABLE;
			damageInfo.in.m_deathType = DEATH_NORMAL;
			damageInfo.in.m_sourceID = INVALID_ID;
			damageInfo.in.m_amount = damageRate;
			jet->attemptDamage( &damageInfo );
		}

		if (--m_checkAirfield <= 0)
		{
			m_checkAirfield = HOW_OFTEN_TO_CHECK;
			Object* airfield = findSuitableAirfield( jet );
			if (airfield)
			{
				jet->setProducer(airfield);
				return STATE_SUCCESS;
			}
		}

		return STATE_CONTINUE;
	}

};
EMPTY_DTOR(JetOrHeliCirclingDeadAirfieldState)

//-------------------------------------------------------------------------------------------------
/*
	Success: we returned to the dead-airfield location
	Failure: shouldn't normally happen
*/
class JetOrHeliReturningToDeadAirfieldState : public AIInternalMoveToState
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetOrHeliReturningToDeadAirfieldState, "JetOrHeliReturningToDeadAirfieldState")		
public:
	JetOrHeliReturningToDeadAirfieldState( StateMachine *machine ) : AIInternalMoveToState( machine, "JetOrHeliReturningToDeadAirfieldState") { }

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
		{
			return STATE_FAILURE;
		}

		setAdjustsDestination(true);
		m_goalPosition = *jetAI->friend_getProducerLocation();

		return AIInternalMoveToState::onEnter();
	}

};
EMPTY_DTOR(JetOrHeliReturningToDeadAirfieldState)

//-------------------------------------------------------------------------------------------------
// This solution uses the 
// http://www.faqs.org/faqs/graphics/algorithms-faq/ 
// Subject 1.03
static Bool intersectInfiniteLine2D
(
	Real ax, Real ay, Real ao, 
	Real cx, Real cy, Real co, 
	Real& ix, Real& iy
)
{
	Real bx = ax + Cos(ao);
	Real by = ay + Sin(ao);
	Real dx = cx + Cos(co);
	Real dy = cy + Sin(co);

	Real denom = ((bx - ax) * (dy - cy) - (by - ay) * (dx - cx));
	if (denom == 0.0f) 
	{
		// the lines are parallel.
		return false;
	}

	// The lines intersect.
	Real r = ((ay - cy) * (dx - cx) - (ax - cx) * (dy - cy) ) / denom;
	ix = ax + r * (bx - ax);
	iy = ay + r * (by - ay);
	return true;
}

//-------------------------------------------------------------------------------------------------
/*
	Success: we are on the ground at the runway start
	Failure: we are unable to get on the ground
*/
class JetOrHeliTaxiState : public AIMoveOutOfTheWayState 
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetOrHeliTaxiState, "JetOrHeliTaxiState")		
private:
	TaxiType m_taxiMode;
public:
	JetOrHeliTaxiState( StateMachine *machine, TaxiType m ) : m_taxiMode(m), AIMoveOutOfTheWayState( machine ) { }

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;
		
		jetAI->setCanPathThroughUnits(true);
		jetAI->friend_setTakeoffInProgress(m_taxiMode != TO_PARKING);
		jetAI->friend_setLandingInProgress(m_taxiMode == TO_PARKING);
		jetAI->friend_setTaxiInProgress(true);
		
		if( m_taxiMode == TO_PARKING )
		{
			//Instantly reload flares.
			CountermeasuresBehaviorInterface *cbi = jet->getCountermeasuresBehaviorInterface();
			if( cbi )
			{
				cbi->reloadCountermeasures();
			}
		}

		jetAI->friend_setAllowAirLoco(false);
		jetAI->chooseLocomotorSet(LOCOMOTORSET_TAXIING);
		DEBUG_ASSERTCRASH(jetAI->getCurLocomotor(), ("no loco"));

		Object* airfield;
		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID(), &airfield);
		if (pp == NULL)
			return STATE_SUCCESS;	// no airfield? just skip this step.
		
		ParkingPlaceBehaviorInterface::PPInfo ppinfo;
		if (!pp->reserveSpace(jet->getID(), jetAI->friend_getParkingOffset(), &ppinfo))
			return STATE_FAILURE;	// full?
		
		Coord3D intermedPt;
		Bool intermed = false;
		Real orient = atan2(ppinfo.runwayPrep.y - ppinfo.parkingSpace.y, ppinfo.runwayPrep.x - ppinfo.parkingSpace.x);
		if (fabs(stdAngleDiff(orient, ppinfo.parkingOrientation)) > PI/128)
		{
			intermedPt.z = (ppinfo.parkingSpace.z + ppinfo.runwayPrep.z) * 0.5f;
			intermed = intersectInfiniteLine2D(
				ppinfo.parkingSpace.x, ppinfo.parkingSpace.y, ppinfo.parkingOrientation,
				ppinfo.runwayPrep.x, ppinfo.runwayPrep.y, ppinfo.parkingOrientation + PI/2,
				intermedPt.x, intermedPt.y);
		}

		jetAI->destroyPath();
		Path *movePath;
		movePath = newInstance(Path);
		Coord3D pos = *jet->getPosition();
		movePath->prependNode( &pos, LAYER_GROUND );
		movePath->markOptimized();

		if (m_taxiMode == TO_PARKING)
		{
			if( jet->testStatus( OBJECT_STATUS_DECK_HEIGHT_OFFSET ) )
			{
				//We're on an aircraft carrier.
				const std::vector<Coord3D> *pTaxiLocations = pp->getTaxiLocations( jet->getID() );
				if( pTaxiLocations )
				{
					std::vector<Coord3D>::const_iterator it;
					for( it = pTaxiLocations->begin(); it != pTaxiLocations->end(); it++ )
					{
						movePath->appendNode( it, LAYER_GROUND );
					}
				}

				//We just landed... see if we can get a better space forward so we don't stop and pause 
				//at our initially assigned spot.
				Coord3D pos;
				pp->calcBestParkingAssignment( jet->getID(), &pos );

				movePath->appendNode( &pos, LAYER_GROUND );
			}
			else
			{
				//We're on a normal airfield
				movePath->appendNode( &ppinfo.runwayPrep, LAYER_GROUND );
				if (intermed)
					movePath->appendNode( &intermedPt, LAYER_GROUND );
				movePath->appendNode( &ppinfo.parkingSpace, LAYER_GROUND );
			}
		}
		else if (m_taxiMode == FROM_PARKING)
		{
			if( jet->testStatus( OBJECT_STATUS_DECK_HEIGHT_OFFSET ) )
			{
				if( !(ppinfo.runwayStart == ppinfo.runwayPrep) )	
				{
					movePath->appendNode( &ppinfo.runwayStart, LAYER_GROUND );
				}
			}
			else
			{
				if (intermed)
					movePath->appendNode( &intermedPt, LAYER_GROUND );
				movePath->appendNode( &ppinfo.runwayPrep, LAYER_GROUND );
				movePath->appendNode( &ppinfo.runwayStart, LAYER_GROUND );
			}
		}
		else if (m_taxiMode == FROM_HANGAR)
		{
			if( jet->testStatus( OBJECT_STATUS_DECK_HEIGHT_OFFSET ) )
			{
				//Aircraft carrier
				if( jet->testStatus( OBJECT_STATUS_REASSIGN_PARKING ) )
				{
					//This status means we are being reassigned a parking space. We're not actually moving from the
					//hangar. So simply move to the new parking spot which was just switched from under us in
					//FlightDeckBehavior::update()
					jet->clearStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_REASSIGN_PARKING ) );
					movePath->appendNode( &ppinfo.runwayPrep, LAYER_GROUND );
				}
				else
				{
					const std::vector<Coord3D> *pCreationLocations = pp->getCreationLocations( jet->getID() );
					if( !pCreationLocations )
					{
						DEBUG_CRASH( ("No creation locations specified for runway for JetAIBehavior -- taxiing from hanger (Kris).") );
						return STATE_FAILURE;
					}
					std::vector<Coord3D>::const_iterator it;
					Bool firstNode = TRUE;
					for( it = pCreationLocations->begin(); it != pCreationLocations->end(); it++ )
					{
						if( firstNode )
						{
							//Skip the first node because it's the creation location.
							firstNode = FALSE;
							continue;
						}
						movePath->appendNode( it, LAYER_GROUND );
					}
					movePath->appendNode( &ppinfo.runwayPrep, LAYER_GROUND );
				}
			}
			else
			{
				//Airfield
 				movePath->appendNode( &ppinfo.parkingSpace, LAYER_GROUND );
			}
		}

		m_waitingForPath = FALSE;	 
		TheAI->pathfinder()->setDebugPath(movePath);

		setAdjustsDestination(false);	// precision is necessary

		jetAI->friend_setPath( movePath );
		DEBUG_ASSERTCRASH(jetAI->getCurLocomotor(), ("no loco"));
		jetAI->getCurLocomotor()->setUsePreciseZPos(true);
		jetAI->getCurLocomotor()->setUltraAccurate(true);
		jetAI->getCurLocomotor()->setAllowInvalidPosition(true);
		jetAI->ignoreObstacleID(jet->getProducerID());

		StateReturnType ret = AIMoveOutOfTheWayState::onEnter();
		return ret;
	}

	virtual StateReturnType update()
	{
		Object* jet = getMachineOwner();
		if (jet->isEffectivelyDead())
			return STATE_FAILURE;

		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;

		if( m_taxiMode == TO_PARKING || m_taxiMode == FROM_HANGAR )
		{
			//Keep checking to see if there is a better spot as it moves forward. If we find a better spot, then
			//append the position to our move.
			ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
			Coord3D bestPos;
			Int oldIndex, newIndex;
			// Check pp for null, as it is possible for your airfield to get destroyed while taxiing.jba [8/27/2003]
			if( pp!=NULL && pp->calcBestParkingAssignment( jet->getID(), &bestPos, &oldIndex, &newIndex ) )
			{
				Path *path = jetAI->friend_getPath();
				if( path )
				{
					path->appendNode( &bestPos, LAYER_GROUND );
				}
			}
		}

		return AIMoveOutOfTheWayState::update();
	}

	virtual void onExit( StateExitType status )
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if (jetAI)
		{
			jetAI->getCurLocomotor()->setUsePreciseZPos(false);
			jetAI->getCurLocomotor()->setUltraAccurate(false);
			jetAI->getCurLocomotor()->setAllowInvalidPosition(false);
			jetAI->friend_setTakeoffInProgress(false);
			jetAI->friend_setLandingInProgress(false);
			jetAI->friend_setTaxiInProgress(false);
			jetAI->setCanPathThroughUnits(false);
		}

		AIMoveOutOfTheWayState::onExit(status);
	}

};
EMPTY_DTOR(JetOrHeliTaxiState)

//-------------------------------------------------------------------------------------------------
/*
	Success: we are on the ground at the runway start
	Failure: we are unable to get on the ground
*/
class JetTakeoffOrLandingState : public AIFollowPathState 
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetTakeoffOrLandingState, "JetTakeoffOrLandingState")		
private:
	Real			m_maxLift;
	Real			m_maxSpeed;
#ifdef CIRCLE_FOR_LANDING
	Coord3D		m_circleForLandingPos;
#endif
	Bool			m_landing;
	Bool			m_landingSoundPlayed;

public:
	JetTakeoffOrLandingState( StateMachine *machine, Bool landing ) : m_landing(landing), AIFollowPathState( machine, "JetTakeoffOrLandingState" ) { }

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if (!jetAI)
			return STATE_FAILURE;

		if (jet->isEffectivelyDead())
			return STATE_FAILURE;

		jetAI->friend_setTakeoffInProgress(!m_landing);
		jetAI->friend_setLandingInProgress(m_landing);
		jetAI->friend_setAllowAirLoco(true);
		jetAI->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
		Locomotor* loco = jetAI->getCurLocomotor();
		DEBUG_ASSERTCRASH(loco, ("no loco"));
		loco->setMaxLift(BIGNUM);
		BodyDamageType bdt = getRetailBodyModule(jet)->getDamageState();
		m_maxLift = loco->getMaxLift(bdt);
		m_maxSpeed = loco->getMaxSpeedForCondition(bdt);
		m_landingSoundPlayed = FALSE;
		if (m_landing)
		{
			loco->setMaxSpeed(loco->getMinSpeed());
		}
		else
		{
			loco->setMaxLift(0);
		}
		loco->setUsePreciseZPos(true);
		loco->setUltraAccurate(true);
		jetAI->ignoreObstacleID(jet->getProducerID());

		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
		if (pp == NULL)
			return STATE_SUCCESS;	// no airfield? just skip this step
		
		ParkingPlaceBehaviorInterface::PPInfo ppinfo;
		if (!pp->reserveSpace(jet->getID(), jetAI->friend_getParkingOffset(), &ppinfo))
		{
			// it's full.
			return STATE_FAILURE;
		}
		
		// only check this for landing; we might have already given up the reservation to the guy behind us for takeoff
		if (m_landing)
		{
			if (!pp->reserveRunway(jet->getID(), m_landing))
			{
				DEBUG_CRASH(("we should never get to this state unless we have a runway available"));
				return STATE_FAILURE;
			}
		}
		
		std::vector<Coord3D> path;
		if (m_landing)
		{
#ifdef CIRCLE_FOR_LANDING
			m_circleForLandingPos = ppinfo.runwayApproach;
			m_circleForLandingPos.z = (ppinfo.runwayEnd.z + ppinfo.runwayApproach.z)*0.5f;
#else
			path.push_back(ppinfo.runwayApproach);
#endif
			if( jet->testStatus( OBJECT_STATUS_DECK_HEIGHT_OFFSET ) )
			{
				//Assigned to an aircraft carrier which has separate landing strips.
				path.push_back( ppinfo.runwayLandingStart );
				path.push_back( ppinfo.runwayLandingEnd );
			}
			else
			{
				//Assigned to an airstrip -- land the same way we took off but in reverse.
				path.push_back(ppinfo.runwayEnd);
				path.push_back(ppinfo.runwayStart);
			}
		}
		else
		{
			ppinfo.runwayEnd.z = ppinfo.runwayApproach.z;
			path.push_back(ppinfo.runwayEnd);
			path.push_back(ppinfo.runwayExit);
		}

		setAdjustsDestination(false);	// precision is necessary
		setAdjustFinalDestination(false); // especially at the endpoint!

		jetAI->friend_setGoalPath( &path );

		StateReturnType ret = AIFollowPathState::onEnter();
		
		return ret;
	}

	virtual StateReturnType update()
	{
		Object* jet = getMachineOwner();
		if (jet->isEffectivelyDead())
			return STATE_FAILURE;

		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;
		
		if (m_landing)
		{
#ifdef CIRCLE_FOR_LANDING
			if (jet->getPosition()->z > m_circleForLandingPos.z)
			{
				const Real THRESH = 4.0f;
				jetAI->getCurLocomotor()->setAltitudeChangeThresholdForCircling(THRESH);
				jetAI->setLocomotorGoalPositionExplicit(m_circleForLandingPos);
				return STATE_CONTINUE;
			}
			else
#endif
			{
				jetAI->getCurLocomotor()->setMaxLift(BIGNUM);
#ifdef CIRCLE_FOR_LANDING
				jetAI->getCurLocomotor()->setAltitudeChangeThresholdForCircling(0);
#endif
			}

			if( !m_landingSoundPlayed )
			{
				ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
				Real zPos = jet->getPosition()->z;
				Real zSlop = 0.25f;
				PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination( jet->getPosition() );
				Real groundZ = TheTerrainLogic->getLayerHeight( jet->getPosition()->x, jet->getPosition()->y, layer );
				if( pp )
				{
					groundZ += pp->getLandingDeckHeightOffset();
				}
				
				if( zPos - zSlop <= groundZ )
				{
					m_landingSoundPlayed = TRUE;
					AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_aircraftWheelScreech;	
					soundToPlay.setPosition( jet->getPosition() );
					TheAudio->addAudioEvent( &soundToPlay );
				}
			}
		}
		else
		{
			ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
			if (pp)
				pp->transferRunwayReservationToNextInLineForTakeoff(jet->getID());

			//Calculate the distance of the jet from the end of the runway as a ratio from the start.
			//As it approaches the end of the runway, the plane will gain more lift, even if it's already
			//going quickly. Using speed for lift is bad in the case of the aircraft carrier, because
			//we don't want it to take off quickly.
			ParkingPlaceBehaviorInterface::PPInfo ppinfo;
			pp->calcPPInfo( jet->getID(), &ppinfo );
			Coord3D vector = ppinfo.runwayEnd;
			vector.sub( jet->getPosition() );
			Real dist = vector.length();
			
			Real ratio = 1.0f - (dist / ppinfo.runwayTakeoffDist);
			ratio *= ratio; //dampen it....
			if (ratio < 0.0f) ratio = 0.0f;
			if (ratio > 1.0f) ratio = 1.0f;
			jetAI->getCurLocomotor()->setMaxLift(m_maxLift * ratio);
		}

		StateReturnType ret = AIFollowPathState::update();
		return ret;
	}

	virtual void onExit( StateExitType status )
	{
		AIFollowPathState::onExit(status);

		// just in case.
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return;

		jetAI->friend_setTakeoffInProgress(false);
		jetAI->friend_setLandingInProgress(false);
		jetAI->friend_enableAfterburners(false);

		// Paranoia checks - sometimes onExit is called when we are 
		// shutting down, and not all pieces are valid.  CurLocomotor
		// is definitely null in some cases. jba.
		Locomotor* loco = jetAI->getCurLocomotor();
		if (loco)
		{
			loco->setUsePreciseZPos(false);
			loco->setUltraAccurate(false);
			// don't restore lift if dead -- this may fight with JetSlowDeathBehavior!
			if (!jet->isEffectivelyDead())
				loco->setMaxLift(BIGNUM);
#ifdef CIRCLE_FOR_LANDING
			loco->setAltitudeChangeThresholdForCircling(0);
#endif
		}
		jetAI->ignoreObstacleID(INVALID_ID);
		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
		if (!m_landing)
		{
			if (pp && !jetAI->friend_keepsParkingSpaceWhenAirborne())
				pp->releaseSpace(jet->getID());
		}
		if (pp)
			pp->releaseRunway(jet->getID());
	}
};
EMPTY_DTOR(JetTakeoffOrLandingState)

//-------------------------------------------------------------------------------------------------
static Real calcDistSqr(const Coord3D& a, const Coord3D& b)
{
	return sqr(a.x-b.x) + sqr(a.y-b.y) + sqr(a.z-b.z);
}

//-------------------------------------------------------------------------------------------------
/*
	Success: we are on the ground at the runway start
	Failure: we are unable to get on the ground
*/
class HeliTakeoffOrLandingState : public State 
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(HeliTakeoffOrLandingState, "HeliTakeoffOrLandingState")		
protected:
	// snapshot interface
	virtual void crc( Xfer *xfer )
	{
		// empty. jba.
	}

	virtual void xfer( Xfer *xfer )
	{
		// version
		XferVersion currentVersion = 1;
		XferVersion version = currentVersion;
		xfer->xferVersion( &version, currentVersion );

		// set on create. xfer->xferBool(&m_landing);
		xfer->xferCoord3D(&m_path[0]);
		xfer->xferCoord3D(&m_path[1]);
		xfer->xferInt(&m_index);
		xfer->xferCoord3D(&m_parkingLoc);
		xfer->xferReal(&m_parkingOrientation);
	}
	virtual void loadPostProcess()
	{
		// empty. jba.
	}

private:
	Coord3D		m_path[2];
	Int				m_index;
	Coord3D		m_parkingLoc;
	Real			m_parkingOrientation;
	Bool			m_landing;
public:
	HeliTakeoffOrLandingState( StateMachine *machine, Bool landing ) : m_landing(landing), 
		State( machine, "HeliTakeoffOrLandingState" ), m_index(0)
		{ 
			m_parkingLoc.zero();
		}

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;

		jetAI->friend_setTakeoffInProgress(!m_landing);
		jetAI->friend_setLandingInProgress(m_landing);
		jetAI->friend_setAllowAirLoco(true);
		jetAI->chooseLocomotorSet(LOCOMOTORSET_NORMAL);

		Locomotor* loco = jetAI->getCurLocomotor();
		DEBUG_ASSERTCRASH(loco, ("no loco"));
		loco->setUsePreciseZPos(true);
		loco->setUltraAccurate(true);
		jetAI->ignoreObstacleID(jet->getProducerID());

		Object* airfield;
		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID(), &airfield);
		if (pp == NULL)
			return STATE_SUCCESS;	// no airfield? just skip this step
		
		Coord3D landingApproach;
		if (jet->isKindOf(KINDOF_PRODUCED_AT_HELIPAD))
		{
			if (m_landing)
			{
				m_parkingLoc = jetAI->friend_getLandingPosForHelipadStuff();
				m_parkingOrientation = jet->getOrientation();
			}
			else
			{
				m_parkingOrientation = jet->getOrientation();
				m_parkingLoc = *jet->getPosition();
			}
			landingApproach = m_parkingLoc;
			landingApproach.z += pp->getApproachHeight() + pp->getLandingDeckHeightOffset();
		}
		else
		{
			ParkingPlaceBehaviorInterface::PPInfo ppinfo;
			if (!pp->reserveSpace(jet->getID(), jetAI->friend_getParkingOffset(), &ppinfo))
				return STATE_FAILURE;
			m_parkingLoc = ppinfo.parkingSpace;
			m_parkingOrientation = ppinfo.parkingOrientation;
			landingApproach = m_parkingLoc;
			landingApproach.z += (ppinfo.runwayApproach.z - ppinfo.runwayEnd.z);
		}
		
		if (m_landing)
		{
			m_path[0] = landingApproach;
			m_path[1] = m_parkingLoc;
		}
		else
		{
			m_path[0] = m_parkingLoc;
			m_path[1] = landingApproach;
			m_path[1].z = landingApproach.z;
		}
		m_index = 0;

		return STATE_CONTINUE;
	}

	virtual StateReturnType update()
	{
		Object* jet = getMachineOwner();
		if (jet->isEffectivelyDead())
			return STATE_FAILURE;

		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;

// I have disabled this because it is no longer necessary and is a bit funky lookin' (srj)
#ifdef NOT_IN_USE
		// magically position it correctly.
		jet->getPhysics()->scrubVelocity2D(0);
		Coord3D hoverloc = m_path[m_index];
		hoverloc.z = jet->getPosition()->z;
#if 1
		Coord3D pos = *jet->getPosition();
		Real dx = hoverloc.x - pos.x;
		Real dy = hoverloc.y - pos.y;
		Real dSqr = dx*dx+dy*dy;
		const Real DARN_CLOSE = 0.25f;
		if (dSqr < DARN_CLOSE) 
		{
			jet->setPosition(&hoverloc);
		} 
		else 
		{
			Real dist = sqrtf(dSqr);
			if (dist<1) dist = 1;
			pos.x += PATHFIND_CELL_SIZE_F*dx/(dist*LOGICFRAMES_PER_SECOND);
			pos.y += PATHFIND_CELL_SIZE_F*dy/(dist*LOGICFRAMES_PER_SECOND);
			jet->setPosition(&pos);
		}
#else
		jet->setPosition(&hoverloc);
#endif
		jet->setOrientation(m_parkingOrientation);
#endif

		if (jet->isKindOf(KINDOF_PRODUCED_AT_HELIPAD) || !m_landing)
		{
			TheAI->pathfinder()->adjustDestination(jet, jetAI->getLocomotorSet(), &m_path[m_index]);
			TheAI->pathfinder()->updateGoal(jet, &m_path[m_index], LAYER_GROUND);
		}

		jetAI->setLocomotorGoalPositionExplicit(m_path[m_index]);

		const Real THRESH = 3.0f;
		const Real THRESH_SQR = THRESH*THRESH;
		const Coord3D* a = jet->getPosition();
		const Coord3D* b = &m_path[m_index];
		Real distSqr = calcDistSqr(*a, *b);
		if (distSqr <= THRESH_SQR)
			++m_index;
		
		if (m_index >= 2)
			return STATE_SUCCESS;

		return STATE_CONTINUE;
	}

	virtual void onExit( StateExitType status )
	{
		// just in case.
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return;

		jetAI->friend_setTakeoffInProgress(false);
		jetAI->friend_setLandingInProgress(false);

		// Paranoia checks - sometimes onExit is called when we are 
		// shutting down, and not all pieces are valid.  CurLocomotor
		// is definitely null in some cases. jba.
		Locomotor* loco = jetAI->getCurLocomotor();
		if (loco)
		{
			loco->setUsePreciseZPos(false);
			loco->setUltraAccurate(false);
			// don't restore lift if dead -- this may fight with JetSlowDeathBehavior!
			if (!jet->isEffectivelyDead())
				loco->setMaxLift(BIGNUM);
		}

		jetAI->ignoreObstacleID(INVALID_ID);
		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
		if (m_landing)
		{
			jetAI->friend_setAllowAirLoco(false);
			jetAI->chooseLocomotorSet(LOCOMOTORSET_TAXIING);
		}
		else
		{
			if (pp && !jetAI->friend_keepsParkingSpaceWhenAirborne())
				pp->releaseSpace(jet->getID());
		}
	}

};
EMPTY_DTOR(HeliTakeoffOrLandingState)

//-------------------------------------------------------------------------------------------------
class JetOrHeliParkOrientState : public State
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetOrHeliParkOrientState, "JetOrHeliParkOrientState")		
protected:
	// snapshot interface STUBBED.
	virtual void crc( Xfer *xfer ){};
	virtual void xfer( Xfer *xfer ){XferVersion cv = 1;	XferVersion v = cv; xfer->xferVersion( &v, cv );}
	virtual void loadPostProcess(){};

public:
	JetOrHeliParkOrientState( StateMachine *machine ) : State( machine, "JetOrHeliParkOrientState") { }

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;

		if (jet->isKindOf(KINDOF_PRODUCED_AT_HELIPAD))
		{
			return STATE_SUCCESS;
		}

		jetAI->friend_setTakeoffInProgress(false);
		jetAI->friend_setLandingInProgress(true);

		jetAI->ignoreObstacleID(jet->getProducerID());
		return STATE_CONTINUE;
	}

	virtual StateReturnType update()
	{
		Object* jet = getMachineOwner();
		if (jet->isEffectivelyDead())
			return STATE_FAILURE;

		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
		{
			return STATE_FAILURE;
		}

		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
		if (pp == NULL)
			return STATE_FAILURE;
		
		ParkingPlaceBehaviorInterface::PPInfo ppinfo;
		if (!pp->reserveSpace(jet->getID(), jetAI->friend_getParkingOffset(), &ppinfo))
			return STATE_FAILURE;

		const Real THRESH = 0.001f;
		if (fabs(stdAngleDiff(jet->getOrientation(), ppinfo.parkingOrientation)) <= THRESH)
			return STATE_SUCCESS;

		// magically position it correctly.
		jet->getPhysics()->scrubVelocity2D(0);
		Coord3D hoverloc = ppinfo.parkingSpace;
		if( jet->testStatus( OBJECT_STATUS_DECK_HEIGHT_OFFSET ) )
		{
			hoverloc = ppinfo.runwayPrep;
		}

		hoverloc.z = jet->getPosition()->z;
		jet->setPosition(&hoverloc);

		jetAI->setLocomotorGoalOrientation(ppinfo.parkingOrientation);

		return STATE_CONTINUE;
	}

	virtual void onExit( StateExitType status )
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return;

		jetAI->friend_setTakeoffInProgress(false);
		jetAI->friend_setLandingInProgress(false);
		jetAI->ignoreObstacleID(INVALID_ID);
	}
};
EMPTY_DTOR(JetOrHeliParkOrientState)

//-------------------------------------------------------------------------------------------------
class JetPauseBeforeTakeoffState : public AIFaceState
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetPauseBeforeTakeoffState, "JetPauseBeforeTakeoffState")		
protected:
	// snapshot interface
	virtual void crc( Xfer *xfer )
	{
		// empty. jba.
	}

	virtual void xfer( Xfer *xfer )
	{
		// version
		XferVersion currentVersion = 1;
		XferVersion version = currentVersion;
		xfer->xferVersion( &version, currentVersion );

		// set on create. xfer->xferBool(&m_landing);
		xfer->xferUnsignedInt(&m_when);
		xfer->xferUnsignedInt(&m_whenTransfer);
		xfer->xferBool(&m_afterburners);
		xfer->xferBool(&m_resetTimer);
		xfer->xferObjectID(&m_waitedForTaxiID);
	}
	virtual void loadPostProcess()
	{
		// empty. jba.
	}

private:
	UnsignedInt		m_when;
	UnsignedInt		m_whenTransfer;
	ObjectID			m_waitedForTaxiID;
	Bool					m_resetTimer;
	Bool					m_afterburners;

	Bool findWaiter()
	{
		Object* jet = getMachineOwner();
		ParkingPlaceBehaviorInterface* pp = getPP(getMachineOwner()->getProducerID());
		if (pp)
		{
			Int count = pp->getRunwayCount();
			for (Int i = 0; i < count; ++i)
			{
				Object* otherJet = TheGameLogic->findObjectByID( pp->getRunwayReservation( i, RESERVATION_TAKEOFF ) );
				if (otherJet == NULL || otherJet == jet)
					continue;

				AIUpdateInterface* ai = otherJet->getAIUpdateInterface();
				if (ai == NULL)
					continue;

				if (ai->getCurrentStateID() == TAXI_TO_TAKEOFF)
				{
					if (m_waitedForTaxiID == INVALID_ID)
					{
						m_waitedForTaxiID = otherJet->getID();
					}
					return true;
				}
			}
		}
		return false;
	}

public:
	JetPauseBeforeTakeoffState( StateMachine *machine ) : 
		AIFaceState(machine, false), 
		m_when(0), 
		m_whenTransfer(0),
		m_waitedForTaxiID(INVALID_ID), 
		m_resetTimer(false),
		m_afterburners(false) 
	{ 
		// nothing
	}

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;

		jetAI->friend_setTakeoffInProgress(true);
		jetAI->friend_setLandingInProgress(false);

		m_when = 0;
		m_whenTransfer = 0;
		m_waitedForTaxiID = INVALID_ID;
		m_resetTimer = false;
		m_afterburners = false;

		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
		if (pp == NULL)
			return STATE_SUCCESS;	// no airfield? just skip this step.
		
		ParkingPlaceBehaviorInterface::PPInfo ppinfo;
		if (!pp->reserveSpace(jet->getID(), jetAI->friend_getParkingOffset(), &ppinfo))
			return STATE_SUCCESS;	// full?

		getMachine()->setGoalPosition(&ppinfo.runwayEnd);
		
		return AIFaceState::onEnter();
	}

	virtual StateReturnType update()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if (jet->isEffectivelyDead())
			return STATE_FAILURE;

		// always call this.
		StateReturnType superStatus = AIFaceState::update();
		
		if (findWaiter())
			return STATE_CONTINUE;

		UnsignedInt now = TheGameLogic->getFrame();
		if (!m_resetTimer)
		{
			// we had to wait, but now everyone else is ready, so restart our countdown.
			m_when = now + jetAI->friend_getTakeoffPause();
			if (m_waitedForTaxiID == INVALID_ID)
			{
				m_waitedForTaxiID = jet->getID();	// just so we don't pick up anyone else
				m_whenTransfer = now + 1;	
			}
			else
			{
				m_whenTransfer = now + 2;	// 2 seems odd, but is correct
			}
			m_resetTimer = true;
		}

		if (!m_afterburners)
		{
			jetAI->friend_enableAfterburners(true);
			m_afterburners = true;
		}

		DEBUG_ASSERTCRASH(m_when != 0, ("hmm"));
		DEBUG_ASSERTCRASH(m_whenTransfer != 0, ("hmm"));

			// once we start the final wait, release the runways for guys behind us, so they can start taxiing
		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
		if (pp && now >= m_whenTransfer)
		{
			pp->transferRunwayReservationToNextInLineForTakeoff(jet->getID());
		}

		if (now >= m_when)
			return superStatus;

		return STATE_CONTINUE;
	}

	virtual void onExit(StateExitType status)
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		jetAI->friend_setTakeoffInProgress(false);
		jetAI->friend_setLandingInProgress(false);
		AIFaceState::onExit(status);
	}

};
EMPTY_DTOR(JetPauseBeforeTakeoffState)

//-------------------------------------------------------------------------------------------------
class JetOrHeliReloadAmmoState : public State
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetOrHeliReloadAmmoState, "JetOrHeliReloadAmmoState")		
private:
	UnsignedInt		m_reloadTime;
	UnsignedInt		m_reloadDoneFrame;

protected:

	// snapshot interface
	virtual void crc( Xfer *xfer )
	{
		// empty. jba.
	}

	virtual void xfer( Xfer *xfer )
	{
		// version
		XferVersion currentVersion = 1;
		XferVersion version = currentVersion;
		xfer->xferVersion( &version, currentVersion );

		// set on create. xfer->xferBool(&m_landing);
		xfer->xferUnsignedInt(&m_reloadTime);
		xfer->xferUnsignedInt(&m_reloadDoneFrame);
	}
	virtual void loadPostProcess()
	{
		// empty. jba.
	}

public:
	JetOrHeliReloadAmmoState( StateMachine *machine ) : State( machine, "JetOrHeliReloadAmmoState") { }

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		if( !jetAI )
			return STATE_FAILURE;

		jetAI->friend_setTakeoffInProgress(false);
		jetAI->friend_setLandingInProgress(false);
		jetAI->friend_setUseSpecialReturnLoco(false);
		
		m_reloadTime = 0;
		for (Int i = 0; i < WEAPONSLOT_COUNT;	++i)
		{
			const Weapon* weapon = jet->getWeaponInWeaponSlot((WeaponSlotType)i);
			if (weapon == NULL)
				continue;
			
			Int remaining = weapon->getRemainingAmmo();
			Int clipSize = weapon->getClipSize();
			Int rt = weapon->getClipReloadTime(jet);
			if (clipSize > 0)
			{
				// bias by amount empty.
				Int needed = clipSize - remaining;
				rt = (rt * needed) / clipSize;
			}
			if (rt > m_reloadTime)
				m_reloadTime = rt;
		}
		
		if (m_reloadTime < 1)
			m_reloadTime = 1;
		m_reloadDoneFrame = m_reloadTime + TheGameLogic->getFrame();
		return STATE_CONTINUE;
	}

	virtual StateReturnType update()
	{
		Object* jet = getMachineOwner();
		UnsignedInt now = TheGameLogic->getFrame();
		Bool allDone = true;
		for (Int i = 0; i < WEAPONSLOT_COUNT;	++i)
		{
			Weapon* weapon = jet->getWeaponInWeaponSlot((WeaponSlotType)i);
			if (weapon == NULL)
				continue;
			
			if (now >= m_reloadDoneFrame)
				weapon->setClipPercentFull(1.0f, false);
			else
				weapon->setClipPercentFull((Real)(m_reloadTime - (m_reloadDoneFrame - now)) / m_reloadTime, false);

			if (weapon->getRemainingAmmo() != weapon->getClipSize())
				allDone = false;
		}

		if (allDone)
			return STATE_SUCCESS;

		return STATE_CONTINUE;
	}

	virtual void onExit(StateExitType status)
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();
		jetAI->friend_setTakeoffInProgress(false);
		jetAI->friend_setLandingInProgress(false);
	}

};
EMPTY_DTOR(JetOrHeliReloadAmmoState)

//-------------------------------------------------------------------------------------------------
/*
	Success: we are close enough to a friendly airfield to land
	Failure: we are unable to get close enough to a friendly airfield to land
*/
class JetOrHeliReturnForLandingState : public AIInternalMoveToState
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(JetOrHeliReturnForLandingState, "JetOrHeliReturnForLandingState")		
public:
	JetOrHeliReturnForLandingState( StateMachine *machine ) : AIInternalMoveToState( machine, "JetOrHeliReturnForLandingState") { }

	virtual StateReturnType onEnter()
	{
		Object* jet = getMachineOwner();
		JetAIUpdate* jetAI = (JetAIUpdate*)jet->getAIUpdateInterface();

		ParkingPlaceBehaviorInterface* pp = getPP(jet->getProducerID());
		if (pp == NULL)
		{
			// nuke the producer id, since it's dead
			jet->setProducer(NULL);

			Object* airfield = findSuitableAirfield( jet );
			pp = airfield ? getPP(airfield->getID()) : NULL;
			if (airfield && pp)
			{
				jet->setProducer(airfield);
			}
			else
			{
				return STATE_FAILURE;
			}
		}
		
		if (jet->isKindOf(KINDOF_PRODUCED_AT_HELIPAD))
		{
			m_goalPosition = jetAI->friend_getLandingPosForHelipadStuff();
		}
		else
		{
			ParkingPlaceBehaviorInterface::PPInfo ppinfo;
			if (!pp->reserveSpace(jet->getID(), jetAI->friend_getParkingOffset(), &ppinfo))
				return STATE_FAILURE;

			m_goalPosition = jetAI->friend_needsRunway() ? ppinfo.runwayApproach : ppinfo.parkingSpace;
		}
		setAdjustsDestination(false);		// precision is necessary

		return AIInternalMoveToState::onEnter();
	}
};
EMPTY_DTOR(JetOrHeliReturnForLandingState)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class JetAIStateMachine : public AIStateMachine
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( JetAIStateMachine, "JetAIStateMachine" );

public:
	JetAIStateMachine( Object *owner, AsciiString name );

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class HeliAIStateMachine : public AIStateMachine
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( HeliAIStateMachine, "HeliAIStateMachine" );

public:
	HeliAIStateMachine( Object *owner, AsciiString name );

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/INI/ini_parsers.cpp
//-------------------------------------------------------------------------------------------------
/*static*/ void JetAIUpdateModuleData::buildFieldParse(MultiIniFieldParse& multiIniFieldParse) 
{
  AIUpdateModuleData::buildFieldParse(multiIniFieldParse);

	static const FieldParse dataFieldParse[] = 
	{
		{ "OutOfAmmoDamagePerSecond",			INI::parsePercentToReal, NULL, offsetof( JetAIUpdateModuleData, m_outOfAmmoDamagePerSecond ) },
		{ "NeedsRunway",									INI::parseBool, NULL, offsetof( JetAIUpdateModuleData, m_needsRunway ) },
		{ "KeepsParkingSpaceWhenAirborne",INI::parseBool, NULL, offsetof( JetAIUpdateModuleData, m_keepsParkingSpaceWhenAirborne ) },
		{ "TakeoffDistForMaxLift",				INI::parsePercentToReal, NULL, offsetof( JetAIUpdateModuleData, m_takeoffDistForMaxLift ) },
		{ "TakeoffPause",									INI::parseDurationUnsignedInt, NULL, offsetof( JetAIUpdateModuleData, m_takeoffPause ) },
		{ "MinHeight",										INI::parseReal, NULL, offsetof( JetAIUpdateModuleData, m_minHeight ) },
		{ "ParkingOffset",								INI::parseReal, NULL, offsetof( JetAIUpdateModuleData, m_parkingOffset ) },
		{ "SneakyOffsetWhenAttacking",		INI::parseReal, NULL, offsetof( JetAIUpdateModuleData, m_sneakyOffsetWhenAttacking ) },
		{ "AttackLocomotorType",					INI::parseIndexList, TheLocomotorSetNames, offsetof( JetAIUpdateModuleData, m_attackingLoco ) },
		{ "AttackLocomotorPersistTime",		INI::parseDurationUnsignedInt, NULL, offsetof( JetAIUpdateModuleData, m_attackLocoPersistTime ) },
		{ "AttackersMissPersistTime",			INI::parseDurationUnsignedInt, NULL, offsetof( JetAIUpdateModuleData, m_attackersMissPersistTime ) },
		{ "ReturnForAmmoLocomotorType",		INI::parseIndexList, TheLocomotorSetNames, offsetof( JetAIUpdateModuleData, m_returningLoco ) },
		{ "LockonTime",										INI::parseDurationUnsignedInt, NULL, offsetof( JetAIUpdateModuleData, m_lockonTime ) },
		{ "LockonCursor",									INI::parseAsciiString, NULL, offsetof( JetAIUpdateModuleData, m_lockonCursor ) },
		{ "LockonInitialDist",						INI::parseReal, NULL, offsetof( JetAIUpdateModuleData, m_lockonInitialDist ) },
		{ "LockonFreq",										INI::parseReal, NULL, offsetof( JetAIUpdateModuleData, m_lockonFreq ) },
		{ "LockonAngleSpin",							INI::parseAngleReal, NULL, offsetof( JetAIUpdateModuleData, m_lockonAngleSpin ) },
		{ "LockonBlinky",									INI::parseBool, NULL, offsetof( JetAIUpdateModuleData, m_lockonBlinky ) },
		{ "ReturnToBaseIdleTime",					INI::parseDurationUnsignedInt, NULL, offsetof( JetAIUpdateModuleData, m_returnToBaseIdleTime ) },
		{ 0, 0, 0, 0 }
	};
  multiIniFieldParse.add(dataFieldParse);
}

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
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?update@JetAIUpdate@@ present-unmatched
// Retail's AIUpdateInterface::isWaitingForPath reads +0x1E9 (7B body
// 8A81E9010000C3 measured in AIUpdate.cpp's object, which shares this unit's
// copy); this unit's header copy differs from the 8-copy majority, and both
// minority objects sort ahead of it in link order (L on 8 units). This read
// goes straight at the member instead of odr-using the ZH inline, whose
// COMDAT would otherwise displace the majority copy.
static Bool bfmeJetWaitingForPath(const AIUpdateInterface *ai)
{
	return *(const Bool *)((const char *)ai + 0x1E9);
}
UpdateSleepTime JetAIUpdate::update()
{
	const JetAIUpdateModuleData* jetAIUpdateModuleData = getJetAIUpdateModuleData();

	getProducerLocation();

	Object* jet = getObject();

	ParkingPlaceBehaviorInterface* pp = getPP(getObject()->getProducerID());

	// If idle & out of ammo, return
	// have to call our parent's isIdle, because we override it to never return true
	// when we have a pending command...
	UnsignedInt now = TheGameLogic->getFrame();

	// srj sez: not 100% sure on this. calling RELOAD_AMMO "idle" allows us to get healed while reloading,
	// but might have other side effects we didn't want. if this does prove to cause a bug, be sure
	// that jets (and ESPECIALLY comanches) are still getting healed at airfields.
	if (AIUpdateInterface::isIdle() || getStateMachine()->getCurrentStateID() == RELOAD_AMMO)
	{
		if (pp != NULL)
		{
			if (!getFlag(ALLOW_AIR_LOCO) && 
					!getFlag(HAS_PENDING_COMMAND) &&
						jet->isKindOf(KINDOF_PRODUCED_AT_HELIPAD) &&
						getRetailBodyModule(jet)->getHealth() == getRetailBodyModule(jet)->getMaxHealth())
			{
				// we're completely healed, so take off again
				pp->setHealee(jet, false);
				friend_setAllowAirLoco(true);
				getStateMachine()->clear();
				setLastCommandSource( CMD_FROM_AI );
				getStateMachine()->setState( TAKING_OFF_AWAIT_CLEARANCE );
			}
			else
			{
				pp->setHealee(jet, !getFlag(ALLOW_AIR_LOCO));
			}
		}

		// note that we might still have weapons with ammo, but still be forced to return to reload.
		if (isOutOfSpecialReloadAmmo() && getFlag(ALLOW_AIR_LOCO))
		{
			m_returnToBaseFrame = 0;

			// this is really a "just-in-case" to ensure the targeter list doesn't spin out of control (srj)
			pruneDeadTargeters();

			setFlag(USE_SPECIAL_RETURN_LOCO, true);
			setLastCommandSource( CMD_FROM_AI );
			getStateMachine()->setState(RETURNING_FOR_LANDING);
		}
		else if (getFlag(HAS_PENDING_COMMAND) 
			// srj sez: if we are reloading ammo, wait will we are done before processing the pending command.
			&& getStateMachine()->getCurrentStateID() != RELOAD_AMMO)
		{
			m_returnToBaseFrame = 0;

			AICommandParms parms(AICMD_MOVE_TO_POSITION, CMD_FROM_AI);	// values don't matter, will be wiped by next line
			m_mostRecentCommand.reconstitute(parms);
			setFlag(HAS_PENDING_COMMAND, false);

 			aiDoCommand(&parms);
		}
		else if (m_returnToBaseFrame != 0 && now >= m_returnToBaseFrame && getFlag(ALLOW_AIR_LOCO))
		{
			m_returnToBaseFrame = 0;
			DEBUG_ASSERTCRASH(isOutOfSpecialReloadAmmo() == false, ("Hmm, this seems unlikely -- isOutOfSpecialReloadAmmo()==false"));
			setFlag(USE_SPECIAL_RETURN_LOCO, false);
			setLastCommandSource( CMD_FROM_AI );
			getStateMachine()->setState(RETURNING_FOR_LANDING);
		}
		else if (m_returnToBaseFrame  == 0 && jetAIUpdateModuleData->m_returnToBaseIdleTime > 0 && getFlag(ALLOW_AIR_LOCO))
		{
			m_returnToBaseFrame = now + jetAIUpdateModuleData->m_returnToBaseIdleTime;
		}
	}
	else
	{
		if (pp != NULL)
		{
			pp->setHealee(getObject(), false);
		}
		m_returnToBaseFrame = 0;
		if (getFlag(ALLOW_INTERRUPT_AND_RESUME_OF_CUR_STATE_FOR_RELOAD) && 
						isOutOfSpecialReloadAmmo() && getFlag(ALLOW_AIR_LOCO))
		{
			setFlag(USE_SPECIAL_RETURN_LOCO, true);
			setFlag(HAS_PENDING_COMMAND, true);
			setFlag(ALLOW_INTERRUPT_AND_RESUME_OF_CUR_STATE_FOR_RELOAD, false);
			setLastCommandSource( CMD_FROM_AI );
			getStateMachine()->setState(RETURNING_FOR_LANDING);
		}
	}

	Real minHeight = friend_getMinHeight();
	if( pp )
	{
		minHeight += pp->getLandingDeckHeightOffset();
	}

	Drawable* draw = jet->getDrawable();
	if (draw != NULL)
	{
		StateID id = getStateMachine()->getCurrentStateID();
		Bool needToCheckMinHeight = (id >= JETAISTATETYPE_FIRST && id <= JETAISTATETYPE_LAST) || 
																	!jet->isAboveTerrain() ||
																	!getFlag(ALLOW_AIR_LOCO);
		if( needToCheckMinHeight || jet->getStatusBits().test( OBJECT_STATUS_DECK_HEIGHT_OFFSET ) )
		{
			Real ht = jet->isAboveTerrain() ? jet->getHeightAboveTerrain() : 0;
			if (ht < minHeight)
			{
				Matrix3D tmp(1);
				tmp.Set_Z_Translation(minHeight - ht);
				draw->setInstanceMatrix(&tmp);
			}
			else
			{
				draw->setInstanceMatrix(NULL);
			}
		}
		else
		{
			draw->setInstanceMatrix(NULL);
		}
	}

	PhysicsBehavior* physics = jet->getPhysics();
	if (physics->getVelocityMagnitude() > 0 && getFlag(ALLOW_AIR_LOCO))
		jet->setModelConditionState(MODELCONDITION_JETEXHAUST);
	else
		jet->clearModelConditionState(MODELCONDITION_JETEXHAUST);

	if (jet->testStatus(OBJECT_STATUS_IS_ATTACKING))
	{
		m_attackLocoExpireFrame = now + jetAIUpdateModuleData->m_attackLocoPersistTime;
		m_attackersMissExpireFrame = now + jetAIUpdateModuleData->m_attackersMissPersistTime;
	}
	else
	{
		if (m_attackLocoExpireFrame != 0 && now >= m_attackLocoExpireFrame)
		{
			m_attackLocoExpireFrame = 0;
		}
		if (m_attackersMissExpireFrame != 0 && now >= m_attackersMissExpireFrame)
		{
			m_attackersMissExpireFrame = 0;
		}
	}

	if (m_untargetableExpireFrame != 0 && now >= m_untargetableExpireFrame)
	{
		m_untargetableExpireFrame = 0;
	}

	positionLockon();
	
	if (m_attackLocoExpireFrame != 0)
	{
		chooseLocomotorSet(jetAIUpdateModuleData->m_attackingLoco);
	}
	else if (getFlag(USE_SPECIAL_RETURN_LOCO))
	{
		chooseLocomotorSet(jetAIUpdateModuleData->m_returningLoco);
	}

	
	if( !jet->isKindOf( KINDOF_PRODUCED_AT_HELIPAD ) )
	{
		Drawable *draw = jet->getDrawable();
		if( draw )
		{
			if( getFlag(TAKEOFF_IN_PROGRESS) 
					|| getFlag(LANDING_IN_PROGRESS) 
					|| getObject()->isSignificantlyAboveTerrain() 
					|| isMoving() 
					|| bfmeJetWaitingForPath(this) )
			{
				if( !m_enginesOn )
				{
					//We just started moving, therefore turn on the engines!			
					draw->enableAmbientSound( TRUE );
					m_enginesOn = TRUE;
				}
			}
			else if( m_enginesOn )
			{
				//We're no longer moving, so turn off the engines!
				draw->enableAmbientSound( FALSE );
				m_enginesOn = FALSE;
			}
		}
	}


	/*UpdateSleepTime ret =*/ AIUpdateInterface::update();
	//return (mine < ret) ? mine : ret;
	/// @todo srj -- someday, make sleepy. for now, must not sleep.
	return UPDATE_SLEEP_NONE;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
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