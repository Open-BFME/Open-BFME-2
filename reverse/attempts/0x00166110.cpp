// ??0BfmeRva00166110@@QAE@ABV0@@Z
// partial score=0.95 date=2026-10-05
// cl: /G7 /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector copy constructor for a 36-byte element, recovered under
// the class name BfmeRva00166110. Retail calls out-of-line get_allocator
// (0x001627F0, whose own 7-byte body is only the hidden return pointer for an
// empty allocator) on the source into a stack temporary, then
// _Vector_base<BfmePod36>::_Vector_base(size_type, const allocator&) at
// 0x00162800 with the (finish - start) / 36 count from the 0x38E38E39 magic
// multiply, then expands __uninitialized_copy's _Construct loop inline. The
// explicit `template class _STL::vector<BfmePod36,...>` below is what forces
// both of those to stay out-of-line calls, which is retail's shape.
//
// Element layout, read off the copy loop's store schedule: the payload is 33
// bytes from offset 0 of a 36-byte slot -- eight dwords (0x00..0x1c) plus a
// byte at 0x20 -- not 33 bytes from offset 4 as the first bank of this body
// modelled. Retail's own schedule is what fixes it, because the loop copies the
// leading dword separately through the loop-carried [esi] / [edi], anchors a
// store block at element + 0x1C and walks it down through negative
// displacements ([eax-0x18] .. [ecx+4]) with ebp as scratch, and carries a
// `test edi,edi` guard with a push/pop ebp pair. That grouping -- a 16-byte
// block at 0x04, an 8-byte block at 0x14, a dword at 0x1C, a byte at 0x20,
// after a standalone leading dword at 0x00 -- is what BfmePod36's nesting
// reproduces. See reverse/re_attempts.log row 0x166110.
//
// /G7 is the unit's tell, shared with every other WW3D2 unit that carries this
// shape, and it is worth seven bytes here: it takes the emitted body from 180 to
// 178 and moves 51 of 175 bytes onto retail's addresses, against 44 without it.
// Every flag lever measured -- /O1 /O2 /Ox /Ob1 /Ot, /G4 /G6 /G7, /arch:SSE,
// /arch:SSE2, /favor:INTEL and __EHsc on and off -- either leaves the copy loop
// alone or collapses it.
//
// What still does not reproduce: retail keeps `this` in ebx through the loop and
// reloads it from the hidden copy-constructor parameter slot at [esp+0x10]
// before its seventh store, because its ebp is the loop's value scratch; this
// body has a free ebx, so cl spends it on a second address scratch. Retail also
// anchors the block at element + 0x1C where this one anchors at element + 0x14:
// reaching retail's anchor needs a non-aggregate member before the trailing group
// (a union does it, measured), but the trailing run then collapses into four
// dword stores where retail keeps three dwords and a byte. The two requirements
// have not been satisfied at the same time.
#include <vector>

struct Pod16 { int a0, a1, a2, a3; };
struct Pod8 { int b0, b1; };
struct Byte1 { char c; };

struct BfmePod36 {
    int lead;
    Pod16 hi;
    Pod8 mid;
    int t2;
    Byte1 by;
    BfmePod36() {}
    BfmePod36(const BfmePod36 &o)
        : lead(o.lead), hi(o.hi), mid(o.mid), t2(o.t2), by(o.by) {}
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