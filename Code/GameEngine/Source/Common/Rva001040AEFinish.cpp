// ?Rva001040AESub@@YAXPAMMMPBM@Z
// ?Rva001040AESub@@YAXPAMMMPBM@Z 0x001040AE 39B
// cl: /MD
// __cdecl 2-float subtraction helper: dest[0]=x-src[0], dest[1]=y-src[1].
// Evidence: callers ClosestPointOnLineSegment 0x006B3100 (x2), 0x00104359 (x2),
// 0x002F8B00 and 0x0030B3D1. Complete comparison siblings precede at 0x10404E/0x104079.
// Forming both results into a local 2-float vector before the stores reproduces
// retail's dx-then-dy xmm0/xmm1 order.
void __cdecl Rva001040AESub(float *dest, float x, float y, const float *src)
{
	float d[2];
	d[0] = x - src[0];
	d[1] = y - src[1];
	dest[0] = d[0];
	dest[1] = d[1];
}

// Reference semantics: BFME1 Bfme5NinetyTwo.cpp at
// 9cbfb551fe20dae985f91f2319d8997287b6a705 (unchanged from 40e7f2f).
// Retail 0x00104079..0x001040AE is a cdecl comparison of two float pairs.
// The original type and function name remain unknown; use only the native
// float[2] access contract, consistent with the adjacent subtraction above.
bool Rva00104079PairDiffers(const float *left, const float *right)
{
    int equal;
    if (left[0] == right[0] && left[1] == right[1])
        equal = 1;
    else
        equal = 0;
    unsigned char same = (unsigned char)equal;
    return same == 0;
}

// The complete native predecessor 0x0010404E..0x00104079 compares the same
// primitive float-pair access contract and returns a full integer zero/one.
// This is not the interior false-return fragment at 0x00104076.
int Rva0010404EPairEqual(const float *left, const float *right)
{
    if (left[0] == right[0] && left[1] == right[1])
        return 1;
    return 0;
}
