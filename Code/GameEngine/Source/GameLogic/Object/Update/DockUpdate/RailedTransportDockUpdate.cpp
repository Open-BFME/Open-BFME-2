// cl: /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate.cpp); this unit had no counterpart under Code/.
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate.cpp); this unit had no counterpart under Code/.
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: RailedTransportDockUpdate.cpp ////////////////////////////////////////////////////////////
// Author: Colin Day, August 2002
// Desc:   Railed Transport Dock Update
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Module/RailedTransportDockUpdate.h"

// TYPES //////////////////////////////////////////////////////////////////////////////////////////
enum { UNLOAD_ALL = -1 };

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/INI/ini_parsers.cpp
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*static*/ void RailedTransportDockUpdateModuleData::buildFieldParse( MultiIniFieldParse &multiIniFieldParse )
{
  DockUpdateModuleData::buildFieldParse( multiIniFieldParse );

	static const FieldParse dataFieldParse[] = 
	{

		{ "PullInsideDuration", INI::parseDurationUnsignedInt, NULL, offsetof( RailedTransportDockUpdateModuleData, m_pullInsideDurationInFrames ) },	
		{ "PushOutsideDuration",INI::parseDurationUnsignedInt, NULL, offsetof( RailedTransportDockUpdateModuleData, m_pushOutsideDurationInFrames ) },
		{ "ToleranceDistance",  INI::parseReal,								 NULL, offsetof( RailedTransportDockUpdateModuleData, m_toleranceDistance ) },
		{ 0, 0, 0, 0 }

	};

  multiIniFieldParse.add( dataFieldParse );

}  // end buildFieldParse

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0RailedTransportDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z owned by RailedTransportDockUpdateCtor.cpp; declared here only.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1RailedTransportDockUpdate@@MAE@XZ present-unmatched
RailedTransportDockUpdate::~RailedTransportDockUpdate( void )
{

}  // end ~RailedTransportDockUpdate

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** The dock action callback, return FALSE when done docking */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Is clear to enter the railed transport */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Is anything currently loading or unloading */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Start the unload process */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Unload a single individual only */
// ------------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
/** If we have an object recorded as currently docking with us, pull that object inside
	* and when it is inside, contain it */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** If we have an object recorded as being pushed out of us then do that here */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Iterate callback for the finding the first contained object */
// ------------------------------------------------------------------------------------------------
static void getFirstContain( Object *obj, void *userData )
{
	Object **firstContain = (Object **)userData;

	// if object has been found get out of here
	if( *firstContain != NULL )
		return;

	// assign this as the first object found
	*firstContain = obj;

}  // end getFirstContain

// ------------------------------------------------------------------------------------------------
/** Start the next object contained by us as "unloading and coming out" */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WWLib/UpdateInitializationThunks.cpp
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
// The callee at 0x0044FC52 is the rowed virtual
// SpecialAbilityUpdate::continuePreparation, called directly.
class SpecialAbilityUpdate
{
public:
	virtual bool continuePreparation();
};

class Rva004B01E6Owner
{
public:
	bool rva004B01E6();

private:
	char m_pad00[0x24];
	int m_24;
};

// ?rva004B01E6@Rva004B01E6Owner@@QAE_NXZ
bool Rva004B01E6Owner::rva004B01E6()
{
	if (m_24 == 2)
		return false;
	return ((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::continuePreparation();
}
