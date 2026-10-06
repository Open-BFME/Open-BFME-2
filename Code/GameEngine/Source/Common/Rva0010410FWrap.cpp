// cl: /MD
// ?Rva0010410FWrap@@YAMM@Z, retail 0x0010410F, 61 bytes.
// Evidence: unlock lane, callers at 0x00104167 and 0x00104533, callee Rva000930C0 fmod wrapper, float const g_00BC746C.
extern float g_00BC746C;
float __cdecl Rva000930C0(float lhs, float rhs);

float __cdecl Rva0010410FWrap(float a)
{
	if (0.0f > a)
		return g_00BC746C - Rva000930C0(0.0f - a, g_00BC746C);
	else
		return Rva000930C0(a, g_00BC746C);
}
