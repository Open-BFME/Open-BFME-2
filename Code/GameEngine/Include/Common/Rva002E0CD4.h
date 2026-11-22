// Rva002E0CD4: canonical declarations for the members 6 units call through private views of it.
// Layout target facts: the getters 0x002E0CAC/0x002E0CD4/0x002E14DD read an inner pointer at +0x40
// (its +0x8/+0xC/+0x10/+0x14) and own ints at +0x260/+0x290/+0x294; the rest stays opaque.
#ifndef CANONICAL_RVA002E0CD4_H
#define CANONICAL_RVA002E0CD4_H

struct Rva002E0CD4Inner
{
	char m_pad[8];
	int m_8;
	int m_C;
	int m_10;
	int m_14;
};

class Rva002E0CD4
{
public:
	char m_pad[0x40];
	Rva002E0CD4Inner *m_40;
	char m_pad2[0x260 - 0x44];
	int m_260;
	char m_pad3[0x290 - 0x264];
	int m_290;
	int m_294;
	int rva002E0CAC() const;
	int get() const;
	int rva002E14DD() const;
};

#endif // CANONICAL_RVA002E0CD4_H
