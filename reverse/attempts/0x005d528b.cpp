// ?PopulatePlayerList@ChatWindowsLan@@QAE_NPAV?$vector@UBfmeStringRecord005D511F@@V?$allocator@UBfmeStringRecord005D511F@@@_STL@@@_STL@@@Z
// partial score=0.9241608391608391 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /EHs /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <vector>
#include <set>
#include <map>
// WorldBuilder ChatWindowsLan::GetLobbyPlayers, ChatWindowsLan.cpp:99/102.
// Native 5D557F..5D5648 proves the complete EH body and list/address layout.
// String record lifetime and vector append use their existing verified owners.
#include "unicode_string.h"

struct BfmeStringRecord005D511F {
    UnicodeString text0;
    unsigned int word0, word1;
    UnicodeString text1;
    unsigned int word2;
    BfmeStringRecord005D511F(const BfmeStringRecord005D511F &);
    BfmeStringRecord005D511F(const UnicodeString &, unsigned int,
        unsigned int, const UnicodeString &, unsigned int);
    ~BfmeStringRecord005D511F();
};
namespace _STL { template<> void vector<BfmeStringRecord005D511F>::push_back(const BfmeStringRecord005D511F &); }
struct BfmeNetAddress {
    bool Rva00248CBF(const BfmeNetAddress *) const;
    unsigned int address;
    unsigned int port;
};
struct LANPlayer {
    UnicodeString name;
    unsigned char m_unknown04[12];
    LANPlayer *next;
    BfmeNetAddress address;
};

// Reduced interfaces: only the native call-site slots are named here.
class LANAPI {
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
    V10(0) V10(1) V10(2) V10(3) V10(4)
    V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58)
    virtual LANPlayer *GetLobbyPlayers(); // +EC
    V(60) V(61) V(62) V(63)
    virtual const BfmeNetAddress *GetLocalAddress(); // +100
#undef V10
#undef V
};
class GameTextInterface {
public:
#define V(n) virtual void slot##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
    V(8) V(9) V(10) V(11) V(12) V(13) V(14)
#undef V
    virtual UnicodeString fetch(const char *, bool *);
};
extern LANAPI *TheLAN;
extern GameTextInterface *TheGameText;
extern int GameSpyColor[];

class ChatWindowsLan {
public:
    void GetLobbyPlayers(_STL::vector<BfmeStringRecord005D511F> *);
    bool PopulatePlayerList(_STL::vector<BfmeStringRecord005D511F>*);
    char unknown00[0x10]; class GameWindow *playerList10;
};

void ChatWindowsLan::GetLobbyPlayers(
    _STL::vector<BfmeStringRecord005D511F> *players)
{
    if (!TheLAN)
        return;
    LANPlayer *player = TheLAN->GetLobbyPlayers();
    if (!player)
        return;
    const BfmeNetAddress *local = TheLAN->GetLocalAddress();
    UnicodeString description = TheGameText->fetch("APT:PlayerInLobby", 0);
    do {
        const BfmeNetAddress &address = player->address;
        int colorIndex = address.Rva00248CBF(local) ? 10 : 8;
        BfmeStringRecord005D511F record(player->name, address.address,
            address.port, description, GameSpyColor[colorIndex]);
        players->push_back(record);
        player = player->next;
    } while (player);
}

class GameWindow;
int GadgetListBoxGetNumEntries(GameWindow *);
void GadgetListBoxGetSelected(GameWindow *,int *);
int Rva003253BEGet(GameWindow *,int,int);
int GadgetListBoxGetNumColumns(GameWindow *);
void GadgetListBoxSetColumnWidths(GameWindow *,int,int *);
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetTopVisibleEntry(GameWindow *,int);
void Rva00326F9BSet(GameWindow *,const int **);
class ModuleData;
template<> void _STL::vector<const ModuleData *>::push_back(const ModuleData *const &);
template<class T> class Rva002444BEAllocator : public _STL::allocator<T> {};
typedef _STL::vector<int,Rva002444BEAllocator<int> > SelectionIDs;
class ChatWindowsInGame {public:int rva005AFDC5(int,const UnicodeString &,const UnicodeString &,int);};
class GameWindowManager {public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
 V10(0) V10(1) V10(2) V10(3) V10(4) V(50) V(51)
 virtual void selectionChanged(int);
#undef V10
#undef V
};
extern GameWindowManager *TheWindowManager;
class Rva00072FE6 {public:~Rva00072FE6();};
class Rva002EE9B7 {public:Rva002EE9B7();void *header;int count;int compare;};
struct NativeSelectionSet:public Rva002EE9B7 {
 __forceinline NativeSelectionSet(){}
 __forceinline ~NativeSelectionSet(){reinterpret_cast<Rva00072FE6*>(this)->~Rva00072FE6();}
 __forceinline _STL::set<int> &set(){return *reinterpret_cast<_STL::set<int>*>(this);}
};
bool ChatWindowsLan::PopulatePlayerList(_STL::vector<BfmeStringRecord005D511F>*players)
{
 GameWindow *list=playerList10;
 if(!list)return false;
 if(players->empty()){GadgetListBoxReset(list);return true;}
 if(GadgetListBoxGetNumColumns(list)==1){int widths[4]={1,1,97,0};GadgetListBoxSetColumnWidths(list,4,widths);}
 int top=GadgetListBoxGetTopVisibleEntry(list);
 int entries=GadgetListBoxGetNumEntries(list);
 union{int user;int row;} counter;
 int *selected;
 GadgetListBoxGetSelected(list,reinterpret_cast<int*>(&selected));
 NativeSelectionSet ids;
 int i=0;
 for(;i<entries;++i){if(selected[i]<0)break;counter.user=Rva003253BEGet(list,selected[i],2);ids.set().insert(counter.user);}
 GadgetListBoxReset(list);
 SelectionIDs rows;
 counter.row=0;
 for(_STL::vector<BfmeStringRecord005D511F>::iterator p=players->begin();p!=players->end();++counter.row,++p){
  int user=p->word0;
  reinterpret_cast<ChatWindowsInGame*>(this)->rva005AFDC5(user,p->text0,UnicodeString::TheEmptyString,p->word2);
  if(ids.set().find(user)!=ids.set().end())reinterpret_cast<_STL::vector<const ModuleData*>*>(&rows)->push_back(reinterpret_cast<const ModuleData*const &>(counter.row));
 }
 Rva00326F9BSet(list,reinterpret_cast<const int**>(&rows));
 if(rows.size()!=i)TheWindowManager->selectionChanged(0);
 GadgetListBoxSetTopVisibleEntry(list,top);
 return true;
}
