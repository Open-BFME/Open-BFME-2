// cl: /O1 /MD
// ?rva002B3F9F@@YAXPAXH@Z @0x002B3F9F 52B: resolve, clear, tail-release.
// Same resolve-then-act family as the banked 0x2B3F3B (same +0x78 vector,
// same 0x40CBD7 lookup-or-null with lea [ebp+8] out-param, same +0xC4 flag
// and +0xAC rowed 0x7DEEF release) but with NO EH prolog (plain push ebp
// frame) and a tail jmp to the release: null-test, clear +0xC4, pop ebp,
// jmp 0x7DEEF. Evidence: retail
//   push ebp; mov ebp,esp; push [ebp+0xC]; lea eax,[ebp+8]; push eax
//   mov eax,[ebp+8]; mov ecx,[eax+0x78]; call 0x40CBD7
//   mov eax,[ebp+8]; test eax,eax; je end
//   mov byte [eax+0xC4],0; mov ecx,[ebp+8]; add ecx,0xAC; pop ebp; jmp 0x7DEEF
//   end: pop ebp; ret
// Boundary: Ghidra FUN_006b3f9f 52B; follows 0x2B3F3B; successor 0x2B3FD3
// (mov eax,imm32 / call __EH_prolog). Names are address-derived.
class Rva0040CBD7Vec
{
public:
	void rva0040CBD7(void **out, int key);
	char m_pad[0x40];
	char *m_first;
	char *m_last;
};

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};

class Rva002B3F9FSelf
{
public:
	char m_pad78[0x78];
	Rva0040CBD7Vec *m_vec;
	char m_pad79[0xAC - 0x78 - 4];
	TargetRef00217D4C m_hintAC;
	char m_padAD[0xC4 - 0xAC - 8];
	unsigned char m_flagC4;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

void rva002B3F9F(void *self, int key)
{
	((Rva002B3F9FSelf *)self)->m_vec->rva0040CBD7((void **)&self, key);
	if (self == 0)
		return;
	((Rva002B3F9FSelf *)self)->m_flagC4 = 0;
	ReleaseTreeHintRef00217D4C(&((Rva002B3F9FSelf *)self)->m_hintAC);
}
