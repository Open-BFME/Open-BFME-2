// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Coord3D::GetLengthEstimate and Coord3D::lengthEstimate at 0x00003ACE.
//
// Retail inlines the 2D estimate three times - once for the comparison and
// once inside each arm - which is what the fifteen fabs calls in the body are:
// four per 2D estimate plus one for z, three times over. MSVC 7.1 will not do
// that from coord3d.cpp: at /O1 it calls the out-of-line 0x000037D1, and /Ob2
// does not change its mind about a 108-byte callee. So the body lives in its
// own unit, which leaves coord3d.cpp and its 68 rows untouched.
//
// The expansion has to be TEXTUAL. A __forceinline GetLengthEstimate2D inlines
// the same instructions but leaves the compiler holding z in a third stack
// slot across the second arm - eleven bytes of movss spill and reload that
// retail does not have - and it does so whether the callee is written as an
// if/return or as a ternary. Spelling the estimate out as a macro is the only
// form tried that reproduces retail's two-slot frame.

#include <math.h>

// The companion view, not Coord3D.h (it takes that guard, so it
// precedes Coord3DBase.h): it also declares lengthEstimate, which retail
// exports alongside GetLengthEstimate.
#include "../../../Include/Lib/Coord3DCtorView.h"

#include "../../../Include/Lib/Coord3DBase.h"

static const float length_estimate_factor = 0.25f;

#define ESTIMATE_2D                                                           \
    (fabs(x) > fabs(y) ? (float)(fabs(x) + length_estimate_factor * fabs(y))     \
                       : (float)(fabs(y) + length_estimate_factor * fabs(x)))

float Coord3D::GetLengthEstimate() const
{
    if (ESTIMATE_2D > fabs(z)) {
        return (float)(ESTIMATE_2D + length_estimate_factor * fabs(z));
    }
    return (float)(fabs(z) + length_estimate_factor * ESTIMATE_2D);
}

// Zero Hour's lower-case API carries the same estimate. Retail exports it at 0x00003ACE too:
// /OPT:ICF folded the identical body onto GetLengthEstimate's.
float Coord3D::lengthEstimate() const
{
    if (ESTIMATE_2D > fabs(z)) {
        return (float)(ESTIMATE_2D + length_estimate_factor * fabs(z));
    }
    return (float)(fabs(z) + length_estimate_factor * ESTIMATE_2D);
}
