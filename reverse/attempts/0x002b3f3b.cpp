// ?rva002B3F3B@@YAXPAXH@Z
// partial score=0.88 date=2026-10-05
// cl: /O1 /MD /EHsc
// ?rva002B3F3B@@YAXPAXH@Z @0x002B3F3B 100B: resolve-then-act with C++ EH.
// Opens with mov eax,imm32 / call __EH_prolog (rowed 0x629188 MASM): the
// function carries a try/catch(...) (Rva002236B9Dtor /EHsc precedent).
// The by-value self pointer is resolved in place through the 0x40CBD7
// lookup-or-null helper (thiscall on the +0x78 vector: lea eax,[ebp+8] for
// the out-param, key pushed first), then under try: null-test, bare-call
// 0x2B3E7E check with the pointer live in eax (zero-arg pin, same as
// 0x2B3EFA), +0xC4 mark and 0x40C45C notify; try-exit or [ebp-4],-1, then the
// rowed 0x7DEEF fastcall release on the +0xAC member; fs:[0] restore, leave.
// Evidence: retail
//   mov eax,0xB76358; call __EH_prolog; mov eax,[ebp+8]; mov ecx,[eax+0x78]
//   push [ebp+0xC]; lea eax,[ebp+8]; push eax; call 0x40CBD7
//   mov eax,[ebp+8]; and [ebp-4],0; test eax,eax; je skip1
//   call 0x2B3E7E; test al,al; je skip1
//   mov eax,[ebp+8]; mov byte [eax+0xC4],1; mov ecx,[ebp+8]; call 0x40C45C
//   mov eax,[ebp+8]; or [ebp-4],-1; test eax,eax; je skip2
//   lea ecx,[eax+0xAC]; call 0x7DEEF; fs:[0] restore; leave; ret
//   sole caller 0x2BE23E (push [ebp+8]; call; pop ecx).
// Boundary: Ghidra FUN_006b3f3b 100B; follows the landed 0x2B3EFA ret;
// successor 0x2B3F9F opens with push ebp. Names are address-derived.
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

class Rva002B3EFAElem
{
public:
	void rva0040C45C();
	char m_pad[0xC4];
	unsigned char m_flagC4;
};

class Rva002B3F3BSelf
{
public:
	char m_pad78[0x78];
	Rva0040CBD7Vec *m_vec;
	char m_pad79[0xAC - 0x78 - 4];
	TargetRef00217D4C m_hintAC;
	char m_padAD[0xC4 - 0xAC - 8];
	unsigned char m_flagC4;
};

// Zero-arg 0x2B3E7E check pin: candidate arrives in EAX, caller keeps it
// live across the bare call (see Rva002B3EFA.cpp).
bool Rva002B3E7ECheck();

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

void rva002B3F3B(void *self, int key)
{
	Rva002B3F3BSelf *s = (Rva002B3F3BSelf *)self;
	s->m_vec->rva0040CBD7((void **)&s, key);
	try {
		if (s != 0 && Rva002B3E7ECheck()) {
			s->m_flagC4 = 1;
			((Rva002B3EFAElem *)s)->rva0040C45C();
		}
	}
	catch (...) {
	}
	if (s != 0)
		ReleaseTreeHintRef00217D4C(&s->m_hintAC);
}
