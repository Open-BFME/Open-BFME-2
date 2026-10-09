// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT /ICode/GameEngine/Source/Common
// Native526103 push_back is used by the named BuildLocalBuilderList at526421.
// The caller passes one pointer to a builder node; the old polymorphic8B
// Rva00526103Element inference is contradicted by this target evidence.
// Use the established4B Rva00525119 handle shared by sorting/readiness.
// Allocation5258C0 requests12B nodes and copyA9840 copies one word;
// these template folds must be admitted with whole-body relocation proof.
// stlport
#include <list>
#include "Rva00525119.h"
namespace _STL {
template<> class allocator<char> {public:static char *allocate(unsigned int,const void *);};
template<> void _Construct<Rva00525119>(Rva00525119 *,const Rva00525119 &);
template<> __declspec(noinline) _List_node<Rva00525119> *list<Rva00525119,allocator<Rva00525119> >::_M_create_node(const Rva00525119 &x) {
 _List_node<Rva00525119> *p=(_List_node<Rva00525119> *)allocator<char>::allocate(sizeof(_List_node<Rva00525119>),0);
 _Construct(&p->_M_data,x);return p;
}
}
template _STL::list<Rva00525119>::iterator _STL::list<Rva00525119>::insert(iterator,const Rva00525119 &);
template void _STL::list<Rva00525119>::push_back(const Rva00525119 &);
