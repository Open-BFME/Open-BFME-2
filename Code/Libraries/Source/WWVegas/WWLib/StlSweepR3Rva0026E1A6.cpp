// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <vector>



// Retail's value destructor (0x000796BC, the pair destructor ICF-folded with
// the locomotor-set and science-vector maps) frees one vector buffer at +4:
// the mapped value is a vector of trivially destructible elements.
struct Rva0026E1A6Record { _STL::vector<const void *> items; };
typedef _STL::pair<const int,Rva0026E1A6Record> Rva0026E1A6Pair;
typedef _STL::_Rb_tree<int,Rva0026E1A6Pair,_STL::_Select1st<Rva0026E1A6Pair>,_STL::less<int>,_STL::allocator<Rva0026E1A6Pair> > Rva0026E1A6Tree;
// Emit only the owned destructor and its dependencies.
template Rva0026E1A6Tree::~_Rb_tree();

// Native0026E1F75B tail-forwards unchanged ECX to the owned56B tree
// destructor0026E1A6; original wrapper owner/name/lifetime role unknown.
struct LocomotorMapView { Rva0026E1A6Tree tree; ~LocomotorMapView(); };
LocomotorMapView::~LocomotorMapView() {}
