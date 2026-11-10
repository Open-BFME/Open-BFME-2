// cl: /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
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

// Keep STLport4.5.3's integer comparison inline without a competing copy.
namespace _STL {
template<> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int& a,const int& b) const
{ return a < b; }
}

typedef int Int;

class GameWindow;
class WinInstanceData;
class PlayerInfo;
class GameSpyStagingRoom;
typedef std::map<Int, GameSpyStagingRoom *> StagingRoomMap;

#include "../../../../../Include/GameNetwork/GameInfo.h"


#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"

extern GameSpyInfoInterface *TheGameSpyInfo;		// 0x00E02320

struct CustomMatchOwner { char beforeMovie[0x274]; void *movie; };
class AptOnlineCustomMatch
{
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
 virtual void slot8(); virtual void slot9(); virtual const char *slotAptPath();
 void PopulateGamesListBox();
	static void GamesListTooltipFunc(GameWindow *, WinInstanceData *, unsigned int);
	int rva0059F496(GameSpyStagingRoom *);
	void MpOwnerGetLocalPlayerName(UnicodeString &name);
	GameSpyStagingRoom *GetGameToJoin();

private:
 unsigned char m_pad004[0x58-4];
 CustomMatchOwner *owner58;
 unsigned char m_pad05c[0xec-0x5c];
 int mode;
 unsigned char m_pad0f0[0x320-0xf0];
 int savedGame;
 unsigned char m_pad324[0x450-0x324];
 unsigned char gameList[0x48c-0x450];
 GameWindow *list;
 unsigned char m_pad490[0x4b8-0x490];
	Int m_gameToJoinID;				// +0x4B8
 char pad4bc[4]; bool joinEnabled;
};

// AptOnlineCustomMatch::MpOwnerGetLocalPlayerName, retail 0x0059EBAF.
void AptOnlineCustomMatch::MpOwnerGetLocalPlayerName(UnicodeString &name)
{
	if (!TheGameSpyInfo)
		return;
	GameInfo *myGame = reinterpret_cast<GameInfo *>(TheGameSpyInfo->getCurrentStagingRoom());
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

// Native 005A08C8..005A0B4C; WB names the tooltip callback.
// The icon getter returns an integer, compared with the shared zero value.
struct PlayerInfo { unsigned char reserved[0xC]; int wins, losses; };
struct RGBColor;
#include "../../../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
extern int g_currentAptOnlineCustomMatch;
class Rva003FF1C2 { public: bool rva003FF1C2() const; };
int GadgetListBoxGetEntryBasedOnXY(GameWindow *, int, int, int &, int &);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);
void AptOnlineCustomMatch::GamesListTooltipFunc(GameWindow *window, WinInstanceData *, unsigned int mouse)
{
 if (!g_currentAptOnlineCustomMatch) return;
 int row, column;
 int x = mouse & 0xffff;
 int y = mouse >> 16;
 GadgetListBoxGetEntryBasedOnXY(window, x, y, row, column);
 if (row == -1 || column == -1) {
  TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
  return;
 }
 StagingRoomMap *rooms = TheGameSpyInfo->getStagingRoomList();
 int key = (int)GadgetListBoxGetItemData(window, row, 3);
 StagingRoomMap::iterator it = rooms->find(key);
 if (it == rooms->end()) {
  TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
  return;
 }
 GameInfo *room = (GameInfo *)it->second;int zero=0;
 switch (column) {
 case 0:
  if ((column?(int)GadgetListBoxGetItemData(window, row, 0):(int)GadgetListBoxGetItemData(window, row, 0))!=zero)
   TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:UserMapIcon"), -1, 0, 1.0f);
  break;
 case 1:
  if ((column?(int)GadgetListBoxGetItemData(window, row, 1):(int)GadgetListBoxGetItemData(window, row, 1))!=zero)
   TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:AdvSetting"), -1, 0, 1.0f);
  break;
 case 2:
  if ((column?(int)GadgetListBoxGetItemData(window, row, 2):(int)GadgetListBoxGetItemData(window, row, 2))!=zero)
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
    PlayerInfo *info = TheGameSpyInfo->rva00382CCE(name.str());
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

// Native 0059F496..0059F94E populates a seven-column game-list row.
// WB14F6FF0 and reference games-list code guide purpose; target reads prove
// all offsets, virtual slots, column widths, flags and labels used below.
class GameWindow;class Image;class ThingTemplate;
int GadgetListBoxGetNumColumns(GameWindow*);
void GadgetListBoxSetColumnWidths(GameWindow*,int,int*);
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool);
int GadgetListBoxAddEntryImage(GameWindow*,const Image*,int,int,int,int,bool,int);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column);
#include "../../../../../Include/Common/MpGameRules.h"
int Rva00559EDCCompare(int*,int*);
int Rva005DB335Get(int);
#include "../../../../../Include/Common/VersionClass.h"
extern Version*TheVersion;
class GlobalData;extern GlobalData*TheWritableGlobalData;
struct ListVersionData{char beforeVersion[0xb04];int version;char beforeBuild[0xb38-0xb08];int build;};
class GameSpyStagingRoom{public:
 virtual void v00();virtual void v04();virtual void v08();virtual void v0c();virtual void v10();virtual void v14();virtual void v18();virtual void v1c();
 virtual int players();virtual int maximumPlayers();
 virtual void v28();virtual void v2c();virtual void v30();virtual void v34();virtual void v38();virtual void v3c();virtual void v40();virtual void v44();virtual void v48();virtual void v4c();virtual void v50();
 virtual int ping();virtual UnicodeString title();
 void cleanUpSlotPointers();
 char beforeType[0x5c-4];int type;int rules[10];char beforeVersionBlock[0x90-0x88];int versionBlock[12];int version,build;char beforeId[0xfe0-0xc8];int id;char beforeLocked[0xfec-0xfe4];bool locked;
};
#include "../../../../../Include/GameClient/MapMetaData.h"
#include "../../../../../Include/GameClient/AptMapPreview.h"
#include "../../../../../Include/GameClient/AptMpGameSetup.h"
#include "../../../../../Include/GameClient/Image.h"
extern ImageCollection*TheMappedImageCollection;
static __forceinline bool hasWide(const UnicodeString&name){const unsigned short*p=name.str();int n=name.getLength();for(int i=0;i<n;++i)if(p[i]>=256)return true;return false;}
int AptOnlineCustomMatch::rva0059F496(GameSpyStagingRoom*game)
{
 int widths[7]={4,5,5,36,33,10,7};
 if(GadgetListBoxGetNumColumns(list)<7)GadgetListBoxSetColumnWidths(list,7,widths);
 game->cleanUpSlotPointers();
 bool mismatch=game->version!=((ListVersionData*)TheWritableGlobalData)->version||game->build!=((ListVersionData*)TheWritableGlobalData)->build;
 int color=TheVersion->rva00237E63(game->versionBlock,mismatch);
 UnicodeString name=game->title();
 if(TheGameSpyInfo->getDisallowAsianText()){if(hasWide(name))return -1;}
 else if(TheGameSpyInfo->getDisallowNonAsianText()){if(!hasWide(name))return -1;}
 int row=GadgetListBoxAddEntryText(list,name,color,-1,3,true);
 const Image*lock=0;const Image*userMap=0;
 switch(mode){
 case 0:{
  MapMetaData*meta=((AptMapPreview*)((char*)this+0xd0))->rva0057D922(((GameInfo*)game)->getMap());
  UnicodeString display=meta->bfme_getBaseDisplayName();GadgetListBoxAddEntryText(list,display,color,row,4,true);
  if(!meta->m_isOfficial)userMap=TheMappedImageCollection->findImageByName("AptUserMapNotConquered");
  break;
 }
 case 1:
  {if(((Rva003FF1C2*)game)->rva003FF1C2())lock=TheMappedImageCollection->findImageByName("AptLobbyResumeSavedGame");}
  break;
 }
 if(!lock&&game->locked)lock=TheMappedImageCollection->findImageByName("AptLock");
 int defaults[10];const int currentMode=mode;MpGameRules::GetDefaults(currentMode,defaults);
 const Image*settings=Rva00559EDCCompare(defaults,game->rules)?TheMappedImageCollection->findImageByName("AptLobbyNonDefaultSettings"):0;
 GadgetListBoxAddEntryImage(list,lock,row,2,20,20,true,-1);
 GadgetListBoxAddEntryImage(list,settings,row,1,20,20,true,-1);
 GadgetListBoxAddEntryImage(list,userMap,row,0,20,20,true,-1);
 GadgetListBoxSetItemData(list,(void *)(lock!=0),row,2);GadgetListBoxSetItemData(list,(void *)(settings!=0),row,1);GadgetListBoxSetItemData(list,(void *)(userMap!=0),row,0);
 UnicodeString text;text.format((const unsigned short*)L"%d/%d",game->players(),game->maximumPlayers());
 GadgetListBoxAddEntryText(list,text,color,row,5,true);
 text.format((const unsigned short*)L"%d",game->ping());GadgetListBoxAddEntryText(list,text,color,row,6,true);
 const Image*pingImage=((AptMpGameSetup*)((char*)this+0x70))->rva0043E512(Rva005DB335Get(game->ping()));
 GadgetListBoxAddEntryImage(list,pingImage,row,6,20,20,true,-1);const int gameId=game->id;GadgetListBoxSetItemData(list,(void *)gameId,row,3);
 return row;
}

// Native 005A061B..005A0808 (493B); WorldBuilder callgraph lead names this list-rebuild method.
// Receiver reads 320/450/48C/4C0, room type5C and IDFE0, plus virtual20/24
// are target facts. The owner movie274 and Apt path slot28 feed the common
// enable/disable call. Both capacity outcomes inspect the same join byte;
// spelling the explicit full-game branch lets cl share its address before JE.
void GadgetListBoxGetSelected(GameWindow *, int *);
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetSelected(GameWindow *, int);
void GadgetListBoxSetTopVisibleEntry(GameWindow *, int);
class ModuleData;
class Rva00601941 { public: void rva00601941(); };
class Rva00580B40 { public: void rva00580B40(const ModuleData *); };
class LANGameInfo;
class Rva0058113D { public: LANGameInfo *rva0058113D(unsigned int); };
class Rva0043DB66ByteOneSetter { public: void enable(); };
#include "../../../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int Rva00524EF4AptCall(Rva00222A8BTarget *, void *, const char *, const char *);
void AptOnlineCustomMatch::PopulateGamesListBox()
{
    if (!list || savedGame)
        return;
    int selected = -1;
    int newSelected = -1;
    int gameID = 0;
    GadgetListBoxGetSelected(list, &selected);
    if (selected != -1)
        gameID = (int)GadgetListBoxGetItemData(list, selected, 3);
    int top = GadgetListBoxGetTopVisibleEntry(list);
    GadgetListBoxReset(list);
    ((Rva00601941 *)gameList)->rva00601941();
    StagingRoomMap *rooms = TheGameSpyInfo->getStagingRoomList();
    for (StagingRoomMap::iterator it = rooms->begin(); it._M_node != rooms->end()._M_node; ++it) {
        GameSpyStagingRoom *room = it->second;
        if (!room || mode != room->type)
            continue;
        ((Rva00580B40 *)gameList)->rva00580B40((const ModuleData *)room);
    }
    unsigned int index = 0;
    GameSpyStagingRoom *room;
    while ((room = (GameSpyStagingRoom *)((Rva0058113D *)gameList)->rva0058113D(index)) != 0) {
        int row = rva0059F496(room);
        if (room->id == gameID) {
            newSelected = row;
            ((AptMpGameSetup *)((char *)this + 0x70))->rva0043FA68((GameInfo *)room);
        }
        ++index;
    }
    GadgetListBoxSetSelected(list, newSelected);
    GadgetListBoxSetTopVisibleEntry(list, top);
    if (newSelected < 0) {
        if (gameID != 0) TheWindowManager->winSetLoneWindow(0);
        ((AptMpGameSetup *)((char *)this + 0x70))->rva0043FA68(0);
    } else {
        StagingRoomMap *selectedRooms=TheGameSpyInfo->getStagingRoomList();
        int id=(int)GadgetListBoxGetItemData(list,newSelected,3);
        StagingRoomMap::iterator found=selectedRooms->find(id);
        if(found._M_node!=selectedRooms->end()._M_node) {
            GameSpyStagingRoom *game=found->second;
            int maximum=game->maximumPlayers();
            if(game->players()!=maximum) {
                if(joinEnabled)goto finish;
                joinEnabled=true;
                {
                void *movie=owner58->movie;
                Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,movie,slotAptPath(),"EnableButtonJoinGame");
                }
                goto finish;
            } else {
                if(joinEnabled) {
                    joinEnabled=false;
                    void *movie=owner58->movie;
                    Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,movie,slotAptPath(),"DisableButtonJoinGame");
                }
                goto finish;
            }
        }
    }
    if(!joinEnabled)goto finish;
    joinEnabled=false;
    {
    void *movie=owner58->movie;
    Rva00524EF4AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,movie,slotAptPath(),"DisableButtonJoinGame");
    }
finish:
    ((Rva0043DB66ByteOneSetter *)((char *)this + 0x70))->enable();
}
