// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva005B0E9F@Rva005B0E9F@@QAEPAUBfmePod8@@H@Z @0x005B0E9F 71B
// Evidence: callers 0x005B1046 (uses +4 as float for setOrientation) and
// 0x005B1E95 (uses +0 as int arg) prove 8-byte element {int; float}.
// Vector at +0x15c (start/finish diff sar 3 = /8). Static empty zero
// (int 0 via and [m],0; float 0.0f via xorps/movss) with guard byte,
// returned on out-of-range. Matches BfmePod size-only convention.
#include <vector>

struct BfmePod8 { int a; float b; };

// g_00E06460: matched references place it at VA 0xe06460 (zero-filled; a plain-data view).
BfmePod8 g_00E06460;
extern int g_00E06468;
// g_00E06468: matched references place it at VA 0xe06468 (zero-filled .bss).
int g_00E06468;

class Rva005B0E9F {
    char _pad[0x15c];
    _STL::vector<BfmePod8> _vec;
public:
    BfmePod8 *rva005B0E9F(int idx);
};

BfmePod8 *Rva005B0E9F::rva005B0E9F(int idx)
{
    if (!(g_00E06468 & 1)) {
        g_00E06468 |= 1;
        g_00E06460.a = 0;
        g_00E06460.b = 0.0f;
    }
    if ((unsigned int)idx >= _vec.size())
        return &g_00E06460;
    return &_vec[idx];
}
