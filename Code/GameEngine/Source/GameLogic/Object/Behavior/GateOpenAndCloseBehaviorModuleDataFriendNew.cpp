// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GateOpenAndCloseBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253F1F, 81 bytes. Dedicated TU: the factory news 0x4C, runs the
// pinned nullary ctor (0x498E2E, EH installing vtable 0x00C501B0 plus vector
// members at +0x2C/+0x38 for the table Geometry fields), then feeds the new
// data plus the class parse proc (rowed at 0x253F0E, pushed immediate, no pin)
// to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x48 pad). Recipe:
// AIGateUpdateModuleDataFriendNew.cpp. Class identity is the rowed
// GateOpenAndCloseBehaviorModuleData::buildFieldParse proc (table 0x00BF19F8
// holds OpenByDefault/ResetTime/PercentOpen/Proxy/Repel/Geometry/Sound fields
// with GeometryForOpen at +0x2C plus GeometryForClosed at +0x38, matching the
// ctor member builds) pushed as the factory's proc immediate; the ctor lives
// in the GateOpenAndClose cluster at 0x498xxx beside the behavior pool key.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class GateOpenAndCloseBehaviorModuleData
{
public:
	GateOpenAndCloseBehaviorModuleData();
	virtual ~GateOpenAndCloseBehaviorModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x4C - 4];
};

// ?friend_newModuleData@GateOpenAndCloseBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GateOpenAndCloseBehaviorModuleData::friend_newModuleData(INI *ini)
{
	GateOpenAndCloseBehaviorModuleData *data = new GateOpenAndCloseBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GateOpenAndCloseBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
