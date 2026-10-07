// cl: /Ireference/shims/sweep /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_namekey /Ireference/shims/functionlexicon_bfme2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/functionlexicon /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ?parseWinClass@@YA_NPADPAVWinInstanceData@@0PAX@Z,
// retail 0x0031639C, 76 bytes. Dedicated TU.
//
// Clones the landed parseSystemCallback TU (quote-scan, strtok,
// AsciiString set, nameToKey, registry lookup tail).
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC.
// - stringSeps "\"" lives at 0xC0C2B4.
// - StringBase::set is the matched narrow row at 0x55F5.
// - The callback name shares the system global AsciiString at 0xE01308.
// - nameToKey(const AsciiString&) at 0x9FA65 is matched; TheNameKeyGenerator
//   at 0xDF36A4.
// - The verified lexicon wrapper at 0x2D2371 tries slot 5 then
//   slot 6 for index -1); sole caller is this verb.
// - The winclass slot stores to the global at 0xE012EC.
// - Identity: the .data dispatch table at 0x9BE198 pairs 'WINCLASS'
//   with 0x71639C.

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif



#include "PreRTS.h"
#include "Common/FunctionLexicon.h"




extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00DFF024Registry;

extern Rva00DFF024Registry *TheRva00DFF024Registry;
extern AsciiString g_systemCallbackName;
extern void *g_winClassCallback;
// g_winClassCallback: matched references place it at VA 0xe012ec (zero-filled .bss).
void * g_winClassCallback;

class WinInstanceData;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseWinClass@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseWinClass(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	// scan to the first " mark
	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;  // skip the first "
	c = strtok(ptr, stringSeps);  // name value
	g_systemCallbackName.set(c);

	NameKeyType key = TheNameKeyGenerator->nameToKey(g_systemCallbackName);
	g_winClassCallback = reinterpret_cast<FunctionLexicon *>(TheRva00DFF024Registry)->rva002D2371(key);

	return true;
}

static const void *s_parseWinClassAnchor = (const void *)parseWinClass;
