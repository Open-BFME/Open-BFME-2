// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /ICode/Libraries/Include /ICode/GameEngine/Source/Common /Ireference/shims/bfmealloc /I. /ICode/GameEngine/Include/GameLogic
// stlport
enum NameKeyType { NAMEKEY_INVALID = 0 };
typedef unsigned int UnsignedInt;
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
#include "Lib/Coord3D.h"
#include "Lib/Coord3DBase.h"
#include "GameLogicObjectLookupView.h"
class AIUpdateInterface;
struct Rva004598F2Point
{
public:
	Rva004598F2Point() {}
	Rva004598F2Point(const Rva004598F2Point &other) : x(other.x), y(other.y), z(other.z) {}
	Rva004598F2Point(const Coord3D &o) : x(o.x), y(o.y), z(o.z) {}
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
};
struct SiegeDeployModuleDataView
{
public:
	char m_pad00[0x18];
    unsigned int m_delay; // +0x18
    unsigned int m_disabledDuration; // +0x1C
    bool m_evacuate; // +0x20
    bool m_exit; // +0x21
	bool m_noAdjust; // +0x22
	char m_pad23[0x1];
	float m_searchRadius; // +0x24 +0x24
	float m_pushDistance; // +0x28 +0x28
	float m_approachScale; // +0x2C
};
#include "../../../../Include/Common/ObjectModule.h"

class SpecialPowerTemplate;
class Waypoint;
struct BehaviorModuleInterface { virtual void f0C(); };
struct UpdateModuleInterface
{
    virtual void f10();
    virtual void u1();
    virtual void u2();
    virtual void u3();
    virtual void u4();
    virtual void u5();
    virtual void u6();
    virtual void u7();
    virtual void u8();
    virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
    virtual ~UpdateModule();
    void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
    unsigned int m_14;
    int m_18;
    int m_1C;
};
class SpecialPowerUpdateInterface
{
public:
    virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
        const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way) = 0;
    virtual void gap1();
    virtual bool rva004C575F();
};
class SpecialPowerStopInterface
{
public:
    virtual void gap0() = 0;
    virtual bool rva004C5751() = 0;
    virtual void gap2() = 0;
    virtual void gap3() = 0;
    virtual void gap4() = 0;
    virtual void gap5() = 0;
    virtual void gap6() = 0;
    virtual void gap7() = 0;
    virtual void gap8() = 0;
    virtual void gap9() = 0;
    virtual void gap10() = 0;
    virtual void gap11() = 0;
    virtual void gap12() = 0;
    virtual void gap13() = 0;
    virtual void gap14() = 0;
    virtual void gap15() = 0;
    virtual void gap16() = 0;
    virtual void stopSpecialPower() = 0;
};
class WeaponModeSpecialPowerUpdateBase : public UpdateModule,
    public SpecialPowerUpdateInterface, public SpecialPowerStopInterface
{
public:
    WeaponModeSpecialPowerUpdateBase(Thing *thing, const ModuleData *moduleData);
protected:
    unsigned int m_28;
    int m_2C;
    unsigned int m_30;
    float m_34;
};
//
// Three SiegeDeploySpecialPower overrides on the interface vtables its matched
// ctor 0x004C56BA installs over WeaponModeSpecialPowerUpdateBase: 0x00C5DCCC
// at +0x20 and 0x00C5DC68 at +0x24. Each is compiled with its subobject this.
// The deploy state int sits at +0x38 (the matched xfer saves it first; the
// unrowed setter 0x004C5BE3 compares its argument with it), the bool at +0x70.
// Names are by address.
//
// ?rva004C575F@SiegeDeploySpecialPower@@UAE_NXZ, retail 0x004C575F, 19 bytes:
// +0x20 slot 2; true unless the state is 0 or 1.
// ?rva004C5751@SiegeDeploySpecialPower@@UAE_NXZ, retail 0x004C5751, 14 bytes:
// +0x24 slot 1; the negation of +0x20 slot 2, called virtually.
// ?stopSpecialPower@SiegeDeploySpecialPower@@UAEXXZ, retail 0x004C5E41, 33 bytes:
// +0x24 slot 17; states 0/1 call the setter with 0, states 2/3 set +0x70.

class Object;
class ModuleData;













enum ObjectStatusTypes
{
	BFME_STATUS_40 = 0x40
};
enum DisabledType { DISABLED_ZERO=0 };
struct Rva0028AC4EEntry;
class SiegePhaseContain;
class AIUpdateInterface;
struct SiegePhaseConditions {unsigned words[19];__forceinline unsigned test(int i)const{return words[i>>5]&(1u<<(i&31));}__forceinline void set(int i){words[i>>5]|=1u<<(i&31);}__forceinline void clear(int i){words[i>>5]&=~(1u<<(i&31));}};
class Object
{
	friend class SiegeDeploySpecialPower;
public:
	void setStatus(ObjectStatusTypes bit, bool flag);
    void setDisabledUntil(DisabledType, unsigned);
    void rva0028AE6D();
    const Rva0028AC4EEntry *rva0028AC4E() const;
	const Rva004598F2Point *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x08];
	float m_xAxis;
	unsigned char m_pad0C[0x18 - 0x0C];
	float m_yAxis;
	unsigned char m_pad1C[0x28 - 0x1C];
	float m_zAxis;
	unsigned char m_pad2C[0x38 - 0x2C];
	Rva004598F2Point m_position;
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_pad78[0x10C - 0x78];
    SiegePhaseConditions conditions; // +0x10C
    unsigned char m_pad158[0x250 - 0x158];
    SiegePhaseContain *contain; // +0x250
    unsigned char m_pad254[4];
	AIUpdateInterface *m_ai;
protected:
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
};

class SiegeDeploySpecialPower : public WeaponModeSpecialPowerUpdateBase
{
public:
    SiegeDeploySpecialPower(Thing *thing, const ModuleData *moduleData);
    virtual ~SiegeDeploySpecialPower();
    virtual NameKeyType getModuleNameKey() const;
    virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
        const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions, const Waypoint *way);
    virtual bool rva004C575F();
    virtual bool rva004C5751();
    virtual void stopSpecialPower();
    virtual UpdateSleepTime update();
    Rva004598F2Point computeApproachPoint(Object *target, Rva004598F2Point *dockPosition, bool *docked) throw();
    void rva004C5E62();
    void rva004C573C();
private:
    void setPhase(int state);
    const SiegeDeployModuleDataView *data() const { return (const SiegeDeployModuleDataView *)m_moduleData; }
    int m_phase; // +0x38
    unsigned int m_frame; // +0x3C
    ObjectID m_dockID; // +0x40
    ObjectID m_44; // +0x44
    Coord3DBase m_48; // +0x48
    Rva004598F2Point m_approachPoint; // +0x54
    bool m_docked; // +0x60
    unsigned char m_pad61[3];
    Rva004598F2Point m_dockPosition; // +0x64
    bool m_stop; // +0x70
};

// ?rva004C575F@SiegeDeploySpecialPower@@UAE_NXZ @0x004C575F
bool SiegeDeploySpecialPower::rva004C575F()
{
	return !(m_phase == 0 || m_phase == 1);
}

// ?rva004C5751@SiegeDeploySpecialPower@@UAE_NXZ @0x004C5751
bool SiegeDeploySpecialPower::rva004C5751()
{
	return !rva004C575F();
}

// ?stopSpecialPower@SiegeDeploySpecialPower@@UAEXXZ @0x004C5E41
void SiegeDeploySpecialPower::stopSpecialPower()
{
	switch (m_phase)
	{
	case 0:
	case 1:
		setPhase(0);
		break;
	case 2:
	case 3:
		m_stop = true;
		break;
	}
}

// ?rva004C5E62@SiegeDeploySpecialPower@@QAEXXZ @0x004C5E62 30B
void SiegeDeploySpecialPower::rva004C5E62()
{
	m_object->setStatus((ObjectStatusTypes)0x40, false);
	setPhase(0);
	m_dockID = INVALID_OBJECT_ID;
}
