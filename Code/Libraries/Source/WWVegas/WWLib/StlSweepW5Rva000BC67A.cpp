// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

struct Rva000BC67AElement { Rva000BC67AElement();Rva000BC67AElement(const Rva000BC67AElement&);~Rva000BC67AElement();Rva000BC67AElement&operator=(const Rva000BC67AElement&);char bytes[1]; bool operator<(const Rva000BC67AElement&)const; bool operator==(const Rva000BC67AElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_List_iterator<Rva000BC67AElement, _STL::_Nonconst_traits<Rva000BC67AElement> > _STL::list<Rva000BC67AElement, _STL::allocator<Rva000BC67AElement> >::erase(_STL::_List_iterator<Rva000BC67AElement, _STL::_Nonconst_traits<Rva000BC67AElement> >);
