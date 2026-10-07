// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
// ??4Rva003844D7@@QAEAAV0@ABV0@@Z @ 0x003874F9 (111B).
// Open-play stats block operator=: base Rva003877A7 then one Rva003876A4Element
// map plus two Rva00383B39Key maps plus two Rva00387568Element maps.
// Layout from retail offsets; callees rowed in Rva003877A7OpAssign and StlSweep units.
// Callers pin PSPlayerAllStats setOpenPlayStats and Rva00385333 operator=.

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};
template <class T> struct _Identity {};
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	_Rb_tree &operator=(const _Rb_tree &that);
	char m_pad[0x0c];
};
}

struct Rva00383B39Key
{
	int word;
	bool operator<(const Rva00383B39Key &b) const { return word < b.word; }
	bool operator==(const Rva00383B39Key &b) const { return word == b.word; }
};

struct Rva003876A4Element
{
	Rva003876A4Element();
	Rva003876A4Element(const Rva003876A4Element &that);
	~Rva003876A4Element();
	Rva003876A4Element &operator=(const Rva003876A4Element &that);
	char bytes[8];
};
bool operator<(const Rva003876A4Element &a, const Rva003876A4Element &b);

struct Rva00387568Element
{
	Rva00387568Element();
	Rva00387568Element(const Rva00387568Element &that);
	~Rva00387568Element();
	Rva00387568Element &operator=(const Rva00387568Element &that);
	char bytes[8];
};
bool operator<(const Rva00387568Element &a, const Rva00387568Element &b);

class Rva003877A7
{
public:
	Rva003877A7 &operator=(const Rva003877A7 &that);
private:
	char m_pad[0x154];
};

class Rva003844D7 : public Rva003877A7
{
public:
	Rva003844D7 &operator=(const Rva003844D7 &that);
private:
	typedef _STL::_Rb_tree<Rva003876A4Element, Rva003876A4Element, _STL::_Identity<Rva003876A4Element>, _STL::less<Rva003876A4Element>, _STL::allocator<Rva003876A4Element> > MapC;
	typedef _STL::_Rb_tree<Rva00383B39Key, Rva00383B39Key, _STL::_Identity<Rva00383B39Key>, _STL::less<Rva00383B39Key>, _STL::allocator<Rva00383B39Key> > MapA;
	typedef _STL::_Rb_tree<Rva00387568Element, Rva00387568Element, _STL::_Identity<Rva00387568Element>, _STL::less<Rva00387568Element>, _STL::allocator<Rva00387568Element> > MapB;
	MapC m_154;
	MapA m_160;
	MapA m_16c;
	MapB m_178;
	MapB m_184;
};

Rva003844D7 &Rva003844D7::operator=(const Rva003844D7 &that)
{
	Rva003877A7::operator=(that);
	m_154 = that.m_154;
	m_160 = that.m_160;
	m_16c = that.m_16c;
	m_178 = that.m_178;
	m_184 = that.m_184;
	return *this;
}
