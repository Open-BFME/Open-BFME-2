// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /I.
// stlport
//
// ?exitObjectInAHurry@OpenContain@@UAEXPAVObject@@@Z, retail 0x004656DF..0x00465972
// (659 bytes, EH, RET 4).
//
// Provenance: the Zero Hour OpenContain::exitObjectInAHurry (GeneralsMD
// GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp) supplies the
// purpose and statement order. The ZH layout in OpenContain.cpp does not fit
// BFME2: retail's ExitInterface subobject sits at +0x30 (module data at
// [this-0x2C], owner at [this-0x28], removeFromContain slot 41 on the contain
// interface at [this-0x10]), so this unit spells only what the body reads.
// Target facts from the body:
// - door: the open-time (module data +0x78) is stored into the countdown at
//   +0x70 and, when nonzero, the inline condition swap (clear bit 22, set
//   bit 21 at owner +0x10C) calls the rowed notifier 0x0028AE6D;
// - exit paths (module data +0x74), the "ExitStart"/"ExitEnd" bone names,
//   the exit-path cycle at +0x6C and the rally point at +0xD0/+0xDC;
// - BFME2 replaces ZH's vehicle pathfind refresh with the rowed owner
//   helpers 0x0028AD7C / 0x0028ACDC, writes the ignore-collision frame at AI
//   +0x178 directly, and ends with 0x0028ACDC on the exiting object instead of
//   Pathfinder::updateGoal.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
// /D_CRTIMP= keeps free a direct call; itoa stays an import-slot call.
extern "C" char *(__cdecl *_imp___itoa)(int,char*,int);
enum PathfindLayerEnum {LAYER_GROUND=0};
enum ExitDoorType {DOOR_1=0};
enum CommandSourceType {CMD_FROM_AI=2};
double Rva000422A0Atan2(float,float);
extern bool BfmeAIExitDoorFlag;
// Retail 0x00DC97E4: a writable .data float (50.0) read only by exitObjectViaDoor, for the
// arrival test and the scale (WorldBuilder passes it to MathCoord3D::operator*= by value).
// Descriptive identifier; the original name is unknown.
float BfmeOpenContainExitDistance=50.0f;
class Rva0035149F;
class Matrix3D;
class LocomotorSet;
class ConditionBits {
public:
 unsigned int test(int bit) const{return words[bit>>5]&(1U<<(bit&0x1f));}
 void set(int bit){words[bit>>5]|=1U<<(bit&0x1f);}
 void clear(int bit){words[bit>>5]&=~(1U<<(bit&0x1f));}
 unsigned int words[4];
};
class Thing {public:void setPosition(const Coord3D*);void setOrientation(float);};
class AIUpdateInterface;
class Object:public Thing {
public:
 void rva0028AE6D();
 bool getSingleLogicalBonePosition(const char*,Coord3D*,Matrix3D*) const;
 int rva0028B511() const;
 void setLayer(PathfindLayerEnum);
 void rva0028AD7C();
 void rva0028ACDC(int);
 bool rva002931BA();
 const Coord3D *getPosition() const{return &position;}
 void *vtable;unsigned char *thingTemplate;char pad8[0x38-8];Coord3D position;float orientation;
 char pad48[0x10c-0x48];ConditionBits conditionBits;char pad11c[0x258-0x11c];AIUpdateInterface *ai;
};
template<class Tag,int N>class Slots:public Slots<Tag,N-1>{public:virtual void gap(Tag*,char(*)[N]);};template<class Tag>class Slots<Tag,1>{public:virtual void gap(Tag*,char(*)[1]);};
void Rva00030830GameFree(void*);
void Rva00030830FreeAllocation(void*);
struct BfmeE12 {float x,y,z;};
class Rva000E016A {public:BfmeE12 *rva000E016A(unsigned,Coord3D*,Coord3D*);};
namespace _STL {
template <class I,class O> O __copy_ptrs(I,I,O,const __false_type&);
// Visible and called out of line as retail's 0x002CA82C, so the caller's vector does not escape.
// Member-wise, as retail's copy: a struct copy would compile to movsd here.
template <> inline __declspec(noinline)
void _Construct<Coord3D, Coord3D>(Coord3D *__p, const Coord3D &__val)
{
    if (__p)
    {
        __p->x = __val.x;
        __p->y = __val.y;
        __p->z = __val.z;
    }
}
// No __uninitialized_copy declaration: with the generic body visible, _M_insert_overflow
// (0x002CDF8A) leaves its __false_type tags uninitialized as retail does.
}
class Rva0035149F {public:BfmeE12 *start,*finish,*end;Rva0035149F &rva0035149F(const Rva0035149F&);};
enum AICommandType {AICMD_PATH=9,AICMD_PATH_ANGLE=0x25};
struct AICommandParms {
 AICommandParms(AICommandType,CommandSourceType);
 ~AICommandParms(){if(coords.start)free(coords.start);}
 int cmd,source;Coord3D pos;Object *target;char pad18[8];Rva0035149F coords;char pad2c[0xc0-0x2c];
};
class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *, CommandSourceType);
	void rva0036EE16(const Rva0035149F*,Object*,CommandSourceType);
	void rva0036EF09(const Rva0035149F*,Object*,float,CommandSourceType);
	virtual void aiDoCommand(const AICommandParms*);
};
struct AIGoalView {char pad[0x24];Coord3D goal;};
class AIUpdateInterface:public Slots<AIUpdateInterface,110>{
public:
 virtual bool isIdle() const;
 virtual void slot111();virtual void slot112();virtual void slot113();virtual void slot114();
 virtual void slot115();virtual void slot116();
 virtual void doQuickExit(const _STL::vector<Coord3D>*);
 void ignoreObstacle(const Object*);
 char pad4[0x20-4];AICommandInterface commands;char pad24[0x30-0x24];AIGoalView *goalView;char pad34[0x148-0x34];Coord3D position148;char pad154[0x178-0x154];unsigned int ignoreCollisionUntil;char pad17c[0x1cc-0x17c];
 LocomotorSet &locomotorSet(){return *(LocomotorSet*)((char*)this+0x1cc);}
};
#include "../../../../Include/GameLogic/AIPathfind.h"
#include "../../../../Include/GameLogic/AI.h"
extern GameLogic *TheGameLogic;
extern int BfmeLogicFramesPerSecond;
#include "../../../../Include/GameLogic/Module/OpenContainModuleData.h"
class OpenContainModule:public Slots<OpenContainModule,1>{public:OpenContainModuleData *moduleData;Object *owner;Object *getObject() const{return owner;}const OpenContainModuleData *getOpenContainModuleData() const{return moduleData;}char padC[0x20-0xc];};
class ContainModuleInterface:public Slots<ContainModuleInterface,41>{public:virtual void removeFromContain(Object*,bool);char pad4[0x10-4];};
#include "../../../../Include/GameLogic/Module/ExitInterface.h"
class OpenContain:public OpenContainModule,public ContainModuleInterface,public ExitInterface{
public:
 virtual void removeFromContain(Object*,bool);
 virtual void exitObjectViaDoor(Object*,ExitDoorType);
 virtual void exitObjectInAHurry(Object*);
 char pad34[0x6c-0x34];int whichExitPath;unsigned int doorCloseCountdown;
 char pad74[0xd0-0x74];Coord3D rallyPoint;bool rallyPointExists;
};
static __forceinline void concatChar(AsciiString &asciiString,char c)
{
 ((StringBase<char>*)&asciiString)->concat(&c,1);
}
// ?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z, retail 0x0046525F..0x004656DF
// (1152 bytes, EH, RET 8). BFME2 adds the arrival branch for owners without exit paths; the
// WorldBuilder twin (wb 0x1196CE0) gives its statements: startPosition from the owner's position
// snapped by getClosestPointOnLand, the saved goal, delta and displacement from the position, the
// arrival test, then normalize, target = startPosition, delta scaled and added to target.
// As in the twin the pathfinder comes through TheAI's accessor and the goal through the AI's goal
// view, with no named copies: cl numbers the first 32 locals by first assignment and sorts the
// scale's operands by that number, so two extra locals move delta.y out of that block and retail's
// split (x and y multiplied from memory, z preloaded) is lost.
void OpenContain::exitObjectViaDoor(Object *exitObj,ExitDoorType exitDoor)
{
 removeFromContain(exitObj,false);
 Object *me=getObject();
 doorCloseCountdown=getOpenContainModuleData()->m_doorOpenTime;
 if(doorCloseCountdown){
  if(me->conditionBits.test(22)||!me->conditionBits.test(21)){
   me->conditionBits.clear(22);
   me->conditionBits.set(21);
   me->rva0028AE6D();
  }
 }
 int numberExits=getOpenContainModuleData()->m_numberOfExitPaths;
 if(numberExits>0){
  AsciiString startBone("ExitStart");
  AsciiString endBone("ExitEnd");
  Coord3D endPosition;
  AIUpdateInterface *ai;
  {
  Coord3D startPosition;
  if(numberExits>1){
   char suffix[8];
   _imp___itoa(whichExitPath,suffix,10);
   if(whichExitPath<10){
    concatChar(startBone,'0');
    concatChar(endBone,'0');
   }
   whichExitPath=whichExitPath%numberExits+1;
   startBone.concat(suffix);
   endBone.concat(suffix);
  }
  me->getSingleLogicalBonePosition(((StringBase<char>*)&startBone)->str(),&startPosition,0);
  me->getSingleLogicalBonePosition(((StringBase<char>*)&endBone)->str(),&endPosition,0);
  float exitAngle=me->orientation;
  exitObj->setPosition(&startPosition);
  exitObj->setOrientation(exitAngle);
  exitObj->setLayer((PathfindLayerEnum)me->rva0028B511());
  ai=exitObj->ai;
  TheAI->m_pathfinder->AddObjectToPathfindMap(exitObj);
  if(ai){
   ai->ignoreObstacle(exitObj);
   ai->ignoreCollisionUntil=TheGameLogic->getFrame()+BfmeLogicFramesPerSecond;
   TheAI->pathfinder()->adjustToPossibleDestination(exitObj,ai->locomotorSet(),&endPosition);
  }
  }
  _STL::vector<Coord3D> exitPath;
  exitPath.push_back(endPosition);
  exitPath.push_back(endPosition);
  if(rallyPointExists)
   exitPath.push_back(rallyPoint);
  if(ai){
   ai->commands.rva0036EE16((const Rva0035149F*)&exitPath,me,CMD_FROM_AI);
   exitObj->rva0028ACDC((int)&endPosition);
  }
 }else{
  if(me->thingTemplate[0x11f]&0x80){
   AIUpdateInterface *ai;
   Coord3D savedGoal,target,startPosition;
   float exitAngle;
   const Coord3D *pos=&me->position;
   startPosition.x=pos->x;
   startPosition.y=pos->y;
   startPosition.z=pos->z;
   if(TheAI->pathfinder()->getClosestPointOnLand(pos,me,&startPosition)){
    ai=exitObj->ai;
    if(ai){
     {
     Coord3D delta,displacement;
     savedGoal.x=ai->goalView->goal.x;
     savedGoal.y=ai->goalView->goal.y;
     delta.x=startPosition.x-pos->x;
     delta.y=startPosition.y-pos->y;
     savedGoal.z=ai->goalView->goal.z;
     delta.z=startPosition.z-pos->z;
     exitAngle=(float)Rva000422A0Atan2(delta.y,delta.x);
     const Coord3D *dest=&me->ai->position148;
     target.x=dest->x;
     target.y=dest->y;
     target.z=dest->z;
     displacement.x=target.x-pos->x;
     displacement.y=target.y-pos->y;
     displacement.z=target.z-pos->z;
     if(displacement.length()<BfmeOpenContainExitDistance){
      delta.normalize();
      target=startPosition;
      delta.x*=BfmeOpenContainExitDistance;
      delta.y*=BfmeOpenContainExitDistance;
      delta.z*=BfmeOpenContainExitDistance;
      target.x+=delta.x;
      target.y+=delta.y;
      target.z+=delta.z;
     }
     }
     exitObj->setPosition(&startPosition);
     exitObj->setOrientation(exitAngle);
     if(!exitObj->rva002931BA()){
      _STL::vector<Coord3D> exitPath;
      exitPath.push_back(target);
      exitPath.push_back(target);
      exitPath.push_back(savedGoal);
      if(BfmeAIExitDoorFlag)
       ai->commands.rva0036EF09((const Rva0035149F*)&exitPath,me,exitAngle,CMD_FROM_AI);
      else
       ai->commands.rva0036EE16((const Rva0035149F*)&exitPath,me,CMD_FROM_AI);
      target=savedGoal;
     }
     exitObj->rva0028ACDC((int)&target);
    }
   }
  }
  TheAI->m_pathfinder->AddObjectToPathfindMap(exitObj);
 }
}


void OpenContain::exitObjectInAHurry(Object *exitObj)
{
 removeFromContain(exitObj,false);
 Object *me=getObject();
 doorCloseCountdown=getOpenContainModuleData()->m_doorOpenTime;
 if(doorCloseCountdown){
  if(me->conditionBits.test(22)||!me->conditionBits.test(21)){
   me->conditionBits.clear(22);
   me->conditionBits.set(21);
   me->rva0028AE6D();
  }
 }
 int numberExits=getOpenContainModuleData()->m_numberOfExitPaths;
 if(numberExits>0){
  AsciiString startBone("ExitStart");
  AsciiString endBone("ExitEnd");
  Coord3D startPosition;
  Coord3D endPosition;
  if(numberExits>1){
   char suffix[8];
   _imp___itoa(whichExitPath,suffix,10);
   if(whichExitPath<10){
    concatChar(startBone,'0');
    concatChar(endBone,'0');
   }
   whichExitPath=whichExitPath%numberExits+1;
   startBone.concat(suffix);
   endBone.concat(suffix);
  }
  me->getSingleLogicalBonePosition(((StringBase<char>*)&startBone)->str(),&startPosition,0);
  me->getSingleLogicalBonePosition(((StringBase<char>*)&endBone)->str(),&endPosition,0);
  float exitAngle=me->orientation;
  exitObj->setPosition(&startPosition);
  exitObj->setOrientation(exitAngle);
  exitObj->setLayer((PathfindLayerEnum)me->rva0028B511());
  _STL::vector<Coord3D> exitPath;
  exitPath.push_back(endPosition);
  AIUpdateInterface *ai=exitObj->ai;
  AIUpdateInterface *myAi=me->ai;
  TheAI->m_pathfinder->AddObjectToPathfindMap(exitObj);
  if(ai){
   if(myAi&&myAi->isIdle()&&(me->thingTemplate[0x109]&2)){
    me->rva0028AD7C();
    me->rva0028ACDC((int)&me->position);
   }
   ai->ignoreObstacle(0);
   ai->ignoreCollisionUntil=TheGameLogic->getFrame()+BfmeLogicFramesPerSecond;
   Pathfinder *pathfinder=TheAI->m_pathfinder;
   pathfinder->adjustToPossibleDestination(exitObj,ai->locomotorSet(),&endPosition);
  }
  exitPath.push_back(endPosition);
  if(rallyPointExists)
   exitPath.push_back(rallyPoint);
  if(ai){
   ai->doQuickExit(&exitPath);
   exitObj->rva0028ACDC((int)&endPosition);
  }
 }else{
  TheAI->m_pathfinder->AddObjectToPathfindMap(exitObj);
 }
}

inline Rva0035149F &Rva0035149F::rva0035149F(const Rva0035149F &other)
{
 _STL::__false_type tag;
 typedef BfmeE12 *(__cdecl *Copy)(const BfmeE12*,const BfmeE12*,BfmeE12*,const _STL::__false_type&);
 Copy copy=&_STL::__copy_ptrs<const BfmeE12*,BfmeE12*>;
 if(&other==this)return *this;
 unsigned n=other.finish-other.start,cap=end-start;
 if(n>cap){
  BfmeE12 *fresh=((Rva000E016A*)this)->rva000E016A(n,(Coord3D*)other.start,(Coord3D*)other.finish);
  if(start)Rva00030830GameFree(start);
  start=fresh;end=fresh+n;
 }else{
  unsigned sz=finish-start;
  if(sz>=n){
   copy((const BfmeE12*)other.start,(const BfmeE12*)other.finish,start,tag);
  }else{
   copy((const BfmeE12*)other.start,(const BfmeE12*)(other.start+sz),start,tag);
   _STL::__uninitialized_copy((Coord3D*)(other.start+(finish-start)),(Coord3D*)other.finish,(Coord3D*)finish,tag);
  }
 }
 finish=start+n;
 return *this;
}
__declspec(noinline) inline void AICommandInterface::rva0036EE16(const Rva0035149F *info,Object *target,CommandSourceType src)
{
 AICommandParms parms(AICMD_PATH,src);parms.coords.rva0035149F(*info);parms.target=target;aiDoCommand(&parms);
}
__declspec(noinline) inline void AICommandInterface::rva0036EF09(const Rva0035149F *info,Object *target,float value,CommandSourceType src)
{
 AICommandParms parms(AICMD_PATH_ANGLE,src);parms.coords.rva0035149F(*info);parms.target=target;parms.pos.x=value;aiDoCommand(&parms);
}
// Coord3D::length (0x00003571) and ::normalize (0x000035B6) are `inline` (select-any COMDAT) in
// coord3d.cpp; these copies compile byte-exact to both rows, so they are link-safe. Making them
// visible lets VC7.1 see that &delta/&displacement do not escape: fixes the fld/mov order at 0x4654FB.
#include <math.h>
inline __declspec(noinline) float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}
inline __declspec(noinline) void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}
