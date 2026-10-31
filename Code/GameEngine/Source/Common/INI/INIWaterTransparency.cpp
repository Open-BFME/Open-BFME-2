// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseWaterTransparencyDefinition @0x00200EE4 (254B): Zero Hour
// INIWater.cpp's body as BFME 1 kept it (Open-BFME-1 INIWater.cpp carries
// this version, commented out). Identity from the INI block table: the
// "WaterTransparency" token's entry names this address. The first
// definition news the 0x5C-byte setting (its ctor 0x00200D80) into
// TheWaterTransparency (0x00DFF488); a map.ini definition (INI load type 2)
// copies the current one into a new override (operator= 0x00200CB1, run with
// the byte g_00E01EA8 raised as BFME 2's other override copies do), marks it
// and links it after the final override; any other second definition throws
// INIException(3, "WaterTransparency found twice"). The final override is
// filled from the setting's field-parse table 0x00C080B0. ZH's skybox
// texture refresh after an override parse is gone.
#include "ascii_string.h"

class INI;
struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class INIException
{
public:
	INIException(const char *errorMessage);
	INIException(int argCount, const char *errorMessage, ...);
	INIException(const INIException &that);
	~INIException();
	char *mFailureMessage; // +0x00
	int m_argCount; // +0x04
};

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseWaterSettingDefinition(INI *ini);
	INILoadType getLoadType(void) { return m_loadType; }
	static void parseWaterTransparencyDefinition(INI *ini);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseRGBColor(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);
private:
	int m_00; // +0x00
	int m_04; // +0x04
	INILoadType m_loadType; // +0x08 +0x08
};


template <class T> class OVERRIDE
{
public:
	OVERRIDE(const T *overridable = 0) { m_overridable = overridable; }
	OVERRIDE &operator=(const T *overridable) { m_overridable = overridable; return *this; }
	const T *getNonOverloadedPointer(void) const { return m_overridable; }
	operator const T *() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}

private:
	const T *m_overridable;
};

// The copy 0x00200CB1 is rowed as Rva00200CB1::operator=; call it.


#include "../../../Include/GameClient/Water.h"

// Native200EE4 consumes these canonical accessors inline. Keep the identical
// owned semantics local, preserving the original identical accessor COMDATs.
__forceinline Overridable *Overridable::friend_getFinalOverride()
{
 if (m_nextOverride) return m_nextOverride->friend_getFinalOverride();
 return this;
}
__forceinline void Overridable::markAsOverride()
{
 m_isOverride = true;
}

// The setting's field-parse table, .rdata 0x00C080B0 (ZH Water.cpp's
// entries; offsets are retail's).
const FieldParse WaterTransparencySetting::m_waterTransparencySettingFieldParseTable[] =
{
	{ "TransparentWaterDepth", INI::parseReal, 0, 0x18 },
	{ "TransparentWaterMinOpacity", INI::parseReal, 0, 0x1C },
	{ "StandingWaterColor", INI::parseRGBColor, 0, 0x20 },
	{ "StandingWaterTexture", INI::parseAsciiString, 0, 0x3C },
	{ "AdditiveBlending", INI::parseBool, 0, 0x38 },
	{ "RadarWaterColor", INI::parseRGBColor, 0, 0x2C },
	{ "RiverTransparencyMultiplier", INI::parseReal, 0, 0x40 },
	{ "ReflectionPlaneZ", INI::parseReal, 0, 0x4C },
	{ "ReflectionOn", INI::parseBool, 0, 0x50 },
	{ "ReflectionGuard", INI::parseCoord2D, 0, 0x54 },
	{ 0, 0, 0, 0 }
};

extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
// Owned here: allocated on first parse above; retail .data starts it at 0
// (VA 0x009FF488).
OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
extern unsigned char g_00E01EA8;

void INI::parseWaterTransparencyDefinition(INI *ini)
{
	if (TheWaterTransparency == 0) {
		TheWaterTransparency = new WaterTransparencySetting;
	} else if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES) {
		WaterTransparencySetting *wt = (WaterTransparencySetting *)(TheWaterTransparency.getNonOverloadedPointer());
		WaterTransparencySetting *wtOverride = new WaterTransparencySetting;
		g_00E01EA8 = 1;
		*wtOverride = *wt;
		g_00E01EA8 = 0;

		wtOverride->markAsOverride();

		wt->friend_getFinalOverride()->setNextOverride(wtOverride);
	} else {
		throw INIException(3, "WaterTransparency found twice");
	}

	WaterTransparencySetting *waterTrans = (WaterTransparencySetting *)(TheWaterTransparency.getNonOverloadedPointer());
	waterTrans = (WaterTransparencySetting *)(waterTrans->friend_getFinalOverride());
	ini->initFromINI(waterTrans, waterTrans->getFieldParse());
}
