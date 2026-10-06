// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ??0Rva002186EB@@QAE@XZ, retail 0x002186EB, 61 bytes.
// Constructor with vtable 0x7E5B10 plus two empty AsciiStrings at +4/+8 plus
// map<int void*> at +0x0C via rowed ctor 0x0033C432. Caller at 0x00218D61.
// Layout read off retail (EH states 0 then 1 before the map call) via a
// non-virtual base holding the first string so the derived vtable store lands
// after the +4 zero like retail; ImageCollectionCtor precedent for the
// folded map spelling.

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


namespace _STL
{
template <class First, class Second> struct pair
{
	First first;
	Second second;
};
template <class Type> struct less
{
};
template <class Type> class allocator
{
};
template <class Key, class Value, class Compare, class Alloc> class map
{
public:
	map();
	unsigned char m_pad[0x18];
};
}

class RvaBase04
{
public:
	RvaBase04() {}
	~RvaBase04() {}
	AsciiString m_04;
};

class Rva002186EB : public RvaBase04
{
public:
	Rva002186EB();
	virtual ~Rva002186EB();
private:
	AsciiString m_08;
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_map0C;
};

Rva002186EB::Rva002186EB() : RvaBase04(), m_08()
{
}
