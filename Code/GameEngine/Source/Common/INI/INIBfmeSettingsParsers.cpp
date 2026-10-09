// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BFME 2 INI block parsers for a saved/working settings pair, reached only
// through the block-parse registrations (Rva007ABBF6BlockParseInits.cpp lists
// each token with its parse address), so Ghidra never started a function at
// them. Each copies the saved settings over the working copy, initFromINI's
// the working copy, saves it back unless the INI load type (+0x08) is 2
// (create overrides) or 4, then notifies the owning manager through its
// virtual slot 14 when one exists. BFME 1's parseCloudEffect is the same
// body; its retail (lotrbfme.exe 0x0040BAF0) only differs by BFME 2's /O1
// register caching of the working address.
//
// The copies are compiler-generated copy assignments: with a user-declared
// operator= the compiler also caches the saved address and the parser no
// longer matches, and the implicit operator= emitted here byte-matches the
// retail callee. The tokens are target facts read from the registrations;
// the class and parser names are not known, so they keep address names, and
// the settings globals are named for their token.
//
// The field tables are retail's own rows (token, rowed INI parser, 0,
// offset), read from VA 0x00C08708 and 0x00BE5390; the tokens are retail
// strings, the table names follow the settings. The settings globals are
// defined as storage in Rva007B6880Thunks.cpp beside retail's atexit thunks.
#include "ascii_string.h"

typedef int Int;

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
	Int getLoadType() const { return m_loadType; }

	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseRGBColor(INI *ini, void *instance, void *store, const void *userData);
	static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);
	static void parseGameClientRandomVariable(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_unreconstructed_00[0x08];
	Int m_loadType;
};

struct S12
{
	int a;
	int b;
	int c;
};

// 0x0030AFFB (81B): "Fire" (registration VA 0x00DBD9AC). Saved settings at
// 0x00DFF4B8, working settings at 0x00DFF4F8 (the copy Rva00985E4 slot 14 at
// 0x0030AE42 reads), field table VA 0x00C08708, manager TheFireManager
// (0x00DFF4B4). The copy is Rva0030ADED's implicit operator= (0x0030ADED,
// 85B): two AsciiString sets, then the plain members.
class Rva0030ADED
{
public:
	AsciiString m_00;
	AsciiString m_04;
	S12 m_08;
	S12 m_14;
	unsigned char m_20;
	S12 m_24;
	S12 m_30;
	int m_3C;
};

class FireManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void slot14();
};

extern Rva0030ADED TheFireSettings;
extern Rva0030ADED TheFireSettingsSaved;
extern const FieldParse FireSettingsFields[];
const FieldParse FireSettingsFields[] =
{
	{ "TerrainFireSystem", INI::parseAsciiString, 0, 0x00 },
	{ "TerrainSmokeSystem", INI::parseAsciiString, 0, 0x04 },
	{ "BurntTerrainColor", INI::parseRGBColor, 0, 0x08 },
	{ "FuelIndicatorColor", INI::parseRGBColor, 0, 0x14 },
	{ "EnableScorches", INI::parseBool, 0, 0x20 },
	{ "ScorchFrequency", INI::parseGameClientRandomVariable, 0, 0x24 },
	{ "ScorchSize", INI::parseGameClientRandomVariable, 0, 0x30 },
	{ "ScorchIntensity", INI::parseReal, 0, 0x3C },
	{ 0, 0, 0, 0 }
};
extern FireManager *TheFireManager;

void Rva0030AFFBParse(INI *ini)
{
	TheFireSettings = TheFireSettingsSaved;
	ini->initFromINI(&TheFireSettings, FireSettingsFields);
	Int loadType = ini->getLoadType();
	if (loadType != 2 && loadType != 4)
		TheFireSettingsSaved = TheFireSettings;
	if (TheFireManager)
		TheFireManager->slot14();
}

// 0x0021526C (81B): "CloudEffect" (registration VA 0x00DB9B68). Saved
// settings at 0x00DFE1E8, working settings at 0x00DFE280 (the copy the
// record ctor 0x00214F14 reads), field table VA 0x00BE5390, manager pointer
// 0x00DFE1E4. The copy is Rva00214E02's implicit operator= (0x00214E02,
// 274B): five AsciiString sets at +0x00 +0x04 +0x08 +0x14 +0x94, the plain
// members between them. BFME 1's CloudEffect record is the same idea with a
// shorter tail (its last string is at +0x88).
class Rva00214E02
{
public:
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	int m_0C;
	int m_10;
	AsciiString m_14;
	int m_18;
	int m_1C;
	S12 m_20;
	S12 m_2C;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	unsigned char m_48;
	unsigned char m_49;
	unsigned char m_4A;
	int m_4C;
	S12 m_50;
	int m_5C;
	S12 m_60;
	int m_6C;
	S12 m_70;
	int m_7C;
	int m_80;
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
	AsciiString m_94;
};

class Rva0027070CGlobal
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38();
};

extern Rva00214E02 TheCloudEffectSettings;
extern Rva00214E02 TheCloudEffectSettingsSaved;
extern const FieldParse CloudEffectSettingsFields[];
const FieldParse CloudEffectSettingsFields[] =
{
	{ "CloudTexture", INI::parseAsciiString, 0, 0x00 },
	{ "DarkCloudTexture", INI::parseAsciiString, 0, 0x04 },
	{ "AlphaTexture", INI::parseAsciiString, 0, 0x08 },
	{ "PropagateSpeed", INI::parseReal, 0, 0x0C },
	{ "Angle", INI::parseInt, 0, 0x10 },
	{ "DissipateTexture", INI::parseAsciiString, 0, 0x14 },
	{ "DissipateStartLevel", INI::parseReal, 0, 0x18 },
	{ "DissipateSpeed", INI::parseReal, 0, 0x1C },
	{ "DarkeningFactor", INI::parseRGBColor, 0, 0x20 },
	{ "DarkeningFactorRain", INI::parseRGBColor, 0, 0x2C },
	{ "DarkeningRate", INI::parseInt, 0, 0x38 },
	{ "LighteningRate", INI::parseInt, 0, 0x3C },
	{ "CloudScrollSpeed", INI::parseReal, 0, 0x40 },
	{ "DissipateRateScale", INI::parseReal, 0, 0x44 },
	{ "LightningShadows", INI::parseBool, 0, 0x48 },
	{ "JitterLightningLightPosition", INI::parseBool, 0, 0x49 },
	{ "JitterLightningLightIntensity", INI::parseBool, 0, 0x4A },
	{ "LightningChance", INI::parseReal, 0, 0x4C },
	{ "LightningShadowColor", INI::parseRGBColor, 0, 0x50 },
	{ "LightningShadowIntensity", INI::parseReal, 0, 0x5C },
	{ "LightningDuration", INI::parseGameClientRandomVariable, 0, 0x60 },
	{ "LightningFrequency", INI::parseReal, 0, 0x6C },
	{ "LightningIntensity", INI::parseGameClientRandomVariable, 0, 0x70 },
	{ "LightningLightPosition1", INI::parseCoord2D, 0, 0x7C },
	{ "LightningLightPosition2", INI::parseCoord2D, 0, 0x84 },
	{ "LightningLightPosition3", INI::parseCoord2D, 0, 0x8C },
	{ "LightningFX", INI::parseAsciiString, 0, 0x94 },
	{ 0, 0, 0, 0 }
};
extern Rva0027070CGlobal *g_00DFE1E4;

void Rva0021526CParse(INI *ini)
{
	TheCloudEffectSettings = TheCloudEffectSettingsSaved;
	ini->initFromINI(&TheCloudEffectSettings, CloudEffectSettingsFields);
	Int loadType = ini->getLoadType();
	if (loadType != 2 && loadType != 4)
		TheCloudEffectSettingsSaved = TheCloudEffectSettings;
	if (g_00DFE1E4)
		g_00DFE1E4->slot38();
}
