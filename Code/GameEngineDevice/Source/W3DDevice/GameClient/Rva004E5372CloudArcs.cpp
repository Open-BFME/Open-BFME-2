// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /ICode/Libraries/Include/Lib
// Native full4E5372..4E548D sampler and4E4EA3..4E4F59 predicate.
// WB131ED90/131EF10 and rowed CloudArc::addAngle lead4E5344 establish
// linked arc nodes, center0/radius18 and two-phase angular sampling.
// Retain existing wrapper owner Rva4E54B8 and privatehelper5372 pin.
// Original manager/arc types and slot0 role remain unknown; neutral views
// describe only native center/radius and head4 accesses. Canonical Coord3D
// and native imported sin/cos/length2D; step/turn/end literals exact9digits.
// Explicit coordinate copies avoidREP_MOVSD; grouped deltas plus barrier
// retain allthreeXMM values beforestores. Local state changes before interval
// calls reproduce native schedule; fullCircle flag removes redundant floattest.
#include "Coord3D.h"
#include <math.h>
extern "C"void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva004E5344{public:void rva004E5344(float,float);Coord3D center;char unknown0C[12];float radius;};
struct CloudArcNode {CloudArcNode*next,*prev;Rva004E5344 arc;};
class Rva004E54B8{private:void helper004E5372();public:bool rva004E4EA3(Rva004E5344*,float);int word0;CloudArcNode*head;};
bool Rva004E54B8::rva004E4EA3(Rva004E5344*arc,float angle){
 Coord3D point;point.x=arc->center.x;point.y=arc->center.y;point.z=arc->center.z;
 point.x+=sin(angle)*arc->radius;
 point.y+=cos(angle)*arc->radius;
 for(CloudArcNode*node=head->next;node!=head;node=node->next){
  Rva004E5344*other=&node->arc;
  if(arc!=other){
   Coord3D delta;float dx=other->center.x-point.x;float dy=other->center.y-point.y;float dz=other->center.z-point.z;_ReadWriteBarrier();delta.x=dx;delta.y=dy;delta.z=dz;
   if(delta.GetLength2D()<=other->radius)return true;
  }
 }
 return false;
}
void Rva004E54B8::helper004E5372(){
 const float turn=6.28318548f,step=0.00981747732f;
 for(CloudArcNode*node=head->next;node!=head;node=node->next){
  Rva004E5344*arc=&node->arc;bool covered=false;float first=0.0f;
  bool fullCircle=true;
  while(first<=turn){
   bool hit=rva004E4EA3(arc,first);
   if(!covered){if(hit)covered=true;}
   else if(!hit){fullCircle=false;break;}
   first+=step;
  }
  if(fullCircle){arc->rva004E5344(0.0f,turn);continue;}
  float angle=first;float start=first;covered=false;float end=first+6.29300308f;
  for(;angle<=end;angle+=step){
   bool hit=rva004E4EA3(arc,angle);
   if(!covered){if(hit){covered=true;arc->rva004E5344(start,angle);}}
   else if(!hit){float nextStart=angle;_ReadWriteBarrier();covered=false;start=nextStart;}
  }
 }
}
