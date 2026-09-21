// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Identity: ModuleFactory registers this data class under "EvacuateDamage" (addModule
// pairs the name with this factory); formerly misnamed PanicUpdateModuleData.
//
// ??0EvacuateDamageModuleData@@QAE@XZ, retail 0x004BAD10, 84 bytes. The table
// behind the rowed buildFieldParse proc tracks an evacuation weapon plus a
// damage type plus a panic threshold plus a tracking span, so this is the
// panic-on-damage behavior's module data. The empty UpdateModuleData base
// (inline-empty ctor plus declared-only dtor) is load-bearing for the EH
// state machine (ToppleUpdateModuleDataCtor precedent): it advances the
// state to 0 with no emitted code, so the member init is bracketed by state
// 0/1 exactly as retail. Layout: explicit vtable slot at +0 (factory-TU
// precedent, assigned from the mem-init so the store leads), untouched word
// at +4, evacuation-weapon string at +8 (inline default ctor plus
// declared-only clear and dtor per the Topple precedent; clear reaches the
// rowed 0x36410 clear fold), tracked damage type at +0xC defaulting to 3,
// panic threshold at +0x10 defaulting to 0.1f and tracking span at +0x14
// defaulting to 6. Size 0x18 matches the free 0x250E4B factory news.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class EvacuateDamageModuleData : public UpdateModuleData
{
public:
	EvacuateDamageModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	AsciiString m_evacuationWeapon; // +8
	int m_damageTypeToTrack; // +0xC
	float m_panicThreshold; // +0x10
	int m_trackingTimeSpan; // +0x14
};

// ??0EvacuateDamageModuleData@@QAE@XZ @0x4BAD10
EvacuateDamageModuleData::EvacuateDamageModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C59CF8))
	, m_evacuationWeapon()
{
	m_evacuationWeapon.clear();
	m_damageTypeToTrack = 3;
	m_panicThreshold = 0.1f;
	m_trackingTimeSpan = 6;
}
