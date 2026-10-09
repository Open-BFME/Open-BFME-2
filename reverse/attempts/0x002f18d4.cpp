// ?cellCallback@Rva002F18D4Info@@QAEHPAVPathfindCell@@0HH@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// Semantic guide BF1 f98983a7d PathfindObstacleCallbackDebb0.cpp and ZH
// checkDestination obstacle exemption ladder. Native BF2 2F18D4..2F1AF4 RET16
// proves existing neutral callback ABI, native layer shift4/type4bit, info
// obstacle ID +28, contained-by +274 and payload accesses 0..18. BF2 adds
// template kind masks and owner/partner squared distance comparison; purpose
// and class identity remain inferred from reference and native call graph.
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"
class ThingTemplate {
public:
 bool kind214()const{return (flags[6]>>22)&1;}
 bool kind59()const{return (((const unsigned char*)flags)[7]&8)!=0;}
 bool kind60()const{return (((const unsigned char*)flags)[7]&16)!=0;}
 bool kind189()const{return (((const unsigned char*)flags)[23]&32)!=0;}
 bool kind203()const{return (((const unsigned char*)flags)[25]&8)!=0;}
 bool kind150()const{return (((const unsigned char*)flags)[18]&64)!=0;}
private: unsigned char pad[0x108];unsigned int flags[7];
};
class Object {
public:
 ObjectID getID()const{return m_id;}
 int rva0028B511()const;
 const Coord3D*getPosition()const{return &pos;}
 const ThingTemplate*getTemplate()const{return templ;}
 unsigned char pad0[4];const ThingTemplate*templ;
 unsigned char pad8[0x38-8];Coord3D pos;
 unsigned char pad44[0x74-0x44];ObjectID m_id;
 unsigned char pad78[0x274-0x78];Object*m_containedBy;
};
extern GameLogic*TheGameLogic;
struct PathfindCellInfo {unsigned char pad[0x28];ObjectID obstacle;};
class PathfindCell {
public:
 int getLayer()const{return (packed>>4)&63;}
 int getRawType()const{return bits.type;}
 ObjectID getObstacleID()const {return info?info->obstacle:INVALID_OBJECT_ID;}
 bool IsObstaclePresent(ObjectID)const;
 PathfindCellInfo*info;int unused1,unused2;union{unsigned int packed;struct{unsigned int type:4;unsigned int rest:28;}bits;};
};
class Rva002E6C4D {public:int rva002E6C4D();};
int Rva002E6E8AGet(int);
void*Rva002E6E9FGet(void*);
class Rva002F18D4Info {
public:
 int cellCallback(PathfindCell*,PathfindCell*,int,int);
 Object*m_obj,*m_other;PathfindCell*m_cell;int m_skip;bool m_hitLayer;
 int m_layerCount,m_runLength;
};
int Rva002F18D4Info::cellCallback(PathfindCell*previous,PathfindCell*current,int x,int y){
 if((unsigned char)Rva002E6E8AGet(current->getLayer())){m_layerCount++;m_runLength=0;m_hitLayer=true;}else m_runLength++;
 if(m_skip>0){m_skip--;return 0;}
 if(current->getRawType()!=4)return 0;
 if(current->IsObstaclePresent(m_obj->getID()))return 0;
 Object*other=m_other;
 if(other){
  if(current->IsObstaclePresent(other->m_id))return 0;
  if(current->IsObstaclePresent((ObjectID)(int)Rva002E6E9FGet(other)))return 0;
 }
 Object*obj=m_obj;Object*held=obj->m_containedBy;
 if(held){
  if(current->IsObstaclePresent(held->m_id))return 0;
  held=held->m_containedBy;
  if(held){if(current->IsObstaclePresent(held->m_id))return 0;}
 }
 if(current->IsObstaclePresent((ObjectID)(int)Rva002E6E9FGet(obj)))return 0;
 if((unsigned char)((Rva002E6C4D*)current)->rva002E6C4D())return 0;
 if(m_cell){if(current->IsObstaclePresent(m_cell->getObstacleID()))return 0;}
 Object*unit=TheGameLogic->findObjectByID(current->getObstacleID());
 if(unit){
  bool ownerFlag=m_obj->getTemplate()->kind214();
  if(unit->getTemplate()->kind60()||unit->getTemplate()->kind189()||unit->getTemplate()->kind203()||unit->getTemplate()->kind150()){
   if(m_obj->rva0028B511()!=1)return 0;
   if(m_other){
    if(m_other->rva0028B511()!=1)return 0;
    if(ownerFlag){
     float fx=(float)(x*10),fy=(float)(y*10);
     const Coord3D*op=m_obj->getPosition();const Coord3D*pp=m_other->getPosition();
     float dx=op->x-fx,dy=op->y-fy,px=pp->x-fx,py=pp->y-fy;
     float od=dy*dy+dx*dx,pd=py*py+px*px;
     if(pd>od)return 0;
    }
   }
  }else{
   if(ownerFlag&&!m_obj->getTemplate()->kind59())return 0;
  }
 }
 return 1;
}
