// ?rva0052B045@Rva005392C2@@QAEXXZ
// partial score=0.99 date=2026-10-06
// cl: /O1
// ?rva0052B045@Rva005392C2@@QAEXXZ, RVA 0x0052B045 size 85.
// Leaf lane: called by 3 matched rows showing the call shape.
// Evidence: pin Rva005392C2; Helper pin 0x0056BB8C returning RvaF6Ret;
// TreeHint op= row 0x002174A4; Release row 0x0007DEEF; clear row 0x002BED91;
// callers at 0x004E06EA 0x0052B0ED 0x0052B39A; neighbours share /O1.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};
struct RvaF6Ret
{
	~RvaF6Ret() { _ReadWriteBarrier(); }
	TargetRef00217D4C *m_ptr;
};
struct RvaF6Ret __cdecl Helper0056BB8C(int value);
struct Rva002BED91
{
	TargetRef00217D4C *m_ptr;
	void clear();
};
class Rva005392C2
{
public:
	void rva0052B045();
private:
	char m_pad[0x38];
	int m_38;
	char m_pad3C[0x40 - 0x3C];
	Rva002BED91 m_40;
};
// ?rva0052B045@Rva005392C2@@QAEXXZ present-unmatched
void Rva005392C2::rva0052B045()
{
	if (m_38 != 0)
	{
		RvaF6Ret tmp = Helper0056BB8C(m_38);
		((TreeHintRef00217D4C *)&m_40)->operator=((const TreeHintRef00217D4C &)tmp);
		TargetRef00217D4C *p = tmp.m_ptr;
		if (p != 0)
			ReleaseTreeHintRef00217D4C(p);
	}
	else
	{
		m_40.clear();
	}
}
