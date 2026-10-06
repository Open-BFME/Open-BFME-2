// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1Rva005E0B0F@@UAE@XZ @0x005E0B0F 128B
// Dtor with own vtable 0x00877960 and base 0x0086E330. Calls forwarder
// 0x005CB260 with int 0 on +8 (row says void - same 5B slot1 ICF twin pinned)
// then no-arg int getter pinned 0x005CB265 on +4 compared to +0x14 holder
// then forwarder 0x005CB260 on +4 then holder at +0x14 releases via fastcall
// 0x0007DEEF then two UnicodeStrings at +0xC +0x10 via 0x00036E70. Precedent
// Rva005F918DDtor for holder plus Release shape and Rva005D3AF2Method.
// Evidence: deleting dtors at 0x005CB301 0x005CB31D 0x005CB337 call it.
#include "unicode_string.h"

class Rva005CB260
{
public:
	void rva005CB260();
	void rva005CB260(int);
};

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct Rva005E0B0FHolder14 {
    TargetRef00217D4C *m_ptr;
    __forceinline ~Rva005E0B0FHolder14() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva0086E330Base
{
public:
	virtual ~Rva0086E330Base() {}
};

class Rva005E0B0F : public Rva0086E330Base
{
public:
	virtual ~Rva005E0B0F();
private:
	Rva005CB265 *m_04;
	Rva005CB260 *m_08;
	UnicodeString m_0C;
	UnicodeString m_10;
	Rva005E0B0FHolder14 m_14;
};

Rva005E0B0F::~Rva005E0B0F()
{
	m_08->rva005CB260(0);
	TargetRef00217D4C *p = m_14.m_ptr;
	if (p != 0)
	{
		if (m_04->Rva005CB265::rva005CB265() == (int)p)
			((Rva005CB260 *)m_04)->rva005CB260();
	}
}
