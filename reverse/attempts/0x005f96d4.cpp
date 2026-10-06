// ?rva005F96D4Update@@YIXPAVRva005F96D4@@H@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva005F96D4Update@@YIXPAVRva005F96D4@@H@Z @0x005F96D4 161B evidence:
// fastcall twin orchestrator (this, fwd-dead-forwarded) over m_40/m_44/m_4C
// and m_50/m_54/m_5C plus m_2C/m_3C: dirty-index blocks call rowed thiscall
// ?rva005F94C2@Rva005F963AElem@@QAEXXZ @0x005F94C2 on the head, then load
// sub for both null-check and pinned fastcall
// ?rva009CC208@@YIXPAURva009CC208Sub@@HH@Z @0x005CC208(sub, fwd, 0) with
// fwd untouched in edx; then null-guarded pinned global-0
// ?rva009CB265@@YGXXZ @0x005CB265 on m_2C/m_3C; then pointer loops over
// both ranges calling pinned thiscall-0
// ?rva005F8F31@Rva005F963AElem@@QAEXXZ @0x005F8F31. Single zero (edi).
// TU-local views only.
struct Rva005F963AElem
{
	char m_pad[0x28];
	int m_28;
	void rva005F9567();
	void rva005F94C2();
	void rva005F8F31();
};

struct Rva009CC208Sub
{
	char m_pad[4];
};

void __fastcall rva009CC208(Rva009CC208Sub *sub, int fwd, int x);
void __stdcall rva009CB265();

class Rva005F96D4
{
public:
	char m_pad[0x2C];
	int m_2C;
	char m_pad2[0x3C - 0x30];
	int m_3C;
	Rva005F963AElem **m_40;
	Rva005F963AElem **m_44;
	char m_pad3[0x4C - 0x48];
	int m_4C;
	Rva005F963AElem **m_50;
	Rva005F963AElem **m_54;
	char m_pad4[0x5C - 0x58];
	int m_5C;
};

// ?rva005F96D4Update@@YIXPAVRva005F96D4@@H@Z present-unmatched
void __fastcall rva005F96D4Update(Rva005F96D4 *o, int fwd)
{
	int zero = 0;
	if (o->m_4C < zero)
	{
		if (o->m_40 != o->m_44)
		{
			if ((*o->m_40)->m_28 != zero)
			{
				(*o->m_40)->rva005F94C2();
				Rva009CC208Sub *sub1 = (Rva009CC208Sub *)o->m_2C;
				o->m_4C = zero;
				if (sub1 != 0)
					rva009CC208(sub1, fwd, zero);
			}
		}
	}
	if (o->m_5C < zero)
	{
		if (o->m_50 != o->m_54)
		{
			if ((*o->m_50)->m_28 != zero)
			{
				(*o->m_50)->rva005F94C2();
				Rva009CC208Sub *sub2 = (Rva009CC208Sub *)o->m_3C;
				o->m_5C = zero;
				if (sub2 != 0)
					rva009CC208(sub2, fwd, zero);
			}
		}
	}
	if (o->m_2C != zero)
		rva009CB265();
	if (o->m_3C != zero)
		rva009CB265();
	Rva005F963AElem **p = o->m_40;
	Rva005F963AElem **end = o->m_44;
	while (p != end)
	{
		(*p)->rva005F8F31();
		++p;
	}
	Rva005F963AElem **q = o->m_50;
	Rva005F963AElem **end2 = o->m_54;
	while (q != end2)
	{
		(*q)->rva005F8F31();
		++q;
	}
}
