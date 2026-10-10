// ?rva004F99CC@LivingWorldAutoResolveBattle@@QAE_NXZ
// partial score=0.80852 date=2026-10-10
// ?rva004F99CC@LivingWorldAutoResolveBattle@@QAEXPA_N@Z
// partial score=0.80852 date=2026-10-10
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
template void UnitVector::insert<Rva004F87BCElement *>(Rva004F87BCElement *,Rva004F87BCElement *,Rva004F87BCElement *);

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


struct BfmeE12 {float a,b,c;};
struct Rva004F7D7FRecord {char opaque[1];};
typedef _STL::vector<Rva004F7D7FRecord> CleanupVector;
namespace _STL {template<> CleanupVector::~vector();}
struct RoundUnits {
 Rva004F87BCElement *start,*finish,*capacity;
 RoundUnits() {
  typedef _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > HeaderProvider;
  reinterpret_cast<HeaderProvider*>(this)->HeaderProvider::_Vector_base(_STL::allocator<BfmeE16>());
 }
 ~RoundUnits(){reinterpret_cast<CleanupVector*>(this)->CleanupVector::~CleanupVector();}
 void swap(Rva004FA168Storage &other) {
  reinterpret_cast<_STL::vector<BfmeE12> *>(this)->swap(*reinterpret_cast<_STL::vector<BfmeE12> *>(&other));
 }
};
struct Rva004F88BBIterator {
 void *node;
 Rva004F88BBIterator(void *p):node(p){}
 __declspec(nothrow) Rva004F88BBIterator(const Rva004F88BBIterator &p):node(p.node){}
};
struct Rva004F8C16Element {char opaque[4];};
struct Rva004F9185Cmp {};
void rva004F904F(Rva004F8C16Element *,Rva004F8C16Element *,Rva004F8C16Element *,Rva004F9185Cmp);

class Rva004FA168Map {
public: Rva004FA168Storage &subscript(const int &);
 void rva004F88BB(Rva004F88BBIterator);
 void erase(const Rva004F88BBIterator &p){rva004F88BB(p);}
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
 void rva004F99CC(bool *);
 void addUnitsForCurrentRound(int);
 void rva004F9635(Rva004F9635Rec *);
 void rva004F9658(Rva004FA168Storage &,EntryVector &,ArmySummary *,unsigned,bool);
 _STL::vector<Rva004FA1F3Player> players;
 Rva004FA168Storage currentUnits[2];
 Rva004FA168Map maps[2];
 char unknown3C[0x3C];
 int winner,roundNumber;
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

// WB12EB6F0 names this method at the original home assertion372. Native
// 4F922C..4F92E3 consumes the round at7C in two12B maps, transfers each
// mapped owning vector into the corresponding current-unit vector, erases
// the emptied node and merges the sorted old/new ranges. The unused quiet
// argument retains native RET4; its original debug-only scalar type is unknown.
// RoundUnits uses existing header constructor/cleanup providers without
// claiming their historical element spellings as the army/unit type.
void LivingWorldAutoResolveBattle::addUnitsForCurrentRound(int quiet)
{
 const int *round=&roundNumber;
 Rva004FA168Map *map=maps;
 int left=2;
 do {
  _STL::map<int,int> *tree=reinterpret_cast<_STL::map<int,int> *>(map);
  _STL::map<int,int>::iterator found=tree->find(*round);
  if(found._M_node!=tree->end()._M_node) {
   RoundUnits reinforcements;
   reinforcements.swap(*reinterpret_cast<Rva004FA168Storage *>(reinterpret_cast<char *>(found._M_node)+0x14));
   map->erase(Rva004F88BBIterator(found._M_node));
   Rva004FA168Storage *current=reinterpret_cast<Rva004FA168Storage *>(reinterpret_cast<char *>(map)-0x18);
   unsigned oldSize=current->finish-current->start;
   reinterpret_cast<UnitVector *>(current)->insert(current->finish,reinforcements.start,reinforcements.finish);
   Rva004F87BCElement *end=current->finish;
   Rva004F9185Cmp cmp={};
   rva004F904F(reinterpret_cast<Rva004F8C16Element *>(current->start),reinterpret_cast<Rva004F8C16Element *>(current->start+oldSize),reinterpret_cast<Rva004F8C16Element *>(end),cmp);
  }
  ++map;
 }while(--left);
}
class Rva0059AE94 {public:bool rva0059AE94();};
class Rva0059AEFF {public:int rva0059AEFF();};
class Rva0059ADF4 {public:void rva0059ADF4(int);};
class Rva002B254F {public:int rva002B254F();};
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class Rva00380200 {public:bool rva003805BB(float,bool);};
class ThingTemplate {public:void *getCurrentLivingWorldAutoResolveWeapon(const void*) const;};
class Rva004194D6 {public:float rva00419561(int,float,float,int);};
class Rva00427157 {public:float rva004270FA(int);};
class Rva0033A9A5 {public:const Rva00427157 *rva0033A9A5(const void*);};
class Rva0033A65E {public:void *rva0033A65E();};
class LivingWorldAutoResolveBodyTemplate {public:float getHitpointsForLevel(int);};
int GetGameLogicRandomValue(int,int,char*,int);
struct Rva004F99CCEntry {char opaque00[0xC];int level;int mask[4];char opaque20[0x78];int kills,combatKills;};
struct Rva004F99CCThing {char opaque00[0x5C4];int targetType;};
struct Rva004F99CCBonus {char opaque00[0xC];float attack,experience,defense;};
struct Rva004F99CCUnit;
struct Rva004F99CCUnitRef {Rva004F99CCUnit *value; Rva004F99CCUnit *operator->() const {return value;} operator bool()const{return value!=0;} };
struct Rva004F99CCUnit {
 void *vptr;int references;Rva004F99CCEntry *entry;float health,totalHealth;int opaque14;bool acted;char opaque19[3];Rva004F99CCBonus *bonus;
 Rva004F99CCUnitRef target;void *opaque24,*opaque28;Rva004F99CCThing *thing;unsigned player;
};
struct Rva004F99CCPlayer {char opaque00[0x18];float attack,defense,experience;char opaque24[0x10];};
struct Rva004F99CCSideBonus {char opaque00[4];float attack,defense;};
struct Rva004F6057 {TargetRef00217D4C *m_ptr;Rva004F6057 &operator=(const Rva004F6057 &);};
class Rva002BED91 {public:void set(TargetRef00217D4C*);};
struct Rva004F6986 {Rva004F6057 first,second;Rva004F6986(){first.m_ptr=0;second.m_ptr=0;} ~Rva004F6986();};
struct Rva004F93B0Element {int a[2];};
namespace _STL {template<> void vector<Rva004F93B0Element>::push_back(const Rva004F93B0Element &);}

void LivingWorldAutoResolveBattle::rva004F99CC(bool *allActed)
{
 *allActed=true;
 Rva004F87BCElement **ends=&currentUnits[0].finish;
 int sides=2;
 do {
  Rva004F87BCElement *last=*ends;
  for(Rva004F87BCElement *position=*reinterpret_cast<Rva004F87BCElement **>(reinterpret_cast<char *>(ends)-4);position!=last;++position) {
   Rva004F99CCUnit *unit=reinterpret_cast<Rva004F99CCUnit *>(position->m_ptr);
   if(!reinterpret_cast<Rva0059AE94 *>(unit)->rva0059AE94() || !unit->target)continue;
   if(unit->target->health<=0.0f){*allActed=false;continue;}
   Rva004F99CCUnitRef *target=&unit->target;
   Rva004194D6 *weapon=reinterpret_cast<Rva004194D6 *>(reinterpret_cast<ThingTemplate *>(unit->thing)->getCurrentLivingWorldAutoResolveWeapon(unit->entry->mask));
   if(!static_cast<unsigned char>(reinterpret_cast<Rva002B254F *>(TheLivingWorldLogic)->rva002B254F())) {
    int missChance=reinterpret_cast<int *>(weapon)[4];
    if(GetGameLogicRandomValue(1,100,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\AutoResolve\\LivingWorldAutoResolveBattle.cpp",817)<=missChance)goto acted;
   }
   {
    const Rva00427157 *armor=reinterpret_cast<Rva0033A9A5 *>((*target)->thing)->rva0033A9A5((*target)->entry->mask);
    float totalHealth=unit->totalHealth;
    int targetType=(*target)->thing->targetType;
    int level=unit->entry->level;
    float baseDamage=weapon->rva00419561(level,totalHealth,reinterpret_cast<LivingWorldAutoResolveBodyTemplate *>(reinterpret_cast<Rva0033A65E *>(unit->thing)->rva0033A65E())->getHitpointsForLevel(level),targetType);
    unsigned attacker=unit->player;
    unsigned defender=(*target)->player;
    float attack=1.0f;
    if(unit->bonus)attack=unit->bonus->attack;
    float armorFactor=const_cast<Rva00427157 *>(armor)->rva004270FA(unit->thing->targetType);
    float defense=1.0f;
    if((*target)->bonus)defense=(*target)->bonus->defense;
    Rva004F99CCSideBonus **sideBonus=*reinterpret_cast<Rva004F99CCSideBonus ***>(reinterpret_cast<char*>(this)+0x54);
    float attackerBonus=1.0f;
    if(sideBonus[attacker])attackerBonus=sideBonus[attacker]->attack;
    float defenderBonus=1.0f;
    if(sideBonus[defender])defenderBonus=sideBonus[defender]->defense;
    const Rva004F99CCPlayer *playerData=reinterpret_cast<const Rva004F99CCPlayer *>(players.begin());
    (*target)->health-=playerData[defender].defense*playerData[attacker].attack*defenderBonus*attackerBonus*defense*armorFactor*attack*baseDamage;
    if((*target)->health<=0.0f) {
     float experience=playerData[attacker].experience*reinterpret_cast<Rva0059AEFF *>(target->value)->rva0059AEFF();
     Rva00380200 **skills=*reinterpret_cast<Rva00380200 ***>(reinterpret_cast<char*>(this)+0x48);
     if(skills[attacker])skills[attacker]->rva003805BB(experience,true);
     if(unit->bonus)experience*=unit->bonus->experience;
     reinterpret_cast<Rva0059ADF4 *>(unit)->rva0059ADF4(static_cast<int>(experience));
     Rva004F6986 death;
     reinterpret_cast<Rva002BED91 *>(&death.first)->set(reinterpret_cast<TargetRef00217D4C *>(unit));
     death.second=*reinterpret_cast<Rva004F6057 *>(target);
     reinterpret_cast<_STL::vector<Rva004F93B0Element> *>(reinterpret_cast<char *>(this)+0x3C)->push_back(*reinterpret_cast<const Rva004F93B0Element *>(&death));
     ++unit->entry->combatKills;
     ++unit->entry->kills;
    }
   }
   acted:unit->acted=true;
  }
  ends=reinterpret_cast<Rva004F87BCElement **>(reinterpret_cast<char *>(ends)+12);
 }while(--sides);
}
