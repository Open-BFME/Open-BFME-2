// cl: /Ireference/shims/bfme2_ascii /O1
// Reconstruction of the 218B version-gated xfer at 0x003189AD: xfer a
// true flag, three labelled ints through the rowed XferEnum helpers, the
// +0x08 int through the global's slot 88, three member ints through Xfer
// slots 27/30 gated on the version byte (init 4), and either a member
// fill through 0x318871 (version 4) or a zero plus a bitset word indexed
// by the enum out-param. Slot meanings below 37 are unproven guesses
// constrained only by index and arity (XferEnum is independently slot 37);
// the flag/version bytes and all offsets are target facts.
#include <string.h>

class Xfer;

void XferGlobalWeatherType(Xfer *xfer, int *value);
void XferGlobalWeatherAffectsType(Xfer *xfer, int *value);
void XferAttributeModifierCategoryType(Xfer *xfer, int *value);

class Xfer
{
public:
	class Version
	{
	public:
		Version(unsigned char earliest, unsigned char current)
			: m_earliest(earliest), m_current(current) {}

		unsigned char m_earliest;
		unsigned char m_current;
	};

	virtual ~Xfer() = 0;				// 0
	virtual void s01() = 0; virtual void s02() = 0;	// 1-2
	virtual void s03() = 0; virtual void s04() = 0;
	virtual void s05() = 0; virtual void s06() = 0;
	virtual void s07() = 0; virtual void s08() = 0;
	virtual void s09() = 0;				// 9
	virtual Xfer &operator==(Version &value) = 0;		// 10
	virtual void s11() = 0; virtual void s12() = 0;
	virtual void s13() = 0; virtual void s14() = 0;
	virtual void s15() = 0; virtual void s16() = 0;
	virtual void s17() = 0; virtual void s18() = 0;
	virtual void s19() = 0; virtual void s20() = 0;
	virtual void s21() = 0; virtual void s22() = 0;
	virtual void s23() = 0; virtual void s24() = 0;
	virtual void s25() = 0; virtual void s26() = 0;	// 11-26
	virtual Xfer &slot27(int &value) = 0;		// 27
	virtual void s28() = 0; virtual void s29() = 0;	// 28-29
	virtual Xfer &slot30(int &value) = 0;		// 30
};

class Rva003189ADGlobal
{
public:
	virtual void g00() = 0; virtual void g01() = 0;
	virtual void g02() = 0; virtual void g03() = 0;
	virtual void g04() = 0; virtual void g05() = 0;
	virtual void g06() = 0; virtual void g07() = 0;
	virtual void g08() = 0; virtual void g09() = 0;
	virtual void g10() = 0; virtual void g11() = 0;
	virtual void g12() = 0; virtual void g13() = 0;
	virtual void g14() = 0; virtual void g15() = 0;
	virtual void g16() = 0; virtual void g17() = 0;
	virtual void g18() = 0; virtual void g19() = 0;
	virtual void g20() = 0; virtual void g21() = 0;
	virtual void g22() = 0; virtual void g23() = 0;
	virtual void g24() = 0; virtual void g25() = 0;
	virtual void g26() = 0; virtual void g27() = 0;
	virtual void g28() = 0; virtual void g29() = 0;
	virtual void g30() = 0; virtual void g31() = 0;
	virtual void g32() = 0; virtual void g33() = 0;
	virtual void g34() = 0; virtual void g35() = 0;
	virtual void g36() = 0; virtual void g37() = 0;
	virtual void g38() = 0; virtual void g39() = 0;
	virtual void g40() = 0; virtual void g41() = 0;
	virtual void g42() = 0; virtual void g43() = 0;
	virtual void g44() = 0; virtual void g45() = 0;
	virtual void g46() = 0; virtual void g47() = 0;
	virtual void g48() = 0; virtual void g49() = 0;
	virtual void g50() = 0; virtual void g51() = 0;
	virtual void g52() = 0; virtual void g53() = 0;
	virtual void g54() = 0; virtual void g55() = 0;
	virtual void g56() = 0; virtual void g57() = 0;
	virtual void g58() = 0; virtual void g59() = 0;
	virtual void g60() = 0; virtual void g61() = 0;
	virtual void g62() = 0; virtual void g63() = 0;
	virtual void g64() = 0; virtual void g65() = 0;
	virtual void g66() = 0; virtual void g67() = 0;
	virtual void g68() = 0; virtual void g69() = 0;
	virtual void g70() = 0; virtual void g71() = 0;
	virtual void g72() = 0; virtual void g73() = 0;
	virtual void g74() = 0; virtual void g75() = 0;
	virtual void g76() = 0; virtual void g77() = 0;
	virtual void g78() = 0; virtual void g79() = 0;
	virtual void g80() = 0; virtual void g81() = 0;
	virtual void g82() = 0; virtual void g83() = 0;
	virtual void g84() = 0; virtual void g85() = 0;
	virtual void g86() = 0; virtual void g87() = 0;
	virtual void slot88(Xfer *xfer, int *value) = 0;	// 88
};

extern Rva003189ADGlobal *TheRva003189ADGlobal;

class Rva003189ADSub10
{
public:
	void rva00362255(Xfer *xfer);
	int m_00;
	int m_04;
};

class Rva003189ADSub4C
{
public:
	void rva00318871(Xfer *xfer);
	int m_flags;
};

class Rva003189ADOwner
{
public:
	void rva003189AD(Xfer *xfer);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	Rva003189ADSub10 m_10;
	int m_18;
	int m_1c;
	int m_20;
	unsigned char m_gap[0x4c - 0x24];
	Rva003189ADSub4C m_4c;
};

void Rva003189ADOwner::rva003189AD(Xfer *xfer)
{
	Xfer::Version version(1, 4);
	*xfer == version;
	XferGlobalWeatherType(xfer, &m_04);
	TheRva003189ADGlobal->slot88(xfer, &m_08);
	XferGlobalWeatherAffectsType(xfer, &m_0c);
	m_10.rva00362255(xfer);
	xfer->slot27(m_10.m_04);
	unsigned int out = 0;
	XferAttributeModifierCategoryType(xfer, (int *)&out);
	if (version.m_current >= 2)
		xfer->slot30(m_18);
	if (version.m_current >= 3)
	{
		xfer->slot30(m_1c);
		xfer->slot30(m_20);
	}
	if (version.m_current >= 4)
		m_4c.rva00318871(xfer);
	else
	{
		int *words = (int *)&m_4c;
		memset(words, 0, 4);
		if (out != 0)
		{
			int bit = 1 << (out & 31);
			words[out >> 5] |= bit;
		}
	}
}
