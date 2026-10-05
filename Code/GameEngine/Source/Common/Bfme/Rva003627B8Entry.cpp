// cl: /O1 /DNDEBUG /MD
//
// ?rva003627B8@Rva003627B8Entry@@QAEXH@Z retail 0x003627B8 65 bytes.
// Entry guard in Buff 9x0x44 family: byte flag at +0x04, subcheck at +0x30
// via rowed 0x362499, unsigned threshold at +0x14, same-this reset via
// 0x362609 with 0, link release via rowed 0x419BA5 when [m_18+8]==3 then
// clear m_18. Evidence: bracket contiguity 0x36276F+73=0x3627B8 and
// 0x3627B8+65=0x3627F9; rowed caller 0x362862 loops entries->rva003627B8(a);
// fresh game.dat capstone decode (push esi/mov esi ecx/byte cmp/lea ecx
// +0x30/call 362499/test/jne/mov eax esp+8/cmp [esi+0x14]/jbe/push 0/mov
// ecx esi/call 362609/mov ecx [esi+0x18]/test/je/cmp [ecx+8] 3/jne/call
// 419BA5/and [esi+0x18] 0/pop esi/ret 4); Ghidra FUN_007627b8 65B; holder
// 9x0x44 layout from sibling Rva00362862Item; callees rowed 0x362499 and
// 0x419BA5 plus pinned 0x362609 (retail REL32 at 0x3627DA). Donor-negative:
// seat-47-r2 survey found no compatible Buff donor helper; narrow rg for
// Notify/notify in reference/open-bfme-1/game returns only unrelated hits;
// rev 6583b3c1 untouched. Names opaque address-derived; pins prove nothing.

class Rva00362499
{
public:
	unsigned char rva00362499();
private:
	char m_00[4];
	void *m_04;
	void *m_08;
};

class Rva00419BA5
{
public:
	void rva00419BA5();
};

struct Rva003627B8LinkState
{
	char m_pad[8];
	int m_state;
};

class Rva003627B8Entry
{
public:
	void rva003627B8(int a);
	void rva00362609(int v);
private:
	char m_00[4];
	unsigned char m_04;
	char m_pad05[15];
	unsigned int m_14;
	void *m_18;
	char m_pad1C[20];
	Rva00362499 m_check;
	char m_tail[8];
};

void Rva003627B8Entry::rva003627B8(int a)
{
	if (m_04 != 0 && !m_check.rva00362499() && (unsigned int)a > m_14)
		rva00362609(0);
	if (m_18 != 0 && ((Rva003627B8LinkState *)m_18)->m_state == 3)
	{
		((Rva00419BA5 *)m_18)->rva00419BA5();
		m_18 = 0;
	}
}
