// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005E2439@Rva005E2439@@QAEXXZ @0x005E2439 39B
// Unlock sibling of 0x005E2460: same [this+0xC]->[+0x170][[this+0x20]] chain
// then virtual slot 0x18 on [this+8] with D else slot 0x14 with entry.
// Evidence: unlock lane plus 3 callers including 0x005E24D8 which passes same this.
#include "unicode_string.h"

struct Rva005E2439D
{
	char _00[0x20];
	void *m_20;
};

struct Rva005E2439C
{
	char _00[0x20];
	Rva005E2439D *m_20obj;
};

struct Rva005E2439A
{
	char _00[0x170];
	Rva005E2439C **m_table;
};

struct Rva005E2439Obj
{
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5(void *p);
	virtual void s6(void *p);
};

class Rva005E2439
{
public:
	void rva005E2439();
	void rva005E2540();
private:
	char _00[0x08];
	Rva005E2439Obj *m_08;
	Rva005E2439A *m_0C;
	char _10[0x10];
	int m_20;
};

void Rva005E2439::rva005E2439()
{
	Rva005E2439A *a = m_0C;
	int idx = m_20;
	Rva005E2439C *entry = a->m_table[idx];
	void *d = entry->m_20obj;
	Rva005E2439Obj *obj = m_08;
	if (d != 0)
		obj->s6(d);
	else
		obj->s5(entry);
}
void Rva005E2439::rva005E2540()
{
	if (m_20 < 0)
		return;
	rva005E2439();
}
