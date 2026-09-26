// cl: /O1 /GX /arch:SSE /MD /DNDEBUG
//
// ??1ToggleDeploySpecialAbilityUpdateModuleData@@UAE@XZ, retail 0x004AE685,
// 82 bytes. ToggleDeploySpecialAbilityUpdate ModuleData dtor over the ctor TU
// layout ToggleDeploySpecialAbilityUpdateModuleDataCtor.cpp (pinned
// Rva0044EB54 base 0xC8 plus cleared words at +0xC8/+0xCC, factory news 0xD0,
// vtable 0x00C553D8 with slot 0 deleting dtor at 0x004AE669 calling here).
// Destroys +0xCC then +0xC8 through the rowed Release_Ref at 0x00050ED3 when
// non-null (states 1/0), then the DamageModuleBase base through the pinned
// 0x0044ECCE body (state -1). Shape follows GiveOrRestoreUpgradeSpecialPower
// ModuleDataDtor 0x004CD2E8 (novtable derived plus virtual base, no entry or
// exit vtable store) with the Bloodthirsty holder inline pattern.

class DamageModuleBase
{
public:
	virtual ~DamageModuleBase();

private:
	unsigned char m_pad[0xC8 - 4];
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct DeployRefHolder
{
	~DeployRefHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

class __declspec(novtable) ToggleDeploySpecialAbilityUpdateModuleData : public DamageModuleBase
{
public:
	virtual ~ToggleDeploySpecialAbilityUpdateModuleData();

private:
	DeployRefHolder m_holderC8; // +0xC8
	DeployRefHolder m_holderCC; // +0xCC
};

ToggleDeploySpecialAbilityUpdateModuleData::~ToggleDeploySpecialAbilityUpdateModuleData()
{
}
