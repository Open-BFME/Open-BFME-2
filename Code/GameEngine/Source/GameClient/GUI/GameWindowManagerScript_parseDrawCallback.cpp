// cl: /Ireference/shims/sweep /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_namekey /Ireference/shims/functionlexicon_bfme2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/functionlexicon /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ?parseDrawCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z,
// retail 0x003164CC, 76 bytes. Dedicated TU.
//
// Clones the landed parseSystemCallback TU.
// - name global AsciiString at 0xE01314, store global at 0xE012F8.
// - verified FunctionLexicon::gameWinDrawFunc at 0x2D2341 tries slot 3 then
//   slot 4 for index -1); sole caller is this verb.
// - dispatch table at 0x9BE198 pairs 'DRAWCALLBACK' with 0x7164CC.

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
// TheRva00DFF024Registry: matched references place it at VA 0xdff024 (zero-filled .bss).
Rva00DFF024Registry * TheRva00DFF024Registry;
extern AsciiString g_drawCallbackName;
extern void *g_drawCallback;
// g_drawCallback: matched references place it at VA 0xe012f8 (zero-filled .bss).
void * g_drawCallback;

class WinInstanceData;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseDrawCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseDrawCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = strtok(ptr, stringSeps);
	g_drawCallbackName.set(c);

	NameKeyType key = TheNameKeyGenerator->nameToKey(g_drawCallbackName);
	g_drawCallback = reinterpret_cast<void *>(reinterpret_cast<FunctionLexicon *>(TheRva00DFF024Registry)->gameWinDrawFunc(key));

	return true;
}

static const void *s_parseDrawCallbackAnchor = (const void *)parseDrawCallback;
