// cl: /O1 /GX /arch:SSE /MD /DNDEBUG
//
// ??1TeleportSpecialAbilityUpdateModuleData@@UAE@XZ retail 0x00492F19 74B.
// Dtor over ctor TU layout TeleportSpecialAbilityUpdateModuleDataCtor.cpp
// vtable 0x00C4E208 strings at +0xCC/+0xD0 plus trivial Busy at +0xC8
// plus MaxDistance at +0xD4 size 0xD8 via factory 0x24DC00.
// Destroys +0xD0 then +0xCC through pinned StringBase 0x36410 states 1/0
// then base DamageModuleBase through pinned 0x44ECCE state -1.
// Shape follows GiveOrRestoreUpgradeSpecialPowerModuleDataDtor 0x4CD2E8
// 74B precedent novtable derived plus virtual base.
template<typename T> class StringBase
{
public:
	~StringBase();

private:
	void *m_data;
};

class DamageModuleBase
{
public:
	virtual ~DamageModuleBase();

private:
	unsigned char m_pad[0xC8 - 4];
};

class __declspec(novtable) TeleportSpecialAbilityUpdateModuleData : public DamageModuleBase
{
public:
	virtual ~TeleportSpecialAbilityUpdateModuleData();

private:
	int m_busyForDuration;
	StringBase<char> m_destinationWeaponName;
	StringBase<char> m_sourceWeaponName;
	float m_maxDistance;
};

// ??1TeleportSpecialAbilityUpdateModuleData@@UAE@XZ @0x00492F19
TeleportSpecialAbilityUpdateModuleData::~TeleportSpecialAbilityUpdateModuleData()
{
}
