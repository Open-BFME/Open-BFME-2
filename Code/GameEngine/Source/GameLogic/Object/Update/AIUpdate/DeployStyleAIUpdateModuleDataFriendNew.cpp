// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DeployStyleAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0025517E, 81 bytes. Dedicated TU: the factory news 0x74, runs
// the pinned ctor (0x255154, frameless 42B body over the pinned Transport
// base with the UnpackTime/PackTime zeros plus turret bools plus
// MustDeployToAttack true plus DeployedAttributeModifier null and the
// unique vtable 0x00BF3440; banked partial 0.95 pending a xor-vtable
// scheduling lever), then feeds the new data plus the class parse proc
// (rowed base-call link at 0x24D1CB, pushed immediate, Transport base proc
// plus table 0x00BEECB0 holding UnpackTime at +0x64 through
// DeployedAttributeModifier at +0x70, five of seven fields matching BFME1's
// DeployStyleAIUpdateModuleData table verbatim) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x70 pad). Recipe:
// WorkerAIUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// DeployStyleAIUpdateModuleData::buildFieldParse proc pushed as the
// factory's proc immediate (unique image-wide).

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DeployStyleAIUpdateModuleData
{
public:
	DeployStyleAIUpdateModuleData();
	virtual ~DeployStyleAIUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x74 - 4];
};

// ?friend_newModuleData@DeployStyleAIUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeployStyleAIUpdateModuleData::friend_newModuleData(INI *ini)
{
	DeployStyleAIUpdateModuleData *data = new DeployStyleAIUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DeployStyleAIUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
