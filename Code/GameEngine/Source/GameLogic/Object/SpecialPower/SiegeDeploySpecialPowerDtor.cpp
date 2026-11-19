// cl: /DNDEBUG /MD /EHsc
// ??1SiegeDeploySpecialPower@@UAE@XZ @0x004C57C1 84B: virtual public dtor restoring five vptrs (+0 +0C +10 +20 +24) then calling the rowed SiegeDeploy helper 0x004C573C and the rowed base ??1Rva00589079@@UAE@XZ at 0x00589079. EH prolog with state 0 around the helper then -1 for the base. Class from pool string SiegeDeploySpecialPower and ctor 0x004C56BA over WeaponModeSpecialPowerUpdateBase. Caller ??_G at 0x004C585B. Recipe SiegeDeployHordeSpecialPowerDtor 39B plus helper call with EH.

class SpecialPowerTemplate;
class Object;
struct Coord3D;
class Waypoint;
enum UpdateSleepTime;

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

// The +0x10 update interface: slot 0 of retail's table 0x00C5DCF0 is the rowed
// SiegeDeploySpecialPower::update (0x004C5E80).
class SiegeDeploySpecialPower_S2
{
public:
	virtual UpdateSleepTime update() = 0;

private:
	char m_pad04[12];
};

// The +0x20 special-power interface: slot 0 of retail's table 0x00C5DCCC is the rowed
// SiegeDeploySpecialPower::initiateIntentToDoSpecialPower (0x004C6133).
class SiegeDeploySpecialPower_S3
{
public:
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *, const Object *, const Coord3D *, unsigned int, const Waypoint *) = 0;
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
	virtual UpdateSleepTime update();	// 0x004C5E80
	virtual void initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate, const Object *targetObj, const Coord3D *targetPos, unsigned int commandOptions, const Waypoint *way);	// 0x004C6133
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

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f4@SiegeDeploySpecialPower_S4@@UAEXXZ=?eq@Rva0026A910@@QBE_NH@Z")
