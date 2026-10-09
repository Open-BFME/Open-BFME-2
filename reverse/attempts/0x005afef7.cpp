// ?rva005AFEF7@ChatWindowsInGame@@QAEHPAV?$vector@HV?$allocator@H@_STL@@@_STL@@PAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@3@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
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
