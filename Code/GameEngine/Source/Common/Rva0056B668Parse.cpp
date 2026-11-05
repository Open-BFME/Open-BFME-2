// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG
// stlport
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// ?Rva0056B668Parse@@YAXPAVINI@@PAX1PBX@Z @0x0056B668 255B
// Target evidence: stored callback slot 0x0083780C is adjacent to "Object";
// retail tests INI type 2 and 5 and uses the ArmyIcon reload message.
// Donor structure: sibling Rva0056BF1FParse.cpp has the same 255B parser,
// two-table MultiIniFieldParse setup, INIException paths and vector append.
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

class Rva0056B63E;
class ModuleData
{
};

class Rva0056B63E : public ModuleData
{
public:
	Rva0056B63E(void *arg);

private:
	char m_pad[0x58];
	unsigned m_visibleArmySizes;
	unsigned char m_clickable;
	unsigned char m_displayAtRallyPoint;
	unsigned char m_showOnlyAfterMoveOrder;
};

struct Rva004DFCB0Element
{
	const ModuleData *module;
};

int Rva0056B7DEGet(void);

// Retail VA 0x00C39498 (.rdata): the VisibleArmySizes bit names, four entries
// directly followed by the "HERO_ONLY" literal (no separate sentinel word).
extern const char *const g_00C39498[] = { "HERO_ONLY", "SMALL", "MEDIUM", "LARGE" };

// Retail VA 0x00C6D4D0 (.rdata): this object template's own field table, four
// records and a zero sentinel, chained after the base table (Rva0056B7DEGet).
extern const FieldParse g_00C6D4D0[] = {
	{ "VisibleArmySizes", &INI::parseBitString32, g_00C39498, 0x58 },
	{ "Clickable", &INI::parseBool, 0, 0x5C },
	{ "DisplayAtRallyPoint", &INI::parseBool, 0, 0x5D },
	{ "ShowOnlyAfterMoveOrder", &INI::parseBool, 0, 0x5E },
	{ 0, 0, 0, 0 }
};

void Rva0056B668Parse(INI *ini, void *instance, void *store, const void *userData)
{
	if (ini->m_loadType == 2)
		throw INIException(8, "Cannot override Living World objects in map.ini");
	if (ini->m_loadType == 5)
		throw INIException(8, "Reload of LivingWorldArmyIconSubObjectTemplate not supported");
	const char *token = ini->getNextToken(0);
	Rva004DFCB0Element item = { new Rva0056B63E(&AsciiString(token)) };
	MultiIniFieldParse parse;
	parse.add((const FieldParse *)Rva0056B7DEGet(), 0);
	parse.add(g_00C6D4D0, 0);
	ini->initFromINIMulti((void *)item.module, parse);
	((_STL::vector<Rva004DFCB0Element> *)store)->push_back(item);
}
