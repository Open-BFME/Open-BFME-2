// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "DetachableRiderBody" (addModule
// pairs the name with this factory); formerly misnamed ChinookAIUpdateModuleData.
//
// ?friend_newModuleData@DetachableRiderBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00251740, 84 bytes. Dedicated TU: the factory news 0x180, runs the
// declared-only nullary ctor (pinned at 0x4C1E8B, sole caller is this
// factory), then feeds the new data plus the class parse proc (rowed at
// 0x4C1B80, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x17C pad). Recipe: StealthUpdateModuleDataFriendNew.cpp. Class identity is
// the rowed DetachableRiderBodyModuleData::buildFieldParse proc (ZH Rope table
// plus SupplyTruck parent) pushed as the factory's proc immediate; the ctor
// installs vtable 0x00BF4028 and fits the 0x180 news size (floats at
// +0x174/+0x17C). The prior ??0ChinookAIUpdateModuleData pin at 0x49C4D2
// belonged to the rowed ChinookAIUpdate factory's 0xE4 class (vtable
// 0x00C51280), not to this ModuleData class.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DetachableRiderBodyModuleData
{
public:
	DetachableRiderBodyModuleData();
	virtual ~DetachableRiderBodyModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x180 - 4];
};

// ?friend_newModuleData@DetachableRiderBodyModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DetachableRiderBodyModuleData::friend_newModuleData(INI *ini)
{
	DetachableRiderBodyModuleData *data = new DetachableRiderBodyModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DetachableRiderBodyModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
