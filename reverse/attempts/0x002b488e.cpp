// ?rva002B488E@Rva002B488E@@QAEHPAX@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /MD
// ?rva002B488E@Rva002B488E@@QAEHPAX@Z @0x002B488E 83B: __thiscall int scan.
// Null-arg and empty-table guards return 0; otherwise each pointer in the
// +0x8C/+0x90 table is probed through the 0x2E0A9F check with the argument,
// returning the first nonzero result, with the count recomputed every pass.
// Evidence: retail
//   cmp [esp+4],0; push esi; mov esi,ecx; jne HASARG; xor eax,eax; jmp END
//   HASARG: mov eax,[esi+0x90]; sub eax,[esi+0x8C]; push edi; xor edi,edi
//   sar eax,2; je EMPTY
//   LOOP: mov eax,[esi+0x8C]; push [esp+0xC]; mov ecx,[eax+edi*4]
//   call 0x2E0A9F; test eax,eax; jne FOUND
//   mov eax,[esi+0x90]; sub eax,[esi+0x8C]; inc edi; sar eax,2
//   cmp edi,eax; jb LOOP
//   EMPTY: xor eax,eax; FOUND/END: pop edi; pop esi; ret 4
// Boundary: range-table 83B ending at 0x2B48E1 (push esi). Names are
// address-derived.
class Rva002E0A9FElem
{
public:
	int rva002E0A9F(void *arg);
};

class Rva002B488E
{
public:
	int rva002B488E(void *arg);
private:
	char m_pad[0x8C];
	int m_begin8C;
	int m_end90;
};

int Rva002B488E::rva002B488E(void *arg)
{
	if (arg == 0)
		return 0;
	int e = m_end90;
	int d = e - m_begin8C;
	int i = 0;
	if ((d >> 2) == 0)
		return 0;
	do {
		int r = ((Rva002E0A9FElem **)m_begin8C)[i]->rva002E0A9F(arg);
		if (r != 0)
			return r;
		++i;
	} while (i < ((m_end90 - m_begin8C) >> 2));
	return 0;
}
