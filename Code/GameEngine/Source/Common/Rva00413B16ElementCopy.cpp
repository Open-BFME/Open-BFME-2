// cl: /O1 /EHs /MD
//
// ??0Rva00413B16Element@@QAE@ABU0@@Z @0x00413951 61B: existing pin (copy
// constructor called by the rowed _Construct<Rva00413B16Element> 0x0041398E).
// 0x18-byte element: rowed vector<unsigned int> copy at +0 (0x002CFAB9), then
// the unrowed copy constructor 0x004137C6 at +0xC under EH state 0, named by
// an address-derived pin since its type is not recovered.

namespace _STL
{
template <class T>
class allocator;

template <class T, class Alloc = allocator<T> >
class vector
{
public:
	vector(const vector<T, Alloc> &other);
	~vector();

private:
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
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
