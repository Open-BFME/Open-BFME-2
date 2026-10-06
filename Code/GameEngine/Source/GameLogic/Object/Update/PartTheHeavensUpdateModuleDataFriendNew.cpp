// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@PartTheHeavensUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024F4FD, 84 bytes. Dedicated TU: the factory news 0x94, runs the
// pinned ctor (0x4ACBF8, sole raw caller is this factory), then feeds the new
// data plus the class parse proc (rowed at 0x4AC987 in the shared Update TU,
// pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// The TU-local class keeps only size and virtuality (vptr plus 0x90 pad).
// Identity: PartTheHeavensUpdate pool key 69B at 0x4AC942 ends where the proc
// begins; the factory exclusively pushes the proc VA; table Texture Radius
// Color Opacity Angle.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class PartTheHeavensUpdateModuleData
{
public:
	PartTheHeavensUpdateModuleData();
	virtual ~PartTheHeavensUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x94 - 4];
};

// ?friend_newModuleData@PartTheHeavensUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *PartTheHeavensUpdateModuleData::friend_newModuleData(INI *ini)
{
	PartTheHeavensUpdateModuleData *data = new PartTheHeavensUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, PartTheHeavensUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
