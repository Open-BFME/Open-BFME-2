// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <list>

struct Rva00548267Element { _STL::deque<char> values[1]; bool operator<(const Rva00548267Element&) const; bool operator==(const Rva00548267Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_List_iterator<Rva00548267Element, _STL::_Nonconst_traits<Rva00548267Element> > _STL::list<Rva00548267Element, _STL::allocator<Rva00548267Element> >::erase(_STL::_List_iterator<Rva00548267Element, _STL::_Nonconst_traits<Rva00548267Element> >, _STL::_List_iterator<Rva00548267Element, _STL::_Nonconst_traits<Rva00548267Element> >);
