// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?Rva002E2386Parse@@YAXPAVINI@@@Z @0x002E2386 231B. LivingWorldPlayerTemplate block parse.
// Evidence: BlockParse LivingWorldPlayerTemplate 0x00DBD0A8 parse 0x002E2386; REF slot 0x009BD0B0 neighbours LivingWorldPlayerTemplate NONE HOLD; error literals LivingWorldPlayerTemplateStore Invalid data passed in 0x00804AF0 and No name specified 0x00804ABC via INIException 0x0002F681 plus TI1 0x008FE2FC; getNextToken 0x0002DF97 plus StringBase ctor 0x00037BA0 plus set 0x000366F0 plus releaseBuffer 0x00036410; new 0x40 plus ctor 0x002E0906; FieldParse g_00C04820 via initFromINI 0x0002DE78; store Va00DFF0B0Lookup plus vector push_back 0x004DFCB0.
#include <vector>
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

// Retail 0x00C3BC20: seventeen integer fields followed by a zero terminator.
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

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

struct _s__ThrowInfo;

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

extern const FieldParse g_00C04820;

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

extern Rva002E18C3Lookup *Va00DFF0B0Lookup;
extern Rva002E18C3Lookup *Va00E03140Lookup;

// ?Rva002E2386Parse@@YAXPAVINI@@@Z
void Rva002E2386Parse(INI *ini)
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
	ini->initFromINI((void *)obj, &g_00C04820);
	Va00DFF0B0Lookup->m_vec.push_back(obj);
}

// ?Rva00420A29Parse@@YAXPAVINI@@@Z
// Native 0x00420A29..0x00420B10; LivingWorldAITemplate registration at
// 0x00DC8478. Retail retains the PlayerTemplateStore error strings here.
void Rva00420A29Parse(INI *ini)
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
	Va00E03140Lookup->m_vec.push_back(obj);
}
