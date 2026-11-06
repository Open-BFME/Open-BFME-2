// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// This donor Object view does not use native disabled-mask +0x1C8.
// Keep its unrecovered callers separate from native Object::isDisabled.
#define isDisabled specialPowerModuleDonorIsDisabled
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp); this unit had no counterpart under Code/.
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

// FILE: SpecialPowerModule.cpp ///////////////////////////////////////////////////////////////////
// Author: Colin Day, April 2002
// Desc:	 Special power module interface
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameAudio.h"
#include "Common/GlobalData.h"
#include "Common/INI.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Science.h"
#include "Common/SpecialPower.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/DeletionUpdate.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/SpecialPowerUpdateModule.h"
#include "GameLogic/ScriptEngine.h"

#include "GameClient/Eva.h"
#include "GameClient/InGameUI.h"
#include "GameClient/ControlBar.h"

// Player's shared special-power timers are rowed under the receiver-prefix
// view Rva002AC6B1PlayerTimers (Rva002AC6B1PlayerTimers.cpp): getOrStart
// 0x002AC7A0 and resetOrStart 0x002AC6E1, Zero Hour's
// Player::getOrStartSpecialPowerReadyFrame/resetOrStartSpecialPowerReadyFrame.
// The Zero Hour bodies below call them there; the Player donor copies are gone.
class Rva002AC6B1PlayerTimers
{
public:
	unsigned getOrStart(const SpecialPowerTemplate *specialPowerTemplate);
	void resetOrStart(const SpecialPowerTemplate *specialPowerTemplate);
};


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// The BFME2 constructor is defined and byte-verified in
// SpecialPowerModuleCtor.cpp at RVA 0x00493C5A. The former Zero Hour
// implementation here called resolveSpecialPower and omitted BFME2 fields;
// its duplicate definition displaced the native provider at link time.

//-------------------------------------------------------------------------------------------------
// ?getInitiateSound@SpecialPowerModule@@UBEABVAudioEventRTS@@XZ present-unmatched
const AudioEventRTS& SpecialPowerModule::getInitiateSound() const
{
	return getSpecialPowerModuleData()->m_initiateSound;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SpecialPowerModule::~SpecialPowerModule is defined with its retail-matched body in
// SpecialPowerModuleDtor_Unresolved.cpp (0x00493DEF).

//-------------------------------------------------------------------------------------------------
// ?setReadyFrame@SpecialPowerModule@@UAEXI@Z present-unmatched
void SpecialPowerModule::setReadyFrame( UnsignedInt frame )
{ 
	m_availableOnFrame = frame; 

	//If a script should change the ready frame, we need to update the paused frame. This value isn't
	//used directly to determine if paused or not... it uses m_pausedCount.
	m_pausedOnFrame = TheGameLogic->getFrame();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?resolveSpecialPower@SpecialPowerModule@@IAEXXZ present-unmatched
void SpecialPowerModule::resolveSpecialPower( void )
{
	/*

	// if we're pre-built, and not from a command center, and a building register us with the UI
	if( getSpecialPowerModuleData()->m_specialPowerTemplate->hasPublicTimer() == TRUE &&
			TheGameLogic->getFrame() == 0 && getObject()->getControllingPlayer() &&
		  getObject()->isKindOf( KINDOF_COMMANDCENTER ) == FALSE &&
			getObject()->isKindOf( KINDOF_STRUCTURE ) )
	{
		//KM: The KINDOF_STRUCTURE check was made to prevent scripted bombers from registering their
		//    special powers as public timers.
		TheInGameUI->addSuperweapon( getObject()->getControllingPlayer()->getPlayerIndex(), 
																 getPowerName(), 
																 getObject()->getID(), 
																 getSpecialPowerModuleData()->m_specialPowerTemplate );
	}
	*/
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/SpecialPowerModule_onSpecialPowerCreationMethodThunk.cpp

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?SpecialPowerModule::getRequiredScience present-unmatched
ScienceType SpecialPowerModule::getRequiredScience( void ) const
{

	return getSpecialPowerModuleData()->m_specialPowerTemplate->getRequiredScience();
}  // end ~SpecialPowerModule

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?SpecialPowerModule::getSpecialPowerTemplate present-unmatched
const SpecialPowerTemplate * SpecialPowerModule::getSpecialPowerTemplate( void ) const
{

	return getSpecialPowerModuleData()->m_specialPowerTemplate;
}  // end ~SpecialPowerModule

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?isModuleForPower@SpecialPowerModule@@UBE_NPBVSpecialPowerTemplate@@@Z present-unmatched
Bool SpecialPowerModule::isModuleForPower( const SpecialPowerTemplate *specialPowerTemplate ) const
{
	
	// get the module data
	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();

	//
	// if the special power template defined in the module data matches the template we want
	// to check then we are for it!
	//
	if( modData->m_specialPowerTemplate == specialPowerTemplate )
	{
		//We match templates.
		return TRUE;
	}
	//We don't match templates.
	return FALSE;
		
}  // end canExecutePower

//-------------------------------------------------------------------------------------------------
/** Is this special power ready to use */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule_isReady_Thunk.cpp
// SpecialPowerModule::isReady is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleIsReady.cpp (0x004934DE).

//-------------------------------------------------------------------------------------------------
/** Get the percentage ready a special power is to use
	* 1.0f = ready now
	* 0.5f = 50% ready
	* 0.2f = 20% ready
	* etc ... */
//-------------------------------------------------------------------------------------------------
// Matched via Code/masm_dumps/SpecialPowerModule_getPercentReady.asm @ 0x00268A90 (210B)
// Retail: early [this+0x14] flag returns 0.0; no ZH 0.99999 paused-at-ready path
// ?SpecialPowerModule::getPercentReady present-unmatched
Real SpecialPowerModule::getPercentReady() const
{
	if( m_pausedCount > 0 && m_pausedPercent == 1.0f )
	{
			//Don't consider it ready if paused.
		return 0.99999f;
	}

#if defined(_DEBUG) || defined(_INTERNAL) || defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)
	if( TheGlobalData->m_specialPowerUsesDelay == FALSE ) 
		return 1.0f;
#endif
	
	// easy case ... is ready
	if( isReady() )
		return 1.0f;

	if( m_pausedCount > 0 )
	{
		return m_pausedPercent;
	}

	// get the module data
	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();

	// sanity
	if( modData->m_specialPowerTemplate == NULL )
		return 0.0f;

	UnsignedInt readyFrame = m_availableOnFrame;

	//unless
	const Object* obj = getObject();
	if ( obj )
	{
		Player *player = getObject()->getControllingPlayer();
		if ( player )
		{
			if ( modData->m_specialPowerTemplate->isSharedNSync())
			{
				readyFrame = ((Rva002AC6B1PlayerTimers *)player)->getOrStart( getSpecialPowerTemplate() );
			}
		}
	}

	// calculate the percent	
	Real percent = 1.0f - ((readyFrame - TheGameLogic->getFrame()) / 
												 (Real)modData->m_specialPowerTemplate->getReloadTime());

	return percent;
}

//-------------------------------------------------------------------------------------------------
// A special power module that is only supposed to be fired via scripts. An example of this
// are the various cargo plane units we have. Scripters can launch specials from them after
// specifying a waypoint path for them to follow them.
//-------------------------------------------------------------------------------------------------
// ?isScriptOnly@SpecialPowerModule@@UBE_NXZ present-unmatched
Bool SpecialPowerModule::isScriptOnly() const
{
	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();
	return modData->m_scriptedSpecialPowerOnly;
}


//-------------------------------------------------------------------------------------------------
/** A special power has been used ... start the recharge process by computing the frame
	* we will become fully available on in the future again */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/promoted__startPowerRecharge_SpecialPowerModule_UAEXXZ_0026AE00.cpp
// ?startPowerRecharge@SpecialPowerModule@@UAEXXZ present-unmatched
void SpecialPowerModule::startPowerRecharge()
{
#if defined(_DEBUG) || defined(_INTERNAL) || defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)
	// this is a cheat ... remove this for release!
	if( TheGlobalData->m_specialPowerUsesDelay == FALSE ) 
		return;
#endif

	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();

	// sanity
	if( modData->m_specialPowerTemplate == NULL )
	{
		DEBUG_CRASH(("special power not found"));
		return;
	}

	Object* obj = getObject();
	if (!obj)
		return;

	Player* player = getObject()->getControllingPlayer();
	if (!player)
		return;

	//Here, we make sure that general specials work as one between command centers
	// only factory type faction buildings should do this, and only with generals powers (in general)
	// but there are no restrictions on the use of SharedNSync on specialPowerTemplates at large
	if ( modData->m_specialPowerTemplate->isSharedNSync() )
	{
		((Rva002AC6B1PlayerTimers *)player)->resetOrStart( modData->m_specialPowerTemplate );
	}
	else
	{
		// set the frame we will be 100% available on now
		m_availableOnFrame = TheGameLogic->getFrame() + getSpecialPowerTemplate()->getReloadTime();
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleInitiateIntentThunk.cpp
// ?initiateIntentToDoSpecialPower@SpecialPowerModule@@IAE_NPBVObject@@PBUCoord3D@@PBVWaypoint@@I@Z present-unmatched
Bool SpecialPowerModule::initiateIntentToDoSpecialPower( const Object *targetObj, const Coord3D *targetPos, const Waypoint *way, UnsignedInt commandOptions )
{
	Bool valid = false;
	// tell our update modules that we intend to do this special power.
	for( BehaviorModule** behaviorModule = getObject()->getBehaviorModules(); *behaviorModule; ++behaviorModule )
	{
		SpecialPowerUpdateInterface* spu = (*behaviorModule)->getSpecialPowerUpdateInterface();
		if( spu )
		{
			//Validate that we are calling the correct module!
			if( isModuleForPower( getSpecialPowerModuleData()->m_specialPowerTemplate ) )
			{
				if( spu->doesSpecialPowerUpdatePassScienceTest() )
				{
					if( spu->initiateIntentToDoSpecialPower( getSpecialPowerModuleData()->m_specialPowerTemplate, targetObj, targetPos, way, commandOptions ) )
					{
						//Kris: Aug 2003
						//We have executed the special power, so don't try to execute any more. This logic
						//was changed for multi-level spectres. Before, multiple modules would get launched
						//causing 2 or 3 spectres to be created.
						valid = true;
						break;
					}
				}
			}
		}
	}

	// Zero Hour recorded the use in AcademyStats here; BFME 2 has no AcademyStats
	// (AcademyStats::recordSpecialPowerUsed was this unit's only link blocker).
	
	//If we depend on our update module to trigger the special power, make sure we have the
	//appropriate update module!
	if( !valid && getSpecialPowerModuleData()->m_updateModuleStartsAttack )
	{
		DEBUG_CRASH( ("Object does not contain a special power module to execute.  Did you forget to add it to the object INI?\n"));
		//DEBUG_CRASH(( "Object does not contain special power module (%s) to execute.  Did you forget to add it to the object INI?\n",
		//							command->m_specialPower->getName().str() ));
	}

	return valid;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?triggerSpecialPower@SpecialPowerModule@@IAEXPBUCoord3D@@@Z present-unmatched
void SpecialPowerModule::triggerSpecialPower( const Coord3D *location )
{
	aboutToDoSpecialPower( location );	// do BEFORE recharge

	createViewObject(location);
	
	// we won't be able to use the power for X number of frames now
	startPowerRecharge();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Matched via Code/masm_dumps/SpecialPowerModule_createViewObject.asm @ 0x00269130 (422B)
// SpecialPowerModule::createViewObject is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleCreateViewObject.cpp (0x00493845).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SpecialPowerModule::markSpecialPowerTriggered (0x00494591) is rowed in SpecialPowerModuleDo.cpp; a second definition here would not link.


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SpecialPowerModule::aboutToDoSpecialPower is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleTrigger.cpp (0x004939AB); a second definition here would not link.

// The ZH body above was the only caller here of the header-inline
// SpecialPowerTemplate::getSpecialPowerType, rowed at 0x002AAE3D from this
// unit; this helper (no retail address) keeps cl emitting that copy.
// ?SpecialPowerTemplateTypeEmissionAnchor absent-from-retail
SpecialPowerType SpecialPowerTemplateTypeEmissionAnchor( const SpecialPowerTemplate *specialPowerTemplate )
{
	return specialPowerTemplate->getSpecialPowerType();
}

//-------------------------------------------------------------------------------------------------
//By default, special powers are not triggered by it's update module -- in which case
//it triggers it and resets its timer immediately. When the update module triggers it,
//then all we do is initiate the special power, and trust that the update module will 
//do the rest.
//-------------------------------------------------------------------------------------------------
// SpecialPowerModule::doSpecialPower is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleDo.cpp (0x0049490F).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SpecialPowerModule::doSpecialPowerAtObject is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleDo.cpp (0x0049495B).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?doSpecialPowerAtLocation@SpecialPowerModule@@UAEXPBUCoord3D@@MI@Z present-unmatched
void SpecialPowerModule::doSpecialPowerAtLocation( const Coord3D *loc, Real angle, UnsignedInt commandOptions )
{
	if (m_pausedCount > 0 || getObject()->isDisabled()) {
		return;
	}

	//This tells the update module that we want to do our special power. The update modules
	//will then start processing each frame.
	initiateIntentToDoSpecialPower( NULL, loc, NULL, commandOptions );

	//Only trigger the special power immediately if the updatemodule doesn't start the attack.
	//An example of a case that wouldn't trigger immediately is for a unit that needs to 
	//close to range before firing the special attack. A case that would trigger immediately
	//is the napalm strike. If we don't call this now, it's up to the update module to do so.
	if( !getSpecialPowerModuleData()->m_updateModuleStartsAttack )
	{
		triggerSpecialPower( loc );
	}
}  

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?doSpecialPowerUsingWaypoints@SpecialPowerModule@@UAEXPBVWaypoint@@I@Z present-unmatched
void SpecialPowerModule::doSpecialPowerUsingWaypoints( const Waypoint *way, UnsignedInt commandOptions )
{
	if (m_pausedCount > 0 || getObject()->isDisabled()) {
		return;
	}

	//This tells the update module that we want to do our special power. The update modules
	//will then start processing each frame.
	initiateIntentToDoSpecialPower( NULL, NULL, way, commandOptions );

	//Only trigger the special power immediately if the updatemodule doesn't start the attack.
	//An example of a case that wouldn't trigger immediately is for a unit that needs to 
	//close to range before firing the special attack. A case that would trigger immediately
	//is the napalm strike. If we don't call this now, it's up to the update module to do so.
	if( !getSpecialPowerModuleData()->m_updateModuleStartsAttack )
	{
		triggerSpecialPower( NULL );// This type doesn't create view objects
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// SpecialPowerModule::pauseCountdown is rowed at 0x00492FC2 (Rva00492FC2.cpp).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/SpecialPowerModule_getReadyFrame_Thunk.cpp
// ?getReadyFrame@SpecialPowerModule@@UBEIXZ present-unmatched
UnsignedInt SpecialPowerModule::getReadyFrame( void ) const
{
	if ( getSpecialPowerTemplate()->isSharedNSync() )
	{
		const Object* obj = getObject();
		if ( obj )
		{
			Player *player = getObject()->getControllingPlayer();
			if ( player )
				return ((Rva002AC6B1PlayerTimers *)player)->getOrStart( getSpecialPowerTemplate() );
		}
	}

	if (m_pausedCount > 0 || getObject()->isDisabled())
	{
		Int pausedFrames = TheGameLogic->getFrame() - m_pausedOnFrame;
		return m_availableOnFrame + pausedFrames;
	}
	else
	{
		return m_availableOnFrame;
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@SpecialPowerModule@@MAEXPAVXfer@@@Z present-unmatched
void SpecialPowerModule::crc( Xfer *xfer )
{


}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?xfer@SpecialPowerModule@@MAEXPAVXfer@@@Z present-unmatched
void SpecialPowerModule::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	BehaviorModule::xfer( xfer );

	// available on frame
	xfer->xferUnsignedInt( &m_availableOnFrame );

	// paused by script
	xfer->xferInt( &m_pausedCount );

	// paused on frame
	xfer->xferUnsignedInt( &m_pausedOnFrame );

	// paused percent
	xfer->xferReal( &m_pausedPercent );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// SpecialPowerModule::loadPostProcess is rowed at 0x00493B1E (SpecialPowerModuleRva00493B1E.cpp).

//-------------------------------------------------------------------------------------------------
// Two more out-of-line final-override accessors in the shape of the
// SpecialPowerTemplate getters above (call the rowed const
// friend_getFinalOverride 0x00288609, then read the result): 0x0028F8CE
// returns the address of the dword at +0x10 and 0x002AAE46 the dword at
// +0x20. The BFME2 template fields there are not identified (ZH's m_id /
// m_initiateSound positions do not fit both), so the owner is an
// address-named Overridable view and the fields are named by offset.
class Rva0028F8CEOverrideView : public Overridable
{
public:
	const UnsignedInt *rva0028F8CE( void ) const;
	UnsignedInt rva002AAE46( void ) const;
private:
	const Rva0028F8CEOverrideView *getFO( void ) const { return (const Rva0028F8CEOverrideView *)friend_getFinalOverride(); }
	UnsignedInt m_0C;
	UnsignedInt m_10;
	UnsignedInt m_14;
	UnsignedInt m_18;
	UnsignedInt m_1C;
	UnsignedInt m_20;
};

const UnsignedInt *Rva0028F8CEOverrideView::rva0028F8CE( void ) const
{
	return &getFO()->m_10;
}

UnsignedInt Rva0028F8CEOverrideView::rva002AAE46( void ) const
{
	return getFO()->m_20;
}
