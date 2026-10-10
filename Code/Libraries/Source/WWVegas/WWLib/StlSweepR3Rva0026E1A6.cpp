// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva0026E1A6Record {  char bytes[1]; };
typedef _STL::pair<const int,Rva0026E1A6Record> Rva0026E1A6Pair;
typedef _STL::_Rb_tree<int,Rva0026E1A6Pair,_STL::_Select1st<Rva0026E1A6Pair>,_STL::less<int>,_STL::allocator<Rva0026E1A6Pair> > Rva0026E1A6Tree;
// Emit only the owned destructor and its dependencies.
template Rva0026E1A6Tree::~_Rb_tree();

// Native0026E1F75B tail-forwards unchanged ECX to the owned56B tree
// destructor0026E1A6; original wrapper owner/name/lifetime role unknown.
struct Rva0026E1F7TreeCleanupForward {void cleanup();};
void Rva0026E1F7TreeCleanupForward::cleanup() {reinterpret_cast<Rva0026E1A6Tree*>(this)->~Rva0026E1A6Tree();}
