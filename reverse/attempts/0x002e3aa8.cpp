// ?adjustCameraMovement@PolygonTrigger@@QAE_NPBUCoord3D@@0PAU2@_N@Z
// partial score=0.9893906110161907 date=2026-10-10
// ?adjustCameraMovement@PolygonTrigger@@QAE_NPBUCoord3D@@0PAU2@_N@Z
// partial score=0.8841387566392382 date=2026-10-09
// cl: /I. /O1 /G7  /arch:SSE /DNDEBUG /MD
// WB ABA7D0 names PolygonTrigger::adjustCameraMovement; native2E3AA8..2E3D7B
// RET16 supplies the complete723B camera constraint. BFME2 adds this method
// beyond the ZH polygon reference. Existing point queries and Line2D intersection
// provide the shared semantic spine; every algorithm branch is retail-measured.
#include "Code/Libraries/Include/Lib/Coord2D.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
struct Rva002E3A8DPair {float x;unsigned yBits;};
class Rva002E3A8DHolder {public:Rva002E3A8DPair*get(Rva002E3A8DPair*,int);};
bool IntersectLine2D(const Coord2D*,const Coord2D*,const Coord2D*,const Coord2D*,Coord2D*);
class PolygonTrigger {public:bool rva002E3A39(const Coord3D&);bool adjustCameraMovement(const Coord3D*,const Coord3D*,Coord3D*,bool);private:char prefix[8];Coord2D*begin,*end;};
#include <math.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
inline __declspec(noinline) float Coord2D::length()const{return (float)sqrt(x*x+y*y);}
inline __declspec(noinline) void Coord2D::normalize(){float len=length();if(len!=0){x/=len;y/=len;}}
bool PolygonTrigger::adjustCameraMovement(const Coord3D*from,const Coord3D*to,Coord3D*out,bool slide){
 const Coord3D*start=from;Coord2D from2,to2,delta;from2.x=start->x;from2.y=start->y;to2.x=to->x;to2.y=to->y;delta.x=to2.x-from2.x;delta.y=to2.y-from2.y;
 if(rva002E3A39(*to)){*out=*to;return true;}
 if(!rva002E3A39(*start)){*out=*start;return false;}
 Coord2D current,previous,intersection;int i=0;const int n=end-begin;
 for(;i<n;++i){((Rva002E3A8DHolder*)this)->get((Rva002E3A8DPair*)&current,i);((Rva002E3A8DHolder*)this)->get((Rva002E3A8DPair*)&previous,i?i-1:n-1);if(IntersectLine2D(&current,&previous,&from2,&to2,&intersection)){
 Coord3D candidate;
 {
  Coord2D normal;const float edgeY=previous.y-current.y;const float edgeX=previous.x-current.x;
  const float cross=(start->y-current.y)*edgeX-(start->x-current.x)*edgeY;
  normal.x=edgeY;normal.y=0.0f-edgeX;normal.normalize();
  if(cross>0.0f){normal.x*=-1.0f;normal.y*=-1.0f;}
  candidate.x=normal.x*0.1f+intersection.x;candidate.y=normal.y*0.1f+intersection.y;candidate.z=0.0f;
 }
 if(!rva002E3A39(candidate)){*out=*start;return false;}
 if(slide){
  Coord3D along;along.x=previous.x-current.x;along.y=previous.y-current.y;along.z=0.0f;
  if((*(const volatile float*)&delta.x)*along.x+(*(const volatile float*)&delta.y)*along.y<0.0f){along.x*=-1.0f;along.y*=-1.0f;along.z*=-1.0f;}
  float remaining=delta.length();{Coord3D used;used.x=candidate.x-start->x;used.y=candidate.y-start->y;used.z=0.0f-start->z;remaining-=used.length();}
  if(remaining>0.1f){remaining*=0.4f;along.normalize();float x=(*(const volatile float*)&remaining)*along.x;_ReadWriteBarrier();float z=(*(const volatile float*)&along.z)*remaining;float bx=(*(const volatile float*)&candidate.x);float y=(*(const volatile float*)&remaining)*along.y;Coord3D next;next.x=bx+x;next.y=(*(const volatile float*)&candidate.y)+y;next.z=z;if(rva002E3A39(next))candidate=next;}
 }
 *out=candidate;return true;
 }}
 return false;
}

