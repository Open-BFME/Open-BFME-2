// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ExperienceScalarUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025042E, 84 bytes. Dedicated TU: the factory news 0x11C, runs
// the rowed ctor (0x4B6187, frameless over the OpenContain base with the
// folded vtable and AddXPScalar float-zero), then feeds the new data plus
// the rowed class parse proc (0x4B61A4, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. Recipe:
// GeometryUpgradeModuleDataFriendNew.cpp. Class identity is the rowed
// ExperienceScalarUpgrade proc (Upgrade base proc 0x4CE29D plus table
// 0x00858524 holding AddXPScalar at +0x118 matching the ctor store)
// pushed as the factory's proc immediate; the rowed ExperienceScalarUpgrade
// pool key at 0x4B6142 ends where the ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ExperienceScalarUpgradeModuleData
{
public:
	ExperienceScalarUpgradeModuleData();
	virtual ~ExperienceScalarUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x11C - 4];
};

// ?friend_newModuleData@ExperienceScalarUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ExperienceScalarUpgradeModuleData::friend_newModuleData(INI *ini)
{
	ExperienceScalarUpgradeModuleData *data = new ExperienceScalarUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ExperienceScalarUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
