// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Identity: ModuleFactory registers this data class under "EntEnragedUpdate" (addModule
// pairs the name with this factory); formerly misnamed EnragedUpdateModuleData.
//
// ??0EntEnragedUpdateModuleData@@QAE@XZ, retail 0x004B249D, 104 bytes. The
// table behind the rowed buildFieldParse proc carries five Enraged fields
// plus ScanDelayTime/ScanDistance plus two ObjectFilter fields, so this is
// the Enraged behavior's module data (see EnragedBehaviorPoolKey.cpp). The
// empty UpdateModuleData base (inline-empty ctor plus declared-only dtor)
// is load-bearing for the EH state machine (ToppleUpdateModuleDataCtor
// precedent): it advances the state to 0 with no emitted code, so the
// member init is bracketed by state 0/1 exactly as retail; a standalone
// class emits only state 0. Layout past the base: explicit vtable slot at
// +0 (factory-TU precedent, assigned from the mem-init so the store leads),
// untouched word at +4, ints at +8/+0xC/+0x10, scan-distance float at +0x14,
// two filter members at +0x18/+0x1C constructed through the opaque 0x3623E5
// pin (same mangled owner as AnimationSteeringUpdateModuleDataCtor.cpp;
// that TU models 16 bytes of storage, here each slot is 4, so this TU keeps
// 4 — the pin claims only the address; the filters stay trivially
// destructible so the base alone brackets the states) and four trailing
// ints to size 0x30. Body order is load-bearing: the six integer zeros
// first (kept together so the scheduler uses one zeroed register), then
// the delay 5, then the 300.0f scan distance.

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

	unsigned char m_data[4];
};

#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class EntEnragedUpdateModuleData : public UpdateModuleData
{
public:
	EntEnragedUpdateModuleData();

private:
	const void *m_vtable; // +0
	int m_baseTail; // +4
	int m_scanDelayTime; // +8, defaults to LogicFramesPerSecond
	int m_enragedTime; // +0xC
	int m_timeUntilCanRageAgain; // +0x10
	float m_scanDistance; // +0x14
	Rva003623E5Member m_hatedFilter; // +0x18
	Rva003623E5Member m_friendlyFilter; // +0x1C
	int m_transitionTime; // +0x20
	int m_transitionFX; // +0x24
	int m_onBuffFX; // +0x28
	int m_offBuffFX; // +0x2C
};

// ??0EntEnragedUpdateModuleData@@QAE@XZ @0x4B249D
EntEnragedUpdateModuleData::EntEnragedUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C56980))
{
	m_scanDelayTime = LogicFramesPerSecond;
	m_scanDistance = 300.0f;
	m_enragedTime = 0;
	m_timeUntilCanRageAgain = 0;
	m_transitionTime = 0;
	m_transitionFX = 0;
	m_onBuffFX = 0;
	m_offBuffFX = 0;
}
