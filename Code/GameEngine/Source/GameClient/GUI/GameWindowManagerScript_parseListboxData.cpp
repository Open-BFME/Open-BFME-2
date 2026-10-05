// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?parseListboxData@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x0031501A, 300 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseListboxData): LENGTH via scanShort, AUTOSCROLL via scanBool, optional
// SCROLLIFATEND via _strcmpi, AUTOPURGE/SCROLLBAR/MULTISELECT via scanBool,
// COLUMNS via scanShort with a NEW Int[] width array, FORCESELECT via scanBool.
// BFME2 facts (all retail-measured):
// - scanShort/scanInt/scanBool are the GameWindowManagerScript file-statics at
//   0x00314E6D/0x00314E96/0x00314E42 (declared-not-defined here;
//   pin/rows resolve them).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the many
//   call sites cache the import to esi like retail).
// - _strcmpi rides the import at 0xBBA518 (dllimport decl; the single site
//   emits a direct FF15 call).
// - "ScrollIfAtEnd" lives at 0xC0C244; seps " :,\n\r\t" at 0xC0C254.
// - ListboxData layout: listLength +0, columns +2, columnWidthPercentage +4,
//   autoScroll +8, autoPurge +9, scrollBar +0xA, multiSelect +0xB,
//   forceSelect +0xC, scrollIfAtEnd +0xD, columnWidth +0x14.
// - operator new[] at 0x2FDE0 is a matched row (no pin needed).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'LISTBOXDATA'
//   with 0x71501A (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

typedef int Int;
typedef short Short;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

class WinInstanceData;

// Array-new rides the game vector-new at 0x2FDE0 (matched row). Without this
// declaration MSVC 7.1 folds trivial-type array-new to scalar new (0x2FDA0).
void *__cdecl operator new[](unsigned int s);

struct ListboxData
{
	Short listLength;  // +0
	Short columns;  // +2
	Int *columnWidthPercentage;  // +4
	Bool autoScroll;  // +8
	Bool autoPurge;  // +9
	Bool scrollBar;  // +0xA
	Bool multiSelect;  // +0xB
	Bool forceSelect;  // +0xC
	Bool scrollIfAtEnd;  // +0xD
	unsigned char pad[0x14 - 0xE];  // +0xE
	Int *columnWidth;  // +0x14
};

// scanShort/scanInt/scanBool live in GameWindowManagerScript.cpp (file-statics
// at 0x00314E6D/0x00314E96/0x00314E42). Declared extern (not static: MSVC
// rejects defined-never statics with C2129); the decorations are identical
// and the pin/rows resolve the addresses.
static Int scanShort(const char *source, Short &val);
Int scanInt(const char *source, Int &val);
Int scanBool(const char *source, Bool &val);

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buffer, const char *format, ...);

// Local static copy of the 41B sscanf wrapper at 0x00314E6D (rowed from
// parseTextEntryData_Thunk.cpp, which keeps it static so it emits no global
// and no other TU can bind to it). Same body as the thunk, so the calls
// above still emit exactly as verified; internal linkage means no COMDAT
// conflict with the row owner's copy.
// ?scanShort@@YAHPBDAAF@Z present-unmatched
static Int scanShort(const char *source, Short &val)
{
	Int temp = 0;
	Int ret = sscanf(source, "%d", &temp);
	val = (Short)temp;
	return ret;
}

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// ?parseListboxData@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseListboxData(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	ListboxData *listData = (ListboxData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	// "LENGTH"
	c = strtok(buffer, seps);  // label
	c = strtok(NULL, seps);  // value
	scanShort(c, listData->listLength);

	// "AUTOSCROLL"
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, listData->autoScroll);

	// "SCROLLIFATEND" (optional)
	c = strtok(NULL, seps);  // label
	if (!_strcmpi(c, "ScrollIfAtEnd"))
	{
		c = strtok(NULL, seps);  // value
		scanBool(c, listData->scrollIfAtEnd);
		c = strtok(NULL, seps);  // label
	}
	else
	{
		listData->scrollIfAtEnd = FALSE;
	}

	// "AUTOPURGE"
	c = strtok(NULL, seps);  // value
	scanBool(c, listData->autoPurge);

	// "SCROLLBAR"
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, listData->scrollBar);

	// "MULTISELECT"
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, listData->multiSelect);

	// "COLUMNS"
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanShort(c, listData->columns);
	if (listData->columns > 1)
	{
		listData->columnWidthPercentage = new Int[listData->columns];
		for (Int i = 0; i < listData->columns; i++)
		{
			c = strtok(NULL, seps);  // label
			c = strtok(NULL, seps);  // value
			scanInt(c, listData->columnWidthPercentage[i]);
		}
	}
	else
		listData->columnWidthPercentage = NULL;
	listData->columnWidth = NULL;

	// "FORCESELECT"
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanBool(c, listData->forceSelect);

	return TRUE;
}

static const void *s_parseListboxDataAnchor = (const void *)parseListboxData;
