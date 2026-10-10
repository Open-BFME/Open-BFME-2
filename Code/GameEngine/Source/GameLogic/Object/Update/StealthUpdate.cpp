// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp); this unit had no counterpart under Code/.
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

// FILE: StealthUpdate.cpp ////////////////////////////////////////////////////////////////////////
// Author: Kris Morness, May 2002
// Desc:	 An update that checks for a status bit to stealth the owning object
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

#define DEFINE_STEALTHLEVEL_NAMES
#define DEFINE_OBJECT_STATUS_NAMES

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/GameState.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Radar.h"
#include "Common/Team.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Xfer.h"

#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/GameClient.h"
#include "GameClient/Eva.h"

#include "GameLogic/Damage.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/SpawnBehavior.h"

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


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// StealthUpdateModuleData ctor/dtor/buildFieldParse live in their rowed units
// (StealthUpdateModuleDataCtor.cpp, StealthUpdateModuleDataDtor.cpp,
// ModuleDataBuildFieldParse.cpp); this file merely declares them via
// GameLogic/Module/StealthUpdate.h.
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_ctor_Thunk.cpp
// ??0StealthUpdate@@ present-unmatched
StealthUpdate::StealthUpdate( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();

	m_stealthAllowedFrame = TheGameLogic->getFrame() + data->m_stealthDelay;

	//Must be enabled manually if using disguise system (bomb truck uses)
	m_enabled = !data->m_teamDisguised;

	//Added By Sadullah Nader
	//Initialization(s) inserted
	m_detectionExpiresFrame = 0;
	//
	m_pulsePhaseRate		= 0.2f;
	m_pulsePhase				= GameClientRandomValueReal(0, PI);

	m_disguiseAsPlayerIndex			= -1;
	m_disguiseAsTemplate			  = NULL;
	m_transitioningToDisguise		= false;
	m_disguised									= false;
	m_disguiseTransitionFrames	= 0;
	m_disguiseHalfpointReached  = false;
	m_nextBlackMarketCheckFrame = 0;
	m_framesGranted = 0;
	
	if( data->m_innateStealth )
	{
		//Giving innate stealth units this status bit allows other code to easily check the status bit.
		getObject()->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_CAN_STEALTH ) );
	}

	// start active, since some stealths start enabled from the get-go
  if ( data->m_grantedBySpecialPower )
	  setWakeFrame( getObject(), UPDATE_SLEEP_FOREVER );
  else
	  setWakeFrame( getObject(), UPDATE_SLEEP_NONE );

	// we do not need to restore a disguise
	m_xferRestoreDisguise = FALSE;

} 

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/StealthUpdateDestructorThunk.cpp
// ??1StealthUpdate@@ present-unmatched
StealthUpdate::~StealthUpdate( void )
{

}

//-------------------------------------------------------------------------------------------------
void isBlackMarket( Object *obj, void *userData )
{
	if( obj && obj->isKindOf( KINDOF_FS_BLACK_MARKET ) )
	{
		if( obj->isEffectivelyDead() )
		{
			return;
		}
		if( obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) )
		{
			return;
		}
		if( obj->testStatus( OBJECT_STATUS_SOLD ) )
		{
			return;
		}
		*(Bool*)userData = TRUE;
	}
}

//---------------------------------------------------------------------------------------~-_-~-_-~-
// ?receiveGrant@StealthUpdate@@ present-unmatched
void StealthUpdate::receiveGrant( Bool active, UnsignedInt frames )
{
  Object *obj = getObject();
  if ( obj == NULL )
    return;

  if (this->canDisguise())
    return; //so bombtrucks and stuff do not get foiled by this.

	//Kris: Turn it off if we pass in FALSE for active.
	if( !active && m_enabled )
	{
		//markAsDetected();
	}

	m_enabled = active;

	if( m_enabled )
	{
		//On
		obj->setStatus( MAKE_OBJECT_STATUS_MASK2( OBJECT_STATUS_CAN_STEALTH, OBJECT_STATUS_STEALTHED ) );
		m_stealthAllowedFrame = TheGameLogic->getFrame();
	  setWakeFrame( obj, UPDATE_SLEEP_NONE );
		m_framesGranted = frames;
	}
	else
	{
		//Off
		obj->clearStatus( MAKE_OBJECT_STATUS_MASK2( OBJECT_STATUS_CAN_STEALTH, OBJECT_STATUS_STEALTHED ) );
		m_stealthAllowedFrame = FOREVER;
		m_framesGranted = 0;
		Drawable *draw = obj->getDrawable();
		if( draw )
		{
			draw->setEffectiveOpacity( 1.0f );
		}
	}

  const ContainModuleInterface *contain = getRetailContain(obj);
  if ( contain && contain->isRiderChangeContain() )
  {
    const Object *rider = contain->friend_getRider(); 
    if ( rider )
    {
      StealthUpdate *riderStealth = rider->getStealth();
      if ( riderStealth )
        riderStealth->receiveGrant( active, frames );
    }
  }



}


//-------------------------------------------------------------------------------------------------
// ?allowedToStealth@StealthUpdate@@ present-unmatched
Bool StealthUpdate::allowedToStealth( Object *stealthOwner ) const
{
	const Object *self = getObject();
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();
	UnsignedInt now = TheGameLogic->getFrame();

	UnsignedInt flags = data->m_stealthLevel;
	if( self != stealthOwner )
	{
		//Extract the rules from the rider's stealthupdate module data instead
		//of our own, because the rider determines if the container can stealth or not.

    const StealthUpdate *stealthUpdate = stealthOwner->getStealth();
		if( stealthUpdate )
		{
			flags = stealthUpdate->getStealthLevel();
		}
	}

	//With regards to slaves that stealth with us, we need to all be stealthed or not at all. If
	//any of the slaves can't stealth, then reveal everyone!
	if( self->isKindOf( KINDOF_SPAWNS_ARE_THE_WEAPONS ) )
	{
		SpawnBehaviorInterface *sbInterface = self->getSpawnBehaviorInterface();
		if( sbInterface )
		{
			if( !sbInterface->areAllSlavesStealthed() )
			{
				sbInterface->revealSlaves();
				return FALSE;
			}
		}
	}

	if( flags & STEALTH_NOT_WHILE_ATTACKING && self->getStatusBits().test( OBJECT_STATUS_IS_FIRING_WEAPON ) )
	{
		//Doesn't stealth while aggressive (includes approaching).
		return FALSE;
	}
	
	if( flags & STEALTH_NOT_WHILE_USING_ABILITY && self->getStatusBits().test( OBJECT_STATUS_IS_USING_ABILITY ) )
	{
		//Doesn't stealth while using a special ability (starting with preparation, which takes place after unpacking).
		return FALSE;
	}
	
	if( flags & STEALTH_ONLY_WITH_BLACK_MARKET && m_nextBlackMarketCheckFrame < now )
	{
		//randomize timer a little incase we have a whole bunch on the same frame.
		m_nextBlackMarketCheckFrame += data->m_blackMarketCheckFrames + GameLogicRandomValue( 0, 10 ); 
		
		//If we can't find an active black market, then we can't stealth.
		Bool blackMarket = FALSE;
		self->getControllingPlayer()->iterateObjects( isBlackMarket, &blackMarket );
		if( !blackMarket )
		{
			return FALSE;
		}
	}

	if( !stealthOwner->getStatusBits().test( OBJECT_STATUS_CAN_STEALTH ) )
	{
		return FALSE;
	}
	
	if( flags & STEALTH_NOT_WHILE_TAKING_DAMAGE && getRetailBodyModule(self)->getLastDamageTimestamp() >= now - 1 )
	{
		//Only if it's not healing damage.
		if( getRetailBodyModule(self)->getLastDamageInfo()->in.m_damageType != DAMAGE_HEALING )
		{
			//Can't stealth if we just took damage in the last frame or two.
			if( getRetailBodyModule(self)->getLastDamageTimestamp() != 0xffffffff )
			{
				//But it's initialized to 0xffffffff so we don't think we took damage on the first frame. 
				return FALSE;
			}
		}
	}

	//We need all required status or else we fail
	// If we have any requirements
	if( data->m_requiredStatus.any()  &&  !self->getStatusBits().testForAll( data->m_requiredStatus ) )
		return FALSE; 

	//If we have any forbidden statii, then fail
	if( self->getStatusBits().testForAny( data->m_forbiddenStatus ) )
		return FALSE; 


	//Do a quick preliminary test to see if we are restricted by firing particular weapons and we fired a shot last frame or this frame.
	if( flags & STEALTH_NOT_WHILE_FIRING_WEAPON && self->getStatusBits().test( OBJECT_STATUS_IS_FIRING_WEAPON ) )
	{
		if( (flags & STEALTH_NOT_WHILE_FIRING_WEAPON) == STEALTH_NOT_WHILE_FIRING_WEAPON )
		{
			//Not allowed to stealth while firing ANY weapon!
			return FALSE;
		}

		//Now do weapon specific checks.
		Weapon *weapon;
		UnsignedInt lastFrame = TheGameLogic->getFrame() - 1;

		if( flags & STEALTH_NOT_WHILE_FIRING_PRIMARY )
		{
			//Check primary weapon status
			weapon = self->getWeaponInWeaponSlot( PRIMARY_WEAPON );
			if( weapon && weapon->getLastShotFrame() >= lastFrame )
			{
				return FALSE;
			}
		}
		if( flags & STEALTH_NOT_WHILE_FIRING_SECONDARY )
		{
			//Check secondary weapon status
			weapon = self->getWeaponInWeaponSlot( SECONDARY_WEAPON );
			if( weapon && weapon->getLastShotFrame() >= lastFrame )
			{
				return FALSE;
			}
		}
		if( flags & STEALTH_NOT_WHILE_FIRING_TERTIARY )
		{
			//Check tertiary weapon status
			weapon = self->getWeaponInWeaponSlot( TERTIARY_WEAPON );
			if( weapon && weapon->getLastShotFrame() >= lastFrame )
			{
				return FALSE;
			}
		}
	}

	const Object *containedBy = self->getContainedBy();
	if( containedBy )
	{
		ContainModuleInterface *contain = getRetailContain(containedBy);
		if( contain && !contain->isGarrisonable() )
		{
			return FALSE;
		}
	}

  //new past-alpha feature, grr...
	if( flags & STEALTH_NOT_WHILE_RIDERS_ATTACKING )
	{
    ContainModuleInterface *myContain = getRetailContain(self);
    if ( myContain && myContain->isPassengerAllowedToFire() )
    {
      if ( myContain->isAnyRiderAttacking() )
        return FALSE;

    }
  }



	const PhysicsBehavior *physics = self->getPhysics();
	if ((flags & STEALTH_NOT_WHILE_MOVING) && physics != NULL && 
					physics->getVelocityMagnitude() > getStealthUpdateModuleData()->m_stealthSpeed)
		return FALSE;
	
	if( self->testScriptStatusBit(OBJECT_STATUS_SCRIPT_UNSTEALTHED))
	{
		//We can't stealth because a script disabled this ability for this object!
		return FALSE;
	}

	return TRUE;
}


//---------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ?hintDetectableWhileUnstealthed@StealthUpdate@@ present-unmatched
void StealthUpdate::hintDetectableWhileUnstealthed() 
{
	Object *self = getObject();
	const StealthUpdateModuleData *md = getStealthUpdateModuleData();

	if( self && md->m_hintDetectableStates.testForAny( self->getStatusBits() ) )
	{
		if ( self->getControllingPlayer() == ThePlayerList->getLocalPlayer() )
		{
			Drawable *selfDraw = self->getDrawable();
			if ( selfDraw )
				selfDraw->setSecondMaterialPassOpacity( 1.0f );
		}
	}
}



//-------------------------------------------------------------------------------


// ?getFriendlyOpacity@StealthUpdate@@ present-unmatched
Real StealthUpdate::getFriendlyOpacity() const
{
	return getStealthUpdateModuleData()->m_friendlyOpacityMin; 
}


//=============================================================================
// indicate how the given unit is "stealthed" with respect to a given player.
// ?calcStealthedStatusForPlayer@StealthUpdate@@ present-unmatched
StealthLookType StealthUpdate::calcStealthedStatusForPlayer(const Object* obj, const Player* player)
{
	/*
		for stealthy things, there are these distinct "logical" states:

		-- not stealthed at all (ie, totally visible)
		-- stealthed 
		-- stealthed-but-detected

		and the following visual states:

		-- normal (n)
		-- invisible (i)
		-- stealthed-but-visible-to-friendly-folks (sv)
		-- stealthed-but-visible-to-everyone-due-to-being-detected (sd)

		Let's be ubergeeks and make a matrix of the possibilities:
				
								Ally		Nonally
		normal:			(n)			(n)
		stealthed:	(sv)		(i)
		detected:		(sd)		(sd)


		Or, to put it another way:

		If normal, you always appear normal.
		If stealthed (and not detected), you appear as (sv) to allies and (i) to others. 
		If detected, you always appears as (sd).

		Sorry, there is one more condition, stealthed, but visible to friendly folks, YET detected
		In this state we render outselves visible and we ovlerlay the detection effect as a warning
		we'll call this STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED


	*/
	

	if (obj->isEffectivelyDead())
		return STEALTHLOOK_NONE;			// making sure he turns visible when he dies

	if( obj->getStatusBits().test( OBJECT_STATUS_STEALTHED ) )
	{
		const Team* team = obj->getTeam();
		Relationship r = team ? team->getRelationship(player->getDefaultTeam()) : NEUTRAL;
		if( !player->isPlayerActive() )
		{
			//Observer players are friends to everyone!
			r = ALLIES;
		}

// srj sez: disguised stuff doesn't work well when combined with the normal "detected" stuff.
// so special case it here.
		if (canDisguise())
		{
			if (r != ALLIES && isDisguised())
				return STEALTHLOOK_DISGUISED_ENEMY;
			else
				return STEALTHLOOK_NONE;
		}

		if( obj->getStatusBits().test( OBJECT_STATUS_DETECTED ) )			// we're detected.
		{
			if (r == ALLIES)// if we're friendly to the given player, detection DOES matter though.
				return STEALTHLOOK_VISIBLE_FRIENDLY_DETECTED;
			else
				return STEALTHLOOK_VISIBLE_DETECTED;
		}
		else
		{
			if (r == ALLIES)
			{
				// if we're friendly to the given player, detection doesn't matter.
				return STEALTHLOOK_VISIBLE_FRIENDLY;
			}
			else
			{
// srj sez: disguised stuff doesn't work well when combined with the normal "detected" stuff.
// so special case it above.
//				if( getStealthUpdateModuleData()->m_teamDisguised )
//				{
//					return STEALTHLOOK_DISGUISED_ENEMY;
//				}
				// we're effectively hidden.
				return STEALTHLOOK_INVISIBLE;
			}
		}
	}
	else
	{
		return STEALTHLOOK_NONE;
	}
}

//-------------------------------------------------------------------------------------------------
// ?calcStealthOwner@StealthUpdate@@ present-unmatched
Object* StealthUpdate::calcStealthOwner()
{
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();
	//If we are going to use the rider for stealth rules, then we need to separate the
	//rider and the container. The rider will determine if the container is stealthed or
	//not.
	if( data->m_useRiderStealth )
	{
		//We're actually going to logically check the rider as the stealth owner, but the
		//stealth effects will go on the container.
		ContainModuleInterface *contain = getRetailContain(getObject());
		if( contain )
		{
			const ContainedItemsList *riderList = contain->getContainedItemsList();
			ContainedItemsList::const_iterator riderIterator;
			riderIterator = riderList->begin();
			if( riderIterator != riderList->end() )
			{
				//Return this rider!
				return *riderIterator;
			}
		}
	}
	//Not applicable, return ourself.
	return getObject();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?StealthUpdate::calcSleepTime present-unmatched
UpdateSleepTime StealthUpdate::calcSleepTime() const
{
	return m_enabled ? UPDATE_SLEEP_NONE : UPDATE_SLEEP_FOREVER;
}

//-------------------------------------------------------------------------------------------------
/** The update callback. */
//-------------------------------------------------------------------------------------------------
// The exact update body is owned by StealthUpdateLogic.cpp.

//-------------------------------------------------------------------------------------------------
void setWakeupIfInRange( Object *obj, void *userData)
{
	Object *victim = (Object *)userData;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai) {
		return;
	}

	Real vision = obj->getVisionRange();

	Coord3D srcpos = *obj->getPosition();
	Coord3D dstpos = *victim->getPosition();

	srcpos.sub(&dstpos);
	if (srcpos.length() > vision)
		return;

	ai->wakeUpAndAttemptToTarget();

//	if( obj->isKindOf( KINDOF_SELECTABLE ) && ( obj->isAbleToAttack() || !obj->isKindOf( KINDOF_STRUCTURE ) )) {
//		Drawable *draw = obj->getDrawable();
//		if( draw ) {
//			draw->setEmoticon( "Emoticon_Alarm", 5000 );
//		}
//	}
}


//-------------------------------------------------------------------------------------------------
// ?markAsDetected@StealthUpdate@@ present-unmatched
void StealthUpdate::markAsDetected(UnsignedInt numFrames)
{
	Object *self = getObject();
	Object *stealthOwner = calcStealthOwner();

	UnsignedInt stealthDelay, orderIdlesToAttack;
	if( self == stealthOwner )
	{
		const StealthUpdateModuleData *data = getStealthUpdateModuleData();
		//Use the standard module data information (because we stealth ourself)
		stealthDelay = data->m_stealthDelay;
		orderIdlesToAttack = data->m_orderIdleEnemiesToAttackMeUponReveal;
	}
	else
	{
		//Extract the rules from the rider's stealthupdate module data instead
		//of our own, because the rider determines if the container can stealth or not.
    const StealthUpdate *stealthUpdate = stealthOwner->getStealth();
		if( stealthUpdate )
		{
			stealthDelay = stealthUpdate->getStealthDelay();
			orderIdlesToAttack = stealthUpdate->getOrderIdleEnemiesToAttackMeUponReveal();
		}
	}


	Player *thisPlayer = self->getControllingPlayer();

	//If we are disguised, remove the disguise permanently!
	if( isDisguised() )
	{
		disguiseAsObject( NULL );
	}

	UnsignedInt now = TheGameLogic->getFrame();
	if( !numFrames )
	{
		//Kris:
		//If numFrames is zero (the default value), use the stealth delay specified in the ini file.
		m_detectionExpiresFrame = now + stealthDelay;
	}
	else if ( m_detectionExpiresFrame < now + numFrames )
	{
		m_detectionExpiresFrame = now + numFrames;
	}

	if( orderIdlesToAttack )
	{
		// This can't be a partitionmanager thing, because we need to know which objects can see
		// us. Therefore, walk the play list, and for each player that considers us an enemy, 
		// check if any of their units can see us.

		Int numPlayers = ThePlayerList->getPlayerCount();
		for (Int n = 0; n < numPlayers; ++n)
		{

			Player *player = ThePlayerList->getNthPlayer(n);
			if (!player)
				continue;

			if (player->getRelationship(thisPlayer->getDefaultTeam()) != ENEMIES)
				continue;

			player->iterateObjects(setWakeupIfInRange, self);
		}
	}
}

//-------------------------------------------------------------------------------------------------
// The exact disguise body is owned by StealthUpdateLogic.cpp.

// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdateChangeVisualDisguiseThunk.cpp
// ?changeVisualDisguise@StealthUpdate@@ present-unmatched
void StealthUpdate::changeVisualDisguise()
{
	Object *self = getObject();
	const StealthUpdateModuleData *data = getStealthUpdateModuleData();

	Drawable *draw = self->getDrawable();
	// We need to maintain our selection across the un/disguise, so pull selected out here.
	Bool selected = draw->isSelected();

	if( m_disguiseAsTemplate )
	{
		Player *player = ThePlayerList->getNthPlayer( m_disguiseAsPlayerIndex );

		ModelConditionFlags flags = draw->getModelConditionFlags();
		
		//Get rid of the old instance!
		TheGameClient->destroyDrawable( draw );

		draw = TheThingFactory->newDrawable( m_disguiseAsTemplate );
		if( draw )
		{
			TheGameLogic->bindObjectAndDrawable(self, draw);
			draw->setPosition( self->getPosition() );
			draw->setOrientation( self->getOrientation() );
			draw->setModelConditionFlags( flags );
			draw->updateDrawable();
			self->getPhysics()->resetDynamicPhysics();
			if( selected )
			{
				TheInGameUI->selectDrawable( draw );
			}
			Player *clientPlayer = ThePlayerList->getLocalPlayer();
			if( self->getControllingPlayer()->getRelationship( clientPlayer->getDefaultTeam() ) != ALLIES && clientPlayer->isPlayerActive() )
			{
				//Neutrals and enemies will see this disguised unit as the team it's disguised as.
				if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
					draw->setIndicatorColor( player->getPlayerNightColor() );
				else
					draw->setIndicatorColor( player->getPlayerColor() );
			}
			else
			{
				//If it's on our team or our ally's team, then show it's true colors.
				if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
					draw->setIndicatorColor( self->getNightIndicatorColor() );
				else
					draw->setIndicatorColor( self->getIndicatorColor() );
			}
		}

		//Play a disguise sound!
		AudioEventRTS sound = *self->getTemplate()->getPerUnitSound( "DisguiseStarted" );
		sound.setObjectID( self->getID() );
		TheAudio->addAudioEvent( &sound );

		FXList::doFXPos( data->m_disguiseFX, self->getPosition() );

		m_disguised = true;
		self->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_DISGUISED ) );
		self->setModelConditionState( MODELCONDITION_DISGUISED );

		//33) Did the player ever build a "disguisable" unit and never used the disguise ability?
		self->getControllingPlayer()->getAcademyStats()->recordVehicleDisguised();
	}
	else if( m_disguiseAsPlayerIndex != -1 )
	{
		m_disguiseAsPlayerIndex = -1;
		ModelConditionFlags flags = draw->getModelConditionFlags();
		
		//Get rid of the old instance!
		TheGameClient->destroyDrawable( draw );

		const ThingTemplate *tTemplate = self->getTemplate();

		TheThingFactory->newDrawable( tTemplate );
		if( draw )
		{
			TheGameLogic->bindObjectAndDrawable(self, draw);
			draw->setPosition( self->getPosition() );
			draw->setOrientation( self->getOrientation() );
			draw->setModelConditionFlags( flags );
			draw->updateDrawable();
			self->getPhysics()->resetDynamicPhysics();
			if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
				draw->setIndicatorColor( self->getNightIndicatorColor() );
			else
				draw->setIndicatorColor( self->getIndicatorColor() );
			if( selected )
			{
				TheInGameUI->selectDrawable( draw );
			}

			//UGH!
			//A concrete example is the bomb truck. Different payloads are displayed based on which upgrades have been
			//made. When the bomb truck disguises as something else, these subobjects are lost because the vector is
			//stored in W3DDrawModule. When we revert back to the original bomb truck, we call this function to 
			//recalculate those upgraded subobjects.
			self->forceRefreshSubObjectUpgradeStatus();
		}

		Bool successfulReveal = false;
		AIUpdateInterface *ai = self->getAI();
		if( ai )
		{
			Object *currTarget = ai->getCurrentVictim();
			if( currTarget )
			{
				successfulReveal = true;
			}
		}

		//Play a reveal sound!
		AudioEventRTS sound;
		if( successfulReveal )
		{
			sound = *self->getTemplate()->getPerUnitSound( "DisguiseRevealedSuccess" );
		}
		else
		{
			sound = *self->getTemplate()->getPerUnitSound( "DisguiseRevealedFailure" );
		}
		sound.setObjectID( self->getID() );
		TheAudio->addAudioEvent( &sound );

		FXList::doFXPos( data->m_disguiseRevealFX, self->getPosition() );
		m_disguised = false;
		self->clearStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_DISGUISED ) );
		self->clearModelConditionState( MODELCONDITION_DISGUISED );
	}

	//Reset the radar (determines color on add)
	TheRadar->removeObject( self );
	TheRadar->addObject( self );

	// couldn't possibly need to restore a disguise now :)
	m_xferRestoreDisguise = FALSE;

}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@StealthUpdate@@ present-unmatched
void StealthUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// StealthUpdate::xfer is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdateXfer.cpp (0x00374942).

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@StealthUpdate@@ present-unmatched
void StealthUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

	//
	// we will need to restore our disguise when the game is ready to run ... NOTE that we
	// cannot restore it here because if we called changeVisualDisguise() it would
	// destroy our drawable and create new stuff.  The destruction of a drawable during
	// a load is *very* bad ... it has a snapshot instance in the game state, other things
	// may be pointing at it etc.
	//
	if( isDisguised() )
		m_xferRestoreDisguise = TRUE;

}  // end loadPostProcess
