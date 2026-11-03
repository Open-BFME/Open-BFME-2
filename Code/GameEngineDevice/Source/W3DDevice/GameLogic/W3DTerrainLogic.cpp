// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/zh_outofline /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogic.cpp); this unit had no counterpart under Code/.
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

// FILE: W3DTerrainLogic.cpp //////////////////////////////////////////////////////////////////////
// W3D implementation details for logical terrain
// Author: Colin Day, April 2001
///////////////////////////////////////////////////////////////////////////////////////////////////

// Retail calls _mbscpy through the import thunk at 0x00629176.
#include <mbstring.h>
#include "Common/GameMemory.h"
#include "W3DDevice/GameClient/HeightMap.h"
#include "W3DDevice/GameLogic/W3DTerrainLogic.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "Common/PerfTimer.h"
#include "Common/MapReaderWriterInfo.h"
#include "Common/GlobalData.h"
#include "Common/Xfer.h"
#include "GameClient/GameClient.h"

#include "GameClient/MapUtil.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
// bfme link decl-only begin
namespace _STL { template <> ICoord2D * allocator<ICoord2D>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??4?$vector@UICoord2D@@V?$allocator@UICoord2D@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct ICoord2D;
namespace _STL { template <> vector<ICoord2D,allocator<ICoord2D> > & vector<ICoord2D,allocator<ICoord2D> >::operator=(vector<ICoord2D,allocator<ICoord2D> > const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PBUICoord2D@@PAU1@@_STL@@YAPAUICoord2D@@PBU1@0PAU1@ABU__false_type:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct ICoord2D;
namespace _STL { template <> ICoord2D * __uninitialized_copy<ICoord2D const *,ICoord2D *>(ICoord2D const *,ICoord2D const *,ICoord2D *,__false_type const &); }

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// The constructor 0x00062A7E is defined in TerrainLogicCtor_Rva00062A7EProduct.cpp and the
// destructor 0x00062AF7 in OpaqueSingleInheritanceDtors.cpp.

//-------------------------------------------------------------------------------------------------
/** Device DEPENDENT implementation init details for logical terrain */
//-------------------------------------------------------------------------------------------------
// W3DTerrainLogic::init (retail 0x00062B17) is defined in Rva00062B17Init.cpp,
// which uses BFME 2's field offsets rather than the Zero Hour header layout
// this unit compiles against.

//-------------------------------------------------------------------------------------------------
/** Reset */
//-------------------------------------------------------------------------------------------------
// W3DTerrainLogic::reset (retail 0x00062B44) is defined in
// W3DTerrainLogicReset.cpp, which uses BFME 2's field offsets rather than the
// Zero Hour header layout this unit compiles against.

//-------------------------------------------------------------------------------------------------
/** newMap */
//-------------------------------------------------------------------------------------------------
void W3DTerrainLogic::newMap( Bool saveGame )
{

	TheTerrainRenderObject->loadRoadsAndBridges( this, saveGame );
	TerrainLogic::newMap( saveGame );
}  // end update

//-------------------------------------------------------------------------------------------------
/** Update */
//-------------------------------------------------------------------------------------------------
/** Device DEPENDENT implementation for load details of logical terrain.
Note - if query is true, we are  */
//-------------------------------------------------------------------------------------------------
// Zero Hour's loadMap, getExtent, getMaximumPathfindExtent and getExtentIncludingBorder
// bodies are gone: none is rowed, nothing outside this unit referenced them, and loadMap
// pulled in Zero Hour-only names (CachedFileInputStream, WorldHeightMap's stream ctor).

//-------------------------------------------------------------------------------------------------
Bool W3DTerrainLogic::isClearLineOfSight(const Coord3D& pos, const Coord3D& posOther) const
{
	if (TheTerrainRenderObject) 
	{
		return TheTerrainRenderObject->isClearLineOfSight(pos, posOther);
	}	
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------------------------
/** W3D specific get height function for logical terrain */
//-------------------------------------------------------------------------------------------------
// W3DTerrainLogic::getGroundHeight is rowed at 0x00062C45 (Rva00062FFFTerrainMaximumExtent.cpp)
// with BFME2's body; the Zero Hour copy here was a second, non-retail definition.

//-------------------------------------------------------------------------------------------------
/** Get the height considering the layer. */
//-------------------------------------------------------------------------------------------------
// W3DTerrainLogic::getLayerHeight is defined in W3DTerrainLogicGetLayerHeight.cpp.
//-------------------------------------------------------------------------------------------------
/** W3D isCliffCell for terrain logic */
//-------------------------------------------------------------------------------------------------
Bool W3DTerrainLogic::isCliffCell( Real x, Real y) const
{

	return TheTerrainRenderObject->isCliffCell(x,y);

}  // end isCliffCell

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// Zero Hour's crc override is gone: BFME 2's Snapshot table has no crc slot.

// ------------------------------------------------------------------------------------------------
/** Xfer
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicXfer.cpp

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// W3DTerrainLogic::loadPostProcess (retail 0x00062E4A) is defined in TerrainLogicBridges.cpp.

// ?rva000DE5B7@Rva000DE5B7@@QAE?AVAsciiString@@XZ 0x000DE5B7 27 callee StringBase copy 0x000365F0 callers 0x000DE648 0x002DB64E
// 27B AsciiString getter at +0x48 through the rowed StringBase copy ctor; same shape as
// GameInfo::getMap 0x0023E943 and Rva002041E1 0x002041E1 (27B, /O1 /EHsc).
struct Rva000DE5B7
{
	char m_pad[0x48];
	AsciiString m_str;
	AsciiString rva000DE5B7();
};

AsciiString Rva000DE5B7::rva000DE5B7()
{
	return m_str;
}

// ?rva000DE59C@Rva000DE59C@@QAE?AVAsciiString@@XZ 0x000DE59C 27 callee StringBase copy 0x000365F0 callers 0x000DE870 0x002DB6FD
// 27B AsciiString getter at +0x34 through the rowed StringBase copy ctor; same shape as
// Rva000DE5B7 0x000DE5B7 and GameInfo::getMap 0x0023E943 (27B, /O1 /EHsc).
struct Rva000DE59C
{
	char m_pad[0x34];
	AsciiString m_str;
	AsciiString rva000DE59C();
};

AsciiString Rva000DE59C::rva000DE59C()
{
	return m_str;
}

// Native 00062E64..00062E6A: standalone RET0 leaf from the unattempted gap
// audit. Read the +4 word then subtract the +0 word. The native accesses
// establish the word widths and offsets; the original owner, signedness and
// field meanings are unresolved. Keep the neutral member in its approved TU.
class Rva00062E64
{
public:
 unsigned rva00062E64() const;
private:
 unsigned word00, word04;
};
unsigned Rva00062E64::rva00062E64() const
{
 return word04-word00;
}
