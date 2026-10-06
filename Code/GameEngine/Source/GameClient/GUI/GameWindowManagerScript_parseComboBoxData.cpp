// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?parseComboBoxData@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315146, 166 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseComboBoxData): isEditable, maxChars, maxDisplay, asciiOnly,
// lettersAndNumbersOnly. BFME2 packs the two trailing options as bits
// (0x10 = ascii, 0x40 = letters-and-numbers) in an Int at +0xC instead of
// the two plain Bools the ZH/BFME1 header declares.
// BFME2 facts (all retail-measured):
// - scanInt/scanBool are the GameWindowManagerScript file-statics at
//   0x00314E96/0x00314E42 (declared-not-defined here; pins resolve them).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the many
//   call sites cache the import to esi like retail).
// - seps " :,\n\r\t" lives at 0xC0C254.
// - ComboBoxData head is { isEditable +0, maxDisplay +4, maxChars +8 }
//   (sweep-shim GameClient/Gadget.h order; retail reads +8 before +4).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'COMBOBOXDATA'
//   with 0x715146 (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class WinInstanceData;

struct ComboBoxData
{
	Bool isEditable;  // +0
	Int maxDisplay;  // +4
	Int maxChars;  // +8
	// BFME2 packs the trailing options here (retail zeroes the dword,
	// then ORs bit 0x10 for asciiOnly and bit 0x40 for
	// lettersAndNumbersOnly).
	Int asciiFlags;  // +0xC
};

// scanInt/scanBool live in GameWindowManagerScript.cpp (file-statics at
// 0x00314E96/0x00314E42). Declared extern (not static: MSVC rejects
// defined-never statics with C2129); the decorations are identical and the
// pins resolve the addresses.
Int scanInt(const char *source, Int &val);
Int scanBool(const char *source, Bool &val);

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseComboBoxData@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseComboBoxData(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	ComboBoxData *comboData = (ComboBoxData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	Bool flag = false;

	c = strtok(buffer, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, comboData->isEditable);

	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, comboData->maxChars);

	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, comboData->maxDisplay);

	comboData->asciiFlags = 0;

	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, flag);
	if (flag)
		comboData->asciiFlags |= 0x10;

	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, flag);
	if (flag)
		comboData->asciiFlags |= 0x40;

	return true;
}

static const void *s_parseComboBoxDataAnchor = (const void *)parseComboBoxData;
