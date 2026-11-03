// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleData@LifetimeUpdate@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E3A3, 81 bytes. Dedicated TU: the ZH LifetimeUpdateModuleData
// header sizes the class at 0x10 but retail news 0x18 (push-imm8; the rowed
// nullary ctor at 0x3A4A7D is a BFME1-verbatim donor). TU-local 0x18-byte
// ModuleData class plus declared-only ctor reproduces the data-factory stub;
// operator new, __EH_prolog and INI::initFromINIMultiProc (rowed 0x2DEB5)
// resolve via their rows. The buildFieldParse address is taken (DIR32 site
// the gate copies from retail); the TU-local empty def carries a
// present-unmatched marker since its retail counterpart 0x7A4A6C is unrowed.
// Spelling: MAKE_STANDARD_MODULE_DATA_MACRO_ABC. Recipe: FriendNew TUs.

class INI;
class MultiIniFieldParse;
class ModuleData;

typedef void (*LifetimeFieldProc)(MultiIniFieldParse &);

#include "../../../../Include/Common/INI/INI.h"

class LifetimeUpdateModuleData
{
public:
	LifetimeUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &field);

private:
	char m_pad[0x18];
};

// LifetimeUpdateModuleData::buildFieldParse: defined in ModuleDataBuildFieldParse.cpp (its row's unit).

#include "../../../../Include/GameLogic/Module/LifetimeUpdateClass.h"

// ?friend_newModuleData@LifetimeUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LifetimeUpdate::friend_newModuleData(INI *ini)
{
	LifetimeUpdateModuleData *data = new LifetimeUpdateModuleData;
	if (ini) {
		ini->initFromINIMultiProc(data, LifetimeUpdateModuleData::buildFieldParse);
	}
	return reinterpret_cast<ModuleData *>(data);
}
