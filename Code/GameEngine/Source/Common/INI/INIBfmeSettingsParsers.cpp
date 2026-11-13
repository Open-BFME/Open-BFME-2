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

#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/S12.h"

// 0x0030AFFB (81B): "Fire" (registration VA 0x00DBD9AC). Saved settings at
// 0x00DFF4B8, working settings at 0x00DFF4F8 (the copy Rva00985E4 slot 14 at
// 0x0030AE42 reads), field table VA 0x00C08708, manager TheFireManager
// (0x00DFF4B4). The copy is Rva0030ADED's implicit operator= (0x0030ADED,
// 85B): two AsciiString sets, then the plain members.
#include "../../../../Libraries/Include/Lib/RGBColor.h"

struct RvaFireColor : RGBColor
{
	RvaFireColor(float redValue, float greenValue, float blueValue) { red = redValue; green = greenValue; blue = blueValue; }
};

// The client random variable (rowed setRange 0x002341E7); its inline
// default constructor zeroes all three words. No user-declared copy here, so
// the settings copy keeps its inline 12-byte moves.
class GameClientRandomVariable
{
public:
	enum DistributionType { CONSTANT, UNIFORM };

	GameClientRandomVariable() { m_type = CONSTANT; m_low = 0.0f; m_high = 0.0f; }
	void setRange(float low, float high, DistributionType type = UNIFORM);

private:
	DistributionType m_type;
	float m_low;
	float m_high;
};

class Rva0030ADED
{
public:
	Rva0030ADED();

	AsciiString m_00;
	AsciiString m_04;
	RvaFireColor m_08;
	RvaFireColor m_14;
	bool m_20;
	GameClientRandomVariable m_scorchFrequency;
	GameClientRandomVariable m_scorchSize;
	float m_3C;
};

// 0x0030AEB6 (217B): the defaults, constructed into both settings globals by
// retail's initializers at 0x007AE79E/0x007AE7B4.
Rva0030ADED::Rva0030ADED() :
	m_08(0.2f, 0.2f, 0.2f),
	m_14(0.8f, 0.7f, 0.6f),
	m_20(false),
	m_3C(0.95f)
{
	m_scorchFrequency.setRange(30.0f, 90.0f);
	m_scorchSize.setRange(5.0f, 20.0f);
}

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

void parseFireDefinition(INI *ini)
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
	Rva00214E02();

	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	int m_propagateSpeed;
	int m_angle;
	AsciiString m_14;
	int m_dissipateStartLevel;
	int m_dissipateSpeed;
	S12 m_20;
	S12 m_darkeningFactorRain;
	int m_darkeningRate;
	int m_3C;
	int m_cloudScrollSpeed;
	int m_dissipateRateScale;
	unsigned char m_lightningShadows;
	unsigned char m_jitterLightningLightPosition;
	unsigned char m_jitterLightningLightIntensity;
	int m_lightningChance;
	S12 m_lightningShadowColor;
	int m_lightningShadowIntensity;
	GameClientRandomVariable m_lightningDuration;
	int m_lightningFrequency;
	GameClientRandomVariable m_lightningIntensity;
	int m_lightningLightPosition1;
	int m_80;
	int m_lightningLightPosition2;
	int m_88;
	int m_lightningLightPosition3;
	int m_90;
	AsciiString m_lightningFX;
};

// 0x002150CE (51B): the defaults, constructed into both settings globals by
// retail's initializers at 0x007AD9BC/0x007AD9D2. Only the five strings and
// the two client random variables (LightningDuration +0x60,
// LightningIntensity +0x70) have constructors; their inline ones zero them.
Rva00214E02::Rva00214E02()
{
}

class Rva0027070CGlobal
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();

	unsigned char m_pad04[0x1c];
	unsigned char m_active;		// +0x20
	unsigned char m_pad21[0x97];
	void *m_stateB8;		// +0xB8
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
extern Rva0027070CGlobal *TheCloudEffectManager;

void parseCloudEffectDefinition(INI *ini)
{
	TheCloudEffectSettings = TheCloudEffectSettingsSaved;
	ini->initFromINI(&TheCloudEffectSettings, CloudEffectSettingsFields);
	Int loadType = ini->getLoadType();
	if (loadType != 2 && loadType != 4)
		TheCloudEffectSettingsSaved = TheCloudEffectSettings;
	if (TheCloudEffectManager)
		TheCloudEffectManager->slot38();
}

class Rva009519B
{
public:
	virtual void rva002150BE();
};

void Rva009519B::rva002150BE()
{
	TheCloudEffectSettings = TheCloudEffectSettingsSaved;
}


// Retail 0x00212118 (107B EH __stdcall, by-value AsciiString): the BFME 1
// twin is Rva00612560BfmeState.cpp (lotrbfme 0x00612560). Tests the shared
// cloud/weather manager, calls slot 14, compares the by-value string with
// the data literal "ACTIVE" (BFME 2 VA 0x00BE51BC) through the rowed
// StringBase<char>::compare 0x000069B1, sets the manager's +0x20 flag, and
// calls slot 16 when +0xB8 is clear. BFME 2 shifts BFME 1's +0x1C/+0xA8 to
// +0x20/+0xB8 and slots 9/11 to 14/16.
void __stdcall setCloudEffectState(AsciiString text)
{
	if (TheCloudEffectManager != 0)
	{
		TheCloudEffectManager->slot38();
		if (((const StringBase<char> *)&text)->compare("ACTIVE") == 0)
		{
			TheCloudEffectManager->m_active = 1;
			if (TheCloudEffectManager->m_stateB8 == 0)
				TheCloudEffectManager->slot40();
		}
		else
		{
			TheCloudEffectManager->m_active = 0;
		}
	}
}
