// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?SetUpSubUIs@Rva005E2439@@QAEXXZ @0x005E2439 39B
// Unlock sibling of 0x005E2460: same [this+0xC]->[+0x170][[this+0x20]] chain
// then virtual slot 0x18 on [this+8] with D else slot 0x14 with entry.
// Evidence: unlock lane plus 3 callers including 0x005E24D8 which passes same this.
#include "unicode_string.h"

struct Rva005E2439D
{
	char _00[0x20];
	void *m_20;
	char _24[0x28 - 0x24];
	struct Rva002DF9E9 *m_28;
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
	void SetUpSubUIs();
	void rva005E2460();
	void rva005E2540();
private:
	char _00[0x08];
	Rva005E2439Obj *m_08;
	Rva005E2439A *m_0C;
	char _10[0x10];
	int m_20;
};

void Rva005E2439::SetUpSubUIs()
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
	SetUpSubUIs();
}
// ?rva005E2460@Rva005E2439@@QAEXXZ @0x005E2460 (120B)
// Chain sibling of SetUpSubUIs above on the same [this+0xC]->[+0x170]
// table: label holder at entry+0x20, UnicodeString via rowed 0x002DF9E9
// when present else rowed free 0x005C95CA, forwarded to rowed 0x005F0CC1.
// Evidence: WB ShowSelectionName branch structure + retail 120B; the d+0x28
// label pointer is a retail load, not donor invention.
#include "../../Include/Common/Rva002DF9E9.h"
class Rva005F0CC1
{
public:
	void rva005F0CC1(const UnicodeString &text);
};
class Rva005E2338Elem;
UnicodeString Rva005C95CAGet(const Rva005E2338Elem *);
void Rva005E2439::rva005E2460()
{
	Rva005E2439C *entry = m_0C->m_table[m_20];
	Rva005E2439D *d = entry->m_20obj;
	if (d != 0) {
		Rva002DF9E9 *labelObj = d->m_28;
		((Rva005F0CC1 *)this)->rva005F0CC1(labelObj->rva002DF9E9());
	} else {
		((Rva005F0CC1 *)this)->rva005F0CC1(Rva005C95CAGet((const Rva005E2338Elem *)entry));
	}
}
