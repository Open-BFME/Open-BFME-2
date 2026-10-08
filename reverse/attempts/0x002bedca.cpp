// ?rva002BEDCA@Rva002D3627Host@@QAEHPBUCoord3D@@M@Z
// partial score=0.8 date=2026-10-07
// ?d_004ff207@@YAXXZ
// partial score=0.86 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native 004FF207..004FF28E, 135B, RET0. The receiver forwards its
// record +28 to the rowed manager helper, then uses the record's XY and
// two floats in a camera-like singleton's four-word virtual slot +9C.
// Original receiver, method and record names remain unknown.
#include "Coord3D.h"
#include "Coord2D.h"
#include "wwmath.h"
#include <math.h>
extern int g_009BA4E8;

struct Rva004FF207Point : Coord3D
{
    Rva004FF207Point(float xx, float yy) { x=xx; y=yy; z=0.0f; }
    Rva004FF207Point(const Rva004FF207Point &v) { x=v.x; y=v.y; z=v.z; }
};
struct Rva004FF207Pair : Coord2D
{
    Rva004FF207Point point() const { return Rva004FF207Point(x, y); }
};

struct Rva004FF207Record {
	char unknown00[0x48];
	Rva004FF207Pair point;
	Coord2D values;
};
class Rva003EE980 { public: void rva003EE980(int); };
class LivingWorldManager {
public:
	struct Settings {char pad[0x1bc];float rate0;char pad1c0[4];float rate1,limit;};char unknown00[0x14];Settings settings;char pad1e0[0x88];Rva003EE980 *member268;
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
	virtual void slot29(Coord3D*);
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39(const Coord3D *, float, float, int);
	int rva002BEDCA(const Coord3D *, float);
};
extern Rva002D3627Host *g_00DFEF18;
class Rva004FF207 {
public:
	void rva004FF207();
private:
	char unknown00[0x28];
	Rva004FF207Record *record;
};

int Rva002D3627Host::rva002BEDCA(const Coord3D *target,float value) {
 Coord3D current; slot29(&current);
 float x=current.x-target->x,y=current.y-target->y,z=current.z-target->z;
 float distance=WWMath::Sqrt(z*z+y*y+x*x)/TheLivingWorldManager->settings.rate1;
 const LivingWorldManager::Settings &settings=TheLivingWorldManager->settings;
 float magnitude=(float)fabs((double)(slot25()-value));float change=magnitude/settings.rate0*0.03333333507180214f;
 const float &longer=change>distance ? change:distance;
 float time=WWMath::Clamp(longer,0.0f,settings.limit);
 return (int)((double)g_009BA4E8*time);
}
