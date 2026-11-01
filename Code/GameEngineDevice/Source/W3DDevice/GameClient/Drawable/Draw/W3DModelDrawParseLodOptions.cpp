// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /DNDEBUG /MD /O1 /arch:SSE /G7
//
// ?parseLodOptions@W3DModelDrawModuleData@@SAXPAUINI@@PAX11@Z @0x00079305 223B
// The stored callback is adjacent to the "LodOptions" table label; the donor
// parser and retail error string establish the LOW/MEDIUM/HIGH field semantics.

#include "ascii_string.h"
#include "Common/INIException.h"

#include <string.h>

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

#include "../../../../../../GameEngine/Include/Common/INI/INI.h"

// Retail's LOD-options table at RVA 0x007C6B00 (.rdata, five records and the zero sentinel), transcribed from retail's bytes.
extern const FieldParse TheLodOptionsFieldParse[] =
{
	{ "AllowMultipleModels", INI::parseBool, 0, 0x0 },
	{ "MaxRandomTextures", INI::parseInt, 0, 0x4 },
	{ "MaxRandomAnimations", INI::parseInt, 0, 0x8 },
	{ "MaxAnimFrameDelta", INI::parseReal, 0, 0xC },
	{ "RandomStartFramePercent", INI::parseInt, 0, 0x10 },
	{ 0, 0, 0, 0 }
};

class W3DModelDrawModuleData
{
public:
	static void parseLodOptions(INI *ini, void *object, void *store, const void *userData);
};

void W3DModelDrawModuleData::parseLodOptions(INI *ini, void *object, void *, const void *)
{
	AsciiString token = ini->getNextAsciiString();
	((StringBase<char> &)(token)).toLower();
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
