// cl: /DNDEBUG /MD /EHsc
// ?rva00418C33@Rva00418BFB@@QAE?AURva00418BFBIter@@PAURva00418BFBNode@@0ABURva00418BFBKey@@0@Z @ 0x00418C33 149B: tree _M_insert hint worker
// calling rowed 0x00418BB7 less over keys at +0x10 left at +8 right at +0xC
// plus rowed node factory 0x00382B7F and _Rebalance 0x00025490. Unblocks 0x00418D3C.
// Evidence: chain packet calls 0x00418BB7 shape matches STL _M_insert with member less.
struct Rva00418BFB;
namespace _STL {
	template <typename T> class allocator {};
	template <typename T> struct _Select1st {};
	template <typename T> struct less {};
	template <typename A, typename B> struct pair { A first; B second; };
	struct _Rb_tree_node_base {};
	template <typename V> struct _Rb_tree_node {};
	template <typename K, typename V, typename KOV, typename C, typename A>
	class _Rb_tree {
	public:
		typedef V value_type;
		typedef _Rb_tree_node<V> *_Link_type;
		friend struct ::Rva00418BFB;
	protected:
		_Link_type _M_create_node(const value_type &v);
	};
	template <typename D> class _Rb_global {
	public:
		static void _Rebalance(_Rb_tree_node_base *x, _Rb_tree_node_base *&root);
	};
}

struct Rva00418BFBKey {
	int lo;
	int hi;
};
struct Rva00418BFBNode {
	int _c0;
	Rva00418BFBNode *_parent;
	Rva00418BFBNode *_left;
	Rva00418BFBNode *_right;
	Rva00418BFBKey _key;
};
struct Rva00418BFBComp {
	bool operator()(const void *a, const void *b) const;
};
struct Rva00418BFBIter {
	Rva00418BFBNode *node;
};
struct Rva00418BFB {
	Rva00418BFBNode *_head;
	int _size;
	Rva00418BFBComp _comp;
	Rva00418BFBIter rva00418C33(Rva00418BFBNode *x, Rva00418BFBNode *y, const Rva00418BFBKey &v, Rva00418BFBNode *w);
};

typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > IntTree418C33;

Rva00418BFBIter Rva00418BFB::rva00418C33(Rva00418BFBNode *x, Rva00418BFBNode *y, const Rva00418BFBKey &v, Rva00418BFBNode *w)
{
	Rva00418BFBNode *z;
	if (y == _head || (w == 0 && (x != 0 || _comp((const void *)&v, (const void *)&y->_key)))) {
		z = (Rva00418BFBNode *)((IntTree418C33 *)this)->_M_create_node((const IntTree418C33::value_type &)v);
		y->_left = z;
		if (y == _head) {
			_head->_parent = z;
			_head->_right = z;
		} else if (y == _head->_left) {
			_head->_left = z;
		}
	} else {
		z = (Rva00418BFBNode *)((IntTree418C33 *)this)->_M_create_node((const IntTree418C33::value_type &)v);
		y->_right = z;
		if (y == _head->_right) {
			_head->_right = z;
		}
	}
	z->_parent = y;
	z->_left = 0;
	z->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)z, (_STL::_Rb_tree_node_base *&)_head->_parent);
	++_size;
	Rva00418BFBIter it;
	it.node = z;
	return it;
}
