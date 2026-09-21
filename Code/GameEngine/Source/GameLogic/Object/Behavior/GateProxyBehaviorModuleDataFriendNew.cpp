// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@GateProxyBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253FB1, 87 bytes. Dedicated TU: the factory news 0x4C through
// the implicit derived ctor (inlined: pinned GateOpenAndClose base ctor at
// 0x498E2E plus the derived vtable via the pinned ??_7 at 0x00BEF380), then
// feeds the new data plus the inherited class parse proc (rowed GateOpenAnd-
// Close proc at 0x253F0E, pushed immediate, no pin: the proxy defines no table
// of its own) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is
// non-null. Operator new and __EH_prolog resolve via their rows. Recipe: the
// 81B GateOpenAndCloseBehaviorModuleData factory plus the inlined implicit
// derived ctor (standard 81B shape plus the 6B vtable overwrite). Class
// identity is the GateProxyBehavior pool key (rowed at 0x24E30E); the 18B
// derived ctor is rowed at 0x24E359.

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

private:
	unsigned char m_pad[0x4C - 4];
};

class GateProxyBehaviorModuleData : public GateOpenAndCloseBehaviorModuleData
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GateProxyBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GateProxyBehaviorModuleData::friend_newModuleData(INI *ini)
{
	GateProxyBehaviorModuleData *data = new GateProxyBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, GateOpenAndCloseBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
