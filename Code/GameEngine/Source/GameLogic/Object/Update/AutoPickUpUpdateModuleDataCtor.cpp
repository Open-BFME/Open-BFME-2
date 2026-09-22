// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0AutoPickUpUpdateModuleData@@QAE@XZ, retail 0x00496308, 151 bytes.
// Auto-pickup behavior data: the own table at 0x00C4F4B8 carries
// ScanDelayTime at +8, PickUpFilter at +0xC, ScanDistance at +0x10,
// EatObjectEntry at +0x14, AutoThrowObject at +0x20, RunFromButton at
// +0x21, RunFromButtonNumber at +0x24 and CanScanWhileAttackingOrMoving at
// +0x28, matching every store below; the ModuleData factory at 0x24E099
// news 0x2C and the pool key at 0x495CEC ends where the parse proc begins.
// Shape follows EnragedUpdateModuleDataCtor (empty UpdateModuleData base
// with inline-empty ctor plus declared-only dtor arms the EH states with
// no code, explicit vtable assigned from the mem-init so the store leads)
// plus RespawnUpdateModuleDataCtor (two 28B FixedStorage temps
// copy-constructed in place from the prototype at 0x00DFEFA4 through the
// rowed copy ctor, consumed by value through the 0x362087 pin). The
// EatObjectEntry vector at +0x14 builds through the 0x211E58 fold; its
// element type is unproven, so the TU keeps the BfmeE16 stand-in
// (fold-equivalent and byte-correct, BattlePlanUpdate precedent) and the
// row carries the identity.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class AutoPickUpUpdateModuleData : public UpdateModuleData
{
public:
	AutoPickUpUpdateModuleData();

private:
	const void *m_vtable; // +0
	int m_unused04; // +4
	int m_scanDelayTime; // +8
	Rva003623E5Member m_pickUpFilter; // +0xC
	float m_scanDistance; // +0x10
	_STL::vector<BfmeE16> m_eatObjectEntries; // +0x14, element unproven
	unsigned char m_autoThrowObject; // +0x20
	unsigned char m_runFromButton; // +0x21
	unsigned char m_pad22[2]; // +0x22
	int m_runFromButtonNumber; // +0x24
	unsigned char m_canScanWhileAttackingOrMoving; // +0x28
	unsigned char m_tail[3]; // +0x29..+0x2B, factory news 0x2C
};

// ??0AutoPickUpUpdateModuleData@@QAE@XZ @0x496308
AutoPickUpUpdateModuleData::AutoPickUpUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4F108))
	, m_scanDelayTime(LogicFramesPerSecond)
	, m_scanDistance(300.0f)
{
	m_runFromButtonNumber = 0;
	m_autoThrowObject = 0;
	m_runFromButton = 0;
	m_canScanWhileAttackingOrMoving = 0;
	m_pickUpFilter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
