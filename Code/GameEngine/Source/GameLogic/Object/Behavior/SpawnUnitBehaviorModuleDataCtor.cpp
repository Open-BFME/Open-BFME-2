// cl: /O1 /GX /DNDEBUG /MD /arch:SSE

// ??0SpawnUnitBehaviorModuleData@@QAE@XZ, retail 0x0025598C (101 bytes).
// The module-data half of SpawnUnitBehavior: vtable 0x00BF36C0, UnitName
// string@8 plus UnitCommand string@C (both set to "" via rowed StringBase
// set 0x55F5), unused int@10 plus unused floats@14/@18, SpawnOnce flag@1C.
// Field identity is retail's own INI table at 0x00C59238 (landed
// buildFieldParse row: UnitName plus UnitCommand plus SpawnOnce with
// SpawnOnce at 0x1C per BFME1 SpawnUnitBehavior) joined to the rowed
// SpawnUnitBehavior poolkey 0x4B8752 in the same cluster plus factory
// 0x2559F1 news 0x20 sole caller plus rowed proc 0x4B8840. The empty
// UpdateModuleData base (inline-empty ctor plus declared-only dtor) is
// load-bearing for the EH state machine (Bloodthirsty precedent): it
// brackets states 0/2 exactly as retail (AsciiString pair plus array-free
// stores need no extra states). /arch:SSE for movss float zeroing (DemoTrap
// precedent: x87 fldz otherwise).

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0)
	{
	}
	~StringBase();
	void set(const char *str);

private:
	void *m_data;
};

typedef StringBase<char> AsciiString;

class UpdateModuleData
{
public:
	UpdateModuleData()
	{
	}
	~UpdateModuleData();
};

class SpawnUnitBehaviorModuleData : public UpdateModuleData
{
public:
	SpawnUnitBehaviorModuleData();

private:
	const void *m_vtable;
	unsigned int m_unused04;
	AsciiString m_unitName;
	AsciiString m_unitCommand;
	unsigned int m_unused10;
	float m_unused14;
	float m_unused18;
	bool m_spawnOnce;
};

// ??0SpawnUnitBehaviorModuleData@@QAE@XZ @0x25598C
SpawnUnitBehaviorModuleData::SpawnUnitBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00BF36C0))
{
	m_unitName.set("");
	m_unitCommand.set("");
	m_unused10 = 0;
	m_unused14 = 0.0f;
	m_unused18 = 0.0f;
	m_spawnOnce = false;
}
