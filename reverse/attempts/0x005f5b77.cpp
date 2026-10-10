// ?rva005F5B77@Rva005F5B77@@QAEXXZ
// partial score=0.87 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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
typedef _STL::set<int> SelectedMemberSet;
struct Rva005F56B0Selection {char prefix[0x10]; SelectedMemberSet members;};
class ArmySummaryEntry {public: char prefix[0xb8]; int target; int fieldBC; char padC0[4]; bool fieldC4; __forceinline bool hasUpgrade()const{return fieldBC!=0;}};
class Rva0040CB3AIndexedField {public: int get(int) const;};
struct LivingWorldArmy {char prefix[0x20]; int id; char pad24[0x78-0x24]; Rva0040CB3AIndexedField *summary;};
struct Arg54;
class Rva002B280C {public: bool rva002B280C(Arg54*);};
struct Rva002B488EResult;
class Rva002BA8F1Logic {public: Rva002B488EResult *rva002B488E(int);};
class Rva002B6C9F {public: bool rva002B8019(int,int,int);};
class Rva003F287F; class Rva004E0632;
class LivingWorldLogic {public: void GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F*,int,int*,int*); const Rva004E0632 *GetArmoryToUpgradeTroop(ArmySummaryEntry*,LivingWorldArmy*,Rva003F287F*); char prefix[0xf4]; int flagF4;};
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva00318F42 {public: bool rva00318F42();};
class Rva005E1008 {public: void rva005E0E99(bool);};
class Rva005E1160Flag {public: __declspec(noinline) void rva005E1160(bool); char prefix[8]; Rva005E1008 *inner;};
void Rva005E1160Flag::rva005E1160(bool enabled){inner->rva005E0E99(enabled);}
class Rva005E0D94 {public: void rva005E0D94();};
class GameMessage {public: enum Type {MSG_0x6B0=0x6b0,MSG_0x6A9=0x6a9,MSG_0x6B1=0x6b1,MSG_0x6B3=0x6b3,MSG_0x6BF=0x6bf}; void appendIntegerArgument(int);};
class MessageStream {public:
#define V(n) virtual void slot##n();
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
#undef V
virtual GameMessage *appendMessage(GameMessage::Type);
};
extern MessageStream *TheMessageStream;
static bool Rva005F56B0(Rva005F56B0Selection *selection,LivingWorldArmy *army) {
 if(!TheLivingWorldLogic || TheLivingWorldLogic->flagF4 || !reinterpret_cast<Rva002B280C*>(TheLivingWorldLogic)->rva002B280C(reinterpret_cast<Arg54*>(army)))return false;
 if(selection->members.size()) {
  Rva0040CB3AIndexedField *summary=army->summary;
  SelectedMemberSet::iterator end=selection->members.end();
  for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
   ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
   int target=entry->target;
   if(!target)return false;
   Rva002B488EResult *targetArmy=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B488E(target);
   if(!targetArmy || !reinterpret_cast<Rva002B6C9F*>(TheLivingWorldLogic)->rva002B8019(reinterpret_cast<int>(army),reinterpret_cast<int>(entry),reinterpret_cast<int>(targetArmy)))return false;
  }
  return true;
 }
 return reinterpret_cast<Rva00318F42*>(army)->rva00318F42();
}
static void Rva005F5749(Rva005F56B0Selection *selection,LivingWorldArmy *army) {
 if(selection->members.size()) {
  Rva0040CB3AIndexedField *summary=army->summary;
  SelectedMemberSet::iterator end=selection->members.end();
  for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
   ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
   if(entry->target) {
    GameMessage *message=TheMessageStream->appendMessage(GameMessage::MSG_0x6B0);
    message->appendIntegerArgument(army->id);
    message->appendIntegerArgument(*it);
   }
  }
 }else if(reinterpret_cast<Rva00318F42*>(army)->rva00318F42()) {
  GameMessage *message=TheMessageStream->appendMessage(GameMessage::MSG_0x6A9);
  message->appendIntegerArgument(army->id);
 }
}
class Rva005F57D8 {public: void rva005F57D8(); char prefix[0x20]; LivingWorldArmy *army; Rva005F56B0Selection *selection;};
void Rva005F57D8::rva005F57D8(){reinterpret_cast<Rva005E1160Flag*>(reinterpret_cast<char*>(this)+8)->rva005E1160(Rva005F56B0(selection,army));}
class Rva005F57F2 {public: void rva005F57F2(); char prefix[0x18]; LivingWorldArmy *army; Rva005F56B0Selection *selection;};
void Rva005F57F2::rva005F57F2(){reinterpret_cast<Rva005E0D94*>(this)->rva005E0D94();if(Rva005F56B0(selection,army))Rva005F5749(selection,army);}

// Native 5F5D41..5F5EA6: selection-wide disband-state check and messages.
// The C4 state bit and first-element state check are target facts;
// CanDisbandArmyMember identity is the existing verified WB-led provider.
bool CanDisbandArmyMember(LivingWorldArmy*,int);
static bool Rva005F5D41(Rva005F56B0Selection *selection,LivingWorldArmy *army) {
 if(!TheLivingWorldLogic || TheLivingWorldLogic->flagF4 || !selection->members.size())return false;
 Rva0040CB3AIndexedField *summary=army->summary;
 SelectedMemberSet::iterator it=selection->members.begin();
 bool state=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it))->fieldC4;
 if(!state && !CanDisbandArmyMember(army,*it))return false;
 SelectedMemberSet::iterator end=selection->members.end();
 for(++it;it!=end;++it) {
  ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
  if(state) {if(!entry->fieldC4)return false;}
  else {if(entry->fieldC4 || !CanDisbandArmyMember(army,*it))return false;}
 }
 return true;
}
static void Rva005F5DEE(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 Rva0040CB3AIndexedField *summary=army->summary;
 SelectedMemberSet::iterator end=selection->members.end();
 for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
  ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
  GameMessage::Type type;
  if(entry->fieldC4)type=GameMessage::MSG_0x6B3;
  else if(CanDisbandArmyMember(army,*it))type=GameMessage::MSG_0x6B1;
  else continue;
  GameMessage *message=TheMessageStream->appendMessage(type);
  message->appendIntegerArgument(army->id);
  message->appendIntegerArgument(*it);
 }
}
class Rva005F5E69 {public:void rva005F5E69(); char prefix[0x20];LivingWorldArmy *army;Rva005F56B0Selection *selection;};
void Rva005F5E69::rva005F5E69(){reinterpret_cast<Rva005E1160Flag*>(reinterpret_cast<char*>(this)+8)->rva005E1160(Rva005F5D41(selection,army));}
class Rva005F5E83 {public:void rva005F5E83();char prefix[0x18];LivingWorldArmy *army;Rva005F56B0Selection *selection;};
void Rva005F5E83::rva005F5E83(){if(Rva005F5D41(selection,army))Rva005F5DEE(army,selection);}

// Native 5F5968..5F5BF2: upgrade/cancel selection checks and dispatchers.
// WB names the two private workers CanUpgradeAny and SendUpgradeMessages;
// BC, count budget, and message6BF are target facts. Cached end iterators
// and same-TU callers permit the native EBX/EDI/EAX private entries.
class Rva00318C32Ret;
class Rva00318C79Owner {public:Rva00318C32Ret *rva00318C32();};
class Rva002B2B66 {public:int rva002B2B66();};
static bool Rva005F5968(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 Rva003F287F *region=reinterpret_cast<Rva003F287F*>(reinterpret_cast<Rva00318C79Owner*>(army)->rva00318C32());
 int countA,countB;
 TheLivingWorldLogic->GetNumUpgradeableTroopsInRegionForPlayer(region,reinterpret_cast<Rva002B2B66*>(TheLivingWorldLogic)->rva002B2B66(),&countA,&countB);
 if(countA<=0)return false;
 Rva0040CB3AIndexedField *summary=army->summary;
 SelectedMemberSet::iterator end=selection->members.end();
 for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
  ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
  if(!entry->fieldBC && TheLivingWorldLogic->GetArmoryToUpgradeTroop(entry,army,region))return true;
 }
 return false;
}
static bool Rva005F59F6(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 Rva0040CB3AIndexedField *summary=army->summary;
 _STL::_Rb_tree_node_base *header=*reinterpret_cast<_STL::_Rb_tree_node_base**>(&selection->members);
 for(_STL::_Rb_tree_node_base *node=header->_M_left;node!=header;node=_STL::_Rb_global<bool>::_M_increment(node)) {
  if(reinterpret_cast<ArmySummaryEntry*>(summary->get(*reinterpret_cast<int*>(reinterpret_cast<char*>(node)+16)))->hasUpgrade())return true;
 }
 return false;
}
static void Rva005F5A5A(LivingWorldArmy *army,Rva005F56B0Selection *selection) {
 Rva003F287F *region=reinterpret_cast<Rva003F287F*>(reinterpret_cast<Rva00318C79Owner*>(army)->rva00318C32());
 int countA,countB;
 TheLivingWorldLogic->GetNumUpgradeableTroopsInRegionForPlayer(region,reinterpret_cast<Rva002B2B66*>(TheLivingWorldLogic)->rva002B2B66(),&countA,&countB);
 if(countA>0) {
  Rva0040CB3AIndexedField *summary=army->summary;
  SelectedMemberSet::iterator end=selection->members.end();
  for(SelectedMemberSet::iterator it=selection->members.begin();it!=end;++it) {
   ArmySummaryEntry *entry=reinterpret_cast<ArmySummaryEntry*>(summary->get(*it));
   if(!entry->fieldBC && TheLivingWorldLogic->GetArmoryToUpgradeTroop(entry,army,region)) {
    GameMessage *message=TheMessageStream->appendMessage(GameMessage::MSG_0x6BF);
    message->appendIntegerArgument(army->id);
    message->appendIntegerArgument(*it);
    if(--countA<=0)break;
   }
  }
 }
}
class Rva005F5B77 {public:void rva005F5B77();char prefix[0x20];LivingWorldArmy *army;Rva005F56B0Selection *selection; __forceinline bool enabled(){LivingWorldArmy *a=army;Rva005F56B0Selection *b=selection;return (Rva005F59F6(a,b)||Rva005F5968(a,b))?'\1':'\0';}};
void Rva005F5B77::rva005F5B77(){reinterpret_cast<Rva005E1160Flag*>(reinterpret_cast<char*>(this)+8)->rva005E1160(enabled());}
struct Rva005F5B0FA;struct Rva005F5B0FB;
void Rva005F5B0FNotify(Rva005F5B0FA*,Rva005F5B0FB*);
class Rva005F5BAE {public:void rva005F5BAE();char prefix[0x18];LivingWorldArmy *army;Rva005F56B0Selection *selection;};
void Rva005F5BAE::rva005F5BAE(){if(Rva005F5968(army,selection))Rva005F5A5A(army,selection);else if(Rva005F59F6(army,selection))Rva005F5B0FNotify(reinterpret_cast<Rva005F5B0FA*>(army),reinterpret_cast<Rva005F5B0FB*>(selection));}
