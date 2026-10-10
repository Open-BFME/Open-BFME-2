// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// Native2EF239..2EF25B is the twin of2EF25B: its pool is DBD4B0.
// Existing int-key insertion2F0D4E and its Rva002F1DA1Mapped value
// establish the eight-byte value. The local int-pair construction view
// is proven against every byte of the shared60C9D9 copy, not inferred
// merely from a pin. No new pin, layout or storage owner is introduced.
#include <map>
#include <memory>
class Rva002EB448 { public: void *rva002EB448(); };
#include "../../../../GameEngine/Include/Common/Rva002E8548Pool.h"
extern Rva002E8548 g_IntKeyedTreeNodePool;
struct Rva002F1DA1Mapped { int a; };
typedef _STL::pair<const int,Rva002F1DA1Mapped> Value2EF239;
typedef _STL::pair<const int,int> Copy2EF239;
namespace _STL {
template<> __declspec(noinline) void _Construct<Copy2EF239,Copy2EF239>(Copy2EF239 *,const Copy2EF239 &);
}
typedef _STL::_Rb_tree<int,Value2EF239,_STL::_Select1st<Value2EF239>,_STL::less<int>,_STL::allocator<Value2EF239> > Tree2EF239;
namespace _STL {
template<> Tree2EF239::_Link_type Tree2EF239::_M_create_node(const Value2EF239 &value) {
 void *raw=reinterpret_cast<Rva002EB448 *>(&g_IntKeyedTreeNodePool)->rva002EB448();
 _Link_type node=static_cast<_Link_type>(raw);
 _Construct(reinterpret_cast<Copy2EF239 *>(&node->_M_value_field),reinterpret_cast<const Copy2EF239 &>(value));
 return node;
}
template<> __declspec(noinline) void _Construct<Copy2EF239,Copy2EF239>(Copy2EF239 *p,const Copy2EF239 &value) {
 new(p) Copy2EF239(value);
}
}

struct CreateNodeExposure2EF239 : Tree2EF239 {
 static Tree2EF239::_Link_type (Tree2EF239::*emitIntMappedNode)(const Value2EF239 &);
};
Tree2EF239::_Link_type (Tree2EF239::*CreateNodeExposure2EF239::emitIntMappedNode)(const Value2EF239 &) = &CreateNodeExposure2EF239::_M_create_node;
