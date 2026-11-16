// cl: /DNDEBUG /MD
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
	char m_pad[0x70];
};

class Rva0057DFFB
{
public:
	bool rva0057DFFB(bool arg);	// rowed 0x0057DFFB
};

class LoadScreen
{
public:
	virtual void update(int x);
	char m_pad[0x10 - 4];
};

#include "../../Include/GameNetwork/NetworkInterfaceClass.h"

extern NetworkInterface *TheNetwork;

#include "GameLogicObjectLookupView.h"

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
	int m_mode;
	Rva0057E3DB m_18;
	Slot88 *m_88;
	char m_pad8C[0xD0 - 0x8C];
	bool m_initialized;
};

int Rva00559F7EGet(int mode);
int Rva00559F95Get(int mode);

void Rva0043A0C1::rva0043A0C1(int percent)
{
	if (!m_initialized) {
		m_18.rva0057E24B((int)m_88);
		m_initialized = ((Rva0057DFFB *)&m_18)->rva0057DFFB(true);
	}
	m_10->a2(0);
	int mode = m_mode;
	if (mode > 0 && (mode <= 2 || mode == 5)) {
		if (TheNetwork != 0) {
			if (percent <= 100)
				TheNetwork->slot35(percent);
			TheNetwork->slot15(0);
		} else if (percent <= 100) {
			TheGameLogic->processProgress(m_88->getValue(), percent);
		}
	}
	((LoadScreen *)this)->LoadScreen::update(percent);
}
