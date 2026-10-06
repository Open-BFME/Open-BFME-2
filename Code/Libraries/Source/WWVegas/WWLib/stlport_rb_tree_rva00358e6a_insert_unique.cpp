// cl: /O1 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// Target evidence: the tree body at 0x00359032 uses the case-sensitive
// AsciiString operator< at 0x0005598C, compares each node value beginning at
// +0x10, and calls the rowed decrement helper at 0x000242C0. The adjacent,
// rowed clear/reset methods establish the tree header at this+0 and its count
// at this+4. The rowed Rva00358B65 destructor establishes an 8-byte value
// beginning with a StringBase/AsciiString and carrying an opaque TargetRef at
// +4. The template instantiation below models only that proven layout and key
// comparison; it does not assign an application-level container identity.
#include <set>

class AsciiString;
bool __cdecl operator<(const AsciiString &left, const AsciiString &right);

struct Rva00359032Value
{
	unsigned int m_stringRepresentation;
	void *m_04;
};

inline bool operator<(const Rva00359032Value &left, const Rva00359032Value &right)
{
	return operator<(*reinterpret_cast<const AsciiString *>(&left.m_stringRepresentation),
		*reinterpret_cast<const AsciiString *>(&right.m_stringRepresentation));
}

typedef _STL::_Rb_tree<Rva00359032Value, Rva00359032Value,
	_STL::_Identity<Rva00359032Value>, _STL::less<Rva00359032Value>,
	_STL::allocator<Rva00359032Value> > Rva00359032Tree;

template _STL::pair<Rva00359032Tree::iterator, bool>
Rva00359032Tree::insert_unique(const Rva00359032Tree::value_type &value);
