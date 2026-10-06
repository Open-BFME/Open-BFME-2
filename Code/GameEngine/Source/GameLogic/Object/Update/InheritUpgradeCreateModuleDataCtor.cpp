// cl: /GX /DNDEBUG /MD
//
// ??0InheritUpgradeCreateModuleData@@QAE@XZ, retail 0x004B9508, 69 bytes.
// EH ctor: single state-0 store, vtable 0x00C59768 at +0, 0.0f at +8, member
// at +0xC zeroed through the rowed clear80 helper, member at +0x8C built by
// the pinned nullary ctor. Table 0xC59728 holds Radius@8 Upgrade@C
// ObjectFilter@8C; factory 0x250CC3 news 0x90. V4: empty CreateModuleData
// base as the sole unwindable (state 0, no transitions, no -1) plus body in
// retail order; the filter is a plain member driven by a construct-method
// alias pin (a declared ctor would implicitly construct early AND double
// with any body call).

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();

private:
	char m_pad[0x80];
};

class Rva003623E5Member
{
public:
	void construct();

private:
	int m_value;
};

class CreateModuleData
{
public:
	CreateModuleData() {}
	~CreateModuleData();

private:
};

class InheritUpgradeCreateModuleData : public CreateModuleData
{
public:
	InheritUpgradeCreateModuleData();

private:
	void *m_vtable;
	unsigned int m_unused04;
	float m_radius;
	Rva001EAE6FHelper m_upgrade;
	Rva003623E5Member m_filter;
};

extern const void *const g_00C59768[];

// ??0InheritUpgradeCreateModuleData@@QAE@XZ
InheritUpgradeCreateModuleData::InheritUpgradeCreateModuleData()
{
	m_vtable = (void *)g_00C59768;
	m_radius = 0.0f;
	m_upgrade.clear80();
	m_filter.construct();
}
