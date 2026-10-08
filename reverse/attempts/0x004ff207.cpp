// ?d_004ff207@@YAXXZ
// partial score=0.86 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 004FF207..004FF28E, 135B, RET0. The receiver forwards its
// record +28 to the rowed manager helper, then uses the record's XY and
// two floats in a camera-like singleton's four-word virtual slot +9C.
// Original receiver, method and record names remain unknown.
#include "Coord3D.h"
#include "Coord2D.h"

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
	char unknown00[0x268];
	Rva003EE980 *member268;
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
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
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

void Rva004FF207::rva004FF207()
{
	TheLivingWorldManager->member268->rva003EE980(reinterpret_cast<int>(record));
	Rva004FF207Point point = record->point.point();
	Coord2D values = record->values;
	g_00DFEF18->slot39(&point, values.x, values.y,
		g_00DFEF18->rva002BEDCA(&point, record->values.y));
}
