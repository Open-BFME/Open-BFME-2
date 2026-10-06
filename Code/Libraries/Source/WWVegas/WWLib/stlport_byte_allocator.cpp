// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport's raw byte allocator at BFME2 RVA 0x000307F0 (22 bytes).
// Its matched indirect call forwards (bytes, memory class 3, hint) through
// VA 0x00DE0404, the callback slot defined by mem_ops.cpp. Use that existing
// definition so both wrappers share the same runtime binding.
// Other allocator spellings remain fold candidates in the pin list; this
// definition supplies the established narrow-char member.
#include <memory>
extern "C" void *(__cdecl *__gameMemAllocatePtr)(unsigned int, int, const void *);
char *_STL::allocator<char>::allocate(unsigned int n, const void *hint)
{
    unsigned int bytes = n;
    const void *hintCopy = hint;
    return (char *)__gameMemAllocatePtr(bytes, 3, hintCopy);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?allocate@BucketAlloc@@SAPAXIPBX@Z=?allocate@?$allocator@D@_STL@@SAPADIPBX@Z")
