// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// _STL::__uninitialized_copy<AsciiString*, AsciiString*>, retail
// 0x0002C4B2, 38 bytes. Dedicated TU so the AsciiString _Construct helper
// at 0x0002C485 stays an out-of-line call inside this loop. Element stride
// is 4 (StringBase m_data model, not the 8-byte Buffer model at 0x142CE0).

#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <memory>

// Rowed helper at 0x0002C485:
// ??$_Construct@VAsciiString@@V1@@_STL@@YAXPAVAsciiString@@ABV1@@Z
// (void __cdecl _STL::_Construct<class AsciiString,class AsciiString>).
template AsciiString *_STL::__uninitialized_copy(const AsciiString *, const AsciiString *, AsciiString *, const _STL::__false_type &);
