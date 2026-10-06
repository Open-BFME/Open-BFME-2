// cl: /Ireference/shims/bfme2_ascii /MD /Ireference/shims/moduledata
// ??1LaserUpdateModuleData@@UAE@XZ @0x003631E8, 75B.
// Virtual dtor slot evidence: ??_G at 0x003631CC (rowed, slot 0 of vtable 0x00C17120) calls here. Destroys AsciiStrings at +0x14 then +0x0C then +0x08 via pinned 0x00036410 then restores base Snapshot vtable 0x00BBB554 with trivial base inlined (no base call). Layout from rowed ctor 0x00363147 (MuzzleParticleSystem +0x08 ParentFireBoneName +0x0C TargetParticleSystem +0x14 inline-ctor AsciiStrings, bool +0x10 float +0x18 trivial, factory news 0x1C at 0x0024D55A). Donor BFME1 LaserUpdateModuleDataDestructorThunk.
#include "Common/Snapshot.h"

#include "ascii_string.h"

class __declspec(novtable) LaserUpdateModuleData : public Snapshot
{
public:
	virtual ~LaserUpdateModuleData();

private:
	unsigned char m_pad[0x08 - 4];
	AsciiString m_muzzleParticleSystem; // +0x08
	AsciiString m_parentFireBoneName; // +0x0C
	bool m_parentFireBoneOnTurret; // +0x10
	unsigned char m_pad11[3];
	AsciiString m_targetParticleSystem; // +0x14
	float m_unk18; // +0x18
};

LaserUpdateModuleData::~LaserUpdateModuleData()
{
}
