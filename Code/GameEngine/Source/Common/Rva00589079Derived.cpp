// cl: /MD
//
// Opaque five-vptr MI destructor tail-calling the pinned 0x24A797 base.
// Retail 0x00589079 (39B) stores four vptrs plus the const 0xC70108 at +0x24,
// then tail-jumps to the 0x24A797 middle. Same model as the landed Rva00494A97
// body (which tail-calls this one); the fifth slot carries a const, not a
// zero. Identity unproven (opaque Rva name); the shape (vptr stores plus a
// tail-jump into a rowed/pinned MI dtor) is the dtor evidence.

class Xfer;

// The ObjectModule and BehaviorModuleInterface vptrs of UpdateModule: retail
// names these classes' leading vftables ??_7<class>@@6BObjectModule@@@ and
// ??_7<class>@@6BBehaviorModuleInterface@@@ (data ledger 0x008497B4 and
// 0x008496F8 for FireWeaponWhenDeadBehavior), as its ctor unit emits them.
// Every BehaviorModuleInterface vftable of these classes holds the empty
// default 0x004D43D0 in slot 0 (the getBody binding of the UpdateModule dtor
// units).
class Thing;
class ModuleData;

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);

private:
	char m_pad04[8];
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
};

class UpdateModule : public BehaviorModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
};

class Rva00589079_S2
{
public:
	virtual void f2() = 0;

private:
	char m_pad04[12];
};

class Rva00589079_S3
{
public:
	virtual void f3();
};

class Rva00589079_S4
{
public:
	virtual void f4();
};

class Rva00589079 : public UpdateModule, public Rva00589079_S2, public Rva00589079_S3, public Rva00589079_S4
{
public:
	virtual ~Rva00589079()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00589079_Anchor(Rva00589079 *p)
{
	p->Rva00589079::~Rva00589079();
}

class Rva00481F82_S2
{
public:
	virtual void f2();

private:
	char m_pad04[12];
};

class Rva00481F82_S3
{
public:
	virtual void f3();
};

class Rva00481F82_S4
{
public:
	virtual void f4();
};

class Rva00481F82 : public UpdateModule, public Rva00481F82_S2, public Rva00481F82_S3, public Rva00481F82_S4
{
public:
	virtual ~Rva00481F82()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00481F82_Anchor(Rva00481F82 *p)
{
	p->Rva00481F82::~Rva00481F82();
}

class Rva00482E96_S2
{
public:
	virtual void f2();

private:
	char m_pad04[12];
};

class Rva00482E96_S3
{
public:
	virtual void f3();

private:
	char m_pad18[4];
};

class Rva00482E96_S4
{
public:
	virtual void f4();
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};



class FireWeaponWhenDeadBehavior;

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class UpgradeMux
{
	friend class FireWeaponWhenDeadBehavior;
protected:
	virtual void upgradeMuxXfer(Xfer *xfer);
};

class Member2C
{
public:
	virtual void xfer(Xfer *xfer);
};

class FireWeaponWhenDeadBehavior : public UpdateModule, public Rva00482E96_S2, public Rva00482E96_S3, public Rva00482E96_S4
{
public:
	virtual ~FireWeaponWhenDeadBehavior()
	{
	}
	virtual void loadPostProcess();
	virtual void s02();
protected:
	virtual void xfer(Xfer *xfer);
public:
	// Slot 4 of vtable 0x008497B4 (0x00482E51, rowed in FireWeaponWhenDeadBehaviorPoolKey.cpp),
	// as FireWeaponWhenDeadBehavior.cpp declares it: both units emit this vtable and must
	// emit the same copy.
	virtual NameKeyType getModuleNameKey() const;
private:
	Member2C m_m2C;
	char m_pad30[0x78];
	int m_iA8;
};

template <typename T> class StringBase
{
	friend class FireWeaponWhenDeadBehavior;
	void validate() const;
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void Rva00482E96_Anchor(FireWeaponWhenDeadBehavior *p)
{
	p->FireWeaponWhenDeadBehavior::~FireWeaponWhenDeadBehavior();
}

// ?loadPostProcess@FireWeaponWhenDeadBehavior@@UAEXXZ retail 0x00482C39 17 bytes.
// Slot 1 (offset 0x4) of vtable 0x008497B4 (class of ??1Rva00482E96@@UAE@XZ).
// Validates wide strings at +0 and +0x20, second as tail-jmp to rowed
// ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0. No other callees.
// Honest address name: identity is class+slot only (opaque Rva).
void FireWeaponWhenDeadBehavior::loadPostProcess()
{
	((StringBase<unsigned short>*)this)->validate();
	((StringBase<unsigned short>*)((char*)this + 0x20))->validate();
}

void FireWeaponWhenDeadBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	if (version.m_minimum >= 2)
		((UpdateModule *)this)->UpdateModule::xfer(xfer);
	else
		((BehaviorModule *)this)->BehaviorModule::xfer(xfer);
	((UpgradeMux *)((char *)this + 0x20))->UpgradeMux::upgradeMuxXfer(xfer);
	if (version.m_minimum >= 3) {
		m_m2C.xfer(xfer);
		*xfer == m_iA8;
	}
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f4@Rva00481F82_S4@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?f3@Rva00482E96_S3@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?s02@FireWeaponWhenDeadBehavior@@UAEXXZ=?Rva00482E4BGet@@YAHXZ")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f2@Rva00481F82_S2@@UAEXXZ=?update@TerrainResourceBehavior@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva00482E96_S2@@UAEXXZ=?update@Rva00482BB9@@QAEHXZ")
#pragma comment(linker, "/alternatename:?f3@Rva00481F82_S3@@UAEXXZ=?rva00482152@Rva00482152@@UAEXH@Z")
#pragma comment(linker, "/alternatename:?f3@Rva00589079_S3@@UAEXXZ=?Set_Animation@RenderObjClass@@UAEXPAVHAnimClass@@M0MM@Z")
#pragma comment(linker, "/alternatename:?f4@Rva00482E96_S4@@UAEXXZ=?onDie@FireWeaponWhenDeadBehavior@@UAEXPBVDamageInfo@@@Z")
#pragma comment(linker, "/alternatename:?f4@Rva00589079_S4@@UAEXXZ=?eq@Rva0026A910@@QBE_NH@Z")
