// ?GetResolutionOptions@LivingWorldBattle@@QAEHXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
// LivingWorldBattle.cpp -- battle-player members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. Swapping two armies exchanges their pointers in
// the array at +0x04 and swaps the matching 0x68-byte army records at +0x10
// through 0x003F40EF (unnamed).

typedef int Int;

class CreateAHeroData;
class Rva003F4DCA { public: int rva003F4DCA(int,int); };
class Rva002B7250 { public: void rva002B7250(CreateAHeroData*); };
struct Rva003B8B61Elem { virtual void destroy(int); char pad04[0x68-4]; };
namespace _STL {
 template<> void** vector<void*,allocator<void*> >::erase(void**);
 template<> Rva003B8B61Elem*vector<Rva003B8B61Elem,allocator<Rva003B8B61Elem> >::erase(Rva003B8B61Elem*);
}



#include "../reference/shims/bfme2_ascii/string_base.h"
class LivingWorldBattle;

class GameLogic; extern GameLogic*TheGameLogic;
class GameInfo; extern GameInfo*TheGameInfo; extern GameInfo*TheSkirmishGameInfo;
class Rva00210C66CmpBoolField {public:bool get()const;};
class Rva002B254F {public:int rva002B254F();void*rva002B256E();};
class Rva003F44A9 {public:bool rva003F44ED();};
class Rva002E071E {public:int rva002E0BC0(int);};
class Rva0020E89C;
class Rva0020EAF6View {public:Rva0020E89C*rva0020EAF6(int);};
struct Rva003F4FD4LogicView {char pad00[0x98];void*player;char pad9C[0xB0-0x9C];Rva0020EAF6View*manager;};
struct Rva003F4FD4GameLogicView {char pad00[0x114];int mode;};
struct Rva003F4FD4GameInfoView {char pad00[0x7C];int kind;};
struct Rva003F4FD4Adjacent {char pad00[8];int id;char pad0C[0x18-0xC];};
struct Rva003F4FD4Region {
 char pad00[0xA9];bool special;char padAA[0x12C-0xAA];int id;
 char pad130[0x1A8-0x130];std::vector<Rva003F4FD4Adjacent> adjacent;
};
struct Rva003F4FD4OwnedRegion {char pad00[0x13C];int playerID;};
class Rva003F4FD4Tutorial {
public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();virtual void slot04();
 virtual void slot05();virtual void slot06();virtual void slot07();virtual void slot08();virtual void slot09();
 virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();
 virtual int slot14(LivingWorldBattle*);
};

struct Rva003F4E07Results;
struct Rva003F4E07Entry {
 int opaque00; StringBase<char> name; char pad08[0xA8-8]; bool flagA8;
};
struct Rva003F4E07SummaryPair { int key; Rva003F4E07Entry* entry; };
struct Rva003F4E07Summary { char pad00[0x40]; std::vector<Rva003F4E07SummaryPair>entries; };
class LivingWorldArmy {
 public: char pad00[0x18]; StringBase<char> name; char pad1C[0x78-0x1C]; Rva003F4E07Summary*summary;
};
class Rva003190A5 { public: bool query() const; };
class Rva0040CB2CIndexedField { public: int get(int) const; };
struct Rva002B488EResult { char pad00[0x54]; int playerID; };
class Rva002BA8F1Logic { public: Rva002B488EResult*rva002B488E(int);int rva002B5256(bool); };
class LivingWorldLogic {public:bool WillPlayerBeEliminatedIfHeOrSheLosesThisRegion(int,int);}; extern LivingWorldLogic* TheLivingWorldLogic;
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

// The 104-byte swap worker is already owned by this STLport instantiation.
struct Rva003F40EFRecord;
namespace _STL { template<> void swap<Rva003F40EFRecord>(Rva003F40EFRecord&, Rva003F40EFRecord&); }

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
 int GetResolutionOptions();void*rva003F4DEE(void*);int rva003F4831();
 void RemoveArmy(LivingWorldArmy*);
 void ComputeBattleResultsForPlayersAfterAutoBattle(Rva003F4E07Results*);

private:
	char m_pad00[8];
	Rva003F5224List m_list08;
	std::vector<Rva003F5397Slot>m_table18;
 Rva003F4FD4Region*region24;char pad28[0x38-0x28];int winningSide;
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
	_STL::swap(*(Rva003F40EFRecord*)&m_records[first], *(Rva003F40EFRecord*)&m_records[second]);
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

int LivingWorldBattle::GetResolutionOptions()
{
 if((unsigned char)((Rva002B254F*)TheLivingWorldLogic)->rva002B254F())
  return ((Rva003F4FD4Tutorial*)((Rva002B254F*)TheLivingWorldLogic)->rva002B256E())->slot14(this);
 Rva003F4FD4Region*region=region24;
 if(!region)return 0;
 Rva003F4FD4GameInfoView*info=0;
 GameLogic*gameLogic=TheGameLogic;
 if(((Rva00210C66CmpBoolField*)gameLogic)->get())info=(Rva003F4FD4GameInfoView*)TheGameInfo;
 else if(((Rva003F4FD4GameLogicView*)gameLogic)->mode!=3)info=(Rva003F4FD4GameInfoView*)TheSkirmishGameInfo;
 if(region->special)return 8;
 int flags=0;
 if(info->kind!=2)flags=2;
 bool mayRetreat=false;
 bool eliminated=false;
 void*localPlayer=((Rva003F4FD4LogicView*)TheLivingWorldLogic)->player;
 BattlePlayer*player=localPlayer?(BattlePlayer*)rva003F4DEE(localPlayer):0;
 if(player){
  if(!((Rva003F44A9*)player)->rva003F44ED())mayRetreat=false;
  else {
   std::vector<Rva003F4FD4Adjacent>*adjacent=&region->adjacent;
   for(unsigned i=0;i<adjacent->size();++i){
    Rva0020E89C*owned=((Rva003F4FD4LogicView*)TheLivingWorldLogic)->manager->rva0020EAF6((*adjacent)[i].id);
    if(owned&&(unsigned char)((Rva002E071E*)player->m_player)->rva002E0BC0(((Rva003F4FD4OwnedRegion*)owned)->playerID)){
     mayRetreat=true;break;
    }
   }
  }
  int regionID=region24->id;
  int playerID=player->m_player->id;
  if(TheLivingWorldLogic->WillPlayerBeEliminatedIfHeOrSheLosesThisRegion(playerID,regionID))eliminated=true;
  if(mayRetreat&&!eliminated)flags|=4;
 }
 if(info->kind!=1){
  if(((Rva003F4FD4GameLogicView*)TheGameLogic)->mode==0)flags|=8;
  else {
   int count=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B5256(false);
   if(rva003F4831()==count)flags|=8;
   else flags|=2;
  }
 }
 return flags;
}
