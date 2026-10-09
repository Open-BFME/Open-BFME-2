// ?AdjustFlingDestination@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@PAU3@@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
#include <string.h>
#include "../Code/Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum { PATHFIND_LAYER_UNKNOWN=0, PATHFIND_LAYER_GROUND=1 };
struct Rva0028AC4EEntry;
struct PathfinderTemplateView { char pad[0x56c];int priority;char pad570[0x634-0x570];bool flag; };
struct PathfinderFlingLocomotorTemplate { char pad[0x14];int surfaces; };
struct PathfinderFlingLocomotor { void *word0;PathfinderFlingLocomotorTemplate *info; };
class Object {
public:
 const Rva0028AC4EEntry *rva0028AC4E() const;
 bool rva0028AC62() const;
 bool rva0028AFBB() const;
 int rva0028B511() const;
 void *word0;PathfinderTemplateView *m_template;
};
bool Rva002EBBFBIsOdd(void *);
class Pathfinder;
struct PathfinderFlingProfile {
 int surfaces;
 bool flag4,flag5;
 int maxLayer;
 bool flagC;
};
struct PathfinderFlingContext {
 Pathfinder *pathfinder;
 Coord3D *lastValid;
 int layer;
 PathfinderFlingProfile profile;
 bool flag;
 PathfinderFlingContext(Pathfinder *p,Coord3D *pos,int l,const PathfinderFlingProfile &m,bool f)
  :pathfinder(p),lastValid(pos),layer(l),profile(m),flag(f) {}
};
class Pathfinder {
public:
 void AdjustFlingDestination(Object *,const Coord3D *,Coord3D *);
 int rva002EB4A0(const Coord3D *,const Coord3D *,PathfindLayerEnum,void *);
};
void Pathfinder::AdjustFlingDestination(Object *object,const Coord3D *originalFrom,Coord3D *to)
{
 bool center=Rva002EBBFBIsOdd(object);
 Coord3D from;
 from.x=originalFrom->x;from.y=originalFrom->y;from.z=originalFrom->z;
 if(!center) {
  from.x+=5.0f;from.y+=5.0f;
  to->x+=5.0f;to->y+=5.0f;
 }
 const Rva0028AC4EEntry *entry=object->rva0028AC4E();
 int surfaces=1;
 if(entry) surfaces=reinterpret_cast<const PathfinderFlingLocomotor *>(entry)->info->surfaces;
 int maxLayer=object->m_template->priority;
 bool templateFlag=object->m_template->flag;
 bool flagC=object->rva0028AC62();
 PathfinderFlingProfile profile;
 profile.surfaces=surfaces;profile.flag4=!templateFlag;
 profile.flag5=object->rva0028AFBB();profile.maxLayer=maxLayer-1;profile.flagC=flagC;
 Coord3D lastValid;
 lastValid.x=from.x;lastValid.y=from.y;lastValid.z=from.z;
 bool ground=(*(const unsigned char *)((const char *)object+0x438)&1)==0;
 PathfinderFlingContext query(this,&lastValid,object->rva0028B511(),profile,ground);
 if(rva002EB4A0(&from,to,PATHFIND_LAYER_GROUND,&query))
  *to=lastValid;
 if(!center) {to->x-=5.0f;to->y-=5.0f;}
}
