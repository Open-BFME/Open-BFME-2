// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target 0x2CC70 destroys four-byte strings, then frees the vector storage.
// The element cleanup is StringBase<char>::releaseBuffer at 0x36410.
#include <vector>

#include "ascii_string.h"


typedef char AsciiStringExtent[sizeof(AsciiString) == 4 ? 1 : -1];
template _STL::vector<AsciiString>::~vector();

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1RvaVecAscii@@QAE@XZ=??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1SidesInfoStringVector@@QAE@XZ=??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1TransitionSmallVec@@QAE@XZ=??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1TransitionDamageFXSlotD@@QAE@XZ=??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ")
