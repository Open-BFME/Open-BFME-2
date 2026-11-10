// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/zh_outofline /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// Link view first: Matrix3D(), Matrix3D(bool) and Matrix3D(const Matrix3D&) stay inline without
// emitting /O2 copies that compete with retail's owners (0x000423C5, 0x0004C91A, 0x0006645C).
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to change nothing else in this unit, but if a function added later that builds
#include "../../../../../../../reference/shims/bfme_namekey_inline_link/namekey_inline_link.h"  // NAMEKEY inline-only link view
// an array will not match, try it without this block.
#include "../../../../../Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "../../../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/Update/AIUpdate/RailroadGuideAIUpdate.cpp); this unit had no counterpart under Code/.
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

// FILE: RailroadBehavior.cpp //////////////////////////////////////////////////////////////
// Author: Mark Lorenzen, Sept 2002
// Desc: The railroad track following railroad carriage/locomotive logic module
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	
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

#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"

#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/RailroadGuideAIUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/DemoTrapUpdate.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"

#include "GameClient/Drawable.h"
#include "GameClient/Statistics.h"


///#define RAILROAD_DESYNC_TEST

#ifdef RAILROAD_DESYNC_TEST
#include "winbase.h"
// bfme link decl-only begin
namespace _STL { template <> AsciiString * __copy<AsciiString *, AsciiString *, int>(AsciiString *, AsciiString *, AsciiString *, random_access_iterator_tag const &, int *); }
namespace _STL { template <> AsciiString * __uninitialized_copy<AsciiString const *, AsciiString *>(AsciiString const *, AsciiString const *, AsciiString *, __false_type const &); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::vector(vector<AsciiString, allocator<AsciiString> > const &); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::vector(allocator<AsciiString> const &); }
namespace _STL { template <> unsigned long _Base_bitset<2>::_S_maskbit(unsigned int); }
namespace _STL { template <> bool bitset<45>::_Unchecked_test(unsigned int) const; }
namespace _STL { template <> AsciiString * vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *, AsciiString *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Vector_base@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@IABV?$allocat:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Vector_base<AsciiString,allocator<AsciiString> >::_Vector_base(unsigned int,allocator<AsciiString> const &); }
// Suppress this TU's non-retail copy of ??$_Construct@VAsciiString@@V1@@_STL@@YAXPAVAsciiString@@ABV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Construct<AsciiString,AsciiString>(AsciiString *,AsciiString const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PBVAsciiString@@PAV1@@_STL@@YAPAVAsciiString@@PBV1@0PAV1@ABU__fals:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> AsciiString * __uninitialized_copy<AsciiString const *,AsciiString *>(AsciiString const *,AsciiString const *,AsciiString *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__copy@PAVAsciiString@@PAV1@H@_STL@@YAPAVAsciiString@@PAV1@00ABUrandom_access_iterator_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> AsciiString * __copy<AsciiString *,AsciiString *,int>(AsciiString *,AsciiString *,AsciiString *,random_access_iterator_tag const &,int *); }
// Suppress this TU's non-retail copy of ?erase@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAEPAVAsciiString@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> AsciiString * vector<AsciiString,allocator<AsciiString> >::erase(AsciiString *,AsciiString *); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PAVAsciiString@@V1@V?$allocator@VAsciiString@@@_STL@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> void _STLP_alloc_proxy<AsciiString *,AsciiString,allocator<AsciiString> >::deallocate(AsciiString *,unsigned int); }

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> COMDAT copies, so the calls bind the kept rowed copies.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(size_t, const allocator<AsciiString>&);
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> >&);
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
}
#endif

// TYPES //////////////////////////////////////////////////////////////////////////////////////////
static const Int INVALID_PATH = -1;
#define NORMAL_VEL_Z	0.25f
#define NORMAL_MASS		50.0f




#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif


#define FRAMES_UNPULLED_LONG_ENOUGH_TO_UNHITCH (2)





// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------



// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------






// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------










// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------















///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE ////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


class PartitionFilterIsValidCarriage : public PartitionFilter
{
private:
	Object* m_obj;
	const RailroadBehaviorModuleData* m_data;

public:

	PartitionFilterIsValidCarriage(Object* obj, const RailroadBehaviorModuleData* data) : m_obj(obj), m_data(data) { }
	
#if defined(_DEBUG) || defined(_INTERNAL)
	virtual const char* debugGetName() { return "PartitionFilterIsValidCarriage"; }
#endif

	virtual Bool allow(Object *objOther)
	{

		// must exist!
		if ( m_obj == NULL || objOther == NULL)
			return FALSE;

		//must not be me!
		if (m_obj == objOther)
			return FALSE;
		// must have railroady goodness
		static NameKeyType key_rb = NAMEKEY("RailroadBehavior");
		RailroadBehavior *rb = (RailroadBehavior*)objOther->findUpdateModule(key_rb);
		if( ! rb )
			return FALSE;

		if ( rb->hasEverBeenHitched() )// two of us can't pull you
			return FALSE;

		// must be our ally (well, maybe)
		if (m_obj->getRelationship(objOther) != ALLIES)
			return FALSE;

		// guess it's carriage-worthy!
		return TRUE;
	}
};



// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------



// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------





// ------------------------------------------------------------------------------------------------

#pragma optimize("s", on)
void alignToTerrain( Real angle, const Coord3D& pos, const Coord3D& normal, Matrix3D& mtx)
{
	Coord3D x, y, z;

	z = normal;

	x.x = Cos( angle ); 
	x.y = Sin( angle ); 
	x.z = 0.0f; 
	if (z.z != 0.0f)
	{
		x.z = -(x.x*z.x + x.y*z.y) / z.z;
		x.normalize();
	}

	DEBUG_ASSERTCRASH(fabs(x.x*z.x + x.y*z.y + x.z*z.z)<0.0001,("dot is not zero\n"));

	// now computing the y vector is trivial.
	y.crossProduct( &z, &x, &y );
	y.normalize();

	mtx.Set(  x.x, y.x, z.x, pos.x,
							x.y, y.y, z.y, pos.y,
							x.z, y.z, z.z, pos.z );
}
#pragma optimize("", on)


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------












// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version 
	* 2: Added... like, everything.	
	* 3: m_held script driven flag for hanging out
	**/
// ------------------------------------------------------------------------------------------------





// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------





// The one retail body this unit keeps from the vector<TrackPoint> code.
template void _STL::_Construct<TrackPoint, TrackPoint>(TrackPoint *, const TrackPoint &);
