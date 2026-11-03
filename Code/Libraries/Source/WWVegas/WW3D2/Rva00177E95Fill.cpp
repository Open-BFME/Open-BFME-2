// cl: /arch:SSE /G7 /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: float-triple fill at 0x177E95 (50B). Leaf: writes
// (x,y,z) from stack args into dst, advances dst by byte stride, loops
// over count with early-out on zero. Address-derived names.

// ?rva00177E95@@YAXPAMHMMMH@Z
void rva00177E95(float *dst, int stride, float x, float y, float z, int count)
{
	int remaining = count;
	if (remaining == 0)
		return;
	do {
		dst[0] = x;
		dst[1] = y;
		dst[2] = z;
		dst = (float *)((char *)dst + stride);
		--remaining;
	} while (remaining != 0);
}

// 0x00177EC7..0x00177F0D (70B): copy-then-flip of a float pair. The jnp at
// 0x00177EE7 targets 0x00177F00, the else arm (x = 1.0f), which an earlier
// row had taken for a separate 13B function: it is this body's tail.
struct Rva00177EC7Pair
{
	Rva00177EC7Pair &operator=(const Rva00177EC7Pair &that)
	{
		x = that.x;
		y = that.y;
		return *this;
	}
	float x;
	float y;
};

// ?rva00177EC7@@YAXPAURva00177EC7Pair@@AAU1@@Z
void rva00177EC7(Rva00177EC7Pair *out, Rva00177EC7Pair &value)
{
	*out = value;
	if (value.x != 0.0f) {
		value.x = 0.0f;
		value.y = 1.0f - value.y;
	} else {
		value.x = 1.0f;
	}
}
