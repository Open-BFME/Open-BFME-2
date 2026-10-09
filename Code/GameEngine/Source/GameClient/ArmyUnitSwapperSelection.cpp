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
class ArmySummaryEntry {public: char prefix[0xb8]; int target;};
class Rva0040CB3AIndexedField {public: int get(int) const;};
struct LivingWorldArmy {char prefix[0x20]; int id; char pad24[0x78-0x24]; Rva0040CB3AIndexedField *summary;};
struct Arg54;
class Rva002B280C {public: bool rva002B280C(Arg54*);};
struct Rva002B488EResult;
class Rva002BA8F1Logic {public: Rva002B488EResult *rva002B488E(int);};
class Rva002B6C9F {public: bool rva002B8019(int,int,int);};
class LivingWorldLogic {public: char prefix[0xf4]; int flagF4;};
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva00318F42 {public: bool rva00318F42();};
class Rva005E1008 {public: void rva005E0E99(bool);};
class Rva005E1160Flag {public: __declspec(noinline) void rva005E1160(bool); char prefix[8]; Rva005E1008 *inner;};
void Rva005E1160Flag::rva005E1160(bool enabled){inner->rva005E0E99(enabled);}
class Rva005E0D94 {public: void rva005E0D94();};
class GameMessage {public: enum Type {MSG_0x6B0=0x6b0,MSG_0x6A9=0x6a9}; void appendIntegerArgument(int);};
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
