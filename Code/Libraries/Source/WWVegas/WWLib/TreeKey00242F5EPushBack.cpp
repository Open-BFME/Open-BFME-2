// cl: /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?push_back@?$vector@UTreeKey00242F5E@@V?$allocator@UTreeKey00242F5E@@@_STL@@@_STL@@QAEXABUTreeKey00242F5E@@@Z @0x0052480E 55B.
// STLport 4.5.3 vector<TreeKey00242F5E>::push_back: fast path via dup_00523DD4
// _Construct plus growth via rowed _M_insert_overflow 0x005244DC.
// Sibling of StlportVectorPushBackSiblings 55B push_backs; flags mirror
// TreeKey00242F5EVectorOverflow plus bfme2_ascii for AsciiString member.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "ascii_string.h"

struct TreeKey00242F5E
{
	int m_id;
	AsciiString m_name;
	TreeKey00242F5E(const TreeKey00242F5E &other);
	~TreeKey00242F5E();
};

void __cdecl dup_00523DD4();

namespace _STL
{
// ?_Construct typed placement adapter absent-from-retail
__forceinline void _Construct(TreeKey00242F5E *p, const TreeKey00242F5E &x)
{
	typedef void (__cdecl *Fn)(TreeKey00242F5E *, const TreeKey00242F5E &);
	((Fn)&dup_00523DD4)(p, x);
}
}

template void _STL::vector<TreeKey00242F5E>::push_back(const TreeKey00242F5E &);
