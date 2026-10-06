// cl: /DNDEBUG /MD /EHsc
//
// ?parseStaticTextData@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315283, 47 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseStaticTextData): CENTERED value via the file-static scanBool.
// Verbatim BFME1 shape; the BFME2 in-tree copy carries extra
// centeredVertically/margin stores that retail does NOT have.
// BFME2 facts (all retail-measured):
// - scanBool is the GameWindowManagerScript file-static at 0x00314E42
//   (declared-not-defined here; resolves via pin, out-of-line call).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; two call
//   sites cache the import to esi like retail).
// - seps " :,\n\r\t" lives at 0xC0C254.
// - TextData is { text +0, centered +4 } (ZH Gadget.h); only centered
//   is parsed (retail add ecx,4).
// - Identity: the .data dispatch table at 0x9BE198 pairs
//   'STATICTEXTDATA' with 0x715283 (entries are name@+0/fn@+4; the walker
//   at 0x31701C compares names and calls [eax+4]).

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class WinInstanceData;

struct TextData
{
	void *text;
	Bool centered;
};

// scanBool lives in GameWindowManagerScript.cpp (file-static at 0x00314E42).
// Declared extern (not static: MSVC rejects defined-never statics with
// C2129); the decoration is identical and the pin resolves the address.
Int scanBool(const char *source, Bool &val);

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseStaticTextData@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseStaticTextData(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	TextData *textData = (TextData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	// "CENTERED"
	c = strtok(buffer, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, textData->centered);

	return true;
}

static const void *s_parseStaticTextDataAnchor = (const void *)parseStaticTextData;
