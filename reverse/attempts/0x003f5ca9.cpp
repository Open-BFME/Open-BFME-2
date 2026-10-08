// ?DoXfer@BattlePlayer@LivingWorldBattle@@QAEXPAVXfer@@@Z
// partial score=0.88 date=2026-10-08
// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
// LivingWorldBattle.cpp -- battle-player members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. Swapping two armies exchanges their pointers in
// the array at +0x04 and swaps the matching 0x68-byte army records at +0x10
// through 0x003F40EF (unnamed).

typedef int Int;

class Xfer;
class CreateAHeroData;
class Rva003F4DCA { public: int rva003F4DCA(int,int); };
class Rva002B7250 { public: void rva002B7250(CreateAHeroData*); };
struct Rva003B8B61Elem { virtual void destroy(int); char pad04[0x68-4]; };
namespace _STL {
 template<> void** vector<void*,allocator<void*> >::erase(void**);
 template<> Rva003B8B61Elem*vector<Rva003B8B61Elem,allocator<Rva003B8B61Elem> >::erase(Rva003B8B61Elem*);
}



#include "../reference/shims/bfme2_ascii/string_base.h"
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
class Xfer;class ModuleData;class Rva002E2903Player;
class Rva002BA8F1Logic { public: Rva002E2903Player*find(int,unsigned*);void rva002B8D06(Xfer*,std::vector<const ModuleData*>*); Rva002B488EResult*rva002B488E(int); };
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
	virtual void slot0();virtual void slot1();virtual void slot2();virtual void DoXfer(Xfer*);
 unsigned char m_data[0x64];
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
  void DoXfer(Xfer*);

		Rva003F4E07Player *m_player;
		std::vector<LivingWorldArmy*>m_armies; // +4
		std::vector<BattleArmyRecord>m_records; // +0x10
		int counters[5]; // +0x1C
	};
	void rva003F5397(Int a0, Int a1, Int a2, Int a3);
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

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ScienceType
{
	SCIENCE_0 = 0
};
// The same ScienceType vector's native overflow is rowed at 0x148D00.
namespace _STL {
template <> void vector<ScienceType, allocator<ScienceType> >::_M_insert_overflow(
    ScienceType *, const ScienceType &, const __false_type &, unsigned int, bool);
template <> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
}

enum ObjectID
{
	OBJECTID_0 = 0
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion &version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void xferSnapshot(void*);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(void *value);
	virtual void slot28();
	virtual void slot29();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};



class Rva0040E3EE;
struct BfmeAssignRecord104 { int data[26]; };
namespace _STL { template<> BfmeAssignRecord104*vector<BfmeAssignRecord104,allocator<BfmeAssignRecord104> >::erase(BfmeAssignRecord104*,BfmeAssignRecord104*); }
class Rva003F5A06 {public:void rva003F5C4F(int);};
class Rva003F3FFE {public:void rva003F3FFE(Xfer&);};
class Rva003F5CA9Snapshot {public:virtual void slot0();virtual void slot1();virtual void slot2();virtual void DoXfer(Xfer*);};
void XferLivingWorldPlayerID(Xfer*,int*);
Xfer*Rva003F5729Xfer(Xfer*,std::vector<Rva0040E3EE>*);
void LivingWorldBattle::BattlePlayer::DoXfer(Xfer*xfer)
{
 XferVersion version;version.m_version=1;version.m_currentVersion=4;
 xfer->xferVersion(version);
 if(xfer->isLoading()){
  int id;XferLivingWorldPlayerID(xfer,&id);
  m_player=(Rva003F4E07Player*)((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(id,0);
 }else{
  int id=m_player->id;XferLivingWorldPlayerID(xfer,&id);
 }
 ((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B8D06(xfer,(std::vector<const ModuleData*>*)&m_armies);
 if(version.m_currentVersion>=2)((Rva003F3FFE*)counters)->rva003F3FFE(*xfer);
 if(version.m_currentVersion==3){Rva003F5729Xfer(xfer,(std::vector<Rva0040E3EE>*)&m_records);}
 else if(version.m_currentVersion>=4){
  unsigned count=m_records.size();xfer->xferUnsignedInt(count);
  if(xfer->isLoading()){
   typedef std::vector<BfmeAssignRecord104> V;
   V*v=(V*)&m_records;v->erase(v->begin(),v->end());
   ((Rva003F5A06*)&m_records)->rva003F5C4F(count);
  }
  for(unsigned i=0;i<m_records.size();++i){
   m_records[i].DoXfer(xfer);
  }
 }
}
