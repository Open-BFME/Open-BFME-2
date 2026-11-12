// cl: /Ireference/shims/bfmealloc_alloconly /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include "../../Include/Common/Rva00293486Record.h"
// The record's placement copy is retail 0x002927CB, rowed as the typed
// ?Rva002927CBConstruct (an EH frame around the {int, AsciiString} copy ctor
// 0x000CF475); _M_create_node 0x00293486 calls it. This TU's 8-byte
// template copy is not that body, so the call binds to the row instead.
struct TreeKey00242F5E;
void Rva002927CBConstruct(TreeKey00242F5E *dest, const TreeKey00242F5E &source);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva00293486Record *dest, const Rva00293486Record &source)
{
    Rva002927CBConstruct(reinterpret_cast<TreeKey00242F5E *>(dest),
                         *reinterpret_cast<const TreeKey00242F5E *>(&source));
}
}
#include <list>
// The element is Object::xfer's 8-byte unresolved-trigger pair; its list
// node allocation is the rowed _M_create_node at 0x00293486 (the only caller
// is this unit's insert at 0x002947F0), whose opaque record spelling it shares.
template void _STL::list<Rva00293486Record>::push_back(const Rva00293486Record &);
