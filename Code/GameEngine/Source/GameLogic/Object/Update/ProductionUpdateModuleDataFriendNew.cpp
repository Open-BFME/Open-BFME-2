// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@ProductionUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E88F, 81 bytes. Dedicated TU: the factory news 0x50, runs the
// declared-only ctor (pinned at 0x49F7DB, EH body with Door vector members
// still unrowed), then feeds the new data plus the class parse proc (rowed at
// 0x49FE6A, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x4C pad). Recipe: SupplyWarehouseDockUpdateModuleDataFriendNew.cpp. Class
// identity is retail's own INI table at 0x00C517F0 (MaxQueueEntries/
// NumDoorAnimations/DoorOpeningTime/DoorWaitOpenTime/DoorCloseTime/...,
// donor-backed by the BFME1 ProductionUpdate ModuleData).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ProductionUpdateModuleData
{
public:
	ProductionUpdateModuleData();
	virtual ~ProductionUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x50 - 4];
};

// ?friend_newModuleData@ProductionUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ProductionUpdateModuleData::friend_newModuleData(INI *ini)
{
	ProductionUpdateModuleData *data = new ProductionUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, ProductionUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
