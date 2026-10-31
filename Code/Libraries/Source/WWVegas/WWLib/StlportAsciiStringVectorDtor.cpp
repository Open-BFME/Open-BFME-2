// cl: /O1 /arch:SSE /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// Target 0x2CC70 destroys four-byte strings, then frees the vector storage.
// The element cleanup is StringBase<char>::releaseBuffer at 0x36410.
#pragma inline_depth(3)
#define _STLP_NO_EXCEPTIONS 1
// STLport frees through the game's plain _free at 0x00030830, not the CRT import.
#define free BfmeCrtImportedFree
#include <stdlib.h>
#include <malloc.h>
#undef free
extern "C" void __cdecl free(void *) throw(...);
#include "ascii_string.h"
#include <vector>
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

#pragma inline_depth(3)
typedef char AsciiStringExtent[sizeof(AsciiString) == 4 ? 1 : -1];
template _STL::vector<AsciiString>::~vector();

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1RvaVecAscii@@QAE@XZ=??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1TransitionDamageFXSlotD@@QAE@XZ=??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ")
