// cl: /MD
//
// Destructors of six AIUpdateInterface modules, each tail-calling
// AIUpdateInterface::~AIUpdateInterface at 0x0026E836 (rowed in
// AIUpdateInterfaceDestructor.cpp: five vptrs at +0x00/+0x0C/+0x10/+0x20/+0x24
// plus member cleanup). The base is modelled here with its five-vptr shape
// (root plus four secondaries, the +0x10 one carrying 12 bytes of opaque data
// so the layout reaches +0x20); each class below derives from it and
// overrides every vptr before tail-calling the base destructor. The base
// destructor is only declared here, because a same-TU definition would
// capture the call locally instead of at the ledger address. Vtable values
// are DIR32 auto-patches. One ledger row per destructor.
//
// Identities (target facts): each destructor stores the same root vftable as
// the rowed constructor of its class, and slot 0 of that vftable is the
// scalar deleting destructor that calls it (all six classes are retail module
// classes in module_factory_registrations.csv):
//   AnimalAIUpdate            dtor 0x0047EB78, ctor 0x0047ECA8, vftable 0x00C47B98
//   AssaultTransportAIUpdate  dtor 0x0048F3E0, ctor 0x0048F5A3, vftable 0x00C4CCA0
//   SiegeAIUpdate             dtor 0x00490544, ctor 0x00490506, vftable 0x00C4D330
//   HordeAIUpdate             dtor 0x0049A64B, ctor 0x0049A7F3, vftable 0x00C505F8
//   TransportAIUpdate         dtor 0x004A9080, ctor 0x004A9042, vftable 0x00C53AA8
//   WanderAIUpdate            dtor 0x004A935D, ctor 0x004A931F, vftable 0x00C53D30
// Slot 0 of each secondary vftable is the modelled virtual: update (+0x10),
// aiDoCommand (+0x20) and onCollide (+0x24), overridden where the class's
// own vftable holds its own rowed body (AnimalAIUpdate, AssaultTransportAIUpdate,
// HordeAIUpdate and WanderAIUpdate update at 0x0047EDC9/0x0048F828/0x0049AB10/
// 0x004A9424; AssaultTransportAIUpdate and HordeAIUpdate aiDoCommand at
// 0x0048F7A7/0x0049A9A9) and AIUpdateInterface's otherwise (0x0026E267,
// 0x002673F6, 0x0026DF0D). The three with a +0x3E4 interface store its
// vftable last: 0x00C47B84 (slot 0 0x0047EC5F), 0x00C4CC88 (slot 0
// beginAssault 0x0048F45C) and the Horde dock table 0x00C50868.

// Same complete secondary-interface table installed by both Horde constructors.
// The existing data-row owner supplies its twenty verified function entries.
extern const void *const g_00C50868[];

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

struct AICommandParms;
struct Coord3D;
class Object;

class Rva0026E836_Root
{
public:
	virtual ~Rva0026E836_Root();

private:
	char m_pad04[8];
};

class Rva0026E836_M1
{
public:
	virtual void f1();
};

class Rva0026E836_B2
{
public:
	virtual UpdateSleepTime update();

private:
	char m_pad08[12];
};

class Rva0026E836_M3
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
};

class Rva0026E836_M4
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
	virtual bool wouldLikeToCollideWith(const Object *other) const { return false; }
	virtual bool slot02() const { return false; }
	virtual bool slot03() const { return false; }
	virtual bool slot04() const { return false; }
	virtual bool isSalvageCrateCollide() const { return false; }
};

class AIUpdateInterface : public Rva0026E836_Root, public Rva0026E836_M1, public Rva0026E836_B2, public Rva0026E836_M3, public Rva0026E836_M4
{
public:
	virtual UpdateSleepTime update();
	virtual void aiDoCommand(const AICommandParms *parms);
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);

protected:
	virtual ~AIUpdateInterface();

	char m_pad0028[0x3E4 - 0x28];
};

class SiegeAIUpdate : public AIUpdateInterface
{
public:
	virtual ~SiegeAIUpdate();
};

SiegeAIUpdate::~SiegeAIUpdate()
{
}

class TransportAIUpdate : public AIUpdateInterface
{
public:
	virtual ~TransportAIUpdate();
};

TransportAIUpdate::~TransportAIUpdate()
{
}

class WanderAIUpdate : public AIUpdateInterface
{
public:
	virtual ~WanderAIUpdate();
	virtual UpdateSleepTime update();
};

WanderAIUpdate::~WanderAIUpdate()
{
}

// The +0x3E4 interface's one slot reads a byte of the module data; its name
// is not established, hence the address name.
#include "../../Include/Common/Rva0047EB78_Interface3E4.h"

class AnimalAIUpdate : public AIUpdateInterface, public Rva0047EB78_Interface3E4
{
public:
	virtual ~AnimalAIUpdate();
	virtual UpdateSleepTime update();
	virtual unsigned char rva0047EC5F() const;
};

AnimalAIUpdate::~AnimalAIUpdate()
{
}

class AssaultTransportAIInterface
{
public:
	virtual void beginAssault(const Object *designatedTarget) const = 0;
};

class AssaultTransportAIUpdate : public AIUpdateInterface, public AssaultTransportAIInterface
{
public:
	virtual ~AssaultTransportAIUpdate();
	virtual void aiDoCommand(const AICommandParms *parms);
	virtual UpdateSleepTime update();
	virtual void beginAssault(const Object *designatedTarget) const;
};

AssaultTransportAIUpdate::~AssaultTransportAIUpdate()
{
}

class HordeAIUpdate : public AIUpdateInterface
{
public:
	virtual ~HordeAIUpdate();
	virtual void aiDoCommand(const AICommandParms *parms);
	virtual UpdateSleepTime update();

private:
	const void *m_extra03E4;
};

HordeAIUpdate::~HordeAIUpdate()
{
	m_extra03E4 = g_00C50868;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva0026E836_M1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
