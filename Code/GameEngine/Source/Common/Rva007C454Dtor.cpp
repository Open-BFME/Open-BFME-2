// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??1Rva007C454@@UAE@XZ @0x0007C454 75B (existing pin): destructor of the
// CameraClass-derived Rva007C454 (ctor 0x0007C3CD, copy 0x0007C404). It
// reinstalls both vptrs (0x00BC6C58 at +0, 0x00BC6C54 at +8), frees the
// vector<BfmeE16> storage at +0x3FC (inlined STLport vector/_Vector_base
// destructors, malloc allocator -> free 0x00030830) and calls the rowed
// CameraClass destructor 0x00133A00. Layout follows Rva007C454Ctor.cpp.
// /EHs (not /EHsc): retail keeps an EH state around the free call, so the
// extern "C" free must be treated as possibly throwing.
// The canonical CameraClass (over the canonical RenderObjClass): the class's tables are
// retail's 131-slot 0x00BC6C58 and one-slot 0x00BC6C54 rather than stand-in bases' (P24).
#define BFME_RO_DTOR_DECL_ONLY
#include "../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// Storage deallocation cannot throw; keep the STLport cleanup inline.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline _Vector_base<BfmeE16, allocator<BfmeE16> >::~_Vector_base()
{ if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); }
template <> __declspec(dllimport) __forceinline vector<BfmeE16, allocator<BfmeE16> >::~vector()
{ _Destroy(this->_M_start, this->_M_finish); }
}


#include "../../../Libraries/Source/WWVegas/WW3D2/Rva007C454Camera.h"

Rva007C454::~Rva007C454()
{
}
