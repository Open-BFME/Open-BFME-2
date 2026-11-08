// cl: /O1 /MD /EHsc /DNDEBUG
// ?parseWeatherDefinition@INI@@SAXPAV1@@Z @0x0020187A (279B).
// Zero Hour's INI::parseWeatherDefinition over BFME 2's WeatherSetting: the
// first block creates TheWeatherSetting; a later block in an override load
// (load type 2) copy-constructs an override from the current one (the
// assignment 0x00201412 runs under the global copy flag at 0x00E01EA8), marks
// it as an override (+8) and chains it behind the final override (+4); any
// other repeat throws "WeatherSetting defined twice". The final override is
// then filled from the table at 0x00BE2C10 and the snow manager's
// updateIniSettings (vtable slot 14, 0x00201165) reapplies the settings.
// The 0xB4-byte object's constructor is 0x00201618 (banked, pinned).

class INI;
#include "../../Include/Common/INI/FieldParse.h"


#include "../../Include/Common/INI/INI.h"

#include "../../Include/Common/Overridable.h"

// Retail inlines markAsOverride here (the outline is 0x00248D08).
__forceinline void Overridable::markAsOverride()
{
	m_isOverride = true;
}

class WeatherSetting : public Overridable
{
public:
	WeatherSetting();
	WeatherSetting &operator=(const WeatherSetting &other);

private:
	unsigned char m_rest[0xB4 - 0x10];
};

template <class T> class OVERRIDE
{
public:
	operator const T *() const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}
	OVERRIDE &operator=(const T *value)
	{
		m_overridable = value;
		return *this;
	}
	const T *getNonOverloadedPointer() const { return m_overridable; }

	// volatile: retail re-reads the global after the first-block assignment
	// instead of reusing the new pointer.
	const T *volatile m_overridable;
};

class SnowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void updateIniSettings();
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;
extern SnowManager *TheSnowManager;
extern unsigned char g_00E01EA8;
extern const FieldParse g_00BE2C10[];	// the WeatherSetting field table

// The WeatherSetting field table (.rdata 0x00BE2C10, 31 entries read from
// retail: token, parser, no userData, field offset), defined here beside its
// only user.
extern const FieldParse g_00BE2C10[] =
{
	{ "SnowTexture", INI::parseAsciiString, 0, 0x18 },
	{ "SnowFrequencyScaleX", INI::parseReal, 0, 0x1C },
	{ "SnowFrequencyScaleY", INI::parseReal, 0, 0x20 },
	{ "SnowAmplitude", INI::parseReal, 0, 0x24 },
	{ "SnowPointSize", INI::parseReal, 0, 0x28 },
	{ "SnowMaxPointSize", INI::parseReal, 0, 0x2C },
	{ "SnowMinPointSize", INI::parseReal, 0, 0x30 },
	{ "SnowQuadSize", INI::parseReal, 0, 0x34 },
	{ "SnowBoxHeight", INI::parseReal, 0, 0x38 },
	{ "SnowSpacing", INI::parseReal, 0, 0x3C },
	{ "SnowSpeed", INI::parseReal, 0, 0x40 },
	{ "SnowPointSprites", INI::parseBool, 0, 0x44 },
	{ "SnowEnabled", INI::parseBool, 0, 0x45 },
	{ "IsSnowing", INI::parseBool, 0, 0x46 },
	{ "NumberTiles", INI::parseInt, 0, 0x48 },
	{ "SnowXYSpeed", INI::parseCoord2D, 0, 0x4C },
	{ "LightningEnabled", INI::parseBool, 0, 0x54 },
	{ "LightningFactor", INI::parseGameClientRandomVariable, 0, 0x58 },
	{ "LightningDuration", INI::parseInt, 0, 0x64 },
	{ "LightningChance", INI::parseReal, 0, 0x68 },
	{ "SpellEnabled", INI::parseBool, 0, 0x6C },
	{ "SpellDuration", INI::parseInt, 0, 0x70 },
	{ "RampControl", INI::parseCoord2D, 0, 0x74 },
	{ "RampSpacing", INI::parseCoord2D, 0, 0x84 },
	{ "RampSpeed", INI::parseCoord2D, 0, 0x7C },
	{ "HardwareFogColor", INI::parseRGBColor, 0, 0x8C },
	{ "HardwareFogEnable", INI::parseBool, 0, 0x98 },
	{ "HardwareFogStart", INI::parseReal, 0, 0x9C },
	{ "HardwareFogEnd", INI::parseReal, 0, 0xA0 },
	{ "CloudTextureSize", INI::parseCoord2D, 0, 0xA4 },
	{ "CloudOffsetPerSecond", INI::parseCoord2D, 0, 0xAC },
	{ 0, 0, 0, 0 }
};

static WeatherSetting *g_ws() { return (WeatherSetting *)TheWeatherSetting.getNonOverloadedPointer(); }

void INI::parseWeatherDefinition(INI *ini)
{
	WeatherSetting *ws = g_ws();
	const WeatherSetting *current = 0;
	if (ws) {
		if (ws->friend_getNextOverride())
			current = (const WeatherSetting *)ws->friend_getNextOverride()->friend_getFinalOverride();
		else
			current = ws;
	}
	if (current == 0) {
		TheWeatherSetting = new WeatherSetting;
	} else if (ini->m_loadType == 2) {
		WeatherSetting *wsOverride = new WeatherSetting;
		g_00E01EA8 = 1;
		*wsOverride = *ws;
		g_00E01EA8 = 0;
		wsOverride->markAsOverride();
		Overridable *tail = ws->friend_getNextOverride() ? ws->friend_getNextOverride()->friend_getFinalOverride() : ws;
		tail->setNextOverride(wsOverride);
	} else {
		throw INIException(3, "WeatherSetting defined twice");
	}

	const WeatherSetting *setting = TheWeatherSetting.getNonOverloadedPointer();
	ini->initFromINI((void *)(setting->getNextOverride() ? const_cast<Overridable *>(setting->getNextOverride())->friend_getFinalOverride() : setting), g_00BE2C10);

	if (TheSnowManager)
		TheSnowManager->updateIniSettings();
}
