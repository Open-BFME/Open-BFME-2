// ?continueMoving@LivingWorldArmyIcon@@QAEXPAVCoord2D@@@Z
// partial score=0.75 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE  /ICode/Libraries/Include/Lib
#include "Coord2D.h"
extern "C" double __cdecl sqrt(double);
class Rva003FE13E {public:float rva003FE13E();};
class Rva003FE1DBOwner {public:void rva003FE1DB();};
class LivingWorldArmyIcon {
public:void continueMoving(Coord2D *);
private:char unknown0[0x18];Coord2D current;char unknown20[0x30];Coord2D destination;
};
// Complete native229B RET4 and WB1074010 establish this movement step;
// existing speed helper3FE13E and queue-advance52B3FE1DB keep their opaque names.
void LivingWorldArmyIcon::continueMoving(Coord2D *out) {
 Coord2D d;
 d.x=destination.x-current.x;
 d.y=destination.y-current.y;
 float squared=d.x*d.x+d.y*d.y;
 if(squared>0.001) {
  float inverse=1.0f/(float)sqrt(squared);
  d.x*=inverse;d.y*=inverse;
 }
 float step=((Rva003FE13E*)this)->rva003FE13E();
 d.x*=step;d.y*=step;
 out->x=d.x+current.x;out->y=d.y+current.y;
 d.x=destination.x;d.y=destination.y;
 d.x-=out->x;d.y-=out->y;
 if(d.length()<1.0f) ((Rva003FE1DBOwner*)this)->rva003FE1DB();
}


