// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002F3738@Rva002F3738@@QAEXPAPAX@Z @0x002F3738 33B
// Thiscall, one pointer-to-pointer argument, ret 4: push_back of the 4-byte
// pointer at the argument into the vector at +0, then std::push_heap over
// [begin, end) with the one-byte empty comparator stored at +0xC. Follows
// 0x002F370D (43B) in PathfinderRva002F36E5.cpp; the heap call is the rowed
// push_heap<_Rva002EBB53Wrap **, Rva002EBB53Compare> 0x002F0D35 (its own
// callee __push_heap_aux 0x002EF216 proves the element and comparator).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <algorithm>
#include <functional>
#include <vector>
// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

struct _Rva002EBB53Inner {
    char m_pad[0x10];
    unsigned short m_key;
};
struct _Rva002EBB53Wrap {
    _Rva002EBB53Inner *m_inner;
};
// Empty comparator, greater-than on the payload key: the smallest key is on
// top of the heap.
#include "../../../Include/Common/Rva002EBB53Compare.h"
extern template void _STL::push_heap(_Rva002EBB53Wrap **, _Rva002EBB53Wrap **, Rva002EBB53Compare);

class Rva002F3738
{
public:
	void rva002F3738(void **value);
private:
	_STL::vector<_Rva002EBB53Wrap *> m_vec;
	Rva002EBB53Compare m_compare;
};

void Rva002F3738::rva002F3738(void **value)
{
	m_vec.push_back(*reinterpret_cast<_Rva002EBB53Wrap **>(value));
	_STL::push_heap(m_vec.begin(), m_vec.end(), m_compare);
}
