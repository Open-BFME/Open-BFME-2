// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva001FFC38Copy@@YAPAXPAX000@Z @0x001FFC38 29B: 5-arg forward to rowed 0x00339A8D copy with dummy tag and 0. Evidence: callee row ?Rva00339A8DCopy; callers 0x001FFDE2 0x001FFE02 0x00339E94; neighbours Rva001FFA5A DynamicPortalLinkVector same flags.
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
};
}
typedef _STL::vector<int, _STL::allocator<int> > SciVec;
SciVec *__cdecl Rva00339A8DCopy(SciVec *first, SciVec *last, SciVec *dest, void *tag, int extra);

void *__cdecl Rva001FFC38Copy(void *a, void *b, void *c, void *d)
{
	char tmp;
	return (void *)Rva00339A8DCopy((SciVec *)a, (SciVec *)b, (SciVec *)c, &tmp, 0);
}
