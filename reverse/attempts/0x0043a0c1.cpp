// ?rva0043A0C1@Rva0043A0C1@@QAEXH@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?rva0043A0C1@Rva0043A0C1@@QAEXH@Z @0x0043A0C1 156B
// LoadScreen progress refresh: inits +0x18 panel once via rowed 0x0057E24B
// and pinned 0x0057DFFB, notifies +0x10 slot, then per-mode network or
// GameLogic progress via TheNetwork/TheGameLogic, finishing with
// LoadScreen::update. Evidence: packet disasm with rowed callees, prev/next
// in Common, no callers.
class Rva0057E3DB
{
public:
	void rva0057E24B(int arg);
	bool rva0057DFFB(int arg);
	char m_pad[0x70];
};

class LoadScreen
{
public:
	virtual void update(int x);
	char m_pad[0x10 - 4];
};

class NetworkInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15(int x) = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void s24() = 0;
	virtual void s25() = 0;
	virtual void s26() = 0;
	virtual void s27() = 0;
	virtual void s28() = 0;
	virtual void s29() = 0;
	virtual void s30() = 0;
	virtual void s31() = 0;
	virtual void s32() = 0;
	virtual void s33() = 0;
	virtual void s34() = 0;
	virtual void s35(int x) = 0;
};

extern NetworkInterface *TheNetwork;

class GameLogic
{
public:
	void processProgress(int a, int b);
};

extern GameLogic *TheGameLogic;

class Slot10
{
public:
	virtual void a0() = 0;
	virtual void a1() = 0;
	virtual void a2(int x) = 0;
};

class Slot88
{
public:
	virtual void b00() = 0;
	virtual void b01() = 0;
	virtual void b02() = 0;
	virtual void b03() = 0;
	virtual void b04() = 0;
	virtual void b05() = 0;
	virtual void b06() = 0;
	virtual void b07() = 0;
	virtual void b08() = 0;
	virtual void b09() = 0;
	virtual void b10() = 0;
	virtual void b11() = 0;
	virtual void b12() = 0;
	virtual int getValue() = 0;
};

class Rva0043A0C1 : public LoadScreen
{
public:
	void rva0043A0C1(int percent);
private:
	Slot10 *m_10;
	int m_14;
	Rva0057E3DB m_18;
	Slot88 *m_88;
	char m_pad8C[0xD0 - 0x8C];
	bool m_D0;
};

int Rva00559F7EGet(int mode);
int Rva00559F95Get(int mode);

void Rva0043A0C1::rva0043A0C1(int percent)
{
	if (!m_D0) {
		m_18.rva0057E24B((int)m_88);
		m_D0 = m_18.rva0057DFFB(1);
	}
	m_10->a2(0);
	int mode = m_14;
	if (mode > 0 && (mode <= 2 || mode == 5)) {
		if (TheNetwork != 0) {
			if (percent <= 100)
				TheNetwork->s35(percent);
			TheNetwork->s15(0);
		} else if (percent <= 100) {
			int v = m_88->getValue();
			TheGameLogic->processProgress(percent, v);
		}
	}
	((LoadScreen *)this)->LoadScreen::update(percent);
}
