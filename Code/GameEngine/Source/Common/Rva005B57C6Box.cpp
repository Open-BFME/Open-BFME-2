// cl: -Oy- -GR- -EHsc- /MD
// ?Run@Rva005B57C6Box@@QAEXPAD@Z @0x005B57C6 52B: scan-and-forward. Runs the
// imported sscanf over the string with the runtime table at 0xBE3878
// (outside all PE sections, named extern), capturing an int local and the
// slot itself, then forwards (local, slot, 1) to the pinned 3-arg callee.
// Targets read from retail REL32/DIR32; sscanf via stdio like the BlobCursor
// precedent.
#include <stdio.h>

extern char g_rva005B57C6Fmt[];

struct Rva005B57C6Box
{
	void M54ed(int code, char *s, int flag);
	void Run(char *s);
};

void Rva005B57C6Box::Run(char *s)
{
	int local;
	sscanf(s, g_rva005B57C6Fmt, &local, &s);
	M54ed(local, s, 1);
}
