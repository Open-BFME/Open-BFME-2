// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002230FF@Rva002230FF@@QAEPAXPBX@Z @0x002230FF 37B
// Eva hashtable _M_new_node-style allocator for 12-byte node (4 next + 8 pair).
// Evidence: callers at 0x002234E5 and 0x002E023D pass this in ecx plus one
// AsciiString-keyed arg; allocate 0x000307F0 with (0xc, 0) then dup
// pair<const AsciiString, NoCaseTreeValue4> at 0x00222DBF (twin of rowed
// 0x000A7849 via rowed pair copy 0x00466EA7); unlocks 0x002E01F7 and 0x002234BA.
// Private minimal AsciiString (declared-only copy) keeps pair layout; the
// shared ascii_string.h inlines the copy and fails the gate, so the private
// copy stays with this justification. Dup callee via function-pointer cast
// per Rva002CF9DCCreate precedent (direct call to rowed dup 0x00222DBF).
#define _STLP_NO_EXCEPTIONS 1
#include <memory>

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

void __cdecl dup_00222DBF(void);
typedef void (__cdecl *PairConstructFn)(_STL::pair<const AsciiString, NoCaseTreeValue4> *,
	const _STL::pair<const AsciiString, NoCaseTreeValue4> &);

struct Rva002230FFNode
{
	void *_M_next;
	_STL::pair<const AsciiString, NoCaseTreeValue4> _M_val;
};

class Rva002230FF
{
public:
	void *rva002230FF(const void *obj);
};

void *Rva002230FF::rva002230FF(const void *obj)
{
	Rva002230FFNode *n = (Rva002230FFNode *)_STL::allocator<char>().allocate(12, 0);
	n->_M_next = 0;
	((PairConstructFn)&dup_00222DBF)(&n->_M_val, *(const _STL::pair<const AsciiString, NoCaseTreeValue4> *)obj);
	return n;
}
