// cl: /EHs /MD
// stlport
//
// ??0Rva00413B16Element@@QAE@ABU0@@Z @0x00413951 61B: existing pin (copy
// constructor called by the rowed _Construct<Rva00413B16Element> 0x0041398E).
// 0x18-byte element: rowed vector<unsigned int> copy at +0 (0x002CFAB9), then
// the unrowed copy constructor 0x004137C6 at +0xC under EH state 0, named by
// an address-derived pin since its type is not recovered.

#include <vector>

namespace _STL
{
// Bind vector<unsigned int>'s copy ctor and dtor to their rowed workers
// (0x002CFAB9 copy). Declarations only: the definitions live in the row owners.
template <class T, class A> class vector;
template <> class vector<unsigned int, allocator<unsigned int> >
{
public:
	vector(const vector &other);
	~vector();

private:
	unsigned int *m_start;
	unsigned int *m_finish;
	unsigned int *m_end_of_storage;
};
}

class Rva004137C6
{
public:
	Rva004137C6(const Rva004137C6 &other);

private:
	char m_pad[0xC];
};

struct Rva00413B16Element
{
	Rva00413B16Element(const Rva00413B16Element &other);

	_STL::vector<unsigned int> m_00;
	Rva004137C6 m_0C;
};

Rva00413B16Element::Rva00413B16Element(const Rva00413B16Element &other) :
	m_00(other.m_00),
	m_0C(other.m_0C)
{
}

// The retail call in this body reads 0x004137C6, an address the ledger already
// carries as ??0?$_Rb_tree@URva004137C6Element@@U1@U?$_Identity@URva004137C6Element@@@_STL@@U?$less@URva004137C6Element@@@3@V?$allocator@URva004137C6Element@@@3@@_STL@@QAE@ABV01@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??0Rva004137C6@@QAE@ABV0@@Z=??0?$_Rb_tree@URva004137C6Element@@U1@U?$_Identity@URva004137C6Element@@@_STL@@U?$less@URva004137C6Element@@@3@V?$allocator@URva004137C6Element@@@3@@_STL@@QAE@ABV01@@Z")
