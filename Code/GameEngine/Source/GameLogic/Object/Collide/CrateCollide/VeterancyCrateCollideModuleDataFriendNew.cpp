// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@VeterancyCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00255B2D, 81 bytes. Dedicated TU: the factory news 0x68, runs the
// pinned ctor (0x255B09, frameless body over the rowed CrateCollide base
// 0x4BC657 zeroing +0x5C/+0x60/+0x61 and storing 10 at +0x64 under the folded
// vtable 0x00BF3AC0), then feeds the new data plus the class parse proc
// (pinned chained link at 0x251246, pushed immediate, base CrateCollide proc
// plus table 0x00BEFB60 holding EffectRange at +0x5C plus AddsOwnerVeterancy
// at +0x60 plus IsPilot at +0x61 plus AffectsUpToLevel at +0x64) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x64 pad). Recipe:
// SpecialEnemySenseUpdateModuleDataFriendNew.cpp. Class identity is the ZH
// VeterancyCrateCollide.h donor (m_rangeOfEffect plus m_addsOwnerVeterancy
// plus m_isPilot) extended by BFME2 with AffectsUpToLevel at +0x64; ctor,
// proc and factory are triple-contiguous at 0x255B09.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class VeterancyCrateCollideModuleData
{
public:
	VeterancyCrateCollideModuleData();
	virtual ~VeterancyCrateCollideModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x68 - 4];
};

// ?friend_newModuleData@VeterancyCrateCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *VeterancyCrateCollideModuleData::friend_newModuleData(INI *ini)
{
	VeterancyCrateCollideModuleData *data = new VeterancyCrateCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, VeterancyCrateCollideModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
