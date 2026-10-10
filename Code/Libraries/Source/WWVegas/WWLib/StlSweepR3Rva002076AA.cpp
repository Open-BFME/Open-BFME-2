// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva002076AARecord {  char bytes[1]; };
// Emit the recovered destructor without unrelated whole-map members.
typedef _STL::pair<int const, Rva002076AARecord> Rva002076AAPair;
typedef _STL::_Rb_tree<int, Rva002076AAPair, _STL::_Select1st<Rva002076AAPair>,
 _STL::less<int>, _STL::allocator<Rva002076AAPair> > Rva002076AATree;
template Rva002076AATree::~_Rb_tree();
