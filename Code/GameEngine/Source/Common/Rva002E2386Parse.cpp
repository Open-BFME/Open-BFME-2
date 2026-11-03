// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?parseLivingWorldPlayerTemplateDefinition@@YAXPAVINI@@@Z @0x002E2386 231B. LivingWorldPlayerTemplate block parse.
// Evidence: BlockParse LivingWorldPlayerTemplate 0x00DBD0A8 parse 0x002E2386; REF slot 0x009BD0B0 neighbours LivingWorldPlayerTemplate NONE HOLD; error literals LivingWorldPlayerTemplateStore Invalid data passed in 0x00804AF0 and No name specified 0x00804ABC via INIException 0x0002F681 plus TI1 0x008FE2FC; getNextToken 0x0002DF97 plus StringBase ctor 0x00037BA0 plus set 0x000366F0 plus releaseBuffer 0x00036410; new 0x40 plus ctor 0x002E0906; FieldParse g_00C04820 via initFromINI 0x0002DE78; store TheLivingWorldPlayerTemplateStore plus vector push_back 0x004DFCB0.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"

struct FieldParse;

#include "../../Include/Common/INI/INI.h"

#include "../../Include/Common/INI/FieldParse.h"

// Retail 0x00C3BC20: seventeen integer fields followed by a zero terminator.
// RVA 0x00339900's field parser: the audio-token routine GlobalWeatherSystem.cpp
// names directly for "WeatherSound" (mangled
// ?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z), aliased because this TU spells its
// INI view locally and a redeclaration of the same free function is fine.
#define Rva00333900ParseAlias INI::parseAudioEventRTS

extern const FieldParse g_00C3BC20[] =
{
	{"DesiredSoldierRatio", INI::parseInt, 0, 4},
	{"DesiredArcherRatio", INI::parseInt, 0, 8},
	{"DesiredPikemenRatio", INI::parseInt, 0, 12},
	{"DesiredCavalryRatio", INI::parseInt, 0, 16},
	{"DesiredMonsterRatio", INI::parseInt, 0, 20},
	{"DesiredHeroRatio", INI::parseInt, 0, 24},
	{"DesiredFortressRatio", INI::parseInt, 0, 28},
	{"BuildingScoreArmory", INI::parseInt, 0, 36},
	{"BuildingScoreBarracks", INI::parseInt, 0, 40},
	{"BuildingScoreCastle", INI::parseInt, 0, 44},
	{"BuildingScoreFarm", INI::parseInt, 0, 48},
	{"BonusPreferenceResource", INI::parseInt, 0, 52},
	{"BonusPreferenceArmy", INI::parseInt, 0, 56},
	{"BonusPreferenceLegendary", INI::parseInt, 0, 60},
	{"BonusPreferenceAttack", INI::parseInt, 0, 64},
	{"BonusPreferenceDefense", INI::parseInt, 0, 68},
	{"BonusPreferenceExperience", INI::parseInt, 0, 72},
	{0, 0, 0, 0}
};


struct _s__ThrowInfo;

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

// Retail's LivingWorldPlayerTemplate table at RVA 0x00804820 (.rdata, 256 bytes
// = fifteen 16-byte records plus the zero sentinel), transcribed from retail's
// own bytes. The parse procedures are targets of retail's own pointers and are
// all rowed: 0x0042F11E -> ?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z (row 0x2F11E,
// INI_parseAsciiString.cpp), 0x0042EF56 -> ?parseInt@INI@@SAXPAV1@PAX1PBX@Z (row
// 0x2EF56, INI_parseInt.cpp) and 0x0042EF56's siblings 0x00739900 ->
// ?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z (row 0x339900, the audio-token parser
// GlobalWeatherSystem.cpp already uses for "WeatherSound"). Offsets are the
// record's own field offsets. The `extern` on the definition keeps the object
// external, exactly as the g_00C3BC20 table above.
extern const FieldParse g_00C04820[] =
{
	{"Faction", &INI::parseAsciiString, 0, 4},
	{"StartingWorldCP", &INI::parseInt, 0, 8},
	{"StartingTacticalCP", &INI::parseInt, 0, 0x10},
	{"StartingHeroCP", &INI::parseInt, 0, 0x18},
	{"MaxWorldCP", &INI::parseInt, 0, 0xC},
	{"MaxTacticalCP", &INI::parseInt, 0, 0x14},
	{"MaxHeroCP", &INI::parseInt, 0, 0x1C},
	{"FactionIcon", &INI::parseAsciiString, 0, 0x20},
	{"DefaultArmyIconName", &INI::parseAsciiString, 0, 0x24},
	{"BuildPlotIconName", &INI::parseAsciiString, 0, 0x28},
	{"BuildPlotSelectionPortraitName", &INI::parseAsciiString, 0, 0x2C},
	{"GarrisonSelectionPortraitName", &INI::parseAsciiString, 0, 0x30},
	{"GarrisonDisplayNameTag", &INI::parseAsciiString, 0, 0x34},
	{"Music", &Rva00333900ParseAlias, 0, 0x38},
	{"AutoResolveLoop", &Rva00333900ParseAlias, 0, 0x3C},
	{0, 0, 0, 0}
};

class ModuleData
{
};

class Rva002E0906 : public ModuleData
{
public:
	Rva002E0906();
	AsciiString m_name;
private:
	char m_pad[0x40 - 4];
};

class Rva002E18C3Lookup
{
private:
	char m_pad[0xC];
public:
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_vec;
};

// Target constructor 0x00420977 proves the 0x4C allocation and string at +0.
class Rva00420977 : public ModuleData
{
public:
	Rva00420977();
	AsciiString m_name;
private:
	unsigned char m_pad[0x24 - sizeof(AsciiString)];
	unsigned m_zero24, m_zero28, m_zero2C, m_zero30;
	unsigned m_ten34, m_ten38, m_ten3C, m_ten40, m_ten44, m_ten48;
};

extern Rva002E18C3Lookup *TheLivingWorldPlayerTemplateStore;
extern Rva002E18C3Lookup *TheLivingWorldAITemplateStore;

// ?parseLivingWorldPlayerTemplateDefinition@@YAXPAVINI@@@Z
void parseLivingWorldPlayerTemplateDefinition(INI *ini)
{
	if (ini == 0)
	{
		INIException e(3, "LivingWorldPlayerTemplateStore::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	AsciiString token(ini->getNextToken(0));
	if (token.getLength() == 0)
	{
		INIException e(3, "LivingWorldPlayerTemplateStore::No name specified.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	const ModuleData *obj = new Rva002E0906;
	((Rva002E0906 *)obj)->m_name.setCopyInline(token);
	ini->initFromINI((void *)obj, g_00C04820);
	TheLivingWorldPlayerTemplateStore->m_vec.push_back(obj);
}

// ?parseLivingWorldAITemplateDefinition@@YAXPAVINI@@@Z
// Native 0x00420A29..0x00420B10; LivingWorldAITemplate registration at
// 0x00DC8478. Retail retains the PlayerTemplateStore error strings here.
void parseLivingWorldAITemplateDefinition(INI *ini)
{
	if (ini == 0)
	{
		INIException e(3, "LivingWorldPlayerTemplateStore::Invalid data passed in.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	AsciiString token(ini->getNextToken(0));
	if (token.getLength() == 0)
	{
		INIException e(3, "LivingWorldPlayerTemplateStore::No name specified.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	const ModuleData *obj = new Rva00420977;
	((Rva00420977 *)obj)->m_name.setCopyInline(token);
	ini->initFromINI((void *)obj, g_00C3BC20);
	TheLivingWorldAITemplateStore->m_vec.push_back(obj);
}
