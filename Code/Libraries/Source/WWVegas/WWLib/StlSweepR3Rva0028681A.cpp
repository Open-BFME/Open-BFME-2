// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva0028681ARecord {  char bytes[1]; };
typedef _STL::pair<const int,Rva0028681ARecord> Rva0028681APair;
typedef _STL::_Rb_tree<int,Rva0028681APair,_STL::_Select1st<Rva0028681APair>,_STL::less<int>,_STL::allocator<Rva0028681APair> > Rva0028681ATree;
// Emit only the owned destructor and its dependencies.
template Rva0028681ATree::~_Rb_tree();

// Native0028691C5B tail-forwards unchanged ECX to the owned56B tree
// destructor0028681A; original wrapper owner/name/lifetime role unknown.
struct Rva0028691CTreeCleanupForward {void cleanup();};
void Rva0028691CTreeCleanupForward::cleanup() {reinterpret_cast<Rva0028681ATree*>(this)->~Rva0028681ATree();}
