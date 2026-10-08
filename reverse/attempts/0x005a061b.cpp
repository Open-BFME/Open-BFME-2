// ?PopulateGamesListBox@AptOnlineCustomMatch@@QAEXXZ
// partial score=0.6 date=2026-10-08
// cl: /G7 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
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

class GameSpyStagingRoom
{
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual int rvaSlot20();
    virtual int rvaSlot24();
    unsigned char m_pad04[0x5C - 4];
    int m_type;
    unsigned char m_pad60[0xFE0 - 0x60];
    int m_id;
};
typedef std::map<Int, GameSpyStagingRoom *> StagingRoomMap;

class GameSlot
{
public:
	unsigned char m_pad00[0x30];
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
	GSI_SLOT(16) GSI_SLOT(17) GSI_SLOT(18) GSI_SLOT(19) GSI_SLOT(20) GSI_SLOT(21) GSI_SLOT(22) GSI_SLOT(23)
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

class GameWindow;
void GadgetListBoxGetSelected(GameWindow *, int *);
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetSelected(GameWindow *, int);
void GadgetListBoxSetTopVisibleEntry(GameWindow *, int);
int Rva003253BEGet(GameWindow *, int, int);
class ModuleData;
class Rva00601941 { public: void rva00601941(); };
class Rva00580B40 { public: void rva00580B40(const ModuleData *); };
class LANGameInfo;
class Rva0058113D { public: LANGameInfo *rva0058113D(unsigned int); };
class AptMpGameSetup { public: void rva0043FA68(GameInfo *); };
class Rva0043DB66ByteOneSetter { public: void enable(); };
class GameWindowManager {
public:
#define W(n) virtual void slot##n();
    W(0) W(1) W(2) W(3) W(4) W(5) W(6) W(7) W(8) W(9)
    W(10) W(11) W(12) W(13) W(14) W(15) W(16) W(17) W(18) W(19)
    W(20) W(21) W(22) W(23) W(24) W(25) W(26) W(27) W(28) W(29)
    W(30) W(31) W(32) W(33) W(34) W(35) W(36) W(37) W(38) W(39)
    W(40) W(41) W(42) W(43) W(44) W(45) W(46) W(47) W(48) W(49) W(50) W(51)
#undef W
    virtual void slotD0(GameWindow *);
};
extern GameWindowManager *TheWindowManager;
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int Rva00524EF4AptCall(Rva00222A8BTarget *, void *, const char *, const char *);
struct CustomMatchOwner {
    unsigned char m_pad00[0x274];
    void *m_movie;
};
class AptOnlineCustomMatch
{
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual const char *slotAptPath();
    void MpOwnerGetLocalPlayerName(UnicodeString &name);
    GameSpyStagingRoom *GetGameToJoin();
    void PopulateGamesListBox();
    int rva0059F496(GameSpyStagingRoom *);

private:
    unsigned char m_pad004[0x58 - 4];
    CustomMatchOwner *m_owner;
    unsigned char m_pad05c[0xEC - 0x5C];
    int m_gameType;
    unsigned char m_pad0f0[0x320 - 0xF0];
    int m_savedGame;
    unsigned char m_pad324[0x450 - 0x324];
    unsigned char m_gameList[0x48C - 0x450];
    GameWindow *m_listBox;
    unsigned char m_pad490[0x4B8 - 0x490];
    int m_gameToJoinID;
    unsigned char m_pad4bc[4];
    bool m_joinEnabled;
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

// ?PopulateGamesListBox@AptOnlineCustomMatch@@QAEXXZ present-unmatched
void AptOnlineCustomMatch::PopulateGamesListBox()
{
    if (!m_listBox || m_savedGame)
        return;
    int selected = -1;
    int newSelected = -1;
    int gameID = 0;
    GadgetListBoxGetSelected(m_listBox, &selected);
    if (selected != -1)
        gameID = Rva003253BEGet(m_listBox, selected, 3);
    int top = GadgetListBoxGetTopVisibleEntry(m_listBox);
    GadgetListBoxReset(m_listBox);
    ((Rva00601941 *)m_gameList)->rva00601941();
    StagingRoomMap *rooms = TheGameSpyInfo->getStagingRoomList();
    for (StagingRoomMap::iterator it = rooms->begin(); it != rooms->end(); ++it) {
        GameSpyStagingRoom *room = it->second;
        if (!room || m_gameType != room->m_type)
            continue;
        ((Rva00580B40 *)m_gameList)->rva00580B40((const ModuleData *)room);
    }
    unsigned int index = 0;
    GameSpyStagingRoom *room;
    while ((room = (GameSpyStagingRoom *)((Rva0058113D *)m_gameList)->rva0058113D(index)) != 0) {
        int row = rva0059F496(room);
        if (room->m_id == gameID) {
            newSelected = row;
            ((AptMpGameSetup *)((char *)this + 0x70))->rva0043FA68((GameInfo *)room);
        }
        ++index;
    }
    GadgetListBoxSetSelected(m_listBox, newSelected);
    GadgetListBoxSetTopVisibleEntry(m_listBox, top);
    if (newSelected < 0) {
        if (gameID != 0)
            TheWindowManager->slotD0(0);
        ((AptMpGameSetup *)((char *)this + 0x70))->rva0043FA68(0);
disableJoin:
        if (m_joinEnabled) {
            m_joinEnabled = false;
            void *movie = m_owner->m_movie;
            Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,
                movie, slotAptPath(), "DisableButtonJoinGame");
        }
finish:
        ((Rva0043DB66ByteOneSetter *)((char *)this + 0x70))->enable();
        return;
    }
    StagingRoomMap *selectedRooms = TheGameSpyInfo->getStagingRoomList();
    int id = Rva003253BEGet(m_listBox, newSelected, 3);
    StagingRoomMap::iterator found = selectedRooms->find(id);
    if (found == selectedRooms->end())
        goto disableJoin;
    GameSpyStagingRoom *game = found->second;
    int maxPlayers = game->rvaSlot24();
    if (game->rvaSlot20() == maxPlayers)
        goto disableJoin;
    if (m_joinEnabled)
        goto finish;
    m_joinEnabled = true;
    void *movie = m_owner->m_movie;
    Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,
        movie, slotAptPath(), "EnableButtonJoinGame");
    goto finish;
}
