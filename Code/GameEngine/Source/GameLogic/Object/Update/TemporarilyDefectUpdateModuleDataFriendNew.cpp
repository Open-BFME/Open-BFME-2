// cl: /GX /DNDEBUG /MD
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

extern "C" const void *const __identifier("??_7ObjectHelperModuleData@@6B@")[];  // folded nine-class vftable 0x00C4ED70, by its data-ledger name

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
		m_vtable = reinterpret_cast<void *>(((unsigned int)__identifier("??_7ObjectHelperModuleData@@6B@")));
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

struct FieldParse;
extern const int g_emptyFieldParseTable[];

#include "../../../../Include/Common/INI/FieldParse.h"

// ?rva00254545@@YAXAAVMultiIniFieldParse@@@Z @0x00254545 (17B)
void __declspec(noinline) rva00254545(MultiIniFieldParse &p)
{
	p.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
}

// ?rva004607F3@@YAXAAVMultiIniFieldParse@@@Z @0x004607F3 (17B)
void __declspec(noinline) rva004607F3(MultiIniFieldParse &p)
{
	p.add(reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable), 0);
}

class Rva002533FCData
{
public:
	Rva002533FCData()
	{
		m_vtable = reinterpret_cast<void *>(((unsigned int)__identifier("??_7ObjectHelperModuleData@@6B@")));
	}

private:
	void *m_vtable;
	int m_unused04;
};

// ?ModuleFactoryDataAt002533FC@@YAPAVModuleData@@PAVINI@@@Z @0x002533FC (48B)
ModuleData *ModuleFactoryDataAt002533FC(INI *ini)
{
	Rva002533FCData *data = new Rva002533FCData;
	if (ini)
		ini->initFromINIMultiProc(data, rva00254545);
	return reinterpret_cast<ModuleData *>(data);
}

// ?ModuleFactoryDataAt00253575@@YAPAVModuleData@@PAVINI@@@Z @0x00253575 (48B)
ModuleData *ModuleFactoryDataAt00253575(INI *ini)
{
	Rva002533FCData *data = new Rva002533FCData;
	if (ini)
		ini->initFromINIMultiProc(data, rva004607F3);
	return reinterpret_cast<ModuleData *>(data);
}

class DebugDisplayInterface;
struct _iobuf;
void __cdecl rva000B3FD0DebugDisplay(DebugDisplayInterface *, void *, _iobuf *);

// ICF-folded twin of the 1-byte bodies at 0x000B3FD0: a cdecl empty body is
// a bare ret like every other name folded there; this TU takes its address
// as the initFromINIMultiProc callback, so it provides the spelling itself.
void __cdecl rva000B3FD0DebugDisplay(DebugDisplayInterface *, void *, _iobuf *)
{
}

// ?ModuleFactoryDataAt00255ED8@@YAPAVModuleData@@PAVINI@@@Z @0x00255ED8 (48B)
ModuleData *ModuleFactoryDataAt00255ED8(INI *ini)
{
	Rva002533FCData *data = new Rva002533FCData;
	if (ini)
		ini->initFromINIMultiProc(data, reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(rva000B3FD0DebugDisplay));
	return reinterpret_cast<ModuleData *>(data);
}

