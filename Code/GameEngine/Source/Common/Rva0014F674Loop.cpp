// cl: /DNDEBUG /MD
// Retail 0x0014FA47 forwards to the uninitialized fill worker owned by
// VectorOverflowRva001504A1.cpp at 0x0014F674. The 76-byte payload remains
// address-derived; this declaration shares the retained worker identity.
struct Rva001504A1Record;
namespace _STL {
struct __false_type {};
template<class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n(ForwardIterator, Size, const T &, const __false_type &);
}
void *__cdecl rva0014FA47(void *a, unsigned int b, void *c)
{
    _STL::__false_type tag;
    return _STL::__uninitialized_fill_n<Rva001504A1Record *, unsigned int, Rva001504A1Record>(
        (Rva001504A1Record *)a, b, *(const Rva001504A1Record *)c, tag);
}
