// cl: /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
// ?Rva0056BF1FParse@@YAXPAVINI@@PAX1PBX@Z @0x0056BF1F 255B. LivingWorldBuildPlotIcon sub-object parse: checks INI type at +8 for map.ini override (2) and reload (5) throwing INIException(8) then getNextToken plus new Rva00402F28Item via AsciiString temp plus MultiIniFieldParse two-table init plus vector push_back. Evidence: chain via just-landed 0x0056BEFB ctor plus sibling 0x0056B668 same 255B shape with ArmyIcon strings plus BlockParse LivingWorldBuildPlotIcon 0x00402E30 plus FieldParse tables 0x00C6D690 and 0x00C6D9D8.
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

class Rva00402F28Item;
class ModuleData
{
};

class Rva00402F28Item : public ModuleData
{
public:
	Rva00402F28Item(void *arg);

private:
	char m_pad[0x5C];
};

int Rva0056B7DEGet(void);
// The plot icon's own field table (retail 0x00C6D9D8): three flags.
extern const FieldParse g_00C6D9D8[] = {
	{ "Clickable", &INI::parseBool, 0, 88 },
	{ "HideWhenOccupied", &INI::parseBool, 0, 89 },
	{ "HideWhenNotOccupied", &INI::parseBool, 0, 90 },
	{ 0, 0, 0, 0 },
};

void Rva0056BF1FParse(INI *ini, void *instance, void *store, const void *userData)
{
	if (ini->m_loadType == 2)
		throw INIException(8, "Cannot override Living World objects in map.ini");
	if (ini->m_loadType == 5)
		throw INIException(8, "Reload of LivingWorldBuildPlotIconSubObjectTemplate not supported");
	const char *token = ini->getNextToken(0);
	const ModuleData *item = new Rva00402F28Item(&AsciiString(token));
	MultiIniFieldParse parse;
	parse.add((const FieldParse *)Rva0056B7DEGet(), 0);
	parse.add(g_00C6D9D8, 0);
	ini->initFromINIMulti((void *)item, parse);
	((_STL::vector<const ModuleData *> *)store)->push_back(item);
}
