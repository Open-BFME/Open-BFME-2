// cl: /MD
//
// Destructors of 24 UpdateModule classes, each storing its three vftables at
// +0x00, +0x0C and +0x10 and tail-jumping to UpdateModule::~UpdateModule at
// 0x0024A797.
//
// Target facts: every destructor here stores the shared 0x00BEFF90 at +0x0C,
// which is UpdateModule's BehaviorModuleInterface table (slot 9 getUpdate,
// 0x002533D3), and a three-slot table at +0x10 whose slots 1 and 2 are
// UpdateModule's getDisabledTypesToProcess (0x00253376) or a class override
// and rva0044DF8D (0x0044DF8D). So each class derives from the canonical
// UpdateModule (UpdateModule.h), whose +0x0C and +0x10 interfaces those are.
// A class declares only the overrides a matched row spells under its own
// name (update, xfer; the rest of each family's overrides where its
// constructor unit's view declares them, so both units' vftable copies are
// one copy). Owner identities of the address-named classes stay unproven;
// several constructor units store their tables by name.

#include "../../Include/GameLogic/Module/UpdateModule.h"
#include "../../Include/GameLogic/Module/ObjectHelper.h"

class Rva00253E19 : public UpdateModule
{
public:
	virtual ~Rva00253E19();
};

Rva00253E19::~Rva00253E19()
{
}

class Rva00253EF5 : public UpdateModule
{
public:
	virtual ~Rva00253EF5();
};

Rva00253EF5::~Rva00253EF5()
{
}

class Rva0033EEC9 : public UpdateModule
{
public:
	virtual ~Rva0033EEC9();
};

Rva0033EEC9::~Rva0033EEC9()
{
}

// StealthUpdate (retail module class, module_factory_registrations.csv): its
// constructor 0x00374B02 stores the same three vftables (0x00817F20 at +0,
// the shared 0x007EFF90 at +0xC, 0x00817F14 at +0x10) as this destructor,
// and slot 0 of 0x00817F20 is the deleting destructor 0x00373F3D. The view
// is StealthUpdateCtor.cpp's, so the vftable copies agree.
class StealthUpdate : public UpdateModule
{
public:
	virtual ~StealthUpdate();
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

StealthUpdate::~StealthUpdate()
{
}

class Rva003A4322 : public UpdateModule
{
public:
	virtual ~Rva003A4322();

protected:
	virtual void xfer(Xfer *xfer);
};

Rva003A4322::~Rva003A4322()
{
}

class Rva003A49D1 : public UpdateModule
{
public:
	virtual ~Rva003A49D1();

protected:
	virtual void xfer(Xfer *xfer);
};

Rva003A49D1::~Rva003A49D1()
{
}

class Rva003A4CAE : public UpdateModule
{
public:
	virtual ~Rva003A4CAE();

protected:
	virtual void xfer(Xfer *xfer);
};

Rva003A4CAE::~Rva003A4CAE()
{
}

// The view of GameLogic/Object/Behavior/BuildingBehavior.cpp.
class BuildingBehavior : public UpdateModule
{
public:
	virtual ~BuildingBehavior();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

BuildingBehavior::~BuildingBehavior()
{
}

class Rva0047F92D : public UpdateModule
{
public:
	virtual ~Rva0047F92D();
};

Rva0047F92D::~Rva0047F92D()
{
}

class Rva00488338 : public UpdateModule
{
public:
	virtual ~Rva00488338();
};

Rva00488338::~Rva00488338()
{
}

class Rva0048B671 : public UpdateModule
{
public:
	virtual ~Rva0048B671();
};

Rva0048B671::~Rva0048B671()
{
}

class Rva0048D742 : public UpdateModule
{
public:
	virtual ~Rva0048D742();

protected:
	virtual void xfer(Xfer *xfer);
};

Rva0048D742::~Rva0048D742()
{
}

// The view of HeightDieUpdateCtor.cpp.
class HeightDieUpdate : public UpdateModule
{
public:
	virtual ~HeightDieUpdate();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

HeightDieUpdate::~HeightDieUpdate()
{
}

class Rva0049188D : public UpdateModule
{
public:
	virtual ~Rva0049188D();
};

Rva0049188D::~Rva0049188D()
{
}

// The view of GameLogic/Object/Update/BannerCarrierUpdate.cpp.
class BannerCarrierUpdate : public UpdateModule
{
public:
	virtual ~BannerCarrierUpdate();
	virtual UpdateSleepTime update();
	virtual NameKeyType getModuleNameKey() const;

protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

BannerCarrierUpdate::~BannerCarrierUpdate()
{
}

class Rva00499F45 : public UpdateModule
{
public:
	virtual ~Rva00499F45();

protected:
	virtual void xfer(Xfer *xfer);
};

Rva00499F45::~Rva00499F45()
{
}

// The view of AutoDepositUpdateCtor.cpp.
class AutoDepositUpdate : public UpdateModule
{
public:
	virtual ~AutoDepositUpdate();

	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

AutoDepositUpdate::~AutoDepositUpdate()
{
}

class Rva0049B2A2 : public UpdateModule
{
public:
	virtual ~Rva0049B2A2();
	virtual UpdateSleepTime update();

protected:
	virtual void xfer(Xfer *xfer);
};

Rva0049B2A2::~Rva0049B2A2()
{
}

class ProneUpdate : public UpdateModule
{
public:
	virtual ~ProneUpdate();
};

ProneUpdate::~ProneUpdate()
{
}

class Rva004A0C0E : public UpdateModule
{
public:
	virtual ~Rva004A0C0E();
};

Rva004A0C0E::~Rva004A0C0E()
{
}

class Rva004A3F8B : public UpdateModule
{
public:
	virtual ~Rva004A3F8B();

protected:
	virtual void xfer(Xfer *xfer);
};

Rva004A3F8B::~Rva004A3F8B()
{
}

class Rva004AE78E : public UpdateModule
{
public:
	virtual ~Rva004AE78E();
};

Rva004AE78E::~Rva004AE78E()
{
}

class Rva004CC63A : public UpdateModule
{
public:
	virtual ~Rva004CC63A();

protected:
	virtual void xfer(Xfer *xfer);
};

Rva004CC63A::~Rva004CC63A()
{
}

ObjectHelper::~ObjectHelper()
{
}
