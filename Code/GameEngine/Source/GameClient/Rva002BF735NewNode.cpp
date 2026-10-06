// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002BF735@Rva002BF735@@QAEPAXPBX@Z @0x002BF735 37B
// Hashtable _M_new_node-style allocator for 12-byte node (4 next + 8 pair).
// Evidence: caller at 0x002BFAD6 passes this in ecx plus one AsciiString-keyed
// arg then links the node into its bucket; allocate 0x000307F0 with (0xc 0)
// then dup pair<const AsciiString TreeHintRef00217D4C> at 0x002BF35B (alias of
// rowed _Construct 0x0021789E via rowed pair copy 0x00358B43); landing this
// unblocks 0x002BFAD6. Private minimal AsciiString (declared-only copy) keeps
// pair layout; the shared ascii_string.h inlines the copy and fails the gate
// so the private copy stays with this justification. Dup callee via
// function-pointer cast per Rva002230FFNewNode precedent.
#define _STLP_NO_EXCEPTIONS 1
#include <memory>

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
private:
	char m_pad[4];
};

struct TreeHintRef00217D4C
{
	char m_body[4];
};

void __cdecl dup_002BF35B(void);
typedef void (__cdecl *PairConstructFn)(_STL::pair<const AsciiString, TreeHintRef00217D4C> *,
	const _STL::pair<const AsciiString, TreeHintRef00217D4C> &);

struct Rva002BF735Node
{
	void *_M_next;
	_STL::pair<const AsciiString, TreeHintRef00217D4C> _M_val;
};

class Rva002BF735
{
public:
	void *rva002BF735(const void *obj);
};

void *Rva002BF735::rva002BF735(const void *obj)
{
	Rva002BF735Node *n = (Rva002BF735Node *)_STL::allocator<char>().allocate(12, 0);
	n->_M_next = 0;
	((PairConstructFn)&dup_002BF35B)(&n->_M_val, *(const _STL::pair<const AsciiString, TreeHintRef00217D4C> *)obj);
	return n;
}
