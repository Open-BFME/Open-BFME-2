// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>

struct Rva0035CC18Element { double words[1];bool operator<(const Rva0035CC18Element&)const;bool operator==(const Rva0035CC18Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva0035CC18Element, _STL::allocator<Rva0035CC18Element> >::insert<_STL::_List_iterator<Rva0035CC18Element, _STL::_Const_traits<Rva0035CC18Element> > >(_STL::_List_iterator<Rva0035CC18Element, _STL::_Nonconst_traits<Rva0035CC18Element> >, _STL::_List_iterator<Rva0035CC18Element, _STL::_Const_traits<Rva0035CC18Element> >, _STL::_List_iterator<Rva0035CC18Element, _STL::_Const_traits<Rva0035CC18Element> >);
