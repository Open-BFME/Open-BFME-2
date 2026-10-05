// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// BFME2's LAN lobby screen: the per-slot option setters and their siblings
// that the lobby's callback vftable at 0x00C3E098 holds (slot 12 is
// applySlotTeam). Retail places them together at 0x0044440C..0x004457BC,
// after Rva00444525Init (which pushes "LanLobby.apt").
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/
// BfmeAptScreenLanLobby_*.cpp (f57439f7f4). Identity is carried per body by
// its option key string ("Team=%d", ...) and by the shared call pattern;
// BFME1's class and method names are donor names, not target facts.
//
// Target facts (all read from retail): TheLAN is the global at 0x009FE958
// (defined in Rva00446A77Enable.cpp; the g_00DFE958 spelling is aliased
// there); LANAPI vslot 56 returns the current LANGameInfo, vslot 25 sends a
// game-options string, vslot 26 asks the host for serialized game info.
// LANGameInfo vslot 14 is resetAccepted, and the non-virtual
// LANGameInfo::rva004477C7 0x004477C7 is the host test (slot 0 is local).
// GameSlot keeps the team number at +0x1C and the handicap at +0x20.

#include "ascii_string.h"

class GameSlot
{
public:
	int getTeamNumber() const { return m_teamNumber; }
	int getHandicap() const { return m_handicap; }

	unsigned char m_pad00[0x1C];
	int m_teamNumber; // +0x1C
	int m_handicap; // +0x20
};

class LANGameInfo
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();

	bool rva004477C7() const;
};

struct TransportAddress
{
	TransportAddress() : m_ip(0), m_port(0) {}

	unsigned int m_ip;
	unsigned short m_port;
};

class LANAPI
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void RequestGameOptions(AsciiString options, bool isPublic,
		const TransportAddress &address = TransportAddress()) = 0;
	virtual void requestSerializedGameInfo(bool unused, TransportAddress *destination) = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void v52() = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual LANGameInfo *GetMyGame() = 0;
};

extern LANAPI *g_00DFE958;
#define TheLAN g_00DFE958

class BfmeAptScreenLanLobby
{
public:
	bool applySlotTeam(GameSlot *slot, int team);
	bool applySlotHandicap(GameSlot *slot, int handicap);
};

// Retail 0x004449FD, 198 bytes. BFME2 drops the donor's second
// resetAccepted on the host path.
bool BfmeAptScreenLanLobby::applySlotTeam(GameSlot *slot, int team)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->m_teamNumber = team;
	game->resetAccepted();
	if (game->rva004477C7())
	{
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	else
	{
		AsciiString options;
		options.format("Team=%d", slot->getTeamNumber());
		TheLAN->RequestGameOptions(options, true);
	}
	return true;
}

// Retail 0x00444AC3, 205 bytes: vftable 0x00C3E098 slot 5, "Handicap=%d".
// BFME1 has no handicap option; the body is applySlotTeam's donor shape
// (including its second resetAccepted on the host path) over +0x20, and the
// name follows that family.
bool BfmeAptScreenLanLobby::applySlotHandicap(GameSlot *slot, int handicap)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->m_handicap = handicap;
	game->resetAccepted();
	if (game->rva004477C7())
	{
		game->resetAccepted();
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	else
	{
		AsciiString options;
		options.format("Handicap=%d", slot->getHandicap());
		TheLAN->RequestGameOptions(options, true);
	}
	return true;
}
