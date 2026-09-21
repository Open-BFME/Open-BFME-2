// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@PoisonedBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C3A6, 81 bytes. Dedicated TU: the factory news 0x10, runs the
// pinned nullary ctor (0x253CDD, sole raw caller is this factory), then feeds
// the new data plus the class parse proc (rowed at 0x482F6C, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0xC pad). Recipe:
// RebuildHoleExposeDieModuleDataFriendNew.cpp. Class identity is the rowed
// PoisonedBehaviorModuleData::buildFieldParse proc (PoisonDamageInterval at
// +0x8 plus PoisonDuration at +0xC per the BFME1 donor, field vote 2/2)
// pushed as the factory's proc immediate, beside the rowed PoisonedBehavior
// pool key (0x482F27) ending where the proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class PoisonedBehaviorModuleData
{
public:
	PoisonedBehaviorModuleData();
	virtual ~PoisonedBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x10 - 4];
};

// ?friend_newModuleData@PoisonedBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PoisonedBehaviorModuleData::friend_newModuleData(INI *ini)
{
	PoisonedBehaviorModuleData *data = new PoisonedBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PoisonedBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
