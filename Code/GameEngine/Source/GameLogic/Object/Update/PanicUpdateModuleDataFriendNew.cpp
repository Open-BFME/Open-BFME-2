// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "EvacuateDamage" (addModule
// pairs the name with this factory); formerly misnamed PanicUpdateModuleData.
//
// ?friend_newModuleData@EvacuateDamageModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00250E4B, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// rowed nullary ctor (0x4BAD10, vtable plus cleared weapon string plus
// tracked type and threshold and span defaults), then feeds the new data
// plus the class parse proc (rowed at 0x4BAD64, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new and __EH_prolog resolve via their rows. The TU-local class keeps only
// size and virtuality (vptr plus 0x14 pad). Recipe:
// ToppleUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// EvacuateDamageModuleData::buildFieldParse proc (evacuation weapon plus damage
// type plus panic threshold plus tracking span) pushed as the factory's proc
// immediate; the ctor installs vtable 0x00C59CF8 and fits the 0x18 news
// size.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class EvacuateDamageModuleData
{
public:
	EvacuateDamageModuleData();
	virtual ~EvacuateDamageModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@EvacuateDamageModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EvacuateDamageModuleData::friend_newModuleData(INI *ini)
{
	EvacuateDamageModuleData *data = new EvacuateDamageModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, EvacuateDamageModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
