// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva005A57BA@AptOnlineCustomMatch@@QAE_N_N@Z
// retail 0x005A57BA..0x005A5B38 (894 bytes EH) thiscall RET 4.
//
// The join request of the online custom match screen: refused while the
// pop-up is up (+0x4A0); state 1. The game id comes either from the buddy
// invite (fromInvite: the owner's +0x298 record copied through the rowed
// Rva00516F3F::rva00516F63 and the rowed 0x0059FC9F; +0x4DC cleared) or from
// the selected row of the +0x48C list box (rowed GadgetListBoxGetSelected
// and the column 3 item data 0x003253BE). Errors go through the rowed
// GSMessageBoxOk with TheGameText labels: GUI:Error over GUI:NoGameSelected or
// GUI:NoGameInfo, GUI:JoinFailedDefault over GUI:JoinFailedCRCMismatch (the
// room's exe CRC string +0x90 ini CRC +0xC0 and cmd CRC +0xC4 against
// TheWritableGlobalData's +0xB08 +0xB04 +0xB38) GUI:JoinFailedUnknownLadder
// (ladder port +0x1008 with no LadderList::findLadder hit) or
// GUI:JoinFailedRoomFull (slots 8 and 9 equal). The room comes from
// TheGameSpyInfo's staging room map (slot 41) and an unknown id fails
// silently. Otherwise the id is remembered (+0x4B8) and the join is
// requested (rowed RequestJoinGame) with the invite's password; a passworded
// room instead opens the movie's "EnterPassword" prompt (as CancelPopUpHost
// closes it) refills the game name entry (rowed FillGameNameTextEntry) and
// enters state 10.
// Evidence (target): ECX is the screen (callers 0x005A5BC1 pass their own
// ECX and 0x005A6538 mov ecx esi; the body reads this +0x4A0 +0x488 +0x48C
// +0x58) and the callees RequestJoinGame / FillGameNameTextEntry are rowed
// AptOnlineCustomMatch members; RET 4 with a byte argument and AL result.
// This replaces the pinned spelling ?rva005A57BA@@YGXH@Z (no stdcall: the
// callee uses ECX). WorldBuilder twin 0x014EF9E0 (unnamed; its debug text
// "WOLLobbyMenuSystem - CRC mismatch with the game I'm trying to join")
// has the same labels and order. The method name is address-derived.
// Shape notes: the record ctor initialises its ids before its strings; the
// room's CRC words and ladder port are read through inline getters (which
// gives retail's register choice and the 16-bit test of the port).

#include "ascii_string.h"
#include "unicode_string.h"
#include <map>

typedef int Int;

class GameWindow;
void GadgetListBoxGetSelected(GameWindow *listbox, int *selected);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);

void GSMessageBoxOk(UnicodeString title, UnicodeString message, void (*okFunc)());

class GameTextInterface
{
public:
#define T(n) virtual void t##n();
	T(0) T(1) T(2) T(3) T(4) T(5) T(6) T(7) T(8) T(9) T(10) T(11) T(12) T(13) T(14)
#undef T
	virtual UnicodeString fetch(const char *, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

class Rva0023851C
{
public:
	AsciiString rva0023851C();
};

class GlobalData
{
public:
	unsigned char m_pad000[0xb04];
	int m_iniCRC; // +0xB04
	Rva0023851C m_exeCRC; // +0xB08
	unsigned char m_padB0C[0xb38 - 0xb0c];
	int m_cmdCRC; // +0xB38
};
extern GlobalData *TheWritableGlobalData;

class LadderInfo;
class LadderList
{
public:
	const LadderInfo *findLadder(const AsciiString &addr, unsigned short port);
};
class Rva0054D974;
extern Rva0054D974 *TheLadderList;

class Rva0059F322AsciiField { public: AsciiString get() const; };

class GameSpyStagingRoom
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual int getNumPlayers(); // slot 8 (+0x20)
	virtual int getMaxPlayers(); // slot 9 (+0x24)

	unsigned char m_pad004[0x90 - 0x04];
	Rva0023851C m_exeCRC; // +0x90
	unsigned char m_pad094[0xc0 - 0x94];
	int m_iniCRC; // +0xC0
	int m_cmdCRC; // +0xC4
	unsigned char m_pad0c8[0xfec - 0xc8];
	bool m_hasPassword; // +0xFEC
	unsigned char m_padfed[0x1008 - 0xfed];
	unsigned short m_ladderPort; // +0x1008

	int getIniCRC() const { return m_iniCRC; }
	int getCmdCRC() const { return m_cmdCRC; }
	unsigned short getLadderPort() const { return m_ladderPort; }
};

typedef std::map<Int, GameSpyStagingRoom *> StagingRoomMap;

#define GSI_SLOT(n) virtual void slot##n();
class GameSpyInfoInterface
{
public:
	GSI_SLOT(00) GSI_SLOT(01) GSI_SLOT(02) GSI_SLOT(03) GSI_SLOT(04) GSI_SLOT(05) GSI_SLOT(06) GSI_SLOT(07)
	GSI_SLOT(08) GSI_SLOT(09) GSI_SLOT(10) GSI_SLOT(11) GSI_SLOT(12) GSI_SLOT(13) GSI_SLOT(14) GSI_SLOT(15)
	GSI_SLOT(16) GSI_SLOT(17) GSI_SLOT(18) GSI_SLOT(19) GSI_SLOT(20) GSI_SLOT(21) GSI_SLOT(22) GSI_SLOT(23)
	GSI_SLOT(24) GSI_SLOT(25) GSI_SLOT(26) GSI_SLOT(27) GSI_SLOT(28) GSI_SLOT(29) GSI_SLOT(30) GSI_SLOT(31)
	GSI_SLOT(32) GSI_SLOT(33) GSI_SLOT(34) GSI_SLOT(35) GSI_SLOT(36) GSI_SLOT(37) GSI_SLOT(38) GSI_SLOT(39)
	GSI_SLOT(40)
	virtual StagingRoomMap *getStagingRoomList(); // +0xA4
};
#undef GSI_SLOT
extern GameSpyInfoInterface *TheGameSpyInfo;

struct Rva00416088
{
	Rva00416088() : m_00((unsigned int)-1), m_04((unsigned int)-1) {}
	unsigned int m_00;
	unsigned int m_04;
	AsciiString m_08;
	AsciiString m_0C;
	~Rva00416088();
};

struct Rva00516F3F
{
	Rva00516F3F *rva00516F63(const Rva00516F3F &other);
};

// The buddy-invite join record (Rva00516F3F's layout): three ids, two
// strings (the second the password) and a trailing id.
struct JoinRecord
{
	JoinRecord() : m_00(-1), m_14(-1) {}
	int m_00;
	Rva00416088 m_sub;
	int m_14;
};

struct AptOnlineCustomMatchOwner
{
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
	unsigned char m_pad278[0x298 - 0x278];
	JoinRecord m_invite; // +0x298
};

class Rva0059FC9F { public: int rva0059FC9F(); };

class AptOnlineCustomMatch
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual const char *v10();

	bool rva005A57BA(bool fromInvite);
	bool RequestJoinGame(const char *password);
	void FillGameNameTextEntry(bool flag);

private:
	unsigned char m_pad004[0x58 - 0x04];
	AptOnlineCustomMatchOwner *m_owner; // +0x58
	unsigned char m_pad05c[0x488 - 0x5c];
	int m_state; // +0x488
	GameWindow *m_gameList; // +0x48C
	unsigned char m_pad490[0x4a0 - 0x490];
	bool m_popUp; // +0x4A0
	unsigned char m_pad4a1[0x4a8 - 0x4a1];
	int m_4a8; // +0x4A8
	unsigned char m_pad4ac[0x4b0 - 0x4ac];
	int m_4b0; // +0x4B0
	unsigned char m_pad4b4[0x4b8 - 0x4b4];
	int m_gameToJoinID; // +0x4B8
	unsigned char m_pad4bc[0x4dc - 0x4bc];
	int m_4dc; // +0x4DC
};

bool AptOnlineCustomMatch::rva005A57BA(bool fromInvite)
{
	if (m_popUp)
		return false;
	m_state = 1;
	m_4b0 = 0;
	JoinRecord record;
	int id;
	if (fromInvite)
	{
		((Rva00516F3F *)&record)->rva00516F63(*(const Rva00516F3F *)&m_owner->m_invite);
		id = ((Rva0059FC9F *)this)->rva0059FC9F();
		m_4dc = 0;
	}
	else
	{
		int selected;
		GadgetListBoxGetSelected(m_gameList, &selected);
		if (selected < 0)
		{
			GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:NoGameSelected"), 0);
			return false;
		}
		id = (int)GadgetListBoxGetItemData(m_gameList, selected, 3);
	}
	if (id <= 0)
	{
		GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:NoGameInfo"), 0);
		return false;
	}
	StagingRoomMap *srm = TheGameSpyInfo->getStagingRoomList();
	StagingRoomMap::iterator it = srm->find(id);
	if (it == srm->end())
		return false;
	GameSpyStagingRoom *room = it->second;
	bool exeOK = room && room->m_exeCRC.rva0023851C() == TheWritableGlobalData->m_exeCRC.rva0023851C();
	bool iniOK = room && room->getIniCRC() == TheWritableGlobalData->m_iniCRC;
	bool cmdOK = room && room->getCmdCRC() == TheWritableGlobalData->m_cmdCRC;
	if (!exeOK || !iniOK || !cmdOK)
	{
		GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"), TheGameText->fetch("GUI:JoinFailedCRCMismatch"), 0);
		return false;
	}
	bool unknownLadder = room->getLadderPort() &&
		!((LadderList *)TheLadderList)->findLadder(((Rva0059F322AsciiField *)room)->get(), room->getLadderPort());
	if (unknownLadder)
	{
		GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"), TheGameText->fetch("GUI:JoinFailedUnknownLadder"), 0);
		return false;
	}
	if (room->getNumPlayers() == room->getMaxPlayers())
	{
		GSMessageBoxOk(TheGameText->fetch("GUI:JoinFailedDefault"), TheGameText->fetch("GUI:JoinFailedRoomFull"), 0);
		return false;
	}
	m_gameToJoinID = id;
	if (fromInvite)
		return RequestJoinGame(record.m_sub.m_0C.str());
	if (room->m_hasPassword)
	{
		m_4a8 = -1;
		m_popUp = true;
		void *movie = m_owner->m_movie;
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), movie, v10(), "EnterPassword");
		FillGameNameTextEntry(false);
		m_state = 10;
		return true;
	}
	return RequestJoinGame("");
}
