// cl: /GX /MD /DNDEBUG
// Rva0044ECCE is an address-derived base stand-in; its target class name is unproven.
//
// ??1GiveOrRestoreUpgradeSpecialPowerModuleData@@UAE@XZ, retail 0x004CD2E8, 74 bytes.
// Dtor over ctor TU layout (vtable 0x00C5F900, strings at +0xC8/+0xCC, toggle
// bitset at +0xD0 trivial): destroys +0xCC then +0xC8 through pinned
// ??1StringBase@D at 0x36410 (states 1/0), then base Rva0044ECCE through
// pinned ??1 at 0x44ECCE (state -1). Shape follows LevelGrant precedent
// (novtable derived plus virtual base).

template<typename T> class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();

private:
	unsigned char m_pad[0xC8 - 4];
};

class __declspec(novtable) GiveOrRestoreUpgradeSpecialPowerModuleData : public Rva0044ECCE
{
public:
	virtual ~GiveOrRestoreUpgradeSpecialPowerModuleData();

private:
	StringBase<char> m_commandButtonC8;
	StringBase<char> m_upgradeToGiveCC;
	unsigned char m_toggleD0[0x10];
};

// ??1GiveOrRestoreUpgradeSpecialPowerModuleData@@UAE@XZ @0x004CD2E8
GiveOrRestoreUpgradeSpecialPowerModuleData::~GiveOrRestoreUpgradeSpecialPowerModuleData()
{
}
