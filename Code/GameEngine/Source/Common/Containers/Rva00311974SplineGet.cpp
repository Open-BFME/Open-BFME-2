// Retail Ghidra boundary 00311974..00311B70 (508B); callers 00311DD9/00375A73.
// GameEngine init 0022F47E names TheSplineService and its address-derived owner.
// The service ignores incoming this; explicit state pointer, byte flag and optional float*.
// Target facts: state time18/segmentBegin1C/index20/enabled24; vector2C, padding38,
// sampleBegin3C/sampleIndex40, padding44, output48; records184 with ten duration/sample pairs.
// BF1 9cbfb551fe20 clean Rva003A2270Find and CatmullRom003A14C0 are subsystem leads.
// No corresponding clean ZH Common spline service exists; this interpolation is target reconstruction.
// Function purpose and field roles are inferred from retail arithmetic, loops and consumer use.
// Call-only view of TheTacticalView slots; target slot70 receives the record's B4 word.
// Split guards before the inline active routine preserve retail's early false return paths.
// Explicit float locals around the double CRT fabs calls retain retail's x87 temporary stores.
// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
extern "C" double __cdecl fabs(double);
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct SplineRecord {float duration;float steps[10];Coord3D samples[10];Coord3D point;unsigned tail[2];};
struct SplineState {char pad[0x18];float time,segmentBegin;unsigned segment;bool enabled;char pad25[7];_STL::vector<SplineRecord> records;unsigned pad38;float sampleBegin;int sample;unsigned pad44;Coord3D result;};
class View;extern View *TheTacticalView;
struct SplineViewCalls {virtual void p00();virtual void p04();virtual void p08();virtual void p0c();virtual void p10();virtual void p14();virtual void p18();virtual void p1c();virtual void p20();virtual void p24();virtual void p28();virtual void p2c();virtual void p30();virtual void p34();virtual void p38();virtual void p3c();virtual void p40();virtual void p44();virtual void p48();virtual void p4c();virtual void p50();virtual void p54();virtual void p58();virtual void p5c();virtual void p60();virtual void p64();virtual void p68();virtual void p6c();virtual void visit(unsigned);};
class Rva0022B3F6Subsystem {public:bool rva00311974(SplineState*,bool,float*);};
// ?splineGetActive present-unmatched
static __forceinline bool splineGetActive(SplineState *s,bool notify,float *out) {
 while(s->time-s->segmentBegin>=s->records[s->segment].duration) {
  if(notify)((SplineViewCalls*)TheTacticalView)->visit(s->records[s->segment+2].tail[1]);
  s->segmentBegin+=s->records[s->segment].duration;
  s->sample=0;s->sampleBegin=0.0f;++s->segment;
  if(s->segment+3>s->records.size())return false;
 }
 float t=s->time-s->segmentBegin-s->sampleBegin;
 float dt=s->records[s->segment].steps[s->sample];
 while(t>=dt) {
  s->sampleBegin+=dt;++s->sample;t-=dt;dt=s->records[s->segment].steps[s->sample];
 }
 float duration=dt;
 float fraction=t/duration;
 if(!(duration>0.0f))fraction=1.0f;
 Coord3D p0,p1;
 if(s->sample>0)p0=s->records[s->segment].samples[s->sample-1];else p0=s->records[s->segment+1].point;
 p1=s->records[s->segment].samples[s->sample];
 Coord3D p;
 p.x=p0.x+(p1.x-p0.x)*fraction;p.y=p0.y+(p1.y-p0.y)*fraction;p.z=p0.z+(p1.z-p0.z)*fraction;
 s->result=p;
 if(out) {float a=s->records[s->segment].steps[0],b=s->records[s->segment].steps[9],time=s->time;float first=(float)fabs(a-time);float second=(float)fabs(b-time);*out=(float)fabs(first-second);}
 return true;
}

bool Rva0022B3F6Subsystem::rva00311974(SplineState *s,bool notify,float *out) {
if(!s->enabled)return false;if(!s->records.size())return false;return splineGetActive(s,notify,out);
}
