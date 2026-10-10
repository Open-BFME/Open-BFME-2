// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

struct Rva001FF743Element { char bytes[1]; bool operator<(const Rva001FF743Element&)const; bool operator==(const Rva001FF743Element&)const; };
// Emit only the verified destructor and its required dependencies.
typedef _STL::pair<int const, Rva001FF743Element> Rva001FF743Pair;
typedef _STL::_Rb_tree<int, Rva001FF743Pair, _STL::_Select1st<Rva001FF743Pair>,
 _STL::less<int>, _STL::allocator<Rva001FF743Pair> > Rva001FF743Tree;
template Rva001FF743Tree::~_Rb_tree();
