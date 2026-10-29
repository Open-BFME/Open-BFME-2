// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The two out-of-line callees of the map destructor 0x002F0BB5
// (StlSweepW4Rva002F0BB5.cpp) for _Rb_tree<int, pair<const int, Rva002F0BB5Element>>:
// ?clear@...@QAEXXZ, retail 0x002EEA1D, 41 bytes: STLport 4.5.3's clear()
//   (vendor/stlport/stl/_tree.h:468); its _M_erase 0x002EB46E is rowed as
//   Rva002EB46E::rva002EB46E (Rva002EB46ERelease.cpp) and is called by that name.
// ??1?$_Rb_tree_base@...@QAE@XZ, retail 0x002EEA46, 20 bytes: ~_Rb_tree_base()
//   (_tree.h:230), whose node deallocate pushes the header onto the free-node
//   list of the shared pool g_Va00DBD4C8.
// Formerly rowed as Rva002EB46E::rva002EEA1D / rva002EEA46 (same bodies); twin of
// Rva002EE9E0Reset.cpp.
#include <map>

struct Rva002F0BB5Element { char bytes[1]; bool operator<(const Rva002F0BB5Element&)const; bool operator==(const Rva002F0BB5Element&)const; };

typedef _STL::pair<const int, Rva002F0BB5Element> _Rva002F0BB5Pair;
typedef _STL::allocator<_Rva002F0BB5Pair> _Rva002F0BB5Alloc;
typedef _STL::_Rb_tree<int, _Rva002F0BB5Pair, _STL::_Select1st<_Rva002F0BB5Pair>, _STL::less<int>, _Rva002F0BB5Alloc > _Rva002F0BB5Tree;
typedef _STL::_Rb_tree_base<_Rva002F0BB5Pair, _Rva002F0BB5Alloc > _Rva002F0BB5Base;

struct _Rva002EB46ENode
{
public:
	void *_m_link; // +0x00
	int _m_unk4; // +0x04
	_Rva002EB46ENode *_m_next; // +0x08
	_Rva002EB46ENode *_m_child; // +0x0C
};
// Native DBD4D0 is the shared pool's free-node field at +8.
#include "../../../../GameEngine/Include/Common/Rva002E8548Pool.h"
struct Rva002EB46E {
    void rva002EB46E(_Rva002EB46ENode *p);
};

namespace _STL {
template <> void _Rva002F0BB5Tree::clear()
{
    if (_M_node_count != 0) {
        ((Rva002EB46E *)this)->rva002EB46E((_Rva002EB46ENode *)_M_root());
        _M_leftmost() = this->_M_header._M_data;
        _M_root() = 0;
        _M_rightmost() = this->_M_header._M_data;
        _M_node_count = 0;
    }
}

template <> _Rva002F0BB5Base::~_Rb_tree_base() throw()
{
    _Rva002EB46ENode *head = (_Rva002EB46ENode *)this->_M_header._M_data;
    if (!head)
        return;
    head->_m_link = g_Va00DBD4C8.m_head;
    g_Va00DBD4C8.m_head = head;
}
}

// cl 7.1 treats the specializations like their in-class inline primaries and
// drops them unreferenced; instantiate them so the map destructor's calls resolve.
template void _Rva002F0BB5Tree::clear();
template _Rva002F0BB5Base::~_Rb_tree_base();
