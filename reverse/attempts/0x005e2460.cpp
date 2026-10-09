// ?rva005E2460@Rva005E2460@@QAEXXZ
// partial score=0.96 date=2026-10-09
// ?rva005E2460@Rva005E2460@@QAEXXZ
// partial score=0.96 date=2026-10-02
// cl: /Ireference/shims/bfme2_ascii /O1 /G6 /MD /EHsc
// ?rva005E2460@Rva005E2460@@QAEXXZ @0x005E2460 120B
// Chain method: reads [this+0xC]->[+0x170][[this+0x20]]->[+0x20]->[+0x28] label
// holder; if present fetches its UnicodeString via rowed 0x002DF9E9 else rowed
// free 0x005C95CA STRATEGICHUD:BuildPlotName; forwards to rowed 0x005F0CC1.
// Evidence: chain lane caller of 0x005F0CC1 plus two unclaimed callers.
#include "unicode_string.h"

class Rva002DF9E9
{
public:
	UnicodeString rva002DF9E9();
};

class Rva005F0CC1
{
public:
	void rva005F0CC1(const UnicodeString &text);
};

class Rva005E2338Elem;
UnicodeString Rva005C95CAGet(const Rva005E2338Elem *);

struct Rva005E2460D
{
	char _00[0x28];
	Rva002DF9E9 *m_28;
};

struct Rva005E2460C
{
	char _00[0x20];
	Rva005E2460D *m_20;
};

struct Rva005E2460A
{
	char _00[0x170];
	Rva005E2460C **m_table;
};

class Rva005E2460
{
public:
	void rva005E2460();
private:
	char _00[0x0C];
	Rva005E2460A *m_0C;
	char _10[0x10];
	int m_20;
};

// ?rva005E2460@Rva005E2460@@QAEXXZ present-unmatched
void Rva005E2460::rva005E2460()
{
	Rva005E2460C **table = *(Rva005E2460C **volatile*)&m_0C->m_table;
	int idx = *(const volatile int*)&m_20;
	Rva005E2460C *entry = table[idx];
	Rva005E2460D *d = *(Rva005E2460D *volatile*)&entry->m_20;
	if (d != 0) {
		Rva002DF9E9 *labelObj = d->m_28;
		((Rva005F0CC1 *)this)->rva005F0CC1(labelObj->rva002DF9E9());
	} else {
		((Rva005F0CC1 *)this)->rva005F0CC1(Rva005C95CAGet((const Rva005E2338Elem*)entry));
	}
}
