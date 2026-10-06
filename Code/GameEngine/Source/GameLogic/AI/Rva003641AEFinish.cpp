// cl: /DNDEBUG /MD
//
// ?Rva003641AEClamp@@YGHMM@Z @0x003641AE (68B).
// Clamp a scaled product into [1,128]: the product of the two float factors
// and the two globals is rounded to nearest via an x87 fld/fistp helper, then
// clamped.  Evidence: callers 0x00364FBA and 0x0036596A; globals 0x00BC9D14
// and 0x00C17274 are the float factors; IAT ceil at 0x00BBA578.
// The double accumulator keeps retail's x87 operand order (fld b first,
// fmul g1, fmul a, fmul g2); a plain float chain is reassociated by the
// compiler.  The fistp helper is required because a plain (int) cast emits
// _ftol2 under /O1.

extern float g_00BC9D14;
extern float g_00C17274;

extern "C" __declspec(dllimport) double __cdecl ceil(double v);

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

int __stdcall Rva003641AEClamp(float a, float b)
{
	double d = b;
	b = (float)ceil((a * (d * g_00BC9D14)) * g_00C17274);
	int i = fast_float2long_round(b);
	if (i < 1)
		i = 1;
	if (i > 128)
		i = 128;
	return i;
}
