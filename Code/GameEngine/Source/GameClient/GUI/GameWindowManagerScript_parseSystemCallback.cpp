// cl: /Ireference/shims/sweep /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_namekey /Ireference/shims/functionlexicon_bfme2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/functionlexicon /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ?parseSystemCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x003163E8, 76 bytes.
// Dedicated TU.
//
// Battle for Middle-earth has no twin for this body (BFME2-new global
// callback registry); the shape clones the landed parseName TU (quote-scan,
// strtok, AsciiString set, nameToKey) with a registry lookup tail.
// BFME2 facts (all retail-measured):
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the
//   single site emits the direct indirect call like retail).
// - stringSeps "\"" lives at 0xC0C2B4.
// - StringBase::set is the matched narrow row at 0x55F5 (public QAEXPBD;
//   AsciiString inline set forwards to it).
// - The callback name is the global AsciiString at 0xE01308 (extern object;
//   address patches from retail; shared with parseWinClass).
// - nameToKey(const AsciiString&) at 0x9FA65 is a matched row (declared,
//   never defined here); TheNameKeyGenerator is the extern pointer at
//   0xDF36A4 (DIR32 from retail).
// - The registry lookup at 0x2D225F is thiscall (key, index) over 12 slots
//   at manager+0x0C (null key returns null; index -1 scans all slots via
//   helper 0x2D2235; else slots[index]). The scoped FunctionLexicon
//   interface now names that verified worker and its public table accessors.
// - The system slot is index 0; the resolved pointer stores to the global
//   at 0xE012F0 (extern; address patches from retail).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'SYSTEMCALLBACK'
//   with 0x7163E8 (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif



#include "PreRTS.h"
#include "Common/FunctionLexicon.h"




extern NameKeyGenerator *TheNameKeyGenerator;

// Preserve the existing global pointer binding; the call uses FunctionLexicon.
class Rva00DFF024Registry;

// Keep the established global binding and use the scoped BFME2 lexicon
// interface: this public inline accessor calls the verified 0x002D225F
// worker with native table 0. No private-access shim or new pin is needed.
extern Rva00DFF024Registry *TheRva00DFF024Registry;
extern AsciiString g_systemCallbackName;
extern void *g_systemCallback;
// g_systemCallback: matched references place it at VA 0xe012f0 (zero-filled .bss).
void * g_systemCallback;

class WinInstanceData;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseSystemCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseSystemCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
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
	g_systemCallback = reinterpret_cast<void *>(reinterpret_cast<FunctionLexicon *>(TheRva00DFF024Registry)->gameWinSystemFunc(key));

	return true;
}

static const void *s_parseSystemCallbackAnchor = (const void *)parseSystemCallback;
