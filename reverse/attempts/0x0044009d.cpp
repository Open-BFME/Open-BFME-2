// ?PopulateColorCombo@AptMpGameSetup@@QAE_NH@Z
// partial score=0.87 date=2026-10-08
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
// Full WB/retail body 44009D..4404AC,1039B. BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f
// SkirmishScreenStateRebuildColorCombo.cpp is the semantic reference. Target
// deltas: offered-color vector copy+count, local/host-AI edit permission,
// exclude other human nonobserver colors, optional random entry, and mode dirty.
// Native calls and fields shown here were read independently from both images.
// The random-entry tint is a 4-byte global at native VA DC8D48 with value
// FFFFFFFF and 9 read references; its original name remains unknown.
// AptLobbyRandomColorTint is only a descriptive unresolved external in this
// bank. Before landing, reconcile its ownership and the compiler static guard
// (E03350), already owned by GlobalFlagClearers_E033xx.cpp. Never add a second
// data owner for that flag or whitelist the conflict. Cached images E0334C/48
// are natural static locals, not hand-addressed globals. Native strings agree.
// GameWindow combo copy/dtor and all helpers use existing proven providers;
// no new pin. Throwing STL free30830 gives the exact native EH state resets.
// Current output1041B vs1039B; info/slot EBX/EDI allocation exchanged, frame50
// vs54, mode test/load and editable flag memory/register placement differ.
#include <stdlib.h>
namespace _STL {void __cdecl free(void*);}
#define free _STL::free
#include <vector>
#undef free
#include "ascii_string.h"
class GameSlot {public: bool isHuman() const; bool isObserver() const; bool isAI() const;
 char pad[4];int state;char pad8[4];int color;};
class GameInfo {public:
 virtual void v00();virtual void v01();virtual void v02();virtual void v03();
 virtual void v04();virtual void v05();virtual void v06();virtual void v07();
 virtual void v08();virtual void v09();virtual void v10();virtual void v11();
 virtual void v12();virtual int v13();
 GameSlot*getSlot(int);const GameSlot*getConstSlot(int)const;};
class Rva0043DA65 {public:int rva0043DA65();};
class ColorSetupOwner {public:virtual void v00();virtual bool amIHost();};
class GameWindow {public:void *winGetUserData();};
class MpGameSetupComboRef {public:MpGameSetupComboRef(const MpGameSetupComboRef&);~MpGameSetupComboRef();GameWindow*window;};
class Image;
class ImageCollection {public:const Image*findImageByName(const AsciiString&);};
class MultiplayerColorDefinition {public:char pad[0x10];int color;};
class MultiplayerSettings {public:MultiplayerColorDefinition*getColor(int);};
extern MultiplayerSettings*TheMultiplayerSettings;
extern ImageCollection*TheMappedImageCollection;
extern int AptLobbyRandomColorTint;
class Rva003236E8 {public:int rva003236E8();};
class Rva00323619 {public:void rva00323642();void rva00323619(int);};
class Rva003235B8 {public:int rva003235B8(const Image*,int,int,int);};
class Rva003236A0 {public:void rva003236A0(int,int);};
class BfmeThing925D {public:void bfmeGo925D(void*);};
int Rva003253BEGet(GameWindow*,int,int);
int GadgetListBoxGetNumEntries(GameWindow*);
int Rva0043DDF8(int);
bool rva0043F14D(const _STL::vector<bool>&,const _STL::vector<bool>&);
class AptMpGameSetup {public:bool PopulateColorCombo(int);
 char pad00[0x58];ColorSetupOwner*owner;Rva0043DA65*game;
 char pad60[0x7c-0x60];int mode;char pad80[0x2be-0x80];bool dirty;
 char pad2bf[0x2f4-0x2bf];MpGameSetupComboRef combos[8];
 char pad314[0x3c4-0x314];_STL::vector<bool>offered;int availableCount;bool optional;
};
bool AptMpGameSetup::PopulateColorCombo(int index) {
 GameInfo*info=(GameInfo*)game->rva0043DA65();
 if(!info)return false;
 const GameSlot*cur=info->getConstSlot(index);
 if(!cur)return false;
 _STL::vector<bool>available(offered);
 int count=availableCount;
 int numColors=available.size();
 bool changed=(mode==1);
 bool editable=(info->v13()==index);
 if(owner->amIHost()&&cur->isAI())editable=true;
 if(editable)for(int i=0;i<8;++i){
  GameSlot*slot=info->getSlot(i);
  if(slot&&slot->color>=0&&slot->color<numColors&&i!=index&&slot->isHuman()&&!slot->isObserver()){
   available[slot->color]=false;--count;
  }
 }
 if(optional)++count;
 MpGameSetupComboRef combo(combos[index]);
 GameWindow*list=*(GameWindow**)((char*)combo.window->winGetUserData()+8);
 if(list){int entries=GadgetListBoxGetNumEntries(list);
  if(entries==count){
   _STL::vector<bool>listed(available.size(),false);
   for(int row=0;row<entries;++row){
    int c=Rva003253BEGet(list,row,0);
    if(c<0)continue;
    if(c>=listed.size())break;
    listed[c]=true;
   }
   if(rva0043F14D(listed,available))return false;
  }
 }
 bool wasObserver=(((Rva003236E8*)&combo)->rva003236E8()==1);
 ((Rva00323619*)&combo)->rva00323642();
 MultiplayerColorDefinition*def=TheMultiplayerSettings->getColor(-1);
 if(optional||cur->state==1){
  static const Image*randomImage=TheMappedImageCollection->findImageByName(AsciiString("AptRandomColor"));
  int entry=((Rva003235B8*)&combo)->rva003235B8(randomImage,20,20,AptLobbyRandomColorTint);
  ((Rva003236A0*)&combo)->rva003236A0(entry,-1);
  if(cur->isObserver()||cur->state==1)((BfmeThing925D*)&combo)->bfmeGo925D(0);
 }
 for(int c=0;c<numColors;++c){
  def=TheMultiplayerSettings->getColor(c);
  if(!def||!available[c])continue;
  static const Image*colorImage=TheMappedImageCollection->findImageByName(AsciiString("AptWhiteBox"));
  int entry=((Rva003235B8*)&combo)->rva003235B8(colorImage,20,20,def->color);
  ((Rva003236A0*)&combo)->rva003236A0(entry,c);
 }
 ((Rva00323619*)&combo)->rva00323619(Rva0043DDF8(index)*22+4);
 if(wasObserver)((BfmeThing925D*)&combo)->bfmeGo925D(0);
 if(changed)dirty=true;
 return true;
}
