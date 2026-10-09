// cl: /DNDEBUG /MD
//
// Five-byte wrappers whose whole retail body is one unadjusted `jmp` to an
// already-rowed body. Each name is the pin its matched callers link against
// (reverse/symbols.csv notes give the call sites); the targets are declared,
// not defined, so every jump resolves to the target's own row.
//
// Destructors: a slot-0 scalar deleting destructor calls each one, and the
// body is the base destructor's tail jump with no vptr store, so the derived
// class is novtable over the base it jumps to (the HordeGarrisonContainDtor /
// UVBufferClassDtor shape). Owner identities are not recovered.
//
//   dtor        base dtor   deleting dtor  vtable#slot
//   0x006D6340  0x006DE350  0x006CD620/0x006D71B0 (unwind 0x007A8030, 0x007AA290)
//   0x00574BA0  0x005746D2  0x00574B84     0x00C6E3CC#0
//   0x005EA85A  0x005FC1E4  0x005EA83E     0x00C781DC#0
//   0x005CC677  0x005E21EB  0x005CC65B     0x00C74E8C#0
//   0x00574338  0x005CB8D4  0x00574693     0x00C6E39C#0
//   0x005D13BD  0x005EE05E  0x005D13A1     0x00C755C0#0
//   0x005CC656  0x005E1FBC  0x005CC63A     0x00C74E70#0
//
// Methods: the same jump with the receiver and arguments passed through.
//
//   wrapper     target      caller
//   0x002710E7  0x0030AA80  0x0004C86B Drawable::setPosition -> Thing's
//   0x005C6CC7  0x005C6C89  0x00577E43
//   0x00596074  0x0025C010  0x004DF95D
//   0x0035AA3E  0x0035A1D8  GameLogic::init 0x00243EE7
//   0x0057E6D8  0x0057E6C1  0x0043DCD0
//   0x003FACE4  0x003FAC3F  0x00213AB6
//   0x004FCA0C  0x004FC9CE  0x0052BAE9
//   0x001116E2  0x00111319  W3DAptAux::PostDraw 0x000A907B
//   0x002B77AD  0x002B7582  0x0052C9F9 (ECX = TheLivingWorldLogic 0x00DFEF10)
//   0x003F0DC6  0x003F012F  0x00210D6D
//   0x006CF1B0  0x006CF040  0x002251E5 (cdecl, caller pops the int)
//
// Drawable deriving from Thing at offset 0 is carried from the Zero Hour
// donor (GameClient/Drawable.h); the unadjusted jump agrees with it.

class Rva006DE350
{
public:
	virtual ~Rva006DE350();
};

class __declspec(novtable) BfmeAptValue006DCD20 : public Rva006DE350
{
public:
	virtual ~BfmeAptValue006DCD20();
};

BfmeAptValue006DCD20::~BfmeAptValue006DCD20()
{
}

class Rva005746AF
{
public:
	virtual ~Rva005746AF();
};

class __declspec(novtable) Rva005747DA : public Rva005746AF
{
public:
	virtual ~Rva005747DA();
};

Rva005747DA::~Rva005747DA()
{
}

class Rva005FC1E4
{
public:
	virtual ~Rva005FC1E4();
};

class __declspec(novtable) Rva005EA85A : public Rva005FC1E4
{
public:
	virtual ~Rva005EA85A();
};

Rva005EA85A::~Rva005EA85A()
{
}

class Rva005E21EB
{
public:
	virtual ~Rva005E21EB();
};

class __declspec(novtable) Rva005CC677 : public Rva005E21EB
{
public:
	virtual ~Rva005CC677();
};

Rva005CC677::~Rva005CC677()
{
}

class Rva005CB8D4
{
public:
	virtual ~Rva005CB8D4();
};

class __declspec(novtable) Rva00574338 : public Rva005CB8D4
{
public:
	virtual ~Rva00574338();
};

Rva00574338::~Rva00574338()
{
}

class Rva005EE05E
{
public:
	virtual ~Rva005EE05E();
};

class __declspec(novtable) Rva005D13BD : public Rva005EE05E
{
public:
	virtual ~Rva005D13BD();
};

Rva005D13BD::~Rva005D13BD()
{
}

class Rva005E1FBC
{
public:
	virtual ~Rva005E1FBC();
};

class __declspec(novtable) Rva005CC656 : public Rva005E1FBC
{
public:
	virtual ~Rva005CC656();
};

Rva005CC656::~Rva005CC656()
{
}


// Further destructors of the same shape, each the pinned complete dtor its
// scalar deleting dtor calls (pin notes give the wrapper and vtable):
//
//   dtor        base dtor   class -> base
//   0x00368793  0x0033FF2B  AIFollowWaypointPathExactState -> Rva0033FF2B
//   0x004BB4D1  0x004B96CC  CallHelpOnDamage -> Rva004B96CC
//   0x004C2C76  0x00451F45  LevelGrantSpecialPower -> SpecialAbilityUpdate
//   0x004867F9  0x0045CE54  RebuildHoleExposeDie -> DieModule
//   0x0047E51B  0x0047BF43  RiderChangeContain -> SiegeEngineContain
//   0x000416E7  0x00238B90  Rva000416E7 -> Rva00238B90
//   0x000A43C8  0x00104E03  Rva000A43C8 -> Rva00104E03
//   0x000D089D  0x000C8BE0  Rva000D089D -> W3DModelDrawModuleData
//   0x0010F00C  0x001164F5  Rva0010F00C -> Rva001164F5
//   0x0021113D  0x003FAFB9  Rva0021113D -> Rva003FAFB9
//   0x00225A50  0x0060D0B3  Rva00225A50 -> XferSave
//   0x002563CE  0x00255A42  Rva002563CE -> UpgradeModuleData
//   0x002DB8BA  0x00131BE5  Rva002DB8BA -> Rva00131BE5
//   0x003A972D  0x003A5817  Rva003A972D -> Rva003AEEB3
//   0x003ACB6F  0x003ABC0B  Rva003ACB6F -> Rva003ABC0B
//   0x003ACB74  0x003ABC21  Rva003ACB74 -> Rva005E2D20
//   0x003ACED6  0x003AB9FF  Rva003ACED6 -> Rva003AB9FF
//   0x003ACEF7  0x003ABA4C  Rva003ACEF7 -> Rva003ABA4C
//   0x003AD273  0x003ABA36  Rva003AD273 -> Rva003ABA36
//   0x003AD2AE  0x003ABC58  Rva003AD2AE -> Rva003ABC58
//   0x003FDC41  0x003FCE38  Rva003FDC41 -> Rva003FCE38
//   0x004851A8  0x004B8CDE  Rva004851A8 -> Rva004B8CDE
//   0x00488D3B  0x004D759C  Rva00488D3B -> StateMachine
//   0x004905B0  0x0026E1FC  Rva004905B0 -> TransportAIUpdateModuleData
//   0x004C1B7B  0x004C1569  Rva004C1B7B -> RespawnBodyModuleData
//   0x004C6CC1  0x0044ECCE  Rva004C6CC1 -> Rva0044ECCE
//   0x004C70A8  0x00493DEF  Rva004C70A8 -> SpecialPowerModule
//   0x00510665  0x0050FDDC  Rva00510665 -> Rva0050FDDC
//   0x0052163E  0x003148E6  Rva0052163E -> Rva0031455E
//   0x00576803  0x005D1A42  Rva00576803 -> Rva005D1A42
//   0x0057682F  0x005D1ADE  Rva0057682F -> Rva005D1ADE
//   0x005770F2  0x005D2111  Rva005770F2 -> Rva005D2111
//   0x005CD3A5  0x005CCDDD  Rva005CD3A5 -> Rva005CCDDD
//   0x005F4EE8  0x005FD9FF  Rva005F4EE8 -> Rva005FD9FF
//   0x006F7DF0  0x006ED150  Rva006F7DC0 -> Rva006ED150
//   0x00740555  0x00141DF0  Rva00740555 -> SimpleSceneClass
class Rva0033FF2B
{
public:
	virtual ~Rva0033FF2B();
};

class __declspec(novtable) AIFollowWaypointPathExactState : public Rva0033FF2B
{
public:
	virtual ~AIFollowWaypointPathExactState();
};

AIFollowWaypointPathExactState::~AIFollowWaypointPathExactState()
{
}

class Rva004B96CC
{
public:
	virtual ~Rva004B96CC();
};

class __declspec(novtable) CallHelpOnDamage : public Rva004B96CC
{
public:
	virtual ~CallHelpOnDamage();
};

CallHelpOnDamage::~CallHelpOnDamage()
{
}

class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
};

class __declspec(novtable) LevelGrantSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual ~LevelGrantSpecialPower();
};

LevelGrantSpecialPower::~LevelGrantSpecialPower()
{
}

class DieModule
{
protected:
	virtual ~DieModule();
};

class __declspec(novtable) RebuildHoleExposeDie : public DieModule
{
public:
	virtual ~RebuildHoleExposeDie();
};

RebuildHoleExposeDie::~RebuildHoleExposeDie()
{
}

class SiegeEngineContain
{
public:
	virtual ~SiegeEngineContain();
};

class __declspec(novtable) RiderChangeContain : public SiegeEngineContain
{
public:
	virtual ~RiderChangeContain();
};

RiderChangeContain::~RiderChangeContain()
{
}

class Rva00238B90
{
public:
	virtual ~Rva00238B90();
};

class __declspec(novtable) Rva000416E7 : public Rva00238B90
{
public:
	virtual ~Rva000416E7();
};

Rva000416E7::~Rva000416E7()
{
}

class Rva00104E03
{
public:
	virtual ~Rva00104E03();
};

class __declspec(novtable) Rva000A43C8 : public Rva00104E03
{
public:
	virtual ~Rva000A43C8();
};

Rva000A43C8::~Rva000A43C8()
{
}

class W3DModelDrawModuleData
{
public:
	virtual ~W3DModelDrawModuleData();
};

class __declspec(novtable) Rva000D089D : public W3DModelDrawModuleData
{
public:
	virtual ~Rva000D089D();
};

Rva000D089D::~Rva000D089D()
{
}

class Rva001164F5
{
public:
	virtual ~Rva001164F5();
};

class __declspec(novtable) Rva0010F00C : public Rva001164F5
{
public:
	virtual ~Rva0010F00C();
};

Rva0010F00C::~Rva0010F00C()
{
}

class Rva003FAFB9
{
public:
	virtual ~Rva003FAFB9();
};

class __declspec(novtable) Rva0021113D : public Rva003FAFB9
{
public:
	virtual ~Rva0021113D();
};

Rva0021113D::~Rva0021113D()
{
}

class XferSave
{
public:
	virtual ~XferSave();
};

class __declspec(novtable) Rva00225A50 : public XferSave
{
public:
	virtual ~Rva00225A50();
};

Rva00225A50::~Rva00225A50()
{
}

class UpgradeModuleData
{
public:
	virtual ~UpgradeModuleData();
};

class __declspec(novtable) Rva002563CE : public UpgradeModuleData
{
public:
	virtual ~Rva002563CE();
};

Rva002563CE::~Rva002563CE()
{
}

class Rva00131BE5
{
public:
	virtual ~Rva00131BE5();
};

class __declspec(novtable) Rva002DB8BA : public Rva00131BE5
{
public:
	virtual ~Rva002DB8BA();
};

Rva002DB8BA::~Rva002DB8BA()
{
}

class Rva003AEEB3
{
public:
	virtual ~Rva003AEEB3();
};

class __declspec(novtable) Rva003A972D : public Rva003AEEB3
{
public:
	virtual ~Rva003A972D();
};

Rva003A972D::~Rva003A972D()
{
}

class Rva003ABC0B
{
public:
	virtual ~Rva003ABC0B();
};

class __declspec(novtable) Rva003ACB6F : public Rva003ABC0B
{
public:
	virtual ~Rva003ACB6F();
};

Rva003ACB6F::~Rva003ACB6F()
{
}

class Rva005E2D20
{
public:
	virtual ~Rva005E2D20();
};

class __declspec(novtable) Rva003ACB74 : public Rva005E2D20
{
public:
	virtual ~Rva003ACB74();
};

Rva003ACB74::~Rva003ACB74()
{
}

class Rva003AB9FF
{
public:
	virtual ~Rva003AB9FF();
};

class __declspec(novtable) Rva003ACED6 : public Rva003AB9FF
{
public:
	virtual ~Rva003ACED6();
};

Rva003ACED6::~Rva003ACED6()
{
}

class Rva003ABA4C
{
public:
	virtual ~Rva003ABA4C();
};

class __declspec(novtable) Rva003ACEF7 : public Rva003ABA4C
{
public:
	virtual ~Rva003ACEF7();
};

Rva003ACEF7::~Rva003ACEF7()
{
}

class Rva003ABA36
{
public:
	virtual ~Rva003ABA36();
};

class __declspec(novtable) Rva003AD273 : public Rva003ABA36
{
public:
	virtual ~Rva003AD273();
};

Rva003AD273::~Rva003AD273()
{
}

class Rva003ABC58
{
public:
	virtual ~Rva003ABC58();
};

class __declspec(novtable) Rva003AD2AE : public Rva003ABC58
{
public:
	virtual ~Rva003AD2AE();
};

Rva003AD2AE::~Rva003AD2AE()
{
}

class Rva003FCE38
{
public:
	virtual ~Rva003FCE38();
};

class __declspec(novtable) Rva003FDC41 : public Rva003FCE38
{
public:
	virtual ~Rva003FDC41();
};

Rva003FDC41::~Rva003FDC41()
{
}

class Rva004B8CDE
{
public:
	virtual ~Rva004B8CDE();
};

class __declspec(novtable) Rva004851A8 : public Rva004B8CDE
{
public:
	virtual ~Rva004851A8();
};

Rva004851A8::~Rva004851A8()
{
}

class StateMachine
{
public:
	virtual ~StateMachine();
};

class __declspec(novtable) Rva00488D3B : public StateMachine
{
public:
	virtual ~Rva00488D3B();
};

Rva00488D3B::~Rva00488D3B()
{
}

class TransportAIUpdateModuleData
{
public:
	virtual ~TransportAIUpdateModuleData();
};

class __declspec(novtable) Rva004905B0 : public TransportAIUpdateModuleData
{
public:
	virtual ~Rva004905B0();
};

Rva004905B0::~Rva004905B0()
{
}

class RespawnBodyModuleData
{
public:
	virtual ~RespawnBodyModuleData();
};

class __declspec(novtable) Rva004C1B7B : public RespawnBodyModuleData
{
public:
	virtual ~Rva004C1B7B();
};

Rva004C1B7B::~Rva004C1B7B()
{
}

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();
};

class __declspec(novtable) Rva004C6CC1 : public Rva0044ECCE
{
public:
	virtual ~Rva004C6CC1();
};

Rva004C6CC1::~Rva004C6CC1()
{
}

class SpecialPowerModule
{
public:
	virtual ~SpecialPowerModule();
};

class __declspec(novtable) Rva004C70A8 : public SpecialPowerModule
{
public:
	virtual ~Rva004C70A8();
};

Rva004C70A8::~Rva004C70A8()
{
}

class Rva0050FDDC
{
public:
	virtual ~Rva0050FDDC();
};

class __declspec(novtable) Rva00510665 : public Rva0050FDDC
{
public:
	virtual ~Rva00510665();
};

Rva00510665::~Rva00510665()
{
}

class Rva0031455E
{
public:
	virtual ~Rva0031455E();
};

class __declspec(novtable) Rva0052163E : public Rva0031455E
{
public:
	virtual ~Rva0052163E();
};

Rva0052163E::~Rva0052163E()
{
}

class Rva005D1A42
{
public:
	virtual ~Rva005D1A42();
};

class __declspec(novtable) Rva00576803 : public Rva005D1A42
{
public:
	virtual ~Rva00576803();
};

Rva00576803::~Rva00576803()
{
}

class Rva005D1ADE
{
public:
	virtual ~Rva005D1ADE();
};

class __declspec(novtable) Rva0057682F : public Rva005D1ADE
{
public:
	virtual ~Rva0057682F();
};

Rva0057682F::~Rva0057682F()
{
}

class Rva005D2111
{
public:
	virtual ~Rva005D2111();
};

class __declspec(novtable) Rva005770F2 : public Rva005D2111
{
public:
	virtual ~Rva005770F2();
};

Rva005770F2::~Rva005770F2()
{
}

class Rva005CCDDD
{
public:
	virtual ~Rva005CCDDD();
};

class __declspec(novtable) Rva005CD3A5 : public Rva005CCDDD
{
public:
	virtual ~Rva005CD3A5();
};

Rva005CD3A5::~Rva005CD3A5()
{
}

class Rva005FD9FF
{
public:
	virtual ~Rva005FD9FF();
};

class __declspec(novtable) Rva005F4EE8 : public Rva005FD9FF
{
public:
	virtual ~Rva005F4EE8();
};

Rva005F4EE8::~Rva005F4EE8()
{
}

class Rva006ED150
{
public:
	virtual ~Rva006ED150();
};

class __declspec(novtable) Rva006F7DC0 : public Rva006ED150
{
public:
	virtual ~Rva006F7DC0();
};

Rva006F7DC0::~Rva006F7DC0()
{
}

class SimpleSceneClass
{
public:
	virtual ~SimpleSceneClass();
};

class __declspec(novtable) Rva00740555 : public SimpleSceneClass
{
public:
	virtual ~Rva00740555();
};

Rva00740555::~Rva00740555()
{
}

struct Coord3D;

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Drawable : public Thing
{
public:
	void setPosition(const Coord3D *pos);
};

void Drawable::setPosition(const Coord3D *pos)
{
	Thing::setPosition(pos);
}

class Rva005C6C7B
{
public:
	void reset();
};

class Rva005C6CC7Call
{
public:
	void rva005C6CC7();
};

void Rva005C6CC7Call::rva005C6CC7()
{
	((Rva005C6C7B *)this)->reset();
}

class Rva0025C010
{
public:
	void rva0025C010();
};

class Rva00596074
{
public:
	void rva00596074();
};

void Rva00596074::rva00596074()
{
	((Rva0025C010 *)this)->rva0025C010();
}

class Rva0035A1D8
{
public:
	void rva0035A1D8();
};

class Rva00359E13
{
public:
	void rva0035AA3E();
};

void Rva00359E13::rva0035AA3E()
{
	((Rva0035A1D8 *)this)->rva0035A1D8();
}

class AptMpGameRules
{
public:
	void rva0057E6C1();
};

class Rva0057EE5C
{
public:
	void rva0057E6D8();
};

void Rva0057EE5C::rva0057E6D8()
{
	((AptMpGameRules *)this)->rva0057E6C1();
}

class Rva003FAC3F
{
public:
	void rva003FAC3F();
};

class Rva003FAC83
{
public:
	void rva003FACE4();
};

void Rva003FAC83::rva003FACE4()
{
	((Rva003FAC3F *)this)->rva003FAC3F();
}

class Rva0059E2FD;

class Rva004FC9CE
{
public:
	void *rva004FC9CE(const Rva0059E2FD &key);
};

class Rva0020E89C;
struct Res004FCA0C;

class Sub0052BAC1
{
public:
	Res004FCA0C *Rva004FCA0C(Rva0020E89C *key);
};

Res004FCA0C *Sub0052BAC1::Rva004FCA0C(Rva0020E89C *key)
{
	return (Res004FCA0C *)((Rva004FC9CE *)this)->rva004FC9CE(*(const Rva0059E2FD *)key);
}

class BfmeHub982
{
public:
	void bfmeBegin982C();
	void rva001116E2();
};

void BfmeHub982::rva001116E2()
{
	bfmeBegin982C();
}

class LivingWorldLogic
{
public:
	void AwardOwnershipSetsToPlayers();
};

class Rva0059E647World
{
public:
	void rva002B77AD();
};

void Rva0059E647World::rva002B77AD()
{
	((LivingWorldLogic *)this)->AwardOwnershipSetsToPlayers();
}

class Rva003F012F
{
public:
	void rva003F012F();
};

class Rva00210D6DElem
{
public:
	void rva003F0DC6();
};

void Rva00210D6DElem::rva003F0DC6()
{
	((Rva003F012F *)this)->rva003F012F();
}

void Rva006CF040Tick(unsigned int delay);

void Rva006CF1B0(int delay)
{
	Rva006CF040Tick(delay);
}
