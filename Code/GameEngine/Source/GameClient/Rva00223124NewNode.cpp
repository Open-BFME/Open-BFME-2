// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00223124@Rva00223124@@QAEPAXPBX@Z @0x00223124 37B
// Eva hashtable new-node for 12-byte node (4 next + 8 pair<const AsciiString AsciiString>).
// Evidence: callers at 0x0022387F and 0x0002CAB8 load ecx plus one AsciiString-keyed arg;
// allocate 0x000307F0 with (0xc 0) then true _Construct 0x0002C71B via rowed pair copy;
// unlocks 0x0002CA72 and 0x00223854. Same shape and flags as sibling 0x002230FF.
// Private minimal AsciiString (declared-only copy) keeps _Construct out-of-line.
#define _STLP_NO_EXCEPTIONS 1
#include <memory>

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
private:
	char m_pad[4];
};

namespace _STL
{
template <> void _Construct(_STL::pair<const AsciiString, AsciiString> *,
	const _STL::pair<const AsciiString, AsciiString> &);
}

struct Rva00223124Node
{
	void *_M_next;
	_STL::pair<const AsciiString, AsciiString> _M_val;
};

class Rva00223124
{
public:
	void *rva00223124(const void *obj);
};

void *Rva00223124::rva00223124(const void *obj)
{
	Rva00223124Node *n = (Rva00223124Node *)_STL::allocator<char>().allocate(12, 0);
	n->_M_next = 0;
	_STL::_Construct(&n->_M_val, *(const _STL::pair<const AsciiString, AsciiString> *)obj);
	return n;
}
