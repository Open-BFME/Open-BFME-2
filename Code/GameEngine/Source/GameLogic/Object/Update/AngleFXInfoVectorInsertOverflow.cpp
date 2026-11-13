// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<AngleFXInfo>::_M_insert_overflow at 0x00626150, the
// growth path of StructureToppleUpdate's angle-FX list.  Split out of
// StructureToppleUpdate.cpp because retail built this body without /G7 --
// dec ecx and a byte load plus test where that unit writes sub ecx,1 and a
// compare against memory -- and with the bfmealloc allocator (two-argument
// allocate at 0x000307F0, one-argument _free at 0x00030830).

#include <vector>
// Suppress this TU's non-retail copy of ??$_M_allocate_and_copy@PAUAngleFXInfo@@@?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct AngleFXInfo;
namespace _STL { template <> template <> AngleFXInfo * vector<AngleFXInfo,allocator<AngleFXInfo> >::_M_allocate_and_copy<AngleFXInfo *>(unsigned int,AngleFXInfo *,AngleFXInfo *); }

class FXList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
#include "../../../../Include/Common/AngleFXInfo.h"

// Shared allocation/copy specialization, also emitted by Rva00181500Finish.cpp.
template<>
template<>
__declspec(noinline) inline AngleFXInfo * _STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> >::_M_allocate_and_copy<AngleFXInfo *>(
	unsigned int n, AngleFXInfo *first, AngleFXInfo *last)
{
	AngleFXInfo *result = this->_M_end_of_storage.allocate(n);
	for (AngleFXInfo *p = first; p != last; ++p)
	{
		AngleFXInfo *dest = (AngleFXInfo *)((char *)result + ((char *)p - (char *)first));
		if (dest)
			*dest = *p;
	}
	return result;
}

// Instantiate only the rowed members: a whole-class instantiation also emits
// erase(first, last), which retail folds into vector<BfmePod8>'s 0x003FA4DB.
template void _STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> >::_M_insert_overflow(AngleFXInfo *, const AngleFXInfo &, const _STL::__false_type &, _STL::size_t, bool);
template void _STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> >::reserve(_STL::size_t);
template AngleFXInfo *_STL::allocator<AngleFXInfo>::allocate(_STL::size_t, const void *) const;
