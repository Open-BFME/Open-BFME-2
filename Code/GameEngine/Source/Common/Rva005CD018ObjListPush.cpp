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
class Rva005CD018Obj;
// Retail's element is an 8-byte Rva00468520, not this pointer: insert 0x005CCED5 calls the node creator 0x004F711C (0x10-byte node).
// The template's own creator would make a 0xC-byte node and copy 4 bytes.
class Rva00468520;
struct Rva004F711CObj;
Rva004F711CObj *__stdcall Rva004F711CCreate(const Rva00468520 *value);
namespace _STL {
template <> inline _List_node<Rva005CD018Obj *> *list<Rva005CD018Obj *>::_M_create_node(Rva005CD018Obj *const &value)
{
	return reinterpret_cast<_List_node<Rva005CD018Obj *> *>(Rva004F711CCreate(reinterpret_cast<const Rva00468520 *>(&value)));
}
}
template void _STL::list<Rva005CD018Obj *>::push_back(Rva005CD018Obj *const &);
