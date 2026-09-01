// cl: /O1 /arch:SSE2
// The clamp template from Code/GameEngine/Include/Precompiled/PreRTS.h,
// instantiated for Real. Its argument order is (lo, val, hi), not the
// (val, min, max) that WWMath::Clamp takes, which is what the retail body's
// comparison operands identify.

template <class NUM>
inline NUM clamp(NUM lo, NUM val, NUM hi)
{
    if (val < lo)
        return lo;
    else if (val > hi)
        return hi;
    else
        return val;
}

template float clamp<float>(float lo, float val, float hi);
