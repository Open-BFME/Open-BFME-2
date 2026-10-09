// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
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
