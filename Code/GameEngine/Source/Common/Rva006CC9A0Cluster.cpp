// cl: /DNDEBUG /MD /EHs-c-
// ?Rva006CC9A0@@YAXHHH@Z @ 0x006CC9A0 (65B).
//
// The "add input" sibling of Rva006CC950SetMousePos (same TU pattern, same
// three Apt globals at 0x00E17700 / 0x00E176D4 / 0x00E176D0): bails with the
// retail warning when Apt is not initialized, returns quietly when the
// suppression flag or the object pointer is null, otherwise forwards the
// three arguments to the Apt input packer 0x006E3530 on that object.
//
// The warning text is retail's (VA 0x00CE8EFC) including its trailing newline.
// 0x006E3530 is the unnamed three-int thiscall member of the same class the
// near file already declares (Rva006E34D0); only its call is reproduced here.

void __cdecl Rva006CC110Log(int level, const char *fmt, ...);

struct Rva006CC9F0Input { int first,second; unsigned char flag; char pad09[3]; int eventId; };
#include "../../../Libraries/Source/Apt/Rva006E34D0.h"

extern int g_bfmeAptInitAtE17700;
// g_bfmeAptInitAtE17700: matched references place it at VA 0xe17700 (zero-filled .bss).
extern int g_bfmeAptFlagAtE176D4;
// g_bfmeAptFlagAtE176D4: matched references place it at VA 0xe176d4 (zero-filled .bss).
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
// g_bfmeAptPtrAtE176D0: matched references place it at VA 0xe176d0 (zero-filled .bss).

void Rva006CC9A0(int a, int b, int c)
{
	if (!g_bfmeAptInitAtE17700)
		return Rva006CC110Log(0, "WARNING: trying to add input when Apt not initalized\n");
	if (g_bfmeAptFlagAtE176D4)
		return;
	Rva006E34D0 *p = g_bfmeAptPtrAtE176D0;
	if (!p)
		return;
	p->rva006E3530(a, b, c);
}

// Native6CC9F0..6CCA42 RET is82B; aligned CC padding surrounds it.
// This input sibling uses the same globals and full warning as6CC9A0.
// The explicit sixteen-byte copy proves a by-value record at both sides of
// call6E4480; its former four-scalar declaration lost this caller ABI.
void Rva006CC9F0(Rva006CC9F0Input input)
{
 if (!g_bfmeAptInitAtE17700)
  return Rva006CC110Log(0, "WARNING: trying to add input when Apt not initalized\n");
 if (g_bfmeAptFlagAtE176D4) return;
 Rva006E34D0 *p=g_bfmeAptPtrAtE176D0;
 if (!p) return;
 p->rva006E4480(input);
}
