// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva002075F3Record {  char bytes[1]; };
// Emit the recovered destructor without unrelated whole-map members.
typedef _STL::pair<int const, Rva002075F3Record> Rva002075F3Pair;
typedef _STL::_Rb_tree<int, Rva002075F3Pair, _STL::_Select1st<Rva002075F3Pair>,
 _STL::less<int>, _STL::allocator<Rva002075F3Pair> > Rva002075F3Tree;
template Rva002075F3Tree::~_Rb_tree();
