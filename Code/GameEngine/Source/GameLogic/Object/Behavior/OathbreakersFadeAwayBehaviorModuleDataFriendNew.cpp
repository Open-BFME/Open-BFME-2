// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@OathbreakersFadeAwayBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00254936, 55 bytes. Dedicated TU: the factory news 0xC with an
// inline trivial ctor (explicit m_vtable literal 0x00C4ED70 plus int
// FadeOutTime default 1), then feeds the new data plus the class parse proc
// (rowed at 0x4B8A79, pushed immediate, no pin) to
// INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini is non-null. Operator
// new resolves via its row. The TU-local class keeps only size and layout
// (vptr literal plus base int plus FadeOutTime int). Recipe:
// DeletionUpdateModuleDataFriendNew.cpp with the DeletionUpdate inline
// explicit-m_vtable precedent. Class identity is retail's own INI table at
// 0x00C592CC (single FadeOutTime field) beside the rowed
// OathbreakersFadeAwayBehavior pool key (0x4B8A02) and literal name getter
// (0x4B8A22); BFME1 carries the same OathbreakersFadeAwayBehaviorModuleData
// class.

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class OathbreakersFadeAwayBehaviorModuleData
{
public:
	OathbreakersFadeAwayBehaviorModuleData()
	{
		m_vtable = reinterpret_cast<void *>(0x00C4ED70);
		m_fadeOutTime = 1;
	}
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	void *m_vtable;
	int m_baseField;
	int m_fadeOutTime;
};

// ?friend_newModuleData@OathbreakersFadeAwayBehaviorModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *OathbreakersFadeAwayBehaviorModuleData::friend_newModuleData(INI *ini)
{
	OathbreakersFadeAwayBehaviorModuleData *data = new OathbreakersFadeAwayBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, OathbreakersFadeAwayBehaviorModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
