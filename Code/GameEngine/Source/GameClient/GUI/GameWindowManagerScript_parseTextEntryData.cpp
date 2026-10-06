// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?parseTextEntryData@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x003152B2, 181 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseTextEntryData): MAXLEN via scanShort then SECRET/NUMERICAL/ALPHA/ASCIIONLY
// via scanBool. BFME2 packs the three trailing options as bits (0x20 = numerical
// 0x40 = alphanumerical 0x10 = ascii) in a dword at +0xC instead of the four
// plain Bools the ZH/BFME1 header declares and keeps SECRET as a direct byte
// at +0x12 with maxTextLen as a word at +0x10.
// BFME2 facts (all retail-measured):
// - scanShort/scanBool are the GameWindowManagerScript file-statics at
//   0x00314E6D/0x00314E42 (declared-not-defined here; pin/row resolve them).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the many
//   call sites cache the import to esi like retail).
// - seps " :,\n\r\t" lives at 0xC0C254.
// - The flags dword is zeroed between the SECRET block and the NUMERICAL
//   block (retail hoists the store above the next strtok pair).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'TEXTENTRYDATA'
//   with 0x7152B2 (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

typedef int Int;
typedef short Short;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class WinInstanceData;

struct EntryData
{
	unsigned char pad[0x0C];  // +0
	Int flags;  // +0x0C (bit 0x20 numerical 0x40 alphanumerical 0x10 ascii)
	Short maxTextLen;  // +0x10
	Bool secretText;  // +0x12
};

// scanShort/scanBool live in GameWindowManagerScript.cpp (file-statics at
// 0x00314E6D/0x00314E42). Declared extern (not static: MSVC rejects
// defined-never statics with C2129); the decorations are identical and the
// pin/row resolve the addresses.
Int scanShort(const char *source, Short &val);
Int scanBool(const char *source, Bool &val);

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseTextEntryData@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseTextEntryData(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	EntryData *entryData = (EntryData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	Bool flag = false;

	c = strtok(buffer, seps);  // label
	c = strtok(NULL, seps);  // value
	scanShort(c, entryData->maxTextLen);

	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, entryData->secretText);

	entryData->flags = 0;

	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, flag);
	if (flag)
		entryData->flags |= 0x20;

	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, flag);
	if (flag)
		entryData->flags |= 0x40;

	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, flag);
	if (flag)
		entryData->flags |= 0x10;

	return true;
}

static const void *s_parseTextEntryDataAnchor = (const void *)parseTextEntryData;
