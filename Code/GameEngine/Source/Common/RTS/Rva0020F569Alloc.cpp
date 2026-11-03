// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?Rva0020F569Alloc@@YGPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x0020F569 37B hashtable node alloc via rowed allocate 0x000307F0 plus rowed _Construct 0x0020F321.
// Evidence: unlock lane every callee rowed; caller 0x00210372 hash insert; same 37B shape as 0x0020D613 and 0x001DD8C9.
#include <memory>
#include <map>
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Include/Common/NoCaseTreeValue4.h"
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;
void __cdecl Rva0020F321Construct(void *dest, const void *source);
void *__stdcall Rva0020F569Alloc(const NocasePair &src)
{
	char *p = _STL::allocator<char>::allocate(0x0c, 0);
	*(int *)p = 0;
	Rva0020F321Construct((NocasePair *)(p + 4), &src);
	return p;
}
