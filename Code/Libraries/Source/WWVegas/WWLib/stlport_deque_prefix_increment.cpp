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
