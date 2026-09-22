// cl: /O1 /arch:SSE /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "StoreObjectsSpecialPowerModuleData" (addModule
// pairs the name with this factory); formerly misnamed SupplyCenterProductionExitUpdate/SupplyCenterProductionExitUpdateModuleData.
// ??0StoreObjectsSpecialPowerModuleData@@QAE@XZ at 0x004CD8FB.
// Default ctor over the second intermediate base 0x0044EB54 (pinned opaque
// as Rva0044EB54, 0xC8 bytes, default ctor). Single trailing float at +0xC8
// zeroed in the body (factory size 0xCC). Do NOT declare an explicit vptr
// member on the base.
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

class StoreObjectsSpecialPowerModuleData : public Rva0044EB54
{
public:
	StoreObjectsSpecialPowerModuleData();
	virtual ~StoreObjectsSpecialPowerModuleData();

private:
	float m_fC8;
};

StoreObjectsSpecialPowerModuleData::StoreObjectsSpecialPowerModuleData()
	: Rva0044EB54()
{
	m_fC8 = 0.0f;
}

// ??1StoreObjectsSpecialPowerModuleData@@ present-unmatched
StoreObjectsSpecialPowerModuleData::~StoreObjectsSpecialPowerModuleData()
{
}
