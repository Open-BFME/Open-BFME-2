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
// RVA 0x007E1520 is copied to +0x90 of the parse table at VA 0x00DFE018 after
// helper 0x001FD06E initializes its start; the one-time flag is at +0xB0. Retail also
// writes an otherwise-unidentified manager byte at +0x84 when INI state is 2.

#include <new>
#include <string.h>
#include "ascii_string.h"

class INI;

#include "../../../Include/Common/INI/FieldParse.h"

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

#include "../../../Include/GameClient/ParticleSys.h"

#include "../../../Include/Common/INI/INI.h"

extern ParticleSystemManager *TheParticleSystemManager;
// The definition parse table this parser builds once, at retail VA 0x00DFE018
// (0xB4 bytes up to the flag word): the 0x90 bytes helper 0x001FD06E fills,
// the two-entry System table copied in at +0x90, then the one-time flag at
// +0xB0 (VA 0x00DFE0C8). It is this TU's own datum, not part of the
// Make001FCBD7 static guard word at VA 0x00DFE014 just before it. Field
// spellings and the original name are unknown.
struct ParticleSystemDefinitionParse
{
	unsigned char m_baseFields[0x90];	// +0x00, Rva001FD06EInit
	FieldParse m_systemFields[2];		// +0x90
	bool m_built;				// +0xB0
};
static ParticleSystemDefinitionParse s_definitionParse;
extern void Rva001FD06EInit(void *state);

static const FieldParse s_particleSystemFieldParse[] =
{
	{ "System", FXParticleSystem::ParticleSystemTemplate::parse, 0, 0 },
	{ 0, 0, 0, 0 }
};

// Native 1FD093..1FD0B4 (33B), just before parseParticleSystemDefinition: the
// field-parse table build that function inlines (Rva001FD06EInit, then the
// "System" entry and terminator copied in at +0x90), as an out-of-line
// file-static with the table in EAX. No call to it survives in the image; the
// anchor below only forces cl to emit it in that convention. Identity
// unproven; address-derived names.
static __declspec(noinline) void Rva001FD093(unsigned char *table)
{
	Rva001FD06EInit(table);
	memcpy(table + 0x90, s_particleSystemFieldParse, sizeof(s_particleSystemFieldParse));
}

// ?Rva001FD093Anchor absent-from-retail
void Rva001FD093Anchor(unsigned char *table)
{
	Rva001FD093(table);
}

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

	if (!s_definitionParse.m_built) {
		Rva001FD06EInit(&s_definitionParse);
		memcpy(s_definitionParse.m_systemFields, s_particleSystemFieldParse,
			sizeof(s_particleSystemFieldParse));
		s_definitionParse.m_built = true;
	}

	ini->initFromINI(sysTemplate,
		reinterpret_cast<const FieldParse *>(&s_definitionParse));
	if (ini->m_loadType == 2) {
		ParticleSystemManager *manager = TheParticleSystemManager;
		if (manager != 0)
			reinterpret_cast<unsigned char *>(manager)[0x84] = 1;
	}
}
