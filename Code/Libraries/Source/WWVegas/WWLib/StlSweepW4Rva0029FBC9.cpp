// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <string>
#include <utility>

struct Rva0029FBC9Element { char bytes[12]; Rva0029FBC9Element();Rva0029FBC9Element(const Rva0029FBC9Element&);~Rva0029FBC9Element();Rva0029FBC9Element& operator=(const Rva0029FBC9Element&); };

// Native creator 0029E11A allocates 32 bytes: 16 node-link bytes and
// a four-byte key plus 12-byte value. Its copy call reaches 0041360E,
// also rowed by the existing formation-preview pair specialization.
#include "../../../../GameEngine/Include/Common/Rva002A147EElement.h"
typedef _STL::pair<const unsigned,Rva002A147EElement> PreviewValue;
typedef _STL::_Rb_tree<unsigned,PreviewValue,_STL::_Select1st<PreviewValue>,_STL::less<unsigned>,_STL::allocator<PreviewValue> > PreviewTree;
typedef _STL::pair<void*const,Rva0029FBC9Element> OpaqueValue;
typedef _STL::_Rb_tree<void*,OpaqueValue,_STL::_Select1st<OpaqueValue>,_STL::less<void*>,_STL::allocator<OpaqueValue> > OpaqueTree;
namespace _STL {
template<> PreviewTree::_Link_type PreviewTree::_M_create_node(const PreviewValue&);
}
// Expose the existing protected worker without adding an implementation.
struct PreviewTreeProvider : PreviewTree { using PreviewTree::_M_create_node; };
namespace _STL {
template<> __declspec(dllimport) __forceinline OpaqueTree::_Link_type OpaqueTree::_M_create_node(const OpaqueValue&v)
{ return (_Link_type)((PreviewTreeProvider*)this)->_M_create_node(reinterpret_cast<const PreviewValue&>(v)); }
}

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<void *const, Rva0029FBC9Element>, _STL::_Nonconst_traits<_STL::pair<void *const, Rva0029FBC9Element> > > _STL::_Rb_tree<void *, _STL::pair<void *const, Rva0029FBC9Element>, _STL::_Select1st<_STL::pair<void *const, Rva0029FBC9Element> >, _STL::less<void *>, _STL::allocator<_STL::pair<void *const, Rva0029FBC9Element> > >::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, _STL::pair<void *const, Rva0029FBC9Element> const &, _STL::_Rb_tree_node_base *);
