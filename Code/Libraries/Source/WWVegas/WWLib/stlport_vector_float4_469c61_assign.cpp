// cl: /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??4?$vector@UBfmeFloat4Record00469C61@@V?$allocator@UBfmeFloat4Record00469C61@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x0007C316 183B
// vector<BfmeFloat4Record00469C61>::operator= for the 16-byte four-float record (copy via 0x469C61 -> 0x4254E).
// Evidence: leaf body called from 0x7C4BA; 16-byte stride sar 4; rowed callees _M_allocate_and_copy 0x7C25C
// _free 0x30830 and __uninitialized_copy 0x5385F3; copy parts via in-TU __copy_ptrs (stock inline 4-arg
// no distance) folding to the rowed Region2D wrapper family 0x7BF5A/0x7BF77; prev Destroy 0x7C2D7 and next
// Rva007C454Ctor 0x7C3CD; flags follow stlport_vector_BfmeRecord0040B61A_assign.cpp (no STATIC_LIB so no
// distance push per its comment); element name from stlport_vector_float4_469c61.cpp.
#include <stdlib.h>
#include <vector>
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUBfmeFloat4Record00469C61@@U1@V?$allocator@UBfmeFloat4Reco:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeFloat4Record00469C61;
namespace _STL { template <> BfmeFloat4Record00469C61 * _STLP_alloc_proxy<BfmeFloat4Record00469C61 *,BfmeFloat4Record00469C61,allocator<BfmeFloat4Record00469C61> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UBfmeFloat4Record00469C61@@@_STL@@QBEXPAUBfmeFloat4Record00469C61@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<BfmeFloat4Record00469C61>::deallocate(BfmeFloat4Record00469C61 *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
#include "../../../../GameEngine/Include/GameLogic/BfmeFloat4Record00469C61.h"
// Plain four-dword assignment: retail's element copy (0x0007BF5A -> 0x0007BF77) runs
// the shared 16-byte copy 0x0004254E per element.
inline BfmeFloat4Record00469C61 &BfmeFloat4Record00469C61::operator=(const BfmeFloat4Record00469C61 &o) { x = o.x; position.x = o.position.x; position.y = o.position.y; position.z = o.position.z; return *this; }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Construct<BfmeFloat4Record00469C61,BfmeFloat4Record00469C61>(BfmeFloat4Record00469C61 *p,BfmeFloat4Record00469C61 const &v) { new (p) BfmeFloat4Record00469C61(v); } }
namespace _STL {
template<>
_STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> > &
_STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::operator=(
    const _STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> > &other)
{
    if (&other != this) {
        unsigned int otherSize = (unsigned int)(other._M_finish - other._M_start);
        unsigned int cap = (unsigned int)(_M_end_of_storage._M_data - _M_start);
        if (otherSize > cap) {
            BfmeFloat4Record00469C61 *tmp = _M_allocate_and_copy(otherSize, (BfmeFloat4Record00469C61 *)other._M_start, (BfmeFloat4Record00469C61 *)other._M_finish);
            if (_M_start)
                free(_M_start);
            _M_start = tmp;
            _M_end_of_storage._M_data = _M_start + otherSize;
        } else if ((unsigned int)(_M_finish - _M_start) >= otherSize) {
            _STL::__copy_ptrs((const BfmeFloat4Record00469C61 *)other._M_start, (const BfmeFloat4Record00469C61 *)other._M_finish, _M_start, _STL::__false_type());
        } else {
            _STL::__copy_ptrs((const BfmeFloat4Record00469C61 *)other._M_start, (const BfmeFloat4Record00469C61 *)other._M_start + (_M_finish - _M_start), _M_start, _STL::__false_type());
            _STL::__uninitialized_copy((BfmeFloat4Record00469C61 *)(other._M_start + (_M_finish - _M_start)), (BfmeFloat4Record00469C61 *)other._M_finish, _M_finish, _STL::__false_type());
        }
        _M_finish = _M_start + otherSize;
    }
    return *this;
}
}
