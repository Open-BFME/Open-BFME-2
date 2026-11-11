// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva00418500@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAEAAV12@ABV12@@Z 0x00418500 115B
// Second _Rb_tree<int,int> operator= instantiation. The canonical ??4 name is
// already claimed at 0x002CF742, so this twin carries the address-derived
// method name and the sibling shape that matched 0x0038407F exactly: rowed
// clear 0x0022C409 and rowed _M_copy 0x0041848D plus _S_minimum/_S_maximum
// bottom-tested walks. Evidence: callers 0x004186E7 0x004187EA; neighbouring
// stlport_map_int_int_copy_0041848D.
#include "../../../../GameEngine/Include/Common/Rva002294A3.h"

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
	_Rb_tree &rva00418500(const _Rb_tree &x);
private:
	Node *_M_copy_0041848D(Node *x, Node *p);
public:
	_Rb_tree_node_base *_M_header;
	unsigned int _M_node_count;
};

typedef pair<const int, int> IntIntValue;
typedef _Select1st<IntIntValue> IntIntKeyOf;
typedef less<int> IntIntCompare;
typedef allocator<IntIntValue> IntIntAlloc;
typedef _Rb_tree<int, IntIntValue, IntIntKeyOf, IntIntCompare, IntIntAlloc> IntIntTree;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rva00418500(const _Rb_tree &x)
{
	if (this != &x) {
		((Rva002294A3 *)this)->rva0022C409();
		_M_node_count = 0;
		if (x._M_header->m_parent == 0) {
			_M_header->m_parent = 0;
			_M_header->m_left = _M_header;
			_M_header->m_right = _M_header;
		} else {
			_Rb_tree_node_base *header = _M_header;
			header->m_parent = (_Rb_tree_node_base *)((IntIntTree *)this)->_M_copy_0041848D((typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *)x._M_header->m_parent, (typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *)header);
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

template IntIntTree &IntIntTree::rva00418500(const IntIntTree &);

}

// ?rva004186E0@Rva004186E0Map@@QAEAAV1@ABV1@@Z 0x004186E0 18B: the map-level operator=
// over the tree assignment above (its call at 0x004186E7): assigns the trees and
// returns *this. Skeleton twin of AsciiString::operator= 0x00001733. The
// map spelling is address-derived; only its +0 tree is modelled.
class Rva004186E0Map
{
public:
	Rva004186E0Map &rva004186E0(const Rva004186E0Map &other);
private:
	_STL::IntIntTree m_tree;
};

Rva004186E0Map &Rva004186E0Map::rva004186E0(const Rva004186E0Map &other)
{
	m_tree.rva00418500(other.m_tree);
	return *this;
}
