// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 insertion for the evidenced four-byte containment element.
// Retail5925E2 calls the recovered29B node creatorB6447, then links its
// next/previous pointers and returns the iterator through the hidden result.
// Keep the node creator in its verified provider instead of inlining it here.
#include "../../../../GameEngine/Include/GameLogic/ContainmentListView.h"
namespace _STL {
template<> list<Rva0036ADF9Element>::_Node *list<Rva0036ADF9Element>::_M_create_node(const Rva0036ADF9Element &);
template list<Rva0036ADF9Element>::iterator list<Rva0036ADF9Element>::insert(list<Rva0036ADF9Element>::iterator, const Rva0036ADF9Element &);
}
