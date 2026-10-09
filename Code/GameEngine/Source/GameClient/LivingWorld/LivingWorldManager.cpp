// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Native211C68..211DD2, 362B RET16; WB B63430 independently names
// LivingWorldManager::OnSwapArmyMembers and its original source path.
// The army and member-range types below are partial target ABI views.
// WB assertions identify army summaries and transferringUnits, but do not
// establish the original vector element identity or the complete army layout.
// Native18/54/78/88 reads and calls establish the fields/roles used here.
// Callee identity is resolved from retail REL32 bytes: named-source audio
// selection calls DF1B, partial-transfer calls DF8B and full-transfer calls
// DFFB. WB sibling pairing swaps the latter labels and is not call proof.
#include "ascii_string.h"
class Rva002E2903Player;
class Rva002E071E {public:bool rva002E071E(const Rva002E071E *) const;};
class Rva002BA8F1Logic {
public:
 Rva002E2903Player *find(int,unsigned int *);
 char unknown00[0x98];Rva002E071E *localPlayer98;
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva003FDEAD {public:void rva003FDF1B();void rva003FDF8B();void rva003FDFFB();};
struct ArmyMemberRangeView {
 void **first,**last,**capacity;
 bool empty()const{return first==last;}
 unsigned size()const{return last-first;}
};
struct ArmySummaryEntryPairView {void *control,*entry;};
struct ArmySwapSummaryView {
 char unknown00[0x40];
 ArmySummaryEntryPairView *first40,*last44,*capacity48;
 int entryCount()const{return last44-first40;}
};
struct ArmySwapView {
 char unknown00[0x18];AsciiString name18;
 char unknown1C[0x54-0x1c];int player54;
 char unknown58[0x78-0x58];ArmySwapSummaryView *summary78;
 char unknown7C[0x88-0x7c];Rva003FDEAD *audio88;
 bool hasName()const{return !((const StringBase<char> *)&name18)->isEmpty();}
};
class LivingWorldManager {
public:
 void OnSwapArmyMembers(ArmySwapView *,const ArmyMemberRangeView &,ArmySwapView *,const ArmyMemberRangeView &);
};
void LivingWorldManager::OnSwapArmyMembers(ArmySwapView *armyA,const ArmyMemberRangeView &unitsA,ArmySwapView *armyB,const ArmyMemberRangeView &unitsB)
{
 if(unitsA.empty() && unitsB.empty())return;
 Rva002BA8F1Logic *logic=(Rva002BA8F1Logic *)TheLivingWorldLogic;
 int id=armyA->player54;
 Rva002E2903Player *player=logic->find(id,0);
 Rva002E071E *local=((Rva002BA8F1Logic *)TheLivingWorldLogic)->localPlayer98;
 if(!player || !local || !((Rva002E071E *)player)->rva002E071E(local))return;
 bool nameA=armyA->hasName();
 bool nameB=armyB->hasName();
 Rva003FDEAD *audioA=armyA->audio88;
 Rva003FDEAD *audioB=armyB->audio88;
 if(!audioA || !audioB)return;
 if(!unitsA.empty() && !unitsB.empty()) {
  if(nameA)audioA->rva003FDF1B();
  else audioB->rva003FDF1B();
  return;
 }
 bool fromA=!unitsA.empty();
 ArmySwapView *fromArmy=fromA?armyA:armyB;
 ArmySwapView *toArmy=fromA?armyB:armyA;
 const ArmyMemberRangeView &transferringUnits=fromA?unitsA:unitsB;
 bool fromName=fromA?nameA:nameB;
 bool toName=fromA?nameB:nameA;
 Rva003FDEAD *&fromAudio=fromA?audioA:audioB;
 Rva003FDEAD *&toAudio=fromA?audioB:audioA;
 if(toName) {toAudio->rva003FDF1B();return;}
 if(fromName) {fromAudio->rva003FDF8B();return;}
 ArmySwapSummaryView *toSummary=toArmy->summary78;
 if(!toSummary)return;
 if(toSummary->entryCount()>0) {toAudio->rva003FDF1B();return;}
 ArmySwapSummaryView *fromSummary=fromArmy->summary78;
 if(!fromSummary)return;
 if(fromSummary->entryCount()==transferringUnits.size()) {fromAudio->rva003FDFFB();return;}
 fromAudio->rva003FDF8B();
}
