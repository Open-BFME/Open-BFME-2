// cl: /O1 /MD
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
};

int Rva002B4650::rva002B4650()
{
	if (rva002B2BAA()) {
		int n = rva002B3DB2();
		if (n == 0)
			return ++n;
	}
	return 0;
}
