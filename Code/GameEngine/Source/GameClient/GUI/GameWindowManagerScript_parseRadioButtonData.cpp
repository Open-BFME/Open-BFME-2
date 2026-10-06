// cl: /DNDEBUG /MD /EHsc
//
// ?parseRadioButtonData@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x0031522E, 47 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseRadioButtonData): GROUP value via the file-static scanInt.
// Verbatim: the BFME1 ancestor and the BFME2 in-tree source are identical.
// BFME2 facts (all retail-measured):
// - scanInt is the GameWindowManagerScript file-static at 0x00314E96
//   (declared-not-defined here; resolves via pin, out-of-line call).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; two call
//   sites cache the import to esi like retail).
// - seps " :,\n\r\t" lives at 0xC0C254.
// - RadioButtonData is { screen +0, group +4 }; only group is parsed.

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class WinInstanceData;

struct RadioButtonData
{
	Int screen;
	Int group;
};

// scanInt lives in GameWindowManagerScript.cpp (file-static at 0x00314E96).
// Declared extern (not static: MSVC rejects defined-never statics with
// C2129); the decoration is identical and the pin resolves the address.
Int scanInt(const char *source, Int &val);

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseRadioButtonData@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseRadioButtonData(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	RadioButtonData *radioData = (RadioButtonData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	// "GROUP"
	c = strtok(buffer, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, radioData->group);

	return true;
}

static const void *s_parseRadioButtonDataAnchor = (const void *)parseRadioButtonData;
