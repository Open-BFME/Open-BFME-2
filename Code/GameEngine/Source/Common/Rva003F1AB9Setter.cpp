// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport46
// Dump range 18 setter 0x003F1AB9 (70B): vector assign at +0x158 via rowed
// 0x0021C21B plus three ints at +0x14C/+0x150/+0x154 and two bytes at
// +0x1A0/+0x1A1. Straight-line thiscall with six stack args, ret 0x18.
#include <vector>
#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@HV?$allocator@H@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<int, allocator<int> >::_M_clear(); }

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
}

// Native 0x0021C21B is owned by the non-POD-traited four-byte record
// specialization in StlSweepW5Rva0021C21B.cpp. Preserve this caller's
// storage and argument ABI while naming the verified out-of-line provider.
struct Rva0021C21BElement { char bytes[4]; };
typedef _STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > RetailAssignVector;
namespace _STL {
template <> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &
vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(
    const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &);
}

class Rva003F1AB9Owner
{
public:
    void rva003F1AB9(const _STL::vector<int> &v, int a, int b, int c, bool d, bool e);
private:
    char m_pad[0x14C];
    int m_14C;
    int m_150;
    int m_154;
    _STL::vector<int> m_158;
    char m_after158[0x1A0 - (0x158 + 12)];
    unsigned char m_1A0;
    unsigned char m_1A1;
};

void Rva003F1AB9Owner::rva003F1AB9(const _STL::vector<int> &v, int a, int b, int c, bool d, bool e)
{
    *(RetailAssignVector *)&m_158 = *(const RetailAssignVector *)&v;
    m_14C = a;
    m_150 = b;
    m_154 = c;
    m_1A0 = d;
    m_1A1 = e;
}
