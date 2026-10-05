// cl: /O1 /arch:SSE /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "CombineHordeSpecialPowerModuleData" (addModule
// pairs the name with this factory); formerly misnamed AIUpdateInterface.
// Trial: ??0CombineHordeSpecialPowerModuleData@@QAE@XZ.
// Default ctor over opaque intermediate base 0x004930A0 (pinned); vtable
// plus one trailing float. Factory stub order names it.
class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

protected:
	unsigned char m_pad0[0x7C - 4];
	float m_f7C;
};

class CombineHordeSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	CombineHordeSpecialPowerModuleData();
	virtual ~CombineHordeSpecialPowerModuleData();

};

static float kF7C = 0.0f;

CombineHordeSpecialPowerModuleData::CombineHordeSpecialPowerModuleData()
	: SpecialPowerModuleData()
{
	m_f7C = kF7C;
}

// ??1CombineHordeSpecialPowerModuleData@@ present-unmatched
CombineHordeSpecialPowerModuleData::~CombineHordeSpecialPowerModuleData()
{
}
