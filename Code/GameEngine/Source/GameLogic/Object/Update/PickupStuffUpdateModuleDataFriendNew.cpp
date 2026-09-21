// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@PickupStuffUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024D95B, 81 bytes. Dedicated TU: the factory news 0x18, runs the
// pinned nullary ctor (0x491E37, sole raw caller is this factory; 0.97 ctor
// partial banked), then feeds the new data plus the rowed parse proc
// (0x491E87, pushed immediate) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new and __EH_prolog resolve via
// their rows. The TU-local class keeps only size and virtuality (vptr plus
// 0x14 pad). Recipe: LaserUpdateModuleDataFriendNew.cpp. Class identity is
// the rowed PickupStuffUpdateModuleData::buildFieldParse proc pushed as the
// factory's proc immediate; the ctor fits the 0x18 news size; the rowed
// poolkey 0x491E1C (PickupStuff) ends where the proc begins.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class PickupStuffUpdateModuleData
{
public:
	PickupStuffUpdateModuleData();
	virtual ~PickupStuffUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x18 - 4];
};

// ?friend_newModuleData@PickupStuffUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PickupStuffUpdateModuleData::friend_newModuleData(INI *ini)
{
	PickupStuffUpdateModuleData *data = new PickupStuffUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PickupStuffUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
