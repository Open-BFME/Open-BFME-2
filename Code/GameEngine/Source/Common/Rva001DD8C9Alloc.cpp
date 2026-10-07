// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva001DD8C9Alloc@@YGPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x001DD8C9 37B hashtable node alloc via rowed allocate 0x000307F0 plus rowed _Construct 0x000A7849.
// Evidence: unlock lane every callee rowed; caller 0x001DE556 hash insert buckets plus count; same 37B shape as 0x005472D3.
#include <memory>
#include <map>
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
private:
	char m_pad[4];
};
struct NoCaseTreeValue4
{
	char m_body[4];
};
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;
// Use the complete 466EA7 pair-copy provider rather than emitting a
// competing constructor from this allocation helper's flags.
namespace _STL {
template <> NocasePair::pair(const NocasePair &);
}

void *__stdcall Rva001DD8C9Alloc(const NocasePair &src)
{
	char *p = _STL::allocator<char>::allocate(0x0c, 0);
	*(int *)p = 0;
	_STL::_Construct((NocasePair *)(p + 4), src);
	return p;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva001DD8C9@Rva001DE556@@QAEPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z=?Rva001DD8C9Alloc@@YGPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z")
