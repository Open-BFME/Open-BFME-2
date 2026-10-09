// ?rva0044E85E@SpecialAbilityUpdate@@QAE_NPAUCoord3D@@M@Z
// partial score=0.949253 date=2026-10-09
// cl: /O1 /arch:SSE /MD /GX /I.
#include "Code/Libraries/Include/Lib/Coord3D.h"
enum PathfindLayerEnum { LAYER_GROUND=0, LAYER_BRIDGE=1 };
class Object {
public:
 int rva0028B511() const;
 char m_pad00[0x38]; Coord3D m_position;
 char m_pad44[0x258-0x44]; void *m_ai;
};
class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*); };
extern TerrainLogic *TheTerrainLogic;
class Pathfinder { public: bool QuickDoesPathExist(Object*,const Coord3D*,const Coord3D*,int); };
class AI {public: char m_pad00[0x10]; Pathfinder *m_pathfinder;};
extern AI *TheAI;
class SpecialAbilityUpdate {
public:
 bool rva0044E85E(Coord3D *pos,float range);
 char m_pad00[8]; Object *m_object;
};
bool SpecialAbilityUpdate::rva0044E85E(Coord3D *pos,float range)
{
 Object *object=m_object;
 if(object->rva0028B511()>1) return true;
 if(!object->m_ai) return false;
 Coord3D dir=*pos;
 Coord3D result={pos->x,pos->y,pos->z};
 const Coord3D *objectPos=&object->m_position;
 dir.x-=objectPos->x;
 dir.y-=objectPos->y;
 dir.z=0;
 int steps=(int)(range/10.0f)-1;
 dir.Normalize();
 dir.x=10.0f*dir.x;dir.y=10.0f*dir.y;dir.z=10.0f*dir.z;
 bool found=false;
 for(int i=0;i<steps;++i) {
  result.x-=dir.x; result.y-=dir.y; result.z-=dir.z;
  if(TheTerrainLogic->getLayerForDestination(object,&result)!=LAYER_BRIDGE) continue;
  Pathfinder *finder=TheAI->m_pathfinder;
  if(finder->QuickDoesPathExist(object,objectPos,&result,0)){found=true;break;}
 }
 if(!found) return false;
 *pos=result;
 return true;
}
