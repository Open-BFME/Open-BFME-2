// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /DNDEBUG /MD /O1 /arch:SSE /G7
//
// ?parseLodOptions@W3DModelDrawModuleData@@SAXPAUINI@@PAX11@Z @0x00079305 223B
// The stored callback is adjacent to the "LodOptions" table label; the donor
// parser and retail error string establish the LOW/MEDIUM/HIGH field semantics.

#include "ascii_string.h"
#include "Common/INIException.h"

extern "C" int __cdecl strcmp(const char *, const char *);

struct FieldParse;

class INI
{
public:
	AsciiString getNextAsciiString();
	void initFromINI(void *store, const FieldParse *fields);
};

extern const FieldParse TheLodOptionsFieldParse[];

class W3DModelDrawModuleData
{
public:
	static void parseLodOptions(INI *ini, void *object, void *store, const void *userData);
};

void W3DModelDrawModuleData::parseLodOptions(INI *ini, void *object, void *, const void *)
{
	AsciiString token = ini->getNextAsciiString();
	token.toLower();
	int idx;
	if (strcmp(token.str(), "low") == 0)
		idx = 0;
	else if (strcmp(token.str(), "medium") == 0)
		idx = 1;
	else if (strcmp(token.str(), "high") == 0)
		idx = 2;
	else
	{
		throw INIException(1, "Expected LOW, MEDIUM, or HIGH");
	}
	ini->initFromINI((char *)object + 0x188 + idx * 20, TheLodOptionsFieldParse);
}
