// cl: /DNDEBUG /MD /GX-
// Rva003396D3_ParseKillerScience (retail 0x003396D3, 58 bytes). Reads a
// token through the rowed getNextToken at 0x002DF97; when the ScienceStore
// global at 0xDFE0E0 is unloaded it throws a 0xDEAD0001-marked word through
// the pinned _CxxThrowException at 0x00629094 with the info at 0xCFEEE4,
// otherwise the token resolves through the rowed INI::scanScience at
// 0x00338A8D into the store int (ThingTemplateParsePrerequisiteUnit
// precedent for the ScienceType spelling). Serves the KillerScience and
// BonusScience entries of the table at 0x8162A0 (same body). The callback
// name stays address-derived; the owning struct is BFME2-new (no BFME1 donor).

enum ScienceType
{
	SCIENCE_INVALID = 0
};

class ScienceStore;
extern ScienceStore *TheScienceStore;

#include "../../../Include/Common/INI/INI.h"

// Zero Hour's Common/Errors.h; retail's ErrorCode throw info is at 0x00CFEEE4.
enum ErrorCode
{
	ERROR_BASE = 0xdead0001,
	ERROR_BUG = (ERROR_BASE + 0x0000)
};

// ?Rva003396D3_ParseKillerScience@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva003396D3_ParseKillerScience(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(0);
	if (TheScienceStore == 0) {
		throw ERROR_BUG;
	}
	*(int *)store = INI::scanScience(token);
}

// ICF-folded twin of Rva003396D3_ParseKillerScience above (same 58 bytes at
// 0x003396D3): static member functions take no receiver, so the same
// statements under a different name compile to the identical body.
void INI::parseScience(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(0);
	if (TheScienceStore == 0) {
		throw ERROR_BUG;
	}
	*(int *)store = INI::scanScience(token);
}
