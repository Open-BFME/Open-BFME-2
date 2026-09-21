// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@WorkerAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024EF11, 81 bytes. Dedicated TU: the factory news 0x84, runs the
// pinned ctor (0x24EE77, frameless body over the pinned Transport base
// 0x26E5D7 with Worker harvest stores at +0x64 through +0x80), then feeds
// the new data plus the class parse proc (rowed base-call link at 0x24EEBB,
// pushed immediate, Transport base proc plus table 0x00BEF4B0 holding
// MaxBoxes at +0x64 plus SupplyCenterActionDelay at +0x68 plus
// SupplyWarehouseActionDelay at +0x6C plus SupplyWarehouseScanDistance at
// +0x70 plus HarvestTrees at +0x74 plus HarvestActivationRange at +0x78 plus
// HarvestPreparationTime at +0x7C plus HarvestActionTime at +0x80) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x80 pad). Recipe:
// WanderAIUpdateModuleDataFriendNew.cpp. Class identity is the 8/8
// field-name-plus-offset match to BFME1's WorkerAIUpdateModuleData table at
// identical offsets; the proc-VA push is unique image-wide and the ctor has
// a single raw caller (this factory).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class WorkerAIUpdateModuleData
{
public:
	WorkerAIUpdateModuleData();
	virtual ~WorkerAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x84 - 4];
};

// ?friend_newModuleData@WorkerAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WorkerAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	WorkerAIUpdateModuleData *data = new WorkerAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, WorkerAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
