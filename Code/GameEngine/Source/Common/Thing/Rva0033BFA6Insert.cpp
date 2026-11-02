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
	Rva0033BFA6Iter rva0033BFA6(Rva0033BFA6Node *x, Rva0033BFA6Node *parentNode, const Rva0033BFA6Key &insertKey, Rva0033BFA6Node *w);
};
Rva0033BFA6Iter Rva0033BFA6::rva0033BFA6(Rva0033BFA6Node *x, Rva0033BFA6Node *parentNode, const Rva0033BFA6Key &insertKey, Rva0033BFA6Node *w)
{
	Rva0033BFA6Node *newNode;
	if (parentNode == _head || (w == 0 && (x != 0 || _comp((const BitFlags<117> &)insertKey, (const BitFlags<117> &)parentNode->_key)))) {
		newNode = _M_create_node(insertKey);
		parentNode->_left = newNode;
		if (parentNode == _head) {
			_head->_parent = newNode;
			_head->_right = newNode;
		} else if (parentNode == _head->_left) {
			_head->_left = newNode;
		}
	} else {
		newNode = _M_create_node(insertKey);
		parentNode->_right = newNode;
		if (parentNode == _head->_right) {
			_head->_right = newNode;
		}
	}
	newNode->_parent = parentNode;
	newNode->_left = 0;
	newNode->_right = 0;
	_STL::_Rb_global<bool>::_Rebalance((_STL::_Rb_tree_node_base *)newNode, (_STL::_Rb_tree_node_base *&)_head->_parent);
	++_size;
	Rva0033BFA6Iter it;
	it.node = newNode;
	return it;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x002CF84D -> ?Rva002CF84DCreate@@YGPAXPBURva002CF120@@@Z
#pragma comment(linker, "/alternatename:?_M_create_node@Rva0033BFA6@@QAEPAURva0033BFA6Node@@ABURva0033BFA6Key@@@Z=?Rva002CF84DCreate@@YGPAXPBURva002CF120@@@Z")
