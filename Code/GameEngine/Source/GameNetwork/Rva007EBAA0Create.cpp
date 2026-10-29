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

// ?g_bfmeVftTDA@@3PAPAXA: the data ledger's global at VA 0xce157c (the vftable
// these FESL diag objects install).
void *g_bfmeVftTDA[1] = { (void *)10847984 };
