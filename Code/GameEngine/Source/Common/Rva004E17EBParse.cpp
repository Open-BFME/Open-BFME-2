// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /GX
// ?Rva004E17EBParse@@YAXPAVINI@@PAX1PBX@Z @0x004E17EB 129B
// ParseSpawnBuilding proc: throws INIException 3 on null ini or instance with retail literal then builds
// Rva004E179A record inline then INI::initFromINI with table g_00C61BE0 then append 0x0056653F.
// Evidence: table slot 0x0086CD94 neighbour SpawnBuilding plus string ParseSpawnBuilding plus vtable
// 0x00C61B78 plus dtor 0x004E179A plus DoXfer pattern.

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

extern "C" {
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00861BE0: 4 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00C61BE0[5] = {
	{ "Player", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "Building", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "Region", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "InstantCreate", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ 0, 0, 0, 0 }
};

#include "Rva004E179A.h"

class Rva0052BE33
{
	char m_pad[0x10];
};

class Rva0056653FOwner
{
public:
	void append(const Rva0052BE33 &record);
};

// ?Rva004E17EBParse@@YAXPAVINI@@PAX1PBX@Z
void Rva004E17EBParse(INI *ini, void *instance, void *, const void *)
{
	if (ini && instance)
	{
		Rva004E179A record;
		ini->initFromINI(&record, g_00C61BE0);
		((Rva0056653FOwner *)instance)->append(*(const Rva0052BE33 *)&record);
	}
	else
	{
		throw INIException(3, "ParseSpawnBuilding::Invalid data passed in.");
	}
}

// Native C6CD50 FieldParse registration uses the four-argument callback ABI.
// Preserve the witnessed body and existing address binding; both trailing
// parameters are unused. No function-pointer cast or alternate callee pin.
