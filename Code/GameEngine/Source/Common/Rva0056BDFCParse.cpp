// cl: /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// ?Rva0056BDFCParse@@YAXPAVINI@@PAX1PBX@Z @0x0056BDFC 255B. LivingWorldBuildingIcon sub-object parse: checks INI type at +8 for map.ini override (2) and reload (5) throwing INIException(8) then getNextToken plus new Rva0056BDC8 via AsciiString temp plus MultiIniFieldParse two-table init plus vector push_back. Evidence: chain via just-landed 0x0056BDC8 ctor plus sibling 0x0056BF1F same 255B shape with BuildPlotIcon strings plus BlockParse LivingWorldBuildingIcon plus FieldParse tables 0x00C6D690 and 0x00C6D8F8.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
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
// Keep the allocator call out of line, as in the rowed growth helper.
// The proxy, clear and set helpers must remain visible for retail inlining.
class ModuleData;
namespace _STL { template <> const ModuleData **allocator<const ModuleData *>::allocate(size_t, const void *) const; }

#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

class Rva0056BDC8;
class ModuleData
{
};

class Rva0056BDC8 : public ModuleData
{
public:
	Rva0056BDC8(void *arg);

private:
	char m_pad[0x64];
};

int Rva0056B7DEGet(void);
// The icon's fade-type names (retail 0x00C37BF4, 7 entries).
static const char *const s_iconFadeTypeNames[] = {
	"NONE", "IN", "OUT", "INOUT", "STOP", "Opacity", "Additive",
};

// The icon's own field table (retail 0x00C6D8F8): four visibility flags
// and two fade types.
extern const FieldParse g_00C6D8F8[] = {
	{ "Clickable", &INI::parseBool, 0, 96 },
	{ "HideWhenUnderConstruction", &INI::parseBool, 0, 97 },
	{ "HideWhenNotUnderConstruction", &INI::parseBool, 0, 98 },
	{ "HideWhenNotProducing", &INI::parseBool, 0, 99 },
	{ "FadeTypeForShowing", &INI::parseIndexList, s_iconFadeTypeNames, 88 },
	{ "FadeTypeForHiding", &INI::parseIndexList, s_iconFadeTypeNames, 92 },
	{ 0, 0, 0, 0 },
};

void Rva0056BDFCParse(INI *ini, void *instance, void *store, const void *userData)
{
	if (ini->m_loadType == 2)
		throw INIException(8, "Cannot override Living World objects in map.ini");
	if (ini->m_loadType == 5)
		throw INIException(8, "Reload of LivingWorldBuildingIconSubObjectTemplate not supported");
	const char *token = ini->getNextToken(0);
	const ModuleData *item = new Rva0056BDC8(&AsciiString(token));
	MultiIniFieldParse parse;
	parse.add((const FieldParse *)Rva0056B7DEGet(), 0);
	parse.add(g_00C6D8F8, 0);
	ini->initFromINIMulti((void *)item, parse);
	((_STL::vector<const ModuleData *> *)store)->push_back(item);
}
