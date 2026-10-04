// cl: /O1 /EHsc /MD
// ??0Rva005D791C@@QAE@XZ @0x005D791C 55B
// Ctor of an opaque Rva005EE30C-derived class: base ctor 0x005EE2E6,
// then vtable 0x00875DFC, then set<AsciiString> member at +0x28 via the
// rowed set ctor 0x000D3A71. Base size 0x28 from Rva005EE30CCtor.cpp.
// Evidence: vtable store at [this]; unblocks 0x0058A6A8; caller 0x0058ABB1.
// AsciiString is only forward-declared: the member type is declared-only,
// so no AsciiString/StringBase body is defined here.

class Rva005EE30C
{
public:
	Rva005EE30C();
	virtual ~Rva005EE30C();
private:
	char m_pad24[0x24];
};

class AsciiString;

namespace _STL {
template <class T> struct less {
};
template <class T> class allocator {
};
template <class Key, class Compare, class Alloc> class set
{
public:
	set();
};
}

class Rva005D791C : public Rva005EE30C
{
public:
	Rva005D791C();
	virtual ~Rva005D791C();
private:
	_STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_set28;
};

Rva005D791C::Rva005D791C()
{
}
