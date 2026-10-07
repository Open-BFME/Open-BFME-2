// ?update@DisconnectManager@@QAEXPAVConnectionManager@@@Z
// partial score=0.9 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /EHs /O1 /arch:SSE /G7
// stlport
// BANKED PARTIAL. Needs, in Code/GameEngine/Source/Common/GameLogicObjectLookupView.h,
// GameLogic members after m_map: char padB5[0x114 - 0xB5]; int m_unknown114;
// char pad118[0x120 - 0x118]; LoadScreen *m_loadScreen; with getters
// getUnknown114() and getLoadScreen() (class LoadScreen; forward-declared).
// The Rva004D39DEGet row (0x004D39DE, 18 B) moves into this TU: retail's 12
// callers clean up with add esp,8, which only an in-TU definition gives.
// Unpinned callee: updateDisconnectStatus 0x004D4395 (--pin on add_match).
// Remaining diff (36 instruction lines, one region): retail lays out
// `cmp [GameLogic+0x114],3; je victory; turnOnScreen; jmp; <loop else block>;
// victory tests (g==0 -> turnOn, +4C/+48 -> quit, +54 false -> turnOn); quit`,
// this body puts the victory tests inline after `jne turnOn`. Tried without
// change: helper (forceinline, early-return shapes), negated condition,
// do/while(0) breaks, flag variable, separate quit for the stall clause,
// /Ob1 /Ob2 /Oi /Op; worse: switch on +0x114, goto layouts, else-if splits.
// DisconnectManager::update, retail 0x004D46FC, 861 bytes, called by
// ConnectionManager::update 0x004D342A while in game.
//
// Reference: Zero Hour and Open-BFME-1 DisconnectManager::update (track the
// last logic frame and when it was reached, update the disconnect status
// while the screen is on, request pings from the first ping server and count
// the answered repetitions under 2000 ms). BFME 2 rewrote the stall
// detection, read from this body: after 0x00512CCD, every slot that is not
// local-or-live (0x004CEF58), not active (0x004CF0CD) and still connected
// counts as stalled; its stall is charged once per stall to the slot itself
// while the ping success ratio (0x004D38D8) is at least 0.1, else to the
// local slot, in the counters at +0x272 (words) and +0x282 (flags). Every
// other slot clears its flag (the local one only when nothing stalls) and
// resets its timeout through 0x004D39DE. A slot that is inactive, connected
// and silent for 5000 ms (0x004CEFC2) asks for pings. While anything stalls
// +0x270 is set; with no load screen and the screen off, the game is left
// through Network's vtable slot 37 (0x0025E233) once the local slot has
// stalled five times, when fewer than two players remain, or in +0x114 mode 3
// when the victory conditions (0x00E03138, slots +0x4C, +0x48 and +0x54) say
// so; otherwise the screen is turned on. Then 0x004D3942 runs. With nothing
// stalled a shown screen is turned off by 0x004D3906. Pings go out at most
// every 3000 ms (+0x268) and, while stalled, only within 5000 ms of the
// screen coming on (+0x25C); without a ping request the ping counters reset.

// The strings' inlined deallocation frees through the C++-linkage free
// 0x00030830, whose possible throw keeps the unwind state store in front of it.
extern "C" void __cdecl free(void *block) throw(...);

#include "ascii_string.h"
#include "../Common/GameLogicObjectLookupView.h"
#include <string>
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef float Real;

enum
{
	MAX_SLOTS = 8
};

enum DisconnectStateType
{
	DISCONNECTSTATETYPE_SCREENON,
	DISCONNECTSTATETYPE_SCREENOFF
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

extern GameLogic *TheGameLogic;

class NetworkInterface;
struct DisconnectNetworkVTable
{
	void *unknown[37];
	void (__fastcall *rva0025E233)(NetworkInterface *network);
};

class NetworkInterface
{
public:
	void rva0025E233() { m_vtable->rva0025E233(this); }

private:
	DisconnectNetworkVTable *m_vtable;
};

extern NetworkInterface *TheNetwork;

// The victory conditions, held in the data ledger under an address name.
struct UnknownE03138
{
	virtual void u00(); virtual void u01(); virtual void u02(); virtual void u03();
	virtual void u04(); virtual void u05(); virtual void u06(); virtual void u07();
	virtual void u08(); virtual void u09(); virtual void u10(); virtual void u11();
	virtual void u12(); virtual void u13(); virtual void u14(); virtual void u15();
	virtual void u16(); virtual void u17();
	virtual Bool u18();
	virtual Bool u19();
	virtual void u20();
	virtual Bool u21();
};

extern UnknownE03138 *g_00E03138;

struct PingRequest
{
	std::string hostname;
	Int repetitions;
	Int timeout;
};

struct PingResponse
{
	std::string hostname;
	Int avgPing;
	Int repetitions;
};

class PingerInterface
{
public:
	virtual ~PingerInterface();
	virtual Bool startThreads() = 0;
	virtual void endThreads() = 0;
	virtual Bool areThreadsRunning() = 0;
	virtual void addRequest(const PingRequest &req) = 0;
	virtual Bool getRequest(PingRequest &req) = 0;
	virtual void addResponse(const PingResponse &resp) = 0;
	virtual Bool getResponse(PingResponse &resp) = 0;
};

extern PingerInterface *ThePinger;

class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface();
	virtual std::list<AsciiString> getPingServers() = 0;
};

extern GameSpyConfigInterface *TheGameSpyConfig;

void Rva00512CCDShutdown();
Int Rva004D39DEGet(Int slot, Int localSlot)
{
	return (slot < localSlot) ? slot : ((slot == localSlot) ? -1 : slot - 1);
}

class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID();
	Int getNumPlayers();
};

class BFMEConnectionManager
{
public:
	UnsignedByte rva004CEF58(Int slot);
	UnsignedByte rva004CEFC2(Int slot, UnsignedInt timeout);
	Bool isPlayerConnected(Int slot);
	Int isPlayerSlotActive(Int slot);
};

// The ping success ratio test, the end-of-stall step and the screen-off step,
// held in the ledger under address names.
class Rva004D38D8
{
public:
	Bool rva004D38D8(Real ratio);
};

class Rva004D3942
{
public:
	void rva004D3942(ConnectionManager *conMgr);
};

class Rva004D3906
{
public:
	void rva004D3906(Int slot);
};

class DisconnectManager
{
public:
	virtual ~DisconnectManager();
	void update(ConnectionManager *conMgr);

protected:
	void turnOnScreen(ConnectionManager *conMgr);
	void updateDisconnectStatus(ConnectionManager *conMgr);
	void resetPlayerTimeout(Int slot);

private:
	UnsignedInt m_lastFrame;
	Int m_lastFrameTime;
	DisconnectStateType m_disconnectState;
	char m_pad010[0x25c - 0x10];
	UnsignedInt m_timeOfDisconnectScreenOn;
	Int m_pingsSent;
	Int m_pingsRecieved;
	UnsignedInt m_lastPingTime;
	char m_pad26C[0x270 - 0x26c];
	Bool m_stalled;
	UnsignedShort m_stallCount[MAX_SLOTS];
	Bool m_stallCharged[MAX_SLOTS];
};

void DisconnectManager::update(ConnectionManager *conMgr)
{
	Rva00512CCDShutdown();

	Int numStalled = 0;
	Bool needPing = false;
	Int localSlot = conMgr->getLocalPlayerID();
	BFMEConnectionManager *bfmeMgr = (BFMEConnectionManager *)conMgr;
	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (!(UnsignedByte)bfmeMgr->isPlayerSlotActive(i) && bfmeMgr->isPlayerConnected(i) &&
			!bfmeMgr->rva004CEFC2(i, 5000))
			needPing = true;
		if (!bfmeMgr->rva004CEF58(i) && !(UnsignedByte)bfmeMgr->isPlayerSlotActive(i) &&
			bfmeMgr->isPlayerConnected(i))
		{
			++numStalled;
			Int slot = i;
			if (!((Rva004D38D8 *)this)->rva004D38D8(0.1f))
				slot = localSlot;
			if (!m_stallCharged[slot])
			{
				m_stallCharged[slot] = true;
				++m_stallCount[slot];
			}
		}
		else
		{
			if (i != localSlot)
				m_stallCharged[i] = false;
			Int translated = Rva004D39DEGet(i, conMgr->getLocalPlayerID());
			if (translated != -1)
				resetPlayerTimeout(translated);
		}
	}

	if (numStalled == 0)
		m_stallCharged[localSlot] = false;

	if (numStalled > 0)
	{
		m_stalled = true;
		if ((TheGameLogic == 0 || TheGameLogic->getLoadScreen() == 0) &&
			m_disconnectState == DISCONNECTSTATETYPE_SCREENOFF)
		{
			if ((m_stallCount[localSlot] >= 5 && TheNetwork != 0) || conMgr->getNumPlayers() < 2 ||
				(TheGameLogic->getUnknown114() == 3 && g_00E03138 != 0 &&
					(g_00E03138->u19() || g_00E03138->u18() || g_00E03138->u21())))
			{
				if (TheNetwork != 0)
					TheNetwork->rva0025E233();
			}
			else
				turnOnScreen(conMgr);
		}
		((Rva004D3942 *)this)->rva004D3942(conMgr);
	}
	else
	{
		m_stalled = false;
		if (m_disconnectState == DISCONNECTSTATETYPE_SCREENON)
			((Rva004D3906 *)this)->rva004D3906(conMgr->getLocalPlayerID());
	}

	if (m_lastFrameTime == -1 || m_lastFrame != TheGameLogic->getFrame())
	{
		m_lastFrame = TheGameLogic->getFrame();
		m_lastFrameTime = timeGetTime();
	}

	if (m_disconnectState != DISCONNECTSTATETYPE_SCREENOFF)
		updateDisconnectStatus(conMgr);

	if (needPing)
	{
		if (ThePinger == 0)
			return;
		if (timeGetTime() - m_lastPingTime > 3000 &&
			(numStalled == 0 || timeGetTime() - m_timeOfDisconnectScreenOn < 5000))
		{
			PingRequest req;
			req.hostname = TheGameSpyConfig->getPingServers().begin()->str();
			req.repetitions = 5;
			req.timeout = 2000;
			m_pingsSent += req.repetitions;
			ThePinger->addRequest(req);
			m_lastPingTime = timeGetTime();
		}
	}
	else
	{
		m_pingsSent = 0;
		m_pingsRecieved = 0;
		m_lastPingTime = 0;
	}

	if (ThePinger != 0)
	{
		PingResponse resp;
		while (ThePinger->getResponse(resp))
		{
			if (needPing && resp.avgPing < 2000)
				m_pingsRecieved += resp.repetitions;
		}
	}
}
