// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "CurseSpecialPower" (addModule
// pairs the name with this factory); formerly misnamed SpyVisionUpdate/SpyVisionUpdateModuleData.
//
// ?friend_newModuleData@CurseSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00252F74, 84 bytes. Dedicated TU: the rowed no-arg ctor TU
// SpyVisionUpdateCtor.cpp proves a 0xD4-byte class (0xC8-byte opaque base
// plus two ints plus a float); the factory news 0xD4, runs the
// declared-only ctor (rowed at 0x4CCD34), then feeds the new data plus the
// class parse proc at 0x4CCD64 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0xD0 pad). Recipe:
// CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void SpyVisionUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CurseSpecialPower
{
public:
	CurseSpecialPower();
	virtual ~CurseSpecialPower();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xD4 - 4];
};

// ?friend_newModuleData@CurseSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CurseSpecialPower::friend_newModuleData(INI *ini)
{
	CurseSpecialPower *data = new CurseSpecialPower;
	if (ini)
		ini->initFromINIMultiProc(data, SpyVisionUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
