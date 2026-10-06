// ?rva004216A2@@YAXPAMPBM1@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /arch:SSE /G7 /ICode/GameEngine/Source/Common
// Target evidence: retail reads two floats from the second pointer, adds them to floats at offsets 0x18 and 0x1C from the third pointer, writes x/y to the first pointer, and sets z to zero. Caller argument types remain address-named.

void __cdecl rva004216A2(float *out, const float *base, const float *other)
{
	float y = base[1] + other[7];
	float x = base[0] + other[6];
	out[1] = y;
	out[0] = x;
	out[2] = 0.0f;
}
