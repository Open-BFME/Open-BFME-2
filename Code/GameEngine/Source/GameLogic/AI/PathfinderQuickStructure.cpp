// ?QuickDoesPathExistToStructure@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@0H@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /I.
// Uses the published private helper at2F4AC1; its nine stack slots
// are independently corroborated by this complete caller.
#include "Coord3D.h"
struct ICoord2D {int x,y;};
struct QuickStructureCoord:Coord3D {QuickStructureCoord(const Coord3D&r){x=r.x;y=r.y;z=r.z;}};
struct TargetQuickTemplate {char pad[0x56C];int priority;char pad570[0x634-0x570];bool flag;};
class Object {public:bool rva0028AFBB()const;void *vptr;TargetQuickTemplate *definition;char pad8[0x38-8];Coord3D position;char pad44[0xB8-0x44];float observedSize;char padBC[0x258-0xBC];char *ai;};
class LocomotorSet {public:char pad[0x10];unsigned surfaces;};
struct BfmeShapeE15 {char pad[0x10];Coord3D offset;char tail[8];};
class BfmeObjE15 {public:BfmeShapeE15 *bfmeAtE15(int);};
struct QuickStructureCellInfo {char pad[0x28];int structure;};
class PathfindCell {public:QuickStructureCellInfo *info;int word4;unsigned short zone;unsigned short wordA;unsigned flags;enum CellType {CLEAR=0,OBSTACLE=4};CellType type()const{return (CellType)(flags&15);}};
struct Rva002E8BCFSrc;
class Rva002E8BCF {public:Rva002E8BCF(const Rva002E8BCFSrc*,bool,int,bool);unsigned surfaces;bool field4,field5;int priority;bool fieldC;};
ICoord2D *Rva002E7875WorldToCell(ICoord2D*,bool,const Coord3D*);
class Object;class LocomotorSet;class Rva002E8BCF;class Pathfinder;
struct Rva002E7261Info {Pathfinder *pathfinder;int structure;int zone;int x,y;};
enum PathfindLayerEnum {OBSERVED_LAYER=1};
class TerrainLogic {public:PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);};
extern TerrainLogic *TheTerrainLogic;
class Rva002E99F9Sub460 {public:unsigned short rva0053241F(void*,unsigned short);};
class Pathfinder {
public:
private:
 int iterateCellsAlongLine(const ICoord2D*,const ICoord2D*,PathfindLayerEnum,Rva002E7261Info*);
public:
 bool QuickDoesPathExist(Object*,const Coord3D*,const Coord3D*,int);
 bool QuickDoesPathExistToStructure(Object*,const Coord3D*,Object*,int);
 PathfindCell *rva002E8BF8(PathfindLayerEnum,const Coord3D*);
 bool rva002F4AC1(const ICoord2D*,int,int,Object*,PathfindLayerEnum,int,Rva002E7261Info*,void*,void*);
 char pad[0x460];Rva002E99F9Sub460 zones;
};
// Native full600B RET16; WB D39F80 explicitly names this four-argument
// structure reachability query. Target independently proves Object AI258,
// position38, geometryA8/sizeB8, template56C/634, info structure28 and zones460.
// Native size arithmetic is 2-trunc(observedSize*-.1); the negative
// literal is independently verified by the float-reference gate.
bool Pathfinder::QuickDoesPathExistToStructure(Object *object,const Coord3D *from,Object *container,int overrideSet)
{
 char *ai=object->ai;
 if(!ai && !overrideSet)return false;
 LocomotorSet *set=overrideSet?(LocomotorSet*)overrideSet:(LocomotorSet*)(ai+0x1CC);
 if(!(set->surfaces&0x8F))return false;
 QuickStructureCoord target=container->position;
 PathfindLayerEnum targetLayer=TheTerrainLogic->getLayerForDestination(object,&target);
 PathfindLayerEnum sourceLayer=TheTerrainLogic->getLayerForDestination(object,from);
 PathfindCell *sourceCell=rva002E8BF8(sourceLayer,from);
 PathfindCell *targetCell=rva002E8BF8(targetLayer,&target);
 if(targetCell->type()!=4){
  const Coord3D &offset=((BfmeObjE15*)((char*)container+0xA8))->bfmeAtE15(0)->offset;
  target.x=offset.x+target.x;target.y=offset.y+target.y;target.z=offset.z+target.z;
  targetCell=rva002E8BF8(targetLayer,&target);
  if(targetCell->type()!=4)return QuickDoesPathExist(object,from,&target,(int)set);
 }
 int structure=targetCell->info?targetCell->info->structure:0;
 ICoord2D goal;Rva002E7875WorldToCell(&goal,true,&target);
 int priority=object->definition->priority;bool flag=object->definition->flag;
 Rva002E8BCF profile((const Rva002E8BCFSrc*)set,!flag,priority-1,object->rva0028AFBB());
 int sourceZone=zones.rva0053241F(&profile,sourceCell->zone);
 Rva002E7261Info query={this,structure,-1,-1,-1};
 int delta=2-(int)(container->observedSize*-.1f);
 if(rva002F4AC1(&goal,delta,0,object,targetLayer,sourceZone,&query,&profile,set))return true;
 if(rva002F4AC1(&goal,-delta,0,object,targetLayer,sourceZone,&query,&profile,set))return true;
 if(rva002F4AC1(&goal,0,delta,object,targetLayer,sourceZone,&query,&profile,set))return true;
 return rva002F4AC1(&goal,0,-delta,object,targetLayer,sourceZone,&query,&profile,set);
}
