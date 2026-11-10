// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/DamageFX.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
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

// FILE: DamageFX.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, November 2001
// Desc:   DamageFX descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/INI.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/DamageFX.h"
#include "Common/GameAudio.h"

#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$hash_map@W4NameKeyType@@VDamageFX@@U?$hash@W4NameKeyType@@@rts@@U?$equal_to@W4NameKey:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class DamageFX;
namespace _STL { template <> hash_map<NameKeyType,DamageFX,rts::hash<NameKeyType>,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,DamageFX> > >::hash_map(); }
// Suppress this TU's non-retail copy of the DamageFX hashtable destructor: the kept copy is the
// retail /GX body 0x0016DEE0 (Rva0016DEE0Cluster.cpp). Plain declaration-only form (no __imp_).
namespace _STL { template <> hashtable<pair<NameKeyType const ,DamageFX>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,DamageFX> >,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,DamageFX> > >::~hashtable(); }
// Suppress this TU's non-retail copy of ??0?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV?$allocator@PAX@1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> vector<void *,allocator<void *> >::vector(allocator<void *> const &); }

// LINK-COMDAT: rts::equal_to<NameKeyType> is kept as the /O1 copy from FXList.cpp;
// this TU is default-flag for its hashtable clear row, so its own copy differs.
// Specialize only the member under "s" so our emitted copy matches the kept /O1 body,
// while inlined key compares and the clear row keep default flags (as in FXListMapNodeEmit.cpp).
namespace rts {
template<> Bool equal_to<NameKeyType>::operator()(const NameKeyType &a, const NameKeyType &b) const { return a == b; }
}
#pragma optimize("", on)

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

DamageFXStore *TheDamageFXStore = NULL;					///< the DamageFX store definition

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE CLASSES ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// ?DamageFX::DamageFX present-unmatched
DamageFX::DamageFX()
{
	// not necessary.
	//clear();
}

//-------------------------------------------------------------------------------------------------
// ?DamageFX::clear present-unmatched
void DamageFX::clear()
{
	for (Int dt = 0; dt < DAMAGE_NUM_TYPES; ++dt)
	{
		for (Int v = LEVEL_FIRST; v <= LEVEL_LAST; ++v)
		{
			m_dfx[dt][v].clear();
		}
	}
}

//-------------------------------------------------------------------------------------------------
// DamageFX::getDamageFXThrottleTime, getDamageFXList and doDamageFX: the Zero Hour bodies are
// not retail's. BFME 2's versions take no veterancy level and are rowed under placeholder names:
// 0x003605D5 (DamageFXRva003605AF.cpp), 0x003605E3 and 0x003608DF (DamageFXParseCommon.cpp).

//-------------------------------------------------------------------------------------------------
// DamageFX::getFieldParse is rowed in its home unit; this copy was a duplicate definition.

//-------------------------------------------------------------------------------------------------
// parseCommonStuff and DamageFX::parseAmount/parseMajorFXList/parseMinorFXList/parseTime are rowed
// in DamageFXParseCommon.cpp; the Zero Hour copies here were duplicate definitions.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::DamageFXStore present-unmatched
DamageFXStore::DamageFXStore()
{
	m_dfxmap.clear();
}

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::~DamageFXStore present-unmatched
DamageFXStore::~DamageFXStore()
{
	m_dfxmap.clear();
}

//-------------------------------------------------------------------------------------------------
// DamageFXStore::findDamageFX: retail's symbol (0x00360966) is the ArmorStore::findArmorTemplate
// body (ArmorStoreCtor.cpp), which its caller Rva0033962FFinish.cpp already calls; the Zero Hour
// body here is not retail's.

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::init present-unmatched
void DamageFXStore::init()
{
}

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::reset present-unmatched
void DamageFXStore::reset()
{
} 

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::update present-unmatched
void DamageFXStore::update()
{
}
