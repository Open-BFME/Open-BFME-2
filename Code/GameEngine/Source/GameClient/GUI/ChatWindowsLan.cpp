// cl: /O1 /G7 /arch:SSE /EHs /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
#include <set>
#include <map>

// Keep STLport's signed comparison inline without emitting another
// conflicting external copy; stlport_list_int.cpp owns the retail body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &left, const int &right) const
{ return left < right; }
}
// Keep the inlined node comparison local; this unit's incidental
// tree-base operator!= copy conflicts with the selected provider.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
// Keep integer construction inline; stlport_deque_int.cpp owns retail's
// out-of-line _Construct<int, int> body at 0x00620140.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void _Construct<int, int>(int *p, const int &value) { new (p) int(value); }
}
// WorldBuilder ChatWindowsLan::GetLobbyPlayers and PopulatePlayerList (ChatWindowsLan.cpp).
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
class GameInfo;
struct LANGameInfoView {
    char m_pad[0xF5C];
    LANGameInfoView *next;
};
class LANAPI {
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
    V10(0) V10(1) V10(2) V10(3) V10(4)
    V(50) virtual LANGameInfoView *GetGames(); /* +CC */ V(52) V(53) V(54) V(55)
    virtual GameInfo *GetCurrentGame(); // +E0, used by native 5D56D0
    V(57) V(58)
    virtual LANPlayer *GetLobbyPlayers(); // +EC
    V(60) V(61) V(62) V(63)
    virtual const BfmeNetAddress *GetLocalAddress(); // +100
#undef V10
#undef V
};
#include "../../../Include/GameClient/GameText.h"
extern LANAPI *TheLAN;
extern GameTextInterface *TheGameText;
extern int GameSpyColor[];

class ChatWindowsLan {
public:
    void GetLobbyPlayers(_STL::vector<BfmeStringRecord005D511F> *);
    bool PopulatePlayerList(_STL::vector<BfmeStringRecord005D511F>*);
    bool rva005D56D0();
    bool rva005D574C();
    // 0x005D5648 (StringRecordVectorFill005D5648.cpp): a member that never
    // reads ECX; this caller sets ECX=this for it (retail hoists that into the
    // loop test it shares with PopulatePlayerList).
    void rva005D5648(_STL::vector<BfmeStringRecord005D511F> *, GameInfo *);
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
void *GadgetListBoxGetItemData(GameWindow *,int,int);
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
#include "../../../Include/Common/Rva00072FE6.h"
// The selection ids are a set<int>: its constructor is the shared 25-byte
// STLport empty-set body at 0x000D3A71 (??0Rva002EE9B7@@QAE@XZ, provided by
// HordeContainCtor.cpp). Declared only, as CastleBehaviorCtor.cpp does: an
// inline body here emitted a 49-byte EH-framed placement-new copy that link
// order now keeps ahead of the retail one. The tree destructor stays the
// rowed Rva00072FE6 one, and set() views the same storage.
class Rva002EE9B7 {public:Rva002EE9B7();void *header;int count;int compare;};
struct NativeSelectionSet:public Rva002EE9B7 {
 __forceinline NativeSelectionSet(){}
 __forceinline ~NativeSelectionSet(){reinterpret_cast<Rva00072FE6*>(this)->~Rva00072FE6();}
 __forceinline _STL::set<int> &set(){return *reinterpret_cast<_STL::set<int>*>(this);}
};
// Native 5D528B..5D541B (400 B, RET 4). Codegen: the list top-visible entry is a
// volatile local and a compiler barrier follows the list null test; together they take the
// competing value out of the callee-saved registers so the list and player-vector
// webs get retail's EBX/EDI roles (found by the greedy chain search).
bool ChatWindowsLan::PopulatePlayerList(_STL::vector<BfmeStringRecord005D511F>*players)
{
 GameWindow *list=playerList10;
 if(!list)return false;
 _ReadWriteBarrier();
 if(players->empty()){GadgetListBoxReset(list);return true;}
 if(GadgetListBoxGetNumColumns(list)==1){int widths[4]={1,1,97,0};GadgetListBoxSetColumnWidths(list,4,widths);}
 volatile int top = GadgetListBoxGetTopVisibleEntry(list);
 int entries=GadgetListBoxGetNumEntries(list);
 union{int user;int row;} counter;
 int *selected;
 GadgetListBoxGetSelected(list,reinterpret_cast<int*>(&selected));
 NativeSelectionSet ids;
 int i=0;
 for(;i<entries;++i){if(selected[i]<0)break;counter.user=(int)GadgetListBoxGetItemData(list,selected[i],2);ids.set().insert(counter.user);}
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

// Native 5D574C..5D57D3 (135 B). Refreshes the lobby list: the lobby players followed by the
// players of every listed LAN game (rowed 0x005D5648 fill over the game chain through +0xF5C) are
// collected and shown through PopulatePlayerList; false without a LAN API. The native EH frame
// holds the collection vector. The method's real name is unproven (no WorldBuilder match).
bool ChatWindowsLan::rva005D574C()
{
    if (!TheLAN)
        return false;
    _STL::vector<BfmeStringRecord005D511F> players;
    GetLobbyPlayers(&players);
    for (LANGameInfoView *game = TheLAN->GetGames(); game; game = game->next)
        rva005D5648(&players, reinterpret_cast<GameInfo *>(game));
    return PopulatePlayerList(&players);
}

// Native 5D56D0..5D574C is a complete 124-byte EH-framed function.
// The LAN slot at E0 supplies the current GameInfo. The independently
// rowed game/lobby collectors and PopulatePlayerList establish the same
// ChatWindowsLan receiver and string-record vector as rva005D574C above.
// This refresh chooses the current game's players, falling back to the
// lobby while no game is selected. Its original method name is unknown.
bool ChatWindowsLan::rva005D56D0()
{
    if (!TheLAN)
        return false;
    GameInfo *game = TheLAN->GetCurrentGame();
    _STL::vector<BfmeStringRecord005D511F> players;
    if (game)
        rva005D5648(&players, game);
    else
        GetLobbyPlayers(&players);
    return PopulatePlayerList(&players);
}
