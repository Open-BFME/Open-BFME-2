// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??4Rva002B5558@@QAEAAV0@ABV0@@Z @0x002B62DE 115B
// Copy assignment for the Rva002B5558 Head/count family: self-check then
// rowed clear 0x002B5558 then map<int int> tree copy via rowed _M_copy
// 0x002B61FB with leftmost/rightmost fixup and count copy.
// Evidence: calls 0x002B5558 and 0x002B61FB; callers 0x002B73A2 0x002B8293;
// prev 0x002B62A6 dtor; same Head layout as Rva002B5558.cpp.
class Rva002B5558;
#define private friend class ::Rva002B5558; private
#define _M_copy _M_copy_002B61FB
#include <map>
#undef private

// Declared only: suppress generic instantiation so the gate resolves the
// call through the rowed 0x002B61FB body (no local emission).
template <>
_STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::_Link_type _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::_M_copy(_Link_type, _Link_type);

extern "C" void __cdecl free(void *block);

struct Node002B43BA
{
	char m_pad[8];
	Node002B43BA *m_next8;
	Node002B43BA *m_childC;
};

struct Head002B5558
{
	int m_pad0;
	Node002B43BA *m_node4;
	Head002B5558 *m_next8;
	Head002B5558 *m_prevC;
};

typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > MapIntIntTree002B62DE;

class Rva002B5558
{
	Head002B5558 *m_head0;
	int m_count4;
public:
	void rva002B5558();
	Rva002B5558 &operator=(const Rva002B5558 &other);
};

// ?rva002B5558@Rva002B5558@@QAEXXZ @0x002B5558 rowed in Rva002B5558.cpp
// ?_M_copy_002B61FB@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z @0x002B61FB rowed
Rva002B5558 &Rva002B5558::operator=(const Rva002B5558 &other)
{
	if (this == &other)
		return *this;
	rva002B5558();
	m_count4 = 0;
	Node002B43BA *otherRoot = (Node002B43BA *)other.m_head0->m_node4;
	if (otherRoot == 0)
	{
		m_head0->m_node4 = 0;
		m_head0->m_next8 = m_head0;
		m_head0->m_prevC = m_head0;
	}
	else
	{
		MapIntIntTree002B62DE *tree = (MapIntIntTree002B62DE *)this;
		Head002B5558 *header = m_head0;
		Node002B43BA *copyRoot = (Node002B43BA *)tree->_M_copy((MapIntIntTree002B62DE::_Link_type)otherRoot, (MapIntIntTree002B62DE::_Link_type)header);
		header->m_node4 = (Node002B43BA *)copyRoot;
		Node002B43BA *node = (Node002B43BA *)m_head0->m_node4;
		while (node->m_next8 != 0)
			node = node->m_next8;
		m_head0->m_next8 = (Head002B5558 *)node;
		node = (Node002B43BA *)m_head0->m_node4;
		while (node->m_childC != 0)
			node = node->m_childC;
		m_head0->m_prevC = (Head002B5558 *)node;
		m_count4 = other.m_count4;
	}
	return *this;
}
#undef _M_copy
