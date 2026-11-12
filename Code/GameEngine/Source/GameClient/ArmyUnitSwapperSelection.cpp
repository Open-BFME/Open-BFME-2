// cl: /O1 /Oi /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Retail 005F56B0..005F5819: an army-member selection check, its message
// emitter and two callers. Neighbour 005F5614's constructor and C7953C
// identify the subsystem; WorldBuilder independently names the neighbouring
// owner ArmyUnitSwapperDialog::Impl. These particular function names remain
// unknown, so they retain address names.
// Target facts: selection tree +10 (head/count), army ID +20, summary +78,
// summary-entry target ID +B8, LivingWorldLogic flag +F4; message numbers
// 6B0/6A9 and arguments are read directly from the two message paths.
// The address-derived provider views below preserve existing ledger ABIs.
// The private helpers and both callers must stay in this TU. Caching end
// makes the first selection argument dead before iteration; MSVC then uses
// native EAX+stack for 5F56B0 and EAX+EDI for 5F5749 without assembly.
// The 8-byte enable forwarder calls the existing bool provider 5E0E99;
// its existing 5CC30B consumer is rebuilt with the same bool declaration.
#include <set>
#include <string.h>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
typedef _STL::set<int> SelectedMemberSet;
struct Rva005F56B0Selection {char prefix[0x10]; SelectedMemberSet members;};
#include "../../Include/Common/ArmySummaryEntry.h"
#include "../../Include/Common/Rva0040CB3AIndexedField.h"
#include "../../Include/GameLogic/LivingWorldArmy.h"
static inline Rva0040CB3AIndexedField *armySummaryIndex(LivingWorldArmy *army)
{
    return reinterpret_cast<Rva0040CB3AIndexedField *>(army->field78);
}

struct Arg54;
#include "../../Include/Common/Rva002B280C.h"
struct Rva002B488EResult;
#include "../../Include/GameLogic/Rva002BA8F1Logic.h"
#include "../../Include/GameClient/Rva002B6C9F.h"
class Rva003F287F; class Rva004E0632;
#include "../../Include/GameLogic/LivingWorldLogic.h"
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../Include/GameLogic/Rva00318F42.h"
class Rva005E1008 {public: void rva005E0E99(bool);};
class Rva005E1160Flag {public: __declspec(noinline) void rva005E1160(bool); char prefix[8]; Rva005E1008 *inner;};
void Rva005E1160Flag::rva005E1160(bool enabled){inner->rva005E0E99(enabled);}
class Rva005E0D94 {public: void rva005E0D94();};
#include "../../Include/Common/MessageStream.h"
extern MessageStream *TheMessageStream;
// WorldBuilder StrategicInGameUI::CanCancelMove, WB VA 0x0162A1C0 (callgraph lead, score 2.0).
namespace StrategicInGameUI {
static bool CanCancelMove(Rva005F56B0Selection *selection,LivingWorldArmy *army) {
 if(!TheLivingWorldLogic || TheLivingWorldLogic->fieldF4 || !reinterpret_cast<Rva002B280C*>(TheLivingWorldLogic)->rva002B280C(reinterpret_cast<Arg54*>(army)))return false;
 if(selection->members.size()) {
  Rva0040CB3AIndexedField *summary=armySummaryIndex(army);
  SelectedMemberSet::iterator end=selection->members.end();
  for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
   ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
   int target=entry->m_b8;
   if(!target)return false;
   Rva002B488EResult *targetArmy=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B488E(target);
   if(!targetArmy || !reinterpret_cast<Rva002B6C9F*>(TheLivingWorldLogic)->rva002B8019(reinterpret_cast<int>(army),reinterpret_cast<int>(entry),reinterpret_cast<int>(targetArmy)))return false;
  }
  return true;
 }
 return reinterpret_cast<Rva00318F42*>(army)->rva00318F42();
}
}
// WorldBuilder StrategicInGameUI::CancelMove, WB VA 0x0162A3F0 (callgraph lead, score 2.0).
namespace StrategicInGameUI {
static void CancelMove(Rva005F56B0Selection *selection,LivingWorldArmy *army) {
 if(selection->members.size()) {
  Rva0040CB3AIndexedField *summary=armySummaryIndex(army);
  SelectedMemberSet::iterator end=selection->members.end();
  for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
   ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
   if(entry->m_b8) {
    GameMessage *message=TheMessageStream->appendMessage(GameMessage::MSG_LW_CANCEL_ARMY_MEMBER_MOVE);
    message->appendIntegerArgument(army->field20);
    message->appendIntegerArgument(*it);
   }
  }
 }else if(reinterpret_cast<Rva00318F42*>(army)->rva00318F42()) {
  GameMessage *message=TheMessageStream->appendMessage(GameMessage::MSG_LW_CANCEL_ARMY_MOVE_REQUEST);
  message->appendIntegerArgument(army->field20);
 }
}
}
// Slot 1 of Rva005F5819's primary vftable (retail 0x00C79570, installed by
// its constructor 0x005F589E and destructor 0x005F5819).
class Rva005F5819 {public: virtual void rva005F57D8(); char prefix[0x1C]; LivingWorldArmy *army; Rva005F56B0Selection *selection;};
void Rva005F5819::rva005F57D8(){reinterpret_cast<Rva005E1160Flag*>(reinterpret_cast<char*>(this)+8)->rva005E1160(StrategicInGameUI::CanCancelMove(selection,army));}
class Rva005F57F2 {public: void rva005F57F2(); char prefix[0x18]; LivingWorldArmy *army; Rva005F56B0Selection *selection;};
void Rva005F57F2::rva005F57F2(){reinterpret_cast<Rva005E0D94*>(this)->rva005E0D94();if(StrategicInGameUI::CanCancelMove(selection,army))StrategicInGameUI::CancelMove(selection,army);}

// Native 5F5D41..5F5EA6: selection-wide disband-state check and messages.
// The C4 state bit and first-element state check are target facts;
// CanDisbandArmyMember identity is the existing verified WB-led provider.
bool CanDisbandArmyMember(LivingWorldArmy*,int);
// WorldBuilder StrategicInGameUI::ShouldEnableButton, WB VA 0x0162B7B0 (callgraph lead, score 3.0).
namespace StrategicInGameUI {
static bool ShouldEnableButton(Rva005F56B0Selection *selection,LivingWorldArmy *army) {
 if(!TheLivingWorldLogic || TheLivingWorldLogic->fieldF4 || !selection->members.size())return false;
 Rva0040CB3AIndexedField *summary=armySummaryIndex(army);
 SelectedMemberSet::iterator it=selection->members.begin();
 bool state=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it))->m_c4;
 if(!state && !CanDisbandArmyMember(army,*it))return false;
 SelectedMemberSet::iterator end=selection->members.end();
 for(++it;it!=end;++it) {
  ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
  if(state) {if(!entry->m_c4)return false;}
  else {if(entry->m_c4 || !CanDisbandArmyMember(army,*it))return false;}
 }
 return true;
}
}
// WorldBuilder StrategicInGameUI::DisbandArmyMembers, WB VA 0x0162BA80 (callgraph lead, score 2.0).
namespace StrategicInGameUI {
static void DisbandArmyMembers(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 Rva0040CB3AIndexedField *summary=armySummaryIndex(army);
 SelectedMemberSet::iterator end=selection->members.end();
 for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
  ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
  GameMessage::Type type;
  if(entry->m_c4)type=GameMessage::MSG_LW_CANCEL_ARMY_MEMBER_DISBAND;
  else if(CanDisbandArmyMember(army,*it))type=GameMessage::MSG_LW_DISBAND_ARMY_MEMBER;
  else continue;
  GameMessage *message=TheMessageStream->appendMessage(type);
  message->appendIntegerArgument(army->field20);
  message->appendIntegerArgument(*it);
 }
}
}
// Slot 1 of Rva005F5EA6's primary vftable (retail 0x00C795F0, installed by
// its constructor 0x005F5F2B and destructor 0x005F5EA6).
class Rva005F5EA6 {public:virtual void rva005F5E69(); char prefix[0x1C];LivingWorldArmy *army;Rva005F56B0Selection *selection;};
void Rva005F5EA6::rva005F5E69(){reinterpret_cast<Rva005E1160Flag*>(reinterpret_cast<char*>(this)+8)->rva005E1160(StrategicInGameUI::ShouldEnableButton(selection,army));}
class Rva005F5E83 {public:void rva005F5E83();char prefix[0x18];LivingWorldArmy *army;Rva005F56B0Selection *selection;};
void Rva005F5E83::rva005F5E83(){if(StrategicInGameUI::ShouldEnableButton(selection,army))StrategicInGameUI::DisbandArmyMembers(army,selection);}

// Native 5F5968..5F5BF2: upgrade/cancel selection checks and dispatchers.
// WB (StrategicInGameUIUpgradeUnitButton.cpp) names the private workers
// StrategicInGameUI::CanUpgradeAny, CanCancelAnyUpgrades and SendUpgradeMessages;
// BC, count budget, and message6BF are target facts. Cached end iterators
// and same-TU callers permit the native EBX/EDI/EAX private entries.
class Rva00318C32Ret;
#include "../../Include/GameLogic/Rva00318C79Owner.h"
#include "../../Include/Common/Rva002B2B66.h"
namespace StrategicInGameUI {
static bool CanUpgradeAny(LivingWorldArmy *army,Rva005F56B0Selection *selection);
static bool CanCancelAnyUpgrades(LivingWorldArmy *army,Rva005F56B0Selection *selection);
static void SendUpgradeMessages(LivingWorldArmy *army,Rva005F56B0Selection *selection);
}
bool StrategicInGameUI::CanUpgradeAny(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 Rva003F287F *region=reinterpret_cast<Rva003F287F*>(reinterpret_cast<Rva00318C79Owner*>(army)->rva00318C32());
 int upgradeableCount,countB;
 TheLivingWorldLogic->GetNumUpgradeableTroopsInRegionForPlayer(region,reinterpret_cast<Rva002B2B66*>(TheLivingWorldLogic)->rva002B2B66(),&upgradeableCount,&countB);
 if(upgradeableCount<=0)return false;
 Rva0040CB3AIndexedField *summary=armySummaryIndex(army);
 SelectedMemberSet::iterator end=selection->members.end();
 for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
  ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
  if(!entry->m_bc && TheLivingWorldLogic->GetArmoryToUpgradeTroop(entry,army,region))return true;
 }
 return false;
}
bool StrategicInGameUI::CanCancelAnyUpgrades(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 Rva0040CB3AIndexedField *summary=armySummaryIndex(army);
 _STL::_Rb_tree_node_base *header=*reinterpret_cast<_STL::_Rb_tree_node_base**>(&selection->members);
 for(_STL::_Rb_tree_node_base *node=header->_M_left;node!=header;node=_STL::_Rb_global<bool>::_M_increment(node)) {
  if(reinterpret_cast<ArmySummaryEntry*>(summary->get(*reinterpret_cast<int*>(reinterpret_cast<char*>(node)+16)))->hasUpgrade())return true;
 }
 return false;
}
// Native 5F5A32..5F5A5A (40B), between CanCancelAnyUpgrades and
// SendUpgradeMessages: the upgrade button's enable test that
// Rva005F5BF2::enabled inlines, as an out-of-line file-static (army in EAX,
// copied to EBX for CanUpgradeAny's private entry; int 0/1 result). No call
// to it survives in the image; the anchor below only forces cl to emit it in
// that convention. Identity unproven; address-derived names.
static __declspec(noinline) int Rva005F5A32(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 return (StrategicInGameUI::CanCancelAnyUpgrades(army,selection)||StrategicInGameUI::CanUpgradeAny(army,selection))?1:0;
}
// Native 5E39E6..5E39F3 (13B): the army summary lookup these workers inline
// (army+0x78 summary, rowed Rva0040CB3AIndexedField::get 0x0040CBB8) as an
// out-of-line file-static with the army in EAX. No call to it survives in the
// image; the anchor below only forces cl to emit it in that convention.
// Identity unproven; address-derived names.
static __declspec(noinline) int Rva005E39E6(LivingWorldArmy *army,int entryID) {
 return armySummaryIndex(army)->get(entryID);
}
// ?Rva005E39E6Anchor absent-from-retail
int Rva005E39E6Anchor(LivingWorldArmy *army,int entryID) {
 return Rva005E39E6(army,entryID);
}
// ?Rva005F5A32Anchor absent-from-retail
int Rva005F5A32Anchor(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 return Rva005F5A32(army,selection);
}
void StrategicInGameUI::SendUpgradeMessages(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 Rva003F287F *region=reinterpret_cast<Rva003F287F*>(reinterpret_cast<Rva00318C79Owner*>(army)->rva00318C32());
 int upgradeableCount,countB;
 TheLivingWorldLogic->GetNumUpgradeableTroopsInRegionForPlayer(region,reinterpret_cast<Rva002B2B66*>(TheLivingWorldLogic)->rva002B2B66(),&upgradeableCount,&countB);
 if(upgradeableCount>0) {
  Rva0040CB3AIndexedField *summary=armySummaryIndex(army);
  SelectedMemberSet::iterator end=selection->members.end();
  for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
   ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
   if(!entry->m_bc && TheLivingWorldLogic->GetArmoryToUpgradeTroop(entry,army,region)) {
    GameMessage *message=TheMessageStream->appendMessage(static_cast<GameMessage::Type>(0x6BF));
    message->appendIntegerArgument(army->field20);
    message->appendIntegerArgument(*it);
    if(--upgradeableCount<=0)break;
   }
  }
 }
}
// Native5F5B77..5F5BAE materializes a complete 32-bit 0/1 word before
// passing its low boolean byte to the existing8B setter. The ordinary bool
// expression emits50B (AL only); implicit int-to-bool adds a TEST/SETNE.
// Copying the known-valid 0/1 byte representation preserves that word shape
// without inactive-union reads. MSVC/x86 bool is one byte (also proved by
// WB15DF4C0's byte argument load and target setter cached byte41).
// Slot 1 of Rva005F5BF2's primary vftable (retail 0x00C795B4, installed by
// its constructor 0x005F5C77 and destructor 0x005F5BF2).
class Rva005F5BF2 {
public:virtual void rva005F5B77();
 char prefix[0x1C];LivingWorldArmy *army;Rva005F56B0Selection *selection;
 __forceinline int enabled(){LivingWorldArmy*livingWorldArmy=army;Rva005F56B0Selection*memberSelection=selection;return (StrategicInGameUI::CanCancelAnyUpgrades(livingWorldArmy,memberSelection)||StrategicInGameUI::CanUpgradeAny(livingWorldArmy,memberSelection))?1:0;}
};
void Rva005F5BF2::rva005F5B77(){
 int word=enabled();bool flag;memcpy(&flag,&word,sizeof flag);
 reinterpret_cast<Rva005E1160Flag*>(reinterpret_cast<char*>(this)+8)->rva005E1160(flag);
}

struct Rva005F5B0FA;struct Rva005F5B0FB;
namespace StrategicInGameUI { void SendCancelUpgradeMessages(Rva005F5B0FA*,Rva005F5B0FB*); }
class Rva005F5BAE {public:void rva005F5BAE();char prefix[0x18];LivingWorldArmy *army;Rva005F56B0Selection *selection;};
void Rva005F5BAE::rva005F5BAE(){if(StrategicInGameUI::CanUpgradeAny(army,selection))StrategicInGameUI::SendUpgradeMessages(army,selection);else if(StrategicInGameUI::CanCancelAnyUpgrades(army,selection))StrategicInGameUI::SendCancelUpgradeMessages(reinterpret_cast<Rva005F5B0FA*>(army),reinterpret_cast<Rva005F5B0FB*>(selection));}
