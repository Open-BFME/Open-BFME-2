// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@SupplyCenterDockUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024EA14, 81 bytes. Dedicated TU: the factory news 0x1C, runs the
// rowed ctor (0x4A10D5, BFME1 SupplyCenterDock donor over pinned Dock base),
// then feeds the new data plus the class parse proc (rowed chained link at
// 0x4A0DAC, Dock base plus table 0x00C51A80 ValueMultiplier BonusScience
// BonusScienceMultiplier, pushed immediate) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog
// resolve via their rows. The TU-local class keeps only size and virtuality
// (vptr plus 0x18 pad). Recipe: MonsterDockUpdateModuleDataFriendNew.cpp.
// Class identity is the SupplyCenterDockUpdate pool key at 0x4A0E4C plus the
// BFME1 SupplyCenterDock donor files plus the ValueMultiplier table.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class SupplyCenterDockUpdateModuleData
{
public:
	SupplyCenterDockUpdateModuleData();
	virtual ~SupplyCenterDockUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x1C - 4];
};

// ?friend_newModuleData@SupplyCenterDockUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SupplyCenterDockUpdateModuleData::friend_newModuleData(INI *ini)
{
	SupplyCenterDockUpdateModuleData *data = new SupplyCenterDockUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, SupplyCenterDockUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
