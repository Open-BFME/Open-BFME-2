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

class Debug
{
public:
	class Format
	{
	public:
		explicit Format(const char *format, ...);
		operator const char *() const { return m_buffer; }

	private:
		char m_buffer[512];
	};
};

class BfmeAwakenLog
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
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

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
extern const FieldParse g_00C1EE54[];
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
		ini->initFromINI(list, g_00C1EE54);
		list->dump();
	}
}
