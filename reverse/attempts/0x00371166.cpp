// ?moveFormationToPos@AIGroup@@QAEXPBUCoord3D@@W4CommandSourceType@@H_N2@Z
// partial score=0.7252090375378046 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?moveFormationToPos@AIGroup@@QAEXPBUCoord3D@@W4CommandSourceType@@H_N2@Z
// partial score=0.7025641974 date=2026-10-09
// cl: /I. /O1 /G7 /EHs /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Donor semantic spine: f98983a7d ZH AIGroup::friend_moveFormationToPos.
// Native371166..371AE2 RET20 / WB EE0AF0 independently name BFME2 formation move.
#include <list>
#include <vector>
#include "Coord3D.h"
#include "Coord2D.h"
namespace _STL {template<> void vector<Coord3D>::push_back(const Coord3D&);}
enum CommandSourceType {CMD_FROM_PLAYER=0};
enum PathfindLayerEnum {LAYER_INVALID=0,LAYER_GROUND=1};
float ACos(float);
class Object; class LocomotorSet; class Rva0035149F;
class Rva00295A0FCommands {public:void Rva00295A0FCommand(void*,int,int);};
class AICommandInterface {public:
 void aiMoveToPosition(const Coord3D*,CommandSourceType);
 void rva0036EE89(const Rva0035149F*,Object*,float,CommandSourceType);
 void rva0036EF09(const Rva0035149F*,Object*,float,CommandSourceType);
};
struct FormationLocomotorTemplate {char pad0[0x78];int mode;};
struct FormationLocomotor {char pad0[4];FormationLocomotorTemplate *type;};
class AIUpdateInterface {public:
#define AIV(n) virtual void slot##n();
 AIV(0) AIV(1) AIV(2) AIV(3) AIV(4) AIV(5) AIV(6) AIV(7) AIV(8) AIV(9)
 AIV(10) AIV(11) AIV(12) AIV(13) AIV(14) AIV(15) AIV(16) AIV(17) AIV(18) AIV(19)
 AIV(20) AIV(21) AIV(22) AIV(23) AIV(24) AIV(25) AIV(26) AIV(27) AIV(28) AIV(29)
 AIV(30) AIV(31) AIV(32) AIV(33) AIV(34) AIV(35) AIV(36) AIV(37) AIV(38) AIV(39)
 AIV(40) AIV(41) AIV(42) AIV(43) AIV(44) AIV(45) AIV(46) AIV(47) AIV(48) AIV(49)
 AIV(50) AIV(51) AIV(52) AIV(53) AIV(54) AIV(55) AIV(56) AIV(57) AIV(58) AIV(59)
 AIV(60) AIV(61) AIV(62) AIV(63) AIV(64) AIV(65) AIV(66) AIV(67) AIV(68) AIV(69)
 AIV(70) AIV(71) AIV(72) AIV(73) AIV(74) AIV(75) AIV(76) AIV(77) AIV(78) AIV(79)
 AIV(80) AIV(81) AIV(82) AIV(83) AIV(84) AIV(85) AIV(86) AIV(87) AIV(88) AIV(89)
 AIV(90) AIV(91) AIV(92) AIV(93) AIV(94) AIV(95) AIV(96) AIV(97) AIV(98) AIV(99)
 AIV(100) AIV(101) AIV(102) AIV(103) AIV(104) AIV(105) AIV(106) AIV(107) AIV(108) AIV(109)
 AIV(110) AIV(111) AIV(112) AIV(113) AIV(114) AIV(115) AIV(116) AIV(117) AIV(118) AIV(119)
 AIV(120) AIV(121) AIV(122) AIV(123) AIV(124) AIV(125) AIV(126) AIV(127) AIV(128) AIV(129)
 AIV(130) AIV(131) AIV(132) AIV(133) AIV(134) AIV(135) AIV(136)
#undef AIV
 virtual bool slot137();
 const LocomotorSet &getLocomotorSet() const {return *reinterpret_cast<const LocomotorSet*>(reinterpret_cast<const char*>(this)+0x1CC);}
 void *surfaces() const {return m_surfaces;}
 char pad4[0x20-4]; AICommandInterface commands;
 char pad21[0x1DC-0x21]; void *m_surfaces;
 char pad1E0[0x1F0-0x1E0];FormationLocomotor *locomotor;
};
class ThingTemplate {public:char pad0[0x564];int formationRank;};
class Object {public:
 int rva0028B511() const;
 bool rva002907A1();
 bool isDisabledByHeld() const{return held();}
 AIUpdateInterface *getAIUpdateInterface() const{return ai;}
 bool rva0028C264(int*,int);
 bool isAbleToAttack() const;
 void rva0028ACEE(int,int);
 const Coord3D *getPosition() const {return &pos;}
 bool held()const{return (disabled[0]&8)!=0;}
 char pad0[4];const ThingTemplate *type;
 char pad8[0x38-8];Coord3D pos;
 char pad44[0x1C8-0x44];unsigned char disabled[0x258-0x1C8];AIUpdateInterface *ai;
 char pad25C[0x414-0x25C];Coord2D offset;
};
class PathNode {public:char pad0[8];PathNode *next;Coord3D position;};
class Path {public:~Path();char pad0[4];PathNode *first,*last;};
class Pathfinder {public:
 bool IsLineBlocked(void*,void*,PathfindLayerEnum,const Coord3D*,const Coord3D*);
 int AdjustGroundPathPosition(const Coord3D*,Coord3D*);
 bool adjustDestination(Object*,const LocomotorSet&,Coord3D*,const Coord3D*);
};
struct FormationAIData {char pad0[0xA4];float spacing;char padA8[4];float terrainSpacing;};
class AI {public:char pad0[0x10];Pathfinder *pathfinder;char pad14[4];FormationAIData *data;};
extern AI *TheAI;
struct FormationExtent {Coord3D lo,hi;};
class TerrainLogic {public:
#define TV(n) virtual void slot##n();
 TV(0) TV(1) TV(2) TV(3) TV(4) TV(5) TV(6) TV(7)
 virtual void slot8(FormationExtent*);
 TV(9) TV(10) TV(11) TV(12) TV(13) TV(14) TV(15) TV(16) TV(17) TV(18) TV(19)
 TV(20) TV(21) TV(22) TV(23) TV(24) TV(25) TV(26) TV(27) TV(28) TV(29)
 TV(30) TV(31) TV(32) TV(33) TV(34) TV(35) TV(36) TV(37) TV(38) TV(39)
 TV(40) TV(41) TV(42) TV(43) TV(44) TV(45) TV(46) TV(47) TV(48) TV(49)
#undef TV
 virtual bool slot50(const Coord3D*);
};
extern TerrainLogic *TheTerrainLogic;
struct Coord3DCopy : Coord3D {Coord3DCopy(){} Coord3DCopy(const Coord3DCopy&p){x=p.x;y=p.y;z=p.z;} Coord3DCopy(const Coord3D&p){x=p.x;y=p.y;z=p.z;}};
static const float &larger(const float&a,const float&b){return a>b?a:b;}
static inline void sub(Coord3D &v,const Coord3D&r){v.x-=r.x;v.y-=r.y;v.z-=r.z;}
static inline float sqrd(const Coord3D&v){return v.x*v.x+v.z*v.z+v.y*v.y;}
class AIGroup {public:
 bool getCenter(Coord3D*);
 static void rotateOffset(const Coord3D*,const Coord3D*,Coord2D*);
 void moveFormationToPos(const Coord3D*,CommandSourceType,int,bool,bool);
private:char pad0[4];std::list<Object*> members;char pad8[0x14-8];Path *groundPath;
};
void AIGroup::moveFormationToPos(const Coord3D *pos,CommandSourceType source,int mode,bool ground,bool keepFormation)
{
 Coord3D center;
 if(!getCenter(&center))return;
 PathNode *startNode=0,*endNode=0;
 Coord3DCopy endPoint=*pos;
 Coord3DCopy startPoint=center;
 Coord3DCopy moveStart=center;
 float startDistance=TheAI->data->spacing*4.0f;
 float endDistance=TheAI->data->spacing*2.0f;
 bool useMoveStart=false;
 if(members.empty())return;
 float spacing=0.0f;
 bool wider=false;
 for(std::list<Object*>::iterator i=members.begin();i!=members.end();++i){
  Object *obj=*i;Coord2D offset=obj->offset;
  float required=(float)obj->type->formationRank*TheAI->data->spacing-offset.x;
  spacing=larger(spacing,required);
  int info;if(obj->rva0028C264(&info,4))wider=true;
 }
 spacing+=TheAI->data->spacing*0.5f;
 startDistance=larger(startDistance,spacing);
 if(wider)startDistance*=2.0f;
 if(groundPath){
  static_cast<Coord3D&>(startPoint)=groundPath->first->position;
  float remaining=startDistance;
  Coord3DCopy previous=startPoint;
  for(PathNode *node=groundPath->first;node;node=node->next){
   Coord3D delta=node->position;
   delta.x-=previous.x;delta.y-=previous.y;delta.z=0.0f;
   if(delta.x*delta.x+delta.y*delta.y>remaining*remaining){
    useMoveStart=true;startNode=node;
    delta.normalize();delta.x*=remaining;delta.y*=remaining;delta.z*=remaining;
    moveStart=previous;moveStart.x+=delta.x;moveStart.y+=delta.y;moveStart.z+=delta.z;
    break;
   }
   static_cast<Coord3D&>(previous)=node->position;
   remaining-=delta.GetLength();
  }
  static_cast<Coord3D&>(endPoint)=groundPath->last->position;
  Coord3D delta=groundPath->last->position;sub(delta,moveStart);
  if(sqrd(delta)<endDistance*endDistance)useMoveStart=false;
  for(PathNode *node=groundPath->first;node;node=node->next){
   Coord3D delta=node->position;delta.x-=endPoint.x;delta.y-=endPoint.y;
   if(delta.x*delta.x+delta.y*delta.y>endDistance*endDistance)endNode=node;
  }
  for(PathNode *node=endNode;node;node=node->next)if(node==startNode)endNode=0;
  if(!startNode || !endNode){delete groundPath;groundPath=0;startNode=0;endNode=0;}
 }
 Coord3DCopy facingStart=startPoint;
 if(endNode)static_cast<Coord3D&>(facingStart)=endNode->position;
 Coord3D facing;facing.x=(float)((double)endPoint.x-(double)facingStart.x);facing.y=endPoint.y-facingStart.y;facing.z=endPoint.z-facingStart.z;
 facing.normalize();float angle=ACos(facing.x);if(facing.y<0.0f)angle=-angle;
 for(std::list<Object*>::iterator i=members.begin();i!=members.end();++i){
  Object *unit=*i;if(unit->held())continue;
  AIUpdateInterface *ai=unit->ai;if(!ai)continue;
  Coord2D offset=unit->offset;
  bool pathClear=true;
  if(TheAI->pathfinder->IsLineBlocked(unit,unit->ai->surfaces(),(PathfindLayerEnum)unit->rva0028B511(),unit->getPosition(),&startPoint)){
   pathClear=false;
   if(useMoveStart && !TheAI->pathfinder->IsLineBlocked(unit,unit->ai->surfaces(),(PathfindLayerEnum)unit->rva0028B511(),unit->getPosition(),&moveStart))pathClear=true;
  }
  std::vector<Coord3D> path;
  Coord3DCopy previous=startPoint;
  if(useMoveStart && pathClear){
   Coord2D rotated=offset;rotateOffset(&previous,&moveStart,&rotated);
   previous=moveStart;
   Coord3DCopy dest;dest.x=moveStart.x+rotated.x;dest.y=moveStart.y+rotated.y;dest.z=moveStart.z;
   if(ground==true)TheAI->pathfinder->AdjustGroundPathPosition(&moveStart,&dest);
   path.push_back(dest);
  }
  if(startNode && pathClear){
   for(PathNode *node=startNode;node;node=node->next){
    Coord3DCopy dest=node->position;Coord2D rotated=offset;
    rotateOffset(&previous,&dest,&rotated);
    if(TheTerrainLogic->slot50(&dest)){rotated.x*=TheAI->data->terrainSpacing;rotated.y*=TheAI->data->terrainSpacing;}
{_ReadWriteBarrier();     dest.x+=rotated.x;dest.y+=rotated.y;}
    if(ground==true)TheAI->pathfinder->AdjustGroundPathPosition(&node->position,&dest);
    path.push_back(dest);
    if(node==endNode)break;
    previous=dest;
   }
  }
  Coord2D rotated=offset;rotateOffset(&previous,&endPoint,&rotated);
  if(TheTerrainLogic->slot50(&endPoint)){rotated.x*=TheAI->data->terrainSpacing;rotated.y*=TheAI->data->terrainSpacing;}
  if(ai->locomotor && ai->locomotor->type->mode==0 && !keepFormation){rotated.x*=0.0f;rotated.y*=0.0f;}
  Coord3DCopy dest;dest.x=endPoint.x+rotated.x;dest.y=endPoint.y+rotated.y;dest.z=endPoint.z;
  if(ground==true)TheAI->pathfinder->AdjustGroundPathPosition(&endPoint,&dest);
  if(!TheAI->pathfinder->adjustDestination(unit,ai->getLocomotorSet(),&dest,0)){
   FormationExtent extent;TheTerrainLogic->slot8(&extent);
   if(!(dest.x>extent.lo.x && dest.x<extent.hi.x && dest.y>extent.lo.y && dest.y<extent.hi.y)){
    dest=endPoint;TheAI->pathfinder->adjustDestination(unit,ai->getLocomotorSet(),&dest,0);
   }
  }
  unit->rva0028ACEE((int)&dest,(int)LAYER_GROUND);path.push_back(dest);
  if(mode==1 && unit->isAbleToAttack()){
   if(!ai->slot137())reinterpret_cast<Rva00295A0FCommands*>(&ai->commands)->Rva00295A0FCommand(&dest,0x7fffffff,(int)source);
   else ai->commands.rva0036EF09(reinterpret_cast<const Rva0035149F*>(&path),0,angle,source);
  }else{
   if(!ai->slot137())ai->commands.aiMoveToPosition(&dest,source);
   else ai->commands.rva0036EE89(reinterpret_cast<const Rva0035149F*>(&path),0,angle,source);
  }
 }
}

bool AIGroup::getCenter(Coord3D *center)
{
	int count = 0;
	center->x = 0.0f;
	center->y = 0.0f;
	center->z = 0.0f;

	std::list<Object *>::iterator i;
	for (i = members.begin(); i != members.end(); ++i)
	{
		if ((*i)->isDisabledByHeld())
			continue;	// don't bother counting riders in the center calculation
		if (!(*i)->rva002907A1())
			continue;
		AIUpdateInterface *ai = (*i)->getAIUpdateInterface();
		if (ai)
		{
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;
			++count;
		}
	}

	if (count == 0 && !members.empty())
	{
		for (i = members.begin(); i != members.end(); ++i)
		{
			if ((*i)->isDisabledByHeld())
				continue;	// don't bother counting riders in the center calculation
			const Coord3D *objPos = (*i)->getPosition();
			center->x = objPos->x + center->x;
			center->y += objPos->y;
			center->z += objPos->z;
			++count;
		}
	}

	center->x /= count;
	center->y /= count;
	center->z /= count;
	return count > 0;
}

