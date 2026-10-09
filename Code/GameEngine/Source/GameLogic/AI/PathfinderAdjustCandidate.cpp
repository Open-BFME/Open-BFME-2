// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Semantic lead: ZH AIPathfind.cpp checkForAdjust; BFME2 native 002F57E6
// replaces the locomotor query with Object path tests and rejects excessive
// height deltas. Existing Rva002F70E5QueryCallback.cpp supplies this ABI.
#include <math.h>
struct Rva002F70E5Coord { float x,y,z; };
#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum PathfindLayerEnum { LAYER_GROUND=0 };
struct ThingTemplate { char pad[0x109]; unsigned char kind109; };
class Object { public: void *vptr; ThingTemplate *type; char pad[0x38-8]; Coord3D position; };
class PathfindCell { public: char pad[0xc]; unsigned int flags; int getLayer() const {return(flags>>4)&0x3f;} };
void *rva002EBC59(void *,void *,int,int,int);
class Pathfinder {
public:
 PathfindCell *getCell(PathfindLayerEnum,int,int);
 bool rva002E9EA7(Object *,int,int,PathfindLayerEnum,int,unsigned char,int *);
 bool QuickDoesPathExist(Object *,const Coord3D *,const Coord3D *,int);
};
class Rva002F57E6Query {
public:
 bool rva002F57E6(unsigned int a,unsigned int b,unsigned char mode,unsigned int x,int y,unsigned int layer,unsigned int radius,unsigned char center,Rva002F70E5Coord *destination,float originalZ,int *word);
 char pad[0x24]; int minX,minY,maxX,maxY;
};
bool Rva002F57E6Query::rva002F57E6(unsigned int a,unsigned int b,unsigned char mode,unsigned int x,int y,unsigned int layer,unsigned int radius,unsigned char center,Rva002F70E5Coord *destination,float originalZ,int *word) {
 Pathfinder *pathfinder=(Pathfinder *)this; Object *object=(Object *)a;
 PathfindCell *cell=pathfinder->getCell((PathfindLayerEnum)layer,(int)x,y);
 if(!cell) return false;
 if((cell->flags&0xf)==2) return false;
 if(mode && ((int)x<minX || y<minY || (int)x>maxX || y>maxY)) return false;
 if(!pathfinder->rva002E9EA7(object,(int)x,y,(PathfindLayerEnum)layer,radius,center,word)) return false;
 {
  Coord3D tmp,adjust;
  adjust=*(Coord3D *)rva002EBC59(&tmp,object,x,y,cell->getLayer());
  if(!(object->type->kind109&0x10)) {
   if(originalZ>0.0f && fabs(adjust.z-originalZ)>50.0f) return false;
   bool adjustedPathExists=pathfinder->QuickDoesPathExist(object,&object->position,&adjust,0);
   bool pathExists=pathfinder->QuickDoesPathExist(object,&object->position,(Coord3D *)destination,0);
   if(!pathExists) {
    if(pathfinder->QuickDoesPathExist(object,(Coord3D *)destination,&adjust,0)) adjustedPathExists=true;
   }
   if(!adjustedPathExists) return false;
  }
  *(Coord3D *)destination=adjust;
  return true;
 }
}
