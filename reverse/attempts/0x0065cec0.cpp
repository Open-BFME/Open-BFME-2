// ?Rva0065CEC0Allocate@@YAPAXIH@Z
// partial score=1.0 date=2026-10-09
// cl: /O2 /MD
// Native defaults stored by the allocator constructor at 65CF60 and init at
// 65CF90. Retail 65CEC0 forwards size to the MSVCR71 malloc thunk 628F92;
// 65CED0 forwards the pointer to the free thunk 628F98. Both ignore the
// allocator callback's second argument and return with caller stack cleanup.
// Semantic donor: BFME1 874e38488c GameAudio.cpp BfmePoolGlue operator-new /
// operator-delete wrappers (7EFFE0/7EFFF0). Callback role and target addresses
// are BFME2 facts; address-derived names preserve the unknown original names.

namespace BfmeAllocatorCRT {
extern "C" void *__cdecl malloc(unsigned int);
extern "C" void __cdecl free(void *);
}

void *__cdecl Rva0065CEC0Allocate(unsigned int size, int)
{
    return BfmeAllocatorCRT::malloc(size);
}

void __cdecl Rva0065CED0Release(void *pointer, int)
{
    BfmeAllocatorCRT::free(pointer);
}
