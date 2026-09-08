// cl: /Ireference/shims/dockupdate /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Update/FireSpreadUpdate.cpp); this unit had no counterpart under Code/.
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

// FILE: FireSpreadUpdate.cpp /////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, April 2002
// Desc:   Update looks for ::Aflame and explicitly ignites someone nearby if set
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// dockupdate shim has to win the UpdateModule.h include guard before
// GameLogic.h (pulled in below) reaches the reference tree's own copy -- see
// reference/shims/dockupdate/GameLogic/Module/UpdateModule.h for the evidence
// (retail's UpdateModule carries one extra reserved dword after
// m_indexInLogic). Found for ProjectileStreamUpdate.cpp by unclaimed_scan's
// layout report (a uniform -4 displacement shift); this unit derives
// directly from UpdateModule too, so its own members shift the same way.
#include "GameLogic/Module/UpdateModule.h"

#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/FireSpreadUpdate.h"
#include "GameLogic/Module/FlammableUpdate.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// This is a one sided query, as in I am not checking for "Flammable By Me", I'm simply testing for a property
class PartitionFilterFlammable : public PartitionFilter
{
public:

	PartitionFilterFlammable(){ }
	
	virtual Bool allow(Object *objOther);
#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterFlammable"; }
#endif
};

//-------------------------------------------------------------------------------------------------
Bool PartitionFilterFlammable::allow(Object *objOther)
{
	// It must be burnable in general, and burnable now
	static NameKeyType key_FlammableUpdate = NAMEKEY("FlammableUpdate");
	FlammableUpdate* fu = (FlammableUpdate*)objOther->findUpdateModule(key_FlammableUpdate);
	if (fu == NULL)
		return FALSE;

	if( ! fu->wouldIgnite() )
		return FALSE;

	return TRUE;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
FireSpreadUpdateModuleData::FireSpreadUpdateModuleData()
{
	m_minSpreadTryDelayData = 0;
	m_maxSpreadTryDelayData = 0;
	m_oclEmbers = NULL;
	m_spreadTryRange = 0;
}

//-------------------------------------------------------------------------------------------------
/*static*/ void FireSpreadUpdateModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  UpdateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "OCLEmbers",				INI::parseObjectCreationList,		NULL, offsetof( FireSpreadUpdateModuleData, m_oclEmbers ) },
		{ "MinSpreadDelay",		INI::parseDurationUnsignedInt,	NULL, offsetof( FireSpreadUpdateModuleData, m_minSpreadTryDelayData ) },
		{ "MaxSpreadDelay",		INI::parseDurationUnsignedInt,	NULL, offsetof( FireSpreadUpdateModuleData, m_maxSpreadTryDelayData ) },
		{ "SpreadTryRange",		INI::parseReal,									NULL, offsetof( FireSpreadUpdateModuleData, m_spreadTryRange ) },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
FireSpreadUpdate::FireSpreadUpdate( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
FireSpreadUpdate::~FireSpreadUpdate( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
UpdateSleepTime FireSpreadUpdate::update( void )
{
	const FireSpreadUpdateModuleData* d = getFireSpreadUpdateModuleData();
	Object* me = getObject();

	if( !me->getStatusBits().test( OBJECT_STATUS_AFLAME ) )
		return UPDATE_SLEEP_FOREVER;		// not on fire -- sleep forever
	{
		ObjectCreationList::create( d->m_oclEmbers, getObject(), NULL );

		if( d->m_spreadTryRange != 0 )
		{
			// This will spread fire explicitly
			PartitionFilterFlammable fFilter;
			PartitionFilter *filters[] = { &fFilter, NULL };

//			SimpleObjectIterator *iter = NULL;
//			iter = ThePartitionManager->iterateObjectsInRange(getObject(), 
//																									d->m_spreadTryRange, 
//																									FROM_CENTER_3D, 
//																									filters, 
//																									ITER_SORTED_NEAR_TO_FAR
//																									);
//			MemoryPoolObjectHolder hold(iter);
//			Object *objectToLight = iter->first();
//
// srj sez: the above code is stupid and slow. since we only want the closest object,
// just ask for that; the above has to find ALL objects in range, but we ignore all 
// but the first (closest).
//
			Object* objectToLight = ThePartitionManager->getClosestObject(getObject(), d->m_spreadTryRange, FROM_CENTER_3D, filters);
			if( objectToLight )
			{
				static NameKeyType key_FlammableUpdate = NAMEKEY("FlammableUpdate");
				FlammableUpdate* fu = (FlammableUpdate*)objectToLight->findUpdateModule(key_FlammableUpdate);
				if( fu )
					fu->tryToIgnite();
			}
		}

		return UPDATE_SLEEP(calcNextSpreadDelay());
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void FireSpreadUpdate::startFireSpreading()
{
	if( !getObject()->getStatusBits().test( OBJECT_STATUS_AFLAME ) )
		return;	// sorry, must be on fire

	setWakeFrame(getObject(), UPDATE_SLEEP(calcNextSpreadDelay()));
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
UnsignedInt FireSpreadUpdate::calcNextSpreadDelay()
{
	const FireSpreadUpdateModuleData* d = getFireSpreadUpdateModuleData();
	UnsignedInt delay = GameLogicRandomValue( d->m_minSpreadTryDelayData, d->m_maxSpreadTryDelayData );
	if (delay < 1)
		delay = 1;
	return delay;
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void FireSpreadUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void FireSpreadUpdate::xfer( Xfer *xfer )
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
void FireSpreadUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
