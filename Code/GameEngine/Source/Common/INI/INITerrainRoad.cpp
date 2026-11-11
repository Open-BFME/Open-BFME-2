// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Reference: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/Common/INI/INITerrainRoad.cpp. Its road parser
// preserves the ZH parser's lookup/create/field-parse purpose and the BFME
// exception text. Target identity: WB iniParseTerrainRoadDefinition at
// 0x00B243A0, paired by that text with retail 0x001FF288..0x001FF347.
// Target reads name at +4 and bridge flag at +8; the name accessor is
// inline here, as retail reads the StringBase header directly. The existing
// lookup provider retains its address-derived identity pending reconciliation.
#include "ascii_string.h"

struct FieldParse;
#include "../../../Include/Common/INI/FieldParse.h"
#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/GameClient/TerrainRoadType.h"
#include "../../../Include/GameClient/TerrainRoadCollection.h"
extern TerrainRoadCollection *TheTerrainRoads;

void INI::parseTerrainRoadDefinition(INI *ini)
{
    AsciiString name;
    name = ini->getNextToken();
    TerrainRoadType *road = TheTerrainRoads->findRoad(name);
    if (road)
    {
        if (road->isBridge())
            throw INIException(3, "Redefining bridge '%s' as a road!", road->getName().str());
    }
    else
        road = TheTerrainRoads->newRoad(name);
    ini->initFromINI(road, TerrainRoadType::m_terrainRoadFieldParseTable);
}

// BFME 1's same donor TU provides this sibling. WorldBuilder's
// iniParseTerrainBridgeDefinition at 0x00AC2760 and its unique error text
// establish target identity. Native 0x001DAEB8..0x001DAF77 supplies the
// separate bridge list lookup, opposite flag check, and bridge parse table.
void INI::parseTerrainBridgeDefinition(INI *ini)
{
    AsciiString name;
    name = ini->getNextToken();
    TerrainRoadType *bridge = TheTerrainRoads->findBridge(name);
    if (bridge)
    {
        if (!bridge->isBridge())
            throw INIException(3, "Redefining road '%s' as a bridge!\n", bridge->getName().str());
    }
    else
        bridge = TheTerrainRoads->newBridge(name);
    ini->initFromINI(bridge, TerrainRoadType::m_terrainBridgeFieldParseTable);
}

// INI block registration. BFME's INI keeps its block types on a list of
// 12-byte BlockParse nodes; each unit links its own nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the
// link. MSVC 7.1 builds token and parse in .data, so each node's .text$yc
// initializer is only the 21-byte link (retail .CRT$XCU 0x007AD57F,
// node 0x00DB9404).
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theRoadBlockParse( "Road", INI::parseTerrainRoadDefinition );
