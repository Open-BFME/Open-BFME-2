// cl: /O1 /arch:SSE /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "CurseSpecialPowerModuleData" (addModule
// pairs the name with this factory); formerly misnamed SpyVisionUpdate/SpyVisionUpdateModuleData.
// ??0CurseSpecialPowerModuleData@@QAE@XZ (0x44EB54-base family).
// Default ctor; two trailing ints plus one trailing float. Vtable hand-placed
// late (novtable) after the ints.
class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();
	virtual ~SpecialAbilityUpdateModuleData();

protected:
	unsigned char m_pad[0xC8 - 4];
};

// SpyVisionUpdate_vftable: matched references place it at VA 0xc5f778 (retail .rdata value 56).
extern "C" char SpyVisionUpdate_vftable = 56;

class __declspec(novtable) CurseSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
	CurseSpecialPowerModuleData();
	virtual ~CurseSpecialPowerModuleData();

private:
	int m_iC8;
	int m_iCC;
	float m_fD0;
};

static float kZero = 0.0f;

CurseSpecialPowerModuleData::CurseSpecialPowerModuleData()
	: SpecialAbilityUpdateModuleData()
{
	m_iC8 = 0;
	m_iCC = 0;
	*reinterpret_cast<char **>(this) = &SpyVisionUpdate_vftable;
	m_fD0 = kZero;
}

// ??1CurseSpecialPowerModuleData@@ present-unmatched
CurseSpecialPowerModuleData::~CurseSpecialPowerModuleData()
{
}
