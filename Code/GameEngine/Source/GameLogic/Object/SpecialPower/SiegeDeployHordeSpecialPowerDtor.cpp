// cl: /O1 /MD
//
// ??1SiegeDeployHordeSpecialPower@@UAE@XZ, retail 0x004C63EF, 39 bytes.
// Destructor for SiegeDeployHordeSpecialPower (ctor rowed at 0x004C6386 in
// SiegeDeployHordeSpecialPowerCtor.cpp, vtable 0x0085DD94 with slot 0 ??_G
// at 0x004C64B7).
//
// Donor: BFME1 SiegeDeployHordeSpecialPowerDestructorThunk.cpp names the
// virtual public dtor ??1SiegeDeployHordeSpecialPower@@UAE@XZ. The body
// restores the five vtable pointers of the complete object -- the derived
// slot at +0x00 plus secondaries at +0x0C/+0x10/+0x20/+0x24 -- then
// tail-jumps to the rowed base dtor ??1Rva00589079@@UAE@XZ at 0x00589079.
// Model follows ??1Rva00494A97@@UAE@XZ in OpaqueScalarDeletingDtors.cpp
// (same 5-store plus tail-jmp shape, fifth slot const 0xC4E900) and
// PoisonedBehaviorDtor.cpp. The base is declared only so the call resolves
// via its ledger row, and the vtable values are DIR32 auto-patches.

class Rva00589079
{
public:
	virtual ~Rva00589079();

private:
	char m_pad04[8];
};

class SiegeDeployHordeSpecialPower_S1
{
public:
	virtual void f1();
};

class SiegeDeployHordeSpecialPower_S2
{
public:
	virtual void f2();

private:
	char m_pad04[12];
};

class SiegeDeployHordeSpecialPower_S3
{
public:
	virtual void f3();
};

class SiegeDeployHordeSpecialPower_S4
{
public:
	virtual void f4();
};

class SiegeDeployHordeSpecialPower : public Rva00589079,
	public SiegeDeployHordeSpecialPower_S1,
	public SiegeDeployHordeSpecialPower_S2,
	public SiegeDeployHordeSpecialPower_S3,
	public SiegeDeployHordeSpecialPower_S4
{
public:
	virtual ~SiegeDeployHordeSpecialPower();
};

SiegeDeployHordeSpecialPower::~SiegeDeployHordeSpecialPower()
{
}
