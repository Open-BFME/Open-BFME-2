// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD
// Retail 0x005DA854..0x005DAA36, 482 bytes, ret 4. WorldBuilder
// 0x015D32A0 names AIUpgradeHeuristicFortress::getUpgradeHeuristicResult
// and asserts its player, AI and structure stats (lines 31..70). The target
// measures scheduling at +8 and the result word at +0xC; enum names remain
// unknown. The AI mode +0x16C must equal 2 before scanning structure IDs.
// Existing target providers supply the filter ABI; the receiver views and
// template flag at +0x120 below expose only the fields retail accesses.
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
#include <string.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Player;
struct Rva002A8AB1Record { char prefix[0x16c]; int mode; };
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); void *rva002A8F24(Player *); };
extern Rva002A8F24 *g_00DFEEF8;
extern int g_Va00DBA4E4;
class Rva005C4AD1LeaField { public: void *get() const; };
struct IdRange { ObjectID *begin,*end; };
struct TemplateView { char prefix[0x120]; unsigned char flag120; };
class Object { public: char prefix[4]; TemplateView *type; char pad8[0x38-8]; Coord3D pos; };
// Template spelling follows the existing KINDOFMASK_NONE owner. Retail
// measures seven words; WorldBuilder uses its different BitFlags<218> layout.
template<int N> class BitFlags { public: unsigned int bits[7]; BitFlags() { memset(bits,0,sizeof(bits)); } void set(unsigned i) { bits[i/32]|=1UL<<(i%32); } };
extern BitFlags<116> KINDOFMASK_NONE;
class BfmeFixedStorage0004543D { char bytes[28]; public: BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &) throw(); };
class Rva00045411BitSet { char bytes[28]; public: Rva00045411BitSet(int,int); };
class Rva000421C8 {
public:
 Rva000421C8():m_next(0) {}
 virtual ~Rva000421C8() {}
 virtual bool allow(Object *)=0;
 virtual int getPlayerMask() { return -1; }
 Rva000421C8 *link(Rva000421C8 *);
 Rva000421C8 *m_next;
};
class PartitionFilterRejectByKindOf:public Rva000421C8 {
 BfmeFixedStorage0004543D a,b;
public:
 PartitionFilterRejectByKindOf(const BfmeFixedStorage0004543D &,const BfmeFixedStorage0004543D &);
 virtual ~PartitionFilterRejectByKindOf() {}
 virtual bool allow(Object *);
};
class Rva003959FA:public Rva000421C8 {
 BfmeFixedStorage0004543D mask;
public:
 Rva003959FA(const BfmeFixedStorage0004543D &);
 virtual ~Rva003959FA() {}
 virtual bool allow(Object *);
};
class Rva00261409Filter:public Rva000421C8 {
public:
 Rva00261409Filter(Player *p,bool match,int flags):m_player(p),m_match(match),m_flags(flags) {}
 virtual ~Rva00261409Filter() {}
 virtual bool allow(Object *);
 virtual int getPlayerMask();
 Player *m_player; bool m_match; int m_flags;
};
class Rva0026119DFilter:public Rva000421C8 {
public:
 virtual ~Rva0026119DFilter() {}
 virtual bool allow(Object *);
};
extern PartitionManager *ThePartitionManager;
extern GameLogic *TheGameLogic;
int GetGameLogicRandomValue(int,int,char *,int);
class AIUpgradeHeuristicFortress {
public:
 int getUpgradeHeuristicResult(Player *);
 char prefix[8]; unsigned int nextFrame; int result;
};
int AIUpgradeHeuristicFortress::getUpgradeHeuristicResult(Player *player)
{
 Rva002A8AB1Record *ai=g_00DFEEF8->rva002A8AB1(player);
 if(ai->mode==2) {
  unsigned int frame=TheGameLogic->getFrame();
  if(nextFrame==-1 || nextFrame<=frame) {
   nextFrame=frame+60*g_Va00DBA4E4;
   void *stats=g_00DFEEF8->rva002A8F24(player);
   Rva005C4AD1LeaField *structures=*(Rva005C4AD1LeaField **)((char *)stats+8);
   IdRange *range=(IdRange *)structures->get();
   ObjectID *it=range->begin;
   ObjectID *end=range->end;
   for(;it!=end;++it) {
    Object *obj=TheGameLogic->findObjectByID(*it);
    if(obj && (obj->type->flag120&4)) {
     BitFlags<116> mask;mask.set(3);mask.set(90);
     // All four filters are full-expression temporaries. Retail resets their
     // base vptrs before querying the returned handle.
     BfmeWideResult near=ThePartitionManager->iterateObjectsInRange(&obj->pos,300.0f,0,
      Rva0026119DFilter().link(&Rva00261409Filter(player,true,4))
       ->link(&Rva003959FA(*(const BfmeFixedStorage0004543D *)&mask))
       ->link(&PartitionFilterRejectByKindOf(*(const BfmeFixedStorage0004543D *)&Rva00045411BitSet(0,7),*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)),0);
     if(near.next()) {
      if(GetGameLogicRandomValue(1,3,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUpgradeHeuristicFortress.cpp",70)==1) result=0;
      break;
     }
    }
   }
  }
 }
 return result;
}
