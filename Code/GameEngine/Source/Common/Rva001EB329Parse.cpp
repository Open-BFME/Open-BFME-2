// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva001EB329@Rva001EB329@@QAEXPAVINI@@@Z, retail 0x001EB329, 89 bytes.
// __thiscall INI parse validator: initFromINI(this) via rowed 0x0002DE78 and table
// CampaignMissionFieldParse (VA 0x00BDF0E8), then if map string at +4 isEmpty (rowed StringBase 0x00001E2F) throw
// INIException code 3 with retail literal using mission string at +0 as t ? t+8
// : g_Rva0107301CEmptyString. Throw idiom (ctor 0x0002F681 plus CxxThrow plus
// throwinfo anchor) from Rva004135CDParse. Evidence: leaf lane, caller 0x001ED326,
// prev Rva001EB2CCMapPath and next Rva001EB3A6BoundsCheck share flags.
#include "ascii_string.h"

class INI;
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"


// Retail's campaign mission field table at VA 0x00BDF0E8 (.rdata, 112 bytes:
// six records and the zero sentinel), transcribed from retail's own bytes.
extern const FieldParse CampaignMissionFieldParse[] =
{
	{ "Map",                                 &INI::parseAsciiString,             0, 0x04 },
	{ "IntroMovie",                          &INI::parseAsciiString,             0, 0x08 },
	{ "LoadScreenImage",                     &INI::parseAsciiString,             0, 0x0C },
	{ "LoadScreenMusicTrack",                &INI::parseAudioEventRTS,                  0, 0x10 },
	{ "MillisecondsAfterStartToStartFadeUp", &INI::parseDurationUnsignedInt,     0, 0x14 },
	{ "DelayCarryoverSpawningOf",            &INI::parseAsciiStringVectorAppend, 0, 0x18 },
	{ 0, 0, 0, 0 }
};




class Rva001EB329
{
public:
	void rva001EB329(INI *ini);
private:
	AsciiString m_missionName;
	AsciiString m_mapName;
};

void Rva001EB329::rva001EB329(INI *ini)
{
	ini->initFromINI(this, CampaignMissionFieldParse);
	if (((const StringBase<char> *)&m_mapName)->isEmpty())
	{
		char *t = *(char **)this;
		const char *s = t ? t + 8 : "";
		throw INIException(3, "Campaign missions must have a Map. %s does not", s);
	}
}
