// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
#include <memory>
#include <string>
#include <vector>
#include <utility>

struct Rva000F4003Element { _STL::auto_ptr<unsigned> value;unsigned word0;Rva000F4003Element(const Rva000F4003Element&b);Rva000F4003Element& operator=(const Rva000F4003Element&b);bool operator<(const Rva000F4003Element&)const;bool operator==(const Rva000F4003Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<Rva000F4003Element, _STL::_Const_traits<Rva000F4003Element> > _STL::set<Rva000F4003Element, _STL::less<Rva000F4003Element>, _STL::allocator<Rva000F4003Element> >::lower_bound(Rva000F4003Element const &) const;
