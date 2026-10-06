// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>

struct Rva0052223EElement { double words[1];bool operator<(const Rva0052223EElement&)const;bool operator==(const Rva0052223EElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_List_iterator<Rva0052223EElement, _STL::_Nonconst_traits<Rva0052223EElement> > _STL::list<Rva0052223EElement, _STL::allocator<Rva0052223EElement> >::erase(_STL::_List_iterator<Rva0052223EElement, _STL::_Nonconst_traits<Rva0052223EElement> >, _STL::_List_iterator<Rva0052223EElement, _STL::_Nonconst_traits<Rva0052223EElement> >);
