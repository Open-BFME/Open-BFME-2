// ?GamesListTooltipFunc@AptOnlineCustomMatch@@SAXPAVGameWindow@@PAVWinInstanceData@@I@Z
// partial score=0.9907 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// stlport
// AptOnlineCustomMatch.cpp -- AptOnlineCustomMatch members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and asserts TheGameSpyInfo and the current game exist; retail
// supplies the bytes and skips both instead.
//
// The game owner's name is slot 0's name (+0x30, a UnicodeString). The
// current game comes from GameSpyInfo's virtual at +0xD4 (Zero Hour's
// getCurrentStagingRoom; the name is carried from that donor).
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>

typedef int Int;

class GameSpyStagingRoom;
class GameWindow;
class WinInstanceData;
class PlayerInfo;
typedef std::map<Int, GameSpyStagingRoom *> StagingRoomMap;

class GameSlot
{
public:
	unsigned char m_pad00[0x30];
	bool isHuman() const;
	UnicodeString m_name;				// +0x30
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slotNum);			// 0x003FF29F
};

#define GSI_SLOT(n) virtual void slot##n();

class GameSpyInfoInterface
{
public:
	GSI_SLOT(00) GSI_SLOT(01) GSI_SLOT(02) GSI_SLOT(03) GSI_SLOT(04) GSI_SLOT(05) GSI_SLOT(06) GSI_SLOT(07)
	GSI_SLOT(08) GSI_SLOT(09) GSI_SLOT(10) GSI_SLOT(11) GSI_SLOT(12) GSI_SLOT(13) GSI_SLOT(14) GSI_SLOT(15)
	GSI_SLOT(16) GSI_SLOT(17) GSI_SLOT(18) GSI_SLOT(19) GSI_SLOT(20) GSI_SLOT(21) virtual PlayerInfo *rva005A09E9(const char *name); GSI_SLOT(23)
	GSI_SLOT(24) GSI_SLOT(25) GSI_SLOT(26) GSI_SLOT(27) GSI_SLOT(28) GSI_SLOT(29) GSI_SLOT(30) GSI_SLOT(31)
	GSI_SLOT(32) GSI_SLOT(33) GSI_SLOT(34) GSI_SLOT(35) GSI_SLOT(36) GSI_SLOT(37) GSI_SLOT(38) GSI_SLOT(39)
	GSI_SLOT(40)
	virtual StagingRoomMap *getStagingRoomList();	// +0xA4
	GSI_SLOT(42) GSI_SLOT(43) GSI_SLOT(44) GSI_SLOT(45) GSI_SLOT(46) GSI_SLOT(47)
	GSI_SLOT(48) GSI_SLOT(49) GSI_SLOT(50) GSI_SLOT(51) GSI_SLOT(52)
	virtual GameInfo *getCurrentStagingRoom();	// +0xD4
};

#undef GSI_SLOT

extern GameSpyInfoInterface *TheGameSpyInfo;		// 0x00E02320

class AptOnlineCustomMatch
{
public:
	static void GamesListTooltipFunc(GameWindow *, WinInstanceData *, unsigned int);
	void MpOwnerGetLocalPlayerName(UnicodeString &name);
	GameSpyStagingRoom *GetGameToJoin();

private:
	unsigned char m_pad000[0x4b8];
	Int m_gameToJoinID;				// +0x4B8
};

// AptOnlineCustomMatch::MpOwnerGetLocalPlayerName, retail 0x0059EBAF.
void AptOnlineCustomMatch::MpOwnerGetLocalPlayerName(UnicodeString &name)
{
	if (!TheGameSpyInfo)
		return;
	GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();
	if (!myGame)
		return;
	name.set(myGame->getSlot(0)->m_name);
}

// AptOnlineCustomMatch::GetGameToJoin, retail 0x005A0808: the staging room
// for the remembered game id (+0x4B8), or NULL (Zero Hour's staging room
// map lookup; the list comes from GameSpyInfo's virtual at +0xA4).
GameSpyStagingRoom *AptOnlineCustomMatch::GetGameToJoin()
{
	StagingRoomMap *srm = TheGameSpyInfo->getStagingRoomList();
	if (!srm)
		return 0;
	StagingRoomMap::iterator it = srm->find(m_gameToJoinID);
	if (it == srm->end())
		return 0;
	return it->second;
}

struct PlayerInfo { unsigned char reserved[0xC]; int wins, losses; };
struct RGBColor;
class Mouse { public: void rva001EEA6D(UnicodeString, int, const RGBColor *, float); };
extern Mouse *TheMouse;
class GameTextInterface {
public:
#define T(n) virtual void t##n();
 T(0) T(1) T(2) T(3) T(4) T(5) T(6) T(7) T(8) T(9) T(10) T(11) T(12) T(13) T(14)
#undef T
 virtual UnicodeString fetch(const char *, bool *exists = 0);
};
extern GameTextInterface *TheGameText;
extern int g_Va00E063EC;
class Rva003FF1C2 { public: bool rva003FF1C2() const; };
int GadgetListBoxGetEntryBasedOnXY(GameWindow *, int, int, int &, int &);
int Rva003253BEGet(GameWindow *, int, int);
void AptOnlineCustomMatch::GamesListTooltipFunc(GameWindow *window, WinInstanceData *, unsigned int mouse)
{
 if (!g_Va00E063EC) return;
 int row, column;
 int x = mouse & 0xffff;
 int y = mouse >> 16;
 GadgetListBoxGetEntryBasedOnXY(window, x, y, row, column);
 if (row == -1 || column == -1) {
  TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
  return;
 }
 StagingRoomMap *rooms = TheGameSpyInfo->getStagingRoomList();
 int key = Rva003253BEGet(window, row, 3);
 StagingRoomMap::iterator it = rooms->find(key);
 if (it == rooms->end()) {
  TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
  return;
 }
 GameInfo *room = (GameInfo *)it->second;
 switch (column) {
 case 0:
  if (Rva003253BEGet(window, row, 0))
   TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:UserMapIcon"), -1, 0, 1.0f);
  break;
 case 1:
  if (Rva003253BEGet(window, row, 1))
   TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:AdvSetting"), -1, 0, 1.0f);
  break;
 case 2:
  if (Rva003253BEGet(window, row, 2))
   if (((Rva003FF1C2 *)room)->rva003FF1C2())
    TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:MpSaveGame"), -1, 0, 1.0f);
   else
    TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:PasswordIcon"), -1, 0, 1.0f);
  break;
 default: {
  UnicodeString tooltip;
  for (int i = 0; i < 8; ++i) {
   GameSlot *slot = room->getSlot(i);
   if (slot->isHuman()) {
    if (tooltip.getLength()) tooltip.concat((const unsigned short *)L"\n");
    tooltip.concat(slot->m_name);
    AsciiString name;
    name.translate(slot->m_name);
    PlayerInfo *info = TheGameSpyInfo->rva005A09E9(name.str());
    if (info) {
     UnicodeString record;
     record.format((const unsigned short *)L" (%d/%d)", info->wins, info->losses);
     tooltip.concat(record);
    }
   }
  }
  TheMouse->rva001EEA6D(tooltip, -1, 0, 1.0f);
  break;
 }
 }
}
