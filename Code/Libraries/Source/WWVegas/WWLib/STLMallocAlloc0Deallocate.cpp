// cl: /DNDEBUG /MD /EHsc /Od

// STLport __malloc_alloc<0>::deallocate(void*, size_t), BFME2 RVA 0x00023A70,
// 18 bytes. Byte-identical donor: BFME1 RVA 0x0082B100. The method body is
// from vendor/stlport/stl/_alloc.h. Preserve retail's unoptimized frame and
// dllimport free call, and emit the real template method instead of a C facade.
extern "C" __declspec(dllimport) void __cdecl free(void *);

namespace _STL {
template <int inst>
class __malloc_alloc {
public:
    static void deallocate(void *p, unsigned int) { free((char *)p); }
};

template void __malloc_alloc<0>::deallocate(void *, unsigned int);
}
