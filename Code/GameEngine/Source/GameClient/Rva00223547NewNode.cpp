// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00223547@Rva00223547@@QAEPAXPBX@Z @0x00223547 37B
// Eva hashtable new-node for 12-byte node (4 next + 8 pair<const AsciiString TreeHintRef00217D4C>).
// Evidence: caller at 0x0022371D loads ecx plus one AsciiString-keyed arg;
// allocate 0x000307F0 with (0xc 0) then dup 0x00223168 twin of rowed 0x0021789E
// via rowed pair copy 0x00358B43; unlocks 0x002236F2. Same shape and flags as
// sibling 0x002230FF. Dup callee via function-pointer cast per Rva002CF9DCCreate.
// Private minimal AsciiString (declared-only copy) keeps pair layout.
#define _STLP_NO_EXCEPTIONS 1
#include <memory>

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct TreeHintRef00217D4C
{
	char m_body[4];
};

void __cdecl dup_00223168(void);
typedef void (__cdecl *PairConstructFn)(_STL::pair<const AsciiString, TreeHintRef00217D4C> *,
	const _STL::pair<const AsciiString, TreeHintRef00217D4C> &);

struct Rva00223547Node
{
	void *_M_next;
	_STL::pair<const AsciiString, TreeHintRef00217D4C> _M_val;
};

class Rva00223547
{
public:
	void *rva00223547(const void *obj);
};

void *Rva00223547::rva00223547(const void *obj)
{
	Rva00223547Node *n = (Rva00223547Node *)_STL::allocator<char>().allocate(12, 0);
	n->_M_next = 0;
	((PairConstructFn)&dup_00223168)(&n->_M_val, *(const _STL::pair<const AsciiString, TreeHintRef00217D4C> *)obj);
	return n;
}

// ?rva0022356C@Rva0022356C@@QAEPAXPBX@Z @0x0022356C 37B
// Hashtable new-node for 16-byte node (4 next + 12 BfmeStringRecord00222E08).
// Same shape as sibling 0x00223547 above: allocate 0x10 via 0x000307F0,
// zero next, placement-copy the record via rowed 0x00223195, return node.
// Evidence: caller at 0x002237F2 sets ecx plus one record arg and links the
// returned node into the bucket; unlocks 0x002237C7. Record layout (AsciiString
// text + 4-byte ref) from Code/GameEngine/Source/Common/StringRecordInlineCopyBFME2.cpp.
struct BfmeStringRecord00222E08
{
	// 12 bytes: AsciiString text + 4-byte ref; members untouched, passed by pointer.
	char m_body[12];
};

namespace _STL
{
	template<> void _Construct<BfmeStringRecord00222E08, BfmeStringRecord00222E08>(
		BfmeStringRecord00222E08 *, const BfmeStringRecord00222E08 &);
}

struct Rva0022356CNode
{
	void *_M_next;
	BfmeStringRecord00222E08 _M_val;
};

class Rva0022356C
{
public:
	void *rva0022356C(const void *obj);
};

void *Rva0022356C::rva0022356C(const void *obj)
{
	Rva0022356CNode *n = (Rva0022356CNode *)_STL::allocator<char>().allocate(16, 0);
	n->_M_next = 0;
	_STL::_Construct(&n->_M_val, *(const BfmeStringRecord00222E08 *)obj);
	return n;
}
