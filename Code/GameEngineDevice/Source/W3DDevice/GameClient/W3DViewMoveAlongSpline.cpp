// Native89ED4..8A0E5 (529B) and WB998EC0 independently name this
// BFME2 extension to the reference W3DView path controller. GeneralsMD
// moveAlongWaypointPath supplies elapsed/ease/distance/constraint semantics;
// BFME1 revision874e38488c7d and rowed spline service311974 are subsystem leads.
// Target proves the two state prefixes22F4/2368,184B sample stride, endpoint
// record(size-2),24 validation gate,45 completion,46 initial wait and result48.
// State tail byte68 in the second member is native freeze23D0. Its other
// tail fields remain opaque; no role is asserted beyond witnessed accesses.
// Existing service's state prefix is preserved; native client slot70 is the
// endpoint notification. Explicit three-scalar point construction supplies
// native SSE loads before its12B copy. Inline reference-argument expansion
// preserves separate bound stores instead of merging destination addresses.
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Include/Lib
// stlport
#include "Coord3D.h"
#include "Coord2D.h"
struct ViewBounds {Coord2D lo,hi;};
struct SplinePoint:public Coord3D {__forceinline SplinePoint(float a,float b,float c){x=a;y=b;z=c;}};
#include <vector>
__forceinline void expand(float &lo,float &hi,float x){if(x<lo)lo=x;else if(x>hi)hi=x;}
class ParabolicEase {public:float operator()(float)const;float in,out;};
struct SplineRecord {float duration;float steps[10];Coord3D samples[10];Coord3D point;unsigned tail[2];};
struct SplineState {
 void *vptr;int total,elapsed,wait;ParabolicEase ease;
 float time,segmentBegin;unsigned segment;bool enabled;char pad25[7];
 std::vector<SplineRecord> records;float distance;float sampleBegin;int sample;
 char byte44;bool finished,waiting;char byte47;Coord3D result;
 char pad54[0x68-0x54];bool byte68;char pad69[3];int word6c,word70;
};
class Rva0022B3F6Subsystem {public:bool rva00311974(SplineState*,bool,float*);};
extern Rva0022B3F6Subsystem *TheSplineService;
class GlobalData {public:char pad[0x9a4];bool disabled;};
extern GlobalData *TheWritableGlobalData;
class W3DView {public:
virtual void slot000();
virtual void slot004();
virtual void slot008();
virtual void slot00C();
virtual void slot010();
virtual void slot014();
virtual void slot018();
virtual void slot01C();
virtual void slot020();
virtual void slot024();
virtual void slot028();
virtual void slot02C();
virtual void slot030();
virtual void slot034();
virtual void slot038();
virtual void slot03C();
virtual void slot040();
virtual void slot044();
virtual void slot048();
virtual void slot04C();
virtual void slot050();
virtual void slot054();
virtual void slot058();
virtual void slot05C();
virtual void slot060();
virtual void slot064();
virtual void slot068();
virtual void slot06C();
virtual void setCameraLock(unsigned);
 private:
 char pad04[8];Coord3D m_pos;char pad18[0x22f4-0x18];SplineState camera,locator;
 char pad23dc[0x240c-0x23dc];ViewBounds bounds;
 char pad241c[0x244c-0x241c];Coord3D locatorPos;
 void moveCameraOrLocatorAlongSplinePath(int,bool);
};
void W3DView::moveCameraOrLocatorAlongSplinePath(int milliseconds,bool useLocator){
 SplineState *info=useLocator?&locator:&camera;
 if(!info->enabled)return;
 float oldTime=(float)info->elapsed;
 info->elapsed+=milliseconds;
 if(TheWritableGlobalData->disabled){
  if(info->elapsed>info->total)locator.byte68=false;
  return;
 }
 if(info->elapsed>info->total){
  if(!useLocator&&!info->finished)setCameraLock(info->records[info->records.size()-2].tail[1]);
  locator.byte68=false;
  const Coord3D &end=info->records[info->records.size()-2].point;
  SplinePoint pos(end.x,end.y,end.z);
  if(useLocator)locatorPos=pos;
  else{
   m_pos=pos;
   expand(bounds.lo.x,bounds.hi.x,pos.x); expand(bounds.lo.y,bounds.hi.y,pos.y);
  }
  if(!info->finished)info->finished=true;
  info->elapsed-=milliseconds;
  oldTime=(float)info->elapsed;
 }
 float reciprocal=1.0f/info->total;
 float delta=info->ease(info->elapsed*reciprocal)-info->ease(oldTime*reciprocal);
 info->time+=delta*info->distance;
 if(info->waiting){info->time=0.0f;if(info->elapsed>info->wait){info->waiting=false;info->elapsed=0;}}
 if(!info->finished)TheSplineService->rva00311974(info,!useLocator,0);
 if(useLocator)locatorPos=info->result;else m_pos=info->result;
}
