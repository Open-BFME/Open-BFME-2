// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@KeepObjectDieModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253BB7, 81 bytes. Dedicated TU: the factory news 0x40, runs the
// rowed nullary ctor (0x253B78, sole raw caller is this factory;
// CollapsingTime 0x19 plus StayOnRadar 0 over the opaque SEH base 0x253510),
// then feeds the new data plus the class parse proc (rowed at 0x253B95,
// pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x3C pad).
// Recipe: CrushDieModuleDataFriendNew.cpp. Class identity is the rowed
// KeepObjectDieModuleData::buildFieldParse proc (CollapsingTime at +0x38
// plus StayOnRadar at +0x3C) pushed as the factory's proc immediate, plus
// the ModuleFactory registrar at 0x00258D9B mapping the KeepObjectDie INI
// name to this factory.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class KeepObjectDieModuleData
{
public:
	KeepObjectDieModuleData();
	virtual ~KeepObjectDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x40 - 4];
};

// ?friend_newModuleData@KeepObjectDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *KeepObjectDieModuleData::friend_newModuleData(INI *ini)
{
	KeepObjectDieModuleData *data = new KeepObjectDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, KeepObjectDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
