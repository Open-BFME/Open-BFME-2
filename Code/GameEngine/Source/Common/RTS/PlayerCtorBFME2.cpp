// cl: /I. /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Player constructor semantic donor: BF1 f98983a7d Player.cpp399-459 and
// ZH Player.cpp303-362. Target init2AF729 establishes field meanings;
// native2B0F3C establishes initialization order and three base views.
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <hash_map>
#include <list>
#include <vector>
#define BFME_SNAPSHOT_NAME_SLOT
#include "reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
class Player;
class PlayerTemplate;
class Rva002B0F3CIface {
public:
 Rva002B0F3CIface() {} ~Rva002B0F3CIface() {}
 virtual void v0()=0; virtual void v1()=0; virtual void v2()=0;
};
class ExperienceScalarTable;
class Rva00380200 {
public:
 Rva00380200(); virtual ~Rva00380200() {}
 virtual bool rva0038037C(int); virtual void slot2();
 virtual void resetRank(); virtual void onRank(void*); virtual bool isReady();
private:
 AsciiString *m_ptr; ExperienceScalarTable *m_scalars;
 float m_0C,m_10; int m_14,m_18,m_1C,m_20,m_24,m_28;
};
class Rva003B0E83 {public:Rva003B0E83*rva003B0E83();};
struct HandicapView {float values[4];HandicapView(){((Rva003B0E83*)this)->rva003B0E83();}};
class Rva002AE5EB {
public: Rva002AE5EB() throw(); virtual ~Rva002AE5EB();
private: int words[10]; bool flag;
};
class S3Money : public Snapshot {
public:
 S3Money():money(0),owner(0){} virtual ~S3Money() {}
 virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 int money,owner;
};
class Rva001EAE6FHelper {public:Rva001EAE6FHelper*clear80() throw();};
struct Rva002B0F3CUpgradeMask {unsigned words[32];Rva002B0F3CUpgradeMask() throw(){((Rva001EAE6FHelper*)this)->clear80();}};
// Scope the target 16-byte energy member: the older EnergyConstructorThunk
// emits a different 20-byte ABI at808880 and cannot provide this member.
class Rva002B0F3CEnergy : public Snapshot {
public:
 Rva002B0F3CEnergy():production(0),consumption(0),owner(0){} virtual ~Rva002B0F3CEnergy() {}
 virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 int production,consumption;Player*owner;
};
class Rva004F599E : public Snapshot {public:Rva004F599E();virtual ~Rva004F599E();virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);int words[42];};
struct Rva001FEAB2Element {char bytes[1];};
struct Rva002AF625Element {char bytes[8];Rva002AF625Element();Rva002AF625Element(const Rva002AF625Element&);~Rva002AF625Element(){} };
class Rva002AC340 {public:Rva002AC340() throw();~Rva002AC340();private: unsigned words[5];};
class Rva002AC026Member {
public:
 void*head;void*init(void*);
 Rva002AC026Member(const _STL::allocator<int>&a){init((void*)&a);}
 ~Rva002AC026Member();
};
class Rva0029FB3BMember {
public:
 void*head;void*init(void*);
 Rva0029FB3BMember(const _STL::allocator<int>&a){init((void*)&a);}
 ~Rva0029FB3BMember();
};
class ScoreKeeper {public:ScoreKeeper();virtual ~ScoreKeeper();private:unsigned words[0x330/4];};
struct ReadyTimer {int power,ready;};
struct ProductionCostModifier;
class UnitRevivalTracker {public:UnitRevivalTracker(Player*);virtual ~UnitRevivalTracker();private:unsigned words[4];};
class Squad;
class Player : public Snapshot, public Rva002B0F3CIface, public Rva00380200 {
public:
 Player(int);virtual ~Player();
 virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 virtual void v0();virtual void v1();virtual void v2();
 virtual bool rva0038037C(int);virtual void slot2();virtual void resetRank();virtual void onRank(void*);virtual bool isReady();
 void init(const PlayerTemplate*);
 const PlayerTemplate*tmplate;UnicodeString displayName;HandicapView handicap;
 AsciiString name;int nameKey,index;AsciiString side;int type;
 Rva002AE5EB r60;S3Money money;void*upgradeList;
 int radar,disableRadar;bool radarDisabled;char gapA9[3];int bombard,hold,search;void*battle;
 Rva002B0F3CUpgradeMask inProgress,completed;Rva002B0F3CEnergy energy;Rva004F599E stats;
 void*buildList;int unknown27C;unsigned color,nightColor;
 _STL::map<int,void*>cost;
 _STL::hash_map<int,Rva001FEAB2Element>time,scratchTime;
 _STL::hash_map<int,Rva002AF625Element>timeCounts;
 _STL::map<int,void*>veterancy;
 void*ai,*defaultTeam,*resources,*tunnel;int unknown2EC;
 _STL::vector<unsigned>sciences,disabled,hidden;float bounty;
 Rva002AC340 r318;
 Rva002AC026Member prototypes;void*playerRelations,*teamRelations;
 bool canBuildBase,canBuildUnits,observer,flag33B,listInScoreScreen,unitsHunt,flag33E,flag33F;
 bool attackedBy[20];int attackedFrame;unsigned attackFrames[20];int unknown3A8,unknown3AC;
 _STL::vector<unsigned>v3B0;
 ScoreKeeper score;int unknown6F0;
 _STL::list<ProductionCostModifier*>modifiers;float unknown6F8;int unknown6FC;
 _STL::list<int>unknown700;
 _STL::list<ReadyTimer>timers;
 Squad*squads[10];Squad*selection;bool dead,flag735;char gap736[2];
 UnitRevivalTracker revival;AsciiString text74C;void*unknown750;
 Rva0029FB3BMember r754;
};
typedef char PlayerCtorSizeCheck[sizeof(Player)==0x758?1:-1];
Player::Player(int playerIndex):
 index(playerIndex),upgradeList(0),battle(0),buildList(0),ai(0),resources(0),tunnel(0),
 prototypes(_STL::allocator<int>()),playerRelations(0),teamRelations(0),flag33F(false),unknown3AC(-1),
 selection(0),revival(this),unknown750(0),r754(_STL::allocator<int>())
{
 for(int i=0;i<10;++i)squads[i]=0;
 init(0);
}
