// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva002FE8AACreate@@YGPAXPBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x002FE8AA 34B: list node create allocating 0x10 via rowed 0x000307F0 and constructing pair at +8 via rowed dup 0x002FE87D. Evidence: caller at 0x002FEC9B list insert; same shape as list AsciiString _M_create_node 0x001FD682.
#include <list>
#include "ascii_string.h"

struct NoCaseTreeValue4 { unsigned char m_data[4]; };

void __cdecl dup_002FE87D(void);
typedef void (__cdecl *PairNocase4ConstructFn)(_STL::pair<const AsciiString, NoCaseTreeValue4> *, const _STL::pair<const AsciiString, NoCaseTreeValue4> &);

void *__stdcall Rva002FE8AACreate(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src)
{
	char *block = _STL::allocator<char>::allocate(0x10, 0);
	((PairNocase4ConstructFn)&dup_002FE87D)((_STL::pair<const AsciiString, NoCaseTreeValue4> *)(block + 8), *src);
	return block;
}
