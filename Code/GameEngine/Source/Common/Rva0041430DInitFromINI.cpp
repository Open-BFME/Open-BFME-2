// cl: /DNDEBUG /MD
// 0x0041430D, 18B: forwards the caller's object and INI pointer to the
// rowed INI initializer with the field table referenced by retail.

struct FieldParse;

#include "../../Include/Common/INI/INI.h"

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
void Rva001DEE74Parse(INI *ini, void *instance, void *store, const void *userData);

class Rva0041430D
{
public:
	void rva0041430D(INI *ini);
};

// Retail's own six-record table, transcribed from .rdata at RVA 0x00839FF8 (VA
// 0x00C39FF8, file offset 0x008393F8): EvaEvent through the rowed free
// Rva001DEE74Parse at +8, CountOnlyKillsByLocalPlayer and
// CountOnlyKillsAgainstLocalPlayer through INI::parseBool at +0x18/+0x19,
// MinimumCountForAnnouncement through INI::parseUnsignedInt at +0xC,
// MaximumTimeForAnnouncementMS through INI::parseDurationUnsignedInt at +0x10, and
// ObjectFilter through the rowed free iniParseObjectFilter at +0x14, then the
// zero terminator. `extern` on the definition keeps the table external.
extern const FieldParse g_00C39FF8[];
const FieldParse g_00C39FF8[] =
{
	{ "EvaEvent", &Rva001DEE74Parse, 0, 8 },
	{ "CountOnlyKillsByLocalPlayer", &INI::parseBool, 0, 24 },
	{ "CountOnlyKillsAgainstLocalPlayer", &INI::parseBool, 0, 25 },
	{ "MinimumCountForAnnouncement", &INI::parseUnsignedInt, 0, 12 },
	{ "MaximumTimeForAnnouncementMS", &INI::parseDurationUnsignedInt, 0, 16 },
	{ "ObjectFilter", &iniParseObjectFilter, 0, 20 },
	{ 0, 0, 0, 0 }
};

void Rva0041430D::rva0041430D(INI *ini)
{
	ini->initFromINI(this, g_00C39FF8);
}
