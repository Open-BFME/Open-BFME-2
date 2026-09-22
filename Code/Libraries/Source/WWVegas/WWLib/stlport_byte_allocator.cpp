// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME's raw byte allocator at RVA 0x307F0.
// Every allocating container in game.dat funnels through this 19-byte body:
// it forwards (bytes, memory-class 3, hint) to the game allocator table at
// 0x00DE0404 and is folded image-wide across the char/wide/pair/BucketAlloc
// spellings (five pins, one address). Rowed under the narrow-char spelling;
// the sibling pins stand as fold candidates. The table call is a direct
// memory-indirect FF15 through an extern function-pointer global whose DIR32
// slot the verifier masks (clamp-table precedent).
#include <memory>
extern "C" void *(__cdecl *g_byteAllocatorTable)(unsigned int, int, const void *);
char *_STL::allocator<char>::allocate(unsigned int n, const void *hint)
{
    unsigned int bytes = n;
    const void *hintCopy = hint;
    return (char *)g_byteAllocatorTable(bytes, 3, hintCopy);
}
