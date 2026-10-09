// ?rva00365E98@Path@@QAEXPAVObject@@PBUCoord3D@@H_N@Z
// partial score=0.9709515446 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Native365E98..36617B RET16 complete739. Existing Path/Object/Coord3D
// consumer pin retained. ZH Path::optimize supplies the node/optimized-link
// spine; this BFME2 pass rebuilds from optimized nodes with direction-dependent
// first-segment options and frees the original raw chain. Native facts: Path
// head4/tail8/flagC, node links0/8 positionC portal20; entry+4 settings70/84/D8.
// No original names asserted for mode values or option bits.
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
typedef bool Bool;typedef int Int;
struct Rva0028AC4EEntry;
class Object {public:const Rva0028AC4EEntry *rva0028AC4E()const;};
class Rva001E3F27FloatChaseField {public:float get()const;};
class Rva00373CAAFloatChaseField {public:float get()const;};
class Rva001E46E1 {public:Bool rva001E543F(Object *);Bool rva001E4015(Object *,const Coord3D *);};
struct DirectionTemplateView {char pad00[0x40];float word40;char pad44[0x70-0x44];Int mode70;char pad74[0x84-0x74];float word84;char pad88[0xD8-0x88];Int wordD8;};
struct DirectionEntryView {void *word0;DirectionTemplateView *settings;};
class PathNode {public:PathNode *next,*previous,*nextOptimized;Coord3D pos;Int layer;Bool canOptimize;char pad1D[3];Int portalID;};
class Rva00363BC7 {public:void *rva00363BC7(Coord2D *,float *);};
struct DirectionOptions {Bool flag0,flag1;float value4;Bool flag8;};
void FreePooledNode(void *);
class Path {
public:
 void rva00365E98(Object *,const Coord3D *,Int,Bool);
 void rva003649B1(const PathNode *);
 void rva00365B8A(Object *,PathNode *,PathNode *,const Coord3D *,float);
 Bool rva00365309(Object *,PathNode *,const Coord3D *,DirectionOptions *,Int,float,Bool);
 void rva00364AA2(PathNode *,PathNode *,PathNode *,float);
 void *vtable;PathNode *first,*last;Bool optimized;
};
static __forceinline const float &directionMax(const float &a,const float &b) {return a>b?a:b;}
static __forceinline const float &directionMin(const float &a,const float &b) {return a>b?b:a;}
void Path::rva00365E98(Object *obj,const Coord3D *input,Int surfaces,Bool blocked)
{
 PathNode *original=first;first=0;last=0;optimized=true;
 Coord3D direction;direction.x=input->x;direction.y=input->y;direction.z=input->z;
 float turn,segmentSpeed,fast;turn=0.0f;segmentSpeed=5.0f;
 const Rva0028AC4EEntry *entry=obj->rva0028AC4E();
 Bool reversed=false,longSegment=false;float longSpeed=5.0f;
 if(entry) {
  Rva001E46E1 *controller=(Rva001E46E1 *)entry;
  if(controller->rva001E543F(obj))turn=((Rva001E3F27FloatChaseField *)entry)->get();
  else turn=((Rva00373CAAFloatChaseField *)entry)->get();
  if(((const DirectionEntryView *)entry)->settings->wordD8) {
   Coord2D delta;float length;
   PathNode *next=(PathNode *)((Rva00363BC7 *)original)->rva00363BC7(&delta,&length);
   if(next && controller->rva001E4015(obj,&next->pos)) {
    direction.x*=-1.0f;direction.y*=-1.0f;reversed=true;direction.z*=-1.0f;
    segmentSpeed=((Rva00373CAAFloatChaseField *)entry)->get();
    fast=((Rva001E3F27FloatChaseField *)entry)->get();
    longSpeed=directionMax(fast,segmentSpeed);
    if(length>longSpeed*3.0f)longSegment=true;
   }
  }
  segmentSpeed=((Rva001E3F27FloatChaseField *)entry)->get();
 }
 PathNode *current=original->nextOptimized,*previous=original;
 if(reversed && longSegment)rva00365B8A(obj,original,current,input,longSpeed);
 else if(turn>0.0f) {
  DirectionOptions options;options.value4=turn;float radius=((const DirectionEntryView *)entry)->settings->word84;options.flag0=true;options.flag1=false;options.flag8=false;
  if(((Rva001E46E1 *)entry)->rva001E543F(obj)) {
   float lower=((const DirectionEntryView *)entry)->settings->word40;
   radius=directionMin(lower,radius);
  }
  Bool success=rva00365309(obj,original,&direction,&options,surfaces,radius,blocked);
  if(((const DirectionEntryView *)entry)->settings->mode70==8)success=true;
  if(!success) {
   options.flag1=true;
   success=rva00365309(obj,original,&direction,&options,surfaces,radius,blocked);
   if(!success) {options.flag1=success;options.value4=5.0f;}
  }
  options.flag0=false;
  rva00365309(obj,original,&direction,&options,surfaces,radius,blocked);
 } else rva003649B1(original);
 while(current) {
  PathNode *next=current->nextOptimized;
  if(next && current->portalID==0x7fffffff && next->portalID==0x7fffffff)rva00364AA2(previous,current,next,segmentSpeed);
  else rva003649B1(current);
  previous=current;current=next;
 }
 PathNode *node=original;
 do {PathNode *next=node->next;FreePooledNode(node);node=next;}while(node);
}
