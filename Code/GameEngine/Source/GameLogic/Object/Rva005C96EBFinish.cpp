// cl: /DNDEBUG /MD /EHsc
//
// ??0Rva005C96EB@@QAE@PAX@Z @0x005C96EB (104B):
// The previous BFME1 Locomotor donor supplied only a construction-shape lead.
// That identity is refuted: native's Apt screen base and table 0x00C74B70
// differ from the independently rowed Locomotor at 0x001E449A / 0x00BDE888.
// This receiver and its opaque context keep address-derived names. The layout is
// 0x26C. Base ctor 0x00313847 (BfmeAptScreenBase), member ctor 0x00524B7A at
// +0x218, vtable 0x00C74B70 at +0. Clears the dword block at +0x258..+0x264
// through a local int pointer, then ORs status bit 0x640 at +8, copies status
// to +0x254 and clears the byte at +0x268. Evidence: sole factory caller
// 0x005C9886 (pushes 0x26C), and rowed base/member ctors. No donor establishes
// the receiver's target name or the context's type.

// Retail destroys this GameWindow-derived screen base through the rowed
// protected ~GameWindow 0x00314A0C (the unwind funclet / vtable slot 0 target).
#include "../../../Include/GameClient/Bfme2GameWindow.h"

class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase(void *ctx);
	~BfmeAptScreenBase() { ((GameWindow *)this)->GameWindow::~GameWindow(); }
	virtual void slot0();
protected:
	void *m_anchor;
	int m_status;
private:
	char m_rest[0x20C];
};

class MovieWindowPlayback
{
public:
	MovieWindowPlayback();
private:
	void *m_vtable;
	char m_basePad[8];
	void *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
};

class Rva005C96EB : public BfmeAptScreenBase
{
public:
	Rva005C96EB(void *ctx);
private:
	MovieWindowPlayback m_218;
	int m_254;
	int m_258[4];
	unsigned char m_268;
	char m_pad[3];
};

Rva005C96EB::Rva005C96EB(void *ctx) : BfmeAptScreenBase(ctx)
{
	int *p = m_258;
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	p[3] = 0;
	m_status |= 0x640;
	m_254 = m_status;
	m_268 = 0;
}

