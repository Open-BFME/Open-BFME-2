// cl: /O1 /DNDEBUG /MD
//
// TunnelContainModuleData parse-unit (see ContainModuleDataFriendNew.cpp for
// the owner, which registers this proc with initFromINIMultiProc).
//
// ?buildFieldParse@TunnelContainModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0024BCD2, 27 bytes. Chained on the rowed
// HordeGarrisonContainModuleData base proc at 0x47A025, then the own table
// at 0x00BEEAF8, through the rowed MultiIniFieldParse::add at 0x2BC6E.
// The owning factory pushes this proc VA; ModuleFactory registers it
// under "TunnelContain". Row supersedes the parse pin.

class MultiIniFieldParse;

#include "../../../../Include/Common/INI/INI.h"

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

#include "../../../../Include/Common/INI/FieldParse.h"

// The own table at 0x00BEEAF8 (data row): one field, TimeForFullHeal through
// the rowed INI::parseDurationReal 0x00738B0A into +0xD4, then the null
// terminator. Zero Hour's TunnelContainModuleData parses the same token.
extern const FieldParse TunnelContainModuleDataFieldParse[2] =
{
	{ "TimeForFullHeal", &INI::parseDurationReal, 0, 0xD4 },
	{ 0, 0, 0, 0 }
};


#include "../../../../Include/GameLogic/Module/HordeGarrisonContainModuleData.h"

class TunnelContainModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@TunnelContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0024BCD2
void TunnelContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	HordeGarrisonContainModuleData::buildFieldParse(parse);
	parse.add(TunnelContainModuleDataFieldParse, 0);
}
