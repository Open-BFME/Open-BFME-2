// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
// ?Rva0020D613Alloc@@YGPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x0020D613 37B hashtable node alloc via rowed allocate 0x000307F0 plus rowed _Construct 0x0020D5E6.
// Evidence: unlock lane every callee rowed; caller 0x0020D638 hash insert buckets plus count; same 37B shape as 0x001DD8C9.
#include <memory>
#include <map>
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct NoCaseTreeValue4
{
	char m_body[4];
};
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;
void __cdecl Rva0020D5E6Construct(void *dest, const void *source);
void *__stdcall Rva0020D613Alloc(const NocasePair &src)
{
	char *p = _STL::allocator<char>::allocate(0x0c, 0);
	*(int *)p = 0;
	Rva0020D5E6Construct((NocasePair *)(p + 4), &src);
	return p;
}

class Rva000427195
{
public:
	void *rva0020D613(const NocasePair &src);
};

// ICF-folded twin of Rva0020D613Alloc above (same 37 bytes at 0x0020D613):
// the member spelling ignores its receiver, so its stack frame matches the
// stdcall spelling exactly, including the callee-cleaned return.
void *Rva000427195::rva0020D613(const NocasePair &src)
{
	char *p = _STL::allocator<char>::allocate(0x0c, 0);
	*(int *)p = 0;
	Rva0020D5E6Construct((NocasePair *)(p + 4), &src);
	return p;
}
