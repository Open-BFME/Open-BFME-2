// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@CreateObjectDieIfEldestKindofModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024C8C1, 81 bytes. Dedicated TU: the factory news 0x4C, runs the
// pinned nullary ctor (0x485D88, EH over base 0x253510 plus vector 0x211E58
// plus string 0x36410; shared with derived 0x485E19 per SlotToLock precedent),
// then feeds the new data plus the class parse proc (rowed at 0x485A74,
// pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5)
// when ini is non-null. Operator new and __EH_prolog resolve via their rows.
// Class identity is the rowed pool key (0x485A2F) ending where the proc
// begins, plus the rowed CreateObjectDieIfEldestKindofModuleData::
// buildFieldParse proc (CreationList at +0x38 plus DebrisPortion at +0x3C
// plus UpgradeRequired at +0x40) pushed as the factory's proc immediate.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class CreateObjectDieIfEldestKindofModuleData
{
public:
	CreateObjectDieIfEldestKindofModuleData();
	virtual ~CreateObjectDieIfEldestKindofModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0x4C - 4];
};

// ?friend_newModuleData@CreateObjectDieIfEldestKindofModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CreateObjectDieIfEldestKindofModuleData::friend_newModuleData(INI *ini)
{
	CreateObjectDieIfEldestKindofModuleData *data = new CreateObjectDieIfEldestKindofModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, CreateObjectDieIfEldestKindofModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
