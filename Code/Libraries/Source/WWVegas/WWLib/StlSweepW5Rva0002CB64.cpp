// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Retail2CB64/25B and erase2CCFC prove two cdecl pointer arguments/4B stride.
// Cleanup calls the genuine ordinary5B destructor48BA39, which releases36410.
// Original enclosing record/container identities are unknown.
#pragma inline_depth(3)
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <memory>

// Retail's range destroy calls the out-of-line destructor 0x0048BA39 for each
// string, so its first instantiation expands the helpers but not the destructor.
namespace _STL {
template <> __declspec(dllimport) __forceinline void _Destroy<AsciiString>(AsciiString *pointer)
{
    pointer->AsciiString::~AsciiString();
}
#pragma inline_depth(3)
template void _Destroy<AsciiString *>(AsciiString *, AsciiString *);
#pragma inline_depth()
}
