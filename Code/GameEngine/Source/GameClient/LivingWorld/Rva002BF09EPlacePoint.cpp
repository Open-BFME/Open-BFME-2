// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native [002BF09E,002BF0D6),56B, RET4. Coordinate placement delegates
// to the separately verified duration helper [002BEDCA,002BEECB). Displacement length divided by
// manager rate1D8 and absolute scalar change divided by rate1D0 times the
// existing logic-step seconds DBA508; maximum duration clamped0..limit1DC,
// converted to frames through existing frame-rate global DBA4E8.
// Target vslots74/64 establish output-point/scalar ABIs. Original names unknown.
// BF1 WWMath vector3.h/Sqrt/Clamp supply the arithmetic implementation.
#include "Coord3D.h"
#include "wwmath.h"
#include "vector3.h"
#include <math.h>
extern int g_009BA4E8;
extern float opacityLogicStepSeconds;
class LivingWorldManager {
public:
 struct Settings {char pad[0x1bc];float rate0;char pad1c0[4];float rate1,limit;};
 char unknown00[0x14];Settings settings;
};
extern LivingWorldManager *TheLivingWorldManager;
class Rva002D3627Host {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual float slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29(Coord3D *);
 virtual float slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39(const Coord3D *,float,float,int);
 int rva002BEDCA(const Coord3D *,float);
 void rva002BF09E(const Coord3D *);
};

void Rva002D3627Host::rva002BF09E(const Coord3D *point) {
 slot39(point,slot30(),0.0f,rva002BEDCA(point,0.0f));
}
