// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva001DCFC9@Eva@@QAEXPAVINI@@PAX@Z @0x001DCFC9 28B evidence: callers 0x001DEB43 0x001DF688; FieldParse table VA 0x00BDC078; callee initFromINI 0x0002DE78 rowed
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

void Rva001DEA65Parse(INI *, void *, void *, const void *);
class Rva004255F0 { public: static void parseRecordIntoMap(INI *, void *, void *, const void *); };
// The retail table at 0x007DC078: 9 entries and the null terminator; every parser is rowed.
extern const FieldParse g_00BDC078[10] = {
	{ "Priority", (FieldParseProc)&INI::parseUnsignedInt, 0, 0x10 },
	{ "TimeBetweenEventsMS", (FieldParseProc)&INI::parseUnsignedInt, 0, 0x0 },
	{ "ExpirationTimeMS", (FieldParseProc)&INI::parseUnsignedInt, 0, 0x4 },
	{ "QuietTimeMS", (FieldParseProc)&INI::parseUnsignedInt, 0, 0x8 },
	{ "MillisecondsToWaitBeforePlaying", (FieldParseProc)&INI::parseDurationUnsignedInt, 0, 0xC },
	{ "AlwaysPlayFromHomeBase", (FieldParseProc)&INI::parseBool, 0, 0x2C },
	{ "SideSound", (FieldParseProc)&Rva004255F0::parseRecordIntoMap, 0, 0x14 },
	{ "OtherEvaEventsToBlock", &Rva001DEA65Parse, 0, 0x20 },
	{ "CountAsJumpToLocation", (FieldParseProc)&INI::parseBool, 0, 0x2D },
	{ 0, 0, 0, 0 }
};

class Eva { public: void rva001DCFC9(INI *ini, void *obj); };

void Eva::rva001DCFC9(INI *ini, void *obj)
{
	ini->initFromINI(obj, g_00BDC078);
	((char *)obj)[0x2e] = 0;
}
