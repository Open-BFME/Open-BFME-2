// cl: /O1 /arch:SSE2
// Coord3D::GetLengthEstimate at 0x00003ACE.
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

struct Coord3DBase
{
    float x;
    float y;
    float z;
};

class Coord3D : public Coord3DBase
{
public:
    float GetLengthEstimate() const;
};

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
