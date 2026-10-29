// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The two out-of-line callees of the map destructor 0x002F0B8A
// (StlSweepW4Rva002F0B8A.cpp) for _Rb_tree<int, pair<const int, Rva002F0B8AElement>>:
// ?clear@...@QAEXXZ, retail 0x002EE9E0, 41 bytes: STLport 4.5.3's clear()
//   (vendor/stlport/stl/_tree.h:468); its _M_erase 0x002EB416 is rowed as
//   Rva002EB416::rva002EB416 (Rva002EB416Release.cpp) and is called by that name.
// ??1?$_Rb_tree_base@...@QAE@XZ, retail 0x002EEA09, 20 bytes: ~_Rb_tree_base()
//   (_tree.h:230), whose node deallocate pushes the header onto the release list.
// Formerly rowed as Rva002EB416::rva002EE9E0 / rva002EEA09 (same bodies).
#include <map>

struct Rva002F0B8AElement { char bytes[1]; bool operator<(const Rva002F0B8AElement&)const; bool operator==(const Rva002F0B8AElement&)const; };

typedef _STL::pair<const int, Rva002F0B8AElement> _Rva002F0B8APair;
typedef _STL::allocator<_Rva002F0B8APair> _Rva002F0B8AAlloc;
typedef _STL::_Rb_tree<int, _Rva002F0B8APair, _STL::_Select1st<_Rva002F0B8APair>, _STL::less<int>, _Rva002F0B8AAlloc > _Rva002F0B8ATree;
typedef _STL::_Rb_tree_base<_Rva002F0B8APair, _Rva002F0B8AAlloc > _Rva002F0B8ABase;

struct _Rva002EB416Node
{
public:
	void *_m_link; // +0x00
	int _m_unk4; // +0x04
	_Rva002EB416Node *_m_next; // +0x08
	_Rva002EB416Node *_m_child; // +0x0C
};
// g_Va00DBD4B8: VA 0x00dbd4b8 (.data); retail initial bytes 00 00 00 00.
_Rva002EB416Node *g_Va00DBD4B8;
struct Rva002EB416 {
    void rva002EB416(_Rva002EB416Node *p);
};

namespace _STL {
template <> void _Rva002F0B8ATree::clear()
{
    if (_M_node_count != 0) {
        ((Rva002EB416 *)this)->rva002EB416((_Rva002EB416Node *)_M_root());
        _M_leftmost() = this->_M_header._M_data;
        _M_root() = 0;
        _M_rightmost() = this->_M_header._M_data;
        _M_node_count = 0;
    }
}

template <> _Rva002F0B8ABase::~_Rb_tree_base() throw()
{
    _Rva002EB416Node *head = (_Rva002EB416Node *)this->_M_header._M_data;
    if (!head)
        return;
    head->_m_link = g_Va00DBD4B8;
    g_Va00DBD4B8 = head;
}
}

// cl 7.1 treats the specializations like their in-class inline primaries and
// drops them unreferenced; instantiate them so the map destructor's calls resolve.
template void _Rva002F0B8ATree::clear();
template _Rva002F0B8ABase::~_Rb_tree_base();
