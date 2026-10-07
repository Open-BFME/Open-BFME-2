// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp); this unit had no counterpart under Code/.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
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

// FILE: BoneFXUpdate.cpp ///////////////////////////////////////////////////////////////////////
// Author:
// Desc:  
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/GameState.h"
#include "Common/Thing.h"
#include "Common/ThingTemplate.h"
#include "Common/INI.h"
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/FXList.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Module/BoneFXUpdate.h"
#include "GameLogic/Module/BoneFXDamage.h"

const Int MAX_IDX = 32;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0BoneFXUpdateModuleData@@QAE@XZ
// Body in BoneFXUpdate_0BoneFXUpdateModuleData.asm (exact 332B retail).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BoneFXUpdate::BoneFXUpdate: defined in BoneFXUpdateCtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// ?onObjectCreated@BoneFXUpdate@@ present-unmatched
void BoneFXUpdate::onObjectCreated()
{
	static NameKeyType key_BoneFXDamage = NAMEKEY("BoneFXDamage");
	BoneFXDamage* bfxd = (BoneFXDamage*)getObject()->findDamageModule(key_BoneFXDamage);
	if (bfxd == NULL)
	{
		DEBUG_CRASH(("BoneFXUpdate requires BoneFXDamage"));
		throw INI_INVALID_DATA;
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BoneFXUpdate::~BoneFXUpdate: defined in BoneFXUpdateDtor.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
/** Parse fx location info ... that is a named bone */
//-------------------------------------------------------------------------------------------------
static void parseFXLocInfo( INI *ini, void *instance, BoneLocInfo *locInfo )
{
	const char *token = ini->getNextToken( ini->getSepsColon() );

	if( stricmp( token, "bone" ) == 0 )
	{

		// save bone name and location type
		locInfo->boneName = ini->getNextToken();

	}  // end if
	else
	{

		// error
		throw INI_INVALID_DATA;

	}  // end else

}  // end parseFXLocInfo

//-------------------------------------------------------------------------------------------------
/** Parse a random delay.  This is a number pair, where the numbers are a min and max time in miliseconds. */
//-------------------------------------------------------------------------------------------------
void parseGameClientRandomDelay( INI *ini, void *instance, GameClientRandomVariable *delay)
{
	Real min, max;
	INI::parseDurationReal(ini, instance, &min, NULL);
	INI::parseDurationReal(ini, instance, &max, NULL);

	delay->setRange(min, max, GameClientRandomVariable::DistributionType::UNIFORM);
}

static void parseGameLogicRandomDelay( INI *ini, void *instance, GameLogicRandomVariable *delay)
{
	Real min, max;
	INI::parseDurationReal(ini, instance, &min, NULL);
	INI::parseDurationReal(ini, instance, &max, NULL);

	delay->setRange(min, max, GameLogicRandomVariable::DistributionType::UNIFORM);
}

//-------------------------------------------------------------------------------------------------
/** In the form of:
	* <BodyDamageState>FXList<index> = Bone:<BoneName> OnlyOnce:<Yes|No> <Min delay> <Max delay> FXList:<FXListName> */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/BoneFXUpdateModuleDataParseFXListThunk.cpp
// BoneFXUpdateModuleData::parseFXList: defined in BoneFXUpdateParse.cpp (its row's unit).
  // end parseFXList

//-------------------------------------------------------------------------------------------------
/** In the form of:
	* <BodyDamageState>OCL<index> = Bone:<BoneName> OnlyOnce:<Yes|No> <Min delay> <Max delay> OCL:<OCLName> */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/BoneFXUpdateModuleDataParseObjectCreationListThunk.cpp
// BoneFXUpdateModuleData::parseObjectCreationList: defined in BoneFXUpdateParse.cpp (its row's unit).
  // end parseObjectCreationList

//-------------------------------------------------------------------------------------------------
/** In the form of:
	* <BodyDamageState>ParticleSystem<index> = <Bone:BoneName> OnlyOnce:<Yes|No> <Min delay> <Max delay> PSys:<PSysName> */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/RTS/FXModuleDataParseParticleSystemThunks.cpp
// BoneFXUpdateModuleData::parseParticleSystem: defined in BoneFXUpdateParse.cpp (its row's unit).
  // end parseParticleSystem

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/Common/BoneFXUpdate_update_Thunk.cpp
// BoneFXUpdate::update is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateUpdate.cpp (0x00487DEE).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/Libraries/Source/WWVegas/WWLib/UpdateInitializationThunks.cpp
// BoneFXUpdate::initTimes: defined in BoneFXUpdate_initTimes.cpp (its row's unit).

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
void BoneFXUpdate::changeBodyDamageState(BodyDamageType oldState, BodyDamageType newState)
{
	m_curBodyState = newState;
	killRunningParticleSystems();
	initTimes();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BoneFXUpdate::doFXListAtBone is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateUpdate.cpp (0x0048740D).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BoneFXUpdate::doOCLAtBone is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateUpdate.cpp (0x00487480).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BoneFXUpdate::doParticleSystemAtBone is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateUpdate.cpp (0x00487B7D).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void BoneFXUpdate::computeNextClientFXTime(const BaseBoneListInfo *info, Int &nextFrame)
{
	if (info->onlyOnce) {
		nextFrame = -1;
		return;
	}
	// Retail reads GameLogic's current-frame field at +0x40; the included
	// GeneralsMD getFrame() view reads +0x3C. Keep the target-specific layout
	// local to this body instead of changing the shared GameLogic header.
	struct BfmeGameLogicFrameView {
		UnsignedByte unknown[0x40];
		Int frame;
	};
	Int frame = ((const BfmeGameLogicFrameView *)TheGameLogic)->frame;
	nextFrame = frame + static_cast<Int>(info->gameClientDelay.getValue());
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void BoneFXUpdate::computeNextLogicFXTime(const BaseBoneListInfo *info, Int &nextFrame)
{
	if (info->onlyOnce) {
		nextFrame = -1;
		return;
	}
	// Retail reads GameLogic's current-frame field at +0x40; the included
	// GeneralsMD getFrame() view reads +0x3C. Keep the target-specific layout
	// local to this body instead of changing the shared GameLogic header.
	struct BfmeGameLogicFrameView {
		UnsignedByte unknown[0x40];
		Int frame;
	};
	Int frame = ((const BfmeGameLogicFrameView *)TheGameLogic)->frame;
	nextFrame = frame + static_cast<Int>(info->gameLogicDelay.getValue());
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void BoneFXUpdate::killRunningParticleSystems() {
	// retail calls the combined find+destroy convenience method here, not the
	// separate findParticleSystem()/destroy() pair the ZH source used
	for (std::vector<ParticleSystemID>::iterator it = m_particleSystemIDs.begin(); it != m_particleSystemIDs.end(); ++it)
	{
		TheParticleSystemManager->destroyParticleSystemByID(*it);
	}

	m_particleSystemIDs.clear();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// This function is going to suck lots of time, should only be called once.
// BoneFXUpdate::resolveBoneLocations: defined in BoneFXUpdate_resolveBoneLocations.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void BoneFXUpdate::stopAllBoneFX() {
	int i, j;
	for (i = 0; i < BODYDAMAGETYPE_COUNT; ++i) {
		for (j = 0; j < BONE_FX_MAX_BONES; ++j) {
			m_nextFXFrame[i][j] = -1;
			m_nextOCLFrame[i][j] = -1;
			m_nextParticleSystemFrame[i][j] = -1;
		}
	}
	killRunningParticleSystems();
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ?crc@BoneFXUpdate@@MAEXPAVXfer@@@Z present-unmatched
void BoneFXUpdate::crc( Xfer *xfer )
{

	// extend base class
	UpdateModule::crc( xfer );

}  // end crc

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateXfer.cpp

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// ?loadPostProcess@BoneFXUpdate@@MAEXXZ present-unmatched
void BoneFXUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
