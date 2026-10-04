// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 _deque.h at BFME1 6583b3c1ff is the semantic source.
// Retail facts: Ghidra 00419F7C..00419F88 is a 12-byte thiscall wrapper;
// it calls the rowed 00419DF6 increment helper and returns the incoming this.
// That helper proves four pointer fields and a 16-byte element stride.
// BfmeE16 is the existing size-only stand-in used by the matched helper.
// Const/nonconst iterator traits fold to identical code, so no original
// iterator type or constness is claimed: retain the target address name.
#include <deque>
struct BfmeE16 { float x, y, z, w; };
struct Rva00419F7C : _STL::_Deque_iterator_base<BfmeE16> {
    Rva00419F7C &increment();
};
Rva00419F7C &Rva00419F7C::increment()
{
    _M_increment();
    return *this;
}

// The adjacent Ghidra body 00419F70..00419F7C has the same ABI but calls
// rowed 00419DD2: its +0x1c step and +0x70 buffer extent prove 28-byte
// elements. Reuse that helper's existing size-only BfmePod28 declaration;
// the original element identity and iterator traits remain unknown.
struct BfmePod28 { int a[7]; };
struct Rva00419F70 : _STL::_Deque_iterator_base<BfmePod28> {
    Rva00419F70 &increment();
};
Rva00419F70 &Rva00419F70::increment()
{
    _M_increment();
    return *this;
}
