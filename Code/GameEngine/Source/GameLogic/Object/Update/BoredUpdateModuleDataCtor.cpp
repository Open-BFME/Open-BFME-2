// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0BoredUpdateModuleData@@QAE@XZ, retail 0x004966FE, 130 bytes.
// Bored behavior data: the own table at 0x00C4F4E8 carries ScanDelayTime
// at +8, ScanDistance at +0xC, BoredFilter at +0x10,
// CanScanWhileAttackingOrMoving at +0x14 and SpecialPowerTemplate at
// +0x18, matching every store below; the ModuleData factory at 0x24E122
// news 0x1C and the pool key at 0x4966B9 ends where this ctor starts.
// Shape follows AutoPickUpUpdateModuleDataCtor (landed 151/151: empty
// UpdateModuleData base with inline-empty ctor plus declared-only dtor
// arms the EH states with no code, explicit vtable assigned from the
// mem-init so the store leads, two 28B FixedStorage temps
// copy-constructed in place from the prototype at 0x00DFEFA4 through the
// rowed copy ctor, consumed by value through the 0x362087 pin), minus the
// vector, so the states drop 0->2 to 0->1. Retail runs the filter call
// first, so only the vtable is init-listed; the scan stores live in the
// body with their loads hoisted above the temp setup.

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class BoredUpdateModuleData : public UpdateModuleData
{
public:
	BoredUpdateModuleData();

private:
	const void *m_vtable; // +0
	int m_unused04; // +4
	int m_scanDelayTime; // +8
	float m_scanDistance; // +0xC
	Rva003623E5Member m_boredFilter; // +0x10
	unsigned char m_canScanWhileAttackingOrMoving; // +0x14
	unsigned char m_pad15[3]; // +0x15
	int m_specialPowerTemplate; // +0x18
};

// ??0BoredUpdateModuleData@@QAE@XZ @0x4966FE
BoredUpdateModuleData::BoredUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4F590))
{
	m_scanDelayTime = LogicFramesPerSecond;
	m_scanDistance = 300.0f;
	m_boredFilter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
	m_specialPowerTemplate = 0;
	m_canScanWhileAttackingOrMoving = 0;
}
