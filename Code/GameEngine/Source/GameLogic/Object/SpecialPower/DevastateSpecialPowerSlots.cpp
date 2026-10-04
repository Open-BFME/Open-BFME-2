// cl: /O1 /DNDEBUG /MD
//
// Two DevastateSpecialPower overrides on the special-power interface vtable
// 0x00C5E430 its matched ctor 0x004C81E3 installs at +0x10, compiled with that
// subobject this. Names are by address.
//
// ?rva004C822C@DevastateSpecialPower@@UAEXH@Z, retail 0x004C822C, 68 bytes:
// slot 10 (the argument unread); the untargeted use only reports "Error!
// Devastate Power requires either a target object or location" through the
// Debug singleton (the GameLODManagerGetAudioLODIndex.cpp reporting shape).
// ?rva004C82D1@DevastateSpecialPower@@UAEXPAVObject@@H@Z, retail 0x004C82D1,
// 20 bytes: slot 11; slot 12 at the target Object's position (+0x38) with the
// same second argument.

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad000[0x38];
	Coord3D m_position; // +0x38
};

class Debug
{
public:
	static Bool SkipNext(Bool skip);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(Int report);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug *slot6C(Int first, Int second, Int third);
};
extern Debug *theDebug;

Bool bfmeRva000387C0(void);

class ModuleData;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
struct BehaviorModuleInterface { virtual void f0C(); };

class SpecialPowerModuleInterface
{
public:
	virtual void gap0() = 0; virtual void gap1() = 0; virtual void gap2() = 0; virtual void gap3() = 0;
	virtual void gap4() = 0; virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0;
	virtual void gap8() = 0; virtual void gap9() = 0;
	virtual void rva004C822C(int options) = 0;
	virtual void rva004C82D1(Object *target, int options) = 0;
	virtual void slot12(const Coord3D *pos, int options) = 0;
};

class SpecialPowerModule : public BehaviorModule, public BehaviorModuleInterface, public SpecialPowerModuleInterface
{
};

class DevastateSpecialPower : public SpecialPowerModule
{
public:
	virtual void rva004C822C(int options);
	virtual void rva004C82D1(Object *target, int options);
};

// ?rva004C822C@DevastateSpecialPower@@UAEXH@Z @0x004C822C
void DevastateSpecialPower::rva004C822C(int)
{
	if (bfmeRva000387C0())
	{
		Debug::SkipNext(true);
		theDebug->slot60();
		theDebug->slot6C(0, 0, 0)->slot38("Error! Devastate Power requires either a target object or location").slot4C(2);
	}
}

// ?rva004C82D1@DevastateSpecialPower@@UAEXPAVObject@@H@Z @0x004C82D1
void DevastateSpecialPower::rva004C82D1(Object *target, int options)
{
	slot12(target->getPosition(), options);
}
