// cl: /O1 /Oy- /DNDEBUG /MD /GX- /Oi-
// ?parsePerVetLevelPSys@@YAXPAVINI@@PAX1PBX@Z @0x002C8FC0 (66B): Weapon
// veterancy parse verb split from Weapon.cpp (its INI.h declares only the
// static scanIndexList form). Local INI mirrors INI_parseIndexList.cpp
// (member scanIndexList with explicit null seps, rowed at 0x2BD39;
// getNextToken rowed at 0x2DF97; parseParticleSystemTemplate rowed at
// 0x3395BB). /Oy- forces the ebp frame retail carries. TheVeterancyNames
// is the VA 0xDBA4C0 table Upgrade.cpp reads. Ghidra rows this address at
// 70B but the body ends with leave+ret at 66B; the rest is the next function.
#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, const char * const *names);
	static void parseParticleSystemTemplate(INI *ini, void *instance, void *store, const void *userData);
};

extern const char *TheVeterancyNames[];

typedef int VeterancyLevel;

struct ParticleSystemTemplate;

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
