// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /Oi-
//
// ?parseParticleSystemDefinition@INI@@SAXPAV1@@Z, target 0x001FD0B4, 220B.
// Target identity: the FXParticleSystem block-parse node at VA 0x00DB938C
// names this parser at 0x001FD0B4. Retail calls getNextToken, the manager's
// findTemplate, newTemplate on a miss, the ParticleSystemTemplate constructor
// on a hit, then initFromINI. This sequence identifies the GeneralsMD
// INI::parseParticleSystemDefinition donor in INIParticleSys.cpp.
//
// Donor provenance: reference/open-bfme-1 INIParticleSys.cpp at revision
// 6583b3c1ff21db4a561285717028fdafc780b7db; its flags and headers are migrated
// to this BFME2 TU. Retail-specific evidence: the two-entry System table at
// RVA 0x007E1520 is copied to manager state +0x94 after helper 0x001FD06E
// initializes state +0x04; the one-time flag is at state +0xB4. Retail also
// writes an otherwise-unidentified manager byte at +0x84 when INI state is 2.

#include <new>
#include <string.h>
#include "ascii_string.h"

class INI;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const AsciiString &name);
	virtual ~ParticleSystemTemplate();
	static void parse(INI *ini, void *instance, void *store, const void *userData);
};
}

class ParticleSystemTemplate
{
public:
	virtual ~ParticleSystemTemplate();
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	ParticleSystemTemplate *newTemplate(const AsciiString &name);
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *instance, const FieldParse *table);
	static void parseParticleSystemDefinition(INI *ini);
	unsigned char m_unmodelled_000[8];
	int m_parseMode; // +0x08; the compared value 2 is target evidence.
};

extern ParticleSystemManager *TheParticleSystemManager;
extern unsigned int g_Va00DFE014; // target global at VA 0x00DFE014.
extern void Rva001FD06EInit(void *state);

static const FieldParse s_particleSystemFieldParse[] =
{
	{ "System", FXParticleSystem::ParticleSystemTemplate::parse, 0, 0 },
	{ 0, 0, 0, 0 }
};

void INI::parseParticleSystemDefinition(INI *ini)
{
	AsciiString name;
	name.set(ini->getNextToken());

	ParticleSystemTemplate *sysTemplate = TheParticleSystemManager->findTemplate(name);
	if (sysTemplate == 0) {
		sysTemplate = TheParticleSystemManager->newTemplate(name);
	} else {
		sysTemplate->~ParticleSystemTemplate();
		new (reinterpret_cast<FXParticleSystem::ParticleSystemTemplate *>(sysTemplate))
			FXParticleSystem::ParticleSystemTemplate(name);
	}

	unsigned char *parseState = reinterpret_cast<unsigned char *>(&g_Va00DFE014);
	if (parseState[0xB4] == 0) {
		Rva001FD06EInit(parseState + 4);
		memcpy(parseState + 0x94, s_particleSystemFieldParse,
			sizeof(s_particleSystemFieldParse));
		parseState[0xB4] = 1;
	}

	ini->initFromINI(sysTemplate,
		reinterpret_cast<const FieldParse *>(parseState + 4));
	if (ini->m_parseMode == 2) {
		ParticleSystemManager *manager = TheParticleSystemManager;
		if (manager != 0)
			reinterpret_cast<unsigned char *>(manager)[0x84] = 1;
	}
}
