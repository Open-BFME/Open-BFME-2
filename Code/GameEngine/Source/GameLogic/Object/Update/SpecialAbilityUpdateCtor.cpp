// cl: /O1 /arch:SSE /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "TeleportToCasterSpecialPowerModuleData" (addModule
// pairs the name with this factory); formerly misnamed SpecialAbilityUpdate/SpecialAbilityUpdateModuleData.
// ??0TeleportToCasterSpecialPowerModuleData@@QAE@XZ at 0x004CD34E.
// Default ctor over the second intermediate base 0x0044EB54 (pinned opaque
// as Rva0044EB54, 0xC8 bytes). Trailing floats zeroed plus two trailing ints
// (factory size 0xDC).
class Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();

protected:
	unsigned char m_pad[0xC8 - 4];
};

// ??1Rva0044EB54@@ present-unmatched
Rva0044EB54::~Rva0044EB54()
{
}

class TeleportToCasterSpecialPowerModuleData : public Rva0044EB54
{
public:
	TeleportToCasterSpecialPowerModuleData();
	virtual ~TeleportToCasterSpecialPowerModuleData();

private:
	float m_fC8;
	float m_fCC;
	float m_fD0;
	int m_iD4;
	int m_iD8;
};

TeleportToCasterSpecialPowerModuleData::TeleportToCasterSpecialPowerModuleData()
	: Rva0044EB54()
{
	m_iD4 = 0;
	m_iD8 = 0;
	m_fC8 = 0.0f;
	m_fCC = 0.0f;
	m_fD0 = 0.0f;
}

// ??1TeleportToCasterSpecialPowerModuleData@@ present-unmatched
TeleportToCasterSpecialPowerModuleData::~TeleportToCasterSpecialPowerModuleData()
{
}
