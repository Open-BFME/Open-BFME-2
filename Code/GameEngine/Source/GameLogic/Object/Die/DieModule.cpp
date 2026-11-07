// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Die/DieModule.cpp); this unit had no counterpart under Code/.
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

// FILE: DieModule.cpp ////////////////////////////////////////////////////////////////////////////
// Author:
// Desc:   
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_OBJECT_STATUS_NAMES
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/DieModule.h"
#include "GameLogic/Object.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif



//-------------------------------------------------------------------------------------------------
// BFME2's table (retail 0x00C5FFA0, the address getFieldParse 0x004CE52E
// returns) differs from Zero Hour's: no VeterancyLevels, three damage fields
// added. Its layout is BFME2's DieMuxData (DieMuxDataInit.cpp: init 0x004CE534
// and isDieApplicable 0x004CE588), not the Zero Hour header's, so the offsets
// are retail's: death-type word +0x00, exempt/required 128-bit status masks
// +0x04/+0x14, damage threshold +0x24, killer angles +0x28/+0x2C. The status
// masks parse through 0x003B1327, rowed ?parseFromINI@Rva003B1017@@...
class Rva003B1017 { public: static void parseFromINI( INI *ini, void *instance, void *store, const void *userData ); };

const FieldParse* DieMuxData::getFieldParse()
{
	static const FieldParse dataFieldParse[] =
	{
		{ "DeathTypes",						INI::parseDeathTypeFlags,		NULL, 0x00 },
		{ "ExemptStatus",					Rva003B1017::parseFromINI,	NULL, 0x04 },
		{ "RequiredStatus",				Rva003B1017::parseFromINI,	NULL, 0x14 },
		{ "DamageAmountRequired",	INI::parseReal,							NULL, 0x24 },
		{ "MinKillerAngle",				INI::parseAngleReal,				NULL, 0x28 },
		{ "MaxKillerAngle",				INI::parseAngleReal,				NULL, 0x2C },
		{ 0, 0, 0, 0 }
	};
  return dataFieldParse;
}

// Rowed here at 0x004D051E (13B, no retail caller; placed by a unique masked
// search): Zero Hour's table reached it through BitFlags<>::parse, which the
// retail table above no longer instantiates.
template unsigned long _STL::_Base_bitset<2>::_S_maskbit(size_t);

//-------------------------------------------------------------------------------------------------
// Target-specific applicability is owned by DieMuxDataInit.cpp.

// BFME2 has no crc (its Snapshot slot 2 is GetSnapshotName). DieModule's other
// Snapshot slots are the shared 0x0058B03E (loadPostProcess) and 0x004CE56D
// (xfer) rowed elsewhere, so this unit defines none of them.
