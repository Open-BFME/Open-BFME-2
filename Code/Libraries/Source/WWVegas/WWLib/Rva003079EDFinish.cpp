// ?rva003079ED@Rva003079ED@@QAEXXZ
// partial score=0.93 date=2026-10-04
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003079ED@Rva003079ED@@QAEXXZ @0x003079ED 63B
// Reset: nulls three words at +0x14/+0x18/+0x1C then swap-clears the
// vector at +4 via an empty temp (base ctor + swap + free-if-nonempty).
// Evidence: 63B ebp frame with 0x10 locals; three and [esi+x],0
// then lea ebp-1 push lea ebp-0x10 call 0x7FAEA (Vector_base ctor) then
// add esi,4 push lea ebp-0x10 call 0x3079C1 (vector swap) then
// cmp [ebp-0x10],0 je else push [ebp-0x10] call 0x30830 _free; callers
// 0x0032D554 0x0032F470 0x0032F84F 0x0041F095 unblocked.
// Vector element is BfmeE12: base ctor pins to 0x7FAEA; swap retails
// to 0x3079C1 (void* swap gen-alias ICF-twin, byte-identical 44B body).
#include <vector>

struct BfmeE12 { float x, y, z; };

class Rva003079ED
{
public:
    void rva003079ED();

private:
    int _pad0;
    _STL::vector<BfmeE12, _STL::allocator<BfmeE12> > m_vec04;
    int m_gap10;
    void *m_p14;
    void *m_p18;
    void *m_p1c;
};

void Rva003079ED::rva003079ED()
{
    m_p18 = 0;
    m_p14 = 0;
    m_p1c = 0;
    _STL::vector<BfmeE12, _STL::allocator<BfmeE12> > tmp;
    tmp.swap(m_vec04);
}
