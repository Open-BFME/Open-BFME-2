// cl: -Oy- -GR- -EHsc- /MD
// ?Run@Rva005B57C6Box@@QAEXPAD@Z @0x005B57C6 52B: scan-and-forward. Runs the
// imported sscanf over the string with the runtime table at 0xBE3878
// (outside all PE sections, named extern), capturing an int local and the
// slot itself, then forwards (local, slot, 1) to the pinned 3-arg callee.
// Targets read from retail REL32/DIR32; sscanf via stdio like the BlobCursor
// precedent.
#include <stdio.h>

// g_rva005B57C6Fmt was the retail address alias (RVA 0x007E3878) of the constant "%d %d"; the literal is the source.

// 0x005B54ED is rowed as Rva005B566B::rva005B54ED(unsigned, unsigned, bool).
#include "../../Include/Common/Rva005B566B.h"

struct Rva005B57C6Box
{
	void Run(char *s);
};

void Rva005B57C6Box::Run(char *s)
{
	int local;
	sscanf(s, "%d %d", &local, &s);
	((Rva005B566B *)this)->rva005B54ED(local, (unsigned int)s, true);
}
