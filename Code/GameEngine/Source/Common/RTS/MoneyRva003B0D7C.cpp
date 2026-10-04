// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /arch:SSE /EHsc /MD /DNDEBUG
// ?rva003B0D7C@Rva003B0D7C@@QAEXHPAVRva0039B7AD@@_N@Z @0x003B0D7C 188B
// Unlock lane: Money at Player+0x90 subobject, (amt,0,1) thiscall from script 0x003BC048; audio via TheAudio slots 0x138/0x64 with BfmeAudioEventPrefix136(ref+0x38,0)+set(+8)+addAudioEvent; then +4+=amt, g_00E032F8+8 cond, arg2 cond add.
// Evidence: caller 0x003BC048 pushes (amt,0,1) with this=Player+0x90; callees ctor 0x002D97D6 dtor 0x002D9A43 set 0x0033F15D rva0039B7AD 0x0039B7AD rowed; TheAudio 0x009FE6E8 ThePlayerList 0x009FEEE8; neighbours HackInternetAIUpdate/Rva003B0E38Xfer.
// ?rva003B0CB3@Rva003B0D7C@@QAEIIPAVRva0039B795@@_N@Z @0x003B0CB3 201B
// The withdraw twin directly before it, shaped like Zero Hour's
// Money::withdraw: clamp the request to the balance (+4, unsigned, cmova),
// bail on zero, play the misc-audio sound at +0x3C (deposit uses +0x38) when
// asked, subtract, credit the +4 counter of g_00E032F8 for the local
// player's index, report to the optional tracker 0x0039B795, return the
// amount. cmova needs /arch:SSE; the deposit body is unchanged by it.
#include "Common/BfmeAudioEventPrefix136.h"

class AudioManager;
extern AudioManager *TheAudio;
extern class PlayerList *ThePlayerList;
extern void *g_00E032F8;

class Rva0033F15DDwordSlot { public: void set(int); };

struct Rva003B0D7CMisc { char pad[0x38]; OpaqueRefElement4 ref38; OpaqueRefElement4 ref3C; };

class Rva003B0D7CAudioView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *);
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual const Rva003B0D7CMisc *getMiscAudio();
};

class Player
{
public:
	char m_pad00[0x54];
	int m_playerIndex;
};

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_localPlayer;
};

struct G00E032F8Wrap { char m_pad00[4]; int m_val04; int m_val08; };

class Rva0039B7AD
{
public:
	void rva0039B7AD(int delta);
};

class Rva0039B795
{
public:
	void rva0039B795(int delta);
};

class Rva003B0D7C
{
public:
	unsigned int rva003B0CB3(unsigned int amount, Rva0039B795 *arg2, bool flag);
	void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
private:
	char m_pad00[4];
	int m_val04;
	int m_val08;
};

unsigned int Rva003B0D7C::rva003B0CB3(unsigned int amount, Rva0039B795 *arg2, bool flag)
{
	if (amount > (unsigned int)m_val04)
		amount = m_val04;
	if (amount == 0)
		return amount;
	if (flag != false) {
		BfmeAudioEventPrefix136 evt(reinterpret_cast<Rva003B0D7CAudioView *>(TheAudio)->getMiscAudio()->ref3C, 0);
		reinterpret_cast<Rva0033F15DDwordSlot *>(&evt)->set(m_val08);
		reinterpret_cast<Rva003B0D7CAudioView *>(TheAudio)->addAudioEvent(&evt);
	}
	m_val04 -= amount;
	G00E032F8Wrap *g = (G00E032F8Wrap *)g_00E032F8;
	if (g != 0) {
		PlayerList *pl = ThePlayerList;
		if (pl != 0) {
			Player *local = pl->m_localPlayer;
			if (local != 0) {
				if (local->m_playerIndex == m_val08) {
					g->m_val04 += amount;
				}
			}
		}
	}
	if (arg2 != 0) {
		arg2->rva0039B795(amount);
	}
	return amount;
}

void Rva003B0D7C::rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag)
{
	if (amount == 0)
		return;
	if (flag != false) {
		BfmeAudioEventPrefix136 evt(reinterpret_cast<Rva003B0D7CAudioView *>(TheAudio)->getMiscAudio()->ref38, 0);
		reinterpret_cast<Rva0033F15DDwordSlot *>(&evt)->set(m_val08);
		reinterpret_cast<Rva003B0D7CAudioView *>(TheAudio)->addAudioEvent(&evt);
	}
	m_val04 += amount;
	G00E032F8Wrap *g = (G00E032F8Wrap *)g_00E032F8;
	if (g != 0) {
		PlayerList *pl = ThePlayerList;
		if (pl != 0) {
			Player *local = pl->m_localPlayer;
			if (local != 0) {
				if (local->m_playerIndex == m_val08) {
					g->m_val08 += amount;
				}
			}
		}
	}
	if (arg2 != 0) {
		arg2->rva0039B7AD(amount);
	}
}
