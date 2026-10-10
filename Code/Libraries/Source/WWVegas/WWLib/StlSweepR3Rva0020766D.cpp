// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva0020766DRecord {  char bytes[1]; };
// Emit the recovered destructor without unrelated whole-map members.
typedef _STL::pair<int const, Rva0020766DRecord> Rva0020766DPair;
typedef _STL::_Rb_tree<int, Rva0020766DPair, _STL::_Select1st<Rva0020766DPair>,
 _STL::less<int>, _STL::allocator<Rva0020766DPair> > Rva0020766DTree;
template Rva0020766DTree::~_Rb_tree();
