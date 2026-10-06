// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DevastateSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00252653, 84 bytes. Dedicated TU: the factory news 0x90, runs the
// declared-only ctor (pinned at 0x4C84BD; vtable 0x00C5E518 plus Radius, FX,
// TreeValueMultiplier, TreeValueTotalCap and FireWeapon fields), then feeds
// the new data plus the class parse proc (rowed at 0x4C81C8, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0x8C pad).
// Recipe: DemoTrapUpdateModuleDataFriendNew.cpp. Class identity is retail's
// own five-entry INI table at 0x00C5E3D0 (landed buildFieldParse row) joined
// to BFME1's DevastateSpecialPower table (four of five fields verbatim).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DevastateSpecialPowerModuleData
{
public:
	DevastateSpecialPowerModuleData();
	virtual ~DevastateSpecialPowerModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x90 - 4];
};

// ?friend_newModuleData@DevastateSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DevastateSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	DevastateSpecialPowerModuleData *data = new DevastateSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DevastateSpecialPowerModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
