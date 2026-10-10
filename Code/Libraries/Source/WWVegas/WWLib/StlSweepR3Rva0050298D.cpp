// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva00501656 {  char bytes[1]; };
// Emit only the verified destructor and its required dependencies.
typedef _STL::pair<int const, Rva00501656> Rva0050298DPair;
typedef _STL::_Rb_tree<int, Rva0050298DPair, _STL::_Select1st<Rva0050298DPair>,
 _STL::less<int>, _STL::allocator<Rva0050298DPair> > Rva0050298DTree;
template Rva0050298DTree::~_Rb_tree();
