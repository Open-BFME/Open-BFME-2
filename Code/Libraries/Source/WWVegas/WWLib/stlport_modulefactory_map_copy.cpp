// cl: /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// ?_M_clone_node@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@PAU32@@Z,
// retail 0x00413E55, 30 bytes. Dedicated TU.
//
// ?_M_copy@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@PAU32@0@Z,
// retail 0x004136B4, 115 bytes. Same TU.
//
// ModuleFactory::ModuleTemplateMap red-black tree copy (STLport _M_copy shape:
// clone the top, link the parent, recurse right, then walk down the left spine
// cloning). The clone helper calls the rowed _M_create_node 0x0029E11A, then
// copies the color byte and clears left/right. No EH in retail (malloc
// allocator, nothrow), hence /GX-. Evidence: clone 0x00413E55 is 30B with all
// callees rowed; copy 0x004136B4 is a gap between two ModuleFactory.cpp rows
// and calls only the clone plus itself.

enum NameKeyType
{
	NAMEKEY_0 = 0
};

class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		void *m_createProc;
		void *m_createDataProc;
		int m_whichInterfaces;
	};
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

protected:
	Node *_M_clone_node(Node *x);
	Node *_M_create_node(const Value &x);

private:
	Node *_M_copy(Node *x, Node *p);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_clone_node(Node *x)
{
	Node *top = _M_create_node(x->m_value);
	top->m_color = x->m_color;
	top->m_left = 0;
	top->m_right = 0;
	return top;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_copy(Node *x, Node *p)
{
	Node *top = _M_clone_node(x);
	top->m_parent = (_Rb_tree_node_base *)p;
	if (x->m_right != 0)
		top->m_right = (_Rb_tree_node_base *)_M_copy((Node *)x->m_right, top);
	p = top;
	x = (Node *)x->m_left;
	while (x != 0) {
		Node *y = _M_clone_node(x);
		p->m_left = (_Rb_tree_node_base *)y;
		y->m_parent = (_Rb_tree_node_base *)p;
		if (x->m_right != 0)
			y->m_right = (_Rb_tree_node_base *)_M_copy((Node *)x->m_right, y);
		p = y;
		x = (Node *)x->m_left;
	}
	return top;
}

typedef pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleFactoryMapValue;
typedef _Select1st<ModuleFactoryMapValue> ModuleFactoryMapKeyOf;
typedef less<NameKeyType> ModuleFactoryMapCompare;
typedef allocator<ModuleFactoryMapValue> ModuleFactoryMapAlloc;
typedef _Rb_tree<NameKeyType, ModuleFactoryMapValue, ModuleFactoryMapKeyOf, ModuleFactoryMapCompare, ModuleFactoryMapAlloc> ModuleFactoryMapTree;

template ModuleFactoryMapTree::Node *ModuleFactoryMapTree::_M_clone_node(Node *x);
template ModuleFactoryMapTree::Node *ModuleFactoryMapTree::_M_copy(Node *x, Node *p);

}
