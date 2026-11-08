// cl: /Ireference/shims/bfmealloc_alloconly /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
#include <list>

// __node_alloc<1,0>::allocate (STLport node path) otherwise emits a per-TU
// COMDAT that loses to another unit's copy in link order; this explicit
// dllimport+forceinline specialization keeps the body inline and emits none.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}
class Rva00242EE7Obj;
// Retail's element is an 8-byte BfmeStringRecord00239B46, not this pointer: insert 0x00241955 calls the node creator 0x00240C89 (0x10-byte node).
// The template's own creator would make a 0xC-byte node and copy 4 bytes.
struct BfmeStringRecord00239B46;
struct Rva00240C89Node;
Rva00240C89Node *__stdcall Rva00240C89Create(const BfmeStringRecord00239B46 &value);
namespace _STL {
template <> inline _List_node<Rva00242EE7Obj *> *list<Rva00242EE7Obj *>::_M_create_node(Rva00242EE7Obj *const &value)
{
	return reinterpret_cast<_List_node<Rva00242EE7Obj *> *>(Rva00240C89Create(reinterpret_cast<const BfmeStringRecord00239B46 &>(value)));
}
}
template void _STL::list<Rva00242EE7Obj *>::push_back(Rva00242EE7Obj *const &);
