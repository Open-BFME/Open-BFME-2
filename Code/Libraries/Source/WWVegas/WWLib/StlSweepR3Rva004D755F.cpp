// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva004D755FRecord {  char bytes[1]; };
typedef _STL::pair<const int,Rva004D755FRecord> Rva004D755FPair;
typedef _STL::_Rb_tree<int,Rva004D755FPair,_STL::_Select1st<Rva004D755FPair>,_STL::less<int>,_STL::allocator<Rva004D755FPair> > Rva004D755FTree;
template Rva004D755FTree::~_Rb_tree();

// Emit only the owned destructor and its dependencies, rather than the
// unused map operations that introduce four competing shared COMDATs.
// Native004D7597..004D759C5B tail-forwards unchanged ECX to the owned
// tree destructor004D755F. Original wrapper owner and name remain unknown.
struct Rva004D7597TreeCleanupForward { void cleanup(); };
void Rva004D7597TreeCleanupForward::cleanup() {
    reinterpret_cast<Rva004D755FTree *>(this)->~Rva004D755FTree();
}
