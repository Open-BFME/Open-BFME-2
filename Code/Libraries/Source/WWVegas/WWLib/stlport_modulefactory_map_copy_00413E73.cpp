// cl: /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
//
// ?_M_copy_00413E73@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@3@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@_STL@@@2@PAU32@0@Z,
// retail 0x00413E73, 115 bytes. Dedicated TU.
//
// ModuleFactory::ModuleTemplateMap red-black tree copy duplicate (STLport _M_copy shape:
// clone the top, link the parent, recurse right, then walk down the left spine
// cloning). Retail calls the rowed clone 0x00413E55 and itself, identical to the
// rowed copy 0x004136B4 modulo relocations; address-scoped spelling follows the
// fleet _M_copy_006008E6 precedent since the unsuffixed name is claimed by
// 0x004136B4. No EH in retail (malloc allocator, nothrow), hence /GX-.
// Evidence: clone 0x00413E55 is 30B rowed; copy 0x00413E73 sits directly after
// it and is called by 0x00413EE6; left-spine loop with right recursion.

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

private:
	Node *_M_copy_00413E73(Node *x, Node *p);
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename _Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::Node *
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_M_copy_00413E73(Node *x, Node *p)
{
	Node *top = _M_clone_node(x);
	top->m_parent = (_Rb_tree_node_base *)p;
	if (x->m_right != 0)
		top->m_right = (_Rb_tree_node_base *)_M_copy_00413E73((Node *)x->m_right, top);
	p = top;
	x = (Node *)x->m_left;
	while (x != 0) {
		Node *y = _M_clone_node(x);
		p->m_left = (_Rb_tree_node_base *)y;
		y->m_parent = (_Rb_tree_node_base *)p;
		if (x->m_right != 0)
			y->m_right = (_Rb_tree_node_base *)_M_copy_00413E73((Node *)x->m_right, y);
		p = y;
		x = (Node *)x->m_left;
	}
	return top;
}

typedef pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleFactoryMapValue00413E73;
typedef _Select1st<ModuleFactoryMapValue00413E73> ModuleFactoryMapKeyOf00413E73;
typedef less<NameKeyType> ModuleFactoryMapCompare00413E73;
typedef allocator<ModuleFactoryMapValue00413E73> ModuleFactoryMapAlloc00413E73;
typedef _Rb_tree<NameKeyType, ModuleFactoryMapValue00413E73, ModuleFactoryMapKeyOf00413E73, ModuleFactoryMapCompare00413E73, ModuleFactoryMapAlloc00413E73> ModuleFactoryMapTree00413E73;

template ModuleFactoryMapTree00413E73::Node *ModuleFactoryMapTree00413E73::_M_copy_00413E73(Node *x, Node *p);

}
