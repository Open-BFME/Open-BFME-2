// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RebuildHoleExposeDieModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024CB18, 81 bytes. Dedicated TU: the factory news 0x48, runs the
// pinned nullary ctor (0x48671F, sole raw caller is this factory; 0.97
// partial banked with the RMW-and shape, unrowed), then feeds the new data
// plus the class parse proc (rowed at 0x486746, pushed immediate, no pin)
// to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x44 pad). Recipe:
// CrushDieModuleDataFriendNew.cpp. Class identity is the rowed
// RebuildHoleExposeDieModuleData::buildFieldParse proc (HoleName plus
// HoleMaxHealth table 0x00C4AE00) pushed as the factory's proc immediate,
// beside the rowed RebuildHoleExposeDie pool key closing this cluster.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RebuildHoleExposeDieModuleData
{
public:
	RebuildHoleExposeDieModuleData();
	virtual ~RebuildHoleExposeDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x48 - 4];
};

// ?friend_newModuleData@RebuildHoleExposeDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RebuildHoleExposeDieModuleData::friend_newModuleData(INI *ini)
{
	RebuildHoleExposeDieModuleData *data = new RebuildHoleExposeDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RebuildHoleExposeDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
