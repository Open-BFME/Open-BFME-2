// cl: /Ireference/shims/bfmelist /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// CrateTemplate possible-crates list machinery (retail 0x0035CAB4/0x0035CB8D/
// 0x0035CBFE). The element is the 8-byte crateCreationEntry from the landed
// CrateTemplate::parseCrateCreationEntry TU (AsciiString name plus float
// chance). The node allocator is the rowed narrow byte allocator at
// 0x000307F0 (16 bytes, null hint, via bfmealloc). The element _Construct
// helper at 0x0035CA02 is byte-identical for AsciiString-plus-dword payloads
// (pair dup_ row) and the crate entry (AsciiString plus float); a twin pin
// carries the crate spelling. Frameless 34-byte _M_create_node via the
// bfmelist shim (no TRY/UNWIND), same recipe as the UnicodeString list
// create-node TU.
#include <list>

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
};

bool operator==(const crateCreationEntry &a, const crateCreationEntry &b);
bool operator<(const crateCreationEntry &a, const crateCreationEntry &b);

namespace _STL
{

// Declared only; the gate resolves this reference to the pinned body at
// 0x0035CA02 (twin of the pair _Construct dup_ row, identical bytes).
template <>
void _Construct<crateCreationEntry, crateCreationEntry>(
	crateCreationEntry *, const crateCreationEntry &);

}

// ?_M_create_node@?$list@UcrateCreationEntry@@V?$allocator@UcrateCreationEntry@@@_STL@@@_STL@@IAEPAU?$_List_node@UcrateCreationEntry@@@2@ABUcrateCreationEntry@@@Z @0x35CAB4
template <>
_STL::_List_node<crateCreationEntry> *
_STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >::_M_create_node(
	const crateCreationEntry &__x)
{
	_STL::_List_node<crateCreationEntry> *__p =
		(_STL::_List_node<crateCreationEntry> *)_STL::allocator<char>::allocate(16, 0);
	_STL::_Construct(&__p->_M_data, __x);
	return __p;
}

// Explicit instantiation so the class's inline callers (insert, push_back)
// odr-use the specialization above; explicit-instantiation-only members are
// invisible to find_declared_unmatched.
template class _STL::list<crateCreationEntry, _STL::allocator<crateCreationEntry> >;
