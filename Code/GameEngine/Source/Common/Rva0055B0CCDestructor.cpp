// cl: /Ireference/shims/bfmelist /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0055B0CC@@UAE@XZ @ 0x0055B0CC, 122 bytes.
// Destructor for the opaque owner established by its vtable, constructor at
// 0x0055B048 and Xfer member layout at 0x0055AED6. It removes this owner from
// each peer's +0x1C list, clears +0x14, runs reciprocal cleanup at 0x0055B01F,
// then destroys the two lists and AsciiString. The retail base vtable pointer
// is 0x00C6B900; novtable lets the source express its explicit destructor
// transition without depending on unresolved placeholder virtuals.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class Rva0023DAA5List : public _STL::list<int, _STL::allocator<int> >
{
public:
	~Rva0023DAA5List();
	void clear();
};

class AsciiStringMember
{
public:
	~AsciiStringMember();
	void *m_data;
};

class Rva0055AFF1
{
public:
	void rva0055AFF1(int value);
};

class Rva0055B0CC
{
public:
	virtual ~Rva0055B0CC();
	void rva0055B01F();

private:
	float m_04;
	int m_08;
	AsciiStringMember m_0C;
	unsigned int m_10;
	Rva0023DAA5List m_14;
	float m_18;
	Rva0023DAA5List m_1C;
	bool m_20;
	bool m_21;
	int m_24;
	bool m_28;
};

Rva0055B0CC::~Rva0055B0CC()
{
	for (_STL::list<int, _STL::allocator<int> >::iterator it = m_14.begin(); it != m_14.end(); ++it) {
		((Rva0055AFF1 *)*it)->rva0055AFF1((int)this);
	}
	m_14.clear();
	rva0055B01F();
}

// ?rva0055B156@Rva0055B156@@QAEXH@Z @0x0055B156 16B
// Gap between 0x0055B0CC dtor and deleting dtor same TU same flags.
// Evidence: thiscall 1 int arg ret 4; lea [esp+4] push plus add ecx 0x1c
// plus rowed list<int> push_back 0x0005548F; caller 0x004F20CE.
class Rva0055B156
{
public:
	void rva0055B156(int val);
private:
	char m_pad[0x1c];
	_STL::list<int, _STL::allocator<int> > m_list;
};

void Rva0055B156::rva0055B156(int val)
{
	m_list.push_back(val);
}
