// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Rva00445BAALanLobbyTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z,
// retail 0x00445BAA..0x00445DA5 (507 bytes, cdecl, plain ret). The LAN lobby's
// custom games list tooltip callback: AptLanLobby::InitGadgets (0x00445DA5)
// installs it on the "LanLobby::CustomGamesList" window with winSetTooltipFunc.
// WorldBuilder names it AptLanLobby::GamesListTooltipFunc (AptLanLobby.cpp,
// debug build 0x014144F0); the address name stays the ledger identity.
//
// Source shape from the WorldBuilder debug body (the retail body merges it):
// the three "no game under the cursor" exits are separate blocks, each calling
// the mouse tooltip setter with the empty string and returning (row or column
// -1, then a failed ValidateGameInfo). Cases 0..2 test the column's item data
// into a local first (retail keeps the zero in ESI and compares against it);
// every case ends in the common exit. Merging the three empty-string tails
// into one trailing call, or returning from each case, leaves the
// `mov ecx,esp` / `mov [ebp-0x18],esp` pair of the final by-value copy in the
// wrong order.
//
// Target evidence: nothing happens without the lobby screen (0x00E03354); the
// game comes from column 3's item data; column 0, 1 and 2 give their own
// TOOLTIP: strings only when that column's item data is set (column 2 picks
// MpSaveGame or GameStarted by the game's 16-byte nonzero test 0x003FF1C2);
// other columns list the human players' names, one per line. Donor: Open-BFME-1
// GameNetwork/GameSpy/LanLobbyGamesTooltip.cpp (Rva00518150LanLobbyTooltip,
// BFME1 0x00518150), read as a semantic guide only.
//
// Callees resolve through rows: GadgetListBoxGetEntryBasedOnXY 0x00323F6F,
// GadgetListBoxGetItemData 0x003253BE, LANAPI::ValidateGameInfo 0x00449969,
// Mouse 0x001EEA6D, StringBase ctor/concat 0x00037050/0x00006A2A and the slot
// reads of TheGameText (vslot 15) and GameInfo::getConstSlot.

#include "unicode_string.h"

class WinInstanceData;

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *window, WinInstanceData *data, unsigned int mouse));
	void *winGetUserData();
};


int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, int x, int y, int &row, int &column);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);

class GameSlot
{
public:
	void setPlayerTemplate(int playerTemplate);
	void setMapAvailability(bool available);
	bool isHuman() const;
	char m_pad00[0xC];
	int m_color; // +0x0C
	char m_pad10[0x20];
	UnicodeString m_name; // +0x30
	char m_pad34[0xC];
	int m_40; // +0x40
};

class AsciiString;
class GameInfo
{
public:
	int getNumPlayers() const;
	int getNumOpenOrOccupiedSlots() const;
	GameSlot *getSlot(int index);
	void setMapForwarder(AsciiString mapName);
	void setMapCRC(unsigned int mapCRC);
	void setMapSize(unsigned int mapSize);
	// Unrowed 0x003FF1A7 (27 bytes; stores the game mode at +0x5C and resets
	// the rules for it), pinned by address.
	void rva003FF1A7(int mode);
	const GameSlot *getConstSlot(int slot) const;
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
};

class LANGameInfo : public GameInfo
{
public:
	unsigned char m_pad004[0x44 - 0x04];
	unsigned int m_mapCRC; // +0x44
	unsigned int m_mapSize; // +0x48
	unsigned char m_pad04c[0x58 - 0x4C];
	int m_58; // +0x58
	int m_5c; // +0x5C (game mode)
	int m_rules[10]; // +0x60
	int m_88; // +0x88
	unsigned char m_pad08c[0xF5C - 0x8C];
	LANGameInfo *m_next; // +0xF5C
};

// GameInfo's 16-byte nonzero test (rowed under its address name).
class Rva003FF1C2
{
public:
	bool rva003FF1C2() const;
};

void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);

class UnicodeString;
class TransportAddress;
class LANGameInfo;
class GameWindow;
class WinInstanceData;
class LANAPI
{
	friend class AptLanLobby;
	friend void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);
public:
	LANAPI();
	virtual void v00();
	virtual void init();
	virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
	virtual void v06(); virtual void v07(); virtual void v08();
	virtual void reset();
	virtual void update();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void RequestLocations();
	virtual void v16(LANGameInfo *game, TransportAddress *address);
	virtual void v17(); virtual void v18(); virtual void v19();
	virtual void RequestHasMap();
	virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26();
	virtual void v27(UnicodeString text, int value);
	virtual void v28();
	virtual void RequestSetName(UnicodeString name);
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
	virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50();
	virtual LANGameInfo *v51();
	virtual void v52();
	virtual bool SetLocalIP(unsigned int ip);
	virtual bool AmIHost();
	virtual void v55();
	virtual LANGameInfo *GetMyGame();
	virtual void v57();
	virtual void v58();

	unsigned char m_pad04[0x10 - 0x04];
	LANGameInfo *m_games;
	unsigned char m_pad14[0x5D - 0x14];
	unsigned char m_isInLANMenu; // +0x5D
	unsigned char m_pad5e[0x60 - 0x5E];
protected:
	bool ValidateGameInfo(LANGameInfo *game);
};

extern LANAPI *TheLAN;

struct RGBColor;

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

extern Mouse *TheMouse;

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

class AptLanLobby { static AptLanLobby *s_instance; public: static AptLanLobby *Instance() { return s_instance; } }; // Existing storage owner; this body only tests zero.

// Retail 0x00445BAA, 507 bytes: the custom games list tooltip. Donor
// Open-BFME-1 GameNetwork/GameSpy/LanLobbyGamesTooltip.cpp
// (Rva00518150LanLobbyTooltip, BFME1 0x00518150), whose address name it
// keeps. BFME2 target evidence: it does nothing without the lobby screen
// (0x00E03354), reads the game from column 3's item data, and gives columns
// 0..2 their own TOOLTIP: strings (each only when that column's item data is
// set; column 2 picks MpSaveGame or GameStarted by the game's 16-byte
// nonzero test); other columns list the human players' names.
void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *, unsigned int mouse)
{
	if (!AptLanLobby::Instance())
		return;

	int x, y, row, column;
	x = mouse & 0xffff;
	y = mouse >> 16;
	GadgetListBoxGetEntryBasedOnXY(window, x, y, row, column);
	if (row == -1 || column == -1)
	{
		TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		return;
	}
	LANGameInfo *game = (LANGameInfo *)GadgetListBoxGetItemData(window, row, 3);
	if (!TheLAN->ValidateGameInfo(game))
		game = 0;
	if (game == 0)
	{
		TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		return;
	}
	switch (column)
	{
	case 0:
		{
			void *item = GadgetListBoxGetItemData(window, row, 0);
			if (item != 0)
				TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:UserMapIcon"), -1, 0, 1.0f);
		}
		break;
	case 1:
		{
			void *item = GadgetListBoxGetItemData(window, row, 1);
			if (item != 0)
				TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:AdvSetting"), -1, 0, 1.0f);
		}
		break;
	case 2:
		{
			void *item = GadgetListBoxGetItemData(window, row, 2);
			if (item != 0)
			{
				if (((const Rva003FF1C2 *)game)->rva003FF1C2())
					TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:MpSaveGame"), -1, 0, 1.0f);
				else
					TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:GameStarted"), -1, 0, 1.0f);
			}
		}
		break;
	default:
		{
			UnicodeString tooltip;
			for (int i = 0; i < 8; ++i)
			{
				const GameSlot *slot = game->getConstSlot(i);
				if (slot->isHuman())
				{
					if (tooltip.getLength() != 0)
						tooltip += (const unsigned short *)L"\n";
					tooltip += slot->m_name;
				}
			}
			TheMouse->rva001EEA6D(tooltip, -1, 0, 1.0f);
		}
		break;
	}
}
