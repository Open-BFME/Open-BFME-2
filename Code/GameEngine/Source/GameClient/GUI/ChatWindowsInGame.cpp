// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ChatWindowsInGame player-list row insertion, retail5AFDC5..5AFE3F.
// WB1518C40 is unnamed; named PopulatePlayerList WB1514620 calls this
// helper with (playerID,slotName30,teamLabel,color) on the same list object.
// The original helper name remains unknown. Retail establishes player-list
// window10, name column2, team column3, overwrite flags and row userdata.
// GadgetListBoxAddEntryText owns each by-value UnicodeString temporary;
// no EH state belongs to this caller. Use the shared Unicode ABI and the
// existing StringBase<unsigned short>::isEmpty provider at35740.
// All122 bytes, both temporary stack homes and three call targets verified.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
// Existing address-derived scalar allocator view from GameLogicInit.cpp.
// The original allocator identity is unknown; native uses a 12-byte vector
// with 4-byte elements and the folded 4DFCB0 push / 31BD55 erase bodies.
template<class T> class Rva002444BEAllocator : public _STL::allocator<T> {};
typedef _STL::vector<int,Rva002444BEAllocator<int> > SelectionIDs;
// The scalar allocator push pin emits a different body. Call the existing
// owned 4-byte-slot provider through its vector-header/reference ABI view;
// its ModuleData spelling does not establish pointer semantics for IDs.
class ModuleData;
template<> void _STL::vector<const ModuleData *>::push_back(const ModuleData *const &);
class GameWindow;
int GadgetListBoxGetNumEntries(GameWindow *);
void GadgetListBoxGetSelected(GameWindow *,int *);
int Rva003253BEGet(GameWindow *,int,int);
UnicodeString GadgetListBoxGetText(GameWindow *,int,int);
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int,bool);
void Rva00325388Send(GameWindow *,int,int,int);
template<> bool StringBase<unsigned short>::isEmpty() const;
class ChatWindowsInGame {
public:
    bool PopulatePlayerList();
    int rva005AFEF7(SelectionIDs *,_STL::vector<AsciiString> *);
    int rva005AFDC5(int,const UnicodeString &,const UnicodeString &,int);
    char unknown00[0x10];
    GameWindow *playerList10;
};
int ChatWindowsInGame::rva005AFDC5(int user,const UnicodeString &name,const UnicodeString &team,int color)
{
    if(!playerList10) return -1;
    int row=GadgetListBoxAddEntryText(playerList10,name,color,-1,2,true);
    Rva00325388Send(playerList10,user,row,2);
    if(!team.isEmpty()) GadgetListBoxAddEntryText(playerList10,team,color,row,3,true);
    return row;
}

// Retail5AFEF7..5B000C RET8; WB1518D20 is unnamed. PopulatePlayerList
// and AptMessenger establish the per-list receiver and parallel ID/name outputs.
// Clear optional containers, stop at the negative selection sentinel, and
// read userdata/text in column2. The legacy selected-message int-slot API
// writes an array pointer. All277 bytes and three EH cleanup states verified.
int ChatWindowsInGame::rva005AFEF7(SelectionIDs *numbers,_STL::vector<AsciiString> *names)
{
    if(numbers) numbers->clear();
    if(names) names->clear();
    if(!playerList10) return 0;
    int count=0;
    int entries=GadgetListBoxGetNumEntries(playerList10);
    if(entries) {
        int *selected=0;
        GadgetListBoxGetSelected(playerList10,reinterpret_cast<int *>(&selected));
        for(int i=0;i<entries;++i) {
            int row=selected[i];
            if(row<0) break;
            ++count;
            if(numbers) {
                int id=Rva003253BEGet(playerList10,row,2);
                reinterpret_cast<_STL::vector<const ModuleData *> *>(numbers)->push_back(
                    reinterpret_cast<const ModuleData *const &>(id));
            }
            if(names) {
                AsciiString name(GadgetListBoxGetText(playerList10,selected[i],2));
                names->push_back(name);
            }
        }
    }
    return count;
}

int GadgetListBoxGetNumColumns(GameWindow *);
void GadgetListBoxSetColumnWidths(GameWindow *,int,int *);
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetTopVisibleEntry(GameWindow *,int);
void Rva00326F9BSet(GameWindow *,const int **);
class GameSlot { public:
    bool isHuman() const;
    char unknown00[0xc]; int color0C;
    char unknown10[0xc]; int team1C;
    char unknown20[0x10]; UnicodeString name30;
};
class GameInfo { public: GameSlot *getSlot(int); };
extern GameInfo *TheGameInfo;
class GameSpyGameSlot { public: char unknown00[0x1ac]; int profile1AC; };
class GameSpyStagingRoom { public: GameSpyGameSlot *getGameSpySlot(int); };
extern GameSpyStagingRoom *TheGameSpyGame;
class MultiplayerColorDefinition { public: char unknown00[0x10]; int color10; };
class MultiplayerSettings { public: MultiplayerColorDefinition *getColor(int); };
extern MultiplayerSettings *TheMultiplayerSettings;
class GameTextInterface { public:
#define TEXT_SLOT(N) virtual void slot##N();
    TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04)
    TEXT_SLOT(05) TEXT_SLOT(06) TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09)
    TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
    virtual UnicodeString fetch(const char *,bool * = 0);
    virtual UnicodeString fetch(const AsciiString &,bool * = 0);
    virtual void slot16();
    virtual const UnicodeString *slot17(const char *,bool *);
};
extern GameTextInterface *TheGameText;

namespace _STL {
template<> int *find(int *,int *,const int &);
}
// Named WB1514620 / ChatWindowsInGame.cpp72..91 and both localized labels
// identify the native5AFA3C..5AFC21 RET0 bool refresh. Native establishes
// slot color0C/team1C/name30, online profile1AC and window10. Keep selected
// IDs across rebuilding the eight human slots, then restore selected rows
// and top-visible position. Vslots3C/44 and all providers come from target
// evidence; the existing scalar-vector ABI view preserves unknown allocator
// identity. /EHs retains both vector cleanup states and the free wrapper.
// All485 bytes and EH states verified; explicit find result matches the
// native reload of end after the search call.
bool ChatWindowsInGame::PopulatePlayerList()
{
    GameWindow *list=playerList10;
    if(!list) return false;
    if(GadgetListBoxGetNumColumns(list)==1) {
        int widths[4]={1,1,49,49};
        GadgetListBoxSetColumnWidths(list,3,widths);
    }
    SelectionIDs oldIDs;
    rva005AFEF7(&oldIDs,0);
    int top=GadgetListBoxGetTopVisibleEntry(list);
    GadgetListBoxReset(list);
    SelectionIDs newRows;
    for(int i=0;i<8;++i) {
        GameSlot *slot=TheGameInfo->getSlot(i);
        if(!slot || !slot->isHuman()) continue;
        UnicodeString team;
        int number=slot->team1C;
        if(number>=0) team.format(TheGameText->slot17("APT:CurrentTeam",0),number);
        else team=TheGameText->fetch("APT:CurrentTeamNone",0);
        int color=TheMultiplayerSettings->getColor(slot->color0C)->color10;
        int user=i;
        if(TheGameSpyGame) {
            GameSpyGameSlot *online=TheGameSpyGame->getGameSpySlot(i);
            if(online) user=online->profile1AC;
        }
        int row=rva005AFDC5(user,slot->name30,team,color);
        int *found=_STL::find(oldIDs.begin(),oldIDs.end(),user);
        if(found!=oldIDs.end())
            reinterpret_cast<_STL::vector<const ModuleData *> *>(&newRows)->push_back(
                reinterpret_cast<const ModuleData *const &>(row));
    }
    Rva00326F9BSet(list,reinterpret_cast<const int **>(&newRows));
    GadgetListBoxSetTopVisibleEntry(list,top);
    return true;
}
