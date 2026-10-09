// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?rva0051805B@AptOnline@@UAEHXZ
// Retail 0x0051805B..0x0051822B (464 bytes); vtable slot at 0x0086643C.
// Per-frame update of the online shell: updates the current sub-screen
// (+0x290; vslot 6) or runs the no-screen handler 0x00517EA2; updates every
// loaded sub-screen (vector +0x280; vslot 3); when a screen name is pending
// (+0x28C) it asks the Apt movie (+0x274) to "LoadScreen" it through the Apt
// call target, clears the name and queues a type-3 stats request for the
// local profile (TheGameSpyInfo vslot 31) on TheGameSpyPSMessageQueue
// (vslot 4); then the shell mode (+0x2B0) advances: 2 and 3 wait for the
// current screen (vslot 7) and load "OnlineOpenPlay" / "OnlineStrategic"
// unless that screen instance (0x00E06544 / 0x00E06548) is already up then
// go to 5; 5 waits for vslot 9 and goes to 4. Finishes with 0x005170F1 and
// returns 1.
// Evidence: WorldBuilder 0x0145BE80 has the same flow strings and callees.
// Rowed callees: Rva00517EA2::rva00517EA2 0x00517EA2 StringBase<char>::isEmpty
// 0x00001E2F Rva00222A8BTarget::invoke 0x00222A8B AsciiString::clear (pinned
// releaseBuffer 0x00036410) BfmeOpaqueOwnedRecord1432 ctor 0x00556523 / dtor
// 0x0038A1F2 PSPlayerAllStats::setID 0x00552CDE Rva00516F21Invoke
// 0x00516F21 Rva005170CD::rva005170F1 0x005170F1. Layout follows
// AptOnlineShellScreens.cpp (screens +0x280 current +0x290 mode area). The
// method name is address-derived.
// The two load calls must target DISTINCT functions: retail keeps both
// push/call sequences and shares only the stack cleanup, which cl does only
// for different callees (one callee lets it cross-jump the whole sequence).
// WorldBuilder has two 44-byte wrappers there (0x0145E110 / 0x0145E140);
// retail folded both onto 0x00516F21. The second spelling needs the fold pin
// ?Rva00516F21InvokeFold@@YAXPAVRva00222A8BTarget@@PAXPBD2@Z=0x00516F21 with
// its twin body added to Rva00516F21Invoke.cpp. The getMovie() inline
// reproduces retail's early +0x274 load (and with it the cmov-style str()).
#include <vector>
#include "ascii_string.h"

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

void Rva00516F21Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const char *value);
// Second wrapper spelling folded onto 0x00516F21 (see the header comment).
void Rva00516F21InvokeFold(Rva00222A8BTarget *target, void *owner, const char *name, const char *value);

class GameSpyInfoInterface
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30)
#undef V
	virtual int getLocalProfileID() = 0;
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class PSPlayerAllStats
{
public:
	void setID(int id);
	unsigned char m_data[0x548];
};

class BfmeOpaqueOwnedRecord1432
{
public:
	BfmeOpaqueOwnedRecord1432();
	~BfmeOpaqueOwnedRecord1432();
	int m_requestType;          // +0x00
	int m_04;                   // +0x04
	PSPlayerAllStats m_player;  // +0x08
	unsigned char m_rest[0x598 - 0x550];
};

class GameSpyPSMessageQueueInterface
{
public:
	virtual void pad0() = 0;
	virtual void pad1() = 0;
	virtual void pad2() = 0;
	virtual void pad3() = 0;
	virtual void addRequest(const BfmeOpaqueOwnedRecord1432 &request) = 0;
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;

struct AptOnlineSubScreen
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void update();
	virtual void v4();
	virtual void v5();
	virtual void updateCurrent();
	virtual bool isReady();
	virtual void v8();
	virtual bool isDone();
};

extern int g_Va00E06544;
extern int g_Va00E06548;

class Rva00517EA2
{
public:
	void rva00517EA2();
};

class Rva005170CD
{
public:
	void rva005170F1();
};

class AptOnline
{
public:
	virtual int rva0051805B();
	void *getMovie() const { return m_movie; }

private:
	unsigned char m_pad004[0x274 - 0x04];
	void *m_movie;                       // +0x274
	unsigned char m_pad278[0x280 - 0x278];
	_STL::vector<AptOnlineSubScreen *> m_screens; // +0x280
	AsciiString m_pendingScreen;         // +0x28C
	AptOnlineSubScreen *m_current;       // +0x290
	unsigned char m_pad294[0x2B0 - 0x294];
	int m_state;                         // +0x2B0
};

int AptOnline::rva0051805B()
{
	if (m_current)
		m_current->updateCurrent();
	else
		((Rva00517EA2 *)this)->rva00517EA2();
	for (_STL::vector<AptOnlineSubScreen *>::iterator it = m_screens.begin(); it != m_screens.end(); ++it)
		(*it)->update();
	if (!((const StringBase<char> *)&m_pendingScreen)->isEmpty())
	{
		TheRva00222A8BTarget->invoke(getMovie(), "LoadScreen", 1, m_pendingScreen.str(), 0, 0, 0, 0);
		m_pendingScreen.clear();
		if (TheGameSpyInfo)
		{
			int id = TheGameSpyInfo->getLocalProfileID();
			if (id)
			{
				BfmeOpaqueOwnedRecord1432 request;
				request.m_requestType = 0;
				request.m_04 = 3;
				request.m_player.setID(id);
				TheGameSpyPSMessageQueue->addRequest(request);
			}
		}
	}
	switch (m_state)
	{
	case 2:
		if (m_current && m_current->isReady())
		{
			if (m_current != (AptOnlineSubScreen *)g_Va00E06544)
				Rva00516F21Invoke(TheRva00222A8BTarget, m_movie, "LoadScreen", "OnlineOpenPlay");
			m_state = 5;
		}
		break;
	case 3:
		if (m_current && m_current->isReady())
		{
			if (m_current != (AptOnlineSubScreen *)g_Va00E06548)
				Rva00516F21InvokeFold(TheRva00222A8BTarget, m_movie, "LoadScreen", "OnlineStrategic");
			m_state = 5;
		}
		break;
	case 5:
		if (m_current && m_current->isDone())
			m_state = 4;
		break;
	}
	((Rva005170CD *)this)->rva005170F1();
	return 1;
}
