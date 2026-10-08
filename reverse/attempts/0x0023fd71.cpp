// ?ValidateLivingWorldBuildPlotWaypoints@@YAXPBURva0023FD71Start@@H@Z
// partial score=0.8 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ob2 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DNDEBUG /MD /EHsc
#include "ascii_string.h"
#include "Lib/Coord3D.h"
class Waypoint {
public:
 Waypoint(unsigned int,AsciiString,const Coord3D *,AsciiString,AsciiString,AsciiString,bool,int,AsciiString);
 char native[0xc0];
};
struct Rva0023FD71Start { char pad[12]; Coord3D position; };
Waypoint *Rva00506CC3FindWaypoint(const AsciiString &);
void ValidateLivingWorldBuildPlotWaypoints(const Rva0023FD71Start *start,int count) {
 if (count>4) count=4;
 AsciiString name;
 for (int i=0;i<count;++i) {
  name.format("Player_1_BuildPlot_%d",i+1);
  if (!Rva00506CC3FindWaypoint(name)) {
   Coord3D position;
   position.x=start->position.x; position.y=start->position.y; position.z=start->position.z;
   switch (i%4) {
    case 0: position.y+=280.0f; break;
    case 1: position.x+=280.0f; break;
    case 2: position.y-=280.0f; break;
    case 3: position.x-=280.0f; break;
   }
   new Waypoint(0x7ffffffe,name,&position,AsciiString::TheEmptyString,AsciiString::TheEmptyString,AsciiString::TheEmptyString,false,0,AsciiString::TheEmptyString);
  }
 }
}
