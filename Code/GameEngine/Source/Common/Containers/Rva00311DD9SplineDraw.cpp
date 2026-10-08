// Retail 00311DD9/365B, Ghidra boundary; uses sibling SplineService 00311974.
// Target facts: 184B records at vector2C, endpoint A4, currentTime18, sampled result48.
// Draws first/last endpoint extensions and sampled curve in two colors, one terrain-height projection.
// Call-only views: TacticalView slot2C takes two Coord3D pointers and color;
// TerrainLogic slot18 returns ground height for (x,y,null). Global provider names retained.
// Reference lead: BF1 9cbfb551fe20 clean Find/CatmullRom siblings; no ZH Common service donor.
// Owner identity unproven; address-derived name. Derived point adapter preserves canonical Coord3D
// and the scalar copy constructor versus block assignment seen in retail. No new public class view.
// Clear first flag before terrain call, preserving retail's native scheduling.
// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
extern "C" double __cdecl fabs(double);
#include "../../../../Libraries/Include/Lib/Coord3D.h"
struct SplineRecord {float duration;float steps[10];Coord3D samples[10];Coord3D point;unsigned tail[2];};
struct SplineState {char pad[0x18];float time,segmentBegin;unsigned segment;bool enabled;char pad25[7];_STL::vector<SplineRecord> records;unsigned pad38;float sampleBegin;int sample;unsigned pad44;Coord3D result;};
class View;extern View *TheTacticalView;
struct SplineViewCalls {virtual void p00();virtual void p04();virtual void p08();virtual void p0c();virtual void p10();virtual void p14();virtual void p18();virtual void p1c();virtual void p20();virtual void p24();virtual void p28();virtual void draw(const Coord3D*,const Coord3D*,unsigned);virtual void p30();virtual void p34();virtual void p38();virtual void p3c();virtual void p40();virtual void p44();virtual void p48();virtual void p4c();virtual void p50();virtual void p54();virtual void p58();virtual void p5c();virtual void p60();virtual void p64();virtual void p68();virtual void p6c();virtual void visit(unsigned);};
class Rva0022B3F6Subsystem {public:bool rva00311974(SplineState*,bool,float*);};
extern Rva0022B3F6Subsystem *TheSplineService;
class TerrainLogic;extern TerrainLogic *TheTerrainLogic;
struct SplineTerrainCalls {virtual void p00();virtual void p04();virtual void p08();virtual void p0c();virtual void p10();virtual void p14();virtual float height(float,float,void*);};
float Rva000930C0(float,float);
struct SplineDrawPoint:Coord3D {
// ?SplineDrawPoint::SplineDrawPoint present-unmatched
__forceinline SplineDrawPoint(const Coord3D&r){x=r.x;y=r.y;z=r.z;} 
// ?SplineDrawPoint::operator= present-unmatched
__forceinline SplineDrawPoint&operator=(const Coord3D&r){*(Coord3D*)this=r;return *this;}};
class Rva00311DD9:public SplineState {public:void draw(float);};

void Rva00311DD9::draw(float input) {
 time=input-Rva000930C0(input,15.0f);
 if(records.size()<4)return;
 ((SplineViewCalls*)TheTacticalView)->draw(&records[0].point,&records[1].point,0xffffffff);
 ((SplineViewCalls*)TheTacticalView)->draw(&records[records.size()-1].point,&records[records.size()-2].point,0xffffffff);
 SplineDrawPoint previous(records[1].point);
 bool first=true;
 while(TheSplineService->rva00311974(this,0,0)) {
  time+=15.0f;
  if(!first)((SplineViewCalls*)TheTacticalView)->draw(&previous,&result,0xffff0000);
  previous=result;
  first=false;previous.z=((SplineTerrainCalls*)TheTerrainLogic)->height(previous.x,previous.y,0);
  ((SplineViewCalls*)TheTacticalView)->draw(&previous,&result,0xccdd7755);
  previous.z=result.z;
 }
}
