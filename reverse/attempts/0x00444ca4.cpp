// ?rva00444CA4@Rva00444CA4@@QAE_NPAUStartPosArg@@H@Z
// partial score=0.92 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ?rva00444CA4@Rva00444CA4@@QAE_NPAUStartPosArg@@H@Z @0x00444CA4 215B.
// Chain from LANGameInfo::rva004477C7 (rowed): TheLAN global slot 0xE0 yields
// the LANGameInfo, its const check gates a LAN path (slot 0x38, TheLAN slot
// 0x68 with a zeroed 6-byte local, this+0xC enable) versus a "StartPos=%d"
// AsciiString path through TheLAN slot 0x64. Early nulls return false;
// both tails return true. ret 8: two stack args.

#include "ascii_string.h"

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

class LANGameInfo
{
public:
	bool rva004477C7(void) const;
};

struct StartPosArg
{
	unsigned char pad[0x10];
	int x10;
	int x14;
};

struct Slot68Local
{
	int a;
	short b;
	Slot68Local() : a(0), b(0) {}
};

struct Global009FE958 : public VSlots<25>
{
	virtual void slot25(AsciiString s, void *b, int c, void *d) = 0; // +0x64
	virtual void slot26(int a, void *b) = 0; // +0x68
	virtual void h27(void) = 0;
	virtual void h28(void) = 0;
	virtual void h29(void) = 0;
	virtual void h30(void) = 0;
	virtual void h31(void) = 0;
	virtual void h32(void) = 0;
	virtual void h33(void) = 0;
	virtual void h34(void) = 0;
	virtual void h35(void) = 0;
	virtual void h36(void) = 0;
	virtual void h37(void) = 0;
	virtual void h38(void) = 0;
	virtual void h39(void) = 0;
	virtual void h40(void) = 0;
	virtual void h41(void) = 0;
	virtual void h42(void) = 0;
	virtual void h43(void) = 0;
	virtual void h44(void) = 0;
	virtual void h45(void) = 0;
	virtual void h46(void) = 0;
	virtual void h47(void) = 0;
	virtual void h48(void) = 0;
	virtual void h49(void) = 0;
	virtual void h50(void) = 0;
	virtual void h51(void) = 0;
	virtual void h52(void) = 0;
	virtual void h53(void) = 0;
	virtual void h54(void) = 0;
	virtual void h55(void) = 0;
	virtual LANGameInfo *slot56(void) = 0; // +0xE0
};
extern struct Global009FE958 *g_Va009FE958;

class LANGameInfoFull
{
public:
	virtual void s00(void) = 0;
	virtual void s01(void) = 0;
	virtual void s02(void) = 0;
	virtual void s03(void) = 0;
	virtual void s04(void) = 0;
	virtual void s05(void) = 0;
	virtual void s06(void) = 0;
	virtual void s07(void) = 0;
	virtual void s08(void) = 0;
	virtual void s09(void) = 0;
	virtual void s10(void) = 0;
	virtual void s11(void) = 0;
	virtual void s12(void) = 0;
	virtual void s13(void) = 0;
	virtual void slot14(void) = 0; // +0x38
};

class Rva0043DB47DoubleSetter
{
public:
	void enable(void);
};

class Rva00444CA4
{
public:
	bool rva00444CA4(StartPosArg *arg, int value);

private:
	unsigned char m_pad[0x0C];
	Rva0043DB47DoubleSetter m_setter; // +0x0C
};

// ?rva00444CA4@Rva00444CA4@@QAE_NPAUStartPosArg@@H@Z present-unmatched
bool Rva00444CA4::rva00444CA4(StartPosArg *arg, int value)
{
	LANGameInfo *info;
	Global009FE958 *g = g_Va009FE958;
	if (g == 0)
		return false;
	info = g->slot56();
	if (info == 0)
		return false;
	arg->x10 = value;
	arg->x14 = value;
	if (info->rva004477C7()) {
		((LANGameInfoFull *)info)->slot14();
		Slot68Local local;
		g_Va009FE958->slot26(1, &local);
		m_setter.enable();
		return true;
	}
	AsciiString s;
	s.format("StartPos=%d", arg->x10);
	Slot68Local other;
	g_Va009FE958->slot25(s, info, 1, &other);
	return true;
}
