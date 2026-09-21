// ??0PickupStuffUpdateModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-21
// cl: /O1 /Oy- /GX /arch:SSE /DNDEBUG /MD
//
// Partial 0.97: 77/79 bytes; sole wall is pure-load plus setup hoist above
// the EH state arm and vtable store (retail loads float1 and leas the
// filter before and[ebp-4],0 and the vtable store; this shape sinks both).
// See re_attempts.log for the refuted matrix.

extern float g_bfmePickupScanRange;
extern float g_bfmeK1253;

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
};

class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

class PickupStuffUpdateModuleData : public EmptyBase
{
public:
	PickupStuffUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	bool m_skirmishAIOnly; // +8
	float m_scanRange; // +0xC
	Rva003623E5Filter m_stuffToPickUp; // +0x10
	float m_scanIntervalSeconds; // +0x14
};

// ??0PickupStuffUpdateModuleData@@QAE@XZ @0x491E37
PickupStuffUpdateModuleData::PickupStuffUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4DDE0))
	, m_skirmishAIOnly(true)
	, m_scanRange(g_bfmePickupScanRange)
	, m_stuffToPickUp()
{
	m_scanIntervalSeconds = g_bfmeK1253;
}
