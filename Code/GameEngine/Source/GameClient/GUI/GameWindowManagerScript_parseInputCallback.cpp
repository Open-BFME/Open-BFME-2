// cl: /Ireference/shims/sweep /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_namekey /Ireference/shims/functionlexicon_bfme2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/functionlexicon /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z,
// retail 0x00316434, 76 bytes. Dedicated TU.
//
// Clones the landed parseSystemCallback TU.
// - name global AsciiString at 0xE0130C, store global at 0xE012F4.
// - verified FunctionLexicon::findFunction at 0x2D225F with index 1.
// - dispatch table at 0x9BE198 pairs 'INPUTCALLBACK' with 0x716434.

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif



#include "PreRTS.h"
#include "Common/FunctionLexicon.h"




extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00DFF024Registry;

// Keep the established global binding and use the scoped BFME2 lexicon
// interface: this public inline accessor calls the verified 0x002D225F
// worker with native table 1. No private-access shim or new pin is needed.
extern Rva00DFF024Registry *TheRva00DFF024Registry;
extern AsciiString g_inputCallbackName;
extern void *g_inputCallback;
// g_inputCallback: matched references place it at VA 0xe012f4 (zero-filled .bss).
void * g_inputCallback;

class WinInstanceData;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseInputCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = strtok(ptr, stringSeps);
	g_inputCallbackName.set(c);

	NameKeyType key = TheNameKeyGenerator->nameToKey(g_inputCallbackName);
	g_inputCallback = reinterpret_cast<void *>(reinterpret_cast<FunctionLexicon *>(TheRva00DFF024Registry)->gameWinInputFunc(key));

	return true;
}

static const void *s_parseInputCallbackAnchor = (const void *)parseInputCallback;
