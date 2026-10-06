// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?parseTabControlData@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315367, 222 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseTabControlData): TABORIENTATION/EDGE/WIDTH/HEIGHT/COUNT, PANEBORDER,
// then PANEDISABLED count plus per-pane scanBool loop. BFME2 deltas are
// layout-only (subPanes/subPaneDisabled/paneBorder at +0x14/+0x34/+0x3C).
// BFME2 facts (all retail-measured):
// - scanInt/scanBool are the GameWindowManagerScript file-statics at
//   0x00314E96/0x00314E42 (declared-not-defined here; pins resolve them).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the many
//   call sites cache the import to esi like retail).
// - seps " :,\n\r\t" lives at 0xC0C254.
// - TabControlData layout is the sweep-shim GameClient/Gadget.h shape
//   verbatim (5 ints +0..+0x10, subPanes[8] +0x14, subPaneDisabled[8]
//   +0x34, paneBorder +0x3C).
// - Identity: the .data dispatch table at 0x9BE198 pairs 'TABCONTROLDATA'
//   with 0x715367 (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class WinInstanceData;
class GameWindow;

enum
{
	NUM_TAB_PANES = 8
};

struct TabControlData
{
	Int tabOrientation;
	Int tabEdge;
	Int tabWidth;
	Int tabHeight;
	Int tabCount;
	GameWindow *subPanes[NUM_TAB_PANES];
	Bool subPaneDisabled[NUM_TAB_PANES];
	Int paneBorder;
};

// scanInt/scanBool live in GameWindowManagerScript.cpp (file-statics at
// 0x00314E96/0x00314E42). Declared extern (not static: MSVC rejects
// defined-never statics with C2129); the decorations are identical and the
// pins resolve the addresses.
Int scanInt(const char *source, Int &val);
Int scanBool(const char *source, Bool &val);

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseTabControlData@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseTabControlData(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	TabControlData *tabControlData = (TabControlData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	//TABORIENTATION
	c = strtok(buffer, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, tabControlData->tabOrientation);

	//TABEDGE
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, tabControlData->tabEdge);

	//TABWIDTH
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, tabControlData->tabWidth);

	//TABHEIGHT
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, tabControlData->tabHeight);

	//TABCOUNT
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, tabControlData->tabCount);

	//PANEBORDER
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, tabControlData->paneBorder);

	//PANEDISABLED
	Int entryCount = 0;
	c = strtok(NULL, seps);  // label
	c = strtok(NULL, seps);  // value
	scanInt(c, entryCount);

	for (Int paneIndex = 0; paneIndex < entryCount; paneIndex++)
	{
		c = strtok(NULL, seps);  // value
		scanBool(c, tabControlData->subPaneDisabled[paneIndex]);
	}

	return true;
}

static const void *s_parseTabControlDataAnchor = (const void *)parseTabControlData;
