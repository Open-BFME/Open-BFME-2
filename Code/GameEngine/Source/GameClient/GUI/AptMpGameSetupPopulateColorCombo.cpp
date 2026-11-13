// ?PopulateColorCombo@AptMpGameSetup@@QAE_NH@Z
// retail 0x0044009D, 1039 bytes; WB AptMpGameSetup::PopulateColorCombo.
// cl: /O1 /G7 /MD /EHs /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// Rebuilds one lobby slot's colour combo from the offered colours, less the
// colours other human non-observer slots hold, and repopulates it only when
// that set differs from the list box's current item data. Semantic reference:
// BFME 1 SkirmishScreenStateRebuildColorCombo.cpp (ba7ddda7e8). Target deltas
// read from retail and the WB twin: offered-colour vector copy and count,
// local/host-AI edit permission, optional random entry, mode dirty flag. The
// WB twin reads mode through an inline getter (its temp local_100), which
// gives retail's load-then-compare and register choice.
//
// rva0043F14D (retail 0x0043F14D, 87 bytes) is STLport 4.5.3's vector<bool>
// operator== body: the same TU's out-of-line instantiation compiles to the
// same bytes. Its body has to be visible here, as in BFME 1's donor, so MSVC
// sees that neither vector escapes and keeps the listed vector's begin in
// registers across the list-box calls. The address name is kept.
//
// AptLobbyRandomColorTint (native DC8D48) is owned by
// Rva0043F483PopulatePlayerCombo.cpp. The static guard E03350 is this
// function's; its unwind clearers are still rowed in
// GlobalFlagClearers_E033xx.cpp. /EHs with plain free keeps retail's unwind
// states (commit 2d39596721).
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> vector<bool,allocator<bool> >::vector(const vector<bool,allocator<bool> > &); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<bool, bool const *>, _Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *>::_Bit_iter(); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
// bfme link decl-only end
#include "../../../Include/GameNetwork/GameInfo.h"
class Rva0043DA65 {public:int rva0043DA65();};
class ColorSetupOwner {public:virtual void v00();virtual bool amIHost();};
#include "../../../Include/GameClient/Bfme2GameWindow.h"
class MpGameSetupComboRef {public:MpGameSetupComboRef(const MpGameSetupComboRef&);~MpGameSetupComboRef();GameWindow*window;};
class Image;
#include "../../../Include/GameClient/Image.h"
#include "../../../Include/GameNetwork/MultiplayerColorDefinition.h"
#include "../../../Include/GameNetwork/MultiplayerSettingsClass.h"
extern MultiplayerSettings*TheMultiplayerSettings;
extern ImageCollection*TheMappedImageCollection;
extern int AptLobbyRandomColorTint;
class Rva003236E8 {public:int rva003236E8();};
#include "../../../Include/Common/Rva00323619.h"
#include "../../../Include/GameClient/Rva003235B8.h"
class Rva003236A0 {public:void rva003236A0(int,int);};
class BfmeThing925D {public:void bfmeGo925D(void*);};
void*GadgetListBoxGetItemData(GameWindow*,int,int);
int GadgetListBoxGetNumEntries(GameWindow*);
int Rva0043DDF8(int);
__declspec(noinline) bool rva0043F14D(const _STL::vector<bool>&first,const _STL::vector<bool>&second){
 return first.size()==second.size()&&_STL::equal(first.begin(),first.end(),second.begin());}
class AptMpGameSetup {public:bool PopulateColorCombo(int);int getMode()const{return mode;}
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
 bool changed=(getMode()==1);
 bool editable=(info->getLocalSlotNum()==index);
 if(owner->amIHost()&&cur->isAI())editable=true;
 if(editable){
  for(int i=0;i<8;++i){
   GameSlot*slot=info->getSlot(i);
   if(slot&&slot->m_color>=0&&slot->m_color<numColors&&i!=index&&slot->isHuman()&&!slot->isObserver()){
    available[slot->m_color]=false;--count;
   }
  }
 }
 if(optional)++count;
 MpGameSetupComboRef combo(combos[index]);
 GameWindow*list=*(GameWindow**)((char*)combo.window->winGetUserData()+8);
 if(list){
  int entries=GadgetListBoxGetNumEntries(list);
  if(entries==count){
   _STL::vector<bool>listed(available.size(),false);
   for(int row=0;row<entries;++row){
    int c=(int)GadgetListBoxGetItemData(list,row,0);
    if(c<0)continue;
    if(c>=listed.size())break;
    listed[c]=true;
   }
   if(rva0043F14D(listed,available))return false;
  }
 }
 bool wasObserver=(((Rva003236E8*)&combo)->rva003236E8()==1);
 ((Rva00323619*)&combo)->rva00323642();
 TheMultiplayerSettings->getColor(-1);
 if(optional||cur->m_state==1){
  static const Image*randomImage=TheMappedImageCollection->findImageByName(AsciiString("AptRandomColor"));
  int entry=((Rva003235B8*)&combo)->rva003235B8(randomImage,20,20,AptLobbyRandomColorTint);
  ((Rva003236A0*)&combo)->rva003236A0(entry,-1);
  if(cur->isObserver()||cur->m_state==1)((BfmeThing925D*)&combo)->bfmeGo925D(0);
 }
 for(int c=0;c<numColors;++c){
  MultiplayerColorDefinition*def=TheMultiplayerSettings->getColor(c);
  if(!def||!available[c])continue;
  static const Image*colorImage=TheMappedImageCollection->findImageByName(AsciiString("AptWhiteBox"));
  int entry=((Rva003235B8*)&combo)->rva003235B8(colorImage,20,20,def->m_color);
  ((Rva003236A0*)&combo)->rva003236A0(entry,c);
 }
 ((Rva00323619*)&combo)->rva00323619(Rva0043DDF8(index)*22+4);
 if(wasObserver)((BfmeThing925D*)&combo)->bfmeGo925D(0);
 if(changed)dirty=true;
 return true;
}
