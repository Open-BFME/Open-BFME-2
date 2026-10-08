// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// STLport 4.5.3 _M_insert_overflow; reference headers at BFME1 revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, BFME2 bfmealloc shim.
// Target 0x005244DC has a complete 178-byte boundary and 8-byte elements.
// Its copy/fill helpers 0x523E01/0x523E27 call placement construction
// 0x523DD4, whose copy constructor is the recovered TreeKey00242F5E at
// 0xCF475 (integer plus AsciiString). This identifies the element footprint
// and copy behavior; the original application owner/name remains unknown.
// The queue's pair<SubsystemInterface*,void*> identity is refuted by that
// nontrivial copy chain. No SubsystemInterface layout is inferred here.
// All calls and all 178 bytes verify strictly. Allocation 0x523D6C,
// Destroy 0x48CE25 and clear 0xC060A independently reproduce existing bodies.
// The typed placement call uses the existing duplicate name because retail
// contains a separate EH-bearing _Construct copy at 0x523DD4.
#pragma comment(linker, "/alternatename:?dup_00523DD4@@YAXXZ=??$_Construct@UTreeKey00242F5E@@U1@@_STL@@YAXPAUTreeKey00242F5E@@ABU1@@Z")
#define _STLP_NO_EXCEPTIONS 1
// TU-local overload avoids an incompatible shared max<unsigned> COMDAT.
// It implements the same unsigned comparison used by retail's growth path.
namespace _STL {
// ?max unsigned comparison adapter absent-from-retail
__forceinline const unsigned &max(const unsigned &a,const unsigned &b) {
 return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"
struct TreeKey00242F5E {
 int m_id; AsciiString m_name;
 TreeKey00242F5E(const TreeKey00242F5E &);
 ~TreeKey00242F5E();
};
void __cdecl dup_00523DD4();
namespace _STL {
// ?_Construct typed placement adapter absent-from-retail
__forceinline void _Construct(TreeKey00242F5E *p,const TreeKey00242F5E &x) {
 typedef void (__cdecl *Fn)(TreeKey00242F5E *,const TreeKey00242F5E &);
 ((Fn)&dup_00523DD4)(p,x);
}
}
typedef _STL::vector<TreeKey00242F5E,_STL::allocator<TreeKey00242F5E> > TreeKeyVector;
template void TreeKeyVector::_M_insert_overflow(TreeKey00242F5E *,const TreeKey00242F5E &,const _STL::__false_type &,unsigned int,bool);
