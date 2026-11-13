// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseTerrainDefinition @0x00200A65 (133B): Zero Hour INITerrain.cpp.
// Identity from the INI block table: the "Terrain" token's entry names this
// address. The body reads the name token, looks it up through the rowed
// TerrainTypeCollection::findTerrain 0x00317D18 on TheTerrainTypes, makes it
// with the rowed newTerrain 0x0031816C on a miss and fills it from the type's
// field-parse table 0x00C0C3A8 (TerrainType::getFieldParse(), inline in ZH).
#include "ascii_string.h"

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/TerrainType.h"

#include "../../../Include/Common/TerrainTypeCollection.h"

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

// BFME1 INIWaterTextureList.cpp at 34f59164f6d1efd413c5fd37f4894ec834c3c0fe.
// Native 200AEA..200BB4 and WB B29220 establish the WaterTextureList callback.
// Target adaptations: shared AsciiString::set, existing six-entry lookup,
// three-argument diagnostic stream getter and target pointer/field table.
class Rva000C2A30Owner
{
public:
	void dump();
};

class Rva003B1820
{
public:
	void *rva003B1820(const StringBase<char> &name);
};

#include "../debug.h"

#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BfmeAwakenLog.h"

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second, int third);
};

extern Debug *theDebug;
#define TheBfmeAwakenDebug (reinterpret_cast<BfmeAwakenDebug *>(theDebug))
// Independent four-byte zero-initialized pointer cell, retail VA E02D50.
// TheSpecialPowerStore is the preceding cell E02D4C; its broad data-ledger
// extent does not establish ownership of this texture-table pointer.
Rva003B1820 *g_00E02D50;
extern const FieldParse g_waterTextureFieldParseTable[];
extern void _bfme_debugRecordCallsite(int kind);

void iniParseWaterTexturesDefinition(INI *ini)
{
	AsciiString name;
	const char *token = ini->getNextToken();
	name.set(token);

	// Native pointer cell E02D50; distinct from SpecialPowerStore E02D4C.
	Rva000C2A30Owner *list = static_cast<Rva000C2A30Owner *>(g_00E02D50->rva003B1820(*reinterpret_cast<const StringBase<char>*>(&name)));

	if (list == 0)
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		const char *text = name.str();
		BfmeAwakenLog *log = TheBfmeAwakenDebug->slot6C(0, 0, 0);
		log->slot38(Debug::Format("Unable to find water texture type '%s'\n", text));
		log->slot4C(1);
	}
	else
	{
		ini->initFromINI(list, g_waterTextureFieldParseTable);
		list->dump();
	}
}

// The terrain class names (retail .data 0x00DBE340, 47 names and a null), the
// "Class" field's lookup list; read from retail.
const char *terrainTypeNames[] =
{
	"NONE",
	"NEXT",
	"Region",
	"Minas_Tirith",
	"Osgiliath",
	"Dead_Marshes",
	"Edoras",
	"Helm's_Deep",
	"Paths_of_Dead",
	"Fangorn_Forest",
	"Misty_Mountains",
	"Rivendell",
	"Moria",
	"The_Shire",
	"Isengard",
	"Mordor",
	"Misc_Village",
	"Misc_Grassland",
	"Misc_Town",
	"Misc_Woodland",
	"Misc_Water",
	"Type",
	"Grass",
	"Rock",
	"Dirt",
	"Snow",
	"Cliff",
	"Misc",
	"DESERT_1",
	"DESERT_2",
	"DESERT_3",
	"EASTERN_EUROPE_1",
	"EASTERN_EUROPE_2",
	"EASTERN_EUROPE_3",
	"SWISS_1",
	"SWISS_2",
	"SWISS_3",
	"SNOW_1",
	"SNOW_2",
	"SNOW_3",
	"ASPHALT",
	"CONCRETE",
	"TRANSITION",
	"SAND",
	"WOOD",
	"BLEND_EDGE",
	"LOTR_NEW",
	0
};

// TerrainType's field-parse table, retail .rdata 0x00C0C3A8: Zero Hour's four
// fields plus BFME2's TerrainObject (offset 0). Parsers by their rowed
// addresses: parseAsciiString 0x0002F11E, parseBool 0x0002E850, the "Class"
// list parser 0x00339E1C, the TerrainObject parser 0x00318242.
const FieldParse TerrainType::m_terrainTypeFieldParseTable[] =
{
	{ "Texture", INI::parseAsciiString, 0, 0x08 },
	{ "BlendEdges", INI::parseBool, 0, 0x0C },
	{ "Class", INI::Rva00339E1C_ParseBrowser, terrainTypeNames, 0x10 },
	{ "RestrictConstruction", INI::parseBool, 0, 0x1C },
	{ "TerrainObject", INI::Rva00318242_ParseNamedReal, 0, 0x00 },
	{ 0, 0, 0, 0 },
};

// INI block registrations. BFME's INI keeps its block types on a list of
// 12-byte BlockParse nodes; each unit links its own nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the
// link. MSVC 7.1 builds token and parse in .data, so each node's .text$yc
// initializer is only the 21-byte link (retail .CRT$XCU 0x007AD636..0x007AD64B,
// nodes 0x00DB94E0..0x00DB94EC in definition order).
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

BlockParse theTerrainBlockParse( "Terrain", INI::parseTerrainDefinition );
BlockParse theWaterTextureListBlockParse( "WaterTextureList", iniParseWaterTexturesDefinition );
