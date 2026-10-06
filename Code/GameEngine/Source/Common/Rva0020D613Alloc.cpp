// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva0020D613Alloc@@YGPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x0020D613 37B hashtable node alloc via rowed allocate 0x000307F0 plus rowed _Construct 0x0020D5E6.
// Evidence: unlock lane every callee rowed; caller 0x0020D638 hash insert buckets plus count; same 37B shape as 0x001DD8C9.
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
void __cdecl dup_0020D5E6(void);
typedef void (__cdecl *NocasePairConstructFn)(NocasePair *, NocasePair const &);
void *__stdcall Rva0020D613Alloc(const NocasePair &src)
{
	char *p = _STL::allocator<char>::allocate(0x0c, 0);
	*(int *)p = 0;
	((NocasePairConstructFn)&dup_0020D5E6)((NocasePair *)(p + 4), src);
	return p;
}
