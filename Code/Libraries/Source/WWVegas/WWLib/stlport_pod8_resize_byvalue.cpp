// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Pod8 vector resize with the fill value taken BY VALUE (retail 0x005FF96A,
// 63B, ends ret 0xC). STLport 4.5.3 only declares the const-ref resize, so
// this TU derives from the real _STL::vector<BfmePod8> instantiation (same
// headers and flags as stlport_pod_vector_malloc_bodies.cpp, whose prologue
// already matches retail through the erase call) and adds the by-value
// overload retail was built with. The by-value parameter is what emits
// retail's lea edi,[esp+0x10] plus push edi argument forwarding. Callees
// resolve to the rowed 2-argument erase (0x003FA4DB) and _M_fill_insert
// (0x000B02B6).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

#include "../../../../GameEngine/Source/Common/BattlePromptArmyPanelClipImplView.h"
// These elements copy through real copy constructors; their _Construct
// bodies are rowed under the real element names, so call those.
struct BfmePod8;
void __cdecl Rva004C3A9FConstruct(void *, const void *) throw();
namespace _STL {
// 0x004C3A9F
template <> __declspec(dllimport) __forceinline void _Construct<BfmePod8, BfmePod8>(BfmePod8 *p, const BfmePod8 &v) throw()
{ ::Rva004C3A9FConstruct(p, &v); }
}
// Suppress this TU's non-retail copy of ?allocate@?$allocator@UBfmePod8@@@_STL@@QBEPAUBfmePod8@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> BfmePod8 *allocator<BfmePod8>::allocate(size_t, const void *) const; }

// The element retail really holds here is the 8-byte record whose
// _M_fill_insert is the rowed body at 0x000B02B6, spelled BfmeE8 in that
// row's family (its own copies are __uninitialized_copy 0x004C3121 and
// _M_insert_overflow 0x00057C80). This view's BfmePod8 parameter is the same
// record under the older placeholder spelling, so reach the rowed
// instantiation through the E8 view of the same three-pointer vector.
// Retail 0x004C3ACC: this unit owns the 8-byte element's non-trivial copy
// loop (its _Construct is the rowed 0x004C3A9F body). The vector above moved
// to the E8 spelling, so instantiate the copy explicitly to keep that row.
namespace _STL {
template BfmePod8 *__uninitialized_copy<BfmePod8 *, BfmePod8 *>(BfmePod8 *, BfmePod8 *, BfmePod8 *, const __false_type &);
}

struct BfmeE8 { int a[2]; };
namespace _STL {
// The rowed provider serves the link; declare it so this unit emits no copy.
template <> void vector<BfmeE8>::_M_fill_insert(BfmeE8 *, unsigned int, const BfmeE8 &);
}
void BfmePod8Vector::resize(unsigned int n, BfmePod8 x)
{
	if (n < size())
		erase(begin() + n, end());
	else
		((_STL::vector<BfmeE8> *)this)->_M_fill_insert(
			(BfmeE8 *)end(), n - size(), *(const BfmeE8 *)&x);
}

// ?resize@BfmePod8Vector@@QAEXI@Z @ 0x000B0857 (23B). One-argument resize
// forwarding an indeterminate default pod to the rowed by-value resize
// above; the two filler pushes carry the incoming ecx. Callers 0x000B0DA8
// and 0x000B0F82.
void BfmePod8Vector::resize(unsigned int n)
{
	BfmePod8 x;
	resize(n, x);
}

// ?rva005FF9C5@Rva005FF9C5@@QAEXI@Z @ 0x005FF9C5 (19B). A second one-argument
// resize over the same vector, whose default pod is {0, -1}; it forwards to
// the rowed by-value resize 0x005FF96A. Owner type unrecovered.
class Rva005FF9C5 : public BfmePod8Vector
{
public:
	void rva005FF9C5(unsigned int n);
};

void Rva005FF9C5::rva005FF9C5(unsigned int n)
{
	BfmePod8 x;
	x.a[0] = 0;
	x.a[1] = -1;
	resize(n, x);
}
