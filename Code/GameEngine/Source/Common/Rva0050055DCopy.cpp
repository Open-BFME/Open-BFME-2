// cl: /O1 /EHs /MD
//
// ??0Rva0050055D@@QAE@ABV0@@Z @0x0050055D 61B: copy constructor of a holder of
// two STLport int->void* trees: the rowed _Rb_tree copy constructors
// 0x004FFEAF (+0, Rva004FFEAFLess) and 0x004FFF54 (+0xC, Rva004FFF54Less), the
// second under EH state 0. Nine REL32 callers (0x005005DD .. 0x0059CB8E); owner
// unknown, so the name is address-derived.

struct Rva004FFEAFLess;
struct Rva004FFF54Less;

namespace _STL
{
template <class T>
class allocator;

template <class T1, class T2>
struct pair;

template <class Pair>
struct _Select1st;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	_Rb_tree(const _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &other);
	~_Rb_tree();

private:
	void *m_header;
	unsigned int m_node_count;
	int m_compare;
};
}

typedef _STL::pair<const int, void *> Rva0050055DPair;

class Rva0050055D
{
public:
	Rva0050055D(const Rva0050055D &other);

private:
	_STL::_Rb_tree<int, Rva0050055DPair, _STL::_Select1st<Rva0050055DPair>, Rva004FFEAFLess,
			_STL::allocator<Rva0050055DPair> > m_first;
	_STL::_Rb_tree<int, Rva0050055DPair, _STL::_Select1st<Rva0050055DPair>, Rva004FFF54Less,
			_STL::allocator<Rva0050055DPair> > m_second;
};

Rva0050055D::Rva0050055D(const Rva0050055D &other) :
	m_first(other.m_first),
	m_second(other.m_second)
{
}
