// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "EntEnragedUpdate" (addModule
// pairs the name with this factory); formerly misnamed EnragedUpdateModuleData.
//
// ?friend_newModuleData@EntEnragedUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x0024FB7F, 81 bytes. Dedicated TU: the factory news 0x30, runs the
// rowed nullary ctor (0x4B249D, vtable plus twin filters plus delay and
// distance defaults), then feeds the new data plus the class parse proc
// (rowed at 0x4B2505, pushed immediate, no pin) to INI::initFromINIMultiProc
// (rowed at 0x2DEB5) when ini is non-null. Operator new and __EH_prolog
// resolve via their rows. The TU-local class keeps only size and virtuality
// (vptr plus 0x2C pad). Recipe: ToppleUpdateModuleDataFriendNew.cpp. Class
// identity is the rowed EntEnragedUpdateModuleData::buildFieldParse proc (five
// Enraged fields plus ScanDelayTime/ScanDistance plus two ObjectFilter
// fields) pushed as the factory's proc immediate; the ctor installs vtable
// 0x00C56980 and fits the 0x30 news size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class EntEnragedUpdateModuleData
{
public:
	EntEnragedUpdateModuleData();
	virtual ~EntEnragedUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x30 - 4];
};

// ?friend_newModuleData@EntEnragedUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EntEnragedUpdateModuleData::friend_newModuleData(INI *ini)
{
	EntEnragedUpdateModuleData *data = new EntEnragedUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, EntEnragedUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
