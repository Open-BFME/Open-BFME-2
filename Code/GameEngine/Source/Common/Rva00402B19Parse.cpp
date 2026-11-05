// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?parseLivingWorldBuildingIconDefinition@@YAXPAVINI@@@Z @0x00402B19 202B: the
// LivingWorldBuildingIconTemplate block parser. Same shape as the
// LivingWorld sub-object parsers in Rva0056BF1FParse.cpp: map.ini override
// (INI type 2) and reload (type 5) throw INIException(8, ...), then the
// template is made by name through TheLivingWorldManager (0x002140DB news the
// 0x1C-byte Rva00402BE3 and files it in the +0x280 map) and filled from the
// shared 0x0056B767 table plus its own table 0x00C38380, whose +0x10/+0x14/
// +0x18 fields and +0x04 list are Rva00402BE3's. Reached through a block
// parse table, not a direct call; the address name stays.
#include "ascii_string.h"

#include "../../Include/Common/INI/FieldParse.h"


// The six field parsers retail's three LivingWorld icon tables reach. Each is an
// already-rowed body (0x00339900, 0x001DEE74, 0x0056B668, 0x0056BDFC,
// 0x0056BF1F), so the tables below resolve instead of trading one unresolved
// name for another. Declared with the real INI* first argument because that is
// what makes the mangled names the census saw match.
void Rva001DEE74Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva0056B668Parse(INI *ini, void *instance, void *store, const void *userData);
void Rva0056BDFCParse(INI *ini, void *instance, void *store, const void *userData);
void Rva0056BF1FParse(INI *ini, void *instance, void *store, const void *userData);


#include "../../Include/Common/INI/INI.h"

class Rva00402BE3;
class Rva003F9FA9;
class Rva00402EFA;

#include "../../Include/GameLogic/LivingWorldManager.h"

extern LivingWorldManager *TheLivingWorldManager;

int Rva0056B767Get(void);

// Retail VA 0x00C38380 (.rdata, file offset 0x00837D80): the building icon's own
// four field records - three sound events through the rowed audio-token parser
// 0x00339900 and the object name through the rowed Rva0056BDFC parser - plus the
// zero sentinel. The +0x10/+0x14/+0x18 offsets are the three sound slots and
// +0x04 the name slot both the parser above and the rowed constructor 0x00402EFA
// fill through the shared 0x0056B767 table.
// Symbol ?g_00C38380@@3QBUFieldParse@@B, transcribed below.
extern const FieldParse g_00C38380[] =
{
	{ "OnSelectedSound",              &INI::parseAudioEventRTS, 0, 0x10 },
	{ "OnConstructionBegunSound",     &INI::parseAudioEventRTS, 0, 0x14 },
	{ "OnConstructionFinishedSound",  &INI::parseAudioEventRTS, 0, 0x18 },
	{ "Object",                       &Rva0056BDFCParse, 0, 0x04 },
	{ 0, 0, 0, 0 }
};

void parseLivingWorldBuildingIconDefinition(INI *ini)
{
	if (ini->m_loadType == 2)
		throw INIException(8, "Cannot override Living World objects in map.ini");
	if (ini->m_loadType == 5)
		throw INIException(8, "LivingWorldBuildingIconTemplate does not support rapid iteration");
	Rva00402BE3 *icon = TheLivingWorldManager->rva002140DB(AsciiString(ini->getNextToken(0)));
	MultiIniFieldParse parse;
	parse.add((const FieldParse *)Rva0056B767Get(), 0);
	parse.add(g_00C38380, 0);
	ini->initFromINIMulti(icon, parse);
}

// Native 3F9EDF..3F9FA9, cdecl202B. The rowed initializer7AFC56
// binds this callback to the LivingWorldArmyIcon token. Both guards and
// the complete MultiIniFieldParse sequence match the building-icon sibling;
// retail supplies its own rapid-iteration literal, manager factory214060,
// and field tableC37788. The adjacent rowed constructor3F9FA9 is called by
// that factory. BFME1 donor968ca36c Common/INI/INIArmyIcon.cpp confirms the
// subsystem relationship but has different guards and a single-table parse.
// No donor layout or original callback method name is asserted here.
extern const FieldParse LivingWorldArmyIconFields[] =
{
	{ "OnSelectedSound",                      &INI::parseAudioEventRTS, 0, 0x10 },
	{ "OnMovePlannedSound",                   &INI::parseAudioEventRTS, 0, 0x14 },
	{ "OnMoveStartedSound",                   &INI::parseAudioEventRTS, 0, 0x18 },
	{ "WelcomeReinforcementsSound",           &INI::parseAudioEventRTS, 0, 0x1C },
	{ "KickOutReinforcementsSound",           &INI::parseAudioEventRTS, 0, 0x20 },
	{ "DisbandUnitSound",                     &INI::parseAudioEventRTS, 0, 0x24 },
	{ "RetreatTeleportToHomeRegionEvaEvent",  &Rva001DEE74Parse,  0, 0x28 },
	{ "RetreatTeleportToNonHomeRegionEvaEvent", &Rva001DEE74Parse, 0, 0x2C },
	{ "Object",                                &Rva0056B668Parse, 0, 0x04 },
	{ 0, 0, 0, 0 }
};
void parseLivingWorldArmyIconDefinition(INI *ini)
{
    if (ini->m_loadType == 2)
        throw INIException(8, "Cannot override Living World objects in map.ini");
    if (ini->m_loadType == 5)
        throw INIException(8, "LivingWorldArmyIconTemplate does not support rapid iteration");
    Rva003F9FA9 *icon = TheLivingWorldManager->rva00214060(AsciiString(ini->getNextToken(0)));
    MultiIniFieldParse parse;
    parse.add((const FieldParse *)Rva0056B767Get(), 0);
    parse.add(LivingWorldArmyIconFields, 0);
    ini->initFromINIMulti(icon, parse);
}

// Native 402E30..402EFA, cdecl202B. Rowed initializer7AFD61 binds
// LivingWorldBuildPlotIcon. Factory214156 has RET4, allocates24 bytes,
// calls constructor402EFA with the name, and inserts into manager+294.
// Target literalC38488 and field tableC38448 distinguish this sibling.
// Retail VA 0x00C38448 (.rdata, file offset 0x00837E48): two sound
// records through the rowed audio-token parser 0x00339900 and the object name
// through the rowed Rva0056BF1F parser, then the zero sentinel - the 64-byte
// table the ledger bounds before the sibling's rapid-iteration literal.
extern const FieldParse LivingWorldBuildPlotIconFields[] =
{
	{ "OnSelectedSound",         &INI::parseAudioEventRTS, 0, 0x10 },
	{ "OnBuildingDestroyedSound", &INI::parseAudioEventRTS, 0, 0x14 },
	{ "Object",                   &Rva0056BF1FParse, 0, 0x04 },
	{ 0, 0, 0, 0 }
};
void parseLivingWorldBuildPlotIconDefinition(INI *ini)
{
    if (ini->m_loadType == 2)
        throw INIException(8, "Cannot override Living World objects in map.ini");
    if (ini->m_loadType == 5)
        throw INIException(8, "LivingWorldBuildPlotIconTemplate does not support rapid iteration");
    Rva00402EFA *icon = TheLivingWorldManager->rva00214156(AsciiString(ini->getNextToken(0)));
    MultiIniFieldParse parse;
    parse.add((const FieldParse *)Rva0056B767Get(), 0);
    parse.add(LivingWorldBuildPlotIconFields, 0);
    ini->initFromINIMulti(icon, parse);
}
