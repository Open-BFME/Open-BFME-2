// cl: /O1 /MD /GX-
// ?rva002B9A85@Rva002B9A85@@QAEXABURva002B9062Element@@@Z, retail 0x002B9A85, 11 bytes.
// Tail-jump forwarder: adds 0x154 then jumps to rowed vector push_back
// 0x002B9062 for 4-byte element Rva002B9062Element. Evidence: unlock packet;
// caller 0x0056B073; callee row ?push_back@?$vector@URva002B9062Element@@@Z.
struct Rva002B9062Element
{
	int m_x;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Rva002B9062Element, allocator<Rva002B9062Element> >
{
public:
	void push_back(const Rva002B9062Element &x);
};
}

class Rva002B9A85
{
public:
	void rva002B9A85(const Rva002B9062Element &x);
private:
	char m_pad[0x154];
	_STL::vector<Rva002B9062Element, _STL::allocator<Rva002B9062Element> > m_vec;
};

void Rva002B9A85::rva002B9A85(const Rva002B9062Element &x)
{
	m_vec.push_back(x);
}
