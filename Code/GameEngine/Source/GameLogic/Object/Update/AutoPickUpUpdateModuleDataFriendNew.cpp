// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@AutoPickUpUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E099, 81 bytes. Dedicated TU: the factory news 0x2C, runs the
// declared-only ctor (pinned at 0x496308, EH body with filter/vector members
// still unrowed), then feeds the new data plus the class parse proc (rowed at
// 0x496689, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x28 pad). Recipe: SupplyWarehouseDockUpdateModuleDataFriendNew.cpp. Class
// identity is retail's own INI table at 0x00C4F4B8 (ScanDelayTime/
// PickUpFilter/ScanDistance/EatObjectEntry/AutoThrowObject/RunFromButton...,
// donor-backed by the BFME1 AutoPickUpUpdate eat-entry parser).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class AutoPickUpUpdateModuleData
{
public:
	AutoPickUpUpdateModuleData();
	virtual ~AutoPickUpUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x2C - 4];
};

// ?friend_newModuleData@AutoPickUpUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AutoPickUpUpdateModuleData::friend_newModuleData(INI *ini)
{
	AutoPickUpUpdateModuleData *data = new AutoPickUpUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AutoPickUpUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
