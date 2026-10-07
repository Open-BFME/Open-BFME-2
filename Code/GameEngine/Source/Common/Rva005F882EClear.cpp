// cl: /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
//
// ?rva005F882E@Rva005F882E@@QAEXXZ, retail 0x005F882E, 23 bytes.
// Chain body: forwards to the rowed Rva00577EAA::rva00577EAA at 0x00577EAA
// with the same this, then clears the vector<Rva005F8620Element> at +0x20
// through the rowed erase at 0x005F8620 (begin/end inlined). Evidence:
// packet disassembly, callees rowed, thunk at 0x005F884D (mov ecx,[ecx+4]
// then jmp here), prev deleting dtor 0x005F8804 and next push_back 0x005F8855.

class Rva00577E43;
class Rva00577EAA
{
public:
	void rva00577EAA();

private:
	char m_pad00[4];
	Rva00577E43 *m_target;
};

struct Rva005F8620Element;

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A> class vector
{
public:
	T *begin() { return m_begin; }
	T *end() { return m_end; }
	T *erase(T *first, T *last);

	T *m_begin;
	T *m_end;
	T *m_endOfStorage;
};
}

class Rva005F882E : public Rva00577EAA
{
public:
	void rva005F882E();

private:
	char m_pad08[0x20 - 8];
	_STL::vector<Rva005F8620Element, _STL::allocator<Rva005F8620Element> > m_vec;
};

// ?rva005F882E@Rva005F882E@@QAEXXZ @0x005F882E
void Rva005F882E::rva005F882E()
{
	rva00577EAA();
	_STL::vector<Rva005F8620Element, _STL::allocator<Rva005F8620Element> > &vec = m_vec;
	vec.erase(vec.begin(), vec.end());
}
