// cl: /Ireference/shims/zh_outofline /Ireference/shims/partitionfilterzh /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// This donor Object view does not use native disabled-mask +0x1C8.
// Keep its unrecovered callers separate from native Object::isDisabled.
#define isDisabled spectreGunshipUpdateDonorIsDisabled
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/SpectreGunshipUpdate.cpp); this unit had no counterpart under Code/.
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

// FILE: SpectreGunshipUpdate.cpp //////////////////////////////////////////////////////////////////////////
// Author: Mark Lorenzen, April 2003
// Desc:   Update module to handle weapon firing of the SpectreGunship Generals special power.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_DEATH_NAMES

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common\GameAudio.h"
#include "Common\ThingTemplate.h"
#include "Common\ThingFactory.h"
#include "Common\Player.h"
#include "Common\PlayerList.h"
#include "Common\Xfer.h"
#include "Common\ClientUpdateModule.h"

#include "GameClient\ControlBar.h"
#include "GameClient\GameClient.h"
#include "GameClient\Drawable.h"
#include "GameClient\ParticleSys.h"
#include "GameClient\FXList.h"
#include "GameClient/ParticleSys.h"

#include "GameLogic\Locomotor.h"
#include "GameLogic\GameLogic.h"
#include "GameLogic\PartitionManager.h"
#include "GameLogic\Object.h"
#include "GameLogic/PartitionFilterZh.h"
#include "GameLogic\ObjectIter.h"
#include "GameLogic\Weaponset.h"
#include "GameLogic\Weapon.h"
#include "GameLogic\TerrainLogic.h"
#include "GameLogic\Module\SpecialPowerModule.h"
#include "GameLogic\Module\SpectreGunshipUpdate.h"
#include "GameLogic\Module\PhysicsUpdate.h"
#include "GameLogic\Module\LaserUpdate.h"
#include "GameLogic\Module\ActiveBody.h"
#include "GameLogic\Module\AIUpdate.h"
#include "GameLogic\Module\ContainModule.h"

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


#define ORBIT_INSERTION_SLOPE_MAX (0.8f)
#define ORBIT_INSERTION_SLOPE_MIN (0.5f)
#define ONE (1.0f)
#define ZERO (0.0f)
#define LOTS_OF_SHOTS (9999)


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static Real zero = 0.0f;
//-------------------------------------------------------------------------------------------------
/*static*/ void SpectreGunshipUpdateModuleData::buildFieldParse(MultiIniFieldParse& multiIniFieldParse)
{
	ModuleData::buildFieldParse(multiIniFieldParse);

	static const FieldParse dataFieldParse[] = 
	{
    { "SpecialPowerTemplate",           INI::parseSpecialPowerTemplate,   NULL, offsetof( SpectreGunshipUpdateModuleData, m_specialPowerTemplate ) },
    { "GattlingTemplateName",           INI::parseAsciiString,				    NULL, offsetof( SpectreGunshipUpdateModuleData, m_gattlingTemplateName ) },
		{ "HowitzerFiringRate",	            INI::parseDurationUnsignedInt,    NULL, offsetof( SpectreGunshipUpdateModuleData, m_howitzerFiringRate ) },
		{ "OrbitTime",	                    INI::parseDurationUnsignedInt,		NULL, offsetof( SpectreGunshipUpdateModuleData, m_orbitFrames ) },
		{ "HowitzerFollowLag",	            INI::parseDurationUnsignedInt,		NULL, offsetof( SpectreGunshipUpdateModuleData, m_howitzerFollowLag ) },
    { "AttackAreaRadius",	              INI::parseReal,				            NULL, offsetof( SpectreGunshipUpdateModuleData, m_attackAreaRadius ) },
		{ "StrafingIncrement",	            INI::parseReal,				            NULL, offsetof( SpectreGunshipUpdateModuleData, m_strafingIncrement ) },
		{ "OrbitInsertionSlope",	          INI::parseReal,	  			          NULL, offsetof( SpectreGunshipUpdateModuleData, m_orbitInsertionSlope ) },
		{ "RandomOffsetForHowitzer",        INI::parseReal,	                  NULL, offsetof( SpectreGunshipUpdateModuleData, m_randomOffsetForHowitzer ) },
		{ "TargetingReticleRadius",	        INI::parseReal,				            NULL, offsetof( SpectreGunshipUpdateModuleData, m_targetingReticleRadius ) },
		{ "GunshipOrbitRadius",	            INI::parseReal,				            NULL, offsetof( SpectreGunshipUpdateModuleData, m_gunshipOrbitRadius ) },
		{ "HowitzerWeaponTemplate",				  INI::parseWeaponTemplate,				  NULL, offsetof( SpectreGunshipUpdateModuleData, m_howitzerWeaponTemplate ) },
		{ "GattlingStrafeFXParticleSystem",	INI::parseParticleSystemTemplate, NULL, offsetof( SpectreGunshipUpdateModuleData, m_gattlingStrafeFXParticleSystem ) },
		{ "AttackAreaDecal",		            RadiusDecalTemplate::parseRadiusDecalTemplate,	NULL, offsetof( SpectreGunshipUpdateModuleData, m_attackAreaDecalTemplate ) },
		{ "TargetingReticleDecal",		      RadiusDecalTemplate::parseRadiusDecalTemplate,	NULL, offsetof( SpectreGunshipUpdateModuleData, m_targetingReticleDecalTemplate ) },
    

    { 0, 0, 0, 0 }
	};
	multiIniFieldParse.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Retail's AIUpdateInterface::getCurLocomotor reads +0x1F0 (rowed 0x0026FF1E
// from SlavedUpdateRepair.cpp); this unit's header copy reads +0x1B8 (7B body
// 8B81B8010000C3 measured in this unit's own object), and its object sorts
// ahead of the first retail copy in link order, so the link keeps its copy
// (S on the consumers). These reads go straight at the member instead of
// odr-using the ZH inline, whose COMDAT would otherwise displace the retail
// copy.
static Locomotor *bfmeSpectreLoco(AIUpdateInterface *ai)
{
	return *(Locomotor *const *)((const char *)ai + 0x1B8);
}

//-------------------------------------------------------------------------------------------------
// ?initiateIntentToDoSpecialPower@SpectreGunshipUpdate@@ present-unmatched
Bool SpectreGunshipUpdate::initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate, const Object *targetObj, const Coord3D *targetPos, const Waypoint *way, UnsignedInt commandOptions )
{
	const SpectreGunshipUpdateModuleData *data = getSpectreGunshipUpdateModuleData();

	if( m_specialPowerModule->getSpecialPowerTemplate() != specialPowerTemplate )
	{
		//Check to make sure our modules are connected.
		return FALSE;
	}

	if( !BitTest( commandOptions, COMMAND_FIRED_BY_SCRIPT ) )
	{
		m_initialTargetPosition.set( targetPos );
		m_overrideTargetDestination.set( targetPos );
    m_gattlingTargetPosition.set( targetPos );
	}
	else
	{
		UnsignedInt now = TheGameLogic->getFrame();
		m_specialPowerModule->setReadyFrame( now );
   	m_initialTargetPosition.set( targetPos );
		setLogicalStatus( GUNSHIP_STATUS_INSERTING );
	}


  Object * gunShip = getObject();


  if ( gunShip )
  {
    // MAKE TWEAKS TO AI SO SHIP MOVES PRETTY
    AIUpdateInterface *shipAI = gunShip->getAIUpdateInterface();
    if ( shipAI)
    {
     shipAI->chooseLocomotorSet( LOCOMOTORSET_PANIC );
	    bfmeSpectreLoco(shipAI)->setAllowInvalidPosition(TRUE);
	    bfmeSpectreLoco(shipAI)->setUltraAccurate(TRUE);	// set ultra-accurate just so AI won't try to adjust our dest
    }

    Drawable *draw = gunShip->getDrawable();
    if ( draw )
      draw->clearAndSetModelConditionState( MODELCONDITION_DOOR_1_OPENING, MODELCONDITION_DOOR_1_CLOSING );
    friend_enableAfterburners(TRUE);

    setLogicalStatus( GUNSHIP_STATUS_INSERTING ); // The gunship is en route to the tharget area, from map-edge
 

    // TELL THE GUNNERS ABOARD THE GUNSHIP TO HOLD THEIR FIRE UNTIL ORBIT INSERTION
        ContainModuleInterface *shipContain = getRetailContain(gunShip);
    if ( shipContain )
    {

      Object *newGattling = TheGameLogic->findObjectByID( m_gattlingID );
	    const ThingTemplate *gattlingTemplate = TheThingFactory->findTemplate( data->m_gattlingTemplateName );
	    if( newGattling != NULL )
      {
        m_gattlingID = INVALID_ID;
        newGattling = NULL;
      }
      if ( gattlingTemplate )
      {
        newGattling = TheThingFactory->newObject( gattlingTemplate, getObject()->getTeam() ); 
        DEBUG_ASSERTCRASH( gunShip, ("SpecterGunshipUpdate failed to find or create a GATTLING object"));
        shipContain->addToContain( newGattling );
        m_gattlingID = newGattling->getID();
      }


      Object *gattling = TheGameLogic->findObjectByID( m_gattlingID );
      if ( gattling )
        gattling->setDisabled ( DISABLED_PARALYZED );

    }

  }


	data->m_attackAreaDecalTemplate.createRadiusDecal( *getObject()->getPosition(), data->m_attackAreaRadius, getObject()->getControllingPlayer(), m_attackAreaDecal);
	data->m_targetingReticleDecalTemplate.createRadiusDecal( *getObject()->getPosition(), data->m_targetingReticleRadius, getObject()->getControllingPlayer(), m_targetingReticleDecal);


#if defined TRACKERS
	data->m_targetingReticleDecalTemplate.createRadiusDecal( *getObject()->getPosition(), data->m_targetingReticleRadius, getObject()->getControllingPlayer(), m_howitzerTrackerDecal);
#endif


	SpecialPowerModuleInterface *spmInterface = getObject()->getSpecialPowerModule( specialPowerTemplate );
	if( spmInterface )
	{
		SpecialPowerModule *spModule = (SpecialPowerModule*)spmInterface;
		spModule->markSpecialPowerTriggered( &m_initialTargetPosition );
	}
  
	return TRUE;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// PARTITION FILTERS!
//-----------------------------------------------------------------------------
class PartitionFilterLiveMapEnemies : public PartitionFilter
{
private:
	const Object *m_obj;
public:
	PartitionFilterLiveMapEnemies(const Object *obj) : m_obj(obj) { }

	virtual Bool allow(Object *objOther)
	{
		// this is way fast (bit test) so do it first.
		if (objOther->isEffectivelyDead())
			return false;

		// this is also way fast (bit test) so do it next.
		if (objOther->isOffMap() != m_obj->isOffMap())
			return false;

		Relationship r = m_obj->getRelationship(objOther);
		if (r != ENEMIES)
			return false;

		return true;
	}

#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterLiveMapEnemies"; }
#endif
};
//-----------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
/** The update callback. */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// SpectreGunshipUpdate::cleanUp: defined in SpectreGunshipUpdateCleanUp.cpp (its row's unit).


// --------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version 
	* 2: Can't flat-save decals, that's a hella crash (they aren't saved (no memory) and they have a pointer in them).  And half the class wasn't saved.
*/
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------