// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?Rva002FE8AACreate@@YGPAXPBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x002FE8AA 34B: list node create allocating 0x10 via rowed 0x000307F0 and constructing pair at +8 via rowed dup 0x002FE87D. Evidence: caller at 0x002FEC9B list insert; same shape as list AsciiString _M_create_node 0x001FD682.
#include <list>
#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/NoCaseTreeValue4.h"

void __cdecl Rva002FE87DConstruct(void *dest, const void *source);

void *__stdcall Rva002FE8AACreate(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src)
{
	char *block = _STL::allocator<char>::allocate(0x10, 0);
	Rva002FE87DConstruct((_STL::pair<const AsciiString, NoCaseTreeValue4> *)(block + 8), src);
	return block;
}
