// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>



struct Rva004DA149Record {  char bytes[1]; };
typedef _STL::pair<const int,Rva004DA149Record> Rva004DA149Pair;
typedef _STL::_Rb_tree<int,Rva004DA149Pair,_STL::_Select1st<Rva004DA149Pair>,_STL::less<int>,_STL::allocator<Rva004DA149Pair> > Rva004DA149Tree;
// Restrict emission to the owned destructor and its dependencies.
template Rva004DA149Tree::~_Rb_tree();

// Native004DA2EA..004DA2EF5B unchanged-receiver cleanup forwarder to the
// owned tree destructor004DA149; original wrapper owner/name unknown.
// Earlier vector-insert and uninitialized-copy queue names were refuted.
struct Rva004DA2EATreeCleanupForward { void cleanup(); };
void Rva004DA2EATreeCleanupForward::cleanup() {
    reinterpret_cast<Rva004DA149Tree *>(this)->~Rva004DA149Tree();
}
