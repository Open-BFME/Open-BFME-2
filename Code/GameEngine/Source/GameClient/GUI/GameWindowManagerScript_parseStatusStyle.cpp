// cl: /DNDEBUG /MD /EHsc
//
// ?parseStatus@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00314FDC, 31 bytes.
// ?parseStyle@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00314FFB, 31 bytes.
// Dedicated TU (both verbs share the parseBitString callee and tables).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseStatus/parseStyle): zero the bits, then parseBitString over the
// window flag-name table. Verbatim.
// BFME2 facts (all retail-measured):
// - parseBitString is the free function at 0x00314D4D, defined in this TU.
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
extern "C" char *_mbscpy(char *, const char *);

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

// ?parseBitFlag@@YA_NPBDPAIPAPBD@Z
// Donor: clean BFME1 GameWindowManagerScript.cpp, revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76. Compiling the donor under
// BFME2 /O1 /G7 places this emitted helper uniquely at RVA 0x00314D16.
// Target evidence: boundary 0x00314D16-0x00314D4D and the rowed 155-byte
// caller prove case-insensitive table matching and a per-index bit OR.
// The source name and parameter labels follow the donor. Retail uses a
// compiler-private ABI: table in EAX, output word in EDI, string on stack.
// Keep the helper with its real caller: MSVC emits this 55-byte body while
// inlining it into the byte-exact caller and retaining both status/style bodies.
static Bool parseBitFlag( const char *flagString, UnsignedInt *bits, 
													const char **flagList )
{
	const char **c;
	int i;

	for( i = 0, c = flagList; *c; i++, c++ )
	{

		if( !_strcmpi( *c, flagString ) )
		{
			*bits |= (1 << i);
			return true;
		}

	}

	return false;

}

// ?parseBitString@@YAXPBDPAIPAPBD@Z
// The original BFME1 helper call now appears directly; it still inlines to
// the same 155 retail bytes under this TU's existing /O1 settings.
static void parseBitString(const char *inBuffer, UnsignedInt *bits, const char **flagList)
{
	char buffer[256];
	char *tok;
	int count;

	// do not modify the inBuffer argument
	_mbscpy(buffer, inBuffer);

	if (strncmp(buffer, "NULL", 4)) {
		for (tok = strtok(buffer, "+"); tok; tok = strtok(NULL, "+")) {
			parseBitFlag(tok, bits, flagList);
		}
	}
}

