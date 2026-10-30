// ?exitObjectViaDoor@HordeGarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// ?exitObjectViaDoor@HordeGarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// ?exitObjectViaDoor@HordeGarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// ?exitObjectViaDoor@HordeGarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z
// cl: /I. /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?exitObjectViaDoor@HordeGarrisonContain@@UAEXPAVObject@@W4ExitDoorType@@@Z,
// retail 0x0047A14C..0x0047A251 (261 bytes, EH, RET 8): slot 2 of
// HordeGarrisonContain's exit interface (+0x30), Zero Hour's
// ExitInterface::exitObjectViaDoor. When the exiting object's +0x250 body
// hands out a horde contain (its slot 0x7C), the horde's members (slot 0x108
// list view, rowed list-return helper 0x0036AE51) leave first: every member
// not flagged at +0x454, then every member, each removed from the horde (its
// slot 0xA8) and passed to the rowed GarrisonContain::exitObjectViaDoor --
// stopping after one when the module data's +0xAC exit delay is set -- and
// finally the object itself. Without a horde the object exits directly.
// WorldBuilder's twin (0x011A8120) is unnamed.

// Keep the standard header methods inline and defer external iterator
// helpers to their existing rowed providers.
namespace _STL { struct __declspec(dllimport) _List_iterator_base; }
#include <list>
#include "../../../../Include/GameLogic/ContainmentListView.h"

typedef ContainmentList IntList;

namespace _STL
{
// Compare typed nodes directly, as the retail loop does, without emitting the
// non-retail out-of-line _List_iterator_base comparison.
template<class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }

template<> _List_base<Rva0036ADF9Element, allocator<Rva0036ADF9Element> >::~_List_base();
}

class Object;
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

class Rva0047A14CHorde;

class Rva0047A14CBody
{
public:
#define V(n) virtual void b##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30)
#undef V
	virtual Rva0047A14CHorde *slot7C();		// slot 31
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RETAIL_5D = 0x5D,
	OBJECT_STATUS_26 = 0x26
};

class Player;
class Drawable;
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
class Rva0047A14CHorde
{
public:
#define V(n) virtual void s##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41)
	virtual void slotA8(Object *member);	// slot 42
	V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65)
#undef V
	virtual Rva0036AE51ListView slot108();	// slot 66
};

class GarrisonContainModuleData
{
public:
	GarrisonContainModuleData();

private:
	unsigned char m_pad[0xAC];
};

class HordeGarrisonContainModuleData : public GarrisonContainModuleData
{
public:
	HordeGarrisonContainModuleData();

private:
	friend class HordeGarrisonContain;
	int m_exitDelay; // +0xAC
	float m_entryOffset[3]; // +0xB0
	float m_entryPosition[3]; // +0xBC
	float m_exitOffset[3]; // +0xC8
};

void HordeGarrisonContain::exitObjectViaDoor(Object *exitObj, ExitDoorType exitDoor)
{
	Object *member;
	Rva0047A14CBody *body = exitObj->m_body250;
	if (body)
	{
		const HordeGarrisonContainModuleData *data = reinterpret_cast<const HordeGarrisonContainModuleData *>(m_moduleData);
		Rva0047A14CHorde *horde = body->slot7C();
		if (horde)
		{
			IntList members = horde->slot108().rva0036AE51();
			IntList::iterator it;
			it = members.begin();
			while (it != members.end())
			{
				member = (Object *)containmentFirstWord(*it);
				if (member->m_454)
				{
					++it;
					continue;
				}
				horde->slotA8(member);
				GarrisonContain::exitObjectViaDoor(member, exitDoor);
				if (static_cast<unsigned int>(data->m_exitDelay) > 0)
					return;
				++it;
			}
			for (it = members.begin(); it != members.end(); ++it)
			{
				member = (Object *)containmentFirstWord(*it);
				horde->slotA8(member);
				GarrisonContain::exitObjectViaDoor(member, exitDoor);
				if (static_cast<unsigned int>(data->m_exitDelay) > 0)
					return;
			}
			GarrisonContain::exitObjectViaDoor(exitObj, exitDoor);
			return;
		}
	}
	GarrisonContain::exitObjectViaDoor(exitObj, exitDoor);
}
