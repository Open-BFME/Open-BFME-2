// ?rva00082C98@Rva00082C98Host@@QAEXIHHH@Z
// partial score=0.96 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Dump range 1 (0x00082C98 73B): vector clamp/erase wrapper over 12-byte
// elements. Count is (end-begin)/12 via push/pop idiv. If a0 < count,
// erase at begin+a0*12 through the pinned 0x00081A24; else call the pinned
// 0x00082719 with (&a1, a0-count, end). Four int args to match ret 0x10;
// a2/a3 unused. Honest address-derived names.

class Rva00082C98Vec
{
public:
	void eraseAux(void *first, void *last);
	void helperAux(void *e, unsigned int v, int *p);
};

class Rva00082C98Host
{
public:
	void rva00082C98(unsigned int a0, int a1, int a2, int a3);

	void *m_begin; // +0x00
	void *m_end; // +0x04
};

void Rva00082C98Host::rva00082C98(unsigned int a0, int a1, int a2, int a3)
{
	(void)a2;
	(void)a3;
	unsigned int count = ((char *)m_end - (char *)m_begin) / 12;
	if (a0 < count)
	{
		void *e = (char *)m_begin + a0 * 12;
		((Rva00082C98Vec *)this)->eraseAux(e, m_end);
	}
	else
	{
		((Rva00082C98Vec *)this)->helperAux(m_end, a0 - ((char *)m_end - (char *)m_begin) / 12, &a1);
	}
}
