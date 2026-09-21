// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0MissileUpdateModuleData@@QAE@XZ, retail 0x004A77B8, 149 bytes.
// ModuleData ctor over table 0xC53470 (FuelLifetime through DetonateOnNoFuel
// plus 0x118 plus exhaust string at 0x11C). Identity is the rowed MissileUpdate
// pool key 0x4A76C3 in cluster plus chained proc 0x4A74EF (opaque DumbProjectile
// base plus own table) plus factory 0x24EFA0 (news 0x120, sole caller).
// Shape: opaque EMPTY base (EBO, declared-only ctor resolving to the pin at
// 0x45B4F1, contributes no size) plus flat derived members with explicit
// void*m_vtable (no virtuals, no vtable emission). Init-list holds only the
// vtable store; the two 0x1C members construct through the shared helper
// pinned at 0x24C7B3 in decl order. The exhaust string at +0x11C has no
// declared ctor (implicit trivial, so no init store) but a declared-only dtor
// (unwindable for state 1); the body zeroes its m_data, pushes the empty
// literal early via set, stores the C4..DC ints and floats plus +0x118 in
// retail order, and calls set last (AsciiString spelling resolves through the
// alias pin at 0x55F5).

class Rva0045B4F1Base
{
public:
	Rva0045B4F1Base();
	~Rva0045B4F1Base();
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	unsigned char m_data[0x1C];
};

class AsciiString
{
public:
	AsciiString(int zero) : m_data(reinterpret_cast<void *>(zero)) {}
	~AsciiString();
	void set(const char *str);

public:
	void *m_data;
};

class MissileUpdateModuleData : public Rva0045B4F1Base
{
public:
	MissileUpdateModuleData();

private:
	const void *m_vtable; // +0 (EBO: base contributes no size)
	unsigned char m_pad04[0xC0]; // +4..+0xC3
	int m_unkC4; // +0xC4
	int m_unkC8; // +0xC8
	float m_unkCC; // +0xCC
	float m_unkD0; // +0xD0
	int m_unkD4; // +0xD4
	unsigned char m_unkD8; // +0xD8
	int m_unkDC; // +0xDC
	Rva0024C7B3Member m_unkE0; // +0xE0
	Rva0024C7B3Member m_unkFC; // +0xFC
	int m_unk118; // +0x118
	AsciiString m_exhaust; // +0x11C
};

// ??0MissileUpdateModuleData@@QAE@XZ @0x4A77B8
MissileUpdateModuleData::MissileUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C53668))
	, m_exhaust(0)
{
	m_unkC4 = 0;
	m_unkC8 = 0;
	m_unkCC = 0.0f;
	m_unkD0 = 0.0f;
	m_unkD4 = 0;
	m_unkD8 = 0;
	m_unkDC = 0;
	m_unk118 = 0;
	m_exhaust.set("");
}
