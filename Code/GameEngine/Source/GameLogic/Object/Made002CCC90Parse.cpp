// cl: /DNDEBUG /MD
//
// ?q4Notify002CCC90@@YAXPAXPAVMade002CCC90@@HH@Z @0x0050BBEB (58B).
// LuaEventNugget field parser: same MultiIni init tail as the DOT/StealMoney
// q4Notify pair (53B at 0x0050B13A/0x0050B5F6) but builds its one-entry table
// via MultiIniFieldParse::add (rowed 0x0002BC6E) with the FieldParse at
// 0x00864F18 (DIR32) and index 0, instead of the shared buildFieldParse static.
// Caller is ?parseLuaEventNugget@@YAXPAVINI@@PAVWeaponTemplate@@@Z at
// 0x002CCCD5 (Code/GameEngine/Source/GameLogic/Object/WeaponNuggetParse.cpp),
// news 0x134. The four relocs (ctor/add/init/EH none) are gate-filled.

class Made002CCC90;

class INI;

#include "../../../Include/Common/INI/FieldParse.h"


#include "../../../Include/Common/INI/INI.h"

// The table pushed at 0x00C64F18 (.rdata): 5 16-byte records and the
// null terminator read from retail, parsers resolved to their ledger
// names, userData null, nugget offsets 0x128-0x132. The table name is
// descriptive; the original spelling is unknown.
extern const FieldParse LuaEventFieldTable[] =
{
	{ "LuaEvent",      &INI::parseAsciiString,  0, 0x128 },
	{ "Radius",        &INI::parseReal,         0, 0x12C },
	{ "SendToEnemies", &INI::parseBool,         0, 0x130 },
	{ "SendToAllies",  &INI::parseBool,         0, 0x131 },
	{ "SendToNeutral", &INI::parseBool,         0, 0x132 },
	{ 0, 0, 0, 0 }
};

void q4Notify002CCC90(void *ini, Made002CCC90 *nugget, int c, int d)
{
	MultiIniFieldParse tmp;
	tmp.add(LuaEventFieldTable, 0);
	((INI *)ini)->initFromINIMulti(nugget, tmp);
}
