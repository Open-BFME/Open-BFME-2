// cl: /DNDEBUG /MD
// ?parseCommonStuff@@YAXPAVINI@@PBQBDAAH222@Z, retail 0x00360613, 118 bytes.
// DamageFX parseCommonStuff: BFME1 Code/GameEngine/Source/Common/DamageFX.cpp
// parseCommonStuff shape verbatim (vet pair via scanIndexList or 0/3, damage via
// Default->0/29 else scanIndexList). BFME2 deltas retail-measured: damageLast
// Default is 29 (30 types, 0x1d) not 15, second list is retail array at 0x9BFFF0.
// Evidence: 4 callers 0x360689/702/774/7E6 are DamageFX::parseAmount (scanReal),
// parseMajorFXList/parseMinorFXList (parseFXList) and parseTime (parseDuration);
// callees rowed getNextToken 0x2DF97 scanIndexList 0x2BD39 plus strcmpi IAT.
// Static with 4 callers in this TU: /O1 outlines custom eax/ebx/edi convention.

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, ConstCharPtrArray nameList);
	float scanReal(const char *token);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// Name order from the retail .data array at VA 0x00DBFFF0 (RVA 0x009BFFF0).
static const char damageTypeName00[] = "SWORD_SLASH";
static const char damageTypeName01[] = "WITCH_KING_MORGUL_BLADE";
static const char damageTypeName02[] = "REFLECTED";
static const char damageTypeName03[] = "GOOD_ARROW_PIERCE";
static const char damageTypeName04[] = "EVIL_ARROW_PIERCE";
static const char damageTypeName05[] = "SMALL_ROCK";
static const char damageTypeName06[] = "BIG_ROCK";
static const char damageTypeName07[] = "CLUBBING";
static const char damageTypeName08[] = "FLAME";
static const char damageTypeName09[] = "MAGIC";
static const char damageTypeName10[] = "BALROG_SWORD";
static const char damageTypeName11[] = "BALROG_WHIP";
static const char damageTypeName12[] = "ELECTRIC";
static const char damageTypeName13[] = "GIMLI_LEAP";
static const char damageTypeName14[] = "STRUCTURAL";
static const char damageTypeName15[] = "FLOOD_HORSE";
static const char damageTypeName16[] = "BOLT";
static const char damageTypeName17[] = "BOLT2";
static const char damageTypeName18[] = "MAGIC2";
static const char damageTypeName19[] = "MAGIC3";
static const char damageTypeName20[] = "FIRE1";
static const char damageTypeName21[] = "FIRE2";
static const char damageTypeName22[] = "FIRE3";
static const char damageTypeName23[] = "SPARKS1";
static const char damageTypeName24[] = "SPARKS2";
static const char damageTypeName25[] = "EARTH1";
static const char damageTypeName26[] = "EARTH2";
static const char damageTypeName27[] = "POISON";
static const char damageTypeName28[] = "TORNADO";
static const char damageTypeName29[] = "UNDEFINED";

extern const char * const DamageFXDamageTypeNames[] = {
	damageTypeName00, damageTypeName01, damageTypeName02, damageTypeName03,
	damageTypeName04, damageTypeName05, damageTypeName06, damageTypeName07,
	damageTypeName08, damageTypeName09, damageTypeName10, damageTypeName11,
	damageTypeName12, damageTypeName13, damageTypeName14, damageTypeName15,
	damageTypeName16, damageTypeName17, damageTypeName18, damageTypeName19,
	damageTypeName20, damageTypeName21, damageTypeName22, damageTypeName23,
	damageTypeName24, damageTypeName25, damageTypeName26, damageTypeName27,
	damageTypeName28, damageTypeName29, 0
};

#define DAMAGE_NUM_TYPES 30
#define LEVEL_FIRST 0
#define LEVEL_LAST 3

struct DamageDFX
{
	Real m_amountForMajorFX;
	void *m_majorDamageFXList;
	void *m_minorDamageFXList;
	UnsignedInt m_damageFXThrottleTime;
};

class Object;
class FXList;
class DamageFX
{
public:
	static void parseAmount(INI *ini, void *instance, void *store, const void *userData);
	static void parseMajorFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseMinorFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseTime(INI *ini, void *instance, void *store, const void *userData);
	void *rva003605E3(int damageType, float amount, const Object *unused);
	bool rva003608DF(int damageType, float amount, const Object *a, const Object *b);
	DamageDFX m_dfx[DAMAGE_NUM_TYPES][4];
};
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

static void parseCommonStuff(INI *ini, ConstCharPtrArray names, int &vetFirst, int &vetLast, int &damageFirst, int &damageLast)
{
	if (names)
	{
		vetFirst = ini->scanIndexList(ini->getNextToken(0), names);
		vetLast = vetFirst;
	}
	else
	{
		vetFirst = LEVEL_FIRST;
		vetLast = LEVEL_LAST;
	}

	const char *damageName = ini->getNextToken(0);
	if (_strcmpi(damageName, "Default") == 0)
	{
		damageFirst = 0;
		damageLast = DAMAGE_NUM_TYPES - 1;
	}
	else
	{
		damageFirst = ini->scanIndexList(damageName, DamageFXDamageTypeNames);
		damageLast = damageFirst;
	}
}

void DamageFX::parseAmount(INI *ini, void *instance, void *store, const void *userData)
{
	DamageFX *self = (DamageFX *)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;
	int vetFirst, vetLast, damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);
	Real amt = ini->scanReal(ini->getNextToken(0));
	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_amountForMajorFX = amt;
		}
	}
}

void DamageFX::parseMajorFXList(INI *ini, void *instance, void *store, const void *userData)
{
	DamageFX *self = (DamageFX *)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;
	int vetFirst, vetLast, damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);
	void *fx;
	INI::parseFXList(ini, 0, &fx, 0);
	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_majorDamageFXList = fx;
		}
	}
}

void DamageFX::parseMinorFXList(INI *ini, void *instance, void *store, const void *userData)
{
	DamageFX *self = (DamageFX *)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;
	int vetFirst, vetLast, damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);
	void *fx;
	INI::parseFXList(ini, 0, &fx, 0);
	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_minorDamageFXList = fx;
		}
	}
}

void DamageFX::parseTime(INI *ini, void *instance, void *store, const void *userData)
{
	DamageFX *self = (DamageFX *)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;
	int vetFirst, vetLast, damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);
	UnsignedInt t;
	INI::parseDurationUnsignedInt(ini, 0, &t, 0);
	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_damageFXThrottleTime = t;
		}
	}
}

// ?rva003605E3@DamageFX@@QAEPAXHMPBVObject@@@Z @0x003605E3 48B: DamageFX major/minor selector
// via m_dfx[damageType][0] threshold (64B stride from 30x4x16 layout); null on BfmeZeroRange
// equality; caller 0x003608DF passes (index amount Object) and forwards to doFXObj.
void *DamageFX::rva003605E3(int damageType, float amount, const Object *unused)
{
	if (amount == 0.0f)
		return 0;
	if (amount >= m_dfx[damageType][0].m_amountForMajorFX)
		return m_dfx[damageType][0].m_majorDamageFXList;
	return m_dfx[damageType][0].m_minorDamageFXList;
}

// ?rva003608DF@DamageFX@@QAE_NHMPBVObject@@0@Z @0x003608DF 50B: DamageFX doFX wrapper
// calls rva003605E3 for FXList then FXList::doFXObj; false on null else true; caller 0x004BED62.
bool DamageFX::rva003608DF(int damageType, float amount, const Object *a, const Object *b)
{
	void *fx = rva003605E3(damageType, amount, a);
	if (!fx)
		return false;
	FXList::doFXObj((const FXList *)fx, b, a);
	return true;
}
