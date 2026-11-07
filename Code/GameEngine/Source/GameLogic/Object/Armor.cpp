// cl: /FIzh_ascii.h /Ireference/shims/bfme2_drawable_flash /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Armor.cpp); this unit had no counterpart under Code/.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &lhs, const unsigned int &rhs)
{
    return lhs < rhs ? rhs : lhs;
}
}

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

// FILE: ArmorTemplate.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, November 2001
// Desc:   ArmorTemplate descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine


#include "Common/INI.h"
#include "Common/ThingFactory.h"
#include "GameLogic/Armor.h"
#include "GameLogic/Damage.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL {
// The allocator is stateless; only the stored pointers need exchanging.
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &left,
                            _STLP_alloc_proxy<void **, void *, allocator<void *> > &right)
{
    swap(left._M_data, right._M_data);
}
}

namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
ArmorStore* TheArmorStore = NULL;					///< the ArmorTemplate store definition

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
ArmorTemplate::ArmorTemplate()
{
	clear();
}

//-------------------------------------------------------------------------------------------------
// ArmorTemplate::clear is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/ArmorTemplateParse.cpp (0x001D8F1F).

//-------------------------------------------------------------------------------------------------
// ?ArmorTemplate::adjustDamage present-unmatched
Real ArmorTemplate::adjustDamage(DamageType damageType, Real damage) const 
{ 
	if (damageType == DAMAGE_UNRESISTABLE)
		return damage;
	if (damageType == DAMAGE_SUBDUAL_UNRESISTABLE)
		return damage;

	damage *= m_damageCoefficient[damageType];

	if (damage < 0.0f)
		damage = 0.0f;
	
	return damage;
}

//-------------------------------------------------------------------------------------------Static
// ArmorTemplate::parseArmorCoefficients is owned by ArmorTemplateParse.cpp.


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ArmorStore construction is defined in ArmorStoreCtor.cpp.

//-------------------------------------------------------------------------------------------------
// ??1ArmorStore@@UAE@XZ is rowed in its own unit; this copy collided with it.

//-------------------------------------------------------------------------------------------------
// ArmorStore::findArmorTemplate is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/ArmorStoreCtor.cpp (0x00360966).

//-------------------------------------------------------------------------------------------------
// ArmorStore::parseArmorDefinition is owned by ArmorStoreParse.cpp (1D9484).

//-------------------------------------------------------------------------------------------------
/*static*/ void INI::parseArmorDefinition(INI *ini)
{
	ArmorStore::parseArmorDefinition(ini);
}


// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva0060CC99Member@@QAE@XZ=??1?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:?find@FXListMap@@QBEPAUFXListMapNode@@ABW4NameKeyType@@@Z=??$_M_find@W4NameKeyType@@@?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@ABEPAU?$_Hashtable_node@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@1@ABW4NameKeyType@@@Z")

// Callers elsewhere reach this body through a spelling pinned to the same retail
// address with the same calling convention; bind it here.
#pragma comment(linker, "/alternatename:?resize@KeyToBucketMap@NameKeyGenerator@@AAEXI@Z=?resize@?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@5@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@QAEXI@Z")

// Keep the two rowed template bodies formerly emitted by the obsolete parser.
// Explicit instantiation preserves their real definitions without retaining a
// second ArmorStore::parseArmorDefinition.
typedef _STL::pair<const NameKeyType, ArmorTemplate> ArmorRowValue;
typedef _STL::hashtable<ArmorRowValue, NameKeyType, rts::hash<NameKeyType>,
    _STL::_Select1st<ArmorRowValue>, rts::equal_to<NameKeyType>,
    _STL::allocator<ArmorRowValue> > ArmorRowTable;
template _STL::_Hashtable_node<ArmorRowValue> *ArmorRowTable::_M_find<NameKeyType>(const NameKeyType &) const;
template void ArmorRowTable::resize(unsigned int);
template void ArmorRowTable::clear();
template void ArmorRowTable::_M_initialize_buckets(unsigned int);
#pragma inline_depth(0)
// ?armorMapDestructorAnchor absent-from-retail
void armorMapDestructorAnchor(_STL::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > *map)
{
    map->~hash_map();
}

#pragma inline_depth(8)

// INI block registration (LINK-236). BFME's INI keeps its block types on a
// list of 12-byte BlockParse nodes; each unit links its own nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the
// link. MSVC 7.1 builds token and parse in .data, so the node's .text$yc
// initializer is only the 21-byte link. Retail's table holds this
// unit's Drawable.h copy 0x007ACFE5 (static 0x00DFDBCC after TheArmorStore),
// then this node's entry 0x007ACFF5 (node 0x00DB8A74), then its pool-init
// marker 0x007AD00A.
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theArmorBlockParse( "Armor", ArmorStore::parseArmorDefinition );
