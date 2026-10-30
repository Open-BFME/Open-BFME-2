// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0046E455@Rva0046E455@@QAE?AURva0046E455Iter@@PAURva0046E455Node@@0ABVRva00469BEA@@0@Z 0x0046E455 136B evidence: unlock calls rowed create 0x46AC30 plus rowed Rebalance 0x25490 same shape as rowed 0x46AC52 136B
class Rva00469BEA
{
public:
	int m_key00;
	char m_pad04[16];
};
struct Rva0046E455Node
{
	int _c0;
	Rva0046E455Node *_parent;
	Rva0046E455Node *_left;
	Rva0046E455Node *_right;
	int _key10;
	char _pad14[16];
};
struct Rva0046E455Iter
{
	Rva0046E455Node *node;
	Rva0046E455Iter(Rva0046E455Node *n);
};
// ??0Rva0046E455Iter@@QAE@PAURva0046E455Node@@@Z present-unmatched
inline Rva0046E455Iter::Rva0046E455Iter(Rva0046E455Node *n) : node(n) {}
class Rva0046AC30
{
public:
	void *rva0046AC30(const Rva00469BEA &v);
};
struct Rva0046E455Pair {
	Rva0046E455Node *first;
	bool second;
	Rva0046E455Pair(Rva0046E455Node *f, bool s);
	Rva0046E455Pair(Rva0046E455Iter it, bool s);
};
// ??0Rva0046E455Pair@@QAE@PAURva0046E455Node@@_N@Z present-unmatched
inline Rva0046E455Pair::Rva0046E455Pair(Rva0046E455Node *f, bool s) : first(f), second(s) {}
// ??0Rva0046E455Pair@@QAE@URva0046E455Iter@@_N@Z present-unmatched
inline Rva0046E455Pair::Rva0046E455Pair(Rva0046E455Iter it, bool s) : first(it.node), second(s) {}
namespace _STL {
struct _Rb_tree_node_base {};
	template <typename D> class _Rb_global {
	public:
		static void _Rebalance(_Rb_tree_node_base *x, _Rb_tree_node_base *&root);
		static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *x);
		static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *x);
	};
}
struct Rva0046E455
{
	Rva0046E455Node *_head;
	unsigned int _size;
	Rva0046E455Iter rva0046E455(Rva0046E455Node *x, Rva0046E455Node *parent, const Rva00469BEA &v, Rva0046E455Node *w);
	Rva0046E455Pair rva0046E4DD(const Rva00469BEA &v);
	Rva0046E455Iter rva0046EEB5(Rva0046E455Iter position, const Rva00469BEA &v);
};
Rva0046E455Iter Rva0046E455::rva0046E455(Rva0046E455Node *x, Rva0046E455Node *parent, const Rva00469BEA &v, Rva0046E455Node *w)
{
	Rva0046E455Node *newNode;
	if (parent == _head || (w == 0 && (x != 0 || v.m_key00 < parent->_key10))) {
		newNode = (Rva0046E455Node *)((Rva0046AC30 *)this)->rva0046AC30(v);
		parent->_left = newNode;
		if (parent == _head) {
			_head->_parent = newNode;
			_head->_right = newNode;
		} else if (parent == _head->_left) {
			_head->_left = newNode;
		}
	} else {
		newNode = (Rva0046E455Node *)((Rva0046AC30 *)this)->rva0046AC30(v);
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
	return Rva0046E455Iter(newNode);
}
Rva0046E455Pair Rva0046E455::rva0046E4DD(const Rva00469BEA &v)
{
	Rva0046E455Node *header = _head;
	Rva0046E455Node *root = header->_parent;
	Rva0046E455Node *parent = header;
	bool comp = true;
	while (root != 0) {
		parent = root;
		comp = v.m_key00 < root->_key10;
		root = comp ? root->_left : root->_right;
	}
	Rva0046E455Node *j = parent;
	if (comp) {
		if (j == header->_left)
			return Rva0046E455Pair(rva0046E455(parent, parent, v, 0), true);
		j = (Rva0046E455Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)parent);
	}
	if (j->_key10 < v.m_key00)
		return Rva0046E455Pair(rva0046E455(root, parent, v, 0), true);
	return Rva0046E455Pair(j, false);
}
Rva0046E455Iter Rva0046E455::rva0046EEB5(Rva0046E455Iter position, const Rva00469BEA &v)
{
	if (position.node == _head->_left) {
		if (_size <= 0)
			return rva0046E4DD(v).first;
		if (v.m_key00 < position.node->_key10)
			return rva0046E455(position.node, position.node, v, 0);
		else {
			bool comp_pos_v = position.node->_key10 < v.m_key00;
			if (comp_pos_v == false)
				return position;
			Rva0046E455Iter after = position;
			after.node = (Rva0046E455Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.node);
			if (after.node == _head)
				return rva0046E455(0, position.node, v, position.node);
			if (v.m_key00 < after.node->_key10) {
				if (position.node->_right == 0)
					return rva0046E455(0, position.node, v, position.node);
				else
					return rva0046E455(after.node, after.node, v, 0);
			} else {
				return rva0046E4DD(v).first;
			}
		}
	} else if (position.node == _head) {
		if (_head->_right->_key10 < v.m_key00)
			return rva0046E455(0, _head->_right, v, position.node);
		else
			return rva0046E4DD(v).first;
	} else {
		Rva0046E455Iter before = position;
		before.node = (Rva0046E455Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)before.node);
		bool comp_v_pos = v.m_key00 < position.node->_key10;
		if (comp_v_pos && before.node->_key10 < v.m_key00) {
			if (before.node->_right == 0)
				return rva0046E455(0, before.node, v, before.node);
			else
				return rva0046E455(position.node, position.node, v, 0);
		} else {
			Rva0046E455Iter after = position;
			after.node = (Rva0046E455Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)after.node);
			bool comp_pos_v = !comp_v_pos;
			if (!comp_v_pos)
				comp_pos_v = position.node->_key10 < v.m_key00;
			if (!comp_v_pos && comp_pos_v && (after.node == _head || v.m_key00 < after.node->_key10)) {
				if (position.node->_right == 0)
					return rva0046E455(0, position.node, v, position.node);
				else
					return rva0046E455(after.node, after.node, v, 0);
			} else {
				if (comp_v_pos == comp_pos_v)
					return position;
				else
					return rva0046E4DD(v).first;
			}
		}
	}
}
