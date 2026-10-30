// cl: /O1 /DNDEBUG /MD
// ?rva00479B3A@Rva00479B3A@@QAEXPAVObject@@@Z @ 0x00479B3A (69B).
// Garrison chain plus drawable reset plus object touch. Evidence: +0x20
// GarrisonContain pinned 0x00478D0A with Object arg; Thing getDrawable row;
// Rva00270260 bool row cmp 1; Rva002716Holder 0 row; Object +0x454 byte gate
// plus Object pinned 0x0028DCC4; ret 4 single Object arg; neighbours
// VslotSmallBodiesW /O1 and HordeGarrisonContainRva00479B7F /O1.
class Object;
class Drawable;

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Thing;
class ModuleData;
class Xfer;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

enum ExitDoorType
{
	DOOR_NONE_AVAILABLE = -1
};

struct Iface00
{
	virtual ~Iface00();
	virtual void f01();
	virtual void f02();
	virtual void xfer(Xfer *xfer);
	virtual NameKeyType getModuleNameKey() const;
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f0A();
	virtual void f0B();
	virtual void f0C();
	virtual void f0D();
	virtual void f0E();
	virtual void f0F();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18(); virtual void f19(); virtual void f1A(); virtual void f1B();
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

struct Iface0C { virtual void f0C(); };

struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };

struct Iface20
{
	virtual void g00();
	virtual void g01();
	virtual void g02();
	virtual void g03();
	virtual void g04();
	virtual void g05();
	virtual void g06();
	virtual void g07();
	virtual void g08();
	virtual void g09();
	virtual void g10();
	virtual void g11();
	virtual void g12();
	virtual void g13();
	virtual void g14();
	virtual void g15();
	virtual void g16();
	virtual void g17();
	virtual void g18();
	virtual void g19();
	virtual void g20();
	virtual void g21();
	virtual void g22();
	virtual void g23();
	virtual void g24();
	virtual void g25();
	virtual void g26();
	virtual void g27();
	virtual void g28();
	virtual void g29();
	virtual void g30();
	virtual void g31();
	virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37(); virtual void g38();
	virtual void addToContain(Object *obj) = 0;
};

struct Iface24 { virtual void f24(); };

struct Iface28 { virtual void f28(); };

struct Iface2C { virtual void f2C(); };

struct Iface30
{
	virtual void f30();
	virtual void e1();
	virtual void exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor) = 0;
};

struct Iface34 { virtual void f34(); unsigned char m_pad[0x9E0 - 0x38]; };

class OpenContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
{
public:
	virtual void addToContain(Object *obj);
};

class GarrisonContain : public OpenContain
{
public:
	GarrisonContain(Thing *thing, const ModuleData *moduleData);
	virtual ~GarrisonContain();
	virtual void exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor);
	virtual void onContaining(Object *obj, bool flag);
	virtual void onRemoving(Object *obj);
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva0047A040Base9E0
{
public:
	Rva0047A040Base9E0();
	bool rva00588D24(void *a, Object *b);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *object);
	void rva00588E44(void *argument);
	void *rva00588B8A(void *key);
	int m_nextFrame; // +0x00
};

class __declspec(novtable) HordeGarrisonContain : public GarrisonContain, public Rva0047A040Base9E0
{
public:
	HordeGarrisonContain(Thing *thing, const ModuleData *moduleData);
	virtual ~HordeGarrisonContain();
	virtual NameKeyType getModuleNameKey() const;
	virtual void exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor);
	virtual void s1C(); // slot 28
	virtual void rva00479B7F(Object *obj); // slot 29
	virtual void rva00479ADA(Object *obj); // slot 30
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva00270260
{
public:
	bool rva00270260();
};

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RETAIL_5D = 0x5D,
	OBJECT_STATUS_26 = 0x26
};

class Player;
class Rva0047A14CBody;

class Rva00110ConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[8];
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	Player *getControllingPlayer() const;
	void rva0028DCC4();
	Drawable *getDrawable() const;
	void rva0028AE6D();
	char m_pad00[0x110];
	Rva00110ConditionBits m_conditionBits; // +0x110
	char m_pad130[0x120];
	Rva0047A14CBody *m_body250; // +0x250
	char m_pad254[0x200];
	unsigned char m_454; // +0x454
	char m_pad455[0x3];
};
class Rva00479B3A
{
public:
	void rva00479B3A(Object *obj);
private:
	char m_pad00[0x20];
	GarrisonContain m_20;
};

void Rva00479B3A::rva00479B3A(Object *obj)
{
	((GarrisonContain *)((char *)this + 0x20))->GarrisonContain::onRemoving(obj);
	Drawable *drawable = ((Thing *)obj)->getDrawable();
	if (drawable && ((Rva00270260 *)drawable)->rva00270260() == 1)
		drawable->setDrawableHidden(false);
	if (obj->m_454 == 0)
		obj->rva0028DCC4();
}
