// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@DeletionUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x00253CFF, 56 bytes. Dedicated TU: the factory news 0x10 with an
// inline trivial ctor (explicit m_vtable literal plus zeroed min and max
// frames), then feeds the new data plus the class parse proc (rowed at
// 0x253CEE, pushed immediate, no pin) to INI::initFromINIMultiProc (rowed at
// 0x2DEB5) when ini is non-null. Operator new resolves via its row. The
// TU-local class keeps only size and layout (vptr literal plus two ints plus
// 4 pad). Recipe: LifetimeUpdateFriendNewData.cpp with the Lifetime
// explicit-m_vtable precedent. Class identity is retail's own INI table at
// 0x00BF17BC (MinLifetime plus MaxLifetime per ZH DeletionUpdate.h) beside
// the rowed DeletionUpdate bodies (update plus ctor plus pool key).

extern "C" const void *const vtbl_00C4ED70[];  // folded, 9 classes; via ??_7BeaconClientUpdateModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4ED70=??_7BeaconClientUpdateModuleData@@6B@")

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class DeletionUpdateModuleData
{
public:
	DeletionUpdateModuleData()
	{
		m_minFrames = 0;
		m_maxFrames = 0;
		m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C4ED70));
	}
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	void *m_vtable;
	int m_baseField;
	int m_minFrames;
	int m_maxFrames;
};

// ?friend_newModuleData@DeletionUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeletionUpdateModuleData::friend_newModuleData(INI *ini)
{
	DeletionUpdateModuleData *data = new DeletionUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, DeletionUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}
