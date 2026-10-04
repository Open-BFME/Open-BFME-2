// ?rva005D4A66@Rva005D4A66@@QAEXPAVRva005D48DB@@@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD /EHsc
// ?rva005D4A66@Rva005D4A66@@QAEXPAVRva005D48DB@@@Z, RVA 0x005D4A66, 106B. Chain lane: applies
// forwarder 0x005D48DB to each element of vector at +0/+4, tracking progress in
// member at +0xC with EH guard restoring it. Evidence: retail saves [ecx+0xC],
// zeroes it, loops push [begin+idx*4] with ecx=[ebp+8] as forwarder this, call
// 0x005D48DB row, reloads idx, restores on exit; caller 0x005D4C3F.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva005D48DB
{
public:
	void rva005D48DB(void *elem);
};
class Rva005D4A66Guard
{
public:
	Rva005D4A66Guard(int *p)
	{
		m_p = p;
		m_old = *p;
		*m_p = 0;
	}
	virtual ~Rva005D4A66Guard() { *m_p = m_old; }
private:
	int m_old;
	int *m_p;
};
class Rva005D4A66
{
public:
	void rva005D4A66(Rva005D48DB *fwd);
private:
	char *m_begin;
	char *m_end;
	char *m_cap;
	int m_idx;
};
// ?rva005D4A66@Rva005D4A66@@QAEXPAVRva005D48DB@@@Z present-unmatched
void Rva005D4A66::rva005D4A66(Rva005D48DB *fwd)
{
	Rva005D4A66Guard g(&m_idx);
	unsigned int i = 0;
	int count = (m_end - m_begin) >> 2;
	if (count == 0)
		return;
	do
	{
		m_idx = (int)(i + 1);
		_ReadWriteBarrier();
		fwd->rva005D48DB(((void **)m_begin)[i]);
		i = (unsigned int)m_idx;
		count = (m_end - m_begin) >> 2;
	} while (i < (unsigned int)count);
}
