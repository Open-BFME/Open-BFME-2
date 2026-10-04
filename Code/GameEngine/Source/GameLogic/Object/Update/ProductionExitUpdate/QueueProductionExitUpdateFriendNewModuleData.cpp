// cl: /O1 /GX- /DNDEBUG /MD
//
// ?friend_newModuleData@QueueProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025424F, 49 bytes. Ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/
// QueueProductionExitUpdateFriendNewModuleDataThunk.cpp (1281192f68; donor
// flags /DNDEBUG /MD /GX- with BFME 2's /O1 in place of /O2 /Ob2). Compiled
// that way the body places uniquely on unclaimed .text by masked whole-.text
// search (tools/donor_sweep.py).
//
// Identity is retail's own: ModuleFactory's registration at 0x00259827
// pushes "QueueProductionExitUpdate" with this data factory and the rowed
// QueueProductionExitUpdate::friend_newModuleInstance (0x0024E969). The
// factory news 0x34 bytes, runs the rowed ctor at 0x002541FA, and hands the
// parse proc at 0x0025423E to INI::initFromINIMultiProc (rowed 0x0002DEB5).
// As in Zero Hour's MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA, the
// factory is a static of the module class.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class QueueProductionExitUpdateModuleData
{
public:
	QueueProductionExitUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	unsigned char m_bytes[0x34];
};

class QueueProductionExitUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@QueueProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *QueueProductionExitUpdate::friend_newModuleData(INI *ini)
{
	QueueProductionExitUpdateModuleData *data = new QueueProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, QueueProductionExitUpdateModuleData::buildFieldParse);
	return (ModuleData *)data;
}
