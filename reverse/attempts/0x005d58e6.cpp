// ?InsertPlayer@ChatWindowsOnline@@QAEHPAURva005D58E6Player@@H@Z
// partial score=1.0 date=2026-10-10
// cl: /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ChatWindowsOnline player-row insertion, retail5D58E6..5D59F0, RET8.
// WB15CD730 and native helpers establish owner/window10, ID14, name4,
// side28/rank1C and both list image columns. The input record's original
// type spelling is unknown; the accessed prefix keeps an address-owned name.
// Shared string headers, TheGameSpyInfo and TheMappedImageCollection retain
// their existing owners. Native performs wide translation at6CB6A0; WB's
// automatic matcher labels that call incorrectly. Canonical empty Unicode
// is the team argument; the existing raw rank-table datum supplies images.
// No sorted Buddy collector or allocator implementation belongs to this owner.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
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
// WB15CD730 names ChatWindowsOnline::InsertPlayer in ChatWindowsOnline.cpp:91.
// Native observes record name4/profile14/rank1C/side28, original record type unknown.
class Image;
class ImageCollection { public: const Image *findImageByName(const AsciiString &); };
extern ImageCollection *TheMappedImageCollection;
int GedgetListBoxGetDefaultHeight(GameWindow *);
int GadgetListBoxAddEntryImage(GameWindow *,const Image *,int,int,int,int,bool,int);
template<int N> struct Rva005D58E6SlotTag;
template<int N> class Rva005D58E6Slots : public Rva005D58E6Slots<N-1> {
public: virtual void unused(Rva005D58E6SlotTag<N> *);
};
template<> class Rva005D58E6Slots<0> {};
class Rva005D58E6SpyView : public Rva005D58E6Slots<90> {
public: virtual bool didPlayerPreorder(int) const;
};
class Rva00559AC1 { public: const Image *rva00559C25(int,int); };
class Rva00559D0CRankWeights;
extern Rva00559D0CRankWeights g_00E06000;
struct Rva005D58E6Player {
 int unknown0; AsciiString name4; int unknown8,unknownC,unknown10;
 int profile14; int unknown18; int rank1C; int unknown20,unknown24; int side28;
};
class ChatWindowsOnline : public ChatWindowsInGame {
public: int InsertPlayer(Rva005D58E6Player *,int);
};
int ChatWindowsOnline::InsertPlayer(Rva005D58E6Player *player,int color)
{
 GameWindow *window=playerList10;
 if(!window) return 0;
 bool preorder=reinterpret_cast<Rva005D58E6SpyView *>(TheGameSpyInfo)->didPlayerPreorder(player->profile14);
 const Image *image=TheMappedImageCollection->findImageByName(AsciiString("Aptfellowship_clup"));
 UnicodeString text;
 text.translate(player->name4);
 if(!preorder) image=0;
 int height=GedgetListBoxGetDefaultHeight(window);
 int profile=player->profile14;
 int row=rva005AFDC5(profile,text,UnicodeString::TheEmptyString,color);
 GadgetListBoxAddEntryImage(window,image,row,0,height,height,true,-1);
 int side=player->side28;
 const Image *rankImage=reinterpret_cast<Rva00559AC1 *>(&g_00E06000)->rva00559C25(side,player->rank1C);
 GadgetListBoxAddEntryImage(window,rankImage,row,1,height,height,true,-1);
 return row;
}
