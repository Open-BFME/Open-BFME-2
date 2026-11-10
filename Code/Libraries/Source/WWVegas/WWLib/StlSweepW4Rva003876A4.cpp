// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <set>
#include "../../../../GameEngine/Include/Common/Rva0038768DData.h"
void Rva0038768DCopy(Rva0038768DData *, const Rva0038768DData *);

struct Rva003876A4Element
{
    Rva0038768DData m_data;
};
bool operator<(const Rva003876A4Element &, const Rva003876A4Element &);

namespace _STL {
typedef _Rb_tree<Rva003876A4Element, Rva003876A4Element,
    _Identity<Rva003876A4Element>, less<Rva003876A4Element>,
    allocator<Rva003876A4Element> > StatsTree;
typedef _Rb_tree_node<Rva003876A4Element> StatsNode;

// The native node creator copies the byte and dword through the shared worker.
// ?<_Rb_tree::_M_create_node> present-unmatched
template <> __declspec(noinline) inline StatsNode *
StatsTree::_M_create_node(const Rva003876A4Element &value)
{
    StatsNode *node = (StatsNode *)allocator<char>::allocate(sizeof(StatsNode), 0);
    Rva0038768DCopy(&node->_M_value_field.m_data, &value.m_data);
    return node;
}

template <> __forceinline StatsNode *StatsTree::_M_clone_node(StatsNode *source)
{
    StatsNode *node = _M_create_node(source->_M_value_field);
    node->_M_color = source->_M_color;
    node->_M_left = 0;
    node->_M_right = 0;
    return node;
}
}

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree<Rva003876A4Element, Rva003876A4Element, _STL::_Identity<Rva003876A4Element>, _STL::less<Rva003876A4Element>, _STL::allocator<Rva003876A4Element> > & _STL::_Rb_tree<Rva003876A4Element, Rva003876A4Element, _STL::_Identity<Rva003876A4Element>, _STL::less<Rva003876A4Element>, _STL::allocator<Rva003876A4Element> >::operator=(_STL::_Rb_tree<Rva003876A4Element, Rva003876A4Element, _STL::_Identity<Rva003876A4Element>, _STL::less<Rva003876A4Element>, _STL::allocator<Rva003876A4Element> > const &);
