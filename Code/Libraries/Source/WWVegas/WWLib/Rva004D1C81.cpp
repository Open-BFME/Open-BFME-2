// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
//
// ?rva004D1C81@Rva004D1C81@@QAE?AURva004D1C81Iter@@PAURva004D1C81Node@@0ABURva004D1C81Key@@0@Z retail 0x004D1C81 138B
// _M_insert worker for map<unsigned short,int> (pair<const unsigned short,int> value, WORD key at +0x10).
// Real _M_insert for this GH tree already rowed at 0x00157130 (175B, different flags); this 138B /O1 copy
// is the WWLib out-of-line copy called by insert_unique 0x0046ABA6. Calls honest node factory 0x004DCC62
// (0x18 node, pair construct) plus rowed _Rebalance 0x00025490. Shape matches honest precedent
// Rva0046AC52.cpp and WORD-key precedent stlport_rb_tree_BfmeStringRecord004D05B8_insert.cpp
// (mov cx cmp jb). Callers 0x0046AC0C 0x0046E38E.
struct Rva004D1C81;
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
		friend struct ::Rva004D1C81;
	protected:
		_Link_type _M_create_node(const value_type &v);
	};
	template <typename D> class _Rb_global {
	public:
		static void _Rebalance(_Rb_tree_node_base *x, _Rb_tree_node_base *&root);
		static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
		static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *x);
	};
}
class Rva004DCC62
{
public:
	void *rva004DCC62(const void *src);
};
struct Rva004D1C81Node {
	int _c0;
	Rva004D1C81Node *_parent;
	Rva004D1C81Node *_left;
	Rva004D1C81Node *_right;
	unsigned short _key10;
	unsigned short _pad12;
	int _val14;
};
struct Rva004D1C81Key {
	unsigned short key;
	int val;
};
struct Rva004D1C81Iter {
	Rva004D1C81Node *node;
	Rva004D1C81Iter(Rva004D1C81Node *n);
};
// ??0Rva004D1C81Iter@@QAE@PAURva004D1C81Node@@@Z present-unmatched
inline Rva004D1C81Iter::Rva004D1C81Iter(Rva004D1C81Node *n) : node(n) {}
struct Rva004D1C81Pair {
	Rva004D1C81Node *first;
	bool second;
	char _pad[3];
	Rva004D1C81Pair(Rva004D1C81Node *f, bool s);
	Rva004D1C81Pair(Rva004D1C81Iter it, bool s);
};
// ??0Rva004D1C81Pair@@QAE@PAURva004D1C81Node@@_N@Z present-unmatched
inline Rva004D1C81Pair::Rva004D1C81Pair(Rva004D1C81Node *f, bool s) : first(f), second(s) {}
// ??0Rva004D1C81Pair@@QAE@URva004D1C81Iter@@_N@Z present-unmatched
inline Rva004D1C81Pair::Rva004D1C81Pair(Rva004D1C81Iter it, bool s) : first(it.node), second(s) {}
struct Rva004D1C81 {
	Rva004D1C81Node *_head;
	unsigned int _size;
	Rva004D1C81Iter rva004D1C81(Rva004D1C81Node *x, Rva004D1C81Node *parent, const Rva004D1C81Key &v, Rva004D1C81Node *w);
	Rva004D1C81Pair rva0046ABA6(const Rva004D1C81Key &v);
	Rva004D1C81Iter rva0046E31F(Rva004D1C81Iter position, const Rva004D1C81Key &v);
};
Rva004D1C81Iter Rva004D1C81::rva004D1C81(Rva004D1C81Node *x, Rva004D1C81Node *parent, const Rva004D1C81Key &v, Rva004D1C81Node *w)
{
	Rva004D1C81Node *z;
	if (parent == _head || (w == 0 && (x != 0 || v.key < parent->_key10))) {
		z = (Rva004D1C81Node *)((Rva004DCC62 *)this)->rva004DCC62((const void *)&v);
		parent->_left = z;
		if (parent == _head) {
			_head->_parent = z;
			_head->_right = z;
		} else if (parent == _head->_left) {
			_head->_left = z;
		}
	} else {
		z = (Rva004D1C81Node *)((Rva004DCC62 *)this)->rva004DCC62((const void *)&v);
		parent->_right = z;
		if (parent == _head->_right) {
			_head->_right = z;
		}
	}
	z->_parent = parent;
	z->_left = 0;
	z->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)z, (_STL::_Rb_tree_node_base *&)_head->_parent);
	++_size;
	return Rva004D1C81Iter(z);
}
// ?rva0046ABA6@Rva004D1C81@@QAE?AURva004D1C81Pair@@ABURva004D1C81Key@@@Z retail 0x0046ABA6 138B
// insert_unique for map<unsigned short,int>: WORD-key loop via mov cx cmp jb setb, rowed _M_decrement
// 0x000242C0 plus just-landed honest _M_insert 0x004D1C81. Same class/tree as rva004D1C81; chain from it.
// Caller 0x0046E442 in hint 0x0046E31F. Precedent Rva0046AC52::rva002D563D.
Rva004D1C81Pair Rva004D1C81::rva0046ABA6(const Rva004D1C81Key &v)
{
	Rva004D1C81Node *header = _head;
	Rva004D1C81Node *x = header->_parent;
	Rva004D1C81Node *parent = header;
	bool comp = true;
	while (x != 0) {
		parent = x;
		comp = v.key < x->_key10;
		x = comp ? x->_left : x->_right;
	}
	Rva004D1C81Node *j = parent;
	if (comp) {
		if (j == header->_left)
			return Rva004D1C81Pair(rva004D1C81(parent, parent, v, 0), true);
		j = (Rva004D1C81Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)parent);
	}
	if (j->_key10 < v.key)
		return Rva004D1C81Pair(rva004D1C81(x, parent, v, 0), true);
	return Rva004D1C81Pair(j, false);
}
Rva004D1C81Iter Rva004D1C81::rva0046E31F(Rva004D1C81Iter position, const Rva004D1C81Key &v)
{
	if (position.node == _head->_left) {
		if (_size <= 0)
			return rva0046ABA6(v).first;
		if (v.key < position.node->_key10)
			return rva004D1C81(position.node, position.node, v, 0);
		else {
			bool comp_pos_v = position.node->_key10 < v.key;
			if (comp_pos_v == false)
				return position;
			Rva004D1C81Iter after = position;
			after.node = (Rva004D1C81Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.node);
			if (after.node == _head)
				return rva004D1C81(0, position.node, v, position.node);
			if (v.key < after.node->_key10) {
				if (position.node->_right == 0)
					return rva004D1C81(0, position.node, v, position.node);
				else
					return rva004D1C81(after.node, after.node, v, 0);
			} else {
				return rva0046ABA6(v).first;
			}
		}
	} else if (position.node == _head) {
		if (_head->_right->_key10 < v.key)
			return rva004D1C81(0, _head->_right, v, position.node);
		else
			return rva0046ABA6(v).first;
	} else {
		Rva004D1C81Iter before = position;
		before.node = (Rva004D1C81Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)before.node);
		bool comp_v_pos = v.key < position.node->_key10;
		if (comp_v_pos && before.node->_key10 < v.key) {
			if (before.node->_right == 0)
				return rva004D1C81(0, before.node, v, before.node);
			else
				return rva004D1C81(position.node, position.node, v, 0);
		} else {
			Rva004D1C81Iter after = position;
			after.node = (Rva004D1C81Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.node);
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = position.node->_key10 < v.key;
			if (!comp_v_pos && comp_pos_v && (after.node == _head || v.key < after.node->_key10)) {
				if (position.node->_right == 0)
					return rva004D1C81(0, position.node, v, position.node);
				else
					return rva004D1C81(after.node, after.node, v, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else
					return rva0046ABA6(v).first;
			}
		}
	}
}
