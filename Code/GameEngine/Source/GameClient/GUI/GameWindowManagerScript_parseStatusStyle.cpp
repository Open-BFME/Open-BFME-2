// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?parseStatus@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00314FDC, 31 bytes.
// ?parseStyle@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00314FFB, 31 bytes.
// Dedicated TU (both verbs share the parseBitString callee and tables).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseStatus/parseStyle): zero the bits, then parseBitString over the
// window flag-name table. Verbatim.
// BFME2 facts (all retail-measured):
// - parseBitString is the free function at 0x00314D4D
//   (declared-not-defined here; resolves via pin, out-of-line call).
// - WindowStatusNames lives at 0x9BE0D8 (ACTIVE, TOGGLE, DRAGABLE,
//   ENABLED, ...); WindowStyleNames at 0x9BE150 (PUSHBUTTON,
//   RADIOBUTTON, ...). Both are TU-local externs (DIR32 auto-patches
//   from retail, no pins).
// - m_style sits at instData+0x0C, m_status at instData+0x10 (retail
//   add eax,0xC / add eax,0x10 plus and-mem-0).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'STATUS' with
//   0x714FDC and 'STYLE' with 0x714FFB (entries are name@+0/fn@+4; the
//   walker at 0x31701C compares names and calls [eax+4]).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

extern "C" __declspec(dllimport) int __cdecl strncmp(const char *, const char *, unsigned int);
extern "C" __declspec(dllimport) char *__cdecl strtok(char *, const char *);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
extern "C" char *strcpy(char *, const char *);

class WinInstanceData
{
public:
	char m_pad[0x0C];
	UnsignedInt m_style;  // +0x0C
	UnsignedInt m_status;  // +0x10
};

// parseBitString is defined below (same TU). Static free function at
// 0x00314D4D; the pin used to resolve it before conversion.
static void parseBitString(const char *inBuffer, UnsignedInt *bits, const char **flagList);

extern const char *WindowStatusNames[];
extern const char *WindowStyleNames[];

// ?parseStatus@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseStatus(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	instData->m_status = 0;
	parseBitString(buffer, &instData->m_status, WindowStatusNames);

	return true;
}

// ?parseStyle@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseStyle(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	instData->m_style = 0;
	parseBitString(buffer, &instData->m_style, WindowStyleNames);

	return true;
}

static const void *s_parseStatusStyleAnchor = (const void *)parseStatus;
static const void *s_parseStatusStyleAnchor2 = (const void *)parseStyle;

// ?parseBitString@@YAXPBDPAIPAPBD@Z
// BFME1 GameWindowManagerScript.cpp donor with the table walk inlined:
// each '+'-separated token is scanned against the flag table with _strcmpi
// and the matching slot sets its bit. Verbatim otherwise.
static void parseBitString(const char *inBuffer, UnsignedInt *bits, const char **flagList)
{
	char buffer[256];
	char *tok;
	int count;

	// do not modify the inBuffer argument
	strcpy(buffer, inBuffer);

	if (strncmp(buffer, "NULL", 4)) {
		for (tok = strtok(buffer, "+"); tok; tok = strtok(NULL, "+")) {
			count = 0;
			const char **name = flagList;
			while (*name != NULL) {
				if (_strcmpi(*name, tok) == 0) {
					*bits |= 1u << count;
					break;
				}
				++count;
				++name;
			}
		}
	}
}
