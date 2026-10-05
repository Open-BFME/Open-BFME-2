// ??0BfmeRva00166110@@QAE@ABV0@@Z
// partial score=0.82 date=2026-10-05
// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector copy constructor for the 36-byte element, recovered at
// 0x00166110 (175B) under the class name BfmeRva00166110. Retail calls
// out-of-line get_allocator (0x001627F0, the address also held by the wide
// string get_allocator) on the source into a stack temporary, then
// _Vector_base<BfmePod36>::_Vector_base(size_type, const allocator&) at
// 0x00162800 with the (finish-start)/36 count from the 0x38E38E39 magic
// multiply, then expands __uninitialized_copy's element-wise _Construct loop
// inline. The explicit `template class _STL::vector<BfmePod36,...>` below is
// what forces both of those to stay out-of-line calls, which is retail's shape.
//
// The element is non-trivial: the copy moves eight dwords plus a byte. What
// still does not reproduce is the copy loop's register schedule: retail anchors
// the store block at element+0x1c and walks it partly backwards through
// [eax-0x18]/[ebx-0x18] with ebp as scratch, copies the leading dword separately
// through the loop-carried [esi]/[edi], and carries a `test edi,edi` guard and a
// push/pop ebp pair. cl 13.10 scalarises this element copy to one flat block of
// nine positive-offset stores under every lever tried (init-list order both
// ways, scalar vs array members, out-of-line copy constructor, /O1 /O2 /Ob1,
// /EHsc on and off), so the schedule is a codegen wall rather than a source
// shape difference.
#include <vector>

struct BfmePod36 {
    int a0, a1, a2, a3, a4, a5, a6, a7;
    char b;
    BfmePod36() {}
    BfmePod36(const BfmePod36 &o)
        : a0(o.a0), a1(o.a1), a2(o.a2), a3(o.a3),
          a4(o.a4), a5(o.a5), a6(o.a6), a7(o.a7), b(o.b) {}
};

class BfmeRva00166110 : public _STL::_Vector_base<BfmePod36, _STL::allocator<BfmePod36> >
{
public:
    BfmeRva00166110(const BfmeRva00166110 &__x)
        : _STL::_Vector_base<BfmePod36, _STL::allocator<BfmePod36> >(
              size_t(__x._M_finish - __x._M_start), __x.get_allocator())
    {
        this->_M_finish = _STL::__uninitialized_copy(
            (const BfmePod36 *)__x._M_start,
            (const BfmePod36 *)__x._M_finish,
            this->_M_start,
            _STL::__false_type());
    }
    _STL::allocator<BfmePod36> get_allocator() const {
        return _STLP_CONVERT_ALLOCATOR(
            (const _STL::allocator<BfmePod36> &)this->_M_end_of_storage, BfmePod36);
    }
};

template class _STL::vector<BfmePod36, _STL::allocator<BfmePod36> >;

void rva00166110Use(const BfmeRva00166110 &a, const BfmeRva00166110 &b)
{
    BfmeRva00166110 tmp(a);
    new (&tmp) BfmeRva00166110(b);
}
