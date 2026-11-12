// cl: /O2
// 0x007EBAA0: allocate the 0x14-byte FESL diagnostic singleton at
// 0x0130A5A0 if it is still null.

void *Gen007F0130(unsigned int size);

extern void *g_bfmeVftTDA[];
// The +4 slot is the rowed Rva006587B0Print (BfmeConv1321.cpp, 0x006587B0).
void printText(void *p, const char *text);
extern int g_FeslDiagReporter;

void Rva007EBAA0(void)
{
	if (g_FeslDiagReporter)
		return;
	void *p = Gen007F0130(0x14);
	if (p)
	{
		*((int *)p + 2) = 0;
		*((int *)p + 3) = 0;
		*((int *)p + 4) = 0;
		*(int *)p = (int)g_bfmeVftTDA;
		*((int *)p + 1) = (int)&printText;
		g_FeslDiagReporter = (int)p;
	}
	else
		g_FeslDiagReporter = 0;
}

// ?g_bfmeVftTDA@@3PAPAXA: the data ledger's global at VA 0xce157c, the 6-slot
// vftable these FESL diag objects install (four units store it). It held one
// word, retail's slot-0 address as a bare integer (no relocation), so a
// relinked image got a stale code address and five slots of whatever followed.
// Own the complete initialized table instead (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures; the type keeps
// the symbol's mangling.
extern "C" {
void __identifier("?setFields_007EB760@Rva007EB8B0Log@@UAEXHH@Z")();
void __identifier("?bfmeGoELF@BfmeThingELF@@QAEXPAX@Z")();
void __identifier("?Rva007EB8B0@@YAXPAVRva007EB8B0Log@@IPBDZZ")();
void __identifier("?assertFailed@Rva007EB8B0Log@@QAEHPBD0H@Z")();
void __identifier("?errorFrom@Rva007EB8B0Log@@QAEHHPBD0H@Z")();
void __identifier("?bfmeDelTQD@BfmeThingTQD@@QAEPAXE@Z")();
}
void *g_bfmeVftTDA[6] = {
	(void *)&__identifier("?setFields_007EB760@Rva007EB8B0Log@@UAEXHH@Z"), //  0 0x006586F0
	(void *)&__identifier("?bfmeGoELF@BfmeThingELF@@QAEXPAX@Z"), //  1 0x00658710
	(void *)&__identifier("?Rva007EB8B0@@YAXPAVRva007EB8B0Log@@IPBDZZ"), //  2 0x00658820
	(void *)&__identifier("?assertFailed@Rva007EB8B0Log@@QAEHPBD0H@Z"), //  3 0x00658890
	(void *)&__identifier("?errorFrom@Rva007EB8B0Log@@QAEHHPBD0H@Z"), //  4 0x00658930
	(void *)&__identifier("?bfmeDelTQD@BfmeThingTQD@@QAEPAXE@Z")  //  5 0x006587E0
};
