// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD
// BFME 1 donor: game/GameEngine/Source/Common/BfmeConv982.cpp at
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20; Rva007845D0Ratio logic.
// Target identity remains address-based. Native direct calls at RVA A9630,
// A9659 and A96A1 consume XMM0. The preceding RET ends at A925D and
// this closed 69-byte body ends at the rowed getter A92A2.
// Native literals BC93B4/BCF628/BBB8D8 are 0.0001f/0.01f/1.0f.
// Keep this helper private: MSVC optimizes a TU-local float return to XMM0
// when the caller is visible. A public float ABI would return in ST0.
#include <math.h>

static float rva000A925D(float denominator, float numerator)
{
    if (denominator < 0.0001f)
        return 1.0f;
    if (fabs(numerator - denominator) < 0.01f)
        return 1.0f;
    return numerator / denominator;
}

// This unclaimed emission context exposes the private return convention to
// the compiler. It is not a recovered retail caller or a recovery row.
// ?rva000A925DEmissionContext absent-from-retail
void rva000A925DEmissionContext(float denominator, float numerator, float *out)
{
    *out = rva000A925D(denominator, numerator);
}
