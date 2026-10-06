// cl: /MD
//
// ?rva002B6900@Rva002B6900@@QAEXXZ @0x002B6900 63B
// Clear over the +0x130 map/list family: iterate RB nodes via rowed
// _M_increment 0x00024250, destroy each node+0x14 payload through its
// slot-0 virtual (arg 0) then rowed operator delete 0x0002FD60, then
// tail-jmp to rowed clear 0x002B54F9 for the +0x130 member.
// Evidence: calls 0x0002FD60 0x00024250 0x002B54F9; callers 0x002B8434
// 0x002B96C3 0x002B993A 0x002B9D2A 0x002BD277; same +0x130 header shape
// as Rva002B5C5EMapFind.cpp (node+0x14 value pointer).
namespace _STL
{
struct _Rb_tree_node_base
{
	bool _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class D> class _Rb_global
{
public:
	static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);
};
}

void __cdecl operator delete(void *block);

struct Node002B4360
{
	char m_pad[8];
	Node002B4360 *m_next8;
	Node002B4360 *m_childC;
};

struct Head002B54F9
{
	int m_pad0;
	Node002B4360 *m_node4;
	Head002B54F9 *m_next8;
	Head002B54F9 *m_prevC;
};

class Rva002B54F9
{
	Head002B54F9 *m_head0;
	int m_count4;
public:
	void rva002B54F9();
};

struct Val002B6900
{
	virtual void *virt0(int arg);
};

class Rva002B6900
{
	char m_pad[0x130];
	Rva002B54F9 m_map130;
public:
	void rva002B6900();
};

// ?rva002B54F9@Rva002B54F9@@QAEXXZ @0x002B54F9 rowed in Rva002B54F9.cpp
// ?_M_increment@?$_Rb_global@_N@_STL@@SAPAU_Rb_tree_node_base@2@PAU32@@Z @0x00024250 rowed
// ??3@YAXPAX@Z @0x0002FD60 rowed in mem_ops.cpp
void Rva002B6900::rva002B6900()
{
	_STL::_Rb_tree_node_base *header = *( _STL::_Rb_tree_node_base **)((char *)this + 0x130);
	_STL::_Rb_tree_node_base *node = header->_M_left;
	while (node != header)
	{
		Val002B6900 *val = *(Val002B6900 **)((char *)node + 0x14);
		void *p;
		if (val != 0)
			p = val->virt0(0);
		else
			p = 0;
		::operator delete(p);
		node = _STL::_Rb_global<bool>::_M_increment(node);
	}
	m_map130.rva002B54F9();
}
