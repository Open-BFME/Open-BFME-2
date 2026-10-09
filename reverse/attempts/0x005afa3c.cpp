// ?PopulatePlayerList@ChatWindowsInGame@@QAE_NXZ
// partial score=0.98 date=2026-10-09
// cl: /O1 /MD /EHs /EHc- /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// Native 005AFDC5..005AFE3F, 122 bytes, thiscall RET16.
// WorldBuilder 01518C40 (ChatWindowsInGame.cpp) and the named caller
// PopulatePlayerList at 01514620 establish this file and the four arguments:
// player ID, name, team text, and color. Retail stores the listbox at +10,
// adds name in column 2, stores the ID there, and adds nonempty team text in
// column 3. The original helper name and other owner fields remain unknown.
// Shared UnicodeString supplies the native copy worker 37050 and isEmpty
// worker 35740; the existing listbox helpers supply every remaining call.
#include "unicode_string.h"
#include "ascii_string.h"
// stlport
#include <vector>
#include <algorithm>
namespace _STL { template<> _Vector_base<int,allocator<int> >::_Vector_base(const allocator<int>&); }

class GameWindow;
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int, bool);
void Rva00325388Send(GameWindow *, int, int, int);
int Rva003253BEGet(GameWindow *, int, int);
int GadgetListBoxGetNumEntries(GameWindow *);
void GadgetListBoxGetSelected(GameWindow *,int *);
UnicodeString GadgetListBoxGetText(GameWindow *,int,int);

class ChatWindowsInGame
{
public:
    bool PopulatePlayerList();
    int rva005AFEF7(_STL::vector<int> *ids,_STL::vector<AsciiString> *names);
    int rva005AFDC5(int id, const UnicodeString &name,
        const UnicodeString &team, int color);
private:
    char unknown[0x10];
    GameWindow *listBox;
};

int ChatWindowsInGame::rva005AFDC5(int id, const UnicodeString &name,
    const UnicodeString &team, int color)
{
    if (!listBox)
        return -1;
    int row = GadgetListBoxAddEntryText(listBox, name, color, -1, 2, true);
    Rva00325388Send(listBox, id, row, 2);
    if (!team.isEmpty())
        GadgetListBoxAddEntryText(listBox, team, color, row, 3, true);
    return row;
}

int ChatWindowsInGame::rva005AFEF7(_STL::vector<int> *ids,_STL::vector<AsciiString> *names) {
 if(ids) ids->erase(ids->begin(),ids->end());
 if(names) names->erase(names->begin(),names->end());
 if(!listBox) return 0;
 int count=0;
 int entries=GadgetListBoxGetNumEntries(listBox);
 if(entries) {
  int selected=0;
  GadgetListBoxGetSelected(listBox,&selected);
  for(int i=0;i<entries;++i) {
   int row=((const int *)selected)[i];
   if(row<0) break;
   ++count;
   if(ids) {int id=Rva003253BEGet(listBox,row,2); ids->push_back(id);}
   if(names) {AsciiString name=GadgetListBoxGetText(listBox,row,2); names->push_back(name);}
  }
 }
 return count;
}

class GameSlot {
public:
 bool isHuman() const;
 char unknown00[0x0C]; int color; char unknown10[0x0C]; int team;
 char unknown20[0x10]; UnicodeString name;
};
class GameInfo {public: GameSlot *getSlot(int);};
extern GameInfo *TheGameInfo;
class MultiplayerColorDefinition {public: char unknown[0x10]; int color;};
class MultiplayerSettings {public: MultiplayerColorDefinition *getColor(int);};
extern MultiplayerSettings *TheMultiplayerSettings;
class GameSpyGameSlot {public: char unknown[0x1AC]; int profile;};
class GameSpyStagingRoom {public: GameSpyGameSlot *getGameSpySlot(int);};
extern GameSpyStagingRoom *TheGameSpyGame;
class GameTextInterface {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
 SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
 virtual UnicodeString fetch(const char *,bool);
 SLOT(16)
 virtual const UnicodeString *formatText(const char *,bool);
#undef SLOT
};
extern GameTextInterface *TheGameText;
int GadgetListBoxGetNumColumns(GameWindow *);
void GadgetListBoxSetColumnWidths(GameWindow *,int,int *);
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetTopVisibleEntry(GameWindow *,int);
void Rva00326F9BSet(GameWindow *,const int **);
bool ChatWindowsInGame::PopulatePlayerList() {
 GameWindow *list=listBox;
 if(!list) return false;
 if(GadgetListBoxGetNumColumns(list)==1) {
  int widths[4]={1,1,49,49};
  GadgetListBoxSetColumnWidths(list,3,widths);
 }
 _STL::vector<int> selected;
 rva005AFEF7(&selected,0);
 int top=GadgetListBoxGetTopVisibleEntry(list);
 GadgetListBoxReset(list);
 _STL::vector<int> rows;
 for(int i=0;i<8;++i) {
  GameSlot *slot=TheGameInfo->getSlot(i);
  if(!slot || !slot->isHuman()) continue;
  UnicodeString team;
  if(slot->team>=0) team.format(TheGameText->formatText("APT:CurrentTeam",false),slot->team);
  else team=TheGameText->fetch("APT:CurrentTeamNone",false);
  int color=TheMultiplayerSettings->getColor(slot->color)->color;
  int id=i;
  if(TheGameSpyGame) {
   GameSpyGameSlot *online=TheGameSpyGame->getGameSpySlot(i);
   if(online) id=online->profile;
  }
  int row=rva005AFDC5(id,slot->name,team,color);
  if(_STL::find(selected.begin(),selected.end(),id)!=selected.end()) rows.push_back(row);
 }
 Rva00326F9BSet(list,(const int **)&rows);
 GadgetListBoxSetTopVisibleEntry(list,top);
 return true;
}
