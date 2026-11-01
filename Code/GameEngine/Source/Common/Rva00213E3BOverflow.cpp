// Target boundary 0x00213E3B/180 is STLport vector::_M_insert_overflow
// false_type for 16-byte elements. It calls the existing copy loop at
// 0x00211E0D. The append body below calls it at 0x00214270.
// Retail uses sar 4/shl 4
// stride 0x10 and delegates to target helpers allocate 0x002226BE,
// uninitialized_copy 0x00211E0D, Construct 0x00211DFB, fill_n 0x00211E33,
// destroy+free 0x0021397C.
//
// Rva002111C8 is the target 16-byte element (RvaSmartPtr12 plus int) whose
// copy/fill/clear paths are rowed under honest address names; this TU uses
// an STL-sized emitter view to reproduce the overflow shape. Concrete
// application identity is recorded only where independent evidence supports
// it.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
class Rva002111C8;
void Rva00211DFBConstruct(Rva002111C8 *, const Rva002111C8 *);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva002111C8 *destination, const Rva002111C8 &source)
{
    Rva00211DFBConstruct(destination, &source);
}
}

// The existing range provider destroys these same 16-byte tracked records.
struct Rva002115C5;
void Rva00212AD6Get(Rva002115C5 *, Rva002115C5 *);
namespace _STL {
// ?_STL::_Destroy absent-from-retail
static __forceinline void _Destroy(Rva002111C8 *first, Rva002111C8 *last)
{
    Rva00212AD6Get(reinterpret_cast<Rva002115C5 *>(first),
                  reinterpret_cast<Rva002115C5 *>(last));
}
}

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

// Retail's element destroy loop (0x00212AD6, stride 0x10) calls only the
// handle dtor 0x002115C5 (rowed ??1RvaSmartPtr12): the element's own dtor is
// implicit, so it has no address and destroys just this member.
#include "../../Include/Common/RvaSmartPtr12.h"

class Rva002111C8 {
public:
	RvaSmartPtr12 m_00;
	int m_0c;
	Rva002111C8(const Rva002111C8 &) throw();
	Rva002111C8 &operator=(const Rva002111C8 &);
};


template void _STL::vector<Rva002111C8>::_M_insert_overflow(
	Rva002111C8 *, const Rva002111C8 &,
	const _STL::__false_type &, unsigned int, bool);
template void _STL::vector<Rva002111C8>::push_back(const Rva002111C8 &);
