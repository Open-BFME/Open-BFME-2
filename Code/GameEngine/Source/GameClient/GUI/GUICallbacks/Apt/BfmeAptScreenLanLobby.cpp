// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's LAN lobby screen: the per-slot option setters and their siblings
// that the lobby's callback vftable at 0x00C3E098 holds (slot 12 is
// MpOwnerSelectTeam). Retail places them together at 0x0044440C..0x004457BC,
// after Rva00444525Init (which pushes "LanLobby.apt").
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/
// BfmeAptScreenLanLobby_*.cpp (f57439f7f4). Identity is carried per body by
// its option key string ("Team=%d", ...) and by the shared call pattern;
// BFME1's class and method names are donor names, not target facts. The
// BFME2 names (class AptLanLobby; MpOwnerSelectTeam, MpOwnerSelectHandicap,
// MpOwnerSelectPlayer, MpOwnerSelectStartPosition, MpOwnerGetLocalPlayerName,
// MpOwnerPrintMessage, MpOwnerSelectColor, MpOwnerSelectPlayerTemplate,
// MpOwnerSelectHero) come from WorldBuilder's AptLanLobby.cpp, which asserts
// in each body with the same callees and option strings, and from retail's own
// "AptLanLobby::..." callback strings. The other rva-named members keep
// address names.
//
// Target facts (all read from retail): TheLAN is the global at 0x009FE958
// (defined in Rva00446A77Enable.cpp; the g_00DFE958 spelling is aliased
// there); LANAPI vslot 56 returns the current LANGameInfo, vslot 25 sends a
// game-options string, vslot 26 asks the host for serialized game info.
// LANAPI vslot 55 returns the local player name by value.
// LANGameInfo vslot 14 is resetAccepted, and the non-virtual
// LANGameInfo::amIHost 0x004477C7 is the host test (slot 0 is local).
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
// byte is the rowed GameSlot::encodeHero 0x003FF16F, and +0x5C is the
// value the hero preference stores.

#include "ascii_string.h"
#include "unicode_string.h"

class LANGameSlot;

enum SlotState
{
	SLOT_PLAYER = 6
};

struct GameSlotConnectInfo
{
	unsigned int m_nat;
	unsigned short m_port;
};

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
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
	bool isAI() const;
	SlotState getState() const { return m_state; }
	unsigned char encodeHero() const;
	int getColor() const { return m_color; }
	int getPlayerTemplate() const { return m_playerTemplate; }
	int getStartPos() const { return m_startPos; }
	int getTeamNumber() const { return m_teamNumber; }
	int getHandicap() const { return m_handicap; }

	SlotState m_state; // +0x04
	unsigned char m_pad08[0x0C - 0x08];
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
	bool amIHost() const;
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
	virtual void v19(int value) = 0;
	virtual void v20() = 0;
	virtual void v21(UnicodeString text, int kind, int unused) = 0;
	virtual void v22(int value) = 0;
	virtual void v23(bool value) = 0;
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
	virtual void OnPlayerLeave(UnicodeString player) = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v40(const UnicodeString &name, int text) = 0;
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
	virtual bool v54() = 0;
	virtual UnicodeString GetMyName() = 0;
	virtual LANGameInfo *GetMyGame() = 0;
	virtual void v57() = 0;
	virtual void v58() = 0;
	virtual void v59() = 0;
	virtual void v60() = 0;
	virtual void v61() = 0;
	virtual void v62() = 0;
	virtual void v63() = 0;
	virtual int v64(const UnicodeString &text, int kind) = 0;
};

class LANAPI; extern LANAPI *TheLAN;

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

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// Address-derived calls through the pointer held at the matched, address-named
// global at VA 0x00E032FC. The target class and member identities remain
// address-derived.
class Rva0054CFB8Target;

// Target evidence: 0x0054CFB8 consumes two by-value reference handles at
// stack offsets +0x14/+0x18 and releases both through the matched helper.
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0023E8D8;

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;

	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class Rva0023E8D8 : public TreeHintRef00217D4C
{
};

class Rva0054D2DDTarget
{
public:
	__declspec(noinline) void method(int type, const UnicodeString &text, const UnicodeString &title);
	void method(int type, const UnicodeString &text, const UnicodeString &title,
		TreeHintRef00217D4C callback, TreeHintRef00217D4C callback2);
	unsigned char m_unknown00[4];
	Rva0054CFB8Target *m_child04;
};

class Rva0054CFB8Target
{
public:
	Rva0054CFB8Target(int id, const AsciiString &screenName);
	void method(int type, const UnicodeString &text, const UnicodeString &title,
		TreeHintRef00217D4C callback, TreeHintRef00217D4C callback2);
private:
	char m_pad[0x2c];
};

class Rva0054D3D9Target
{
public:
	void method(int type, const UnicodeString &text, const UnicodeString &title);
};

class Rva0054D2CF
{
public:
	Rva0054D2CF(int id, const AsciiString &screenName);
	virtual ~Rva0054D2CF();
	__declspec(noinline) void Rva0054D308(int type, const UnicodeString &text, const UnicodeString &title,
		Rva0023E8D8 callback);

private:
	Rva0054CFB8Target *m_child04;
};

extern int g_Va00E032FC;

void Rva00437E84(int type, const UnicodeString &text, const UnicodeString &title);
void Rva00437EAC(int type, const UnicodeString &text, const UnicodeString &title);
void Rva00437E9C(int value);

// Unrowed 0x0044C0A8 (158 bytes, cdecl, takes both strings by value and a
// pointer that defaults to 0x004B3FD0 when null), pinned by address.
void Rva0044C0A8(UnicodeString title, UnicodeString text, void *callback);

struct Rva00511730State;
extern Rva00511730State *g_Va00E046B8;

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

class AptLanLobby
{
public:
	bool MpOwnerSelectTeam(GameSlot *slot, int team);
	bool MpOwnerSelectHandicap(GameSlot *slot, int handicap);
	bool MpOwnerSelectStartPosition(GameSlot *slot, int startPos);
	bool MpOwnerSelectPlayerTemplate(GameSlot *slot, int playerTemplate);
	bool MpOwnerSelectColor(GameSlot *slot, int color);
	bool MpOwnerSelectHero(GameSlot *slot);
	void MpOwnerGetLocalPlayerName(UnicodeString &dest);
	void saveRulesRva00444279();
	bool setScenarioRva0044440C(int scenario);
	bool bfmeMapChanged(const AsciiString *mapName);
	bool MpOwnerSelectPlayer(GameSlot *slot, SlotState state, int unused);
	void rva00444DC3(bool starting);
	void MpOwnerPrintMessage(const UnicodeString &text, int kind);
	void rva0044421C();
	void rva004441C5(bool flag, int unused);

private:
	unsigned char m_pad00[0x0C];
	Rva0043DB47DoubleSetter m_0c; // +0x0C
	unsigned char m_pad0d[0x88 - 0x0D];
	int m_88; // +0x88
	unsigned char m_pad8c[0x408 - 0x8C];
	GameModePreferences m_prefs; // +0x408
	unsigned char m_pad40c[0x428 - 0x40C];
	int m_428; // +0x428
};

// Retail 0x004449FD, 198 bytes. BFME2 drops the donor's second
// resetAccepted on the host path.
bool AptLanLobby::MpOwnerSelectTeam(GameSlot *slot, int team)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->m_teamNumber = team;
	game->resetAccepted();
	if (game->amIHost())
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
// BFME1 has no handicap option; the body is MpOwnerSelectTeam's donor shape
// (including its second resetAccepted on the host path) over +0x20, and the
// name follows that family.
bool AptLanLobby::MpOwnerSelectHandicap(GameSlot *slot, int handicap)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->m_handicap = handicap;
	game->resetAccepted();
	if (game->amIHost())
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
bool AptLanLobby::MpOwnerSelectStartPosition(GameSlot *slot, int startPos)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->m_startPos = startPos;
	slot->m_startPos14 = startPos;
	if (game->amIHost())
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
bool AptLanLobby::MpOwnerSelectPlayerTemplate(GameSlot *slot, int playerTemplate)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->setPlayerTemplate(playerTemplate);
	game->resetAccepted();
	if (game->amIHost())
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
bool AptLanLobby::MpOwnerSelectColor(GameSlot *slot, int color)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	slot->m_color = color;
	if (game->amIHost())
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
// BFME1 counterpart; the shape is MpOwnerSelectPlayerTemplate's. Unlike its
// siblings it takes only the slot (ret 4): the slot already carries the
// choice, sent as the slot's hero byte and stored to the preferences from
// +0x5C.
bool AptLanLobby::MpOwnerSelectHero(GameSlot *slot)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	game->resetAccepted();
	if (game->amIHost())
	{
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	else
	{
		AsciiString options;
		options.format("Hero=%d", slot->encodeHero());
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
void AptLanLobby::MpOwnerGetLocalPlayerName(UnicodeString &dest)
{
	if (TheLAN)
		dest = TheLAN->GetMyName();
}

// Retail 0x00444279, 98 bytes: vftable 0x00C3E098 slot 2. No BFME1
// counterpart; the name is unknown. It asks for the serialized game info
// and, on the host, stores the game's ten rule ints (+0x60) through the
// rowed GameModePreferences::rva0044DDFB ("Rules") before writing.
void AptLanLobby::saveRulesRva00444279()
{
	if (!TheLAN)
		return;
	TransportAddress address;
	TheLAN->requestSerializedGameInfo(true, &address);
	LANGameInfo *game = TheLAN->GetMyGame();
	if (game && game->amIHost())
	{
		m_prefs.rva0044DDFB(game->m_rules);
		m_prefs.write();
	}
}

// Retail 0x0044440C, 86 bytes: vftable 0x00C3E098 slot 8. No BFME1
// counterpart; the name is unknown. Stores the strategic scenario through
// the rowed GameModePreferences::setStrategicScenario, writes the
// preferences and refreshes the serialized game info.
bool AptLanLobby::setScenarioRva0044440C(int scenario)
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
bool AptLanLobby::bfmeMapChanged(const AsciiString *mapName)
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

// Retail 0x00444B90, 276 bytes: vftable 0x00C3E098 slot 9. Donor
// BfmeAptScreenLanLobby_rva00517B60.cpp (BFME1 0x00517B60, an address name
// there too). LANAPI vslot 37 is the donor's OnPlayerLeave. BFME2 skips the
// update when a non-player slot already has the state, and resets the
// accepted flags only when the AI-ness changes.
bool AptLanLobby::MpOwnerSelectPlayer(GameSlot *slot, SlotState state, int unused)
{
	if (!TheLAN)
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if (!game)
		return false;

	GameSlotConnectInfo info;
	if (slot->getState() == SLOT_PLAYER)
	{
		UnicodeString player = slot->m_name;
		info.m_nat = 0;
		info.m_port = 0;
		slot->setState(state, UnicodeString::TheEmptyString, &info);
		game->resetAccepted();
		TheLAN->OnPlayerLeave(player);
	}
	else if (slot->getState() != state)
	{
		bool wasAI = slot->isAI();
		info.m_nat = 0;
		info.m_port = 0;
		slot->setState(state, UnicodeString::TheEmptyString, &info);
		if (slot->isAI() ^ wasAI)
			game->resetAccepted();
		TransportAddress address;
		TheLAN->requestSerializedGameInfo(true, &address);
	}
	return true;
}

// Target body pushes (type, text, title), loads the object pointer from the
// matched global g_Va00E032FC at VA 0x00E032FC and calls address-derived
// method 0x0054D2DD.
void Rva00437E84(int type, const UnicodeString &text, const UnicodeString &title)
{
	((Rva0054D2DDTarget *)g_Va00E032FC)->method(type, text, title);
}

// ?method@Rva0054D2DDTarget@@QAEXHABVUnicodeString@@0@Z @0x0054D2DD 43B.
// Target evidence: the Ghidra boundary loads the child pointer at +4 and
// forwards the three arguments with two empty callback handles to 0x0054CFB8.
// The child slot is a layout fact; the original class and method identity
// remain unresolved.
void Rva0054D2DDTarget::method(int type, const UnicodeString &text,
	const UnicodeString &title)
{
	m_child04->method(type, text, title, TreeHintRef00217D4C(),
		TreeHintRef00217D4C());
}

Rva0054D2CF::Rva0054D2CF(int id, const AsciiString &screenName)
	: m_child04(new Rva0054CFB8Target(id, screenName))
{
}

void Rva0054D2CF::Rva0054D308(int type, const UnicodeString &text,
	const UnicodeString &title, Rva0023E8D8 callback)
{
	m_child04->method(type, text, title, callback, TreeHintRef00217D4C());
}

void Rva0054D2DDTarget::method(int type, const UnicodeString &text,
	const UnicodeString &title, TreeHintRef00217D4C callback,
	TreeHintRef00217D4C callback2)
{
	m_child04->method(type, text, title, callback, callback2);
}

// Same target-proven forwarder shape; the callee's identity remains its RVA.
void Rva00437EAC(int type, const UnicodeString &text, const UnicodeString &title)
{
	((Rva0054D3D9Target *)g_Va00E032FC)->method(type, text, title);
}

// Retail 0x00444DC3, 166 bytes: vftable 0x00C3E098 slot 16. BFME1's
// counterpart is the dump d_00517220 (its slot 14), so the name is unknown.
// When starting it shows "QM:STARTINGGAME" over "APT:None" through
// 0x00437E84 (type 4) and, if LANAPI vslot 54 holds, calls vslot 22 with 0;
// BFME2 drops BFME1's vslot 14 call on the other path. Otherwise it passes 1
// to 0x00437E9C.
void AptLanLobby::rva00444DC3(bool starting)
{
	if (starting)
	{
		Rva00437E84(4, TheGameText->fetch("APT:None"), TheGameText->fetch("QM:STARTINGGAME"));
		if (TheLAN && TheLAN->v54())
			TheLAN->v22(0);
	}
	else
	{
		Rva00437E9C(1);
	}
}

// Retail 0x004448E5, 280 bytes: vftable 0x00C3E098 slot 17. No BFME1
// counterpart; the name is unknown. Kinds 0 and 1 pass the text through
// LANAPI vslot 64 (with 3) and post the result under L"SYSTEM" through
// vslot 40; kind 1 first hands (L"", text) to 0x0044C0A8 while
// g_Va00E046B8 is unset. Kind 2 goes to vslot 21 as (text, 3, 0).
void AptLanLobby::MpOwnerPrintMessage(const UnicodeString &text, int kind)
{
	if (!TheLAN)
		return;

	switch (kind)
	{
	case 0:
		TheLAN->v40(UnicodeString(L"SYSTEM"), TheLAN->v64(text, 3));
		break;
	case 1:
		if (!g_Va00E046B8)
			Rva0044C0A8(UnicodeString(L""), text, 0);
		TheLAN->v40(UnicodeString(L"SYSTEM"), TheLAN->v64(text, 3));
		break;
	case 2:
		TheLAN->v21(text, 3, 0);
		break;
	}
}

// Retail 0x0044421C, 36 bytes: vftable 0x00C3E098 slot 15. Name unknown;
// the start notice's LANAPI vslot 54 test and vslot 22 call, with 1.
void AptLanLobby::rva0044421C()
{
	if (TheLAN && TheLAN->v54())
		TheLAN->v22(1);
}

// Retail 0x004441C5, 67 bytes: vftable 0x00C3E098 slot 18. Name unknown;
// it sets +0x428 to 12, then passes either (+0x88 == 1) to LANAPI vslot 23
// or 1 to vslot 19.
void AptLanLobby::rva004441C5(bool flag, int unused)
{
	if (!TheLAN)
		return;
	m_428 = 12;
	if (flag)
		TheLAN->v23(m_88 == 1);
	else
		TheLAN->v19(1);
}
