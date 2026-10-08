// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
#include <list>
#include <memory>

#include "../../../../GameEngine/Include/GameLogic/ContainmentListView.h"
// Instantiate the recovered operations only. Retail's single insertion calls
// the node creator; the forced-inline list shim would emit another body here.
namespace _STL {
// Compare the iterator nodes locally, as in the canonical list provider;
// avoid emitting another externally selected iterator-base wrapper.
template<class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits> &a,
                              const _List_iterator<T, Traits> &b)
{ return a._M_node != b._M_node; }
template<> list<Rva0036ADF9Element>::iterator list<Rva0036ADF9Element>::insert(list<Rva0036ADF9Element>::iterator, const Rva0036ADF9Element &);
template list<Rva0036ADF9Element>::list(const list<Rva0036ADF9Element> &);
template _List_base<Rva0036ADF9Element,allocator<Rva0036ADF9Element> >::~_List_base();
template list<Rva0036ADF9Element>::_Node *list<Rva0036ADF9Element>::_M_create_node(const Rva0036ADF9Element &);
}

// Retail 36AE51 (40B): clear the descriptor's first word before copying
// its source, otherwise copy the existing empty-list sentinel at E0362C.
// The copier's insertion callees establish a four-byte element independently.
extern unsigned g_Va00E0362C;
ContainmentList Rva0036AE51ListView::rva0036AE51()
{
    if (a) {
        a = 0;
        return ContainmentList(*b);
    }
    return ContainmentList(*reinterpret_cast<const ContainmentList *>(&g_Va00E0362C));
}
