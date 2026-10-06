// ?rva002B6D18@Rva002B6D18@@QAE_NHHHH@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD
// ?rva002B6D18@Rva002B6D18@@QAE_NHHHH@Z @0x002B6D18 109B: __thiscall bool
// probe of the 6C9F family with four args. Passes the rowed 0x2B2C40
// check and two pinned 0x2B6BCF stages (by &a3, then by &a1 with rotated
// args), then checks the rowed 0x3193EC on the larger of a1/a3 with the
// absolute difference, normalizing through an explicit false/true pair.
// Evidence: retail
//   push ebp; mov ebp,esp; push ebx; mov ebx,[ebp+8]; push esi; push edi
//   mov edi,[ebp+0x10]; push edi; push ebx; mov esi,ecx; call 0x2B2C40
//   test al,al; je FAIL
//   lea eax,[ebp+0x10]; push eax; push edi; push [ebp+0xC]; mov ecx,esi
//   push ebx; call 0x2B6BCF; test al,al; je FAIL
//   lea eax,[ebp+8]; push eax; push ebx; push [ebp+0x14]; mov ecx,esi
//   push edi; call 0x2B6BCF; test al,al; je FAIL
//   mov eax,[ebp+0x10]; mov ecx,[ebp+8]; cmp eax,ecx; jle ELSE
//   sub eax,ecx; push eax; mov ecx,edi; jmp CALL
//   ELSE: sub ecx,eax; push ecx; mov ecx,ebx
//   CALL: call 0x3193EC; test al,al; jne TRUE
//   FAIL: xor al,al; jmp END; TRUE: mov al,1
//   END: pop edi; pop esi; pop ebx; pop ebp; ret 0x10
// The else-if chain shares the mid xor (later fails jump back to the
// first); the final if-not/return-true keeps TRUE after FAIL.
// Boundary: 109B [0x2B6D18,0x2B6D85); prev ret, next prologue. Names
// address-derived except rowed callees and the 0x2B6BCF pin.
struct Arg54;

class Rva002B2C40
{
public:
	bool rva002B2C40(Arg54 *a, Arg54 *b);
};

class Rva002B6BCF
{
public:
	char rva002B6BCF(int a1, int a2, int a3, int *pa);
};

class Rva003193EC
{
public:
	bool rva003193EC(int v);
};

class Rva002B6D18
{
public:
	bool rva002B6D18(int a1, int a2, int a3, int a4);
};

bool Rva002B6D18::rva002B6D18(int a1, int a2, int a3, int a4)
{
	int y = a3, x = a1;
	if (!((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)x, (Arg54 *)y))
		goto fail;
	if (!((Rva002B6BCF *)this)->rva002B6BCF(x, a2, y, &a3))
		goto fail;
	if (!((Rva002B6BCF *)this)->rva002B6BCF(y, a4, x, &a1))
		goto fail;
	{
		int diff;
		Rva003193EC *on;
		if (a3 > a1) {
			diff = a3 - a1;
			on = (Rva003193EC *)a3;
		}
		else {
			diff = a1 - a3;
			on = (Rva003193EC *)a1;
		}
		if (on->rva003193EC(diff))
			goto trueret;
	}
fail:
	return false;
trueret:
	return true;
}
