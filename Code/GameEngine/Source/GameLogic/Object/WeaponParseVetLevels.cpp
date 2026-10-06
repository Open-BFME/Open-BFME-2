// cl: /O1 /Oy- /DNDEBUG /MD /GX- /Oi-
// ?parsePerVetLevelPSys@@YAXPAVINI@@PAX1PBX@Z @0x002C8FC0 (66B): Weapon
// veterancy parse verb split from Weapon.cpp (its INI.h declares only the
// static scanIndexList form). Local INI mirrors INI_parseIndexList.cpp
// (member scanIndexList with explicit null seps, rowed at 0x2BD39;
// getNextToken rowed at 0x2DF97; parseParticleSystemTemplate rowed at
// 0x3395BB). /Oy- forces the ebp frame retail carries. TheVeterancyNames
// is the VA 0xDBA4C0 table Upgrade.cpp reads. Ghidra rows this address at
// 70B but the body ends with leave+ret at 66B; the rest is the next function.
//
// The FXList pair and the all-levels PSys form are the neighbouring Zero Hour
// Weapon.cpp statics, each with its local initialised to NULL (retail stores
// zero before the parse call). WeaponTemplate FieldParse rows: FireFX
// 0x00C00D28 and PreAttackFX 0x00C00D48 -> 0x002C8F98 (40B); VeterancyFireFX
// 0x00C00D68 -> 0x002C8F56 (66B); ProjectileExhaust 0x00C00D58 ->
// 0x002C9002, whose body ends at leave+ret after 40B (Ghidra's 51B also
// takes the unreferenced 0x002C902A thiscall stub that follows).
#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, const char * const *names);
	static void parseParticleSystemTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
};

const char *TheVeterancyNames[] = {
	"REGULAR",
	"VETERAN",
	"ELITE",
	"HEROIC",
	0,
};

typedef int VeterancyLevel;

struct ParticleSystemTemplate;
class FXList;

enum
{
	LEVEL_FIRST = 0,
	LEVEL_LAST = 3
};

typedef int Int;

// ?parseAllVetLevelsFXList@@YAXPAVINI@@PAX1PBX@Z
void parseAllVetLevelsFXList(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	typedef const FXList *ConstFXListPtr;
	ConstFXListPtr *s = (ConstFXListPtr *)store;
	ConstFXListPtr fx = NULL;
	INI::parseFXList(ini, NULL, &fx, NULL);
	for (Int i = LEVEL_FIRST; i <= LEVEL_LAST; ++i)
		s[i] = fx;
}

// ?parsePerVetLevelFXList@@YAXPAVINI@@PAX1PBX@Z
void parsePerVetLevelFXList(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	typedef const FXList *ConstFXListPtr;
	ConstFXListPtr *s = (ConstFXListPtr *)store;
	VeterancyLevel v = (VeterancyLevel)ini->scanIndexList(ini->getNextToken(NULL), TheVeterancyNames);
	ConstFXListPtr fx = NULL;
	INI::parseFXList(ini, NULL, &fx, NULL);
	s[v] = fx;
}

// ?parseAllVetLevelsPSys@@YAXPAVINI@@PAX1PBX@Z
void parseAllVetLevelsPSys(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	typedef const ParticleSystemTemplate *ConstParticleSystemTemplatePtr;
	ConstParticleSystemTemplatePtr *s = (ConstParticleSystemTemplatePtr *)store;
	ConstParticleSystemTemplatePtr pst = NULL;
	INI::parseParticleSystemTemplate(ini, NULL, &pst, NULL);
	for (Int i = LEVEL_FIRST; i <= LEVEL_LAST; ++i)
		s[i] = pst;
}

// ?parsePerVetLevelPSys@@YAXPAVINI@@PAX1PBX@Z
void parsePerVetLevelPSys(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	typedef const ParticleSystemTemplate *ConstParticleSystemTemplatePtr;
	ConstParticleSystemTemplatePtr *s = (ConstParticleSystemTemplatePtr *)store;
	VeterancyLevel v = (VeterancyLevel)ini->scanIndexList(ini->getNextToken(NULL), TheVeterancyNames);
	ConstParticleSystemTemplatePtr pst = NULL;
	INI::parseParticleSystemTemplate(ini, NULL, &pst, NULL);
	s[v] = pst;
}
