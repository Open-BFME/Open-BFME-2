// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdate.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

// FILE: AssistedTargetingUpdate.cpp /////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, September 2002
// Desc:   Outside influences can tell me to attack something out of my normal targeting range
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_WEAPONSLOTTYPE_NAMES
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/Xfer.h"
#include "GameLogic/Object.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/WeaponSet.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/AssistedTargetingUpdate.h"
#include "GameLogic/Module/LaserUpdate.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif



//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// AssistedTargetingUpdateModuleData::buildFieldParse: defined in ModuleDataBuildFieldParse.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0AssistedTargetingUpdate@@QAE@PAVThing@@PBVModuleData@@@Z owned by AssistedTargetingUpdateCtor.cpp: declared only here.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?AssistedTargetingUpdate::~AssistedTargetingUpdate present-unmatched
AssistedTargetingUpdate::~AssistedTargetingUpdate( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
Bool AssistedTargetingUpdate::isFreeToAssist() const
{
	// The reload times of my two weapons are tied together, so Ready is indicitive of either.
	const Object *me = getObject();
	if( !me->isAbleToAttack() )
		return FALSE;// This will cover under construction among other things

	Bool ready = me->getCurrentWeapon() && me->getCurrentWeapon()->getStatus() == READY_TO_FIRE;
	return ready;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Existing 0026C2D9 command-provider spelling; native receiver is
// the AI update at Object+0x258 plus its command-interface subobject +0x20.
class Rva0026C2D9Commands
{
public:
    void Rva0026C2D9Command(void *victim, int shots, int source);
};

// BFME2 FieldParse table VA C4AFE8 uses the rowed ThingFactory parser
// 33940F for LaserFromAssisted / LaserToTarget at +10 / +14. These are
// template pointers in module data, unlike ZH's names and instance caches.
struct BfmeAssistedLaserTemplates
{
    char prefix[0x10];
    const ThingTemplate *fromAssisted;
    const ThingTemplate *toTarget;
};

void AssistedTargetingUpdate::assistAttack( const Object *requestingObject, Object *victimObject )
{
	const AssistedTargetingUpdateModuleData *md = getAssistedTargetingUpdateModuleData();
	Object *me = getObject();
	if (*reinterpret_cast<void **>(reinterpret_cast<char *>(me) + 0x258) == 0)
		return;

	// lock it just till the weapon is empty or the attack is "done"
	me->setWeaponLock( md->m_weaponSlot, LOCKED_TEMPORARILY );
	reinterpret_cast<Rva0026C2D9Commands *>(
        reinterpret_cast<char *>(*reinterpret_cast<void **>(
            reinterpret_cast<char *>(me) + 0x258)) + 0x20)->
        Rva0026C2D9Command(victimObject, md->m_clipSize, CMD_FROM_AI);


	const BfmeAssistedLaserTemplates *lasers =
        reinterpret_cast<const BfmeAssistedLaserTemplates *>(md);
    if (lasers->fromAssisted)
        makeFeedbackLaser(lasers->fromAssisted, requestingObject, me);
    if (lasers->toTarget)
        makeFeedbackLaser(lasers->toTarget, me, victimObject);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?AssistedTargetingUpdate::makeFeedbackLaser present-unmatched
void AssistedTargetingUpdate::makeFeedbackLaser( const ThingTemplate *laserTemplate, const Object *from, const Object *to )
{
	if( !getObject()->getControllingPlayer() )
		return;

	Team *laserTeam = getObject()->getControllingPlayer()->getDefaultTeam();
	Object *laser = TheThingFactory->newObject( laserTemplate, laserTeam );
	if( !laser )
		return;

	// Give it a good basis in reality to ensure it can draw when on screen.
	laser->setPosition(from->getPosition());
	
	Drawable *draw = laser->getDrawable();
	static const NameKeyType key_LaserUpdate = NAMEKEY( "LaserUpdate" );
	LaserUpdate *update = (LaserUpdate*)draw->findClientUpdateModule( key_LaserUpdate );
	if( !update )
	{
		TheGameLogic->destroyObject( laser );
		return;
	}

	update->initLaser( getObject(), to, from->getPosition(), to->getPosition(), "" );
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?AssistedTargetingUpdate::update present-unmatched
UpdateSleepTime AssistedTargetingUpdate::update( void )
{

  const AssistedTargetingUpdateModuleData *d = getAssistedTargetingUpdateModuleData();

	m_laserFromAssisted = TheThingFactory->findTemplate( d->m_laserFromAssistedName );


	m_laserToTarget =TheThingFactory->findTemplate( d->m_laserFromAssistedName );


	return UPDATE_SLEEP_FOREVER;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?AssistedTargetingUpdate::crc present-unmatched
void AssistedTargetingUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?AssistedTargetingUpdate::xfer present-unmatched
void AssistedTargetingUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?AssistedTargetingUpdate::loadPostProcess present-unmatched
void AssistedTargetingUpdate::loadPostProcess( void )
{
  const AssistedTargetingUpdateModuleData *d = getAssistedTargetingUpdateModuleData();

	m_laserFromAssisted = TheThingFactory->findTemplate( d->m_laserFromAssistedName );
	m_laserToTarget =TheThingFactory->findTemplate( d->m_laserFromAssistedName );

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
