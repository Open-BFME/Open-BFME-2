// cl: /MD
// ?rva002B4650@Rva002B4650@@QAEHXZ @0x002B4650 30B: __thiscall int gate.
// Returns 1 only when the 0x2B2BAA guard passes and the 0x2B3DB2 measure
// comes back zero (retained in eax: test/jne fail, inc eax on the zero
// path). Evidence: retail
//   push esi; mov esi,ecx; call 0x2B2BAA; test al,al; je fail
//   mov ecx,esi; call 0x2B3DB2; test eax,eax; jne fail
//   inc eax; pop esi; ret; fail: xor eax,eax; pop esi; ret
// Boundary: Ghidra FUN_006b3db2-adjacent 30B; successor 0x2B466E opens with
// push ebp. Names are address-derived.
class Rva002B4650
{
public:
	bool rva002B2BAA();
	int rva002B3DB2();
	int rva002B4650();
	int rva002B3DD0();
};

extern int g_Va00DBA4E4;

int Rva002B4650::rva002B4650()
{
	if (rva002B2BAA()) {
		int n = rva002B3DB2();
		if (n == 0)
			return ++n;
	}
	return 0;
}

// ?rva002B3DD0@Rva002B4650@@QAEHXZ @0x002B3DD0 20B: the 0x2B3DB2 measure
// rounded up to whole units of g_Va00DBA4E4 (lea eax,[eax+ecx-1]; xor edx;
// div). Callers 0x00574306 0x005750AA. Summing the measure first, in
// unsigned arithmetic, gives retail's lea operand order.
int Rva002B4650::rva002B3DD0()
{
	return ((unsigned int)rva002B3DB2() + (unsigned int)g_Va00DBA4E4 - 1) / (unsigned int)g_Va00DBA4E4;
}
