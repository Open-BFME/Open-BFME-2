// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
// ??4Rva0038454E@@QAEAAV0@ABV0@@Z @ 0x00387945 (291B).
// Strategic stats block operator=: base Rva003877A7 then eight Rva00387568Element
// maps plus two Rva00383B39Key maps plus five Rva00387568Element maps.
// Layout from retail offsets; callees rowed in Rva003877A7OpAssign and StlSweep units.
// Callers pin PSPlayerAllStats setStrategicStats.

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

class Rva0038454E : public Rva003877A7
{
public:
	Rva0038454E &operator=(const Rva0038454E &that);
private:
	typedef _STL::_Rb_tree<Rva00383B39Key, Rva00383B39Key, _STL::_Identity<Rva00383B39Key>, _STL::less<Rva00383B39Key>, _STL::allocator<Rva00383B39Key> > MapA;
	typedef _STL::_Rb_tree<Rva00387568Element, Rva00387568Element, _STL::_Identity<Rva00387568Element>, _STL::less<Rva00387568Element>, _STL::allocator<Rva00387568Element> > MapB;
	MapB m_154;
	MapB m_160;
	MapB m_16c;
	MapB m_178;
	MapB m_184;
	MapB m_190;
	MapB m_19c;
	MapB m_1a8;
	MapA m_1b4;
	MapA m_1c0;
	MapB m_1cc;
	MapB m_1d8;
	MapB m_1e4;
	MapB m_1f0;
	MapB m_1fc;
};

Rva0038454E &Rva0038454E::operator=(const Rva0038454E &that)
{
	Rva003877A7::operator=(that);
	m_154 = that.m_154;
	m_160 = that.m_160;
	m_16c = that.m_16c;
	m_178 = that.m_178;
	m_184 = that.m_184;
	m_190 = that.m_190;
	m_19c = that.m_19c;
	m_1a8 = that.m_1a8;
	m_1b4 = that.m_1b4;
	m_1c0 = that.m_1c0;
	m_1cc = that.m_1cc;
	m_1d8 = that.m_1d8;
	m_1e4 = that.m_1e4;
	m_1f0 = that.m_1f0;
	m_1fc = that.m_1fc;
	return *this;
}
