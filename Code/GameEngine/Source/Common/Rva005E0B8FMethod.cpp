// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva005E0B8F@Rva005E0B0F@@QAEXH@Z @0x005E0B8F 47B
// vslot slot 3 offset 0xC of vtable 0x00877960 class of ??1Rva005E0B0F.
// Same class layout as Rva005E0B0FDtor: +4 getter pin 0x005CB265
// ?rva005CB265@Rva005CB265@@UAEHXZ then forwarder 0x005CB260
// ?rva005CB260@Rva005CB260@@QAEXXZ then holder at +0x14 clears via
// 0x002BED91 ?clear@Rva002BED91@@QAEXXZ. Ret 4 = one unused int arg.
// Evidence: dtor 0x005E0B0F same sequence with push 0 variant.
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

struct Rva002BED91
{
	void *m_ptr;
	void clear();
};

class Rva0086E330Base
{
public:
	virtual ~Rva0086E330Base();
};

class Rva005E0B0F : public Rva0086E330Base
{
public:
	virtual void rva005E0B8F(int);
private:
	Rva005CB265 *m_04;
	Rva005CB260 *m_08;
	UnicodeString m_0C;
	UnicodeString m_10;
	Rva002BED91 m_14;
};

void Rva005E0B0F::rva005E0B8F(int unused)
{
	(void)unused;
	void *holder = m_14.m_ptr;
	if (holder != 0)
	{
		if (m_04->Rva005CB265::rva005CB265() == (int)holder)
			((Rva005CB260 *)m_04)->rva005CB260();
		m_14.clear();
	}
}
