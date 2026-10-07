// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// 0x004FF33D (38B): float select on two int indirections. Returns 0.0 when
// *a equals *b, else the 1.0f at 0x00BBB8D8, through an SSE xorps/movss
// plus x87 fld return. Honest address-derived name on a free function.

float __stdcall Rva004FF33D(int *a, int *b)
{
	return (*a == *b) ? 0.0f : 1.0f;
}
