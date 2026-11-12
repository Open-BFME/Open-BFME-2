// cl: /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC
// stlport
// ChatWindowsOnlineRoom::PopulatePlayerList is named by WB15CDA40
// (ChatWindowsOnline.cpp:246..248). Native 5D6AA4..5D6C3C RET0: the room
// refresh reads the GameSpyInfo room map (slot 0x54), collects the current
// list selections through ChatWindowsInGame::rva005AFEF7, rebuilds the rows
// through ChatWindowsOnline::InsertPlayer and restores the top entry.
// The sorted collector's element type is the native 12-byte record
// Rva005D62E8: the real element type (not a layout alias) is what makes the
// compiler emit retail's deallocate calls and frame slots.
#include <vector>
#include <algorithm>
#include "ascii_string.h"
#include "unicode_string.h"

// vector<int> destruction otherwise instantiates a per-TU allocator
// deallocate COMDAT (one byte shape per TU flags); an explicit
// dllimport+forceinline specialization takes those calls inline so this
// TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
}
// Existing address-derived scalar allocator view; native uses a 12-byte
// vector with 4-byte elements and the folded 4DFCB0 push / 31BD55 erase.
template<class T> class Rva002444BEAllocator : public _STL::allocator<T> {};
typedef _STL::vector<int,Rva002444BEAllocator<int> > SelectionIDs;
// The scalar allocator push pin emits a different body; call the existing
// owned 4-byte-slot provider through its vector-header/reference ABI view.
class ModuleData;
template<> void _STL::vector<const ModuleData *>::push_back(const ModuleData *const &);
class GameWindow;
int GadgetListBoxGetNumEntries(GameWindow *);
void GadgetListBoxGetSelected(GameWindow *,int *);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);
UnicodeString GadgetListBoxGetText(GameWindow *,int,int);
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int,bool);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column);
class ChatWindowsInGame {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual bool PopulatePlayerList();
    virtual bool slot10(const UnicodeString &,SelectionIDs &);
    virtual void slot14(const AsciiString &);
    bool rva005AFCB4(bool);
    bool rva005B00C8(int,unsigned int,unsigned int);
    void rva005B000C();
    int rva005AFEF7(SelectionIDs *,_STL::vector<AsciiString> *);
    int rva005AFDC5(int,const UnicodeString &,const UnicodeString &,int);
    char unknown04[4];
    GameWindow *entry08;
    GameWindow *chat0C;
    GameWindow *playerList10;
    int refreshTime14, lastX18, lastY1C, repeats20;
};

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
// ChatWindowsOnline::InsertPlayer, retail 0x005D58E6..0x005D59F0, RET 8.
// The record's original type spelling is unknown, so the accessed prefix
// keeps an address-owned name.
struct Rva005D58E6Player {
    int unknown0; AsciiString name4; int unknown8,unknownC,unknown10;
    int profile14; int unknown18; int rank1C; int unknown20,unknown24; int side28;
};
class ChatWindowsOnline : public ChatWindowsInGame {
public: int InsertPlayer(Rva005D58E6Player *,int);
};

int GadgetListBoxGetNumColumns(GameWindow *);
void GadgetListBoxSetColumnWidths(GameWindow *,int,int *);
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetTopVisibleEntry(GameWindow *,int);
void Rva00326F9BSet(GameWindow *,const int **);
extern int GameSpyColor[];
namespace _STL { template<> int *find(int *,int *,const int &); }

// Native map values contain profile ID0, name4, and wide status14.
#include <map>
// Compare typed tree iterators locally; the incidental base comparison
// COMDAT differs from the selected provider under this unit's flags.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
// Import-inline: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape, 0x00013740) and inlines it into vector growth; this TU's flags
// would emit a private copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline const unsigned int &max<unsigned int>(const unsigned int &__a, const unsigned int &__b) { return __a < __b ? __b : __a; }
}
class PlayerInfo { public:
 int unknown0; AsciiString name4; int unknown8,unknownC,unknown10;
 int profile14; int flags18; int rank1C; int unknown20,unknown24,side28;
};
class Rva005D62E8 { public:
 Rva005D62E8 *rva005D62E8(PlayerInfo *);
 PlayerInfo *player; int state,color;
};
class Rva005D5A7E;
namespace _STL { template<> void sort(Rva005D5A7E *,Rva005D5A7E *); }
struct PrereqUnitRec { unsigned int words[3]; };
struct BfmeE12 { unsigned int words[3]; };
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<BfmeE12>::deallocate(BfmeE12 *p,size_t n) const { if(p) __sgi_alloc::deallocate(p,n*12); }
}
// The header's slot 21 player map is keyed by AsciiString; the call
// instantiates it, so its comparator must be complete here.
#include "../../../Include/Common/AsciiComparator.h"
#include "../../../Include/GameNetwork/GameSpyInfoInterface.h"
class ChatWindowsOnlineRoom : public ChatWindowsOnline { public:
 virtual bool PopulatePlayerList();
};
bool ChatWindowsOnlineRoom::PopulatePlayerList()
{
 GameWindow *list=playerList10;
 if(!list) return false;
 if(!TheGameSpyInfo) return false;
 if(GadgetListBoxGetNumColumns(list)==1) {
  int widths[4]={1,10,88,1};
  GadgetListBoxSetColumnWidths(list,3,widths);
 }
 _STL::map<int,PlayerInfo> *players=reinterpret_cast<_STL::map<int,PlayerInfo> *>(TheGameSpyInfo->getPlayerInfoMap());
 _STL::vector<int> oldIDs;
 rva005AFEF7(reinterpret_cast<SelectionIDs *>(&oldIDs),0);
 int top=GadgetListBoxGetTopVisibleEntry(list);
 GadgetListBoxReset(list);
 _STL::vector<PrereqUnitRec> sorted;
 for(_STL::map<int,PlayerInfo>::iterator i=players->begin(); i!=players->end(); ++i) {
  Rva005D62E8 record;
  sorted.push_back(*reinterpret_cast<const PrereqUnitRec *>(record.rva005D62E8(&i->second)));
 }
 Rva005D62E8 *first=reinterpret_cast<Rva005D62E8 *>(sorted.begin());
 _STL::sort(reinterpret_cast<Rva005D5A7E *>(first),
            reinterpret_cast<Rva005D5A7E *>(sorted.end()));
 _STL::vector<int> newRows;
 Rva005D62E8 *last=reinterpret_cast<Rva005D62E8 *>(sorted.end());
 for(Rva005D62E8 *i=first;i!=last;++i) {
  int row=InsertPlayer(reinterpret_cast<Rva005D58E6Player *>(i->player),GameSpyColor[i->color]);
  int *found=_STL::find(oldIDs.begin(),oldIDs.end(),i->player->profile14);
  if(found!=oldIDs.end())
   reinterpret_cast<_STL::vector<const ModuleData *> *>(&newRows)->push_back(
    reinterpret_cast<const ModuleData *const &>(row));
 }
 Rva00326F9BSet(list,reinterpret_cast<const int **>(&newRows));
 GadgetListBoxSetTopVisibleEntry(list,top);
 return true;
}
