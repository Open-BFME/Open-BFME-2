// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva002CF9DCCreate@@YGPAXPBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x002CF9DC 37B.
// 12-byte node create: allocates 0xC via rowed byte allocator 0x000307F0,
// zeroes dword at +0, constructs the pair at +4 via rowed dup 0x002CF954
// (object-symbol _Construct<pair<AsciiString,NoCaseTreeValue4>>), returns
// the block, ret 4. Same dup as the NoCase _M_create_node 0x002CFA8E but
// 0xC node (4-byte header + 8-byte pair). Caller at 0x002CFB77 unblocks 0x002CFB4C.
#include <map>
#include <set>
#include <list>
#include <vector>
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct NoCaseTreeValue4 { public: unsigned char m_data[4]; };
class AsciiString { public: void *m_data; };

void __cdecl dup_002CF954(void);
typedef void (__cdecl *NoCasePairConstructFn)(_STL::pair<const AsciiString, NoCaseTreeValue4> *, _STL::pair<const AsciiString, NoCaseTreeValue4> const &);

void *__stdcall Rva002CF9DCCreate(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src)
{
	char *block = _STL::allocator<char>::allocate(0xC, 0);
	*(int *)block = 0;
	((NoCasePairConstructFn)&dup_002CF954)((_STL::pair<const AsciiString, NoCaseTreeValue4> *)(block + 4), *src);
	return block;
}
