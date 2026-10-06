// cl: /Ireference/shims/bfme2_ascii /MD
// ??1DeployStyleAIUpdateModuleData@@UAE@XZ @0x00255F70, 53B.
// Virtual dtor slot evidence: ??_G at 0x00255F54 (rowed, slot 0 of vtable 0x00BF3440) calls here. Destroys AsciiString at +0x70 via pinned 0x00036410 then base TransportAIUpdateModuleData via pinned 0x0026E1FC. Layout from rowed ctor 0x00255154 (base 0x64, UnpackTime +0x64 PackTime +0x68 turret bools +0x6C-0x6F modifier +0x70, factory news 0x74 at 0x0025517E). Donor BFME1 DeployStyleAIUpdateModuleDataDestructorThunk (different Transport-based layout in BFME2, follow retail).
#include "ascii_string.h"

class __declspec(novtable) TransportAIUpdateModuleData
{
public:
	TransportAIUpdateModuleData();
	virtual ~TransportAIUpdateModuleData();

private:
	unsigned char m_pad[0x64 - 4];
};

class __declspec(novtable) DeployStyleAIUpdateModuleData : public TransportAIUpdateModuleData
{
public:
	virtual ~DeployStyleAIUpdateModuleData();

private:
	int m_unpackTime; // +0x64
	int m_packTime; // +0x68
	bool m_resetTurretBeforePacking; // +0x6C
	bool m_turretsFunctionOnlyWhenDeployed; // +0x6D
	bool m_turretsMustCenterBeforePacking; // +0x6E
	bool m_mustDeployToAttack; // +0x6F
	AsciiString m_deployedAttributeModifier; // +0x70
};

DeployStyleAIUpdateModuleData::~DeployStyleAIUpdateModuleData()
{
}
