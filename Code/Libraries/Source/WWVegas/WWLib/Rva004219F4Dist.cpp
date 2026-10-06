// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva004219F4DistSquared@@YAMPBM0@Z @0x004219F4 34B
// Squared 2D distance via x87: dx from +0x38/+0 and dy from +0x3C/+4 then
// dy*dy+dx*dx. Evidence: unlock lane; callers at 0x00421A20 0x00421A2C plus
// five in 0x0042550E compare two results; prev/next are /O1 STL neighbours.
float __cdecl Rva004219F4DistSquared(const float *small, const float *big)
{
	float dx = big[14] - small[0];
	float dy = big[15] - small[1];
	return dy * dy + dx * dx;
}
