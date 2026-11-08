// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??0Rva007C454@@QAE@XZ @0x0007C3CD 43B:
// Constructor for the Camera-derived class with vptr 0x007C6C58/0x007C6C54
// (same vtables as the pinned dtor at 0x0007C454) and a vector<BfmeE16> at
// +0x3FC. Retail calls the rowed CameraClass ctor at 0x00134AB0, stores the
// derived vtables, then constructs the vector through the rowed Vector_base
// at 0x00211E58. Caller at 0x0007C538 (in 0x0007C50B) proves the 0x408-byte
// new size; the dtor at 0x0007C454 frees the +0x3FC storage then calls the
// rowed Camera dtor. CamBase0/CamBase1 reproduce Camera's two-vptr MI layout;
// BfmeE16 is the 16-byte POD from stlport_vector_e16_o1.cpp.
// The canonical CameraClass (over the canonical RenderObjClass): the class's tables are
// retail's 131-slot 0x00BC6C58 and one-slot 0x00BC6C54 rather than stand-in bases' (P24).
#define BFME_RO_DTOR_DECL_ONLY
#include "../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }


#include "../../../Libraries/Source/WWVegas/WW3D2/Rva007C454Camera.h"

Rva007C454::Rva007C454()
{
}

