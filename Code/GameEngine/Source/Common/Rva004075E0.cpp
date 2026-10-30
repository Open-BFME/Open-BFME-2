// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva004075E0@Rva004075E0@@QAE?AURva004075E0Iter@@PAURva004075E0Node@@0ABURva004075E0Key@@0@Z retail 0x004075E0 136B
// Evidence: unlock lane; rowed _M_create_node uintbool 0x002D464E plus _Rebalance 0x00025490 plus inlined less uint; callers 0x004076CA 0x00407CE9; prev Rva004074B6 next Rva004076EE same /O1.
struct Rva004075E0;
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
		friend struct ::Rva004075E0;
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
struct Rva004075E0Node {
	int _c0;
	Rva004075E0Node *_parent;
	Rva004075E0Node *_left;
	Rva004075E0Node *_right;
	unsigned int _key10;
	bool _val14;
	char _pad15[3];
};
struct Rva004075E0Key {
	unsigned int key;
	bool val;
	char _pad[3];
};
struct Rva004075E0Iter {
	Rva004075E0Node *node;
	Rva004075E0Iter(Rva004075E0Node *n);
};
// ??0Rva004075E0Iter@@QAE@PAURva004075E0Node@@@Z present-unmatched
inline Rva004075E0Iter::Rva004075E0Iter(Rva004075E0Node *n) : node(n) {}
struct Rva004075E0Pair {
	Rva004075E0Node *first;
	bool second;
	char _pad[3];
	Rva004075E0Pair(Rva004075E0Node *f, bool s);
	Rva004075E0Pair(Rva004075E0Iter it, bool s);
};
// ??0Rva004075E0Pair@@QAE@PAURva004075E0Node@@_N@Z present-unmatched
inline Rva004075E0Pair::Rva004075E0Pair(Rva004075E0Node *f, bool s) : first(f), second(s) {}
// ??0Rva004075E0Pair@@QAE@URva004075E0Iter@@_N@Z present-unmatched
inline Rva004075E0Pair::Rva004075E0Pair(Rva004075E0Iter it, bool s) : first(it.node), second(s) {}
struct Rva004075E0 {
	Rva004075E0Node *_head;
	unsigned int _size;
	Rva004075E0Iter rva004075E0(Rva004075E0Node *x, Rva004075E0Node *parent, const Rva004075E0Key &v, Rva004075E0Node *w);
	Rva004075E0Pair rva00407668(const Rva004075E0Key &v);
	Rva004075E0Iter rva00407C7F(Rva004075E0Iter position, const Rva004075E0Key &v);
};
typedef _STL::_Rb_tree<unsigned int, _STL::pair<const unsigned int, bool>, _STL::_Select1st<_STL::pair<const unsigned int, bool> >, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, bool> > > UIntBoolTree075E0;
Rva004075E0Iter Rva004075E0::rva004075E0(Rva004075E0Node *x, Rva004075E0Node *parent, const Rva004075E0Key &v, Rva004075E0Node *w)
{
	Rva004075E0Node *newNode;
	if (parent == _head || (w == 0 && (x != 0 || v.key < parent->_key10))) {
		newNode = (Rva004075E0Node *)((UIntBoolTree075E0 *)this)->_M_create_node((const UIntBoolTree075E0::value_type &)v);
		parent->_left = newNode;
		if (parent == _head) {
			_head->_parent = newNode;
			_head->_right = newNode;
		} else if (parent == _head->_left) {
			_head->_left = newNode;
		}
	} else {
		newNode = (Rva004075E0Node *)((UIntBoolTree075E0 *)this)->_M_create_node((const UIntBoolTree075E0::value_type &)v);
		parent->_right = newNode;
		if (parent == _head->_right) {
			_head->_right = newNode;
		}
	}
	newNode->_parent = parent;
	newNode->_left = 0;
	newNode->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)newNode, (_STL::_Rb_tree_node_base *&)_head->_parent);
	++_size;
	return Rva004075E0Iter(newNode);
}
// ?rva00407668@Rva004075E0@@QAE?AURva004075E0Pair@@ABURva004075E0Key@@@Z retail 0x00407668 134B
// Evidence: chain lane calls rowed 0x004075E0 plus rowed _M_decrement 0x000242C0 plus inlined less uint; caller 0x00407D92; prev same TU same flags.
Rva004075E0Pair Rva004075E0::rva00407668(const Rva004075E0Key &v)
{
	Rva004075E0Node *header = _head;
	Rva004075E0Node *root = header->_parent;
	Rva004075E0Node *parent = header;
	bool comp = true;
	while (root != 0) {
		parent = root;
		comp = v.key < root->_key10;
		root = comp ? root->_left : root->_right;
	}
	Rva004075E0Node *j = parent;
	if (comp) {
		if (j == header->_left)
			return Rva004075E0Pair(rva004075E0(parent, parent, v, 0), true);
		j = (Rva004075E0Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)parent);
	}
	if (j->_key10 < v.key)
		return Rva004075E0Pair(rva004075E0(root, parent, v, 0), true);
	return Rva004075E0Pair(j, false);
}
// ?rva00407C7F@Rva004075E0@@QAE?AURva004075E0Iter@@U2@ABURva004075E0Key@@@Z retail 0x00407C7F 294B
// Evidence: chain lane calls rowed 0x004075E0 plus rowed 0x00407668 plus rowed _M_increment 0x00024250 plus _M_decrement 0x000242C0; caller 0x00407DB6; prev same TU same flags.
Rva004075E0Iter Rva004075E0::rva00407C7F(Rva004075E0Iter position, const Rva004075E0Key &v)
{
	if (position.node == _head->_left) {
		if (_size <= 0)
			return rva00407668(v).first;
		if (v.key < position.node->_key10)
			return rva004075E0(position.node, position.node, v, 0);
		else {
			bool comp_pos_v = position.node->_key10 < v.key;
			if (comp_pos_v == false)
				return position;
			Rva004075E0Iter after = position;
			after.node = (Rva004075E0Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.node);
			if (after.node == _head)
				return rva004075E0(0, position.node, v, position.node);
			if (v.key < after.node->_key10) {
				if (position.node->_right == 0)
					return rva004075E0(0, position.node, v, position.node);
				else
					return rva004075E0(after.node, after.node, v, 0);
			} else {
				return rva00407668(v).first;
			}
		}
	} else if (position.node == _head) {
		if (_head->_right->_key10 < v.key)
			return rva004075E0(0, _head->_right, v, position.node);
		else
			return rva00407668(v).first;
	} else {
		Rva004075E0Iter before = position;
		before.node = (Rva004075E0Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)before.node);
		bool comp_v_pos = v.key < position.node->_key10;
		if (comp_v_pos && before.node->_key10 < v.key) {
			if (before.node->_right == 0)
				return rva004075E0(0, before.node, v, before.node);
			else
				return rva004075E0(position.node, position.node, v, 0);
		} else {
			Rva004075E0Iter after = position;
			after.node = (Rva004075E0Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.node);
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = position.node->_key10 < v.key;
			if (!comp_v_pos && comp_pos_v && (after.node == _head || v.key < after.node->_key10)) {
				if (position.node->_right == 0)
					return rva004075E0(0, position.node, v, position.node);
				else
					return rva004075E0(after.node, after.node, v, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else
					return rva00407668(v).first;
			}
		}
	}
}
