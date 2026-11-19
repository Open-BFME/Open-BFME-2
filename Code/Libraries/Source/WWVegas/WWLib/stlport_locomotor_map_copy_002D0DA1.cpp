// cl: /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// ?rva002D0DA1@?$_Rb_tree@W4LocomotorSetType@@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@U?$_Select1st@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEPAU?$_Rb_tree_node@U?$pair@$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@PAU32@0@Z
// 115B @0x002D0DA1: LocomotorSetType to template-vector map red-black tree
// copy. Same 115B _M_copy shape as the rowed 0x004FFD09 copy of the same
// tree type, but this TU calls the rowed _M_clone_node 0x002D0B9A directly
// (retail E8 targets it), so the clone is declared with its real rowed name
// and only this copy body is emitted under an honest rva method name: the
// real _M_copy mangling is already rowed at 0x004FFD09 and ledger names are
// unique. Self recursion resolves through the new row. No EH in retail
// hence /GX-. Flags copied from stlport_locomotor_map_copy.cpp.

class LocomotorTemplate;
struct Rva002D0B9AElement { short words[1]; };

#include "../../../../../reference/open-bfme-1/game/GameEngine/Include/Common/Enums/LocomotorSetType.h"













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
	template <class K, class V, class S, class C, class A> friend class _Rb_tree;
public:
	typedef _Rb_tree_node<Value> Node;
protected:
	Node *_M_clone_node(Node *x);
public:
	Node *rva002D0DA1(Node *x, Node *p);
};

typedef vector<const LocomotorTemplate *, allocator<const LocomotorTemplate *> > BfmeLocomotorTemplateVector;
typedef pair<const LocomotorSetType, BfmeLocomotorTemplateVector> LocomotorMapValue;
typedef _Select1st<LocomotorMapValue> LocomotorMapKeyOf;
typedef less<LocomotorSetType> LocomotorMapCompare;
typedef allocator<LocomotorMapValue> LocomotorMapAlloc;
typedef _Rb_tree<LocomotorSetType, LocomotorMapValue, LocomotorMapKeyOf, LocomotorMapCompare, LocomotorMapAlloc> LocomotorMapTree;

// Retail's two direct calls target 0x002D0B9A. That row is owned by an
// address-derived tree view; use its name without asserting element identity.
typedef pair<const Rva002D0B9AElement, int> CloneOwnerValue;
typedef _Rb_tree<Rva002D0B9AElement, CloneOwnerValue, _Select1st<CloneOwnerValue>, less<Rva002D0B9AElement>, allocator<CloneOwnerValue> > CloneOwnerTree;

// ?rva002D0DA1@?$_Rb_tree@W4LocomotorSetType@@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@U?$_Select1st@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@QAEPAU?$_Rb_tree_node@U?$pair@$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@PAU32@0@Z present-unmatched
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::rva002D0DA1(Node *x, Node *p)
{
	Node *top = (Node *)((CloneOwnerTree *)this)->_M_clone_node((CloneOwnerTree::Node *)x);
	top->m_parent = (_Rb_tree_node_base *)p;
	if (x->m_right != 0)
		top->m_right = (_Rb_tree_node_base *)rva002D0DA1((Node *)x->m_right, top);
	p = top;
	x = (Node *)x->m_left;
	while (x != 0) {
		Node *y = (Node *)((CloneOwnerTree *)this)->_M_clone_node((CloneOwnerTree::Node *)x);
		p->m_left = (_Rb_tree_node_base *)y;
		y->m_parent = (_Rb_tree_node_base *)p;
		if (x->m_right != 0)
			y->m_right = (_Rb_tree_node_base *)rva002D0DA1((Node *)x->m_right, y);
		p = y;
		x = (Node *)x->m_left;
	}
	return top;
}

template LocomotorMapTree::Node *LocomotorMapTree::rva002D0DA1(Node *x, Node *p);

}
