// ?rva002F14F9@Pathfinder@@QAEPAVObject@@PAV2@0@Z
// ?rva002F14F9@Pathfinder@@QAEPAVObject@@PAV2@0@Z
// ?rva002F14F9@Pathfinder@@QAEPAVObject@@PAV2@0@Z
// ?rva002F14F9@Pathfinder@@QAEPAVObject@@PAV2@0@Z
// cl: /I. /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// wb-lead 2.000 callgraph: Pathfinder::SetBridgeStateRepaired at 0x002E7205.
// Identity evidence: the GeneralsMD AIPathfind.cpp implementation
// Pathfinder::changeBridgeState checks the selected layer, sets its destroyed
// state to the inverse of repaired, then dirties zones with the repaired flag.
// GeneralsMD BridgeBehavior calls that method on bridge damage and repair.
// Target call sites resolve to rowed Rva0036666B at 0x0036666B, unrowed callee
// 0x0036736E and rowed PathfindZoneManager::rva00531481 at 0x00531481. The unrowed
// callee pin is supported by its selected-layer callsite and the GeneralsMD
// PathfindLayer::setDestroyed(Bool) donor. Target arithmetic gives 64-byte
// layers at +0x60 and the final manager-like subobject at +0x460.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
#include <new>
#include "../../Common/GameLogicObjectLookupView.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum
{
 PATHFIND_LAYER_UNKNOWN = 0,
 PATHFIND_LAYER_GROUND = 1
};
typedef int LocomotorSurfaceTypeMask;
class LocomotorSet;
#include "../../../Include/Common/Player.h"
// Relationship order is established by the rowed Object::getRelationship.
class AIUpdateInterface;
struct PathfinderTemplateView
{
public:
	__forceinline bool hasKind(int bit) const
	{
	 return (kinds[bit/8] & (1<<(bit%8)))!=0;
	}
	__forceinline const char *name() const
	{
	 return nameBuffer ? nameBuffer+8 : "";
	}
	__forceinline unsigned testKindWord(unsigned bit)const{return ((const unsigned*)kinds)[bit>>5]&(1U<<(bit&31));}
	char m_pad00[0x64];
	char *nameBuffer; // +0x64
	char m_pad68[0xA0];
	unsigned char kinds[24]; // +0x108
	char m_pad120[0x44C];
	Int priority; // +0x56C
	char m_pad570[0xC4];
	Bool flag; // +0x634
	char m_pad635[0x3];
};
enum Relationship
{
 ENEMIES=0, NEUTRAL=1, ALLIES=2
};
enum ObjectStatusTypes
{
 QuickStatus49=49
};
class Weapon;
enum WeaponSlotType
{
 WEAPONSLOT_PRIMARY=0
};
class Object
{
 public:
 Player *getControllingPlayer() const;
 Object *rva002931F5(bool);
 const Weapon *getCurrentWeapon(WeaponSlotType *) const;
 void *rva0028C1A9() const;
 float rva00263763(const void *) const;
 bool rva0028F518();
 Bool testStatus(ObjectStatusTypes) const;
 Relationship getRelationship(const Object *) const;
 int rva0028B511() const;
 bool rva002E6B89();
 bool IsAtGoalPosition() const;
 bool rva0028AFBB() const;
 float GetGoalAngle() const;
 __forceinline int getID() const
 {
  return *(const int *)((const char *)this+0x74);
 }
 AIUpdateInterface *getAI() const
 {
  return reinterpret_cast<AIUpdateInterface *>(m_258);
 }
 void *m_vtable;
 PathfinderTemplateView *m_template;
 char m_pad08[0x38-8];
 float position[3];
 float m_orientation;
// +0x44
 char m_pad48[0x258 - 0x48];
 char *m_258;
// +0x258 (WorldBuilder +0x260: CanApproachToTarget's gate)
 char m_pad25C[0x274-0x25C];
 Object *container;
};
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/ICoord2DBase.h"
#include "../../Common/Thing/thing.h"
struct Rva002E7ED6Info;
class Pathfinder;
// Native aircraft-path node ABI agrees with the rowed ctor and prepend provider.
#include "../../../Include/GameLogic/PathNode.h"
struct Rva002EDEABArg;
#include "../../../Include/Common/Rva002E93A7Info.h"
#include "../../../Include/GameLogic/Waypoint.h"
class PathfindCell;
class Path
{
 friend class Pathfinder;
 public:
 void prependNode(const Coord3D *,PathfindLayerEnum,Int);
 Path();
///< matched 0x00363DC8
// 0x00364551 / 0x00365E98 (unrowed): Zero Hour's optimize step with a
// BFME facing hint, and a final pass toward a direction (unnamed).
 void rva00364551(Object *obj, LocomotorSurfaceTypeMask surfaces, Bool blocked, const float *facing);
 void rva00365E98(Object *obj, const Coord3D *dir, LocomotorSurfaceTypeMask surfaces, Bool blocked);
 private:
 void *word0;
 PathNode *firstNode;
 Int word8;
 char wordC;
 Bool blockedByAlly;
 char padE[0x28-0xe];
};
#include "../../../Include/Common/Rva002E8C23Pair.h"
int __cdecl Rva002E8C4DCall(int,unsigned char,Rva002E8C23Pair *,int);
bool Rva002EBBFBIsOdd(void *);
struct ICoord2D;
ICoord2D *Rva002E7875WorldToCell(ICoord2D *,bool,const Coord3D *);
extern "C" double __cdecl fabs(double);
struct PathfinderCostCellInfo
{
public:
	int x; // +0x00
	int y; // +0x04
};
struct PathfinderGroundInfo
{
public:
	PathfinderCostCellInfo position; // +0x00
	Int parent; // +0x08
	Waypoint *parentWaypoint; // +0x0C
	unsigned short totalCost; // +0x10
	unsigned short costSoFar; // +0x12
	char m_pad14[0x14];
	Int obstacleID; // +0x28
	unsigned int flags; // +0x2C
};
struct In002E6BA1
{
 Int x,y;
};
class MixFileInfoBuffer;
extern Int TheMixFileInfoPool;
void Rva0052DBCDInit();
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **,Int,In002E6BA1 *);
class Rva002E6C79;
struct Rva002E8BCFSrc;
#include "../../../Include/Common/Rva002E6DC4.h"
void ji_00629952();
struct Rva002F35AFCell;
#include "../../../Include/Common/Rva002E6C79.h"
#include "../../../Include/GameLogic/PathfindCell.h"
// A locomotor's legal surfaces live in its template (+0x04) at +0x14.
#include "../../../Include/GameLogic/LocomotorTemplate.h"
#include "../../../Include/GameLogic/LocomotorClass.h"
// The surfaces each cell type allows, indexed by type (VA 0x00DBD33C,
// defined in Rva002E6DC4Check.cpp).
extern unsigned int g_00DBD33C[16];
extern "C" __declspec(dllimport) double __cdecl floor(double);
float Sin(float x);
float Cos(float x);
// REAL_TO_INT_FLOOR: the IAT floor then an x87 round-to-integer store.
static __forceinline Int realToIntFloor(float f)
{
 float floored = (float)floor((double)f);
 long i;
 __asm
 {
  fld [floored]
  fistp [i]
 }
 return i;
}
struct Rva002E7B29Info;
template<int N> class PathfinderNativeSlots : public PathfinderNativeSlots<N-1>
{
 public: virtual void unusedSlot(PathfinderNativeSlots<N> *);
};
template<> class PathfinderNativeSlots<0>
{
};
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
// The per-object radius/centre split (rowed 0x002EBCA7).
void Rva002EBCA7Split(void *obj, Int *radius, unsigned char *center);
struct Rva002F600CInfo;
// Coord3D::set(const Coord3D *) as Zero Hour's header defines it inline.
static __forceinline void zeroCoord3D(Coord3D *dst)
{
 dst->x = 0.0f;
 dst->y = 0.0f;
 dst->z = 0.0f;
}
static __forceinline void copyCoord3D(Coord3D *dst, const Coord3D *src)
{
 dst->x = src->x;
 dst->y = src->y;
 dst->z = src->z;
}
// Pathfinder_FuncTightenPath (0x34 bytes): WorldBuilder's functor for
// TightenPath's line walk, Zero Hour's TightenPathStruct plus the goal.
class Pathfinder_FuncTightenPath
{
 public:
 Pathfinder_FuncTightenPath(Pathfinder *pathfinder, Object *obj,
 const LocomotorSet &locomotorSet, PathfindLayerEnum layer,
 const Coord3D &goal);
 Pathfinder *m_pathfinder;
// +0x00
 Object *m_obj;
// +0x04
 const LocomotorSet *m_locomotorSet;
// +0x08
 Int m_radius;
// +0x0C
 unsigned char m_center;
// +0x10
 PathfindLayerEnum m_layer;
// +0x14
 Bool m_foundDest;
// +0x18
 Coord3D m_goal;
// +0x1C
 Coord3D m_destPos;
// +0x28
};
// Pathfinder_IsCheckForAdjust (0x3C bytes): WorldBuilder's functor for the
// destination-adjust check; Zero Hour's checkForAdjust info plus the goal,
// an optional second position whose layer wins, a float and a word.
class Pathfinder_IsCheckForAdjust
{
 public:
 Pathfinder_IsCheckForAdjust(Pathfinder *pathfinder, Object *obj,
 void *arg, const Coord3D &goal, const Coord3D *layerPos, float range,
 Int arg6);
 Pathfinder *m_pathfinder;
// +0x00
 Object *m_obj;
// +0x04
 void *m_08;
// +0x08
 Bool m_isHuman;
// +0x0C
 unsigned char m_center;
// +0x0D
 Int m_radius;
// +0x10
 const Coord3D *m_layerPos;
// +0x14
 PathfindLayerEnum m_layer;
// +0x18
 float m_range;
// +0x1C
 Rva002E8C23Pair fallback;
 Int m_28;
// +0x28
 Int m_2C;
// +0x2C
 Coord3D m_goal;
// +0x30
};
// Pathfinder_IsCheckForMeleeHordeAdjust (0x34 bytes): WorldBuilder's functor
// for the melee/horde destination check; Zero Hour's checkForAdjust info
// (isHuman, radius/centre, layer) plus a float and the goal.
class Pathfinder_IsCheckForMeleeHordeAdjust
{
 public:
 Pathfinder_IsCheckForMeleeHordeAdjust(Pathfinder *pathfinder, Object *obj,
 void *arg, const Coord3D &goal, float range);
 Pathfinder *m_pathfinder;
// +0x00
 Object *m_obj;
// +0x04
 void *m_08;
// +0x08
 Bool m_isHuman;
// +0x0C
 unsigned char m_center;
// +0x0D
 Int m_radius;
// +0x10
 PathfindLayerEnum m_layer;
// +0x14
 float m_range;
// +0x18
 char m_pad1C[0x24 - 0x1C];
 Int m_24;
// +0x24
 Coord3D m_goal;
// +0x28
};
// The rowed cell-centre helper 0x002EBC59 (returns its out Coord3D) and the
// pinned 0x002CB35C range probe (WorldBuilder: Weapon::isWithinAttackRange).
void *rva002EBC59(void *out, void *obj, Int a2, Int a3, Int a4);
class Rva002CB35CObj
{
public:
	bool rva002CB35C(int p1, void *p2, void *p3, void *p4, float p5, int p6);
};
// CanApproachToTarget's helpers. The rowed 0x002C9B80 range query returns a
// float; its +0x04 member answers the rowed byte getter 0x002C9400.
class Rva002C9400ByteField
{
 public:
 unsigned char get() const;
};
class Rva002C9B80Owner
{
 public:
 float rva002C9B80(void *a, float b);
 void *m_00;
 Rva002C9400ByteField *m_04;
// +0x04
};
// The 0x24-byte cell-query functor (rowed constructor 0x002E9ACC); the line
// walk 0x002F6C22 calls its 0x002F4D8B callback, which sets +0x1C on a hit.
struct Rva002E8BCFSrc;
struct Rva002F4D8BInfo;
class Rva002E9ACC
{
 public:
 Rva002E9ACC(void *a1, Object *obj, Rva002E8BCFSrc const *src,
 unsigned char a4, unsigned char a5);
 char m_pad00[0x1C];
 Bool m_found;
// +0x1C
 unsigned char m_1D;
// +0x1D
 unsigned char m_1E;
// +0x1E
 unsigned char m_1F;
// +0x1F
 unsigned char m_20;
// +0x20
};
// A hierarchical path node list (rowed 0x002E6C79 gives the next node) whose
// +0 points at a cell record: x, y, and at +0x0C a zone record whose +0x04
// is kept.
#include "../../../Include/Common/Rva002F35AFZone.h"
#include "../../../Include/Common/Rva002F35AFCell.h"
struct Rva002E8C23Param;
Int Rva002E8C23Call(Int,unsigned char,Rva002E8C23Param *);
// The 12-byte record +0x1C1CC collects per hop (zone, next cell x/y).
#include "../../../Include/Common/Rva002F35AFHop.h"
// The 0x14-byte hierarchical path (rowed constructor 0x005348AD); 0x00534557
// adds a cell and 0x00534AAE finishes it (WorldBuilder: computeOrderMap).
class Rva005348AD
{
 public:
 Rva005348AD();
 void rva00534557(Rva002F35AFCell *cell);
 void rva00534AAE();
 private:
 char m_pad[0x14];
};
#include "../../../Include/Common/Rva0036666B.h"
struct IRegion2D;
class Xfer;
#include "../../../Include/GameLogic/PathfindLayer.h"
#include "../../../Include/GameLogic/PathfindZoneManager.h"
#include "../../../Include/Common/Rva002EBC7FPair.h"
void *rva002EBC7F(void *,void *,Rva002EBC7FPair *,int);
#include <math.h>
#include "../../../Include/GameLogic/Module/Rva001E46E1.h"
#include "../../../Include/GameLogic/Module/AIUpdate.h"
// Native 0x002EC0A2 reads Object nodes at cell-info +0x14, +0x20 and +0x24.
// The list-role labels below describe the three observed conflict passes;
// their original member spellings are not established. Nodes link at +0 and
// carry Object* at +8; native Object position/AI/container are +0x38/+0x258/+0x274.
struct PathCollisionNode
{
 PathCollisionNode *next;
 void *word4;
 Object *object;
};
struct PathCollisionInfo
{
 int x,y;
 char gap08[0x14-8];
 PathCollisionNode *occupants;
 PathCollisionNode *hordeGoalNodes;
// Native/WB horde query list at+18.
 char gap1C[4];
 PathCollisionNode *goals;
 PathCollisionNode *reservations;
 ObjectID fallbackID;
// Native/WB fallback lookup when +20 list is empty.
};
struct PathCollisionCell
{
 PathCollisionInfo *info;
};
// Native bridge list links at +4; height and containment use existing
// independently admitted Bridge providers from the terrain-logic family.
#include "../../../Include/GameLogic/BridgeClass.h"
struct Rva002ED236Pos
{
 float x, y, z;
 Rva002ED236Pos(const Coord3D &c)
 {
  x = c.x;
  y = c.y;
  z = c.z;
 }
 ~Rva002ED236Pos()
 {
 }
};
int Rva002E6E8AGet(int layer);
#include "ascii_string.h"
class Rva002E9D09
{
public:
	int rva002E9D09(Object *a1, int a2, int a3);
private:
	Rva002E6DC4 *m_check0; // +0x00
	Object *m_holder4; // +0x04
	int *m_counter8; // +0x08
	bool m_cC; // +0x0C
	char m_pad0D[0x3];
	int m_10; // +0x10
	bool m_14; // +0x14
	char m_pad15[0x3];
	Rva002E8BCFSrc *m_18; // +0x18
};
class Rva002E7C99
{
public:
	void *rva002E7C99(int a, int b, int c, unsigned char d, int e, unsigned char f, int g);
private:
	int m_00; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	unsigned char m_0C; // +0x0C
	unsigned char m_0D[3]; // +0x0D
	int m_10; // +0x10
	unsigned char m_14; // +0x14
	unsigned char m_15[3]; // +0x15
	int m_18; // +0x18
};
void rva002E79A8(int,unsigned char,int,int,int);
// Native 0x002F01B6 addresses this 12-byte floating scratch first. Later
// 0x002F0369 stores integer position at scratch+4 and diameter at scratch+12.
// The two phases do not overlap; this local union preserves that 20-byte reuse.
union PathfinderCheckCoordinates
{
 Coord3D point;
 struct IntegerLayout
 {
  int reserved;
  ICoord2DBase position,size;
 }
 cells;
};
struct PathfinderLogFile;
extern "C" int __cdecl fprintf(PathfinderLogFile *,const char *,...);
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
#include "../../../Include/GameLogic/Rva002F336AOwner.h"
struct PathfinderOpenQueue
{
 PathfindCell **first,**last;
 Bool empty()const
 {
  return first==last;
 }
 PathfindCell *front()const
 {
  return *first;
 }
};
struct ICoord2D;
struct Rva002E7261Info;
#include "../../../Include/GameLogic/AIPathfind.h"
// The 0x002E8045 walk calls this ABI view. The callback at 0x002E7261
// writes its result key at +8 and cell coordinates at +0xC/+0x10.
struct Rva002E7261Info
{
 Pathfinder *m_pathfinder;
 Int m_arg;
 Int m_key;
 ICoord2D m_position;
 Int cellCallback(PathfindCell *, PathfindCell *, Int, Int);
};
class PathfinderOverlapTerrainView:public PathfinderNativeSlots<44>
{
 public: virtual bool objectInteractsWithBridgeLayer(Object *,int);
};
int isGroundOrBridgeLayer(int);
extern int g_Va00DFECD0;
extern GameLogic *TheGameLogic;
int Rva002E9B31Get(void *);
// Keep the canonical helpers visible for caller codegen, with foldable
// out-of-line copies. Their complete retail bodies are 162, 32 and 32 bytes.
inline __declspec(noinline) ICoord2D* __cdecl Rva002E7875WorldToCell(ICoord2D* out, bool center, const Coord3D* pos)
{
 int ix;
 int iy;
 if (center)
 {
  ix = realToIntFloor(pos->x * 0.1f);
  iy = realToIntFloor(pos->y * 0.1f);
 }
 else
 {
  ix = realToIntFloor(pos->x * 0.1f + 0.5f);
  iy = realToIntFloor(pos->y * 0.1f + 0.5f);
 }
 out->x = ix;
 out->y = iy;
 return out;
}
inline __declspec(noinline) struct ICoord2D *__cdecl Rva002EBC14Cell(struct ICoord2D *out, void *p, const struct Coord3D *pos)
{
 Rva002E7875WorldToCell(out, Rva002EBBFBIsOdd(p), pos);
 return out;
}
inline __declspec(noinline) void __cdecl Rva002EBCD6Split(void *p, int *outHalf, int *outRest)
{
 int v = Rva002E9B31Get(p);
 int h = v / 2;
 *outHalf = h;
 *outRest = v - h;
}
#include "../../../Include/GameLogic/Weapon.h"
class PathfinderAttackContainView:public PathfinderNativeSlots<6>
{
 public:virtual int slot18();
};
// Native2F14F9..2F18D4 RET8. WB D3BD40 is the same perimeter/range scan,
// original method name unresolved. Owned adjacent-unit query proves the
// shared layer/footprint/stamp views; each additional filter follows retail.
Object *Pathfinder::rva002F14F9(Object *obj,Object *target)
{
 if(target)
 {
  Object *container=target->rva002931F5(false);
  if(container)target=container;
 }
 ICoord2D cell;
 int extent;
 Rva002EBC14Cell(&cell,obj,(const Coord3D *)obj->position);
 {
  int above;
  Rva002EBCD6Split(obj,&extent,(obj ? &above : &above));
  cell.x-=extent;
  cell.y-=extent;
  extent+=above;
 }
 int layers[2];
 layers[0]=obj->rva0028B511();
 int layerCount=1;
 if(!(unsigned char)isGroundOrBridgeLayer(layers[0]) && reinterpret_cast<PathfinderOverlapTerrainView *>(TheTerrainLogic)->objectInteractsWithBridgeLayer(obj,layers[0]))
 {
  layers[1]=1;
  layerCount=2;
 }
 ++g_Va00DFECD0;
 const Weapon *weapon=obj->getCurrentWeapon(0);
 if(!weapon || !((const Rva002C9400ByteField *)weapon->m_template)->get())return 0;
 int relatedID=0;
 bool status65=obj->testStatus((ObjectStatusTypes)65);
 if(obj ? status65 : status65)
 {
  void *contain=obj->rva002931F5(false)->rva0028C1A9();
  if(contain)relatedID=((PathfinderAttackContainView *)contain)->slot18();
 }
 float attackRange=weapon->getAttackRange(obj);
 float scaledRange=attackRange*0.1f;
 int range = realToIntFloor(scaledRange+0.1f);
 _ReadWriteBarrier();
 Object *best=0;
 float bestDistance=1e10f;
 while (range-- >= 0)
 {
  for(int i=extent;i>=0;--i)
  {
   for(int side=0;side<4;++side)
   {
    int x,y;
    switch(side)
    {
     case 0:x=cell.x+i;
     y=cell.y-1;
     break;
     case 1:x=cell.x+extent;
     y=cell.y+i;
     break;
     case 2:x=cell.x+extent-i-1;
     y=cell.y+extent;
     break;
     case 3:x=cell.x-1;
     y=cell.y+extent-i-1;
     break;
    }
    for(int k=0;k<layerCount;++k)
    {
     PathCollisionCell *pathCollisionCell=(PathCollisionCell *)getCell((PathfindLayerEnum)layers[k],x,y);
     if(pathCollisionCell && pathCollisionCell->info)
     {
      if(pathCollisionCell->info->fallbackID)
      {
       Object *candidate=TheGameLogic->findObjectByID(pathCollisionCell->info->fallbackID);
       if(candidate)
       {
        Relationship relation=obj->getRelationship(candidate);
        if(!candidate->rva002E6B89() && !(*(const unsigned char *)((const char *)candidate+0x438)&1)
        && (relation==ENEMIES || (candidate->m_template->hasKind(50) && relation==NEUTRAL))
        && (!target || candidate==target)
        && (candidate==target || !candidate->m_template->hasKind(130))
        && weapon->isWithinAttackRange((const Object *)obj,(const Object *)candidate,0.0f,1))
        {
         float distance=obj->rva00263763(candidate);
         if(distance<bestDistance)
         {
          bestDistance=distance;
          best=candidate;
         }
        }
       }
      }
      for(PathCollisionNode *node=pathCollisionCell->info->goals;node;node=node->next)
      {
       if(node->object->rva002E6B89())continue;
       Object *candidate=node->object;
       if((*(const unsigned char *)((const char *)candidate+0x438)&1) || candidate->rva0028F518())continue;
       if(candidate->testStatus((ObjectStatusTypes)15) && !candidate->testStatus((ObjectStatusTypes)17))continue;
       if(fabs(candidate->position[2]-obj->position[2])>10.0f)continue;
       Relationship relation=obj->getRelationship(candidate);
       if(relatedID!=candidate->getID() && relatedID!=*(const int *)((const char *)candidate+0x78))
       {
        if(relation==ALLIES)continue;
        if(!candidate->m_template->hasKind(50) && relation==NEUTRAL)continue;
       }
       if(target && candidate!=target && candidate->container!=target)continue;
       if(weapon->isWithinAttackRange((const Object *)obj,(const Object *)candidate,0.0f,1))
       {
        float distance=obj->rva00263763(candidate);
        if(distance<bestDistance)
        {
         bestDistance=distance;
         best=candidate;
        }
       }
      }
     }
    }
   }
  }
  extent += 2;
  --cell.x;
  --cell.y;
 }
 return best;
}
