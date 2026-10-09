// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// Target identity: WB CFCF70 names ValidateLivingWorldBuildPlotWaypoints,
// and native 0023FD71..0023FED9 supplies its bound, four displacement cases,
// formatted waypoint names, and constructor call. Retail caller0024104A
// supplies the starting waypoint and LivingWorldRegion building count.
// Waypoint size C0, position C, and constructor ABI also agree with the
// already matched Waypoint owner at00282212. This BFME2 helper has no BF1
// counterpart; its actual native body, rather than donor layout, is proof.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Waypoint {
public:
    Waypoint(unsigned, AsciiString, const Coord3D *, AsciiString, AsciiString,
             AsciiString, bool, int, AsciiString);
    virtual ~Waypoint();
    char pad04[8];
    Coord3D position;
    char remainder[0xC0-0x18];
};
Waypoint *Rva00506CC3FindWaypoint(const AsciiString &);
void ValidateLivingWorldBuildPlotWaypoints(Waypoint*starting,int count){
 if(count>4)count=4;
 AsciiString name;
 for(int i=0;i<count;++i){
  name.format("Player_1_BuildPlot_%d",i+1);
  Waypoint *waypoint=Rva00506CC3FindWaypoint(name);
  if(!waypoint){
   Coord3D pos;pos.x=starting->position.x;pos.y=starting->position.y;pos.z=starting->position.z;
   switch(i%4){case 0:pos.y+=280.0f;break;case 1:pos.x+=280.0f;break;case 2:pos.y-=280.0f;break;case 3:pos.x-=280.0f;break;}
   new Waypoint(0x7FFFFFFE,name,&pos,AsciiString::TheEmptyString,AsciiString::TheEmptyString,AsciiString::TheEmptyString,false,0,AsciiString::TheEmptyString);
  }
 }
}
