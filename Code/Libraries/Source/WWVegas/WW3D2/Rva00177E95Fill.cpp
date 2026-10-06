// cl: /arch:SSE /G7 /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: float-triple fill at 0x177E95 (50B). Leaf: writes
// (x,y,z) from stack args into dst, advances dst by byte stride, loops
// over count with early-out on zero. Address-derived names.

// ?rva00177E95@@YAXPAMHMMMH@Z
void rva00177E95(float *dst, int stride, float x, float y, float z, int count)
{
	int n = count;
	if (n == 0)
		return;
	do {
		dst[0] = x;
		dst[1] = y;
		dst[2] = z;
		dst = (float *)((char *)dst + stride);
		--n;
	} while (n != 0);
}
