// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@TemporarilyDefectUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00254C9B, 52 bytes. Dedicated TU: the factory news 0x0C with an
// inline trivial ctor (explicit m_vtable literal 0x00C4ED70 plus a zeroed
// defect-duration int at +0x08 matching the DefectDuration field of the
// class table at 0x00C5F5E4), then feeds the new data plus the class parse
// proc (rowed at 0x4CC69E, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null.
// Operator new resolves via its row. The TU-local class keeps only size and
// layout (vptr literal plus one int plus 4 pad). Recipe:
// DeletionUpdateModuleDataFriendNew.cpp with the Deletion explicit-m_vtable
// precedent. Class identity is the rowed TemporarilyDefectUpdate pool key at
// 0x4CC659 (ends where the class proc begins) plus the pushed proc VA.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class TemporarilyDefectUpdateModuleData
{
public:
	TemporarilyDefectUpdateModuleData()
	{
		m_defectDuration = 0;
		m_vtable = reinterpret_cast<void *>(0x00C4ED70);
	}
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	void *m_vtable;
	int m_unused04;
	int m_defectDuration;
};

// ?friend_newModuleData@TemporarilyDefectUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TemporarilyDefectUpdateModuleData::friend_newModuleData(INI *ini)
{
	TemporarilyDefectUpdateModuleData *data = new TemporarilyDefectUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, TemporarilyDefectUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
