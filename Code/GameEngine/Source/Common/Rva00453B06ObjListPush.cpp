// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport46
#include <list>

class Rva00453B06Obj;
class Rva004530ED;
void *__stdcall Rva004534A1Create(const Rva004530ED &value);

// The ledger's pointer-list name is a legacy view of GettingBuiltBehavior's
// 20-byte Rva004530ED entries. Retail insert (0x00453AB8) calls this existing
// 28-byte node creator, which constructs the complete record at node +8.
// Forward node creation to that owner so the emitted insert is a relocation-
// true twin, rather than allocating and copying a pointer-sized entry.
namespace _STL {
template <> __forceinline list<Rva00453B06Obj *>::_Node *
list<Rva00453B06Obj *>::_M_create_node(Rva00453B06Obj *const &value)
{
    return (_Node *)Rva004534A1Create((const Rva004530ED &)value);
}
}
template void _STL::list<Rva00453B06Obj *>::push_back(Rva00453B06Obj *const &);
