// cl: /MD /Oi-
// ?Rva004D6B6E@@YAMM@Z @0x004D6B6E 47B, callers 0x0025EDCB and 0x004D6BC0.
// Free __cdecl float angle: pi/2 when value <= 0, else twice atan(12 / value).
// Target evidence: SSE compare (movss/comiss) against the pooled 0.0 at
// 0x00BBAEAC, x87 divide of the pooled 12.0 at 0x00BC2924, double atan via
// the msvcr71 thunk, fadd st0,st0 doubling, pooled pi/2 at 0x00BC2A24 on the
// low path. Donor carried: BFME1 Code/GameEngine/Source/Common/
// Bfme5SixtyNine.cpp bfmeAngle (same shape, __stdcall, different globals).
// Structural inference: the doubling is a + a on the float result, which
// pops one argument dword before the fadd as retail does.

extern "C" double __cdecl atan(double value);
extern "C" double __cdecl tan(double value);

// ?Rva004D6B3A@@YAMM@Z @0x004D6B3A 52B, callers 0x0025EDA9 and 0x004D6BB1:
// the inverse of 0x004D6B6E, 12 / tan(value / 2), or the pooled 1e10 at
// 0x00BE118C when the tangent is zero. Target evidence: x87 multiply by the
// pooled 0.5 at 0x00BC26F0, double tan via the msvcr71 thunk 0x0062993A,
// fldz/fucomip zero test, fdivr of the pooled 12.0.
// Structural inference: the halved angle is its own float local, which
// keeps fld st(1) ahead of both argument pops as retail.
float __cdecl Rva004D6B3A(float value)
{
	float half = value * 0.5f;
	float t = (float)tan(half);
	if (t != 0.0f)
		return 12.0f / t;
	return 1.0e10f;
}

float __cdecl Rva004D6B6E(float value)
{
	if (value > 0.0f)
	{
		float a = (float)atan(12.0f / value);
		return a + a;
	}
	return 1.5707964f;
}

// ?Rva004D6B9D@@YAMM@Z @0x004D6B9D 27B, caller 0x0025ED98: 0x004D6B3A taking
// degrees. Target evidence: SSE multiply by the pooled 0.017453292 at
// 0x00BBB8D0 (PI / 180.0f with the float PI) before the call.
float __cdecl Rva004D6B9D(float value)
{
	return Rva004D6B3A(value * (3.14159265359f / 180.0f));
}

// ?Rva004D6BB8@@YAMM@Z @0x004D6BB8 21B, caller 0x0025EDBA: the same angle in
// degrees. Target evidence: forwards its float to 0x004D6B6E and multiplies
// by the pooled 57.2957763671875 at 0x00BBB8CC, which is 180.0f / PI with
// the float PI rounded once (not the nearest float to 180/pi).
float __cdecl Rva004D6BB8(float value)
{
	return Rva004D6B6E(value) * (180.0f / 3.14159265359f);
}
