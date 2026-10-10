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
	AsciiString getMap() const;
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
 GSI_SLOT(54) GSI_SLOT(55) GSI_SLOT(56) GSI_SLOT(57) GSI_SLOT(58)
 virtual bool flagEC(); virtual bool flagF0();
};

#undef GSI_SLOT

extern GameSpyInfoInterface *TheGameSpyInfo;		// 0x00E02320

class AptOnlineCustomMatch
{
public:
	static void GamesListTooltipFunc(GameWindow *, WinInstanceData *, unsigned int);
	int rva0059F496(GameSpyStagingRoom *);
	void MpOwnerGetLocalPlayerName(UnicodeString &name);
	GameSpyStagingRoom *GetGameToJoin();

private:
	unsigned char m_pad000[0xec];
 int mode;
 unsigned char m_pad0f0[0x48c-0xf0];
 GameWindow *list;
 unsigned char m_pad490[0x4b8-0x490];
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

// Native 005A08C8..005A0B4C; WB names the tooltip callback.
// The icon getter returns an integer, compared with the shared zero value.
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
extern int g_currentAptOnlineCustomMatch;
class Rva003FF1C2 { public: bool rva003FF1C2() const; };
int GadgetListBoxGetEntryBasedOnXY(GameWindow *, int, int, int &, int &);
int Rva003253BEGet(GameWindow *, int, int);
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
 int key = Rva003253BEGet(window, row, 3);
 StagingRoomMap::iterator it = rooms->find(key);
 if (it == rooms->end()) {
  TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
  return;
 }
 GameInfo *room = (GameInfo *)it->second;int zero=0;
 switch (column) {
 case 0:
  if ((column?Rva003253BEGet(window, row, 0):Rva003253BEGet(window, row, 0))!=zero)
   TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:UserMapIcon"), -1, 0, 1.0f);
  break;
 case 1:
  if ((column?Rva003253BEGet(window, row, 1):Rva003253BEGet(window, row, 1))!=zero)
   TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:AdvSetting"), -1, 0, 1.0f);
  break;
 case 2:
  if ((column?Rva003253BEGet(window, row, 2):Rva003253BEGet(window, row, 2))!=zero)
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

// Native 0059F496..0059F94E populates a seven-column game-list row.
// WB14F6FF0 and reference games-list code guide purpose; target reads prove
// all offsets, virtual slots, column widths, flags and labels used below.
class GameWindow;class Image;class ThingTemplate;
int GadgetListBoxGetNumColumns(GameWindow*);
void GadgetListBoxSetColumnWidths(GameWindow*,int,int*);
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool);
int GadgetListBoxAddEntryImage(GameWindow*,const Image*,int,int,int,int,bool,int);
void Rva00325388Send(GameWindow*,int,int,int);
void Rva00559FAC(int,void*);
int Rva00559EDCCompare(int*,int*);
int Rva005DB335Get(int);
class Version{public:int rva00237E63(const void*,bool);};extern Version*TheVersion;
class GlobalData;extern GlobalData*TheWritableGlobalData;
struct ListVersionData{char beforeVersion[0xb04];int version;char beforeBuild[0xb38-0xb08];int build;};
class GameSpyStagingRoom{public:
 virtual void v00();virtual void v04();virtual void v08();virtual void v0c();virtual void v10();virtual void v14();virtual void v18();virtual void v1c();
 virtual int players();virtual int maximumPlayers();
 virtual void v28();virtual void v2c();virtual void v30();virtual void v34();virtual void v38();virtual void v3c();virtual void v40();virtual void v44();virtual void v48();virtual void v4c();virtual void v50();
 virtual int ping();virtual UnicodeString title();
 void cleanUpSlotPointers();
 char beforeRules[0x60-4];int rules[10];char beforeVersionBlock[0x90-0x88];int versionBlock[12];int version,build;char beforeId[0xfe0-0xc8];int id;char beforeLocked[0xfec-0xfe4];bool locked;
};
class MapMetaData{public:UnicodeString bfme_getBaseDisplayName();char beforeOfficial[0x26];bool official;};
class AptMapPreview{public:MapMetaData*rva0057D922(const AsciiString&);};
class AptMpGameSetup{public:const Image*rva0043E512(int);};
class ImageCollection{public:const Image*findImageByName(const AsciiString&);};extern ImageCollection*TheMappedImageCollection;
static __forceinline bool hasWide(const UnicodeString&name){const unsigned short*p=name.str();int n=name.getLength();for(int i=0;i<n;++i)if(p[i]>=256)return true;return false;}
int AptOnlineCustomMatch::rva0059F496(GameSpyStagingRoom*game)
{
 int widths[7]={4,5,5,36,33,10,7};
 if(GadgetListBoxGetNumColumns(list)<7)GadgetListBoxSetColumnWidths(list,7,widths);
 game->cleanUpSlotPointers();
 bool mismatch=game->version!=((ListVersionData*)TheWritableGlobalData)->version||game->build!=((ListVersionData*)TheWritableGlobalData)->build;
 int color=TheVersion->rva00237E63(game->versionBlock,mismatch);
 UnicodeString name=game->title();
 if(TheGameSpyInfo->flagEC()){if(hasWide(name))return -1;}
 else if(TheGameSpyInfo->flagF0()){if(!hasWide(name))return -1;}
 int row=GadgetListBoxAddEntryText(list,name,color,-1,3,true);
 const Image*lock=0;const Image*userMap=0;
 switch(mode){
 case 0:{
  MapMetaData*meta=((AptMapPreview*)((char*)this+0xd0))->rva0057D922(((GameInfo*)game)->getMap());
  UnicodeString display=meta->bfme_getBaseDisplayName();GadgetListBoxAddEntryText(list,display,color,row,4,true);
  if(!meta->official)userMap=TheMappedImageCollection->findImageByName("AptUserMapNotConquered");
  break;
 }
 case 1:
  {if(((Rva003FF1C2*)game)->rva003FF1C2())lock=TheMappedImageCollection->findImageByName("AptLobbyResumeSavedGame");}
  break;
 }
 if(!lock&&game->locked)lock=TheMappedImageCollection->findImageByName("AptLock");
 int defaults[10];const int currentMode=mode;Rva00559FAC(currentMode,defaults);
 const Image*settings=Rva00559EDCCompare(defaults,game->rules)?TheMappedImageCollection->findImageByName("AptLobbyNonDefaultSettings"):0;
 GadgetListBoxAddEntryImage(list,lock,row,2,20,20,true,-1);
 GadgetListBoxAddEntryImage(list,settings,row,1,20,20,true,-1);
 GadgetListBoxAddEntryImage(list,userMap,row,0,20,20,true,-1);
 Rva00325388Send(list,lock!=0,row,2);Rva00325388Send(list,settings!=0,row,1);Rva00325388Send(list,userMap!=0,row,0);
 UnicodeString text;text.format((const unsigned short*)L"%d/%d",game->players(),game->maximumPlayers());
 GadgetListBoxAddEntryText(list,text,color,row,5,true);
 text.format((const unsigned short*)L"%d",game->ping());GadgetListBoxAddEntryText(list,text,color,row,6,true);
 const Image*pingImage=((AptMpGameSetup*)((char*)this+0x70))->rva0043E512(Rva005DB335Get(game->ping()));
 GadgetListBoxAddEntryImage(list,pingImage,row,6,20,20,true,-1);const int gameId=game->id;Rva00325388Send(list,gameId,row,3);
 return row;
}
