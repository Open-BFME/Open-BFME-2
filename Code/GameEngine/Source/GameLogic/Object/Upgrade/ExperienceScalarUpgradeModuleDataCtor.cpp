// cl: /O1 /MD /GX- /DNDEBUG /arch:SSE
//
// ??0ExperienceScalarUpgradeModuleData@@QAE@XZ, retail 0x004B6187, 29 bytes.
// Frameless store-only ctor over the rowed OpenContainModuleData base
// (0x253487): folded vtable 0x00BF2558 and AddXPScalar float-zero at +0x118
// (xorps plus movss; own table 0x00858524 holds exactly AddXPScalar at
// +0x118; the rowed ExperienceScalarUpgrade pool key at 0x4B6142 ends where
// this ctor begins; this ctor ends where the proc begins; the EH factory
// at 0x25042E news 0x11C and is the only raw caller). Recipe:
// MaxHealthUpgradeModuleDataCtor (explicit vtable slot in body order);
// /arch:SSE for the float-zero store.

class OpenContainModuleData
{
public:
	OpenContainModuleData();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class ExperienceScalarUpgradeModuleData : public OpenContainModuleData
{
public:
	ExperienceScalarUpgradeModuleData();

private:
	float m_addXPScalar; // +0x118
};

// ??0ExperienceScalarUpgradeModuleData@@QAE@XZ @0x4B6187
ExperienceScalarUpgradeModuleData::ExperienceScalarUpgradeModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00BF2558);
	m_addXPScalar = 0.0f;
}
