// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>

struct Rva0054D71BElement { double words[1];bool operator<(const Rva0054D71BElement&)const;bool operator==(const Rva0054D71BElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva0054D71BElement, _STL::allocator<Rva0054D71BElement> >::_M_insert_dispatch<_STL::_List_iterator<Rva0054D71BElement, _STL::_Const_traits<Rva0054D71BElement> > >(_STL::_List_iterator<Rva0054D71BElement, _STL::_Nonconst_traits<Rva0054D71BElement> >, _STL::_List_iterator<Rva0054D71BElement, _STL::_Const_traits<Rva0054D71BElement> >, _STL::_List_iterator<Rva0054D71BElement, _STL::_Const_traits<Rva0054D71BElement> >, _STL::__false_type const &);
