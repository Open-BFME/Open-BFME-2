// cl: /MD
//
// Opaque multiple-inheritance destructors tail-calling UpdateModule::~
// UpdateModule at 0x0024A797 (pinned opaque MI base: three vptrs tail-jumping
// the 0x49B47C fold; identity unproven). Each class below derives (in order)
// from the opaque base, a shared empty polymorphic base, and its own empty
// polymorphic base, giving vptrs at +0x00/+0x0C/+0x10; the empty bases have
// implicit trivial destructors, so the derived destructor stores all three
// vptrs and tail-calls the base destructor. The +0x0C secondary is shared
// across the family (0xBEFF90). Owner identities are unproven (opaque Rva
// names). One ledger row per destructor, landed one commit at a time.

class UpdateModule
{
public:
	virtual ~UpdateModule();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva00253E19_B2
{
public:
	virtual void f2();
};

class Rva00253E19 : public UpdateModule, public MiBase1, public Rva00253E19_B2
{
public:
	virtual ~Rva00253E19();
};

Rva00253E19::~Rva00253E19()
{
}

class Rva00253EF5_B2
{
public:
	virtual void f2();
};

class Rva00253EF5 : public UpdateModule, public MiBase1, public Rva00253EF5_B2
{
public:
	virtual ~Rva00253EF5();
};

Rva00253EF5::~Rva00253EF5()
{
}

class Rva0033EEC9_B2
{
public:
	virtual void f2();
};

class Rva0033EEC9 : public UpdateModule, public MiBase1, public Rva0033EEC9_B2
{
public:
	virtual ~Rva0033EEC9();
};

Rva0033EEC9::~Rva0033EEC9()
{
}

class Rva00373CB1_B2
{
public:
	virtual void f2();
};

// StealthUpdate (retail module class, module_factory_registrations.csv): its
// constructor 0x00374B02 stores the same three vftables (0x00817F20 at +0,
// the shared 0x007EFF90 at +0xC, 0x00817F14 at +0x10) as this destructor,
// and slot 0 of 0x00817F20 is the deleting destructor 0x00373F3D.
class StealthUpdate : public UpdateModule, public MiBase1, public Rva00373CB1_B2
{
public:
	virtual ~StealthUpdate();
};

StealthUpdate::~StealthUpdate()
{
}

class Rva003A4322_B2
{
public:
	virtual void f2();
};

class Rva003A4322 : public UpdateModule, public MiBase1, public Rva003A4322_B2
{
public:
	virtual ~Rva003A4322();
};

Rva003A4322::~Rva003A4322()
{
}

class Rva003A49D1_B2
{
public:
	virtual void f2();
};

class Rva003A49D1 : public UpdateModule, public MiBase1, public Rva003A49D1_B2
{
public:
	virtual ~Rva003A49D1();
};

Rva003A49D1::~Rva003A49D1()
{
}

class Rva003A4CAE_B2
{
public:
	virtual void f2();
};

class Rva003A4CAE : public UpdateModule, public MiBase1, public Rva003A4CAE_B2
{
public:
	virtual ~Rva003A4CAE();
};

Rva003A4CAE::~Rva003A4CAE()
{
}

class Rva004561A2_B2
{
public:
	virtual void f2();
};

class BuildingBehavior : public UpdateModule, public MiBase1, public Rva004561A2_B2
{
public:
	virtual ~BuildingBehavior();
};

BuildingBehavior::~BuildingBehavior()
{
}

class Rva0047F92D_B2
{
public:
	virtual void f2();
};

class Rva0047F92D : public UpdateModule, public MiBase1, public Rva0047F92D_B2
{
public:
	virtual ~Rva0047F92D();
};

Rva0047F92D::~Rva0047F92D()
{
}



class Rva00488338_B2
{
public:
	virtual void f2();
};

class Rva00488338 : public UpdateModule, public MiBase1, public Rva00488338_B2
{
public:
	virtual ~Rva00488338();
};

Rva00488338::~Rva00488338()
{
}

class Rva0048B671_B2
{
public:
	virtual void f2();
};

class Rva0048B671 : public UpdateModule, public MiBase1, public Rva0048B671_B2
{
public:
	virtual ~Rva0048B671();
};

Rva0048B671::~Rva0048B671()
{
}

class Rva0048D742_B2
{
public:
	virtual void f2();
};

class Rva0048D742 : public UpdateModule, public MiBase1, public Rva0048D742_B2
{
public:
	virtual ~Rva0048D742();
};

Rva0048D742::~Rva0048D742()
{
}

class Rva0048FBBA_B2
{
public:
	virtual void f2();
};

class HeightDieUpdate : public UpdateModule, public MiBase1, public Rva0048FBBA_B2
{
public:
	virtual ~HeightDieUpdate();
};

HeightDieUpdate::~HeightDieUpdate()
{
}

class Rva0049188D_B2
{
public:
	virtual void f2();
};

class Rva0049188D : public UpdateModule, public MiBase1, public Rva0049188D_B2
{
public:
	virtual ~Rva0049188D();
};

Rva0049188D::~Rva0049188D()
{
}







class Rva004969FF_B2
{
public:
	virtual void f2();
};

class Rva004969FF : public UpdateModule, public MiBase1, public Rva004969FF_B2
{
public:
	virtual ~Rva004969FF();
};

Rva004969FF::~Rva004969FF()
{
}

class Rva00499F45_B2
{
public:
	virtual void f2();
};

class Rva00499F45 : public UpdateModule, public MiBase1, public Rva00499F45_B2
{
public:
	virtual ~Rva00499F45();
};

Rva00499F45::~Rva00499F45()
{
}

class Rva0049A1AB_B2
{
public:
	virtual void f2();
};

class AutoDepositUpdate : public UpdateModule, public MiBase1, public Rva0049A1AB_B2
{
public:
	virtual ~AutoDepositUpdate();
};

AutoDepositUpdate::~AutoDepositUpdate()
{
}

class Rva0049B2A2_B2
{
public:
	virtual void f2();
};

class Rva0049B2A2 : public UpdateModule, public MiBase1, public Rva0049B2A2_B2
{
public:
	virtual ~Rva0049B2A2();
};

Rva0049B2A2::~Rva0049B2A2()
{
}

class Rva0049FE7B_B2
{
public:
	virtual void f2();
};

class Rva0049FE7B : public UpdateModule, public MiBase1, public Rva0049FE7B_B2
{
public:
	virtual ~Rva0049FE7B();
};

Rva0049FE7B::~Rva0049FE7B()
{
}

class Rva004A0C0E_B2
{
public:
	virtual void f2();
};

class Rva004A0C0E : public UpdateModule, public MiBase1, public Rva004A0C0E_B2
{
public:
	virtual ~Rva004A0C0E();
};

Rva004A0C0E::~Rva004A0C0E()
{
}

class Rva004A3F8B_B2
{
public:
	virtual void f2();
};

class Rva004A3F8B : public UpdateModule, public MiBase1, public Rva004A3F8B_B2
{
public:
	virtual ~Rva004A3F8B();
};

Rva004A3F8B::~Rva004A3F8B()
{
}

class Rva004AE78E_B2
{
public:
	virtual void f2();
};

class Rva004AE78E : public UpdateModule, public MiBase1, public Rva004AE78E_B2
{
public:
	virtual ~Rva004AE78E();
};

Rva004AE78E::~Rva004AE78E()
{
}

// EntEnragedUpdate: its constructor 0x004B2516 stores the same three vftables
// (0x00856948 at +0, the shared 0x007EFF90 at +0xC, 0x0085693C at +0x10) that
// this destructor stores; slot 0 of 0x0085693C is the rowed
// EntEnragedUpdate::update. The +0x10 interface is the one-slot view
// EntEnragedUpdateCtorThunk.cpp uses, so the shared vftable copies agree.
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };





class Rva004CC63A_B2
{
public:
	virtual void f2();
};

class Rva004CC63A : public UpdateModule, public MiBase1, public Rva004CC63A_B2
{
public:
	virtual ~Rva004CC63A();
};

Rva004CC63A::~Rva004CC63A()
{
}

class Rva004DF7C2_B2
{
public:
	virtual void f2();
};

class ObjectHelper : public UpdateModule, public MiBase1, public Rva004DF7C2_B2
{
public:
	virtual ~ObjectHelper();
};

ObjectHelper::~ObjectHelper()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2@Rva0033EEC9_B2@@UAEXXZ=?update@ProjectileStreamUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva00486E18_B2@@UAEXXZ=?Rva004A6563Get@@YAHXZ")
#pragma comment(linker, "/alternatename:?f2@Rva00488338_B2@@UAEXXZ=?update@DeletionUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0049FE7B_B2@@UAEXXZ=?update@ProneUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004A0C0E_B2@@UAEXXZ=?update@RadarUpdate@@UAE?AW4UpdateSleepTime@@XZ")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f2@Rva00253E19_B2@@UAEXXZ=?update@Rva004CED4BUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva00253EF5_B2@@UAEXXZ=?update@NotifyTargetsOfImminentProbableCrushingUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva00373CB1_B2@@UAEXXZ=?update@StealthUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva003A4322_B2@@UAEXXZ=?update@Rva003A4322_B2@@QAEHXZ")
#pragma comment(linker, "/alternatename:?f2@Rva003A49D1_B2@@UAEXXZ=?update@LifetimeUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva003A4CAE_B2@@UAEXXZ=?update@StrafeAreaUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004561A2_B2@@UAEXXZ=?update@BuildingBehavior@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0047F92D_B2@@UAEXXZ=?update@CivilianSpawnUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0048B671_B2@@UAEXXZ=?update@FireSpreadUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0048D742_B2@@UAEXXZ=?update@FloatUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0048FBBA_B2@@UAEXXZ=?update@HeightDieUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0049188D_B2@@UAEXXZ=?update@AttachUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva00491DD3_B2@@UAEXXZ=?update@PickupStuffUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0049506E_B2@@UAEXXZ=?update@AutoFindHealingUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva00495916_B2@@UAEXXZ=?update@DemoTrapUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004969FF_B2@@UAEXXZ=?update@BannerCarrierUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva00499F45_B2@@UAEXXZ=?update@SpecialEnemySenseUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0049A1AB_B2@@UAEXXZ=?update@AutoDepositUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva0049B2A2_B2@@UAEXXZ=?update@Rva0049B2A2@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004A3F8B_B2@@UAEXXZ=?update@HijackerUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004AE78E_B2@@UAEXXZ=?update@DetachableRiderUpdateUpdateReceiver@@QAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004B89C4_B2@@UAEXXZ=?update@OathbreakersFadeAwayBehavior@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004CC63A_B2@@UAEXXZ=?update@TemporarilyDefectUpdate@@UAE?AW4UpdateSleepTime@@XZ")
#pragma comment(linker, "/alternatename:?f2@Rva004DF7C2_B2@@UAEXXZ=__purecall")
