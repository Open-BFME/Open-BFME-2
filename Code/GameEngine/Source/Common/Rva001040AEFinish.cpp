// ?Rva001040AESub@@YAXPAMMMPBM@Z
// ?Rva001040AESub@@YAXPAMMMPBM@Z 0x001040AE 39B
// cl: /MD
// __cdecl 2-float subtraction helper: dest[0]=x-src[0], dest[1]=y-src[1].
// Evidence: callers ClosestPointOnLineSegment 0x006B3100 (x2), 0x00104359 (x2),
// 0x002F8B00 and LINK BONUS 0x0030B3D1; prev 0x00104076, next 0x001042C1.
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
