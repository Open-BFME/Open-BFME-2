// ?spawnArmy@LivingWorldLogic@@QAEPAULivingWorldArmy@@PAVRva004E3184@@PAURva002B6A04Player@@_N@Z
// partial score=0.75 date=2026-10-10
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#include "C:/Users/nleig/.codex/worktrees/b66d-stances/Open-BFME-2/Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include <vector>
#include <map>
#include <list>
#include <set>
class UnicodeString;
namespace _STL {
template <> void _List_base<UnicodeString, allocator<UnicodeString> >::clear();
}
struct LivingWorldRevivalUnitDataView;
struct LivingWorldArmy; class Rva004E3184;
class LivingWorldPlayer { public:
 bool rva002E0B30();
 void AddArmy(class LivingWorldArmy *);
 bool rva002E112A(Rva004E3184 *);
 bool rva002E12F3(int);
 int rva002E199E(const void *);
 void GetRevivalUnitData(int,LivingWorldRevivalUnitDataView *);
 void RemoveRevivalUnit(int);
};
class LivingWorldLogic;
struct LivingWorldBuildingNuggetSpawnArmy;
LivingWorldLogic *TheLivingWorldLogic = 0;
class Rva002B74DE
{
public:
	Rva002B74DE(LivingWorldLogic *logic, Int battle);	
	~Rva002B74DE();						
	Int Update();						
private:
	unsigned char m_data[0x28];
};
class Rva002B90B3
{
public:
	void reset(Rva002B74DE *resolver);			
	Rva002B74DE *get() const { return m_ptr; }
private:
	Rva002B74DE *m_ptr;
};
class Rva002E2903Player
{
public:
	void rva002E2D8D(void *army);				
};
class AsciiString;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(Int index);
	Rva002E2903Player *find(Int playerID, UnsignedInt *index);	
	Rva002E2903Player *find(const AsciiString &name, UnsignedInt *index);	
	struct Rva002B488EResult *rva002B488E(Int armyID);	
	struct Rva002B2579Result *rva002B2579(int id);	
	struct Rva002B3740Item *rva002B2B2D();	
private:
	char m_pad00[0xB0];
	void *m_containerB0;	
	int m_padB4;
	int m_keyB8;	
};
struct LivingWorldUpgradeArmy
{
	unsigned char m_pad000[0x13c];
	Int m_playerID;						
};
struct Rva002B5334Base
{
	unsigned char m_pad00[0x2c];
};
struct Rva002B5334ArmyList
{
	_STL::vector<LivingWorldUpgradeArmy *> m_armies;
};
struct Rva002B5334ArmySet : public Rva002B5334Base, public Rva002B5334ArmyList
{
};
#include "C:/Users/nleig/.codex/worktrees/b66d-stances/Open-BFME-2/Code/Libraries/Include/Lib/Coord2D.h"
class LivingWorldRegionManager
{
public:
	Bool GetRegionCenterPoint(Int regionID, Coord2D *out);	
	Bool GetRegionCenterPoint(class Rva0020E89C *region, Coord2D *out);
	class Rva00318C32Ret *rva0020FAEA(const Coord2D *pos, class Rva00318C32Ret *hint);
	void rva0020FB8B(class LivingWorldBattle *battle);	
	void UpdateBattleMarkers();				
	Int ValidateArmyRegionEntry(struct LivingWorldArmy *army, class Rva00318C32Ret *from, class Rva00318C32Ret *to, Int a, Int b);
	unsigned char m_pad00[0x8];
	Rva002B5334ArmySet *m_armySet;				
	unsigned char m_pad0C[0x14 - 0xc];
	_STL::vector<void *> m_field14;				
private:
	class Rva0020E89C *rva0020EAF6(int key);		
	friend class Rva002BA8F1Logic;
};
class Rva002B4B3D
{
public:
	Bool rva002B4B3D();					
};
class Rva002B3288
{
public:
	Bool rva002B3288();					
};
class Rva002B9099
{
public:
	void clear();						
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);	
class Rva004E0632;
class ArmySummaryEntry
{
public:
	void MarkForUpgrades(const Rva004E0632 *upgrades);	
	void CancelUpgrades();					
	Int getMoveTarget() const { return m_moveTarget; }
	unsigned char m_pad00[0xac];
	unsigned char m_padAC[0xb8 - 0xac];
	Int m_moveTarget;					
	unsigned char m_padBC[0xc4 - 0xbc];
	Bool m_disbanded;					
};
struct ArmySummaryEntryRef
{
	~ArmySummaryEntryRef()
	{
		if (m_entry)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)m_entry + 0xac));
	}
	ArmySummaryEntry *m_entry;
};
class ArmySummary
{
public:
	ArmySummaryEntryRef GetEntry(Int entryID);		
};
class Rva004E3184;
struct Rva002B6A04Player;
class Rva00318D14ByteSlot {public:void set(unsigned char);};
struct LivingWorldArmy
{
 LivingWorldArmy(Int,Rva004E3184 *,Rva002B6A04Player *);
	void initiateMove(const Coord2D &pos, class Rva00318C32Ret *target, Int flags);
	unsigned char m_pad00[0x20];
	Int m_id;						
	unsigned char m_pad24[0x54 - 0x24];
	Int m_ownerPlayer;					
	unsigned char m_pad58[0x74 - 0x58];
	Bool m_field74;						
	unsigned char m_pad75[0x78 - 0x75];
	ArmySummary *m_summary;					
 unsigned char m_pad7C[0x98-0x7C];
};
class Rva002B616FListener
{
public:
	virtual void slot00();
	virtual void onTurnChanged(void *oldTurn, int newTurn);	
};
class Rva002B616FList
{
public:
	void forEach(void (Rva002B616FListener::*notify)(void *, int), void *arg, int value);	
private:
	unsigned char m_data[0x10];
};
class Rva002B7BFB
{
public:
	void rva002B7BFB();					
};
class Rva003B8BAA
{
public:
	void *rva003B8BAA();					
	void rva003B8CAC();					
};
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;
class LivingWorldCampaignManager
{
public:
	void *UseGenericSpawnArmyForPlayer(Int a, Int b);	
	void StartNewCampaign(const AsciiString &name);
	void StartNewCampaign(Int campaign);
};
struct Rva002B8660Army
{
	unsigned char m_pad00[0x4c];
	Int m_id;						
};
struct Rva002B8660Player
{
	unsigned char m_pad00[0x14];
	Int m_id;						
};
class ModuleData;
class Rva004E0632Filter
{
public:
	virtual void slot00();
	virtual Bool accepts(ArmySummaryEntry *entry);		
};
class Rva004E0632
{
public:
	Int rva004E0632() const;				
};
class Rva003F287F
{
public:
	void rva003F287F(_STL::vector<const ModuleData *> &out);	
	void rva003F28DB(_STL::vector<const ModuleData *> &out);	
	unsigned char m_pad000[0x12c];
	Int m_regionID;						
	unsigned char m_pad130[0x13c - 0x130];
	Int m_ownerPlayer;					
};
struct DelayedRegionVictory
{
	Int player;
	Int regionID;
	UnsignedInt flags;
};
struct PrereqUnitRec
{
	unsigned int m_data[3];
	~PrereqUnitRec() {}
};
namespace _STL {
template <> void vector<PrereqUnitRec, allocator<PrereqUnitRec> >::push_back(const PrereqUnitRec &);
}
class Xfer
{
public:
	class Version
	{
	public:
		Version(unsigned char current, unsigned char minimum) : m_current(current), m_minimum(minimum) {}
		unsigned char m_current;
		unsigned char m_minimum;
	};
	virtual void slot00();
	virtual Bool IsLoading() const;				
	virtual void slot08();
	virtual Bool IsCRC() const;				
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual Xfer &XferRawBytes(void *data, UnsignedInt size);	
	virtual Xfer &xferVersion(Version &value);		
	virtual void slot2C();
	virtual Xfer &xferSnapshot(void *snapshot);		
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual Xfer &xferInt(Int &value);			
};
void XferLivingWorldPlayerID(Xfer *xfer, int *playerID);	
struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(Rva003EFE82Obj *obj, void *out);	
struct Rva002B24F0Obj;
int __cdecl Rva002B24F0Get(Rva002B24F0Obj *obj, void *out);	
template <class T> class StringBase
{
public:
	void set(const StringBase &that);			
	bool isEmpty() const;
    int compare(const StringBase &that) const;					
	StringBase &operator=(const StringBase &that) { set(that); return *this; }
private:
	T *m_data;
};
struct Rva003F0F13Elem
{
	float a;
	float b;
};
struct Rva0059E647Entry;
class LivingWorldRegion
{
public:
	void rva003F0FA3(void *army);
	void GetGarrisonArmyPlacementSpot(Rva003F0F13Elem *out);	
	void *rva003F0588();					
	void rva003F2A8C(Int playerID);				
	void rva003EFE72(void *slot, Rva0059E647Entry *buildingTemplate);	
	void BuildBuilding(void *slot, Rva0059E647Entry *buildingTemplate);	
	unsigned char m_pad000[0x13c];
	Int m_ownerPlayer;					
};
class Rva004E3184
{
public:
	Rva004E3184(void *arg);					
	virtual ~Rva004E3184();					
	StringBase<char> m_name;				
	unsigned char m_pad08[0x20 - 0x8];
	Rva003F0F13Elem m_pos;					
	unsigned char m_pad28[0x54 - 0x28];
	Bool flagged()const{return m_flag54;}
	Bool m_flag54;						
	unsigned char m_pad55[0x58 - 0x55];
};
struct Rva002B6A04Template
{
	unsigned char m_pad00[0x24];
	StringBase<char> m_name24;				
	unsigned char m_pad28[0x34 - 0x28];
	StringBase<char> m_name34;				
};
struct Rva002B6A04Player
{
	unsigned char m_pad00[0x40];
	Rva002B6A04Template *m_template;			
};
struct Rva002B6A04Summary
{
	unsigned char m_pad00[0x64];
	StringBase<char> m_name64;				
};
void *__stdcall Rva002B4948Find(void *player, void *region, void *arg);	
#include "C:/Users/nleig/.codex/worktrees/b66d-stances/Open-BFME-2/Code/GameEngine/Source/Common/ArmyMoveDispatchView.h"
#include "C:/Users/nleig/.codex/worktrees/b66d-stances/Open-BFME-2/Code/GameEngine/Source/Common/RegionCenterPointDispatchView.h"
class Rva002BA82BBase00
{
public:
	virtual void slot00();
	virtual void slot04();
private:
	unsigned char m_pad04[0x10 - 0x4];
};
class Rva002BA82BObserver10
{
public:
	virtual void slot00();
};
class Rva002BA82BRegionObserver
{
public:
	virtual void OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID) = 0;
};
struct LivingWorldCollectorPlayerView
{
 char pad00[0x34];
 Int key34;
 char pad38[0x3c4-0x38];
 unsigned char flag3C4;
};
class Rva00072FE6 { public: void rva00072FE6(); };
struct Parent0057605D;struct Parent00575EEA;
class Rva004E071D {public:void rva004E071D(Bool);};
struct LocalCampaignRegions2C {char pad2c[0x2c];_STL::vector<Rva003F287F*>regions;};
struct LocalPlayerId14 {char pad14[0x14];Int id;};
struct LocalRegionOwner13C {char pad13c[0x13c];Int owner;};
class Rva004FC275 {public:void rva004FC275(unsigned char);};
struct LocalRegionPlots170 {char pad13c[0x13c];Int owner;char pad140[0x170-0x140];_STL::vector<Parent00575EEA*>plots;};
struct TurnPhasePairView {void *begin,*end;bool empty()const{return begin==end;}};
struct Parent00575E4E;
class LivingWorldLogic : public Rva002BA82BBase00, public Rva002BA82BObserver10, public Rva002BA82BRegionObserver
{
public:
	virtual void OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID);
	const Rva004E0632 *GetArmoryToUpgradeTroop(ArmySummaryEntry *entry, LivingWorldArmy *army, Rva003F287F *region);
	void UpdateTurnPhase();
	void AdjustArmyTargetLocations();
	void ValidatePlayers();
	void rva002B693F(void *keys);
	UnsignedInt rva002B77B2();
	UnsignedInt rva002B77F7();
	void rva002B5AF7();
 void rva002BD9B4();
 void rva002B768F();
 Bool rva002B3484(Parent0057605D*);
 Bool rva002B3416(Parent00575EEA*);
 void rva002B676D();
 void rva002B88EC();
	Bool rva002B5A5F(Parent00575E4E*);
	bool rva002B4B83();
	Bool EndTurn();
	Bool AdvanceTurnPhase();
	Bool IsCurrentTurnPhaseFinished();
	void processArmyDestroyList();
	void MarkTroopForUpgrades(Int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades);
	void CancelTroopUpgrades(Int entryID, LivingWorldArmy *army);
	void StartAutoResolveBattle(Int battle);
	void rva002BD90D(UnsignedInt flags, Int battle);
	Bool rva002B89E1(Int battle);
	void rva002BD544(Int campaign);
	void rva002B84CD(Int campaign); 
	void rva002B47C3(); 
	void rva002B83E5();
	void rva002B49A8();
	void AutoResolveBattle(Int battle);
	void AutoMarkUnitsForUpgrades();
	void CalcAttackingDirection(const _STL::vector<Int> &path, Coord2D *direction);
	Bool CanMoveArmyMember(LivingWorldArmy *army, Int entryID, Int target);
	Bool rva002B8019(LivingWorldArmy *army, ArmySummaryEntry *entry, Int target);	
	void LetAIResolveRegionAwardDispute(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags);
	Rva002B8660Army *UseGenericSpawnArmyForPlayer(Int a, Rva002B8660Player *player);
	Bool CanMoveArmyMember_internal(LivingWorldArmy *army, ArmySummaryEntry *entry, LivingWorldArmy *target, Bool checkRoom);
	Bool canBuildUnit(LivingWorldBuildingNuggetSpawnArmy *nugget, Int token);
	Int rva002B2C12(LivingWorldArmy *army, LivingWorldArmy *target);
	void GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F *region, Int player, Int *countA, Int *countB);
	void EnforceArmyRegionOwnership();
	Bool rva002B27B5(LivingWorldArmy *army, Rva00318C32Ret *target);
	Rva002B2858Coord AdjustArmyMoveTargetPos(Rva00318C32Ret *target, const Coord2D *pos);	
	void armyMoveRequest(LivingWorldArmy *army, Rva00318C32Ret *target, const Coord2D *pos, Int flags);
	void rva002B2834(LivingWorldArmy *army, Int flags);
	void XferDelayedRegionVictories(Xfer *xfer);
	void XferPlayers(Xfer *xfer);
	void AwardOwnershipSetsToPlayers();
	void spawnCity(Rva004E3184 *city);
	LivingWorldArmy *spawnArmy(Rva004E3184 *spawn, Rva002B6A04Player *player, Bool flag);	
	LivingWorldArmy *CreateEmptyGarrisonArmy(Rva002B6A04Player *player, LivingWorldRegion *region);
	void *rva002B4948(void *player, LivingWorldRegion *region, Int arg);	
	void spawnBuilding(const struct Rva002B99F8Request *request);
	Bool rva002B5CBB(const struct Rva002B4C35Player *player);
	void GameLogic_tacticalBattleComplete();
	void OnBattleComplete(class LivingWorldBattle *battle);
	void rva002B9A90(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags);	
	void rva002B37FF(class LivingWorldBattle *battle);	
	void PrepareBattleForLoading(class LivingWorldBattle *battle);
private:
	void AddDelayedRegionVictory(Rva003F287F *region, Int player, UnsignedInt flags);	
	void CheckTurnPhaseTransitions();		
	void rva002B5B55(void *army);			
	unsigned char m_pad18[0x1c - 0x18];
	Rva002B616FList m_turnListeners;		
	unsigned char m_pad2C[0x3c - 0x2c];
	Rva002B616FList m_battleListeners;		
	unsigned char m_pad4C[0x8c - 0x4c];
	_STL::vector<LivingWorldPlayer *> m_players;	
	LivingWorldPlayer *m_localPlayer;		
	Int m_field9C, m_fieldA0, m_fieldA4, m_fieldA8, m_fieldAC; 
	LivingWorldRegionManager *m_field0B0;		
	unsigned char m_padB4[0xb6 - 0xb4];
	Bool m_fieldB6;					
	unsigned char m_padB7[0xb8 - 0xb7];
	Int m_fieldB8;					
	unsigned char m_padBC[0xcc - 0xbc];
	_STL::vector<void *> m_fieldCC;			
	unsigned char m_padD8[0xf4 - 0xd8];
	Int m_turnPhase;				
	Int m_fieldF8; 
	Int m_turn;					
	UnsignedInt m_field100;				
	UnsignedInt m_field104;				
	Bool m_field108;				
	Bool m_field109;				
	Bool m_native10A; unsigned char m_pad10B;
	_STL::vector<void *> m_field10C;		
	_STL::vector<void *> m_armyDestroyList;		
	unsigned char m_pad124[0x130 - 0x124];
	_STL::map<Int, class RegionAwardDispute *> m_regionAwardDisputes;	
	_STL::multimap<Int, Int> m_spawnedArmies;	
	_STL::vector<DelayedRegionVictory> m_delayedRegionVictories;	
	TurnPhasePairView m_pending154; unsigned char m_pad15C[0x178 - 0x15c];
	Rva002B90B3 m_autoBattleResolver;		
};
struct ThingTemplateKindOf
{
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[6];				
	Bool isKindOf(Int bit) const { return (m_kindOf[bit >> 5] >> (bit & 31)) & 1; }
};
class Rva0037DCA5
{
public:
	void *rva0037DC52();					
};
class Rva003193EC
{
public:
	bool rva00319413(Rva0037DCA5 *entry);
    void rva00319904(Rva003193EC *);			
};
class Rva0040CB2CIndexedField
{
public:
	Int get(Int index) const;					
};
struct Rva002B3325Summary
{
	struct Entry { Int id; ArmySummaryEntry *entry; };
	unsigned char m_pad00[0x40];
	_STL::vector<Entry> m_entries;
};
class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();				
};
struct Rva003F26AAPair {int a,b;};
class LivingWorldRegionConnection {public:bool rva003F26AA(const ModuleData *,Rva003F26AAPair *);};
class Rva00319AA0 {public:void rva00319AA0(const Coord2D *);};
LivingWorldArmy *LivingWorldLogic::spawnArmy(Rva004E3184 *spawn,Rva002B6A04Player *player,Bool bypass)
{
 if(spawn->m_flag54)return 0;
 if(!bypass && !((LivingWorldPlayer*)player)->rva002E112A(spawn))return 0;
 LivingWorldArmy *army=::new LivingWorldArmy(++m_field9C,spawn,player);
 ((Rva00318D14ByteSlot*)army)->set(1);
 ((LivingWorldPlayer*)player)->AddArmy(army);
 Rva002B3325Summary *summary=(Rva002B3325Summary*)army->m_summary;
 if(summary){
  int count=summary->m_entries.size();
  for(int i=0;i<count;++i){
   Rva0037DCA5 *entry=(Rva0037DCA5*)((Rva0040CB2CIndexedField*)summary)->get(i);
   const ThingTemplateKindOf *thing=(const ThingTemplateKindOf*)entry->rva0037DC52();
   if(thing && thing->isKindOf(90)){
    int key=*(int*)((char*)spawn+0x4c);
    if(((LivingWorldPlayer*)player)->rva002E12F3(key)){
     ((LivingWorldPlayer*)player)->GetRevivalUnitData(*(int*)((char*)spawn+0x4c),(LivingWorldRevivalUnitDataView*)entry);
     ((LivingWorldPlayer*)player)->RemoveRevivalUnit(*(int*)((char*)spawn+0x4c));
    }else{
     key=((LivingWorldPlayer*)player)->rva002E199E(thing);
     if(key){
      ((LivingWorldPlayer*)player)->GetRevivalUnitData(key,(LivingWorldRevivalUnitDataView*)entry);
      ((LivingWorldPlayer*)player)->RemoveRevivalUnit(key);
      *(int*)((char*)entry+0xc0)=key;
     }
    }
   }
  }
 }
 Rva00318C32Ret *region=((Rva00318C79Owner*)army)->rva00318C32();
 if(region){
  if(!((StringBase<char>*)((char*)army+0x18))->isEmpty()){
   Rva003F26AAPair pos;
   ((LivingWorldRegionConnection*)region)->rva003F26AA((const ModuleData*)army,&pos);
   ((Rva00319AA0*)army)->rva00319AA0((const Coord2D*)&pos);
  }else{
   LivingWorldArmy *old=(LivingWorldArmy*)rva002B4948(player,(LivingWorldRegion*)region,(Int)army);
   if(old){
    ((Rva003193EC*)old)->rva00319904((Rva003193EC*)army);
    rva002B5B55(army);army=old;
   }else{
    Rva003F26AAPair pos;
    ((LivingWorldRegionConnection*)region)->rva003F26AA((const ModuleData*)army,&pos);
    ((Rva00319AA0*)army)->rva00319AA0((const Coord2D*)&pos);
   }
  }
 }
 return army;
}
