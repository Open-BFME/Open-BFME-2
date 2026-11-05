// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// 0x004FF207 (135B): forwards record +0x28 to TheLivingWorldManager->+0x268's
// rowed 0x003EE980, constructs a 3D point from record +0x48, and dispatches
// TheLivingWorld slot 39 (+0x9C) with inline getters for +0x50/+0x54 and
// rowed movement duration 0x002BEDCA (WB 0x1314300 compiler-temp order).
// 0x004FF28E (50B): the Rva004FF2C0 constructor, storing vtable 0xC63B34
// plus +0x28, forwarding the strings to the rowed 0x4FBC4D base ctor and the
// army to the 0x20E449 copy ctor. Owner identities unproven.

#include "Coord3D.h"
#include "Coord2D.h"
#include "../../Include/GameLogic/LivingWorldManager.h"

struct Rva004FF207Point : Coord3D
{
	Rva004FF207Point(float xx, float yy) { x = xx; y = yy; z = 0.0f; }
	Rva004FF207Point(const Rva004FF207Point &other) { x = other.x; y = other.y; z = other.z; }
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
class LivingWorld;
extern LivingWorld *TheLivingWorld;
class Rva004FF207 {
public:
	void rva004FF207();
	float get50() const { return record->values.x; }
	float get54() const { return record->values.y; }
private:
	char unknown00[0x28];
	Rva004FF207Record *record;
};

void Rva004FF207::rva004FF207()
{
	((Rva003EE980 *)TheLivingWorldManager->field268)->rva003EE980(reinterpret_cast<int>(record));
	Rva004FF207Point point = record->point.point();
	((Rva002D3627Host *)TheLivingWorld)->slot39(&point, get50(), get54(),
		((Rva002D3627Host *)TheLivingWorld)->rva002BEDCA(&point, get54()));
}

extern "C" const void *const __identifier("??_7Rva004FF2C0@@6B@")[];  // vftable 0x00C63B34

// 0x004FBC4D is the rowed Rva004FBCBE constructor and 0x0020E449 the rowed
// Rva0020E449 copy constructor; both are called in place on raw storage.
class UnicodeString;

class Rva004FBCBE
{
public:
	Rva004FBCBE(const UnicodeString &a, const UnicodeString &b, int c);

private:
	char m_base[0x28];	// +0x00 vtable, then the base fields
};

class Rva0020E449
{
public:
	Rva0020E449(const Rva0020E449 &other);
};

// The 0x48-byte region message: its destructor 0x004FF2C0 follows, and the
// new-expression in LivingWorldLogicPlayerObserverRva002BA3F2.cpp names this
// constructor. Only the members it writes; the base view has no destructor,
// as the body unwinds nothing.
class Rva0020E89C;
class Rva003F1241;

class Rva004FF2C0 : public Rva004FBCBE
{
public:
	Rva004FF2C0(Rva0020E89C *region, Rva003F1241 *army, const UnicodeString &title, const UnicodeString &text, int arg);

private:
	Rva0020E89C *m_28;	// +0x28 region
	char m_2C[16];		// +0x2C copy target for 0x20E449
};

Rva004FF2C0::Rva004FF2C0(Rva0020E89C *region, Rva003F1241 *army, const UnicodeString &title, const UnicodeString &text, int arg)
	: Rva004FBCBE(title, text, arg)
{
	*(int *)this = ((unsigned int)__identifier("??_7Rva004FF2C0@@6B@"));
	m_28 = region;
	((Rva0020E449 *)m_2C)->Rva0020E449::Rva0020E449(*(const Rva0020E449 *)army);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
