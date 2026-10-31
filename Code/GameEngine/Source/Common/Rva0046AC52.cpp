// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva0046AC52@Rva0046AC52@@QAE?AURva0046AC52Iter@@PAURva0046AC52Node@@0ABURva0046AC52Key@@0@Z retail 0x0046AC52 136B
// Evidence: unlock lane; rowed _M_create_node uintbool 0x002D464E plus _Rebalance 0x00025490 plus inlined less uint; callers 0x002D569F 0x0046E5CD plus rowed uintbool create 0x002D464E plus Rebalance 0x00025490.
struct Rva0046AC52;
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
		friend struct ::Rva0046AC52;
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
struct Rva0046AC52Node {
	int _c0;
	Rva0046AC52Node *_parent;
	Rva0046AC52Node *_left;
	Rva0046AC52Node *_right;
	int _key10;
	bool _val14;
	char _pad15[3];
};
struct Rva0046AC52Key {
	int key;
	bool val;
	char _pad[3];
};
struct Rva0046AC52Iter {
	Rva0046AC52Node *node;
	Rva0046AC52Iter(Rva0046AC52Node *n);
};
// ??0Rva0046AC52Iter@@QAE@PAURva0046AC52Node@@@Z present-unmatched
inline Rva0046AC52Iter::Rva0046AC52Iter(Rva0046AC52Node *n) : node(n) {}
struct Rva0046AC52Pair {
	Rva0046AC52Node *first;
	bool second;
	char _pad[3];
	Rva0046AC52Pair(Rva0046AC52Node *f, bool inserted);
	Rva0046AC52Pair(Rva0046AC52Iter it, bool inserted);
};
// ??0Rva0046AC52Pair@@QAE@PAURva0046AC52Node@@_N@Z present-unmatched
inline Rva0046AC52Pair::Rva0046AC52Pair(Rva0046AC52Node *f, bool s) : first(f), second(s) {}
// ??0Rva0046AC52Pair@@QAE@URva0046AC52Iter@@_N@Z present-unmatched
inline Rva0046AC52Pair::Rva0046AC52Pair(Rva0046AC52Iter it, bool inserted) : first(it.node), second(inserted) {}
struct Rva0046AC52 {
	Rva0046AC52Node *_head;
	unsigned int _size;
	Rva0046AC52Iter rva0046AC52(Rva0046AC52Node *child, Rva0046AC52Node *parent, const Rva0046AC52Key &entry, Rva0046AC52Node *hint);
	Rva0046AC52Pair rva002D563D(const Rva0046AC52Key &entry);
	Rva0046AC52Iter rva0046E563(Rva0046AC52Iter position, const Rva0046AC52Key &entry);
	Rva0046AC52Iter rva0046F0A5(Rva0046AC52Node *position, const Rva0046AC52Key &entry);
};
typedef _STL::_Rb_tree<unsigned int, _STL::pair<const unsigned int, bool>, _STL::_Select1st<_STL::pair<const unsigned int, bool> >, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, bool> > > UIntBoolTree075E0;
Rva0046AC52Iter Rva0046AC52::rva0046AC52(Rva0046AC52Node *child, Rva0046AC52Node *parent, const Rva0046AC52Key &entry, Rva0046AC52Node *hint)
{
	Rva0046AC52Node *newNode;
	if (parent == _head || (hint == 0 && (child != 0 || entry.key < parent->_key10))) {
		newNode = (Rva0046AC52Node *)((UIntBoolTree075E0 *)this)->_M_create_node((const UIntBoolTree075E0::value_type &)entry);
		parent->_left = newNode;
		if (parent == _head) {
			_head->_parent = newNode;
			_head->_right = newNode;
		} else if (parent == _head->_left) {
			_head->_left = newNode;
		}
	} else {
		newNode = (Rva0046AC52Node *)((UIntBoolTree075E0 *)this)->_M_create_node((const UIntBoolTree075E0::value_type &)entry);
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
	return Rva0046AC52Iter(newNode);
}
// ?rva002D563D@Rva0046AC52@@QAE?AURva0046AC52Pair@@ABURva0046AC52Key@@@Z @0x002D563D 134B
// Evidence: chain lane calls rowed 0x0046AC52 plus rowed _M_decrement 0x000242C0 plus inlined less int; callers 0x002D6454 0x002D6586 0x0046E676.
Rva0046AC52Pair Rva0046AC52::rva002D563D(const Rva0046AC52Key &entry)
{
	Rva0046AC52Node *header = _head;
	Rva0046AC52Node *root = header->_parent;
	Rva0046AC52Node *parent = header;
	bool comp = true;
	while (root != 0) {
		parent = root;
		comp = entry.key < root->_key10;
		root = comp ? root->_left : root->_right;
	}
	Rva0046AC52Node *j = parent;
	if (comp) {
		if (j == header->_left)
			return Rva0046AC52Pair(rva0046AC52(parent, parent, entry, 0), true);
		j = (Rva0046AC52Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)parent);
	}
	if (j->_key10 < entry.key)
		return Rva0046AC52Pair(rva0046AC52(root, parent, entry, 0), true);
	return Rva0046AC52Pair(j, false);
}
// ?rva0046F0A5@Rva0046AC52@@QAE?AURva0046AC52Iter@@PAURva0046AC52Node@@ABURva0046AC52Key@@@Z @0x0046F0A5 29B
// Evidence: chain lane calls rowed 0x0046E563; same TU same flags; caller 0x00470388.
Rva0046AC52Iter Rva0046AC52::rva0046F0A5(Rva0046AC52Node *position, const Rva0046AC52Key &entry)
{
	return rva0046E563(position, entry);
}
// ?rva0046E563@Rva0046AC52@@QAE?AURva0046AC52Iter@@U2@ABURva0046AC52Key@@@Z @0x0046E563 294B
// Evidence: chain lane calls rowed 0x0046AC52 plus rowed 0x002D563D plus rowed _M_increment plus _M_decrement; same TU same flags.
Rva0046AC52Iter Rva0046AC52::rva0046E563(Rva0046AC52Iter position, const Rva0046AC52Key &entry)
{
	if (position.node == _head->_left) {
		if (_size <= 0)
			return rva002D563D(entry).first;
		if (entry.key < position.node->_key10)
			return rva0046AC52(position.node, position.node, entry, 0);
		else {
			bool comp_pos_v = position.node->_key10 < entry.key;
			if (comp_pos_v == false)
				return position;
			Rva0046AC52Iter after = position;
			after.node = (Rva0046AC52Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.node);
			if (after.node == _head)
				return rva0046AC52(0, position.node, entry, position.node);
			if (entry.key < after.node->_key10) {
				if (position.node->_right == 0)
					return rva0046AC52(0, position.node, entry, position.node);
				else
					return rva0046AC52(after.node, after.node, entry, 0);
			} else {
				return rva002D563D(entry).first;
			}
		}
	} else if (position.node == _head) {
		if (_head->_right->_key10 < entry.key)
			return rva0046AC52(0, _head->_right, entry, position.node);
		else
			return rva002D563D(entry).first;
	} else {
		Rva0046AC52Iter before = position;
		before.node = (Rva0046AC52Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)before.node);
		bool comp_v_pos = entry.key < position.node->_key10;
		if (comp_v_pos && before.node->_key10 < entry.key) {
			if (before.node->_right == 0)
				return rva0046AC52(0, before.node, entry, before.node);
			else
				return rva0046AC52(position.node, position.node, entry, 0);
		} else {
			Rva0046AC52Iter after = position;
			after.node = (Rva0046AC52Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.node);
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = position.node->_key10 < entry.key;
			if (!comp_v_pos && comp_pos_v && (after.node == _head || entry.key < after.node->_key10)) {
				if (position.node->_right == 0)
					return rva0046AC52(0, position.node, entry, position.node);
				else
					return rva0046AC52(after.node, after.node, entry, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else
					return rva002D563D(entry).first;
			}
		}
	}
}
