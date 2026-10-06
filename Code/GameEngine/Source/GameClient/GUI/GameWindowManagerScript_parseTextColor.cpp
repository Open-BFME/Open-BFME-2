// cl: /Oy- /DNDEBUG /MD /EHsc
//
// ?parseTextColor@@YA_NPADPAVWinInstanceData@@0PAX@Z, retail 0x00315994, 308 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseTextColor): per-state (enabled/disabled/hilite) color plus border
// color, each as four scans packed ARGB. BFME2 deltas (all retail-measured):
// scanInt (not scanUnsignedInt) into Int locals, manual Horner pack (not
// GameMakeColor), states at +0x15C/+0x164/+0x16C.
// BFME2 facts (all retail-measured):
// - scanInt is the GameWindowManagerScript file-static at 0x00314E96
//   (declared-not-defined here; resolves via pin, out-of-line call).
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl; the many
//   call sites cache the import to esi like retail).
// - seps " :,\n\r\t" lives at 0xC0C254.
// - Pack idiom is the landed INI_parseColorInt.cpp recipe: seed
//   (unsigned char)a, then (x<<8)|(unsigned char)next over r/g/b
//   (retail's movzx/mov-ah chain). Channels scan r,g,b,a into the Int
//   locals in source order.
// - TextDrawData is { color +0, borderColor +4 } (8B stride);
//   m_enabledText/m_disabledText/m_hiliteText at +0x15C/+0x164/+0x16C.
// - Identity: the .data dispatch table at 0x9BE198 pairs 'TEXTCOLOR'
//   with 0x715994 (entries are name@+0/fn@+4; the walker at 0x31701C
//   compares names and calls [eax+4]).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

typedef UnsignedInt Color;

class WinInstanceData;

struct TextDrawData
{
	Color color;
	Color borderColor;
};

struct WinInstanceDataLayout
{
	char m_pad[0x15C];
	TextDrawData m_enabledText;
	TextDrawData m_disabledText;
	TextDrawData m_hiliteText;
};

// scanInt lives in GameWindowManagerScript.cpp (file-static at 0x00314E96).
// Declared extern (not static: MSVC rejects defined-never statics with
// C2129); the decoration is identical and the pin resolves the address.
Int scanInt(const char *source, Int &val);

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// ?parseTextColor@@YA_NPADPAVWinInstanceData@@0PAX@Z
static Bool parseTextColor(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c;
	char *seps = " :,\n\r\t";
	Int r, g, b, a;
	Int i, states = 3;
	TextDrawData *textData;
	Bool first = TRUE;
	WinInstanceDataLayout *layout = (WinInstanceDataLayout *)instData;

	for (i = 0; i < states; i++)
	{
		if (i == 0)
			textData = &layout->m_enabledText;
		else if (i == 1)
			textData = &layout->m_disabledText;
		else if (i == 2)
			textData = &layout->m_hiliteText;
		else
		{
			return FALSE;
		}

		// color
		if (first == TRUE)
			c = strtok(buffer, seps);  // label
		else
			c = strtok(NULL, seps);  // label
		first = FALSE;
		c = strtok(NULL, seps);  // value
		scanInt(c, r);
		c = strtok(NULL, seps);  // value
		scanInt(c, g);
		c = strtok(NULL, seps);  // value
		scanInt(c, b);
		c = strtok(NULL, seps);  // value
		scanInt(c, a);
		UnsignedInt packed = (unsigned char)a;
		packed = (packed << 8) | (unsigned char)r;
		packed = (packed << 8) | (unsigned char)g;
		packed = (packed << 8) | (unsigned char)b;
		textData->color = packed;

		// border color
		c = strtok(NULL, seps);  // label
		c = strtok(NULL, seps);  // value
		scanInt(c, r);
		c = strtok(NULL, seps);  // value
		scanInt(c, g);
		c = strtok(NULL, seps);  // value
		scanInt(c, b);
		c = strtok(NULL, seps);  // value
		scanInt(c, a);
		packed = (unsigned char)a;
		packed = (packed << 8) | (unsigned char)r;
		packed = (packed << 8) | (unsigned char)g;
		packed = (packed << 8) | (unsigned char)b;
		textData->borderColor = packed;
	}

	return TRUE;
}

static const void *s_parseTextColorAnchor = (const void *)parseTextColor;
