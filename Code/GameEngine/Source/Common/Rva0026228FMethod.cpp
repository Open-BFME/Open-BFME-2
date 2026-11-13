// cl: /DNDEBUG /MD
//
// ?rva0026228F@Rva0026228F@@QAEXHH@Z, retail 0x0026228F, 26 bytes.
// Thiscall leaf with two int-sized args: push arg2 then FLT_MAX from global
// 0x00BBB8E0 through a reused push slot then arg1 into virtual slot 0x34.
// Outer ret 8. Honest address-derived owner and name; slot identity unproven.
// No direct named callees.

extern float g_Va00BBB8E0;

#define Gbl00BBB8E0 g_Va00BBB8E0

#include "../../Include/Common/Rva0026228F.h"

void Rva0026228F::rva0026228F(int a, int b)
{
	s34(a, Gbl00BBB8E0, b);
}
