// ?rva0028B98B@Object@@QAEXXZ
// partial score=0.55 date=2026-10-07
// cl: /ICode/Libraries/Include /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
#include "Lib/Coord3D.h"
class Object;
struct Rva002ED236Position : Coord3D {
 Rva002ED236Position(float a,float b,float c) {x=a;y=b;z=c;}
 Rva002ED236Position(const Rva002ED236Position &p) {x=p.x;y=p.y;z=p.z;}
};
class Pathfinder {public:int rva002ED236(Object *,Rva002ED236Position);};
class AI;
extern AI *TheAI;
struct Rva0028B98BAI {char opaque[0x10];Pathfinder *pathfinder;};
class GameLogic {public:char opaque[0x40];unsigned int frame;};
extern GameLogic *TheGameLogic;
class Object {
 char opaque00[0x38];Coord3D position;char opaque44[0x48c-0x44];
 bool pending;char opaque48d[3];unsigned int cachedFrame;
public:void rva0028B98B();
};
void Object::rva0028B98B() {
 if(pending && cachedFrame+13<=TheGameLogic->frame) {
  Rva0028B98BAI *ai=(Rva0028B98BAI *)TheAI;
  if(ai->pathfinder->rva002ED236(this,Rva002ED236Position(position.x,position.y,position.z))==1) {
   cachedFrame=(unsigned int)-1;
   pending=false;
  }
 }
}
