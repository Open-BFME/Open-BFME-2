// ??0BfmeRva00166110@@QAE@ABV0@@Z
// partial score=0.94 date=2026-10-05
// The // cl: flag line and the // stlport marker below MUST stay at the very top
// of any copy of this file. tools/build.py reads flags from the FIRST line
// starting "// cl:" and puts vendor/stlport on the include path only when
// "// stlport" appears. When both sat below the stashed partial header this file
// built with default flags and then did not compile at all (11 errors, _STL not
// a namespace). See reverse/re_attempts.log row 0x166110.
// cl: /G7 /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// finish round from the 0.94 bank
// ??0BfmeRva00166110@@QAE@ABV0@@Z
// partial score=0.99 date=2026-10-05
// cl: /G7 /O2 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// STLport 4.5.3 vector copy constructor for a 36-byte element, recovered under
// the class name BfmeRva00166110. HTreeClass's copy constructor row at
// 0x001662A0 (Code/Libraries/Source/WWVegas/WW3D2/HTreeClassCopyConstructor.cpp)
// copy-constructs its +0x1C member through a body with its own copy
// constructor at 0x00166110, which is this one, so the unit sits beside it.
// /G7 is the shared tell of this WW3D2 shape and is worth seven bytes.
//
// Retail calls out-of-line get_allocator (0x001627F0, whose own 7-byte body is
// only the hidden return pointer for an empty allocator) on the source into a
// stack temporary, then _Vector_base<BfmePod36>::_Vector_base(size_type,
// const allocator&) at 0x00162800 with the (finish - start) / 36 count from the
// 0x38E38E39 magic multiply, then expands __uninitialized_copy's _Construct loop
// inline. The `template class _STL::vector<BfmePod36,...>` instantiation below is
// what forces both of those to stay out-of-line calls, which is retail's shape.
//
// THIS ROUND'S RESULT: the two calls are no longer unpatchable. Every earlier
// bank reported them as a wall on the grounds that "the harness cannot patch a
// REL32 to an address nothing in this TU defines". That is true of the calls,
// but not of the addresses, and the two addresses are independently legible in
// retail's own bytes:
//
//   0x00162800  8b 44 24 08 / push ebx / push esi / mov esi,ecx / push edi
//               16280b lea ebx,[esi+8] / push 0 / push eax / mov ecx,ebx
//               162811 mov [esi],0 / mov [esi+4],0 / call 0x7410 (proxy ctor)
//
//   0x00162823  mov edi,[esp+0x10]   (the size_type argument)
//   0x00162827  test edi,edi / je
//   0x0016282b  lea ecx,[edi+edi*8] / add ecx,ecx / add ecx,ecx
//               => capacity bytes = ((n*9) << 2) * 2 = n * 36
//
// That lea chain is the element size in open-coded arithmetic, and 36 is
// BfmePod36's stride -- the same 0x24 the copy loop below steps by four times
// (0x001661a2/0x001661a5/0x001661a8/0x001661ab add esi/eax/edi/ecx, 0x24).
// 0x00162846 then recomputes n*36 for end_of_storage. So 0x00162800 is genuinely
// this instantiation's own body, NOT an ICF fold onto a 2/4/8-byte base ctor --
// which is the reason 0x00162xxx carries none of the folded 0x00211E58 /
// 0x004F62A4 base ctors that symbols.csv lists for other element sizes, and why
// no _Vector_base<wchar_t> size ctor is pinned anywhere for 0x00162800. Both
// pins below are therefore facts read from retail bytes, not guesses, and
// tools/pin_consistency.py reports the names unused before either was written.
//
// Measured effect, same body, same flags, symbol map only:
//   no pins              142/175   2 unresolved calls
//   _Vector_base pin     146/175   1 unresolved call
//   get_allocator pin    146/175   1 unresolved call
//   both                 150/175   0 unresolved calls
// Eight retail bytes recovered; get_allocator is additionally non-optional,
// since without it cl inlines the empty allocator and the whole body collapses.
//
// What remains is 25 bytes and it is one thing, now precisely characterised.
// Retail hoists the block base at element+0x1C and walks it DOWN through
// [eax-0x18]..[eax+4] (0x00166168 lea edx,[eax-0x18], then -8/-4/0/+4), while
// this body hoists at element+0x14 and walks UP through [eax-0x10]..[eax+0xc]
// (0x00166168 lea edx,[eax-0x10], then 0/4/8/c). Nothing about the element
// contents is in dispute -- both forms copy element+0x04..element+0x24 in the
// same register sequence, through the same 16-byte block, with the same leading
// dword carried in [esi]/[edi] and the same byte at the end; only which end of
// the copied range cl picks as the base differs, and that is decided after
// memberwise-copy decomposition, where no source-level grouping steers it.
// Element layout, read off the store schedule and unchanged from the bank: the
// payload is 33 bytes from offset 0 of a 36-byte slot -- eight dwords
// (0x00..0x1c) plus a byte at 0x20 -- after a standalone leading dword at 0x00,
// a 16-byte block at 0x04, an 8-byte block at 0x14, a dword at 0x1c and the byte
// at 0x20. See reverse/re_attempts.log row 0x166110.
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
        const BfmePod36 *__e2 = __x._M_finish;
        const BfmePod36 *__s2 = __x._M_start;
        BfmePod36 *__f = this->_M_start;
        while (__s2 != __e2) {
            new (__f) BfmePod36(*__s2);
            ++__s2;
            ++__f;
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
