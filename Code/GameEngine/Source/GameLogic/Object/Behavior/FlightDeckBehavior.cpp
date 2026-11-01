// cl: /Ireference/shims/flightdeck_info_public /Ireference/shims/aiupdatelayout /Ireference/shims/zh_outofline /FIzh_ascii.h /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// Matched operations inline; keep CRT math wrappers local to this unit.
#pragma push_macro("inline")
#define inline static inline
#include <math.h>
#pragma pop_macro("inline")

// Link view first: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
#include "../../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Behavior/FlightDeckBehavior.cpp); this unit had no counterpart under Code/.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
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

// FILE: FlightDeckBehavior.cpp ///////////////////////////////////////////////////////////////////
// Author: Kris Morness, May 2003
// Desc: Handles aircraft movement and parking behavior for aircraft carriers.
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
// Bottom-loop overload: this TU's flags compile the generic range-destroy to
// an early-out form, but retail's out-of-line copy is the bottom-tested loop
// (row 32 family2-LK3). The overload wins for (AsciiString*,AsciiString*).
inline void _Destroy(AsciiString * __first, AsciiString * __last)
{ for (; __first != __last; ++__first) __first->~AsciiString(); }
}

#include <vector>
// Bind assignment to the complete rowed provider at 0x002CD098.
namespace _STL {
template <> vector<Coord3D, allocator<Coord3D> > &
vector<Coord3D, allocator<Coord3D> >::operator=(const vector<Coord3D, allocator<Coord3D> > &);
}

#include "Common/CRCDebug.h"
#include "Common/Player.h"
#include "Common/Team.h" 
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"

#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/TerrainLogic.h"
#include "GameLogic/Weapon.h"

#include "GameLogic/Module/FlightDeckBehavior.h"
#include "GameLogic/Module/JetAIUpdate.h"
#include "GameLogic/Module/ProductionUpdate.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned long _Base_bitset<2>::_S_maskbit(unsigned int); }
namespace _STL { template <> bool bitset<45>::_Unchecked_test(unsigned int) const; }
namespace _STL { template <> unsigned int vector<Coord3D, allocator<Coord3D> >::capacity() const; }
namespace _STL { template <> Coord3D * vector<Coord3D, allocator<Coord3D> >::erase(Coord3D *, Coord3D *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Vector_base@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAE@IABV?$allocator@UCoor:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Coord3D;
namespace _STL { template <> _Vector_base<Coord3D,allocator<Coord3D> >::_Vector_base(unsigned int,allocator<Coord3D> const &); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAUCoord3D@@U1@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXPA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Coord3D;
namespace _STL { template <> void _STLP_alloc_proxy<Coord3D *,Coord3D,allocator<Coord3D> >::deallocate(Coord3D *,unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UCoord3D@@@_STL@@QBEXPAUCoord3D@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Coord3D;
namespace _STL { template <> void allocator<Coord3D>::deallocate(Coord3D *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUCoord3D@@U1@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEPAUCo:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Coord3D;
namespace _STL { template <> Coord3D * _STLP_alloc_proxy<Coord3D *,Coord3D,allocator<Coord3D> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?set@?$bitset@$0CN@@_STL@@QAEAAV12@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bitset<45> & bitset<45>::set(unsigned int); }
// Suppress this TU's non-retail copy of ??0?$_Base_bitset@$01@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Base_bitset<2>::_Base_bitset(); }
// Suppress this TU's non-retail copy of ?test@?$bitset@$0CN@@_STL@@QBE_NI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool bitset<45>::test(unsigned int) const; }

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(size_t, const allocator<AsciiString>&);
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> >&);
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> >&);
}

// Declaration-only _Construct: retail's vector<Coord3D> push_back calls the
// pinned out-of-line helper (0x002CA82C) instead of inlining the element
// copy (row 35 family-LK3).
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
// Use the complete retail push_back provider instead of this unit's copy.
template <> void vector<Coord3D>::push_back(const Coord3D &);
}

// vector<FlightDeckInfo>'s push_back and growth path are the rowed /G6 retail
// copies (FlightDeckInfoVectorInsertOverflow.cpp); declaration-only
// specializations stop this /G7 TU emitting its own.
namespace _STL {
template <> void vector<FlightDeckBehavior::FlightDeckInfo>::push_back(const FlightDeckBehavior::FlightDeckInfo &);
template <> void vector<FlightDeckBehavior::FlightDeckInfo>::_M_insert_overflow(FlightDeckBehavior::FlightDeckInfo *, const FlightDeckBehavior::FlightDeckInfo &, const __false_type &, size_t, bool);
template <> FlightDeckBehavior::FlightDeckInfo *allocator<FlightDeckBehavior::FlightDeckInfo>::allocate(size_t, const void *) const;
template <> FlightDeckBehavior::FlightDeckInfo *__uninitialized_fill_n<FlightDeckBehavior::FlightDeckInfo *, size_t, FlightDeckBehavior::FlightDeckInfo>(FlightDeckBehavior::FlightDeckInfo *, size_t, const FlightDeckBehavior::FlightDeckInfo &, const __false_type &);
// The element copy helpers are rowed in partitionmanager_impl.cpp and the
// base constructor is FlightDeckInfoVectorInsertOverflow.cpp's copy; this
// unit sits first in link order, so its own copies would be the ones kept
// (LINK-151).
template <> void _Construct<FlightDeckBehavior::FlightDeckInfo, FlightDeckBehavior::FlightDeckInfo>(FlightDeckBehavior::FlightDeckInfo *, const FlightDeckBehavior::FlightDeckInfo &);
template <> FlightDeckBehavior::FlightDeckInfo *__uninitialized_copy<FlightDeckBehavior::FlightDeckInfo *, FlightDeckBehavior::FlightDeckInfo *>(FlightDeckBehavior::FlightDeckInfo *, FlightDeckBehavior::FlightDeckInfo *, FlightDeckBehavior::FlightDeckInfo *, const __false_type &);
template <> _Vector_base<FlightDeckBehavior::FlightDeckInfo, allocator<FlightDeckBehavior::FlightDeckInfo> >::_Vector_base(const allocator<FlightDeckBehavior::FlightDeckInfo> &);
}

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?FlightDeckBehavior::~FlightDeckBehavior present-unmatched
FlightDeckBehavior::~FlightDeckBehavior( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// note: called from client, so MUST NOT modify self in any way, or desyncs will occur
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// note: called from client, so MUST NOT modify self in any way, or desyncs will occur
//-------------------------------------------------------------------------------------------------
// note: called from client, so MUST NOT modify self in any way, or desyncs will occur
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
const std::vector<Coord3D>* FlightDeckBehavior::getTaxiLocations( ObjectID id ) const
{
	//Find the runway the object is assigned to.
	Int runway = -1;
	for( std::vector<FlightDeckInfo>::const_iterator it = m_spaces.begin(); it != m_spaces.end(); it++ )
	{
		if( it->m_objectInSpace == id )
		{
			runway = it->m_runway;
			break;
		}
	}

	if( runway == -1 )
	{
		DEBUG_CRASH(("only planes with reserved spaces can reserve runways"));
		return NULL;
	}

	//Now get the runway we're assigned to and return it's taxi vector 
	return &(m_runways[ runway ].m_taxi);
}

//-------------------------------------------------------------------------------------------------
const std::vector<Coord3D>* FlightDeckBehavior::getCreationLocations( ObjectID id ) const
{
	//Find the runway the object is assigned to.
	Int runway = -1;
	for( std::vector<FlightDeckInfo>::const_iterator it = m_spaces.begin(); it != m_spaces.end(); it++ )
	{
		if( it->m_objectInSpace == id )
		{
			runway = it->m_runway;
			break;
		}
	}

	if( runway == -1 )
	{
		DEBUG_CRASH(("only planes with reserved spaces can reserve runways"));
		return NULL;
	}

	//Now get the runway we're assigned to and return it's creation vector 
	return &(m_runways[ runway ].m_creation);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// don't really need to autoheal every frame....
const Int HEAL_RATE_FRAMES = LOGICFRAMES_PER_SECOND / 5;

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
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
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
