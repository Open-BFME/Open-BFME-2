// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?GetObjectInfo@AptMyHero@@QAEPAUBfmePod8@@H@Z @0x005B0E9F 71B
// Evidence: callers 0x005B1046 (uses +4 as float for setOrientation) and
// 0x005B1E95 (uses +0 as int arg) prove 8-byte element {int; float}.
// Vector at +0x15c (start/finish diff sar 3 = /8). Static empty zero
// (int 0 via and [m],0; float 0.0f via xorps/movss) with guard byte,
// returned on out-of-range. Matches BfmePod size-only convention.
#include <vector>

struct BfmePod8
{
public:
	int a; // +0x00
	float b; // +0x04
};

// g_00E06460: matched references place it at VA 0xe06460 (zero-filled; a plain-data view).
BfmePod8 g_00E06460;
extern int g_00E06468;
// g_00E06468: matched references place it at VA 0xe06468 (zero-filled .bss).
int g_00E06468;

#include "../../../../GameEngine/Include/GameClient/AptMyHero.h"

// The canonical header keeps the +0x15C vector opaque (field15C); this TU
// reads it as the STLport vector of 8-byte entries the body indexes.
static __forceinline _STL::vector<BfmePod8> &AptMyHeroObjectInfo(AptMyHero *hero)
{
    return *reinterpret_cast<_STL::vector<BfmePod8> *>(hero->field15C);
}

BfmePod8 *AptMyHero::GetObjectInfo(int idx)
{
    if (!(g_00E06468 & 1)) {
        g_00E06468 |= 1;
        g_00E06460.a = 0;
        g_00E06460.b = 0.0f;
    }
    if ((unsigned int)idx >= AptMyHeroObjectInfo(this).size())
        return &g_00E06460;
    return &AptMyHeroObjectInfo(this)[idx];
}
