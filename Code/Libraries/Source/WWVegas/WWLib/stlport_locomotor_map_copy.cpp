// cl: /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// ?_M_copy@?$_Rb_tree@W4LocomotorSetType@@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@U?$_Select1st@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@U?$less@W4LocomotorSetType@@@3@V?$allocator@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@3@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@@2@PAU32@0@Z
// 115B @0x004FFD09: LocomotorSetType to template-vector map red-black tree
// copy. Same 115B _M_copy shape as the rowed map<int int> copy 0x002CF6CF
// and ModuleFactory copy 0x004136B4: clone the top via the opaque thiscall
// twin of the rowed int-int clone 0x0053444F (header-only wrapper identical
// across types) link the parent recurse right then walk the left spine.
// Self recursion resolves through the existing pin. No EH in retail
// hence /GX-.

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

struct Rva004FFD09Node
{
	char m_color;
	char m_pad[3];
	Rva004FFD09Node *m_parent;
	Rva004FFD09Node *m_left;
	Rva004FFD09Node *m_right;
};

class Rva004FFD09
{
public:
	Rva004FFD09Node *rva0053444F(Rva004FFD09Node *x);
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
private:
	Node *_M_copy(Node *x, Node *p);
};

typedef vector<const LocomotorTemplate *, allocator<const LocomotorTemplate *> > BfmeLocomotorTemplateVector;
typedef pair<const LocomotorSetType, BfmeLocomotorTemplateVector> LocomotorMapValue;
typedef _Select1st<LocomotorMapValue> LocomotorMapKeyOf;
typedef less<LocomotorSetType> LocomotorMapCompare;
typedef allocator<LocomotorMapValue> LocomotorMapAlloc;
typedef _Rb_tree<LocomotorSetType, LocomotorMapValue, LocomotorMapKeyOf, LocomotorMapCompare, LocomotorMapAlloc> LocomotorMapTree;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_copy(Node *x, Node *p)
{
	Rva004FFD09 *cloneThis = (Rva004FFD09 *)this;
	Node *top = (Node *)(cloneThis->rva0053444F((Rva004FFD09Node *)x));
	top->m_parent = (_Rb_tree_node_base *)p;
	if (x->m_right != 0)
		top->m_right = (_Rb_tree_node_base *)_M_copy((Node *)x->m_right, top);
	p = top;
	x = (Node *)x->m_left;
	while (x != 0) {
		Node *y = (Node *)(cloneThis->rva0053444F((Rva004FFD09Node *)x));
		p->m_left = (_Rb_tree_node_base *)y;
		y->m_parent = (_Rb_tree_node_base *)p;
		if (x->m_right != 0)
			y->m_right = (_Rb_tree_node_base *)_M_copy((Node *)x->m_right, y);
		p = y;
		x = (Node *)x->m_left;
	}
	return top;
}

template LocomotorMapTree::Node *LocomotorMapTree::_M_copy(Node *x, Node *p);

}
