// LivingWorldScoreKeeper: existing matched complete declaration extracted verbatim.
// ABI proof: reverse/attempt_support/livingworldscorekeeper-qc12-20261031/.
#ifndef BFME_LIVING_WORLD_SCORE_KEEPER_H
#define BFME_LIVING_WORLD_SCORE_KEEPER_H
#if defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#error LivingWorldScoreKeeper requires Snapshot name slot before first inclusion
#endif
#if defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT) || defined(BFME_SNAPSHOT_REFERENCE_XFER) || defined(BFME_SNAPSHOT_CONSTRUCTOR_ONLY)
#error LivingWorldScoreKeeper requires the complete native Snapshot profile
#endif
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include <vector>
#include <map>
class Rva004E06FBPtrChase32Field;
 class LivingWorldBattle;
 struct Rva004EF2ABArg;
 class LivingWorldLogic;
 class CountInputPrefix;
 class ScoreKeeper;
class LivingWorldPhaseObserver {public: ~LivingWorldPhaseObserver(){} virtual void event0_0(int,int){} virtual void event0_1(int,int){} };
#include "LivingWorldObservers.h"
class LivingWorldAutoResolveEventObserver {public: ~LivingWorldAutoResolveEventObserver(){} virtual void event2_0(int,int,int){} virtual void event2_1(int,int,int){} virtual void OnLivingWorldAutoResolveBattleCompleted(int,LivingWorldBattle*,void*){} };
class LivingWorldRTSEventObserver {public: ~LivingWorldRTSEventObserver(){} virtual void event3_0(int,int){} virtual void event3_1(int,LivingWorldBattle*){} };
#include "LivingWorldLogicObserver.h"
class LivingWorldBuildingNuggetSpawnArmyObserver {public: ~LivingWorldBuildingNuggetSpawnArmyObserver(){} virtual void event7_0(int){} virtual void event7_1(int,int){} virtual void event7_2(int,int){} virtual void event7_3(CountInputPrefix*,void*){} };
class LivingWorldPlayer;
struct Rva004EE501 : public _STL::_Vector_base<int, _STL::allocator<int> >
{
	__forceinline Rva004EE501() : _STL::_Vector_base<int, _STL::allocator<int> >(_STL::allocator<int>()) {}
	~Rva004EE501();
};
typedef _STL::map<int,void*> ScoreMapCtor;
typedef _STL::pair<const unsigned,void*> ScoreMapPair;
typedef _STL::_Rb_tree<unsigned,ScoreMapPair,_STL::_Select1st<ScoreMapPair>,_STL::less<unsigned>,_STL::allocator<ScoreMapPair> > ScoreMapDtor;
namespace _STL {template<> map<int,void*>::map();}
struct ScoreMapStorage {
 __forceinline ScoreMapStorage(){((ScoreMapCtor*)this)->ScoreMapCtor::map();}
 __forceinline ~ScoreMapStorage(){((ScoreMapDtor*)this)->ScoreMapDtor::~ScoreMapDtor();}
 char bytes[12];
};
class LivingWorldScoreKeeper : public Snapshot,
	public LivingWorldPhaseObserver,
	public LivingWorldBuildingObserver,
	public LivingWorldAutoResolveEventObserver,
	public LivingWorldRTSEventObserver,
	public LivingWorldRegionObserver,
	public LivingWorldPlayerObserver,
	public LivingWorldLogicObserver,
	public LivingWorldBuildingNuggetSpawnArmyObserver
{
public:
    class PerTurnStats;
	LivingWorldScoreKeeper(int playerIndex, LivingWorldPlayer *player);
	virtual ~LivingWorldScoreKeeper();
	void rva004EE5D2();
	void rva004EE78A();
	void rva004EE950(ScoreKeeper *rtsScoreKeeper);
	void collectEndOfTurnStats(int turn);
 virtual void event0_1(int,int);
virtual void event1_0(Rva004E06FBPtrChase32Field*);virtual void event1_3(const Rva004E06FBPtrChase32Field*,int);
virtual void OnLivingWorldAutoResolveBattleCompleted(int,LivingWorldBattle*,void*);virtual void event3_0(int,int);virtual void event3_1(int,LivingWorldBattle*);
virtual void event4_0(int,int,int);virtual void event5_0(Rva004EF2ABArg*);virtual void event6_1(LivingWorldLogic*);virtual void event7_3(CountInputPrefix*,void*);
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	LivingWorldPlayer *m_player;		// +0x24
	Rva004EE501 m_28;
	_STL::vector<int> m_34, m_40, m_4C;
	_STL::vector<bool> m_58;
	int m_6C;
	long m_startTime;			// +0x70
	int m_74, m_78, m_7C;
	int m_80[5];
	int m_94, m_98;
	ScoreMapStorage m_9C;
	int m_A8, m_AC, m_B0;
	ScoreMapStorage m_B4, m_C0, m_CC;
	int m_D8, m_DC, m_E0, m_E4, m_E8, m_EC, m_F0;
	int m_playerIndex;			// +0xF4
	bool m_F8;
};

#endif
