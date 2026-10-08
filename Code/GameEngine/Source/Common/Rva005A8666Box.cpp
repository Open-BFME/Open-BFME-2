// cl: -GR- -EHsc-
// NAT::targetNotifyMeIWasProbed @0x005A8666 90B (WorldBuilder name, its
// __FUNCTION__ string "NAT::targetNotifyMeIWasProbed"): guarded one-shot setter.
// Unless +0x94C already reads 5, resolve m_8[m_14]; a present object with
// its 0x40 flag set and a present m_8[m_18] plus both byte gates leads
// through the pinned 0x5A831E call to the pinned setter with 3, every other
// failing path uses 5. The int parameter is unused (callback shape). Targets
// read from retail REL32; the 0x5A6C90 callee is matched but spelled local.
struct Rva005A8666Obj
{
	char pad[0x40];
	unsigned char m_40;
};

struct Rva005A8666Ptr
{
	int m_0;
	short m_4;
};

#include "../../Include/GameNetwork/Transport.h"

struct NAT
{
	int m_0;
	Transport *m_04;
	Rva005A8666Obj **m_8;
	int m_C;
	int m_10;
	int m_14;
	int m_18;
	char pad1[0x24 - 0x1c];
	unsigned char m_24;
	unsigned char m_25;
	char pad2[0x90c - 0x26];
	Rva005A8666Ptr *m_90C[8];
	char pad2b[0x942 - 0x92c];
	unsigned char m_942;
	char pad3[0x94c - 0x943];
	int m_94C;
	int m_950;
	char pad4[0x970 - 0x954];
	unsigned char m_970;

	void rva005A831E();
	void rva005A6C90(int code);
	void targetNotifyMeIWasProbed(int unused);
	void gotTargetMangledPort(int a, unsigned short b, int c);
};

void NAT::targetNotifyMeIWasProbed(int unused)
{
	if (m_94C == 5)
		return;
	Rva005A8666Obj *o = m_8[m_14];
	if (o == 0) {
		rva005A6C90(5);
		return;
	}
	if (m_942 != 0)
		return;
	m_942 = 1;
	if ((o->m_40 & 8) == 0)
		return;
	if (m_8[m_18] == 0) {
		rva005A6C90(5);
		return;
	}
	if (m_25 == 0)
		return;
	if (m_24 == 0)
		return;
	rva005A831E();
	rva005A6C90(3);
}

// NAT::gotTargetMangledPort @0x005A86C0 219B (WorldBuilder name, its
// __FUNCTION__ string "NAT::gotTargetMangledPort"): validated triple apply.
// Unless both +0x94C and +0x950 read 4, resolve both indexed slots; present
// pair plus matching first arg stamps +0x25 and, when +0x970 is set, links
// the pair's words (copying b into the peer's +4 and c over on full match).
// A present +0x24 leads through the +4 sub-object consumer and, unless
// +0x94C reads 2 with both flags against a cleared +0x942, through the gate
// to the setter with 3. Same class as targetNotifyMeIWasProbed (shared layout and pins).
void NAT::gotTargetMangledPort(int a, unsigned short b, int c)
{
	if (m_94C == 4 && m_950 == 4)
		return;
	Rva005A8666Obj *o1 = m_8[m_18];
	if (o1 == 0) {
		rva005A6C90(5);
		return;
	}
	Rva005A8666Obj *o2 = m_8[m_14];
	if (o2 == 0) {
		rva005A6C90(5);
		return;
	}
	if (a != m_18)
		return;
	if (m_970 == 0) {
		m_25 = 1;
		goto check24;
	}
	m_25 = 1;
	m_90C[m_18]->m_4 = b;
	if (m_90C[m_14]->m_0 == m_90C[m_18]->m_0)
		m_90C[m_18]->m_0 = c;
check24:
	if (m_24 == 0)
		return;
	m_04->setDestAddrToSocket(m_18, m_90C[m_18]);
	if (m_94C != 2)
		return;
	if ((o2->m_40 & 8) != 0) {
		if (m_942 != 1 && (o1->m_40 & 8) == 0)
			return;
	}
	rva005A831E();
	rva005A6C90(3);
}
