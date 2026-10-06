// cl: /DNDEBUG /MD /EHsc
// ?rva0033BFA6@Rva0033BFA6@@QAE?AURva0033BFA6Iter@@PAURva0033BFA6Node@@0ABURva0033BFA6Key@@0@Z
// @0x0033BFA6 149B. STLport _Rb_tree::_M_insert (hinted insert worker) for the
// ModelCondition SparseMatchFinder tree: the comparator call resolves to the
// rowed ModelCondition MapHelper 0x0033AD13 (SparseMatchFinderModelCondition-
// Compare117.cpp), and the node factory is the thiscall twin of the rowed free
// Rva002CF84DCreate 0x002CF84D (pinned; both target call sites 0x0033BFD9 and
// 0x0033BFF4 load ecx=this before the stdcall body that ignores it). The
// shape is the same 149B _M_insert as the AsciiString-keyed twins in
// stlport_tree_asciistring_key_insert.cpp. Node: parent +4 left +8 right +0xc
// value +0x10; head +0 first +4; _size +4; comparator +8.
struct Rva002CF120;
namespace _STL {
	struct _Rb_tree_node_base {};
	template <typename D> class _Rb_global {
	public:
		static void _Rebalance(_Rb_tree_node_base *x, _Rb_tree_node_base *&root);
	};
}
template <int BitCount> class BitFlags;
struct ModelConditionInfo;
template <class MatchableType, class FlagSet>
class SparseMatchFinder {
public:
	struct MapHelper {
		bool operator()(const FlagSet &a, const FlagSet &b) const;
	};
};
struct Rva0033BFA6Key {
	int lo;
	int hi;
};
struct Rva0033BFA6Node {
	int _c0;
	Rva0033BFA6Node *_parent;
	Rva0033BFA6Node *_left;
	Rva0033BFA6Node *_right;
	Rva0033BFA6Key _key;
};
typedef SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::MapHelper ModelConditionMapHelper117;
struct Rva0033BFA6Iter {
	Rva0033BFA6Node *node;
};
struct Rva0033BFA6 {
	Rva0033BFA6Node *_head;
	int _size;
	ModelConditionMapHelper117 _comp;
	Rva0033BFA6Node *_M_create_node(const Rva0033BFA6Key &v);
	Rva0033BFA6Iter rva0033BFA6(Rva0033BFA6Node *x, Rva0033BFA6Node *y, const Rva0033BFA6Key &v, Rva0033BFA6Node *w);
};
Rva0033BFA6Iter Rva0033BFA6::rva0033BFA6(Rva0033BFA6Node *x, Rva0033BFA6Node *y, const Rva0033BFA6Key &v, Rva0033BFA6Node *w)
{
	Rva0033BFA6Node *z;
	if (y == _head || (w == 0 && (x != 0 || _comp((const BitFlags<117> &)v, (const BitFlags<117> &)y->_key)))) {
		z = _M_create_node(v);
		y->_left = z;
		if (y == _head) {
			_head->_parent = z;
			_head->_right = z;
		} else if (y == _head->_left) {
			_head->_left = z;
		}
	} else {
		z = _M_create_node(v);
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
	Rva0033BFA6Iter it;
	it.node = z;
	return it;
}
