// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "CritterEmitterUpdate" (addModule
// pairs the name with this factory); formerly misnamed DynamicGeometryInfoUpdate/DynamicGeometryInfoUpdateModuleData.
//
// ?friend_newModuleData@CritterEmitterUpdate@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00252906, 81 bytes. Dedicated TU: the rowed no-arg ctor TU
// DynamicGeometryInfoUpdateCtor.cpp proves a 0x24-byte root class (vtable,
// int, two 12-byte vectors, trailing int); the factory news 0x24, runs the
// declared-only ctor (rowed at 0x4C8EFF), then feeds the new data plus the
// class parse proc at 0x4C8FD7 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. Recipe:
// CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void DynamicGeometryInfoUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CritterEmitterUpdate
{
public:
	CritterEmitterUpdate();
	virtual ~CritterEmitterUpdate();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	int m_unused04;
	unsigned char m_a08[12];
	unsigned char m_b14[12];
	int m_i20;
};

// ?friend_newModuleData@CritterEmitterUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CritterEmitterUpdate::friend_newModuleData(INI *ini)
{
	CritterEmitterUpdate *data = new CritterEmitterUpdate;
	if (ini)
		ini->initFromINIMultiProc(data, DynamicGeometryInfoUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
