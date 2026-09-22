// cl: /O1 /GX /DNDEBUG /MD
// Identity: ModuleFactory registers this data class under "CombineHordeSpecialPowerModuleData" (addModule
// pairs the name with this factory); formerly misnamed AIUpdateInterface.
//
// ?friend_newModuleData@CombineHordeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
// retail 0x002527F1, 84 bytes. Dedicated TU: the rowed no-arg ctor TU
// AIUpdateInterfaceCtor.cpp proves the layout; the factory news 0x80, runs
// the declared-only ctor (rowed at 0x4C886E), then feeds the new data plus
// the class parse proc at 0x4C87A9 (pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x7C pad). Recipe:
// CleanupHazardUpdateFriendNew.cpp.

class ModuleData;
class INI;
class MultiIniFieldParse;

void AIUpdateInterfaceParse(MultiIniFieldParse &parse);

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CombineHordeSpecialPowerModuleData
{
public:
	CombineHordeSpecialPowerModuleData();
	virtual ~CombineHordeSpecialPowerModuleData();
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x80 - 4];
};

// ?friend_newModuleData@CombineHordeSpecialPowerModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CombineHordeSpecialPowerModuleData::friend_newModuleData(INI *ini)
{
	CombineHordeSpecialPowerModuleData *data = new CombineHordeSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, AIUpdateInterfaceParse);
	return reinterpret_cast<ModuleData *>(data);
}
