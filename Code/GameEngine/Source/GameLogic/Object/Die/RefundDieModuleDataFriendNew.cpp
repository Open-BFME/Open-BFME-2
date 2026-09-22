// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@RefundDieModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253940, 81 bytes. Dedicated TU: the factory news 0x44, runs the
// rowed nullary ctor (0x2538DB, sole raw caller is this factory; own vtable
// 0xBF0660 plus 0x3623E5 filter member at +0x40 plus UpgradeRequired 0 at
// +0x38 plus RefundPercent 0.0 at +0x3C), then feeds the new data plus the
// class parse proc (rowed at 0x25391E, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new and __EH_prolog resolve via their rows. The TU-local class
// keeps only size and virtuality (vptr plus 0x40 pad).
// Recipe: KeepObjectDieModuleDataFriendNew.cpp. Class identity is the rowed
// RefundDieModuleData::buildFieldParse proc pushed as the factory proc
// immediate, plus the ModuleFactory registrar mapping the RefundDie INI name
// to this factory.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class RefundDieModuleData
{
public:
	RefundDieModuleData();
	virtual ~RefundDieModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x44 - 4];
};

// ?friend_newModuleData@RefundDieModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RefundDieModuleData::friend_newModuleData(INI *ini)
{
	RefundDieModuleData *data = new RefundDieModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, RefundDieModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
