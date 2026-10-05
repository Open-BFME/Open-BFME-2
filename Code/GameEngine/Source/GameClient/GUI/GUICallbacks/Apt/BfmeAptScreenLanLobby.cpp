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
// LANAPI vslot 55 returns the local player name by value.
// LANGameInfo vslot 14 is resetAccepted, and the non-virtual
// LANGameInfo::rva004477C7 0x004477C7 is the host test (slot 0 is local).
// GameSlot keeps the start position at +0x10 (with a second copy at
// +0x14 that the setter writes alongside it), the team number at +0x1C and
// the handicap at +0x20. The lobby's object at +0x0C takes the rowed
// Rva0043DB47DoubleSetter::enable 0x0043DB47, and its game-mode
// preferences object at +0x408 takes the rowed
// GameModePreferences::rva0044DD1E 0x0044DD1E before its vslot 3 (write).
// The player template goes through the rowed GameSlot::setPlayerTemplate
// 0x00400E33 and sits at +0x18; the slot name is the UnicodeString at +0x30.
// GameSlot vslot 5 yields the slot's LANGameSlot (BFME1's vslot 1), whose
// isLocalPlayer is pinned at 0x0044770F; the color sits at +0x0C. The hero
// byte is the rowed GameSlot::rva003FF16F 0x003FF16F, and +0x5C is the
// value the hero preference stores.

#include "ascii_string.h"
#include "unicode_string.h"

class LANGameSlot;

class GameSlot
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual LANGameSlot *getLANSlot();

	void setPlayerTemplate(int playerTemplate);
	void setMapAvailability(bool available);
	unsigned char rva003FF16F() const;
	int getColor() const { return m_color; }
	int getPlayerTemplate() const { return m_playerTemplate; }
	int getStartPos() const { return m_startPos; }
	int getTeamNumber() const { return m_teamNumber; }
	int getHandicap() const { return m_handicap; }

	unsigned char m_pad04[0x0C - 0x04];
	int m_color; // +0x0C
	int m_startPos; // +0x10
	int m_startPos14; // +0x14
	int m_playerTemplate; // +0x18
	int m_teamNumber; // +0x1C
	int m_handicap; // +0x20
	unsigned char m_pad24[0x30 - 0x24];
	UnicodeString m_name; // +0x30
	unsigned char m_pad34[0x5C - 0x34];
	int m_5c; // +0x5C
};

class LANGameSlot : public GameSlot
{
public:
	bool isLocalPlayer() const;
};

class GameInfo
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
	virtual void resetStartSpots();
	virtual void adjustSlotsForMap();

	GameSlot *getSlot(int index);
	void setMapForwarder(AsciiString mapName);
	void setMapCRC(unsigned int mapCRC);
	void setMapSize(unsigned int mapSize);

	unsigned char m_pad04[0x60 - 0x04];
	int m_rules[10]; // +0x60
};

class LANGameInfo : public GameInfo
{
public:
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
	virtual UnicodeString GetMyName() = 0;
	virtual LANGameInfo *GetMyGame() = 0;
};

extern LANAPI *g_00DFE958;
#define TheLAN g_00DFE958

class MapMetaData
{
public:
	unsigned char m_pad00[0x28];
	unsigned int m_filesize; // +0x28
	unsigned int m_CRC; // +0x2C
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

class Rva0043DB47DoubleSetter
{
public:
	void enable();
};

class GameModePreferences
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool write();

	void setStrategicScenario(int scenario);
	void rva0044DDFB(int *rules);
	void rva0044DC54(int hero);
	void rva0044DCB9(int color);
	void rva0044DD1E(int playerTemplate);
};

class BfmeAptScreenLanLobby
{
public:
	bool applySlotTeam(GameSlot *slot, int team);
	bool applySlotHandicap(GameSlot *slot, int handicap);
	bool applySlotStartPos(GameSlot *slot, int startPos);
	bool applySlotPlayerTemplate(GameSlot *slot, int playerTemplate);
	bool applySlotColor(GameSlot *slot, int color);
	bool applySlotHero(GameSlot *slot);
	void copyLanNameRva00444D7B(UnicodeString &dest);
	void saveRulesRva00444279();
	bool setScenarioRva0044440C(int scenario);
	bool bfmeMapChanged(const AsciiString *mapName);

private:
	unsigned char m_pad00[0x0C];
	Rva0043DB47DoubleSetter m_0c; // +0x0C
	unsigned char m_pad0d[0x408 - 0x0D];
	GameModePreferences m_prefs; // +0x408
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

// Retail 0x00444CA4, 215 bytes: vftable 0x00C3E098 slot 11, "StartPos=%d".
// Donor applySlotStartPos; BFME2 writes the position twice and, where BFME1
// set a flag byte on the host path, calls the +0x0C object's enable.
bool BfmeAptScreenLanLobby::applySlotStartPos(GameSlot *slot, int startPos)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->m_startPos = startPos;
	slot->m_startPos14 = startPos;
	if (game->rva004477C7())
	{
		game->resetAccepted();
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
		m_0c.enable();
	}
	else
	{
		AsciiString options;
		options.format("StartPos=%d", slot->getStartPos());
		TheLAN->RequestGameOptions(options, true);
	}
	return true;
}

// Retail 0x004455B2, 262 bytes: vftable 0x00C3E098 slot 10,
// "PlayerTemplate=%d". Donor applySlotPlayerTemplate; BFME2 calls the
// out-of-line setPlayerTemplate and compares the slot names in place.
bool BfmeAptScreenLanLobby::applySlotPlayerTemplate(GameSlot *slot, int playerTemplate)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->setPlayerTemplate(playerTemplate);
	game->resetAccepted();
	if (game->rva004477C7())
	{
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	else
	{
		AsciiString options;
		options.format("PlayerTemplate=%d", slot->getPlayerTemplate());
		TheLAN->RequestGameOptions(options, true);
	}

	GameSlot *local = game->getSlot(game->getLocalSlotNum());
	if (slot->m_name.compare(local->m_name) == 0)
	{
		m_prefs.rva0044DD1E(playerTemplate);
		m_prefs.write();
	}
	return true;
}

// Retail 0x004454A1, 273 bytes: vftable 0x00C3E098 slot 4, "Color=%d".
// Donor Rva00518BF0LanColor.cpp (BFME1 named it by address); a non-host
// only sends its own slot's color, and the local color preference is stored
// through the rowed GameModePreferences::rva0044DCB9 0x0044DCB9.
bool BfmeAptScreenLanLobby::applySlotColor(GameSlot *slot, int color)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->m_color = color;
	if (game->rva004477C7())
	{
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	else
	{
		LANGameSlot *lanSlot = slot->getLANSlot();
		if (!lanSlot)
			return false;
		if (!lanSlot->isLocalPlayer())
			return false;

		AsciiString options;
		options.format("Color=%d", slot->getColor());
		TheLAN->RequestGameOptions(options, true);
	}

	GameSlot *local = game->getSlot(game->getLocalSlotNum());
	if (slot->m_name.compare(local->m_name) == 0)
	{
		m_prefs.rva0044DCB9(color);
		m_prefs.write();
	}
	return true;
}

// Retail 0x004456B8, 260 bytes: vftable 0x00C3E098 slot 6, "Hero=%d". No
// BFME1 counterpart; the shape is applySlotPlayerTemplate's. Unlike its
// siblings it takes only the slot (ret 4): the slot already carries the
// choice, sent as the slot's hero byte and stored to the preferences from
// +0x5C.
bool BfmeAptScreenLanLobby::applySlotHero(GameSlot *slot)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	game->resetAccepted();
	if (game->rva004477C7())
	{
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	else
	{
		AsciiString options;
		options.format("Hero=%d", slot->rva003FF16F());
		TheLAN->RequestGameOptions(options, true);
	}

	GameSlot *local = game->getSlot(game->getLocalSlotNum());
	if (slot->m_name.compare(local->m_name) == 0)
	{
		m_prefs.rva0044DC54(slot->m_5c);
		m_prefs.write();
	}
	return true;
}

// Retail 0x00444D7B, 72 bytes: vftable 0x00C3E098 slot 14. Donor
// AptScreenLanLobbyCopyName.cpp (BFME1 copyLanNameRva005171A0), unchanged;
// the original name is unknown, so the address stays in it.
void BfmeAptScreenLanLobby::copyLanNameRva00444D7B(UnicodeString &dest)
{
	if (TheLAN)
		dest = TheLAN->GetMyName();
}

// Retail 0x00444279, 98 bytes: vftable 0x00C3E098 slot 2. No BFME1
// counterpart; the name is unknown. It asks for the serialized game info
// and, on the host, stores the game's ten rule ints (+0x60) through the
// rowed GameModePreferences::rva0044DDFB ("Rules") before writing.
void BfmeAptScreenLanLobby::saveRulesRva00444279()
{
	if (!TheLAN)
		return;
	TransportAddress address;
	TheLAN->requestSerializedGameInfo(true, &address);
	LANGameInfo *game = TheLAN->GetMyGame();
	if (game && game->rva004477C7())
	{
		m_prefs.rva0044DDFB(game->m_rules);
		m_prefs.write();
	}
}

// Retail 0x0044440C, 86 bytes: vftable 0x00C3E098 slot 8. No BFME1
// counterpart; the name is unknown. Stores the strategic scenario through
// the rowed GameModePreferences::setStrategicScenario, writes the
// preferences and refreshes the serialized game info.
bool BfmeAptScreenLanLobby::setScenarioRva0044440C(int scenario)
{
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	m_prefs.setStrategicScenario(scenario);
	m_prefs.write();
	TransportAddress address;
	TheLAN->requestSerializedGameInfo(true, &address);
	return true;
}

// Retail 0x00444F9C, 234 bytes: vftable 0x00C3E098 slot 7. Donor
// BfmeAptScreenLanLobby_bfmeMapChanged.cpp (BFME1 0x005175B0). Target game
// vslots called after the map size are 15 (resetStartSpots, rowed in
// LANGameInfo's vtable 0x00C3E518), 16 and 14 (resetAccepted); slot 16 takes
// the donor's adjustSlotsForMap name by Zero Hour's declaration order.
bool BfmeAptScreenLanLobby::bfmeMapChanged(const AsciiString *mapName)
{
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	AsciiString lowerMap = *mapName;
	lowerMap.toLower();
	game->setMapForwarder(lowerMap);
	const MapMetaData *map = TheMapCache->findMap(lowerMap);
	if (map)
	{
		game->getSlot(0)->setMapAvailability(true);
		game->setMapCRC(map->m_CRC);
		game->setMapSize(map->m_filesize);
		game->resetStartSpots();
		game->adjustSlotsForMap();
		game->resetAccepted();
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	return true;
}
