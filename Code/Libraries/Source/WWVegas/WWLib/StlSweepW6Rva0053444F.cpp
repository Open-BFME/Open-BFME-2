// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
#include <memory>

struct Rva0053444FElement { unsigned prefix[2];int key;bool operator<(const Rva0053444FElement&b)const {return key<b.key;}bool operator==(const Rva0053444FElement&b)const {return key==b.key;} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_node<Rva0053444FElement> * _STL::_Rb_tree<Rva0053444FElement, Rva0053444FElement, _STL::_Identity<Rva0053444FElement>, _STL::less<Rva0053444FElement>, _STL::allocator<Rva0053444FElement> >::_M_clone_node(_STL::_Rb_tree_node<Rva0053444FElement> *);
