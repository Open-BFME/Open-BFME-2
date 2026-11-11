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
#include "../../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
extern int BfmeLogicFramesPerSecond;
#include "../../../../Include/Common/Rva005C4AD1LeaField.h"
struct IdRange { ObjectID *begin,*end; };
struct TemplateView { char prefix[0x120]; unsigned char flag120; };
class Object { public: char prefix[4]; TemplateView *type; char pad8[0x38-8]; Coord3D pos; };
// Template spelling follows the existing KINDOFMASK_NONE owner. Retail
// measures seven words; WorldBuilder uses its different BitFlags<218> layout.
// LINK: the default ctor's COMDAT loses to the first-in-order copy, so the one
// local mask uses a TU-unique no-init ctor plus the same zeroing stores. No flags touched.
template<int N> class BitFlags { public: unsigned int bits[7]; struct BfmeNoInitFortress {}; BitFlags() { memset(bits,0,sizeof(bits)); } BitFlags(BfmeNoInitFortress) {} void bfmeZeroFortress() { memset(bits,0,sizeof(bits)); } void set(unsigned i) { bits[i/32]|=1UL<<(i%32); } };
extern BitFlags<116> KINDOFMASK_NONE;
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"
#include "../../../../Include/GameLogic/Module/Rva00045411BitSet.h"
#include "../../../../Include/GameLogic/PartitionFilter.h"
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
#include "../../../../Include/GameLogic/Rva00261409Filter.h"
#include "../../../../Include/GameLogic/Rva0026119DFilter.h"
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
 Rva002A8AB1Record *ai=TheSkirmishAIManager->rva002A8AB1(player);
 if(ai->mode==2) {
  unsigned int frame=TheGameLogic->getFrame();
  if(nextFrame==-1 || nextFrame<=frame) {
   nextFrame=frame+60*BfmeLogicFramesPerSecond;
   void *stats=TheSkirmishAIManager->rva002A8F24(player);
   Rva005C4AD1LeaField *structures=*(Rva005C4AD1LeaField **)((char *)stats+8);
   IdRange *range=(IdRange *)structures->get();
   ObjectID *it=range->begin;
   ObjectID *end=range->end;
   for(;it!=end;++it) {
    Object *obj=TheGameLogic->findObjectByID(*it);
    if(obj && (obj->type->flag120&4)) {
     BitFlags<116> mask((BitFlags<116>::BfmeNoInitFortress()));mask.bfmeZeroFortress();mask.set(3);mask.set(90);
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
