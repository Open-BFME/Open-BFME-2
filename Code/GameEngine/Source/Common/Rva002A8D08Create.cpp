// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva002A8D08Create@@YGPAXPAX@Z @0x002A8D08 37B alloc 12 via rowed 0x000307F0 zero +4 via rowed dup 0x002A8C17 return ptr arg src caller 0x002A9059
#include <memory>
void __cdecl dup_002A8C17();

void *__stdcall Rva002A8D08Create(void *src)
{
    void *p = _STL::allocator<char>::allocate(12, 0);
    *(int *)p &= 0;
    ((void (__cdecl *)(void *, const void *))&dup_002A8C17)((char *)p + 4, src);
    return p;
}
