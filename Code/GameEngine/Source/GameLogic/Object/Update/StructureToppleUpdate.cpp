// cl: /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
#define BFME_SNAPSHOT_NAME_SLOT
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate.cpp); this unit had no counterpart under Code/.
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
#include "GameLogic/Module/StructureToppleUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/Weapon.h"
#include "GameClient/Drawable.h"
#include "GameClient/InGameUI.h"
// bfme link decl-only begin
namespace _STL { template <> AngleFXInfo * allocator<AngleFXInfo>::allocate(unsigned int, void const *) const; }
namespace _STL {
template <> void vector<AngleFXInfo>::_M_insert_overflow(AngleFXInfo *, const AngleFXInfo &, const __false_type &, unsigned int, bool);
template <> inline void vector<AngleFXInfo>::push_back(const AngleFXInfo &value)
{
    if (this->_M_finish != this->_M_end_of_storage._M_data) {
        _Construct(this->_M_finish, value);
        ++this->_M_finish;
    } else {
        _IsPODType tag;
        _M_insert_overflow(this->_M_finish, value, tag, 1UL, true);
    }
}
}
template AngleFXInfo *_STL::__uninitialized_fill_n<AngleFXInfo *, unsigned int, AngleFXInfo>(AngleFXInfo *, unsigned int, const AngleFXInfo &, const _STL::__false_type &);
// bfme link decl-only end

// codegen otherwise instantiates the max<unsigned> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy. TRANSITIVE anchor (no angle includes here).
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
// The Zero Hour destructor body is not retail's: ~StructureToppleUpdate is rowed at
// 0x004A54A8 in Rva0024A797Grandchildren.cpp. Defining it here emitted this header's
// Zero Hour vftables first in link order, so the retail-shaped copies lost (LINK-168).

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

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void StructureToppleUpdate::loadPostProcess( void )
{

	// extend base class
	UpdateModule::loadPostProcess();

}  // end loadPostProcess
