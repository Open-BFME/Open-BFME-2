// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Contain/HelixContain.cpp); this unit had no counterpart under Code/.
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

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  FILE: HelixContain.cpp ////////////////////////////////////////////////////////////////////////
//  Author: Mark Lorenzen, April, 2003
//
//  Desc:   
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "Common/Player.h"
#include "Common/Xfer.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/HelixContain.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Weapon.h"

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


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?HelixContainModuleData::HelixContainModuleData present-unmatched
HelixContainModuleData::HelixContainModuleData()
{
//	m_initialPayload.count = 0;
  m_drawPips = TRUE;

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?HelixContainModuleData::buildFieldParse present-unmatched
void HelixContainModuleData::buildFieldParse(MultiIniFieldParse& p)
{
  TransportContainModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{		
    { "PayloadTemplateName",  INI::parseAsciiStringVectorAppend, NULL, offsetof(HelixContainModuleData, m_payloadTemplateNameData) },
    {"ShouldDrawPips",  INI::parseBool, NULL, offsetof(HelixContainModuleData, m_drawPips) },

		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
//void HelixContainModuleData::parseInitialPayload( INI* ini, void *instance, void *store, const void* /*userData*/ )
//{
//	HelixContainModuleData* self = (HelixContainModuleData*)instance;
//	const char* name = ini->getNextToken();
//	const char* countStr = ini->getNextTokenOrNull();
//	Int count = countStr ? INI::scanInt(countStr) : 1;
	
//	self->m_initialPayload.name.set(name);
//	self->m_initialPayload.count = count;
//}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?HelixContain::HelixContain present-unmatched
HelixContain::HelixContain( Thing *thing, const ModuleData *moduleData ) : 
								 TransportContain( thing, moduleData )
{

  m_payloadCreated = FALSE;
  m_portableStructureID = INVALID_ID;

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?HelixContain::~HelixContain present-unmatched
HelixContain::~HelixContain( void )
{

}


// ?HelixContain::onObjectCreated present-unmatched
void HelixContain::onObjectCreated( void )
{
  HelixContain::createPayload();
}



// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?HelixContain::update present-unmatched
UpdateSleepTime HelixContain::update()
{

  Object *portable = getPortableStructure();
  if ( portable )
  {
    portable->setPosition( getObject()->getPosition());
    portable->setOrientation( getObject()->getOrientation());
  }

// ?TransportContain::update present-unmatched
  return TransportContain::update(); // extend base
}


// ?HelixContain::redeployOccupants present-unmatched
void HelixContain::redeployOccupants( void )
{
  Coord3D firePos = *getObject()->getPosition();
  firePos.z += 8;
  

	for (ContainedItemsList::iterator it = m_containList.begin(); it != m_containList.end(); ++it)
  {
    Object* rider = *it;
    if (rider)
      rider->setPosition( &firePos );
  }
}


//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?HelixContain::createPayload present-unmatched
void HelixContain::createPayload()
{
	HelixContainModuleData* self = (HelixContainModuleData*)getHelixContainModuleData();


  // Any number of different passengers can be loaded here at init time
	Object* object = getObject();
	ContainModuleInterface *contain = getRetailContain(object);
	if( contain )
  {
		contain->enableLoadSounds( FALSE );

	  TemplateNameList list = self->m_payloadTemplateNameData;
	  TemplateNameIterator iter = list.begin();
	  while ( iter != list.end() )
	  {
		  const ThingTemplate* temp = TheThingFactory->findTemplate( *iter );
		  if (temp)
		  {
			  Object* payload = TheThingFactory->newObject( temp, object->getTeam() ); 

			  if( contain->isValidContainerFor( payload, true ) )
			  {
				  contain->addToContain( payload );
			  }
			  else
			  {
				  DEBUG_CRASH( ( "HelixContain::createPayload: %s is full, or not valid for the payload %s!", object->getName().str(), self->m_initialPayload.name.str() ) );
			  }

      }

      ++iter;
    }

		contain->enableLoadSounds( TRUE );

  } // endif contain

	m_payloadCreated = TRUE;

}

// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?HelixContain::onBodyDamageStateChange present-unmatched
void HelixContain::onBodyDamageStateChange( const DamageInfo* damageInfo, 
																				BodyDamageType oldState, 
																				BodyDamageType newState)  ///< state change callback
{
  // Need to apply state change to the portable structure
  Object *portable = getPortableStructure();
  if ( newState != BODY_RUBBLE  && portable )
  {
		getRetailBodyModule(portable)->setDamageState( newState );
  }
  
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?HelixContain::getPortableStructure present-unmatched
Object* HelixContain::getPortableStructure( void )
{
  return TheGameLogic->findObjectByID( m_portableStructureID );
}



//-------------------------------------------------------------------------------------------------
// ?HelixContain::onDie present-unmatched
void HelixContain::onDie( const DamageInfo *damageInfo )
{
  Object *portable = getPortableStructure();
  if ( portable )
    portable->kill();

// ?TransportContain::onDie present-unmatched
	TransportContain::onDie( damageInfo );//extend base class
}

//-------------------------------------------------------------------------------------------------
// ?HelixContain::onDelete present-unmatched
void HelixContain::onDelete( void )
{
  Object *portable = getPortableStructure();
  if ( portable )
    TheGameLogic->destroyObject( portable );

  TransportContain::onDelete( );
}

// ------------------------------------------------------------------------------------------------
// ?HelixContain::onCapture present-unmatched
void HelixContain::onCapture( Player *oldOwner, Player *newOwner )
{
//  Need to setteam() the portable structure, that's all;
  Object *portable = getPortableStructure();
  if ( portable )
	  portable->setTeam( newOwner->getDefaultTeam() );
}

//-------------------------------------------------------------------------------------------------
// ?HelixContain::addToContainList present-unmatched
void HelixContain::addToContainList( Object *obj )
{
  if ( obj->isKindOf( KINDOF_PORTABLE_STRUCTURE ) && m_portableStructureID == INVALID_ID)  
  {
    Object *portable = getPortableStructure();
    if ( portable )
      TheGameLogic->destroyObject( portable );

    m_portableStructureID = obj->getID();
    obj->friend_setContainedBy( getObject() );//fool portable into thinking my object is his container


  }
  else
		TransportContain::addToContainList( obj );
}

//-------------------------------------------------------------------------------------------------
// ?HelixContain::addToContain present-unmatched
void HelixContain::addToContain( Object *obj )
{
  if ( obj->isKindOf( KINDOF_PORTABLE_STRUCTURE ) && m_portableStructureID == INVALID_ID)  
  {
    Object *portable = getPortableStructure();
    if ( portable )
      TheGameLogic->destroyObject( portable );

    m_portableStructureID = obj->getID();
    obj->friend_setContainedBy( getObject() );//fool portable into thinking my object is his container


  }
  else
		TransportContain::addToContain( obj );
}

//-------------------------------------------------------------------------------------------------
// ?HelixContain::removeFromContain present-unmatched
void HelixContain::removeFromContain( Object *obj, Bool exposeStealthUnits )
{
  if ( obj->isKindOf( KINDOF_PORTABLE_STRUCTURE ) && obj->getID() == m_portableStructureID )  
	{
    Object *portable = getPortableStructure();
    if ( portable )

      m_portableStructureID = INVALID_ID;
      //portable->kill();

  }
  else
  {
		TransportContain::removeFromContain( obj, exposeStealthUnits );
	}
}


//-------------------------------------------------------------------------------------------------
// ?HelixContain::isValidContainerFor present-unmatched
Bool HelixContain::isValidContainerFor(const Object* obj, Bool checkCapacity) const
{
  if ( obj->isKindOf( KINDOF_PORTABLE_STRUCTURE ) && INVALID_ID == m_portableStructureID )  
    return TRUE;

	return TransportContain::isValidContainerFor( obj, checkCapacity );
}


//-------------------------------------------------------------------------------------------------
// ?HelixContain::friend_getRider present-unmatched
const Object *HelixContain::friend_getRider() const
{
// The draw order dependency bug for riders means that our draw module needs to cheat to get around it.	

  if ( m_portableStructureID != INVALID_ID )
  {
    const Object *portableAsRider = TheGameLogic->findObjectByID( m_portableStructureID );
    return portableAsRider;
  }

	return NULL;
}

//-------------------------------------------------------------------------------------------------
// ?HelixContain::isEnclosingContainerFor present-unmatched
Bool HelixContain::isEnclosingContainerFor( const Object *obj ) const
{
  if ( m_portableStructureID == obj->getID() )
  {
    const Object *portableAsRider = TheGameLogic->findObjectByID( m_portableStructureID );
    if ( portableAsRider == obj )
      return FALSE;
  }


  return TransportContain::isEnclosingContainerFor( obj );
}


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// if my object gets selected, then my visible passengers should, too
// this gets called from
// ?HelixContain::clientVisibleContainedFlashAsSelected present-unmatched
void HelixContain::clientVisibleContainedFlashAsSelected()
{
  if ( m_portableStructureID != INVALID_ID)
  {
    Object *portable = getPortableStructure();
    if ( portable && portable->isKindOf(KINDOF_PORTABLE_STRUCTURE) )
    {
			Drawable *draw = portable->getDrawable();
			if ( draw )
			{
				draw->flashAsSelected(); //WOW!
			}
		}
  }
}


// ?HelixContain::isPassengerAllowedToFire present-unmatched
Bool HelixContain::isPassengerAllowedToFire( ObjectID id ) const
{
  // WHETHER WE ARE ALLOWED TO FIRE DEPENDS ON WHO WE ARE
  // PASSENGERS (PROPER) MAY ONLY IF THE FLAG IS TRUE
  // RIDERS ARE ALWAYS ALLOWED TO FIRE (GATTLING CANNONS)

  if ( getObject() && getObject()->getContainedBy() ) // nested containment voids firing, always
    return FALSE;
  
  if ( m_portableStructureID != INVALID_ID && m_portableStructureID == id )
    return TRUE;
  else
  {
    const Object *rider = TheGameLogic->findObjectByID( id );
    if ( rider && rider->isKindOf( KINDOF_INFANTRY ))
// ?TransportContain::isPassengerAllowedToFire present-unmatched
      return TransportContain::isPassengerAllowedToFire( id );//extend
  }

  return FALSE;

}






//-------------------------------------------------------------------------------------------------
// ?HelixContain::onContaining present-unmatched
void HelixContain::onContaining( Object *obj, Bool wasSelected )
{
	// extend base class
	TransportContain::onContaining( obj, wasSelected );

	// give the object a garrisoned version of its weapon
	obj->setWeaponBonusCondition( WEAPONBONUSCONDITION_GARRISONED );
  obj->setDisabled( DISABLED_HELD );
  

  if ( obj->isKindOf( KINDOF_PORTABLE_STRUCTURE ) && getObject()->testStatus( OBJECT_STATUS_STEALTHED ) )
  {
    StealthUpdate *myStealth =  obj->getStealth();
    if ( myStealth )
    {
      myStealth->receiveGrant( true );
      // note to anyone... once stealth is granted to this gattlingcannon ( or such ) 
      // let its own stealthupdate govern the allowedtostealth cases
      // a portable structure never gets removed, so...
    }
  }




}  // end onContaining

// ?HelixContain::onRemoving present-unmatched
void HelixContain::onRemoving( Object *obj )
{
	// extend base class
	TransportContain::onRemoving(obj);

	// give the object back a regular weapon
	obj->clearWeaponBonusCondition( WEAPONBONUSCONDITION_GARRISONED );
  obj->clearDisabled( DISABLED_HELD );

} // end onRemoving










// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?HelixContain::crc present-unmatched
void HelixContain::crc( Xfer *xfer )
{

	// extend base class
	TransportContain::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?HelixContain::xfer present-unmatched
void HelixContain::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 2;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

  if (version >= 2)
    xfer->xferObjectID( &m_portableStructureID );

	// extend base class
  	TransportContain::xfer( xfer );


}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?HelixContain::loadPostProcess present-unmatched
void HelixContain::loadPostProcess( void )
{

	// extend base class
	TransportContain::loadPostProcess();

}  // end loadPostProcess

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0SidesInfoStringVector@@QAE@ABV0@@Z=??0?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z")
