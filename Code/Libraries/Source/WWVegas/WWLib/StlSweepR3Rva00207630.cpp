// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva00207630Record {  char bytes[1]; };
// Emit the recovered destructor without unrelated whole-map members.
typedef _STL::pair<int const, Rva00207630Record> Rva00207630Pair;
typedef _STL::_Rb_tree<int, Rva00207630Pair, _STL::_Select1st<Rva00207630Pair>,
 _STL::less<int>, _STL::allocator<Rva00207630Pair> > Rva00207630Tree;
template Rva00207630Tree::~_Rb_tree();
