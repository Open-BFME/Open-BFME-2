// cl: /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ChatWindowsOnlineBuddy::PopulatePlayerList is named by WB15CE430,
// ChatWindowsOnline.cpp461..491. Retail establishes playerList10, selected
// IDs and row helpers from the verified ChatWindowsInGame sibling, sorted
// pointer/flag records, and pointee profile0/name4/online10/wide status14.
// BFME1 OnlineChatRva0052E990 is a room-combo population lead, with the same
// GameSpyColor/localized-string conventions but a distinct owner and body.
// It supplies no target layout or identity facts for this Buddy refresh.
// Native widths 0/0/65/35 and three localized-status groups are preserved.
// All824 bytes and cleanup states match; sorted collector60 and implicit
// derived destructor5 are separately verified. The base's inline cleanup
// is identical to its existing21-byte canonical destructor provider.
#include <vector>
#include <algorithm>
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
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);
UnicodeString GadgetListBoxGetText(GameWindow *,int,int);
int GadgetListBoxAddEntryText(GameWindow *,UnicodeString,int,int,int,bool);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column);
template<> bool StringBase<unsigned short>::isEmpty() const;
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

// The base owner is canonical. Retail sorted collector5D6C3C initializes
// its 8-byte pointer/flag vector before calling the existing sort specialization.
struct BfmeE8 { void *p; unsigned char flag; char pad[3]; };
#include "Common/Rva005D639A.h"
inline Rva005D639A::~Rva005D639A() {}
struct Rva005D5853;
namespace _STL { template<> void sort(Rva005D5853 *,Rva005D5853 *); }
class Rva005D63CB : public Rva005D639A {
public:
    Rva005D63CB();
};
Rva005D63CB::Rva005D63CB()
{
    _STL::sort(reinterpret_cast<Rva005D5853 *>(begin()),
               reinterpret_cast<Rva005D5853 *>(end()));
}


int GadgetListBoxGetNumColumns(GameWindow *);
void GadgetListBoxSetColumnWidths(GameWindow *,int,int *);
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetTopVisibleEntry(GameWindow *,int);
void Rva00326F9BSet(GameWindow *,const int **);
class GameTextInterface { public:
#define TEXT_SLOT(N) virtual void slot##N();
    TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04)
    TEXT_SLOT(05) TEXT_SLOT(06) TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09)
    TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
    virtual UnicodeString fetch(const char *,bool * = 0);
    virtual UnicodeString fetch(const AsciiString &,bool * = 0);
};
extern GameTextInterface *TheGameText;
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern int GameSpyColor[];
namespace _STL { template<> int *find(int *,int *,const int &); }
// Native map values contain profile ID0, name4, and wide status14.
// The record pointer is also the address of its profile ID for STL find.
struct BuddyInfo {
    int profile0;
    AsciiString name4;
    int unknown8,unknownC;
    int online10;
    UnicodeString status14;
};
class ChatWindowsOnlineBuddy : public ChatWindowsInGame {
public:
    virtual bool PopulatePlayerList();
};
bool ChatWindowsOnlineBuddy::PopulatePlayerList()
{
    GameWindow *list=playerList10;
    if(!list) return false;
    if(!TheGameSpyInfo) return false;
    if(GadgetListBoxGetNumColumns(list)==1) {
        int widths[4]={0,0,65,35};
        GadgetListBoxSetColumnWidths(list,4,widths);
    }
    SelectionIDs oldIDs;
    rva005AFEF7(&oldIDs,0);
    SelectionIDs newRows;
    UnicodeString scratchLabel;
    int top=GadgetListBoxGetTopVisibleEntry(list);
    GadgetListBoxReset(list);
    Rva005D63CB buddies;
    for(BfmeE8 *it=buddies.begin();it!=buddies.end();++it) {
        if(!it->p) continue;
        int color=6;
        if(!it->flag) color=static_cast<BuddyInfo *>(it->p)->online10?8:9;
        AsciiString key;
        key.format("Buddy:%ls",static_cast<BuddyInfo *>(it->p)->status14.str());
        UnicodeString status;
        if(it->flag) status=TheGameText->fetch("Buddy:BuddyRequest",0);
        else if(static_cast<BuddyInfo *>(it->p)->status14.compareNoCase(
                    reinterpret_cast<const unsigned short *>(L"Offline"))==0 ||
                static_cast<BuddyInfo *>(it->p)->status14.compareNoCase(
                    reinterpret_cast<const unsigned short *>(L"Online"))==0 ||
                static_cast<BuddyInfo *>(it->p)->status14.compareNoCase(
                    reinterpret_cast<const unsigned short *>(L"Matching"))==0)
            status=TheGameText->fetch(key,0);
        else if(static_cast<BuddyInfo *>(it->p)->status14.compareNoCase(
                    reinterpret_cast<const unsigned short *>(L"Staging"))==0 ||
                static_cast<BuddyInfo *>(it->p)->status14.compareNoCase(
                    reinterpret_cast<const unsigned short *>(L"Loading"))==0 ||
                static_cast<BuddyInfo *>(it->p)->status14.compareNoCase(
                    reinterpret_cast<const unsigned short *>(L"Playing"))==0)
            status=TheGameText->fetch(key,0);
        else if(static_cast<BuddyInfo *>(it->p)->status14.compareNoCase(
                    reinterpret_cast<const unsigned short *>(L"Chatting"))==0)
            status=TheGameText->fetch(key,0);
        else status=static_cast<BuddyInfo *>(it->p)->status14;
        int row=rva005AFDC5(static_cast<BuddyInfo *>(it->p)->profile0,
                           UnicodeString(static_cast<BuddyInfo *>(it->p)->name4),
                           status,GameSpyColor[color]);
        int *found=_STL::find(oldIDs.begin(),oldIDs.end(),
                            static_cast<BuddyInfo *>(it->p)->profile0);
        if(found!=oldIDs.end())
            reinterpret_cast<_STL::vector<const ModuleData *> *>(&newRows)->push_back(
                reinterpret_cast<const ModuleData *const &>(row));
    }
    Rva00326F9BSet(list,reinterpret_cast<const int **>(&newRows));
    GadgetListBoxSetTopVisibleEntry(list,top);
    return true;
}
