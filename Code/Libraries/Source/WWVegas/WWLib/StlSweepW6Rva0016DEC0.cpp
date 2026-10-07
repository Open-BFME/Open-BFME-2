// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O2 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
#include <memory>
#include <string>
#include <vector>
#include <utility>

struct Rva0016DEC0Element { _STL::pair<_STL::string,unsigned> value;unsigned word0;bool operator<(const Rva0016DEC0Element&)const;bool operator==(const Rva0016DEC0Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<Rva0016DEC0Element, _STL::_Const_traits<Rva0016DEC0Element> > _STL::set<Rva0016DEC0Element, _STL::less<Rva0016DEC0Element>, _STL::allocator<Rva0016DEC0Element> >::lower_bound(Rva0016DEC0Element const &) const;
