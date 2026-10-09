// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc
// ChatWindowsInGame player-list row insertion, retail5AFDC5..5AFE3F.
// WB1518C40 is unnamed; named PopulatePlayerList WB1514620 calls this
// helper with (playerID,slotName30,teamLabel,color) on the same list object.
// The original helper name remains unknown. Retail establishes player-list
// window10, name column2, team column3, overwrite flags and row userdata.
// GadgetListBoxAddEntryText owns each by-value UnicodeString temporary;
// no EH state belongs to this caller. Use the shared Unicode ABI and the
// existing StringBase<unsigned short>::isEmpty provider at35740.
// All122 bytes, both temporary stack homes and three call targets verified.
#include "unicode_string.h"
class GameWindow;
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int,bool);
void Rva00325388Send(GameWindow *,int,int,int);
template<> bool StringBase<unsigned short>::isEmpty() const;
class ChatWindowsInGame {
public:
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

