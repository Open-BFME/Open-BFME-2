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
class INIException
{
public:
    INIException(int argCount, const char *format, ...);
    INIException(const INIException &that);
    ~INIException();
    char *mFailureMessage;
    int m_argumentCount;
};
class INI
{
public:
    const char *getNextToken(const char *separators = 0);
    void initFromINI(void *what, const FieldParse *parseTable);
    static void parseTerrainRoadDefinition(INI *ini);
    static void parseTerrainBridgeDefinition(INI *ini);
};
class TerrainRoadType
{
public:
    bool isBridge() const { return m_isBridge; }
    const AsciiString &getName() const { return m_name; }
    static const FieldParse m_terrainRoadFieldParseTable[];
    static const FieldParse m_terrainBridgeFieldParseTable[];
private:
    char m_unrecovered00[4];
    AsciiString m_name;
    bool m_isBridge;
};
class TerrainRoadCollection
{
public:
    TerrainRoadType *newRoad(AsciiString name);
    TerrainRoadType *newBridge(AsciiString name);
    TerrainRoadType *findBridge(AsciiString name);
};
extern TerrainRoadCollection *TheTerrainRoads;
class Rva002DB496
{
public:
    void *rva002DB496(AsciiString name);
};

void INI::parseTerrainRoadDefinition(INI *ini)
{
    AsciiString name;
    name = ini->getNextToken();
    TerrainRoadType *road = (TerrainRoadType *)
        ((Rva002DB496 *)TheTerrainRoads)->rva002DB496(name);
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
