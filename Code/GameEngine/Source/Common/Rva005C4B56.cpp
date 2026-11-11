// cl: /O1 /MD
// ?rva005C4B56@Rva005C4B56@@QAEXHHH@Z @0x005C4B56 64B
// Honest address-derived placeholder: method rva005C4B56 in new opaque class
// Rva005C4B56. Unlock lane: landing it makes 0x005C4CC1 and 0x005C4CD4 ready
// plus 0x005C4C69 and 0x005C4C95 waiting on it and 0x00210E5B. Calls virtual
// slot 0x44 twice for bools and slot 0x48 once with bool bool int. Flags at
// +0xB8 via or with set mask and and with not clear mask. Callers share
// +0xAC +0xB0 +0xB8 layout. Prev 0x005C4B1B dtor and next 0x005C4D2F deleting
// dtor in OpaqueSingleInheritanceDtors.cpp. _ReadWriteBarrier between or and
// and stops MSVC folding two flag updates into one load-store with no bytes.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva005C4CC1Sub
{
public:
	char m_pad[0x3C];
	int m_val3C; // +0x3C
	int m_val40; // +0x40
	int m_val44; // +0x44
	int m_val48; // +0x48
	float m_val4C; // +0x4C
};

class Rva003FBA0E
{
public:
	void rva003FBA0E(int a, int b, int c, int d, int e, float f);
};

#include "../../Include/Common/Rva003FB9C8.h"

class Rva005C4B56
{
public:
	virtual ~Rva005C4B56();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11(bool a);
	virtual void s12(bool a);
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual bool s17();
	virtual void s18(bool a, bool b, int c);
	void rva005C4B56(int setBits, int clearBits, int val);
	void rva005C4CC1();
	void rva005C4CD4();
	void rva005C4BC8(bool oldState, bool newState, int c);
private:
	char m_pad2C[0x2C - 4];
	int m_2c; // +0x2C
	char m_padAC[0xAC - 0x2C - 4];
	Rva005C4CC1Sub *m_subAC; // +0xAC
	char m_padB8[0xB8 - 0xAC - 4];
	int m_flags; // +0xB8
};

void Rva005C4B56::rva005C4B56(int setBits, int clearBits, int val)
{
	bool first = s17();
	m_flags |= setBits;
	_ReadWriteBarrier();
	m_flags &= ~clearBits;
	bool second = s17();
	s18(first, second, val);
}

void Rva005C4B56::rva005C4CC1()
{
	rva005C4B56(2, 0, m_subAC->m_val3C);
}

void Rva005C4B56::rva005C4CD4()
{
	rva005C4B56(0, 2, m_subAC->m_val40);
}

// ?rva005C4BC8@Rva005C4B56@@QAEX_N_NH@Z @0x005C4BC8 161B
// Chain lane: calls 0x003FB9C8 just landed; vtable slot 18 of 0x008747B8
// (class of ??1Rva005C4B1B). Prev/next Rva005C4B56. Switch on 3rd arg with
// early-out when == +0x2C; cases call s11/s12 (slots 0x2C/0x30) and rowed
// Rva003FBA0E/Rva003FB9C8/Rva003FB9EB helpers via +0xAC sub (+0x44/+0x48/+0x4C).
// ?rva005C4BC8@Rva005C4B56@@QAEX_N_NH@Z present-unmatched
void Rva005C4B56::rva005C4BC8(bool oldState, bool newState, int c)
{
	bool flag = false;
	if (c == m_2c)
		goto final;
	switch (c) {
	case 1:
		if (oldState)
			goto final;
		if (!newState)
			return;
		((Rva003FB9C8 *)this)->rva003FB9EB(m_subAC->m_val44, 0);
		goto final;
	case 2:
		((Rva003FB9C8 *)this)->rva003FB9C8(m_subAC->m_val48, 0);
		if (oldState != true)
			goto final;
		flag = true;
		goto final;
	case 3: {
		int fadeInTime = m_subAC->m_val44;
		int fadeOutTime = m_subAC->m_val48;
		float vf = m_subAC->m_val4C;
		((Rva003FBA0E *)this)->rva003FBA0E(0, fadeInTime, fadeInTime, fadeOutTime + fadeInTime, 0, vf);
		if (oldState != true)
			goto final;
		flag = true;
		goto final;
	}
	case 4:
		s11(newState);
		goto final;
	default:
		goto final;
	}
final:
	if (oldState == newState)
		return;
	if (flag)
		return;
	s12(newState);
}
