// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Shared pair initializer for LocomotorSetType maps (AIUpdate parse cluster).
// Layout-identical non-const view of the map node pair; constructs from a
// key pointer plus a template vector. The vector copy folds to the rowed
// unsigned-int spelling (twin pin).

#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
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

// Suppress this TU's non-retail copy of ?allocate@?$allocator@PBVLocomotorTemplate@@@_STL@@QBEPAPBVLocomotorTemplate@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class LocomotorTemplate;
namespace _STL { template <> LocomotorTemplate const * * allocator<LocomotorTemplate const *>::allocate(unsigned int,void const *) const; }

typedef _STL::vector<const LocomotorTemplate *> LocomotorTemplateVector;

struct Rva000796CBPair
{
	int first;
	LocomotorTemplateVector second;

	Rva000796CBPair(const int *key, const LocomotorTemplateVector &vec);
};

Rva000796CBPair::Rva000796CBPair(const int *key, const LocomotorTemplateVector &vec)
	: first(*key), second(vec)
{
}
