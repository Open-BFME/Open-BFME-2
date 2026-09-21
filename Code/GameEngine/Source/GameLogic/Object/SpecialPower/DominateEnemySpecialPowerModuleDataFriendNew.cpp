// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DominateEnemySpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00252EE5, 81 bytes. Dedicated TU: the factory news 0xDC, runs
// the rowed ctor (0x4CCA24, 122B EH body over the pinned SpecialPower base
// with DominateRadius plus TriggerFX plus DominatedFX plus PermanentlyConvert
// plus the 0x3623E5 filter member fed from the 0xDFEFA4 global), then feeds
// the new data plus the class parse proc (rowed base-call link at 0x4CC96D,
// pushed immediate, Rva0044EB54 base proc plus table 0x00C5F638 holding the
// Dominate fields, the sole image-wide pusher) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog
// resolve via their rows. The TU-local class keeps only size and virtuality
// (vptr plus 0xD8 pad). Recipe:
// StopSpecialPowerModuleDataFriendNew.cpp. Class identity is the rowed
// DominateEnemySpecialPowerModuleData::buildFieldParse proc pushed as the
// factory's proc immediate (unique image-wide) plus the rowed
// DominateEnemySpecialPower pool key ending where the ctor begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DominateEnemySpecialPowerModuleData
{
public:
	DominateEnemySpecialPowerModuleData();
	virtual ~DominateEnemySpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xDC - 4];
};

// ?friend_newModuleData@DominateEnemySpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DominateEnemySpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	DominateEnemySpecialPowerModuleData *data = new DominateEnemySpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DominateEnemySpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
