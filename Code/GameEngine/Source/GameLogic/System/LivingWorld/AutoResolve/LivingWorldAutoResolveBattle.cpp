// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target identity: WB12EB4A0 names LivingWorldAutoResolveBattle's
// buildReinforcementMaps at its source home lines331..337. Native
// 4FA1F3..4FA2D0 is221B: 52-byte player records, side2C, round map0;
// player's round-key nodes contain ArmySummary pointers at14 consumed by
// the existing GetEntries40E88B. Two destination maps at24 have12B stride.
// The unaccessed player fields and mapped-unit element identity stay opaque.
// Vector header/cleanup use existing whole-byte providers211E58/2B703F,
// as in Rva004FA168MapSubscript; the local wrapper is an owning ABI view,
// not a claim that army entries have BfmeE16's sixteen-byte element type.
// Native198B helper4F9658 independently proves this receiver, vector inputs,
// ArmySummary input, unsigned player index, and unused final flag/RET20;
// its original method name stays unknown. No clean BFME1/ZH donor exists.
#include <vector>
#include <map>
struct Rva0040DC56Element {int a[1];};
typedef _STL::vector<Rva0040DC56Element> EntryVector;
namespace _STL {template<> EntryVector::~vector();}
struct BfmeE16 {float x,y,z,w;};
struct Rva004FA1F3Entries {
 unsigned start,finish,capacity;
 Rva004FA1F3Entries() {
  typedef _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > HeaderProvider;
  reinterpret_cast<HeaderProvider*>(this)->HeaderProvider::_Vector_base(_STL::allocator<BfmeE16>());
 }
 ~Rva004FA1F3Entries() {reinterpret_cast<EntryVector*>(this)->EntryVector::~EntryVector();}
};
class ArmySummary {public: void GetEntries(EntryVector &);};

struct TargetRef00217D4C {virtual void *destroy(unsigned); int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva004F87BCElement {
 TargetRef00217D4C *m_ptr;
 Rva004F87BCElement(TargetRef00217D4C *p):m_ptr(p) {if(p) ++p->references;}
 Rva004F87BCElement(const Rva004F87BCElement &p):m_ptr(p.m_ptr) {if(m_ptr) ++m_ptr->references;}
 ~Rva004F87BCElement() {if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);}
};
typedef _STL::vector<Rva004F87BCElement> UnitVector;

class Rva004F7DF9Vector {public: void reserve(unsigned);};
struct Rva005F8FCC {void *rva005F8FCC(unsigned);};
struct Rva004F9635Rec;
class LivingWorldAutoResolveUnit {
public:
 LivingWorldAutoResolveUnit(const Rva0040DC56Element &,unsigned,ArmySummary *);
 virtual void *rvaDestroy(unsigned);
 int references;
 char unknown08[0x24];
 void *thing;
 unsigned unknown30;
};
class Rva004FA168Storage {public: Rva004F87BCElement *start,*finish,*capacity;};

class Rva004FA168Map {
public: Rva004FA168Storage &subscript(const int &);
private: unsigned header,count,unknown8;
};
struct Rva004FA1F3Player {
 _STL::map<int,ArmySummary*> reinforcements;
 char unknown0C[0x20];
 int side,unknown30;
};
class LivingWorldAutoResolveBattle {
public:
 void buildReinforcementMaps();
 void rva004F9635(Rva004F9635Rec *);
 void rva004F9658(Rva004FA168Storage &,EntryVector &,ArmySummary *,unsigned,bool);
 _STL::vector<Rva004FA1F3Player> players;
 char unknown0C[0x18];
 Rva004FA168Map maps[2];
};
void LivingWorldAutoResolveBattle::buildReinforcementMaps()
{
 for(unsigned i=0;i<players.size();++i) {
  Rva004FA1F3Player &player=players[i];
  Rva004FA168Map &map=maps[player.side];
  _STL::map<int,ArmySummary*>::iterator last=player.reinforcements.end();
  for(_STL::map<int,ArmySummary*>::iterator position=player.reinforcements.begin();position!=last;++position) {
   Rva004FA168Storage *units;
   { int round=position->first; units=&map.subscript(round); }
   ArmySummary *army=position->second;
   Rva004FA1F3Entries entries;
   army->GetEntries(*reinterpret_cast<EntryVector *>(&entries));
   rva004F9658(*units,*reinterpret_cast<EntryVector *>(&entries),army,i,true);
  }
 }
}

// Native4F9658..4F971E198B: reserve for army entry count; retain each
// newly constructed52B auto-resolve unit through the stock owning-pointer
// push_back; release the temporary before rejecting a null thingTemplate2C.
// Decrement finish only in the rejection branch then destroy its reference
// slot with the existing34B provider5F8FCC. Sort via canonical thiscall35B.
// WB debug helper12EB1B0 agrees with the named builder and unit constructor.
void LivingWorldAutoResolveBattle::rva004F9658(Rva004FA168Storage &units,EntryVector &entries,ArmySummary *army,unsigned player,bool flag)
{
 reinterpret_cast<Rva004F7DF9Vector *>(&units)->reserve(unsigned(units.finish-units.start)+entries.size());
 EntryVector::iterator position=entries.begin();
 EntryVector::iterator lastEntry=entries.end();
 for(;position!=lastEntry;++position) {
  { Rva004F87BCElement unit(reinterpret_cast<TargetRef00217D4C *>(new LivingWorldAutoResolveUnit(*position,player,army)));
  reinterpret_cast<UnitVector *>(&units)->push_back(unit); }
  if(!reinterpret_cast<LivingWorldAutoResolveUnit *>((units.finish-1)->m_ptr)->thing) {
   Rva004F87BCElement *last=--units.finish;
   reinterpret_cast<Rva005F8FCC *>(last)->rva005F8FCC(0);
  }
 }
 rva004F9635(reinterpret_cast<Rva004F9635Rec *>(&units));
}
