// cl: /O1 /DNDEBUG /MD
//
// ?friend_newModuleData@FireWeaponCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00254A7A, 49 bytes. Dedicated TU, frameless shape: the factory
// news 0x30, runs the declared-only throw-ctor (pinned at 0x254A36) under a
// null-checked new, then feeds the new data plus the class parse proc (rowed
// at 0x4BB918, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed
// at 0x2DEB5) when ini is non-null. Operator new resolves via its row. The
// TU-local class keeps only size (0x30 pad, no virtuals, so no vptr and no
// EH prolog; the throw-ctor keeps the new frameless). Class identity is
// retail's own CollideWeapon-led INI table at 0x00C5A190 (landed
// buildFieldParse row, donor 4-field verbatim) beside the rowed
// FireWeaponCollide pool key (0x4BB755).
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class FireWeaponCollideModuleData
{
public:
	FireWeaponCollideModuleData() throw();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x30];
};

// ?friend_newModuleData@FireWeaponCollideModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FireWeaponCollideModuleData::friend_newModuleData(INI *ini)
{
	FireWeaponCollideModuleData *data = new FireWeaponCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, FireWeaponCollideModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
