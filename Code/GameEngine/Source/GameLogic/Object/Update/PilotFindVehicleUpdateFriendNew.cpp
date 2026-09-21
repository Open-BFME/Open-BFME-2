// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "EvaAnnounceClientCreate" (addModule
// pairs the name with this factory); formerly misnamed PilotFindVehicleUpdate/PilotFindVehicleUpdateModuleData.
//
// ?friend_newModuleData@EvaAnnounceClientCreate@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x00252A88, 81 bytes. Dedicated TU: the rowed no-arg ctor TU
// PilotFindVehicleUpdateCtor.cpp proves a 0x1C-byte novtable root class
// (three INVALID_ID ors plus zeroed tail); the factory news 0x1C, runs the
// declared-only ctor (rowed at 0x4C999D), then feeds the new data plus the
// class parse proc at 0x4C99C3 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. Recipe:
// CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void PilotFindVehicleUpdateParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class __declspec(novtable) EvaAnnounceClientCreate
{
public:
	EvaAnnounceClientCreate();
	virtual ~EvaAnnounceClientCreate();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	int m_pad04;
	int m_b08;
	int m_c0C;
	int m_d10;
	int m_e14;
	unsigned char m_f18[4];
};

// ?friend_newModuleData@EvaAnnounceClientCreate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *EvaAnnounceClientCreate::friend_newModuleData(INI *ini)
{
	EvaAnnounceClientCreate *data = new EvaAnnounceClientCreate;
	if (ini)
		ini->initFromINIMultiProc(data, PilotFindVehicleUpdateParse);
	return reinterpret_cast<ModuleData *>(data);
}
