// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "TeleportToCasterSpecialPower" (addModule
// pairs the name with this factory); formerly misnamed SpecialAbilityUpdate/SpecialAbilityUpdateModuleData.
//
// ?friend_newModuleData@TeleportToCasterSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00253092, 84 bytes. Dedicated TU: the rowed no-arg ctor TU
// SpecialAbilityUpdateCtor.cpp proves a 0xDC-byte class (0xC8-byte opaque
// base plus trailing floats and ints); the factory news 0xDC, runs the
// declared-only ctor (rowed at 0x4CD34E), then feeds the new data plus the
// class parse proc at 0x4CD389 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0xD8 pad). Recipe:
// CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void SpecialAbilityUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class TeleportToCasterSpecialPower
{
public:
	TeleportToCasterSpecialPower();
	virtual ~TeleportToCasterSpecialPower();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xDC - 4];
};

// ?friend_newModuleData@TeleportToCasterSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TeleportToCasterSpecialPower::friend_newModuleData(INI *ini)
{
	TeleportToCasterSpecialPower *data = new TeleportToCasterSpecialPower;
	if (ini)
		ini->initFromINIMultiProc(data, SpecialAbilityUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
