// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 pointer list used by native Palantir radar pings.
// Native2D4FDB inserts a null node; ctor2D3CA5 writes its ping pointer at
// node+8; release2D3D2A erases the same cursor. These emitted bodies are
// byte-and-relocation twins of the existing int-list providers (zero gain).
#include <list>
class Rva002D5333;
namespace _STL {
template<> list<Rva002D5333*>::_Node *list<Rva002D5333*>::_M_create_node(Rva002D5333*const&);
template list<Rva002D5333*>::iterator list<Rva002D5333*>::insert(list<Rva002D5333*>::iterator,Rva002D5333*const&);
template list<Rva002D5333*>::iterator list<Rva002D5333*>::erase(list<Rva002D5333*>::iterator);
}
