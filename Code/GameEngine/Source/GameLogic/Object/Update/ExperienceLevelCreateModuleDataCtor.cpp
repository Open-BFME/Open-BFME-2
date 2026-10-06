// cl: /DNDEBUG /MD
//
// ??0ExperienceLevelCreateModuleData@@QAE@XZ, retail 0x004B9220, 17 bytes.
// Trivial frameless ctor: or -1 into +8 first, then the vtable literal,
// then false at +0xC. Table 0xC595B4 holds LevelToGrant@8 MPOnly@C; factory
// 0x250BCA news 0x10. Flat TU-local class with explicit void*m_vtable (no
// virtuals, no vtable emission); the +4 gap needs an explicit unused member.

class ExperienceLevelCreateModuleData
{
public:
	ExperienceLevelCreateModuleData();

private:
	void *m_vtable;
	unsigned int m_unused04;
	int m_levelToGrant;
	unsigned char m_mpOnly;
};

// ??0ExperienceLevelCreateModuleData@@QAE@XZ
ExperienceLevelCreateModuleData::ExperienceLevelCreateModuleData()
{
	m_levelToGrant |= -1;
	m_vtable = reinterpret_cast<void *>(0x00C595E8);
	m_mpOnly = 0;
}
