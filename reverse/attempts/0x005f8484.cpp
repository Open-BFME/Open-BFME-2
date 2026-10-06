// ?rva005F8484@Rva005F86C3@@QAEXHH@Z
// partial score=0.9787 date=2026-10-06
// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// ?rva005F8484@Rva005F86C3@@QAEXHH@Z @0x005F8484 115B
// Evidence: vslot slot 3 of vtable 0x00879CBC (class of rowed ??1Rva005F86C3 0x005F86C3), bounds via start/finish at +0x20/+0x24 stride 8, TreeHintRef assign 0x002174A4 and Release 0x0007DEEF, forwarder 0x005C39C4, clear 0x002BED91.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
struct Rva002BED91
{
	TargetRef00217D4C *m_ptr;
	void clear();
};
class Rva005C39C4
{
public:
	TreeHintRef00217D4C rva005C39C4(int x);
};
struct Elem005F8484
{
	TreeHintRef00217D4C m_ref00;
	Rva002BED91 m_holder04;
};
class Rva005F86C3
{
public:
	void rva005F8484(int idx, int val);
private:
	char m_pad[0x20];
	Elem005F8484 *m_start20;
	Elem005F8484 *m_finish24;
};
// ?rva005F8484@Rva005F86C3@@QAEXHH@Z present-unmatched
void Rva005F86C3::rva005F8484(int idx, int val)
{
	if (idx < 0)
		return;
	unsigned int count = (unsigned int)(m_finish24 - m_start20);
	if ((unsigned int)idx >= count)
		return;
	_ReadWriteBarrier();
	Elem005F8484 *e = &m_start20[idx];
	if (e->m_ref00.m_ptr != 0)
		return;
	if (e->m_holder04.m_ptr == 0)
		return;
	e->m_ref00 = ((Rva005C39C4 *)e->m_holder04.m_ptr)->rva005C39C4(val);
	e->m_holder04.clear();
}
