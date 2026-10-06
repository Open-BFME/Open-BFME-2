// ?rva002B6C9F@Rva002B6C9F@@QAE_NHHH@Z
// partial score=0.97 date=2026-10-06
// cl: /O1 /MD
// Range-11 sibling pair sharing the (int,int,int) bool probe shape.
// ?rva002B6C9F@Rva002B6C9F@@QAE_NHHH@Z @0x002B6C9F 70B: __thiscall bool
// probe. Fails on a failed rowed 0x2B2C40 check or a failed pinned
// 0x2B6BCF stage; otherwise returns the rowed 0x3193EC check on the
// third argument normalized through != 0.
// Evidence: retail
//   push ebp; mov ebp,esp; push esi; push [ebp+0x10]; mov esi,ecx
//   push [ebp+8]; call 0x2B2C40; test al,al; jne DO
//   xor al,al; jmp END
//   DO: lea eax,[ebp+8]; push eax; push [ebp+0x10]; mov ecx,esi
//   push [ebp+0xC]; push [ebp+8]; call 0x2B6BCF; test al,al; je FAIL
//   push [ebp+8]; mov ecx,[ebp+0x10]; call 0x3193EC
//   test al,al; setne al
//   END: pop esi; pop ebp; ret 0xC
//   FAIL: shared mid xor (backward je). Flat guards place the first
//   xor mid-function; later fails jump back to it.
// ?rva002B6CE5@Rva002B6CE5@@QAE_NHHH@Z @0x002B6CE5 51B: shorter sibling.
// Returns the 0x2B2C40 check ANDed with the normalized 0x2B6BCF stage;
// the AND form shares the bare-pops exit (al still 0 from the test).
// Evidence: retail
//   (same prologue + 0x2B2C40 call); test al,al; je EXIT
//   (same 0x2B6BCF setup + call); test al,al; setne al
//   EXIT: pop esi; pop ebp; ret 0xC
// Boundary: 70B [0x2B6C9F,0x2B6CE5) + 51B [0x2B6CE5,0x2B6D18); prev ret,
// next prologue. Names address-derived except rowed callees and the
// 0x2B6BCF pin.
struct Arg54;

class Rva002B2C40
{
public:
	bool rva002B2C40(Arg54 *a, Arg54 *b);
};

class Rva002B6BCF
{
public:
	bool rva002B6BCF(int a1, int a2, int a3, int *pa1);
};

class Rva003193EC
{
public:
	bool rva003193EC(int v);
};

class Rva002B6C9F
{
public:
	bool rva002B6C9F(int a1, int a2, int a3);
	bool rva002B6CE5(int a1, int a2, int a3);
};

bool Rva002B6C9F::rva002B6C9F(int a1, int a2, int a3)
{
	if (!((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)a1, (Arg54 *)a3))
		return false;
	else if (!((Rva002B6BCF *)this)->rva002B6BCF(a1, a2, a3, &a1))
		return false;
	else
		return ((Rva003193EC *)a3)->rva003193EC(a1) != false;
}

bool Rva002B6C9F::rva002B6CE5(int a1, int a2, int a3)
{
	return ((Rva002B2C40 *)this)->rva002B2C40((Arg54 *)a1, (Arg54 *)a3)
		&& ((Rva002B6BCF *)this)->rva002B6BCF(a1, a2, a3, &a1);
}
