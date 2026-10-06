// cl: /DNDEBUG /MD /EHsc
// ??1SiegeDeploySpecialPower@@UAE@XZ @0x004C57C1 84B: virtual public dtor restoring five vptrs (+0 +0C +10 +20 +24) then calling the rowed SiegeDeploy helper 0x004C573C and the rowed base ??1Rva00589079@@UAE@XZ at 0x00589079. EH prolog with state 0 around the helper then -1 for the base. Class from pool string SiegeDeploySpecialPower and ctor 0x004C56BA over WeaponModeSpecialPowerUpdateBase. Caller ??_G at 0x004C585B. Recipe SiegeDeployHordeSpecialPowerDtor 39B plus helper call with EH.

class Rva00589079
{
public:
	virtual ~Rva00589079();

private:
	char m_pad04[8];
};

class SiegeDeploySpecialPower_S1
{
public:
	virtual void f1();
};

class SiegeDeploySpecialPower_S2
{
public:
	virtual void f2();

private:
	char m_pad04[12];
};

class SiegeDeploySpecialPower_S3
{
public:
	virtual void f3();
};

class SiegeDeploySpecialPower_S4
{
public:
	virtual void f4();
};

class SiegeDeploySpecialPower : public Rva00589079,
	public SiegeDeploySpecialPower_S1,
	public SiegeDeploySpecialPower_S2,
	public SiegeDeploySpecialPower_S3,
	public SiegeDeploySpecialPower_S4
{
public:
	virtual ~SiegeDeploySpecialPower();
	void rva004C573C();
};

SiegeDeploySpecialPower::~SiegeDeploySpecialPower()
{
	rva004C573C();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@SiegeDeploySpecialPower_S1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
