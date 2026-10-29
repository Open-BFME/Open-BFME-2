// cl: /DNDEBUG /MD /EHsc /Od
// stlport46
// STLport's unoptimized allocation helpers retain stack locals in retail.

#include <stdlib.h>
#include <stdio.h>

namespace _STL
{
typedef void (__cdecl *__oom_handler_type)();

template <int Instance>
class __malloc_alloc
{
private:
    static void *__cdecl _S_oom_malloc(unsigned int bytes);
    static __oom_handler_type __oom_handler;
};

// Algorithm from STLport 4.5.2 stl/_alloc.c; its no-exception branch is in _alloc.h.
template <int Instance>
void *__cdecl __malloc_alloc<Instance>::_S_oom_malloc(unsigned int bytes)
{
    __oom_handler_type __my_malloc_handler;
    void *__result;

    for (;;) {
        __my_malloc_handler = __oom_handler;
        if (__my_malloc_handler == 0) {
            puts("out of memory\n");
            exit(1);
        }
        (*__my_malloc_handler)();
        __result = malloc(bytes);
        if (__result) return __result;
    }
}

template void *__malloc_alloc<0>::_S_oom_malloc(unsigned int);

// The handler slot: _S_oom_malloc's matched DIR32 read at +0x7 resolves to VA
// 0x00DDF4CC in the .data zero-fill tail, so retail starts it null.
template <int Instance>
__oom_handler_type __malloc_alloc<Instance>::__oom_handler = 0;
template __oom_handler_type __malloc_alloc<0>::__oom_handler;
}
