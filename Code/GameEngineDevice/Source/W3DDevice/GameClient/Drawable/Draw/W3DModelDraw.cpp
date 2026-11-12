// cl: /Ireference/shims/bfme_obbox_transform_link /DBFME_WEAPON_BARREL_INLINE_ONLY /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/w3dmodeldraw8 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// Link view first: Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x0004C91A, 0x0006645C).
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
// Retail imports only _strcmpi (stub 0x00629A2A calls msvcr71's); BFME2's
// stricmp spelling resolves there, not to the _stricmp alias.
#define stricmp _strcmpi
#include "../../../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "../../../../../../../reference/shims/bfme_matrix3d_copy_link/matrix3d_copy_link.h"
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp); this unit had no counterpart under Code/.
#include "../../../../../../../reference/shims/bfme_namekey_inline_link/namekey_inline_link.h"  // NAMEKEY inline-only link view
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

// FILE: W3DModelDraw.cpp ///////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Default w3d draw module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_W3DANIMMODE_NAMES
#define DEFINE_WEAPONSLOTTYPE_NAMES

#define NO_DEBUG_CRC

// Retail spells _Rb_tree::insert_unique(const value_type&)'s leftmost fast path
// as `if (__comp && __j == begin())` with `_M_insert(__y, __y, __v)`; the
// vendored STLport carries that spelling behind this switch.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
// (Placed before quoted includes: Common/CRC.h -> winsock2 -> windows
// min/max macros would expand the declarator below.)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "Common/CRC.h"
// The exact assignment specialization is provided by StlportAsciiStringVectorAssign.cpp.
// Keep this consumer on that verified body rather than instantiate the stock copy.
#include <vector>
#include <map>
#include <math.h>
// Declare before W3DModelDraw.h instantiates the PristineBone map lifetime.
struct PristineBoneInfo;
namespace _STL {
template <> map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<const NameKeyType, PristineBoneInfo> > >::map();
template <> _Rb_tree<NameKeyType, pair<const NameKeyType, PristineBoneInfo>, _Select1st<pair<const NameKeyType, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<const NameKeyType, PristineBoneInfo> > >::~_Rb_tree();
}
#include "ascii_string.h"
namespace _STL {
// The retail find wrapper and search body are supplied by MpGameSetupSlots_Init_InitGadgets.cpp.
template <> AsciiString *find<AsciiString *, AsciiString>(AsciiString *, AsciiString *, const AsciiString &);
template <> vector<AsciiString, allocator<AsciiString> > &
vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> > &);
// Bottom-loop overload: this TU's flags compile the generic range-destroy to
// an early-out form, but retail's out-of-line copy is the bottom-tested loop
// (row 32 family-LK3). The overload wins for (AsciiString*,AsciiString*).
inline void _Destroy(AsciiString * __first, AsciiString * __last)
{ for (; __first != __last; ++__first) __first->~AsciiString(); }
}

#include "Common/CRCDebug.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/GameLOD.h"
#include "Common/Xfer.h"
#include "Common/GameState.h"
#include "Common/QuickTrig.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/Shadow.h"
#include "GameLogic/GameLogic.h"		// for real-time frame
#include "GameLogic/Object.h"
#include "GameLogic/WeaponSet.h"
#include "GameLogic/FPUControl.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
// Retail links the size-optimized WeightInfoStruct vector deleting destructor (??_E
// 0x0004554B); it takes the optimization state of the first function that needs it,
// so this unemitted anchor needs it first, as in hlod.cpp. The private struct is
// reached by befriending the anchor while hanim.h is first read; layout and names
// are unchanged.
struct BfmeWeightInfoVddAnchor;
#define private private: friend struct BfmeWeightInfoVddAnchor; private
#include "WW3D2/HAnim.h"
#undef private
struct BfmeWeightInfoVddAnchor { typedef NamedPivotMapClass::WeightInfoStruct Info; };
#pragma optimize("gsy", on)
static void bfmeWeightInfoVddAnchor(BfmeWeightInfoVddAnchor::Info *p) { delete [] p; }
#pragma optimize("", on)
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "WW3D2/HAnim.h"
#include "WW3D2/HLod.h"
#include "WW3D2/RendObj.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "Common/BitFlagsIO.h"

// ZH's inline intersection counters use std::bitset; retail uses four-word
// SWAR bodies in BitFlags117CountInverseIntersection.cpp (inverse: 0x0033AE53).
// Reference those providers instead of emitting competing non-retail COMDATs.
template<> int BitFlags<117>::countIntersection(const BitFlags<117> &that) const;
template<> int BitFlags<117>::countInverseIntersection(const BitFlags<117> &that) const;
// bfme link decl-only begin
// Retail's _Base_bitset<4>::_M_do_and is ThingTemplate.cpp's 25-byte row (0x00331662); this
// unit only emitted an unreferenced 29-byte copy, first in link order.
namespace _STL { template <> void _Base_bitset<4>::_M_do_and(const _Base_bitset<4> &); }
namespace _STL { template <> void _Construct<pair<NameKeyType const, PristineBoneInfo>, pair<NameKeyType const, PristineBoneInfo> >(pair<NameKeyType const, PristineBoneInfo> *, pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> AsciiString * __uninitialized_copy<AsciiString const *, AsciiString *>(AsciiString const *, AsciiString const *, AsciiString *, __false_type const &); }
namespace _STL { template <> _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_Rb_tree(less<NameKeyType> const &, allocator<pair<NameKeyType const, PristineBoneInfo> > const &); }
namespace _STL { template <> _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_Rb_tree(_Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > > const &); }
namespace _STL { template <> _Rb_tree_base<pair<NameKeyType const, PristineBoneInfo>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_Rb_tree_base(allocator<pair<NameKeyType const, PristineBoneInfo> > const &); }
namespace _STL { template <> map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::map(map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > > const &); }
namespace _STL { template <> pair<BitFlags<117> const, ModelConditionInfo const *>::pair(BitFlags<117> const &, ModelConditionInfo const *const &); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::vector(vector<AsciiString, allocator<AsciiString> > const &); }
namespace _STL { template <> _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > > & _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::operator=(_Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > > const &); }
namespace _STL { template <> map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > > & map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::operator=(map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > > const &); }
namespace _STL { template <> PristineBoneInfo & map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::operator[](NameKeyType const &); }
namespace _STL { template <> _Rb_tree_node<pair<NameKeyType const, PristineBoneInfo> > * _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_M_clone_node(_Rb_tree_node<pair<NameKeyType const, PristineBoneInfo> > *); }
namespace _STL { template <> _Rb_tree_node<pair<NameKeyType const, PristineBoneInfo> > * _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_M_copy(_Rb_tree_node<pair<NameKeyType const, PristineBoneInfo> > *, _Rb_tree_node<pair<NameKeyType const, PristineBoneInfo> > *); }
namespace _STL { template <> _Rb_tree_node<pair<NameKeyType const, PristineBoneInfo> > * _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_M_create_node(pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> void _Base_bitset<4>::_M_do_reset(); }
namespace _STL { template <> _Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > > _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, pair<NameKeyType const, PristineBoneInfo> const &, _Rb_tree_node_base *); }
namespace _STL { template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString *, AsciiString const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> bool _Base_bitset<4>::_M_is_any() const; }
namespace _STL { template <> unsigned long _Base_bitset<4>::_S_maskbit(unsigned int); }
namespace _STL { template <> bitset<117> & bitset<117>::_Unchecked_set(unsigned int, int); }
namespace _STL { template <> void map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::clear(); }
template <> int SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::countConditionInverseIntersection(BitFlags<117> const &, BitFlags<117> const &);
template <> ModelConditionInfo const * SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::findBestInfo(_STL::vector<ModelConditionInfo, _STL::allocator<ModelConditionInfo> > const &, BitFlags<117> const &) const;
template <> ModelConditionInfo const * SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::findBestInfoSlow(_STL::vector<ModelConditionInfo, _STL::allocator<ModelConditionInfo> > const &, BitFlags<117> const &) const;
namespace _STL { template <> _Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > > map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::insert(_Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > >, pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > > _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::insert_unique(_Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > >, pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > >, bool> _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::insert_unique(pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> void vector<AsciiString, allocator<AsciiString> >::push_back(AsciiString const &); }
// Use the standalone tree-clear provider, whose genuine STLport erase
// callee also supplies the native out-of-line body.
namespace _STL {
template <> void _Rb_tree<NameKeyType, pair<const NameKeyType, PristineBoneInfo>, _Select1st<pair<const NameKeyType, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<const NameKeyType, PristineBoneInfo> > >::clear();
}
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAVAsciiString@@V1@V?$allocator@VAsciiString@@@_STL@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> void _STLP_alloc_proxy<AsciiString *,AsciiString,allocator<AsciiString> >::deallocate(AsciiString *,unsigned int); }
// Suppress this TU's non-retail copy of ??0?$_Base_bitset@$03@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Base_bitset<4>::_Base_bitset(); }
// Suppress this TU's non-retail copy of ?set@?$bitset@$0HF@@_STL@@QAEAAV12@IH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bitset<117> & bitset<117>::set(unsigned int,int); }
// Suppress this TU's non-retail copy of ?test@?$bitset@$0HE@@_STL@@QBE_NI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool bitset<116>::test(unsigned int) const; }
// Suppress this TU's non-retail copy of ?_Unchecked_test@?$bitset@$0HE@@_STL@@QBE_NI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool bitset<116>::_Unchecked_test(unsigned int) const; }

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
static inline Bool isValidTimeToCalcLogicStuff()
{
	return (TheGameLogic && TheGameLogic->isInGameLogicUpdate()) ||
		(TheGameState && TheGameState->isInLoadGame());
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#if defined(DEBUG_CRC) && (defined(_DEBUG) || defined(_INTERNAL))
// The retail release excludes these debug-only logging definitions.
#include <cstdarg>

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(size_t, const allocator<AsciiString>&);
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> >&);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
}
class LogClass
{
public:
	LogClass(const char *fname);
	~LogClass();
	void log(const char *fmt, ...);
	void dumpMatrix3D(const Matrix3D *m, AsciiString name, AsciiString fname, Int line);
	void dumpReal(Real r, AsciiString name, AsciiString fname, Int line);

protected:
	FILE *m_fp;
};

// ??0LogClass@@ absent-from-retail
LogClass::LogClass(const char *fname)
{
	char buffer[ _MAX_PATH ];
	GetModuleFileName( NULL, buffer, sizeof( buffer ) );
	char *pEnd = buffer + strlen( buffer );
	while( pEnd != buffer )
	{
		if( *pEnd == '\\' )
		{
			*pEnd = 0;
			break;
		}
		pEnd--;
	}
	AsciiString fullPath;
	fullPath.format("%s\\%s", buffer, fname);
	m_fp = fopen(fullPath.str(), "wt");
}

// ??1LogClass@@ absent-from-retail
LogClass::~LogClass()
{
	if (m_fp)
	{
		fclose(m_fp);
	}
}

// ?log@LogClass@@ absent-from-retail
void LogClass::log(const char *fmt, ...)
{
	DEBUG_ASSERTCRASH(isValidTimeToCalcLogicStuff(), ("Calc'ing logic bone pos in client!!!"));
	if (!m_fp /*|| !isValidTimeToCalcLogicStuff()*/)
		return;
	static char buf[1024];
	static Int lastFrame = 0;
	static Int lastIndex = 0;
	if (lastFrame != TheGameLogic->getFrame())
	{
		lastFrame = TheGameLogic->getFrame();
		lastIndex = 0;
	}

	va_list va;
	va_start( va, fmt );
	_vsnprintf(buf, 1024, fmt, va );
	buf[1023] = 0;
	va_end( va );

	char *tmp = buf;
	while (tmp && *tmp)
	{
		if (*tmp == '\r' || *tmp == '\n')
		{
			*tmp = ' ';
		}
		++tmp;
	}

	fprintf(m_fp, "%d:%d %s\n", lastFrame, lastIndex++, buf);
	fflush(m_fp);
}

// ?dumpMatrix3D@LogClass@@ absent-from-retail
void LogClass::dumpMatrix3D(const Matrix3D *matrix3D, AsciiString name, AsciiString fname, Int line)
{
	((StringBase<char> &)(fname)).toLower();
	fname = fname.reverseFind('\\') + 1;
	const Real *matrix = (const Real *)matrix3D;
	log("dumpMatrix3D() %s:%d %s\n",
		fname.str(), line, name.str());
	for (Int i=0; i<3; ++i)
		log("      0x%08X 0x%08X 0x%08X 0x%08X\n",
			AS_INT(matrix[(i<<2)+0]), AS_INT(matrix[(i<<2)+1]), AS_INT(matrix[(i<<2)+2]), AS_INT(matrix[(i<<2)+3]));
}

// ?dumpReal@LogClass@@ absent-from-retail
void LogClass::dumpReal(Real r, AsciiString name, AsciiString fname, Int line)
{
	if (!m_fp || !isValidTimeToCalcLogicStuff())
		return;
	((StringBase<char> &)(fname)).toLower();
	fname = fname.reverseFind('\\') + 1;
	log("dumpReal() %s:%d %s %8.8X (%f)\n",
		fname.str(), line, name.str(), AS_INT(r), r);
}

LogClass BonePosLog("bonePositions.txt");

#define BONEPOS_LOG(x) BonePosLog.log x
#define BONEPOS_DUMPMATRIX3D(x) BONEPOS_DUMPMATRIX3DNAMED(x, #x)
#define BONEPOS_DUMPMATRIX3DNAMED(x, y) BonePosLog.dumpMatrix3D(x, y, __FILE__, __LINE__)
#define BONEPOS_DUMPREAL(x) BONEPOS_DUMPREALNAMED(x, #x)
#define BONEPOS_DUMPREALNAMED(x, y) BonePosLog.dumpReal(x, y, __FILE__, __LINE__)

#else // DEBUG_CRC

#define BONEPOS_LOG(x) {}
#define BONEPOS_DUMPMATRIX3D(x) {}
#define BONEPOS_DUMPMATRIX3DNAMED(x, y) {}
#define BONEPOS_DUMPREAL(x) {}
#define BONEPOS_DUMPREALNAMED(x, y) {}

#endif // DEBUG_CRC

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#if defined(_DEBUG) || defined(_INTERNAL)
extern AsciiString TheThingTemplateBeingParsedName;
extern Real TheSkateDistOverride;
#endif

// flags that aren't read directly from INI, but set in response to various other situations
enum INIReadFlagsType
{
	ANIMS_COPIED_FROM_DEFAULT_STATE = 0,
	GOT_NONIDLE_ANIMS,
	GOT_IDLE_ANIMS,
};

enum ACBits
{
	RANDOMIZE_START_FRAME = 0,
	START_FRAME_FIRST,
	START_FRAME_LAST,
	ADJUST_HEIGHT_BY_CONSTRUCTION_PERCENT,
	PRISTINE_BONE_POS_IN_FINAL_FRAME,
	MAINTAIN_FRAME_ACROSS_STATES,
	RESTART_ANIM_WHEN_COMPLETE,
	MAINTAIN_FRAME_ACROSS_STATES2,
	MAINTAIN_FRAME_ACROSS_STATES3,
	MAINTAIN_FRAME_ACROSS_STATES4,
};

static const char *ACBitsNames[] =
{
	"RANDOMSTART",
	"START_FRAME_FIRST",
	"START_FRAME_LAST",
	"ADJUST_HEIGHT_BY_CONSTRUCTION_PERCENT",
	"PRISTINE_BONE_POS_IN_FINAL_FRAME",
	"MAINTAIN_FRAME_ACROSS_STATES",
	"RESTART_ANIM_WHEN_COMPLETE",
	"MAINTAIN_FRAME_ACROSS_STATES2",
	"MAINTAIN_FRAME_ACROSS_STATES3",
	"MAINTAIN_FRAME_ACROSS_STATES4",
	
	NULL
};

static const Int ALL_MAINTAIN_FRAME_FLAGS =
	(1<<MAINTAIN_FRAME_ACROSS_STATES) |
	(1<<MAINTAIN_FRAME_ACROSS_STATES2) |
	(1<<MAINTAIN_FRAME_ACROSS_STATES3) |
	(1<<MAINTAIN_FRAME_ACROSS_STATES4);

inline Bool isAnyMaintainFrameFlagSet(Int flags)
{
	return (flags & ALL_MAINTAIN_FRAME_FLAGS) != 0;
}

inline Bool isCommonMaintainFrameFlagSet(Int a, Int b)
{
	a &= ALL_MAINTAIN_FRAME_FLAGS;
	b &= ALL_MAINTAIN_FRAME_FLAGS;
	return (a & b) != 0;
}


/** @todo: Move this to some kind of INI file*/
//
// Note: these values are saved in save files, so you MUST NOT REMOVE OR CHANGE
// existing values!
//
static char *TerrainDecalTextureName[TERRAIN_DECAL_MAX]=
{
#ifdef ALLOW_DEMORALIZE
	"DM_RING",//demoralized
#else
	"TERRAIN_DECAL_DEMORALIZED_OBSOLETE",
#endif
	"EXHorde",//enthusiastic
	"EXHorde_UP", //enthusiastic with nationalism 
	"EXHordeB",//enthusiastic vehicle
	"EXHordeB_UP", //enthusiastic vehicle with nationalism
	"EXJunkCrate",//Marks a crate as special
	"EXHordeC_UP", //enthusiastic with fanaticism 
	"EXChemSuit", //Marks a unit as having chemical suit on
	"",	//dummy entry for TERRAIN_DECAL_NONE
	"" //dummy entry for TERRAIN_DECAL_SHADOW_TEXTURE
};

const UnsignedInt NO_NEXT_DURATION = 0xffffffff;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// note that this now returns an ADDREFED handle, which must be released by the caller!
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#pragma optimize("s", on)
inline Bool testFlagBit(Int flags, Int bit)
{
	return (flags & (1<<bit)) != 0;
}
#pragma optimize("", on)

//-------------------------------------------------------------------------------------------------
static Bool findSingleBone(RenderObjClass* robj, const AsciiString& boneName, Matrix3D& mtx, Int& boneIndex)
{
	if (boneName.isNone() || boneName.isEmpty())
		return false;

	boneIndex = robj->Get_Bone_Index(boneName.str());
	if (boneIndex != 0)
	{
		mtx = robj->Get_Bone_Transform(boneIndex);
		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------------------------
static Bool findSingleSubObj(RenderObjClass* robj, const AsciiString& boneName, Matrix3D& mtx, Int& boneIndex)
{
	if (boneName.isNone() || boneName.isEmpty())
		return false;

	RenderObjClass* childObject = robj->Get_Sub_Object_By_Name(boneName.str());
	if (childObject)
	{
		mtx = childObject->Get_Transform();

		// you'd think this would work, but, it does not. do it the hard way.
		// boneIndex = childObject->Get_Sub_Object_Bone_Index(childObject);

		for (Int subObj = 0; subObj < robj->Get_Num_Sub_Objects(); subObj++)
		{	
			RenderObjClass* test = robj->Get_Sub_Object(subObj);
			if (test == childObject)
			{
				boneIndex = robj->Get_Sub_Object_Bone_Index(0, subObj);
#if defined(_DEBUG) || defined(_INTERNAL)
				test->Release_Ref();
				test = robj->Get_Sub_Object_On_Bone(0, boneIndex);
				DEBUG_ASSERTCRASH(test != NULL && test == childObject, ("*** ASSET ERROR: Hmm, bone problem"));
#endif
			}
			if (test) test->Release_Ref();
		}

		childObject->Release_Ref();

		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------------------------
static Bool doSingleBoneName(RenderObjClass* robj, const AsciiString& boneName, PristineBoneInfoMap& map)
{
	Bool foundAsBone = false;
	Bool foundAsSubObj = false;

	PristineBoneInfo info;
	AsciiString tmp;

	AsciiString boneNameTmp = boneName;
	((StringBase<char> &)(boneNameTmp)).toLower();	// convert to all-lowercase to avoid case sens issues later

	setFPMode();

	if (findSingleBone(robj, boneNameTmp, info.mtx, info.boneIndex))
	{
//DEBUG_LOG(("added bone %s\n",boneNameTmp.str()));
		BONEPOS_LOG(("Caching bone %s (index %d)\n", boneNameTmp.str(), info.boneIndex));
		BONEPOS_DUMPMATRIX3D(&(info.mtx));

		map[NAMEKEY(boneNameTmp.str())] = info;
		foundAsBone = true;
	}

	for (Int i = 1; i <= 99; ++i)
	{
		tmp.format("%s%02d", boneNameTmp.str(), i);
		if (findSingleBone(robj, tmp, info.mtx, info.boneIndex))
		{
//DEBUG_LOG(("added bone %s\n",tmp.str()));
			BONEPOS_LOG(("Caching bone %s (index %d)\n", tmp.str(), info.boneIndex));
			BONEPOS_DUMPMATRIX3D(&(info.mtx));
			map[NAMEKEY(tmp.str())] = info;
			foundAsBone = true;
		}
		else
		{
			break;
		}
	}

	if (!foundAsBone)
	{
		if (findSingleSubObj(robj, boneNameTmp, info.mtx, info.boneIndex))
		{
//DEBUG_LOG(("added subobj %s\n",boneNameTmp.str()));
			BONEPOS_LOG(("Caching bone from subobject %s (index %d)\n", boneNameTmp.str(), info.boneIndex));
			BONEPOS_DUMPMATRIX3D(&(info.mtx));
			map[NAMEKEY(boneNameTmp.str())] = info;
			foundAsSubObj = true;
		}

		for (Int i = 1; i <= 99; ++i)
		{
			tmp.format("%s%02d", boneNameTmp.str(), i);
			if (findSingleSubObj(robj, tmp, info.mtx, info.boneIndex))
			{
//DEBUG_LOG(("added subobj %s\n",tmp.str()));
				BONEPOS_LOG(("Caching bone from subobject %s (index %d)\n", tmp.str(), info.boneIndex));
				BONEPOS_DUMPMATRIX3D(&(info.mtx));
				map[NAMEKEY(tmp.str())] = info;
				foundAsSubObj = true;
			}
			else
			{
				break;
			}
		}
	}

	return foundAsBone || foundAsSubObj;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// These rows rest in this unit, and only the Zero Hour ModelConditionInfo bodies that stood here
// made it emit them. A function nothing runs keeps them, and inline_depth keeps its calls out of line.
#pragma inline_depth(0)
static Bool callInlineRows(ModelConditionInfo::TurretInfo *turret, std::vector<ModelConditionFlags> *flags)
{
	turret->clear();
	flags->clear();
	return testFlagBit(0, 0);
}
#pragma inline_depth()

extern const void *const g_modelDrawRowsAnchor = (const void *)&callInlineRows;

// W3DModelDrawModuleData's destructor is retail 0x000C8BE0, rowed and emitted by
// Code/Libraries/Source/WWVegas/WWLib/W3DModelDrawModuleDataDtorRva000C8BE0.cpp. The Zero
// Hour body that stood here (m_conditionStateMap.clear()) was a second strong definition
// that is not retail's and was first in link order, so the link kept it over the row.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#ifdef CACHE_ATTACH_BONE
//-------------------------------------------------------------------------------------------------
#endif

//-------------------------------------------------------------------------------------------------
enum ParseCondStateType
{
	PARSE_NORMAL,
	PARSE_DEFAULT,
	PARSE_TRANSITION,
	PARSE_ALIAS
};

//-------------------------------------------------------------------------------------------------
static void parseAsciiStringLC( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	AsciiString* asciiString = (AsciiString *)store;
	*asciiString = ini->getNextAsciiString();
	asciiString->toLower();
}

//-------------------------------------------------------------------------------------------------
// W3DModelDrawModuleData::buildFieldParse: defined in W3DModelDrawModuleDataBuildFieldParse.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
enum AnimParseType
{
	ANIM_NORMAL,
	ANIM_IDLE
};

//-------------------------------------------------------------------------------------------------
static void parseAnimation(INI* ini, void *instance, void * /*store*/, const void* userData)
{
	AnimParseType animType = (AnimParseType)(UnsignedInt)userData;

	AsciiString animName = ini->getNextAsciiString();
	((StringBase<char> &)(animName)).toLower();

	const char* distanceCoveredToken = ini->getNextTokenOrNull();
	Real distanceCovered = distanceCoveredToken ? INI::scanReal(distanceCoveredToken) : 0;
	DEBUG_ASSERTCRASH(!(animType == ANIM_IDLE && distanceCovered != 0), ("You should not specify nonzero DistanceCovered values for Idle Anims"));

	const char* timesToRepeatToken = ini->getNextTokenOrNull();
	Int timesToRepeat = timesToRepeatToken ? INI::scanInt(timesToRepeatToken) : 1;
	if (timesToRepeat < 1) timesToRepeat = 1;

	W3DAnimationInfo animInfo(animName, (animType == ANIM_IDLE), distanceCovered);

	ModelConditionInfo* self = (ModelConditionInfo*)instance;
	if (self->m_iniReadFlags & (1<<ANIMS_COPIED_FROM_DEFAULT_STATE))
	{
		self->m_iniReadFlags &= ~((1<<ANIMS_COPIED_FROM_DEFAULT_STATE)|(1<<GOT_IDLE_ANIMS)|(1<<GOT_NONIDLE_ANIMS));
		self->m_animations.clear();
	}

	if (animInfo.isIdleAnim())
		self->m_iniReadFlags |= (1<<GOT_IDLE_ANIMS);
	else
		self->m_iniReadFlags |= (1<<GOT_NONIDLE_ANIMS);

	if (!animName.isEmpty() && !animName.isNone())
	{
		while (timesToRepeat--)
			self->m_animations.push_back(animInfo);
	}
}	

//-------------------------------------------------------------------------------------------------
static void parseShowHideSubObject(INI* ini, void *instance, void *store, const void* userData)
{
	std::vector<ModelConditionInfo::HideShowSubObjInfo>* vec = (std::vector<ModelConditionInfo::HideShowSubObjInfo>*)store;
	AsciiString subObjName = ini->getNextAsciiString();
	((StringBase<char> &)(subObjName)).toLower();

	// handle "None"
	if (subObjName.isNone())
	{
		vec->clear();
		return;
	}

	while (subObjName.isNotEmpty())
	{
		Bool found = false;
		for (std::vector<ModelConditionInfo::HideShowSubObjInfo>::iterator it = vec->begin(); it != vec->end(); ++it)
		{
			if (stricmp(it->subObjName.str(), subObjName.str()) == 0)
			{
				it->hide = (userData != NULL);
				found = true;
			}
		}
		
		if (!found)
		{
			ModelConditionInfo::HideShowSubObjInfo info;
			info.subObjName = subObjName;
			info.hide = (userData != NULL);
			vec->push_back(info);
		}
		subObjName = ini->getNextAsciiString();
		((StringBase<char> &)(subObjName)).toLower();
	}
}	

//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
static void parseWeaponBoneName(INI* ini, void *instance, void * store, const void* /*userData*/)
{
	ModelConditionInfo* self = (ModelConditionInfo*)instance;
	AsciiString* arr = (AsciiString*)store;
	
	WeaponSlotType wslot = (WeaponSlotType)INI::scanIndexList(ini->getNextToken(), TheWeaponSlotTypeNames);
	arr[wslot] = ini->getNextAsciiString();
	((StringBase<char> &)(arr[wslot])).toLower();
	if (arr[wslot].isNone())
		arr[wslot].clear();

	if (self)
		self->addPublicBone(arr[wslot]);
}

//-------------------------------------------------------------------------------------------------
static void parseParticleSysBone(INI* ini, void *instance, void * store, const void * /*userData*/)
{
	ParticleSysBoneInfo info;
	info.boneName = ini->getNextAsciiString();
	((StringBase<char> &)(info.boneName)).toLower();
	ini->parseParticleSystemTemplate(ini, instance, &(info.particleSystemTemplate), NULL);
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	self->m_particleSysBones.push_back(info);
}

//-------------------------------------------------------------------------------------------------
static void parseRealRange( INI *ini, void *instance, void *store, const void* /*userData*/ )
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;

	const char *token = ini->getNextToken();
	self->m_animMinSpeedFactor = ini->scanReal( token );
	token = ini->getNextToken();
	self->m_animMaxSpeedFactor = ini->scanReal( token );
}

//-------------------------------------------------------------------------------------------------
static void parseLowercaseNameKey(INI* ini, void *instance, void * store, const void * /*userData*/)
{
	NameKeyType* key = (NameKeyType*)store;

	AsciiString tmp = ini->getNextToken();
	((StringBase<char> &)(tmp)).toLower();

	*key = NAMEKEY(tmp.str());
}

//-------------------------------------------------------------------------------------------------
static void parseBoneNameKey(INI* ini, void *instance, void * store, const void * /*userData*/)
{
	ModelConditionInfo* self = (ModelConditionInfo*)instance;
	NameKeyType* key = (NameKeyType*)store;

	AsciiString tmp = ini->getNextToken();
	((StringBase<char> &)(tmp)).toLower();

	if (self)
		self->addPublicBone(tmp);

	if (tmp.isEmpty() || tmp.isNone())
		*key = NAMEKEY_INVALID;
	else
		*key = NAMEKEY(tmp.str());
}

//-------------------------------------------------------------------------------------------------
static Bool doesStateExist(const ModelConditionVector& modelConditionVector, const ModelConditionFlags& modelConditionFlags)
{
	for (ModelConditionVector::const_iterator it = modelConditionVector.begin(); it != modelConditionVector.end(); ++it)
	{
		for (Int i = it->getConditionsYesCount()-1; i >= 0; --i)
		{
			if (modelConditionFlags == it->getNthConditionsYes(i))
				return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static Int countOnBits(UnsignedInt val)
{
	Int count = 0;
	for (Int i = 0; i < 32; ++i)
	{
		if (val & 1) 
			++count;
		val >>= 1;
	}
	return count;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#if 0
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// W3DModelDraw::~W3DModelDraw: dropped. Its body (??1W3DModelDraw@@MAE@XZ) ODR-used DrawModule's
// inline protected dtor, so defining it also emitted this TU's ??_7DrawModule@@6B@ vftable copy
// (digest 0c012cdf4860), its ??_GDrawModule@@MAEPAXI@Z deleting dtor (f1f3da198369),
// ??1DrawModule@@MAE@XZ (d321ea2f2604) and the ??_7W3DModelDraw@@6BDrawModule@@@ table. At link
// place 1123 that vftable copy came before the copies W3DProjectileStreamDrawDtor,
// W3DBoatWakeModelDrawDtor, W3DLightDrawDestructor and W3DLightDrawConstructor install (digest
// 4fe3271e863a), so all four lost it and could not link. Dropped so their copies win; nothing
// references ??1W3DModelDraw@@MAE@XZ or ??_7W3DModelDraw@@6BDrawModule@@@ (no census blocker).

//-------------------------------------------------------------------------------------------------
// W3DModelDraw::doStartOrStopParticleSys (0x000B6EDE) is rowed in W3DModelDrawParticles.cpp; a second definition here would not link.

//-------------------------------------------------------------------------------------------------
// W3DModelDraw::setHidden is defined with its retail-matched body in Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_setHidden_Rva000B6F6D.cpp (0x000B6F6D).

/**Free all data used by this model's shadow.  This is used to dynamically enable/disable shadows by the options screen*/
// releaseShadows lives in W3DModelDrawShadows.cpp (retail builds it /O1 on the BFME 2 layout).

//-------------------------------------------------------------------------------------------------
// setShadowsEnabled lives in W3DModelDrawShadows.cpp (retail builds it /O1 on the BFME 2 layout).

/**collect some stats about the rendering cost of this draw module */
#if defined(_DEBUG) || defined(_INTERNAL)	
#endif //_DEBUG || _INTERNAL


/**recurse through sub-objs to collect stats about the rendering cost of this draw module */
#if defined(_DEBUG) || defined(_INTERNAL)	
#endif //_DEBUG || _INTERNAL

//-------------------------------------------------------------------------------------------------
void W3DModelDraw::setFullyObscuredByShroud(Bool fullyObscured)
{
	if (m_fullyObscuredByShroud != fullyObscured)
	{
		m_fullyObscuredByShroud = fullyObscured;

		if (m_shadow)
			m_shadow->enableShadowInvisible(m_fullyObscuredByShroud);
		if (m_terrainDecal)
			m_terrainDecal->enableShadowInvisible(m_fullyObscuredByShroud);

		doStartOrStopParticleSys();
	}
}

//-------------------------------------------------------------------------------------------------
static Bool isAnimationComplete(RenderObjClass* renderObj)
{
	if (renderObj && renderObj->Class_ID() == RenderObjClass::CLASSID_HLOD)
	{
		HLodClass *hlod = (HLodClass*)renderObj;
		return hlod->Is_Animation_Complete();
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/**
	Utility function to make it easier to recursively hide all objects connected to a certain bone.
	We will hide all objects connected to bones which are children of boneIdx
*/
static void doHideShowBoneSubObjs(Bool state, Int numSubObjects, Int boneIdx, RenderObjClass *fullObject, const HTreeClass *htree)
{
#if 1	//(gth) fixed and tested this version
	for (Int i=0; i < numSubObjects; i++) 
	{
		bool is_child = false;
		Int parentBoneIndex = fullObject->Get_Sub_Object_Bone_Index(0, i);
		
		while (parentBoneIndex != 0) 
		{
			parentBoneIndex = htree->Get_Parent_Index(parentBoneIndex);

			if (parentBoneIndex == boneIdx) 
			{
				is_child = true;
				break;
			}
		}

		if (is_child) 
		{
			RenderObjClass* childObject = fullObject->Get_Sub_Object(i);
			childObject->Set_Hidden(state);
			childObject->Release_Ref();
		}
	}
#endif
#if 0	//old slow version
	
  for (Int i=0; i < numSubObjects; i++)
  {	
  	Int childBoneIndex = fullObject->Get_Sub_Object_Bone_Index(0, i);
  	Int parentIndex = htree->Get_Parent_Index(childBoneIndex);
  	if (childBoneIndex == parentIndex)
  		continue;

  	if (parentIndex == boneIdx)	// this object has our subobject as parent so copy hide state
  	{	
  		RenderObjClass* childObject = fullObject->Get_Sub_Object(i);
  		// recurse down the hierarchy to hide all sub-children
  		doHideShowBoneSubObjs(state, numSubObjects, childBoneIndex, fullObject, htree);
		childObject->Set_Hidden(state);
  		childObject->Release_Ref();
  	}
  } 
#endif
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/*
	DANGER WARNING READ ME
	DANGER WARNING READ ME
	DANGER WARNING READ ME

	This function must not EVER do ANYTHING which can in any way, shape, or form
	affect GameLogic in any way; if it does, net desyncs will occur and we
	will all lose our jobs. This must remain pure-client-only, and ensure
	that nothing it does can be detected, even in read-only form, by GameLogic!

	DANGER WARNING READ ME
	DANGER WARNING READ ME
	DANGER WARNING READ ME
*/
// handleClientTurretPositioning is byte-verified in W3DModelDrawClientTurret.cpp.

//void W3DModelDraw::handleClientFlagPositioning()
//{
//	const ModelConditionInfo::TurretInfo& tur = m_curState->m_turrets[tslot];
//	Real turretAngle = TheGlobalData->m_downwindAngle;
//	if (tur.m_flagAngleBone )
//	{
//		Matrix3D turretXfrm(1);
//		turretXfrm.Rotate_Z(turretAngle);
//		if (m_renderObject)
//		{
//			m_renderObject->Capture_Bone( tur.m_turretAngleBone );
//			m_renderObject->Control_Bone( tur.m_turretAngleBone, turretXfrm );	
//		}
//	}
//}

//-------------------------------------------------------------------------------------------------
/*
	Note that, strictly speaking this code is WRONG, since it assumes it will get called every frame,
	but in fact, will only get called every frame that it is visible. In practice, this isn't a big problem,
	but...

	@todo fix me someday (srj)
*/
// handleClientRecoil is byte-verified in W3DModelDrawClientTurret.cpp.

//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// W3DModelDraw::setTerrainDecal is rowed in its home unit; this copy was a duplicate definition.

//-------------------------------------------------------------------------------------------------
// setTerrainDecalSize and setTerrainDecalOpacity live in W3DModelDrawTerrainDecal.cpp: retail
// builds them size-optimised (/O1), which this unit's flags do not reproduce.


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#if defined(_DEBUG) || defined(_INTERNAL)	//art wants to see buildings without flags as a test.
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static Bool turretNamesDiffer(const ModelConditionInfo* modelConditionInfo, const ModelConditionInfo* b)
{
	if (!(modelConditionInfo->m_validStuff & ModelConditionInfo::TURRETS_VALID) || !(b->m_validStuff & ModelConditionInfo::TURRETS_VALID))
	{
		return true;
	}
	for (int i = 0; i < MAX_TURRETS; ++i)
		if (modelConditionInfo->m_turrets[i].m_turretAngleNameKey != b->m_turrets[i].m_turretAngleNameKey || 
				modelConditionInfo->m_turrets[i].m_turretPitchNameKey != b->m_turrets[i].m_turretPitchNameKey)
			return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
/** Change the model for this drawable. If color is non-zero, it will also apply team color to the
	model */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// this method must ONLY be called from the client, NEVER From the logic, not even indirectly.
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// (gth) C&C3 Added this accessor for the bounding box of a render object in a W3DModelDraw module
// this method must ONLY be called from the client, NEVER From the logic, not even indirectly.

//-------------------------------------------------------------------------------------------------
// (gth) C&C3 Added this accessor for a bone transform in the render object
// this method must ONLY be called from the client, NEVER From the logic, not even indirectly.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// W3DModelDraw::setPauseAnimation (0x000B377E) is rowed in W3DModelDrawSetPauseAnimation.cpp; a second definition here would not link.

//-------------------------------------------------------------------------------------------------
#ifdef ALLOW_ANIM_INQUIRIES
// srj sez: not sure if this is a good idea, for net sync reasons...
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/** Preload any assets for the time of day requested */
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// isVisible lives in W3DModelDrawIsVisible.cpp (retail builds it /O1 on the BFME 2 layout).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// W3DModelDraw::updateSubObjects is rowed with BFME2's body in W3DModelDrawUpdateSubObjects.cpp;
// the Zero Hour copy here was a second definition.

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version
	* 2: Added animation frame (CBD)
	*/
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
// W3DModelDraw::loadPostProcess: dropped. This body (call the base DrawModule::loadPostProcess and
// return, digest f0e7b4cd44e0) is not retail's 0x000B3A2D, whose 59-byte body is rowed anonymously
// as ?rva000B3A2D@Rva000B3A2D@@QAEXXZ (Code/GameEngine/Source/Common/Rva000B3A2D.cpp) and pinned
// to ?loadPostProcess@W3DModelDraw@@MAEXXZ in reverse/symbols.csv. At link place 1123 this TU's
// wrong copy was the sole definer, so W3DTankTruckDraw.cpp and W3DTankDrawLoadPostProcess.cpp kept
// a definition proven not retail's. Dropped, leaving the name to the pinned 0x000B3A2D owner
// (still rowed under the anonymous name); those two units were blocked either way until that row
// is realized under the real name, so this is not a new blocker for them.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// Preserve the rowed out-of-line Translate_X (0x000B2415, 65B) formerly
// emitted by the removed unverified recoil body. Like the existing WWMath
// emitter units, this member pointer requests ordinary compiler emission;
// it is a compile anchor, with no retail data identity claimed.
extern void (Matrix3D::*const g_bfmeModelDrawTranslateXAnchor)(float);
void (Matrix3D::*const g_bfmeModelDrawTranslateXAnchor)(float) = &Matrix3D::Translate_X;
