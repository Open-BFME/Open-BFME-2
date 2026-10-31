// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
#include "../../../../Include/Common/RegionArmyComparatorView.h"
// LivingWorldBattle.cpp -- battle-player members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. Swapping two armies exchanges their pointers in
// the array at +0x04 and swaps the matching 0x68-byte army summaries at +0x10
// through _STL::swap<ArmySummary> (0x003F40EF).

typedef int Int;

class CreateAHeroData;
class Rva003F4DCA { public: int rva003F4DCA(int,int); };
class Rva002B7250 { public: void rva002B7250(CreateAHeroData*); };
struct Rva003B8B61Elem { virtual void destroy(int); char pad04[0x68-4]; };
namespace _STL {
 template<> void** vector<void*,allocator<void*> >::erase(void**);
 template<> Rva003B8B61Elem*vector<Rva003B8B61Elem,allocator<Rva003B8B61Elem> >::erase(Rva003B8B61Elem*);
}



#include "../../../../../../reference/shims/bfme2_ascii/string_base.h"
struct Rva003F498AOuter;
struct Rva003F4E07Results;
struct Rva003F4E07Entry {
 int opaque00; StringBase<char> name; char pad08[0xA8-8]; bool flagA8;
};
struct Rva003F4E07SummaryPair { int key; Rva003F4E07Entry* entry; };
struct Rva003F4E07Summary { char pad00[0x40]; std::vector<Rva003F4E07SummaryPair>entries; };
struct LivingWorldArmy {
 public: char pad00[0x18]; StringBase<char> name; char pad1C[0x78-0x1C]; Rva003F4E07Summary*summary;
};
class Rva003190A5 { public: bool query() const; };
class Rva0040CB2CIndexedField { public: int get(int) const; };
struct Rva002B488EResult { char pad00[0x54]; int playerID; };
class Rva002BA8F1Logic { public: Rva002B488EResult*rva002B488E(int); };
class LivingWorldLogic; extern LivingWorldLogic* TheLivingWorldLogic;
class Rva003F468D { public: int rva003F4DAE(int); };
struct Rva003F4E07Player { char pad00[0x14];int id; };
struct Rva003F4E07Record { char pad00[0x30];int playerID; };
struct Rva003F4E07ArmyIndex { char pad00[0x30];int index; };
struct Rva003F4E07Pair { Rva003F4E07ArmyIndex*loser;Rva003F4E07ArmyIndex*winner; };
struct Rva003F4E07ArmyKey { int key;int value; };
struct Rva003F4E07Results {
 std::vector<Rva003F4E07Record> records;char pad0C[0x3C-0xC];std::vector<Rva003F4E07Pair> pairs;
 char pad48[0x6C-0x48];std::vector<Rva003F4E07ArmyKey>armies;
};


struct BattleArmyRecord
{
	unsigned char m_data[0x68];
};

// The 104-byte swap worker is the rowed _STL::swap<ArmySummary> (0x003F40EF).
class ArmySummary;
namespace _STL { template<> void swap<ArmySummary>(ArmySummary&, ArmySummary&); }

template <class T> inline void swapValues(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

class Rva003F41A4Elem
{
public:
	void Method(int a, int b, int c, int d, int e);
};

typedef void (Rva003F41A4Elem::*Rva003F41A4Fn)(int, int, int, int, int);

class Rva003F5224List
{
public:
	void forEach(Rva003F41A4Fn fn, int a, int b, int c, int d, int e);

private:
	Rva003F41A4Elem **m_begin;
	Rva003F41A4Elem **m_end;
	Rva003F41A4Elem **m_capacity;
	unsigned int m_index;
};

class Rva005CB260
{
public:
	void rva005CB260();
};

struct Rva003F5397Slot;


class LivingWorldBattle
{
public:
	void RetreatArmiesForPlayer(void *);
	Rva003F498AOuter *rva003F4634(void *);
	int rva003F459A();
	class BattlePlayer
	{
	public:
		void SwapArmies(Int first, Int second);

		Rva003F4E07Player *m_player;
		std::vector<LivingWorldArmy*>m_armies; // +4
		std::vector<BattleArmyRecord>m_records; // +0x10
		int counters[5]; // +0x1C
	};
	void rva003F5397(Int a0, Int a1, Int a2, Int a3);
	void rva003F4A46(int, int, Rva0020E20C *const &);
 void RemoveArmy(LivingWorldArmy*);
 void ComputeBattleResultsForPlayersAfterAutoBattle(Rva003F4E07Results*);

private:
	char m_pad00[8];
	Rva003F5224List m_list08;
	std::vector<Rva003F5397Slot>m_table18;
 char pad24[0x38-0x24];int winningSide;
};

struct Rva003F5397Slot
{
	char m_pad[4];
	std::vector<LivingWorldBattle::BattlePlayer>m_players;
	char m_rest[0x1C - 16];
};

// ?rva003F5397@LivingWorldBattle@@QAEXHHHH@Z @0x003F5397 67B.
// Swap player armies then broadcast via rowed forEach 0x003F5224.
// Evidence: retail imul 0x1C 0x30 plus rowed SwapArmies 0x003F427D plus
// rowed forEach 0x003F5224 with func 0x005CB260 plus caller 0x002B41EB.
void LivingWorldBattle::rva003F5397(Int a0, Int a1, Int a2, Int a3)
{
	((BattlePlayer *)((char *)m_table18[a0].m_players.begin() + a1 * 0x30))->SwapArmies(a2, a3);
	m_list08.forEach((Rva003F41A4Fn)&Rva005CB260::rva005CB260, (int)this, a0, a1, a2, a3);
}

// LivingWorldBattle::BattlePlayer::SwapArmies, retail 0x003F427D.
void LivingWorldBattle::BattlePlayer::SwapArmies(Int first, Int second)
{
	swapValues(m_armies[first], m_armies[second]);
	_STL::swap(*(ArmySummary*)&m_records[first], *(ArmySummary*)&m_records[second]);
}

// ComputeBattleResultsForPlayersAfterAutoBattle: WB 104B1D0 (assertions
// LivingWorldBattle.cpp:848..868), five matching callees and native
// 3F4E07..3F4FAA RET4 identify this body. Native independently establishes
// 28-byte sides, 48-byte players, stats at player+1C, and winner at battle+38.
// Result records have stride52/playerID+30; pair and army-key lists stride8.
// Army +18 name/+78 summary, summary entries +40/+44, entry name+4/flag+A8
// agree in both images. Address-derived types are prefix views; their original
// names and full object extents remain unknown. There is no reusable clean
// BFME1/ZH body for this calculation. Existing owners supply every direct call.
void LivingWorldBattle::ComputeBattleResultsForPlayersAfterAutoBattle(Rva003F4E07Results*results)
{
 for(int side=0;side<(int)m_table18.size();++side) {
  Rva003F5397Slot* slot=&m_table18[side];
  int count=((Rva003F468D*)this)->rva003F4DAE(side);
  for(int playerIndex=0;playerIndex<count;++playerIndex) {
   BattlePlayer*player=&slot->m_players[playerIndex];
   int playerID=player->m_player->id;
   Rva003F4E07Pair*pairEnd=results->pairs.end();
   for(Rva003F4E07Pair*pair=results->pairs.begin();pair!=pairEnd;++pair) {
    if(results->records[pair->winner->index].playerID==playerID) ++player->counters[2];
    else if(results->records[pair->loser->index].playerID==playerID) ++player->counters[3];
   }
   Rva003F4E07ArmyKey*key=results->armies.begin();
   Rva003F4E07ArmyKey*armyEnd=results->armies.end();
   for(;key!=armyEnd;++key) {
    Rva002B488EResult*army=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B488E(key->key);
    if(army && army->playerID==playerID) ++player->counters[4];
   }
   for(unsigned armyIndex=0;armyIndex<player->m_armies.size();++armyIndex) {
    LivingWorldArmy*army=player->m_armies[armyIndex];
    if(!army)continue;
    Rva003F4E07Summary*summary=army->summary;
    if(!summary)continue;
    if(!((Rva003190A5*)army)->query())continue;
    int entries=summary->entries.size();
    for(int entryIndex=0;entryIndex<entries;++entryIndex) {
     Rva003F4E07Entry*entry=(Rva003F4E07Entry*)((Rva0040CB2CIndexedField*)summary)->get(entryIndex);
     if(entry->flagA8)++player->counters[1];
     if(side!=winningSide && army->name.compare(entry->name)==0)++player->counters[4];
    }
   }
  }
 }
}

// WB 104C2E0 assertions1175/1178 and native 3F5647..3F5724 RET4 prove
// removal from the parallel army and starting-record vectors. Reuse the
// independently verified side28/player48/record104 layouts and all five owned
// direct callees. The side cursor addresses the player-vector member (+4),
// advancing by the enclosing side stride. Native increment order is retained.
// The listener view at army+8 and observer at battle+4 are opaque ABI views.
// Explicit vector-erase declarations use the existing library implementations.
void LivingWorldBattle::RemoveArmy(LivingWorldArmy *army)
{
    int side = 0;
    if (side >= (int)m_table18.size()) return;
    std::vector<BattlePlayer>*players = &m_table18[0].m_players;
    do {
        int player = 0;
        if (player < ((Rva003F468D *)this)->rva003F4DAE(side)) {
            BattlePlayer *entry = players->begin();
            do {
                int index = 0;
                if (index < ((Rva003F4DCA *)this)->rva003F4DCA(side, player)) {
                    LivingWorldArmy **position = entry->m_armies.begin();
                    do {
                        if (*position == army) {
                            ((Rva002B7250 *)((char *)army + 8))->rva002B7250((CreateAHeroData *)((char *)this + 4));
                            ((_STL::vector<void *, _STL::allocator<void *> > *)&entry->m_armies)->erase((void **)&entry->m_armies[index]);
                            ((_STL::vector<Rva003B8B61Elem, _STL::allocator<Rva003B8B61Elem> > *)&entry->m_records)->erase((Rva003B8B61Elem *)&entry->m_records[index]);
                            return;
                        }
                        ++position;
                    } while (++index < ((Rva003F4DCA *)this)->rva003F4DCA(side, player));
                }
                ++player;
                entry = (BattlePlayer *)((char *)entry + 0x30);
            } while (player < ((Rva003F468D *)this)->rva003F4DAE(side));
        }
        ++side;
        players = (std::vector<BattlePlayer>*)((char*)players + sizeof(Rva003F5397Slot));
    } while (side < (int)m_table18.size());
}

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "../../../Common/System/XferVectorTypes.h"
#include "../../../../Include/Common/BfmeXfer.h"

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};


// Native 3F5729..3F5822 is the complete 249-byte legacy snapshot-vector
// helper called by BattlePlayer::DoXfer at 3F5D32. WB104F290 independently
// supplies the vector/version flow. The clean source follows the already
// verified XferScienceTypeVector.cpp family, originally transferred from
// BFME1; retail proves the 104-byte stride, Xfer slots, exception text,
// constructor 40E3EE, destructor 40E499, reserve 3F5192 and push 3B9369.
// The element is ArmySummary: constructor 0x0040E3EE stores vtable
// 0x00C394F0 whose slot 0 is the rowed ??1ArmySummary (0x0040E499). The two vector casts reuse the existing reserve/push owners
// over their proven three-pointer container and 104-byte record layouts.
class ArmySummary { public: ArmySummary();virtual ~ArmySummary();char pad[100]; };
struct BfmeAssignRecord104 { int data[26]; };
struct BfmePod104 { int data[26]; };
namespace _STL {
 template<> void vector<BfmeAssignRecord104,allocator<BfmeAssignRecord104> >::reserve(unsigned int);
 template<> void vector<BfmePod104,allocator<BfmePod104> >::push_back(const BfmePod104&);
}
Xfer *Rva003F5729Xfer(Xfer*xfer, std::vector<ArmySummary>*vec)
{
 XferVersion version;version.m_version=1;version.m_currentVersion=1;
 (*xfer == reinterpret_cast<Xfer::Version &>(version));
 UnsignedInt count=(UnsignedInt)vec->size();
 (*xfer == "std::vector") == count;
 if(xfer->IsStoring()) {
  ArmySummary*end=vec->end();ArmySummary*cur=vec->begin();
  while(cur!=end){(*xfer == *reinterpret_cast<Snapshot *>(cur));++cur;}
 }else{
  if(!vec->empty())throw XferException(4,"Vector must be empty on load");
  ((_STL::vector<BfmeAssignRecord104>*)vec)->reserve(count);
  ArmySummary value;
  while(count--){
   ((_STL::vector<BfmePod104>*)vec)->push_back(*(BfmePod104*)&value);
   (*xfer == *reinterpret_cast<Snapshot *>(&vec->back()));
  }
 }
 return xfer;
}

// Native1EC0A0..1EC1B3 (276 bytes, EH): the same snapshot-vector helper over
// the 172-byte carryover unit records (constructor 0x0037DF2C, rowed; virtual
// destructor 0x0037DEE4, pinned as ??1Rva0037DF2C), reusing the rowed
// 172-byte reserve 1EBE2D and push 1EC056 owners through the same casts.
class CarryoverUnit { public: CarryoverUnit();virtual ~CarryoverUnit();char pad[0xA8]; };
struct BfmeAssignRecord172 { int data[43]; };
struct BfmePod172 { int data[43]; };
namespace _STL {
 template<> void vector<BfmeAssignRecord172,allocator<BfmeAssignRecord172> >::reserve(unsigned int);
 template<> void vector<BfmePod172,allocator<BfmePod172> >::push_back(const BfmePod172&);
}
Xfer *Rva001EC0A0Xfer(Xfer*xfer, std::vector<CarryoverUnit>*vec)
{
 XferVersion version;version.m_version=1;version.m_currentVersion=1;
 (*xfer == reinterpret_cast<Xfer::Version &>(version));
 UnsignedInt count=(UnsignedInt)vec->size();
 (*xfer == "std::vector") == count;
 if(xfer->IsStoring()) {
  CarryoverUnit*end=vec->end();CarryoverUnit*cur=vec->begin();
  while(cur!=end){(*xfer == *reinterpret_cast<Snapshot *>(cur));++cur;}
 }else{
  if(!vec->empty())throw XferException(4,"Vector must be empty on load");
  ((_STL::vector<BfmeAssignRecord172>*)vec)->reserve(count);
  CarryoverUnit value;
  while(count--){
   ((_STL::vector<BfmePod172>*)vec)->push_back(*(BfmePod172*)&value);
   (*xfer == *reinterpret_cast<Snapshot *>(&vec->back()));
  }
 }
 return xfer;
}

// Native3F4A46..3F4ABB117B RET12; WB104C5D0 identifies the same side
// and player pointer-array sort. Keep this battle member in its home TU:
// defining it alongside AddBattle lets VC7 hoist the caller callback pointer
// outside the loop, changing native initialization order. Each unit is
// independently byte-verified with the shared two-slot callback prefix.
void LivingWorldBattle::rva003F4A46(int side,int player,Rva0020E20C *const &compare)
{
 BattlePlayer *entry=&m_table18[side].m_players[player];
 int count=(int)entry->m_armies.size();
 for (int first=0;first<count;++first) {
  for(int second=first+1;second<count;++second) {
   void *a=entry->m_armies[first];
   void *b=entry->m_armies[second];
   if(!compare->Compare(a,b)) entry->SwapArmies(first,second);
  }
 }
}

// Native 3F6727..3F6936 (527 bytes, RET4); WorldBuilder names
// LivingWorldBattle::RetreatArmiesForPlayer. Native proves the 52-byte
// player records, round count at world+B0 -> campaign+08 -> settings+58,
// and reverse army removal. Opaque views describe only observed storage.
// The auto-resolve constructor calls its existing owned PlayerStorage name;
// the reference below is a view of the same three-pointer vector header.
struct Rva003F4CC0Inner;
class Rva003F4CC0 {public:Rva003F4CC0Inner *rva003F4CC0(int);};
class Rva003F5DBD {public:void rva003F5E3F(void *,void *);};
struct Rva002BBB96Element {char opaque00[0x18];float strength18;char opaque1C[0x30-0x1C];int player30;};
namespace _STL {
 template<> vector<Rva002BBB96Element>::~vector();
 template<> _Vector_base<Rva002BBB96Element,allocator<Rva002BBB96Element> >::~_Vector_base();
 template<> void _STLP_alloc_proxy<Rva002BBB96Element*,Rva002BBB96Element,allocator<Rva002BBB96Element> >::deallocate(Rva002BBB96Element*,unsigned);
 template<> void allocator<Rva002BBB96Element>::deallocate(Rva002BBB96Element*,unsigned)const;
}
class Rva00380200 {public:Rva00380200();virtual ~Rva00380200();};
class Rva002B2508:public Rva00380200 {public:Rva002B2508();virtual ~Rva002B2508();char opaque04[0x2C-4];};
class Rva002B2EA0 {public:void rva002B2EA0();};
struct RetreatSlots {Rva002B2508 *first;RetreatSlots(Rva002B2508 *p):first(p){}~RetreatSlots(){reinterpret_cast<Rva002B2EA0 *>(this)->rva002B2EA0();}};
// The retreat result list is a PlayerStorage (the auto-resolve battle's
// input): its destructor is the 5-byte thunk 0x002BBD4D the unwind funclet
// jumps to; the normal path expands it into the vector destructor.
struct PlayerStorage : public _STL::vector<Rva002BBB96Element>
{
};
// The 0x80-byte object: ctor 0x004FA3C9 is LivingWorldAutoResolveBattle's
// row, dtor 0x004FA2E2 is rowed as Rva004FA2E2 (LivingWorldAIArmyMover.cpp's
// view). A wrapper constructor would emit a non-retail copy at 0x004FA3C9.
class Rva004FA2E2 {public:~Rva004FA2E2();char opaque00[0x80];};
class LivingWorldAutoResolveBattle : public Rva004FA2E2 {public:LivingWorldAutoResolveBattle(const PlayerStorage&);void applyResults();};
class Rva004FA10FOwner {public:void rva004FA10F();};
class Rva002B8644 {public:void rva002B8644(int);};
class ModuleData;
class Rva002B8A9F {public:void rva002B8A9F(ModuleData*);};
struct RetreatSettings {char opaque00[0x58];int rounds58;};
struct RetreatCampaign {char opaque00[8];RetreatSettings *settings08;};
class LivingWorldLogic {public:void rva002BCCFB(LivingWorldBattle *,int,int);char opaque00[0xB0];RetreatCampaign *campaignB0;};
void LivingWorldBattle::RetreatArmiesForPlayer(void *player) {
 Rva003F498AOuter *side=rva003F4634(player);
 if(!side)return;
 BattlePlayer *entry=reinterpret_cast<BattlePlayer *>(reinterpret_cast<Rva003F4CC0 *>(side)->rva003F4CC0((int)player));
 if(!entry)return;
 PlayerStorage players;
 RetreatSlots slots(new Rva002B2508[rva003F459A()]);
 reinterpret_cast<LivingWorldLogic *>(TheLivingWorldLogic)->rva002BCCFB(this,(int)&players,(int)&slots);
 for(unsigned i=0;i<players.size();++i) {
  int id=reinterpret_cast<Rva003F4E07Player *>(player)->id;
  Rva002BBB96Element &record=players[i];
  if(record.player30==id)record.strength18=0.0f;
 }
 LivingWorldAutoResolveBattle battle(players);
 // Refresh the settings pointer each round, as retail does. Keeping this
 // pointer live gives VC7 the retail EDI induction variable.
 RetreatSettings *settings=reinterpret_cast<LivingWorldLogic *>(TheLivingWorldLogic)->campaignB0->settings08;
 for(int i=0;i<settings->rounds58;++i) {
  reinterpret_cast<Rva004FA10FOwner *>(&battle)->rva004FA10F();
  settings=reinterpret_cast<LivingWorldLogic *>(TheLivingWorldLogic)->campaignB0->settings08;
 }
 battle.applyResults();
 for(int i=int(entry->m_armies.size())-1;i>=0;--i) {
  LivingWorldArmy *army=entry->m_armies[i];
  if(!army->name.isEmpty())reinterpret_cast<Rva002B8644 *>(TheLivingWorldLogic)->rva002B8644((int)army);
  else reinterpret_cast<Rva002B8A9F *>(TheLivingWorldLogic)->rva002B8A9F(reinterpret_cast<ModuleData *>(army));
  reinterpret_cast<Rva002B7250 *>((char*)entry->m_armies[i]+8)->rva002B7250(this?reinterpret_cast<CreateAHeroData *>((char*)this+4):0);
  reinterpret_cast<_STL::vector<void*> *>(&entry->m_armies)->erase(reinterpret_cast<void **>(&entry->m_armies[i]));
  reinterpret_cast<_STL::vector<Rva003B8B61Elem> *>(&entry->m_records)->erase(reinterpret_cast<Rva003B8B61Elem *>(&entry->m_records[i]));
 }
 reinterpret_cast<Rva003F5DBD *>(side)->rva003F5E3F(this,player);
}
