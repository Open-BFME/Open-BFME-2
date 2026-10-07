// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
// ??4Rva003877A7@@QAEAAV0@ABV0@@Z @ 0x003877A7 (414B).
// Stats-block operator= called by pinned 0x003874F9 and 0x00387945.
// Copies 6 plus 6 plus 6 Rva00383B39Key maps then 8 Rva00387568Element maps
// then trailing ints and words. Layout from retail offsets. Same STLport
// Rb_tree operator= callees as StlSweepR3Rva00383FD7 and StlSweepW4Rva00387568.

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
	virtual ~Rva003877A7();
	Rva003877A7 &operator=(const Rva003877A7 &that);

private:
	typedef _STL::_Rb_tree<Rva00383B39Key, Rva00383B39Key, _STL::_Identity<Rva00383B39Key>, _STL::less<Rva00383B39Key>, _STL::allocator<Rva00383B39Key> > MapA;
	typedef _STL::_Rb_tree<Rva00387568Element, Rva00387568Element, _STL::_Identity<Rva00387568Element>, _STL::less<Rva00387568Element>, _STL::allocator<Rva00387568Element> > MapB;
	MapA m_004;
	MapA m_010;
	MapA m_01c;
	MapA m_028;
	MapA m_034;
	MapA m_040;
	MapA m_04c[6];
	MapA m_094[6];
	MapB m_0dc[8];
	int m_13c;
	int m_140;
	unsigned short m_144;
	unsigned short m_146;
	unsigned short m_148;
	unsigned short m_14a;
	unsigned short m_14c;
	int m_150;
};

Rva003877A7 &Rva003877A7::operator=(const Rva003877A7 &that)
{
	m_004 = that.m_004;
	m_010 = that.m_010;
	m_01c = that.m_01c;
	m_028 = that.m_028;
	m_034 = that.m_034;
	m_040 = that.m_040;
	for (int i = 0; i < 6; ++i)
		m_04c[i] = that.m_04c[i];
	for (int i = 0; i < 6; ++i)
		m_094[i] = that.m_094[i];
	m_0dc[0] = that.m_0dc[0];
	m_0dc[1] = that.m_0dc[1];
	m_0dc[2] = that.m_0dc[2];
	m_0dc[3] = that.m_0dc[3];
	m_0dc[4] = that.m_0dc[4];
	m_0dc[5] = that.m_0dc[5];
	m_0dc[6] = that.m_0dc[6];
	m_0dc[7] = that.m_0dc[7];
	m_13c = that.m_13c;
	m_140 = that.m_140;
	m_144 = that.m_144;
	m_146 = that.m_146;
	m_148 = that.m_148;
	m_14a = that.m_14a;
	m_14c = that.m_14c;
	m_150 = that.m_150;
	return *this;
}
