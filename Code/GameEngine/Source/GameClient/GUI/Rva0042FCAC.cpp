// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ?rva0042FCAC@Rva0042FCAC@@QAEPAXPBX@Z @0x0042FCAC 37B: hashtable new-node for 12-byte node (4 next plus 8 pair<const unsigned int bool>). Evidence: allocate 0x000307F0 with 0xc 0 then rowed pair _Construct 0x001FF5AC plus caller 0x0042FD85 linking bucket plus unlocks 0x0042FD55; same shape and flags as sibling Rva00223547.
#define _STLP_NO_EXCEPTIONS 1
#include <memory>

typedef _STL::pair<const unsigned int, bool> UIntBoolHashtablePair;

namespace _STL {
template <> void _Construct<UIntBoolHashtablePair>(
	UIntBoolHashtablePair *, const UIntBoolHashtablePair &);
}

struct Rva0042FCACNode
{
	void *_M_next;
	UIntBoolHashtablePair _M_val;
};

class Rva0042FCAC
{
public:
	void *rva0042FCAC(const void *obj);
};

void *Rva0042FCAC::rva0042FCAC(const void *obj)
{
	Rva0042FCACNode *n = (Rva0042FCACNode *)_STL::allocator<char>().allocate(12, 0);
	n->_M_next = 0;
	_STL::_Construct(&n->_M_val, *(const UIntBoolHashtablePair *)obj);
	return n;
}
