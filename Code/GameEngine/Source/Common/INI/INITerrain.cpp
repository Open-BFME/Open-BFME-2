// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseTerrainDefinition @0x00200A65 (133B): Zero Hour INITerrain.cpp.
// Identity from the INI block table: the "Terrain" token's entry names this
// address. The body reads the name token, looks it up through the rowed
// TerrainTypeCollection::findTerrain 0x00317D18 on TheTerrainTypes, makes it
// with the rowed newTerrain 0x0031816C on a miss and fills it from the type's
// field-parse table 0x00C0C3A8 (TerrainType::getFieldParse(), inline in ZH).
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);

	static void parseTerrainDefinition(INI *ini);
};

class TerrainType
{
public:
	static const FieldParse m_terrainTypeFieldParseTable[];
	const FieldParse *getFieldParse(void) { return m_terrainTypeFieldParseTable; }
};

class TerrainTypeCollection
{
public:
	TerrainType *findTerrain(AsciiString name);
	TerrainType *newTerrain(AsciiString name);
};

extern TerrainTypeCollection *TheTerrainTypes;

void INI::parseTerrainDefinition(INI *ini)
{
	AsciiString name;
	TerrainType *terrainType;

	const char *c = ini->getNextToken();
	name.set(c);

	terrainType = TheTerrainTypes->findTerrain(name);
	if (terrainType == 0)
		terrainType = TheTerrainTypes->newTerrain(name);

	ini->initFromINI(terrainType, terrainType->getFieldParse());
}
