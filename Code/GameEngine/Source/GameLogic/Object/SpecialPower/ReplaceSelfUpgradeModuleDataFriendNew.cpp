// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ReplaceSelfUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x002506CE, 84 bytes. Dedicated TU: the factory news 0x124, runs
// the pinned ctor (0x4B790B, EH body over the OpenContain base with the
// vector member at +0x118), then feeds the new data plus the class parse
// proc (rowed double-add link at 0x4B7023, pushed immediate) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x120 pad). Recipe:
// ElvenWoodSpecialPowerModuleDataFriendNew.cpp. Class identity is the rowed
// ReplaceSelfUpgradeModuleData::buildFieldParse proc (getter table plus
// table 0x00858A88 holding ReplaceWith at +0x118 plus AndThenAddA at +0x118)
// pushed as the factory's proc immediate; the ReplaceSelfUpgrade pool key
// at 0x4B70B4 sits in the same cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ReplaceSelfUpgradeModuleData
{
public:
	ReplaceSelfUpgradeModuleData();
	virtual ~ReplaceSelfUpgradeModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x124 - 4];
};

// ?friend_newModuleData@ReplaceSelfUpgradeModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ReplaceSelfUpgradeModuleData::friend_newModuleData(INI *ini)
{
	ReplaceSelfUpgradeModuleData *data = new ReplaceSelfUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ReplaceSelfUpgradeModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
