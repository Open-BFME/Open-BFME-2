// cl: /EHs /MD
//
// ??4BfmeAssignRecord52@@QAEAAU0@ABU0@@Z @0x002B828A 75B: existing pin (callers
// 0x002B832E 0x002B9167 0x002B91D7, the record's copy_backward/fill/copy).
// Memberwise assignment matching the layout of the rowed dtor 0x002B707E
// (BfmeAssignRecord52Dtor.cpp): rowed Rva002B5558::operator= at +0 (0x002B62DE),
// rowed vector<Rva0040DC56Element>::operator= at +0xC (0x002B719C), then seven
// plain words +0x18..+0x30.

struct Rva0040DC56Element;

namespace _STL
{
template <class T>
class allocator;

template <class T, class Alloc = allocator<T> >
class vector
{
public:
	vector<T, Alloc> &operator=(const vector<T, Alloc> &other);

private:
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};
}

class Rva002B5558
{
public:
	Rva002B5558 &operator=(const Rva002B5558 &other);

private:
	char m_pad[8];
};

struct BfmeAssignRecord52
{
	BfmeAssignRecord52 &operator=(const BfmeAssignRecord52 &other);

	Rva002B5558 m_00;
	char m_pad08[4];
	_STL::vector<Rva0040DC56Element> m_0C;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
};

BfmeAssignRecord52 &BfmeAssignRecord52::operator=(const BfmeAssignRecord52 &other)
{
	m_00 = other.m_00;
	m_0C = other.m_0C;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	m_30 = other.m_30;
	return *this;
}
