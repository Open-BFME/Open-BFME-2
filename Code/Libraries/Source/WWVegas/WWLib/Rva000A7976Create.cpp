// ?Rva000A7976Create@@YGPAXPBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x000A7976 37B.
// 12-byte node create: allocates 0xC via rowed byte allocator 0x000307F0,
// zeroes dword at +0, constructs the pair at +4 via rowed _Construct 0x000A7849
// (pair<const AsciiString,NoCaseTreeValue4> via rowed pair copy 0x00466EA7),
// returns the block, ret 4. Same shape as ?Rva002CF9DCCreate@@YGPAXPBU... at
// 0x002CF9DC and ?Rva00212354NewNode@@YGPAXPBX@Z at 0x00212354 (37B, next+pair).
// Caller 0x000A7A63 unblocks 0x000A7A63/68 path.
// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
#include <map>
#include <set>
#include <list>
#include <vector>
class AsciiString { public: void *m_data; };
struct NoCaseTreeValue4 { public: unsigned char m_data[4]; };
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
template <> void _Construct<_STL::pair<const AsciiString, NoCaseTreeValue4> >(_STL::pair<const AsciiString, NoCaseTreeValue4> *, const _STL::pair<const AsciiString, NoCaseTreeValue4> &);
}
void *__stdcall Rva000A7976Create(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src)
{
	char *block = _STL::allocator<char>::allocate(0xC, 0);
	*(int *)block = 0;
	_STL::_Construct((_STL::pair<const AsciiString, NoCaseTreeValue4> *)(block + 4), *src);
	return block;
}
