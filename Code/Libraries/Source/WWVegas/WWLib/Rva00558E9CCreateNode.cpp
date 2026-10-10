// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native558E9C..558EC1 and558FEE node insertion prove16-byte links plus
// 54C-byte value and signed integer key. Existing5564EB copies the leading
// key then PSPlayerAllStats through38630B. Original mapped/container type
// spelling remains unknown; retain the independently established copy view.
// Twin lead3044C3 differs only node size and target construction provider.
#include <memory>
struct Rva00557C90Element {
 Rva00557C90Element(const Rva00557C90Element &);
 unsigned char bytes[0x54c];
};
namespace _STL {
template<> class allocator<char> { public:static char *allocate(unsigned int bytes,const void *hint); };
template<> void _Construct<Rva00557C90Element,Rva00557C90Element>(Rva00557C90Element *,const Rva00557C90Element &);
}
struct Rva00558E9CNode { unsigned char links[0x10];Rva00557C90Element value; };
class Rva00558E9CTree {
public: Rva00558E9CNode *rva00558E9C(const Rva00557C90Element &value);
};
Rva00558E9CNode *Rva00558E9CTree::rva00558E9C(const Rva00557C90Element &value) {
 char *node=_STL::allocator<char>::allocate(0x10+sizeof(Rva00557C90Element),0);
 _STL::_Construct(reinterpret_cast<Rva00557C90Element *>(node+0x10),value);
 return reinterpret_cast<Rva00558E9CNode *>(node);
}
