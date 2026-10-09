// ?cellCallback@Rva002F4D8BInfo@@QAEHPAVPathfindCell@@0HH@Z
// partial score=0.9417158394 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7
// Native2F4D8B..2F4E54 RET16 full201; callback address independently
// recovered from caller2F6C22. Layer/type bits at cell+C and opaque state
// bytes1C..20 are target-observed. Existing QuickDoesPathExist pin owns
// the four-argument target2F477E. No original names asserted for state bits.
#include "Lib/Coord3D.h"
typedef bool Bool;
class Object;
class PathfindCell {public:
 char pad00[0xC];unsigned flags;
 __forceinline Bool bit17()const {return (unsigned char)((flags>>17)&1)!=0;}
 __forceinline char layer()const {return (char)((flags>>4)&0x3F);}
 __forceinline char type()const {return (flags&0xF);}
};
class Rva002E6DC4 {public:Bool rva002E6DC4(void *,void *);};
void *rva002EBC59(void *,void *,int,int,int);
class Pathfinder {public:Bool QuickDoesPathExist(Object *,const Coord3D *,const Coord3D *,int);};
struct LayerProbeObjectView {char pad00[0x38];Coord3D position;};
struct Rva002F4D8BInfo {
 Pathfinder *pathfinder;Object *object;void *word08;Coord3D position;int word18;
 Bool flag1C,flag1D,flag1E,flag1F,flag20;
 int cellCallback(PathfindCell *,PathfindCell *,int,int);
};
int Rva002F4D8BInfo::cellCallback(PathfindCell *from,PathfindCell *to,int x,int y)
{
 unsigned flags=to->flags;
 if(((unsigned char)((flags>>17)&1)!=0 || (char)((flags>>4)&0x3F)>1) && !flag1D && !flag1E && flag1F)return 1;
 if((flags&0xF)==4 || ((char)((flags>>4)&0x3F)>1 && !flag1D && flag1E))return 0;
 flag1E=false;
 if(!((Rva002E6DC4 *)pathfinder)->rva002E6DC4(&position,to))return 0;
 Coord3D point;rva002EBC59(&point,object,x,y,to->layer());
 if(pathfinder->QuickDoesPathExist(object,&((LayerProbeObjectView *)object)->position,&point,0)) {
  flag1C=true;return 1;
 }
 flag1F=true;
 if(flag20)return 1;
 return flag1D!=0;
}
