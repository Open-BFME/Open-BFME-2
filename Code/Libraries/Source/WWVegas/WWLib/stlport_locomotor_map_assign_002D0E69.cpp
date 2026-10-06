// cl: /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// ?rva002D0E69@?$_Rb_tree@W4LocomotorSetType@@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@U?$_Select1st@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEAAV12@ABV12@@Z
// 115B @0x002D0E69: LocomotorSetType to template-vector map red-black tree
// assign. Calls the rowed clear 0x0026DEE4 then the rowed copy twin
// 0x002D0DA1, relinks leftmost/rightmost and copies node count. Same shape
// as SGI _Rb_tree operator=. Self-assign guard returns *this. No EH in
// retail hence /GX-. Flags copied from stlport_locomotor_map_copy_002D0DA1.cpp.

class LocomotorTemplate;

enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1,
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED,
	LOCOMOTORSET_FREEFALL,
	LOCOMOTORSET_WANDER,
	LOCOMOTORSET_PANIC,
	LOCOMOTORSET_TAXIING,
	LOCOMOTORSET_SUPERSONIC,
	LOCOMOTORSET_SLUGGISH,
	LOCOMOTORSET_COUNT
};

namespace _STL
{

template <class T>
struct less
{
};

template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
	void *_M_start;
	void *_M_finish;
	void *_M_end;
};

template <class K, class V>
struct pair
{
	K first;
	V second;
};

template <class P>
struct _Select1st
{
};

struct _Rb_tree_node_base
{
	char m_color;
	char m_pad[3];
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class V>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	V m_value;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	typedef _Rb_tree_node<Value> Node;
	void clear();
	Node *rva002D0DA1(Node *x, Node *p);
	_Rb_tree &rva002D0E69(const _Rb_tree &x);
public:
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
};

typedef vector<const LocomotorTemplate *, allocator<const LocomotorTemplate *> > BfmeLocomotorTemplateVector;
typedef pair<const LocomotorSetType, BfmeLocomotorTemplateVector> LocomotorMapValue;
typedef _Select1st<LocomotorMapValue> LocomotorMapKeyOf;
typedef less<LocomotorSetType> LocomotorMapCompare;
typedef allocator<LocomotorMapValue> LocomotorMapAlloc;
typedef _Rb_tree<LocomotorSetType, LocomotorMapValue, LocomotorMapKeyOf, LocomotorMapCompare, LocomotorMapAlloc> LocomotorMapTree;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rva002D0E69(const _Rb_tree &x)
{
	if (this != &x) {
		clear();
		_M_node_count = 0;
		if (x._M_header->m_parent == 0) {
			_M_header->m_parent = 0;
			_M_header->m_left = _M_header;
			_M_header->m_right = _M_header;
		} else {
			_Rb_tree_node_base *header = _M_header;
			header->m_parent = (_Rb_tree_node_base *)rva002D0DA1((Node *)x._M_header->m_parent, (Node *)header);
			_Rb_tree_node_base *cur = _M_header->m_parent;
			while (cur->m_left != 0)
				cur = cur->m_left;
			_M_header->m_left = cur;
			cur = _M_header->m_parent;
			while (cur->m_right != 0)
				cur = cur->m_right;
			_M_header->m_right = cur;
			_M_node_count = x._M_node_count;
		}
	}
	return *this;
}

template LocomotorMapTree &LocomotorMapTree::rva002D0E69(const LocomotorMapTree &);

}
