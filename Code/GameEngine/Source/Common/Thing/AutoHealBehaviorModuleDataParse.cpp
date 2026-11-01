// cl: /DNDEBUG /MD
//
// Retail proc at 0x50B5CF adds an UpgradeMux table and a module table; both
// offsets are 0. Its donor-derived AutoHeal class identity conflicts with the
// factory-pinned AutoHeal proc at 0x256929, so keep this address anonymous.

class MultiIniFieldParse;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

// Retail VA 0x00C64D60 (.rdata): 1 field records and a zero sentinel.
extern const FieldParse g_00C64D60[] = {
	{ "AmountStolenPerAttack", &INI::parseReal, 0, 0x128 },
	{ 0, 0, 0, 0 }
};


class Rva0050B5CFBuildFieldParse
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

int __cdecl Rva00507552Get();

// ?buildFieldParse@Rva0050B5CFBuildFieldParse@@SAXAAVMultiIniFieldParse@@@Z
void Rva0050B5CFBuildFieldParse::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>(Rva00507552Get()), 0);
	parse.add(g_00C64D60, 0);
}
