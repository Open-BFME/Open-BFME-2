// cl: /Ireference/shims/bfme2_specialpower_layout /Ireference/open-bfme-1/reference/shims/specialpowermoduledata /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// This donor Object view does not use native disabled-mask +0x1C8.
// Keep its unrecovered callers separate from native Object::isDisabled.
#define isDisabled defectorSpecialPowerDonorIsDisabled
// stlport
// The BFME 1 declaration-only SpecialPowerModuleData shim suppresses ZH
// implicit base destructors. BFME 2 keeps the real 115-byte destructor at
// RVA 0x0049334F; the derived destructor here already tail-calls that name.
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/SpecialPower/DefectorSpecialPower.cpp); this unit had no counterpart under Code/.
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
// FILE: DefectorSpecialPower.cpp 
// Author: Mark Lorenzen, JULY 2002
// Desc:   General can click command cursor on any enemy, and it becomes his
//
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/SpecialPower.h"
#include "Common/Team.h"
#include "Common/Xfer.h"

#include "GameLogic/Module/DefectorSpecialPower.h"
#include "GameLogic/Object.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Constructor and its implicit destructor providers live in
// DefectorSpecialPowerModuleDataCtor.cpp, using the same BFME2 base layout.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// DefectorSpecialPowerModuleData::buildFieldParse is rowed at 0x004C2970 with
// BFME2's body (SpecialPowerModuleDataBuildFieldParse.cpp); the Zero Hour copy
// here was a second, non-retail definition.

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
DefectorSpecialPower::DefectorSpecialPower( Thing *thing, const ModuleData *moduleData )
												: SpecialPowerModule( thing, moduleData )
{

}  // end DefectorSpecialPower

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?DefectorSpecialPower::~DefectorSpecialPower present-unmatched
DefectorSpecialPower::~DefectorSpecialPower( void )
{

}  // end ~DefectorSpecialPower

 
// ------------------------------------------------------------------------------------------------

// ?DefectorSpecialPower::doSpecialPowerAtLocation present-unmatched
void DefectorSpecialPower::doSpecialPowerAtLocation( const Coord3D *loc, Real angle, UnsignedInt commandOptions )
{
	if (getObject()->isDisabled())
		return;

	// only allowed at objects
	return;
}

// ------------------------------------------------------------------------------------------------
// ?DefectorSpecialPower::doSpecialPowerAtObject present-unmatched
void DefectorSpecialPower::doSpecialPowerAtObject( Object *objectToMakeDefector, UnsignedInt commandOptions )
{
	if (getObject()->isDisabled())
		return;

	// sanity check
	if (!objectToMakeDefector)
	{
		return;
	}

	// another sanity check
	const Object *self = getObject();
	if (!self)
	{
		return;
	}

	// call the base class action cause we are *EXTENDING* functionality
  SpecialPowerModule::doSpecialPowerAtObject( objectToMakeDefector, commandOptions );

	//AIUpdateInterface *hisAI = objectToMakeDefector->getAIUpdateInterface();
	//if (hisAI)
	//{			
		// how do I get at SpecialPowerTemplate::getDetectionTime() from here?
		const SpecialPowerTemplate *specPowTemp = getSpecialPowerTemplate();
		UnsignedInt time = specPowTemp->getDetectionTime();


		objectToMakeDefector->defect(self->getControllingPlayer()->getDefaultTeam(), time );// @todo lorenzen hook into the new AIUpdateI methods
	//}

}  

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?DefectorSpecialPower::crc present-unmatched
void DefectorSpecialPower::crc( Xfer *xfer )
{

	// extend base class
	SpecialPowerModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// ?DefectorSpecialPower::xfer present-unmatched
void DefectorSpecialPower::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	SpecialPowerModule::xfer( xfer );

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// Retail 0x004C8A2F: the five-byte tail jump to SpecialPowerModule::loadPostProcess (0x00493B1E) that slot 1 of
// the class's primary table holds; retail folds CashHackSpecialPower's and DefectorSpecialPower's copies.
void DefectorSpecialPower::loadPostProcess( void )
{

	// extend base class
	SpecialPowerModule::loadPostProcess();

}  // end loadPostProcess
