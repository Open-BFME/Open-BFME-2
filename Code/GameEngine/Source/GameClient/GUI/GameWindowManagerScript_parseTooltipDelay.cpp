// cl: /DNDEBUG /MD /EHsc
//
// ?parseTooltipDelay@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x0031525D, 38 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseTooltipDelay): single strtok value straight into the instance delay.
// Verbatim: the BFME1 ancestor and the BFME2 in-tree source are identical.
// BFME2 facts (all retail-measured):
// - scanInt is the GameWindowManagerScript file-static at 0x00314E96
//   (declared-not-defined here; resolves via pin, out-of-line call).
// - strtok rides the msvcr71 import at 0xBBA5EC; a single call site emits
//   the direct FF15 form (no esi caching -- the parseSliderData TU proves
//   the same decl caches to esi once called four times).
// - seps " :,\n\r\t" lives at 0xC0C254.
// - m_tooltipDelay sits at instData+0x198 (retail add ecx,0x198); the
//   TU-local replica pads to that offset (TurretAI-shim precedent).

typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class WinInstanceData
{
public:
	char m_pad[0x198];
	Int m_tooltipDelay;
};

// scanInt lives in GameWindowManagerScript.cpp (file-static at 0x00314E96).
// Declared extern (not static: MSVC rejects defined-never statics with
// C2129); the decoration is identical and the pin resolves the address.
Int scanInt(const char *source, Int &val);

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseTooltipDelay@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseTooltipDelay(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	//RadioButtonData *radioData = (RadioButtonData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	// "getvalue"
	c = strtok(buffer, seps);  // value
	scanInt(c, instData->m_tooltipDelay);

	return true;
}

static const void *s_parseTooltipDelayAnchor = (const void *)parseTooltipDelay;
