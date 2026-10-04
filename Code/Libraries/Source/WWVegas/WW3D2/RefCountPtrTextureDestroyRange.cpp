// cl: /O1 /MD /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// RVA 0x000C99F9, 25 bytes, native Ghidra start and complete RET extent.
// Retail advances four bytes per element and calls the independently matched
// RefCountPtr<TextureClass> destructor at 0x0017098D. Reuse the owning template
// from streakRender.cpp; keep that destructor out of line as in the target.
// The range helper's original template spelling is not established.
#include "../../../../../reference/shims/bfmestreak/ref_ptr.h"
class TextureClass;
template <> RefCountPtr<TextureClass>::~RefCountPtr();

void __cdecl Rva000C99F9Destroy(RefCountPtr<TextureClass> *first,
                              RefCountPtr<TextureClass> *last)
{
    for (; first != last; ++first)
        first->~RefCountPtr();
}
