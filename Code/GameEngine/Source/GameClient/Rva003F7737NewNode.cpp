// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F7737@Rva003F7737@@QAEPAXPBX@Z @0x003F7737 37B
// Hashtable new-node for 16-byte node (4 next + 12 BfmeStringRecord004071F7).
// Same shape as sibling 0x0022356C in Rva00223547NewNode.cpp: allocate 0x10
// via 0x000307F0, zero next, placement-copy the 12-byte record via dup
// 0x003F7674 (twin of rowed _Construct for BfmeStringRecord004071F7 via rowed
// copy 0x004071F7), return node. Evidence: caller at 0x003F78EF sets ecx plus
// one record arg and links the returned node into the bucket; landing this
// unblocks 0x003F78A9. Dup callee via function-pointer cast per
// Rva002BF735NewNode precedent. Record layout (AsciiString text + 2 words)
// from Code/GameEngine/Source/Common/StringRecordCopyBFME2.cpp.
#define _STLP_NO_EXCEPTIONS 1
#include <memory>

struct Rva003F7737Val
{
	char m_body[12];
};

void __cdecl dup_003F7674(void);
typedef void (__cdecl *ValConstructFn)(Rva003F7737Val *, const Rva003F7737Val &);

struct Rva003F7737Node
{
	void *_M_next;
	Rva003F7737Val _M_val;
};

class Rva003F7737
{
public:
	void *rva003F7737(const void *obj);
};

void *Rva003F7737::rva003F7737(const void *obj)
{
	Rva003F7737Node *n = (Rva003F7737Node *)_STL::allocator<char>().allocate(16, 0);
	n->_M_next = 0;
	((ValConstructFn)&dup_003F7674)(&n->_M_val, *(const Rva003F7737Val *)obj);
	return n;
}
