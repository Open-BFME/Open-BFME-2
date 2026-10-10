// cl: /MD
// ?Rva0010410FWrap@@YAMM@Z, retail 0x0010410F, 61 bytes.
// Evidence: unlock lane, callers at 0x00104167 and 0x00104533, callee Rva000930C0 fmod wrapper, float const g_00BC746C.
// Retail float at RVA 0x7C746C (6.2831855f, exactly 0x40C90FDB): used as a
// literal so the TU links self-contained instead of extern-referencing it.
float __cdecl Rva000930C0(float lhs, float rhs);

float __cdecl Rva0010410FWrap(float a)
{
	if (0.0f > a)
		return 6.2831855f - Rva000930C0(0.0f - a, 6.2831855f);
	else
		return Rva000930C0(a, 6.2831855f);
}
