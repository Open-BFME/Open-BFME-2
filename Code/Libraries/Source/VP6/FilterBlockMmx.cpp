// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d7330.md plus retail only.
// No decoder source was consulted.
//
// FilterBlock_mmx (retail 0x001D7330, 486 bytes): builds an 8x8 sub-pixel
// prediction block from two reference pointers (difference 0, 1, one line,
// one line minus 1 or one line plus 1) with the bilinear or bicubic filter
// bank, then widens the byte block into the int16 output. The bilinear bank
// is g_rva00DB81B0Weights (retail 0x00DB81B0, phase times 32); the bicubic
// bank is g_vp6BicubicTapsMmx (retail 0x00DB82B0, phase times 64).

extern const unsigned short g_rva00DB81B0Weights[8][16];

// Eight phases, each of four 16-bit weights replicated eight times for the MMX filters.
#define BFME_BICUBIC_TAP(w) w, w, w, w, w, w, w, w
#define BFME_BICUBIC_TAPS(a, b, c, d) { BFME_BICUBIC_TAP(a), BFME_BICUBIC_TAP(b), BFME_BICUBIC_TAP(c), BFME_BICUBIC_TAP(d) }
extern const short g_vp6BicubicTapsMmx[8][32] =
{
    BFME_BICUBIC_TAPS(0, 128, 0, 0),
    BFME_BICUBIC_TAPS(-4, 118, 16, -2),
    BFME_BICUBIC_TAPS(-7, 106, 34, -5),
    BFME_BICUBIC_TAPS(-8, 90, 53, -7),
    BFME_BICUBIC_TAPS(-8, 72, 72, -8),
    BFME_BICUBIC_TAPS(-7, 53, 90, -8),
    BFME_BICUBIC_TAPS(-5, 34, 106, -7),
    BFME_BICUBIC_TAPS(-2, 16, 118, -4),
};

extern "C" void __cdecl FilterBlock1d_h_mmx(const void *, void *, int, int, int, int, const void *);
extern "C" void __cdecl FilterBlock1d_hb8_mmx(const void *, void *, int, int, int, int, const void *);
extern "C" void __cdecl FilterBlock1d_v_mmx(const void *, void *, int, int, int, int, const void *);
extern "C" void __cdecl FilterBlock1d_vb8_mmx(const void *, void *, int, int, int, int, const void *);
extern "C" void __cdecl FilterBlock2d_mmx(const void *, void *, int, const void *, const void *);
extern "C" void __cdecl FilterBlock2dBil_mmx(const unsigned char *, unsigned char *, int, const void *, const void *);
extern "C" void __cdecl UnpackBlock_MMX(const unsigned char *, short *, unsigned int);

extern "C" void __cdecl FilterBlock_mmx(void *arg1, void *arg2, void *arg3,
    int stride, int weightsA, int weightsB, int mode)
{
    unsigned char scratch[256];
    int distance = (int)arg2 - (int)arg1;
    if (distance < 0)
    {
        void *temporary = arg1;
        arg1 = arg2;
        arg2 = temporary;
        distance = (int)arg2 - (int)arg1;
    }
    if (distance == 0)
        return;

    if (distance == 1)
    {
        if (mode != 0)
            FilterBlock1d_h_mmx(arg1, scratch, stride, distance, 8, 8,
                (const void *)((const unsigned char *)g_vp6BicubicTapsMmx + (weightsA << 6)));
        else
            FilterBlock1d_hb8_mmx(arg1, scratch, stride, 1, 8, 8,
                (const void *)((const unsigned char *)g_rva00DB81B0Weights + (weightsA << 5)));
    }
    else if (distance == stride)
    {
        if (mode != 0)
            FilterBlock1d_v_mmx(arg1, scratch, stride, stride, 8, 8,
                (const void *)((const unsigned char *)g_vp6BicubicTapsMmx + (weightsB << 6)));
        else
            FilterBlock1d_vb8_mmx(arg1, scratch, stride, stride, 8, 8,
                (const void *)((const unsigned char *)g_rva00DB81B0Weights + (weightsB << 5)));
    }
    else if (distance == stride - 1)
    {
        if (mode != 0)
            FilterBlock2d_mmx((const unsigned char *)arg1 - 1, scratch, stride,
                (const void *)((const unsigned char *)g_vp6BicubicTapsMmx + (weightsA << 6)),
                (const void *)((const unsigned char *)g_vp6BicubicTapsMmx + (weightsB << 6)));
        else
            FilterBlock2dBil_mmx((const unsigned char *)arg1 - 1, scratch, stride,
                (const void *)((const unsigned char *)g_rva00DB81B0Weights + (weightsA << 5)),
                (const void *)((const unsigned char *)g_rva00DB81B0Weights + (weightsB << 5)));
    }
    else if (distance == stride + 1)
    {
        if (mode != 0)
            FilterBlock2d_mmx(arg1, scratch, stride,
                (const void *)((const unsigned char *)g_vp6BicubicTapsMmx + (weightsA << 6)),
                (const void *)((const unsigned char *)g_vp6BicubicTapsMmx + (weightsB << 6)));
        else
            FilterBlock2dBil_mmx((const unsigned char *)arg1, scratch, stride,
                (const void *)((const unsigned char *)g_rva00DB81B0Weights + (weightsA << 5)),
                (const void *)((const unsigned char *)g_rva00DB81B0Weights + (weightsB << 5)));
    }
    UnpackBlock_MMX(scratch, (short *)arg3, 8);
}
