// cl: /Ireference/shims/zh_outofline /Ireference/shims/updatemodule_ctor /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp); this unit had no counterpart under Code/.
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

// FILE: StructureToppleUpdate.cpp ///////////////////////////////////////////////////////////////////////
// Author:
// Desc:  
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/INI.h"
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/FXList.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/BoneFXUpdate.h"
#include "GameLogic/Module/StructureToppleUpdate.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"

// Keep the retail AngleFXInfo vector providers emitted in this /O2 TU after
// parseAngleFX moved to the O1/SSE phase-parser unit.
template void _STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> >::push_back(const AngleFXInfo &);


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

const Int MAX_IDX = 32;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
StructureToppleUpdate::StructureToppleUpdate( Thing *thing, const ModuleData* moduleData ) : UpdateModule( thing, moduleData )
{
	
	//Added By Sadullah Nader
	//Initialization(s) inserted
	m_delayBurstLocation.zero();
	m_structuralIntegrity = 0.0f;
	m_toppleDirection.x = m_toppleDirection.y = 0;
	//
	m_toppleFrame = 0;
	m_toppleState = TOPPLESTATE_STANDING;
	m_toppleVelocity = 0.0f;
	m_accumulatedAngle = 0.001f; // Need to give it a little nudge in the right direction
	m_lastCrushedLocation = 0.0f;
	m_nextBurstFrame = -1;
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);

	//Get the extent height here, rather than after it dies -- when it switches to dead state
	//the rubble state has a tiny height.
	Object *building = getObject();
	m_buildingHeight = building->getGeometryInfo().getMaxHeightAbovePosition();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?StructureToppleUpdate::~StructureToppleUpdate present-unmatched
StructureToppleUpdate::~StructureToppleUpdate( void )
{
}

//-------------------------------------------------------------------------------------------------
static void parseOCL( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	StructureToppleUpdateModuleData* self = (StructureToppleUpdateModuleData*)instance;
	StructureTopplePhaseType stphase = (StructureTopplePhaseType)INI::scanIndexList(ini->getNextToken(), TheStructureTopplePhaseNames);
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null! this is OK!
		self->m_ocls[stphase].push_back(ocl);
	}
}

//-------------------------------------------------------------------------------------------------
void parseAngleFX(INI* ini, void *instance, void *store, const void *userData);

//-------------------------------------------------------------------------------------------------
/*static*/ void StructureToppleUpdateModuleData::buildFieldParse(MultiIniFieldParse& p) 
{
  UpdateModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] = 
	{
		{ "MinToppleDelay",						INI::parseDurationUnsignedInt,		NULL, offsetof( StructureToppleUpdateModuleData, m_minToppleDelay ) },
		{ "MaxToppleDelay",						INI::parseDurationUnsignedInt,		NULL, offsetof( StructureToppleUpdateModuleData, m_maxToppleDelay ) },
		{ "MinToppleBurstDelay",			INI::parseDurationUnsignedInt,		NULL, offsetof( StructureToppleUpdateModuleData, m_minToppleBurstDelay ) },
		{ "MaxToppleBurstDelay",			INI::parseDurationUnsignedInt,		NULL, offsetof( StructureToppleUpdateModuleData, m_maxToppleBurstDelay ) },
		{ "StructuralIntegrity",			INI::parseReal,										NULL, offsetof( StructureToppleUpdateModuleData, m_structuralIntegrity ) },
		{ "StructuralDecay",					INI::parseReal,										NULL, offsetof( StructureToppleUpdateModuleData, m_structuralDecay ) },
		{ "DamageFXTypes",						INI::parseDamageTypeFlags,				NULL, offsetof( StructureToppleUpdateModuleData, m_damageFXTypes ) },
		{ "TopplingFX",								INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_toppleFXList ) },
		{ "ToppleDelayFX",						INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_toppleDelayFXList ) },
		{ "ToppleStartFX",						INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_toppleStartFXList ) },
		{ "ToppleDoneFX",							INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_toppleDoneFXList ) },
		{ "CrushingFX",								INI::parseFXList,									NULL, offsetof( StructureToppleUpdateModuleData, m_crushingFXList ) },
		{ "CrushingWeaponName",				INI::parseAsciiString,						NULL, offsetof( StructureToppleUpdateModuleData, m_crushingWeaponName ) },
		{ "OCL",											parseOCL,													NULL, 0 },
		{ "AngleFX",									parseAngleFX,											NULL, 0 },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
	p.add(DieMuxData::getFieldParse(), offsetof( StructureToppleUpdateModuleData, m_dieMuxData ));
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::beginStructureTopple is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A5C8C).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::onDie is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A5E5B).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::update is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A6042).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::doToppleDoneStuff is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A5628).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::doAngleFX is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A57DB).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// theta is the angle of the building with respect to the ground.
// StructureToppleUpdate::applyCrushingDamage is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A5EAC).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::doDamageLine is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A5947).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::doToppleStartFX is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A5B09).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::doToppleDelayBurstFX is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A5B61).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
inline Bool inList(Int value, Int count, const Int idxList[])
{
	for (Int j = 0; j < count; ++j)
	{
		if (idxList[j] == value)
			return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static void buildNonDupRandomIndexList(Int range, Int count, Int idxList[])
{
	for (Int i = 0; i < count; ++i)
	{
		Int idx;
		do
		{
			idx = GameLogicRandomValue(0, range-1);
		} 
		while (inList(idx, i, idxList));
		idxList[i] = idx;
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// StructureToppleUpdate::doPhaseStuff is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdateCrushing.cpp (0x004A584B).

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?StructureToppleUpdate::crc present-unmatched
void StructureToppleUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?StructureToppleUpdate::xfer present-unmatched
void StructureToppleUpdate::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpdateModule::xfer( xfer );

	// topple frame
	xfer->xferUnsignedInt( &m_toppleFrame );

	// topple direction
	xfer->xferCoord2D( &m_toppleDirection );

	// topple state
	xfer->xferUser( &m_toppleState, sizeof( StructureToppleStateType ) );

	// topple velocity
	xfer->xferReal( &m_toppleVelocity );

	// accumulated angle
	xfer->xferReal( &m_accumulatedAngle );

	// structural integrity
	xfer->xferReal( &m_structuralIntegrity );

	// last crushed location
	xfer->xferReal( &m_lastCrushedLocation );

	// next burst frame
	xfer->xferInt( &m_nextBurstFrame );

	// delay burst location
	xfer->xferCoord3D( &m_delayBurstLocation );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?StructureToppleUpdate::loadPostProcess present-unmatched
void StructureToppleUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
