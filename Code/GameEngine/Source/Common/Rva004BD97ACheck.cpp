// cl: /O1 /DNDEBUG /MD
//
// ?rva004BD97A@@YGHHH@Z @ 0x004BD97A (39B).
// Temp plus two calls returning the arg: build a 4-byte local, run the
// pinned cdecl 0x006291AE on (&tmp,0,4), then the pinned thiscall 0x002CF0F0
// on (arg as this) with (&tmp), returning arg. Evidence: retail pushes 4 /
// lea tmp / push 0 / push tmp for the first call (caller-cleans cdecl), mov
// ecx,arg for the second call's this, no add-esp after it (callee-cleans
// thiscall), mov eax,arg for return; boundary prev ret at 0x004BD979 and
// next proc at 0x004BD9A1. Pins are RVAs.

class Rva004BD97AArg
{
public:
	void helper(int tmpAddr);
};

void __cdecl rva006291AE(int a, int b, int c);
int __stdcall rva004BD97A(int arg)
{
	int tmp;
	rva006291AE((int)&tmp, 0, 4);
	((Rva004BD97AArg *)arg)->helper((int)&tmp);
	return arg;
}
