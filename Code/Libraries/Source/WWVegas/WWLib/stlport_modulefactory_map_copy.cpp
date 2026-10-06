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
	Node *m_header;
	unsigned int m_nodeCount;

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

// Target 0x0029FBC9 is the unsigned-key STLport insertion variant. Its
// 136-byte Ghidra boundary ends in RET 20, including the iterator result
// pointer. Unlike the signed-key body at 0x0041362C, its comparison is JB.
// Both calls reach the independently rowed node creator at 0x0029E11A:
// a 32-byte node, 16 bytes of links and a 16-byte key/value record. The
// application's type name at this call site remains unproved; this address
// name records the variant without assigning it ModuleFactory's _M_insert.
// Algorithm reference: vendor/stlport/stl/_tree.c::_M_insert.
namespace _STL {
template <class T> struct _Rb_global {
    static void _Rebalance(_Rb_tree_node_base *, _Rb_tree_node_base *&);
};
}

struct Rva0029FBC9Iterator
{
    _STL::_Rb_tree_node_base *m_node;
    Rva0029FBC9Iterator(_STL::_Rb_tree_node_base *node) : m_node(node) {}
};

class Rva0029FBC9Tree : public _STL::ModuleFactoryMapTree
{
public:
    Rva0029FBC9Iterator insert(_STL::_Rb_tree_node_base *x,
        _STL::_Rb_tree_node_base *y, const _STL::ModuleFactoryMapValue &value,
        _STL::_Rb_tree_node_base *forceRight);
};

// ?insert@Rva0029FBC9Tree@@QAE?AURva0029FBC9Iterator@@PAU_Rb_tree_node_base@_STL@@0ABU?$pair@$$CBW4NameKeyType@@VModuleTemplate@ModuleFactory@@@4@0@Z
Rva0029FBC9Iterator Rva0029FBC9Tree::insert(_STL::_Rb_tree_node_base *x,
    _STL::_Rb_tree_node_base *y, const _STL::ModuleFactoryMapValue &value,
    _STL::_Rb_tree_node_base *forceRight)
{
    Node *node;
    if (y == m_header || (forceRight == 0 &&
        (x != 0 || (unsigned int)value.first <
            (unsigned int)((Node *)y)->m_value.first))) {
        node = _M_create_node(value);
        y->m_left = node;
        if (y == m_header) {
            m_header->m_parent = node;
            m_header->m_right = node;
        } else if (y == m_header->m_left) {
            m_header->m_left = node;
        }
    } else {
        node = _M_create_node(value);
        y->m_right = node;
        if (y == m_header->m_right)
            m_header->m_right = node;
    }
    node->m_parent = y;
    node->m_left = 0;
    node->m_right = 0;
    _STL::_Rb_global<bool>::_Rebalance(node, m_header->m_parent);
    ++m_nodeCount;
    return Rva0029FBC9Iterator(node);
}
