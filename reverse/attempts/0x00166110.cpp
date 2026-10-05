// ??0BfmeRva00166110@@QAE@ABV0@@Z
// partial score=0.93 date=2026-10-05
// cl: /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0BfmeRva00166110@@QAE@ABV0@@Z  @0x00166110  175B
//
// STLport 4.5.3 vector copy constructor for a 36-byte element, recovered under
// the class name BfmeRva00166110. Retail calls out-of-line get_allocator
// (0x001627F0, the address the wide string's get_allocator also holds) on the
// source into a stack temporary, then
// _Vector_base<BfmePod36>::_Vector_base(size_type, const allocator&) at
// 0x00162800 with the (finish - start) / 36 count from the 0x38E38E39 magic
// multiply, then expands __uninitialized_copy's _Construct loop inline. The
// explicit `template class _STL::vector<BfmePod36,...>` below is what forces
// both of those to stay out-of-line calls, which is retail's shape.
//
// Element layout, read off the copy loop's store schedule: the payload is 33
// bytes from offset 0 of a 36-byte slot -- eight dwords (0x00..0x1c) plus a
// byte at 0x20 -- not 33 bytes from offset 4 as the first bank of this body
// modelled. Retail's own schedule is what fixes it, because the loop anchors a
// store block at element + 0x1C and walks it down through negative displacements
// ([eax-0x18] .. [ecx+4]) with ebp as scratch, copies the leading dword
// separately through the loop-carried [esi] / [edi], and carries a
// `test edi,edi` guard with a push/pop ebp pair. That grouping -- a 16-byte
// block at 0x04, an 8-byte block at 0x14, a dword at 0x1C, a byte at 0x20,
// after a standalone leading dword at 0x00 -- is reproduced here by BfmePod36's
// nesting rather than by nine flat scalars, which cl 13.10 flattens into one
// positive-offset store block. See reverse/re_attempts.log row 0x166110.
//
// What still does not reproduce, and why it is not a source-shape difference:
// retail's loop anchor is element + 0x1C where every nesting of the same three
// groups anchors at element + 0x14 (the address of the trailing group, which is
// where a pointer-indirect 32-bit copy block prefers to start), and retail walks
// that block down from element + 0x04 with [eax-0x18] while this body walks the
// other way from + 0x14 with [eax-0x10]. Retail's second scratch is ebx, whose
// live value is the saved `this`, so it pays a reload from the hidden ctor
// parameter slot before its seventh store; this body's ebx is free, so cl uses
// it as a second address scratch. Both are post-SSA register-allocation
// choices. Source levers tried and measured under this toolchain: scalar vs
// array vs nested-struct members, copy-constructor init-list order both ways,
// hand-written assignment bodies, __uninitialized_copy vs placement new vs
// _Construct loops, true_type and false_type dispatch, /O1 /O2 /Ox /Ob1, and
// __EHsc on and off -- 44 of 175 bytes positionally, none reaching the anchor.
#include <vector>

struct Pod16 { int a0, a1, a2, a3; };
struct Pod8 { int b0, b1; };

struct BfmePod36 {
    int lead;
    Pod16 hi;
    Pod8 mid;
    int last;
    char c;
    BfmePod36() {}
    BfmePod36(const BfmePod36 &o)
        : lead(o.lead), hi(o.hi), mid(o.mid), last(o.last), c(o.c) {}
};

class BfmeRva00166110 : public _STL::_Vector_base<BfmePod36, _STL::allocator<BfmePod36> >
{
public:
    BfmeRva00166110(const BfmeRva00166110 &__x)
        : _STL::_Vector_base<BfmePod36, _STL::allocator<BfmePod36> >(
              size_t(__x._M_finish - __x._M_start), __x.get_allocator())
    {
        BfmePod36 *__f = this->_M_start;
        for (const BfmePod36 *__s2 = __x._M_start; __s2 != __x._M_finish;
             ++__s2, (void)++__f) {
            new (__f) BfmePod36(*__s2);
        }
        this->_M_finish = __f;
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