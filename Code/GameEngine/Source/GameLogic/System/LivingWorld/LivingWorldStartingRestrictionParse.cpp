// cl: /O1 /G6 /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ?ParseINI@StartingRestriction@@SAXPAVINI@@PAX@Z, retail 0x0059E9BD
// (132 bytes, cdecl RET, EH). Its own INIException text names it
// StartingRestriction::ParseINI (WorldBuilder 0x014D9450 carries the same
// string). The same shape as the rowed LivingWorldScenario::Scenario::
// ParseINI 0x004FD94E: both arguments are required, a fresh 0x20-byte
// restriction (constructor 0x0059E920, pinned) is filled from the FieldParse
// table at VA 0x00C71178, finished by the rowed 0x0059E848 and handed to the
// owner's list through the rowed 0x004FD4C1. The owner type is unknown.
class INI;
struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};
typedef void (*FieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../../../Include/Common/INI/INI.h"
#include "../../../../../../reference/shims/iniexception/Common/INIException.h"

class Rva0059E920 { public: Rva0059E920(); private: char unknown00[0x20]; };
class Rva0059E848 { public: void rva0059E848(); };
class ModuleData;
class Rva004FD4C1 { public: void rva004FD4C1(const ModuleData *data); };
void parseAsciiStringSetForPositionInfo(void *, void *, void *);
void Rva004FCB23Parse(INI *ini, void *instance, void *store, const void *userData);

// Retail's StartingRestriction field table at VA 0x00C71178 (.rdata, 64 bytes:
// three records and the zero sentinel), transcribed from retail's own bytes.
extern const FieldParse StartingRestrictionFieldParse[] =
{
	{ "Regions",  &INI::parseAsciiStringVector,         0, 0x08 },
	{ "Factions", (FieldParseProc)&parseAsciiStringSetForPositionInfo,    0, 0x04 },
	{ "Teams",    &Rva004FCB23Parse,                    0, 0x14 },
	{ 0, 0, 0, 0 }
};

class StartingRestriction
{
public:
	static void ParseINI(INI *ini, void *owner);
};

void StartingRestriction::ParseINI(INI *ini, void *owner)
{
    if (!ini || !owner)
        throw INIException(3, "Invalid data in StartingRestriction::ParseINI");
    Rva0059E920 *restriction = new Rva0059E920;
    ini->initFromINI(restriction, StartingRestrictionFieldParse);
    ((Rva0059E848 *)restriction)->rva0059E848();
    ((Rva004FD4C1 *)owner)->rva004FD4C1((const ModuleData *)restriction);
}
