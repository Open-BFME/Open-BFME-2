// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/sweep /MD /EHsc /DNDEBUG
// ?drawTooltip@Mouse@@QAEXXZ @0x001EF06F 546B
// BFME2's per-frame Apt tooltip updater (sits in the Mouse cluster between
// rowed 0x001EEC4B and 0x001EF291; sole caller of rowed MoveToolTip 0x003807F3,
// third caller of rowed HideToolTip 0x003807B7). It is NOT ZH's drawTooltip
// (the DisplayString-fill-rect draft still sitting unverified in Mouse.cpp):
// BFME2 drives tooltips through Apt invoker messages, so this waits out the
// tooltip delay, fires the unrowed Show firer 0x003808F0, repositions through
// MoveToolTip with int-to-float coordinates, and counts a hide state down to
// HideToolTip. Evidence:
// - thiscall on a >=0x4FE4 object reusing Mouse's proven slots: UnicodeString
//   tooltip pair +0x12FC/+0x1300 (rowed reset 0x001EE4DC clears both),
//   m_tooltipDelay override +0x4FCC (rowed setter 0x001EEA6D writes it),
//   m_tooltipTextColor +0x4FDC (rowed 0x001EEA6D writes its int channels).
// - delay select matches ZH exactly: default m_tooltipDelayTime (+0x127C),
//   override when m_tooltipDelay (+0x4FCC) >= 0, forced 0 by the GlobalData
//   (0x00DFE758) byte at +0x9C1; still-time via timeGetTime (IAT 0xBBA918)
//   against +0x4FD8 with the +0x1308 shown flag and +0x4FD0/+0x4FD4 stamps.
// - show gate: ScriptEngine (0x00DFE16C) +0x1A138 nonzero returns; TheDisplay
//   (0x00DFE9D8) null, +0x1288 set, +0x12FC empty, +0x9BF clear all take the
//   hide path. Equal +0x12F8/+0x12FC skips the Show block but still sets the
//   +0x1304 state to 4.
// - show block: +0x12F8.set(+0x12FC), font triple from GlobalLanguage data
//   (0x00DFDC84: AsciiString +0xBC, int +0xC0, byte +0xC4) while set else the
//   Mouse triple (+0x126C/+0x1270/+0x1274 = ZH m_tooltipFontName/Size/IsBold),
//   text color via GameMakeColor over the int channels read as bytes, Show
//   through 0x003808F0, Move through rowed 0x003807F3, AsciiString teardown
//   via releaseBuffer 0x00036410 stateless last.
// - hide path: nonempty +0x12F8 returns; --m_1304 past 0 returns; else
//   HideToolTip plus UnicodeString::clear (releaseBuffer 0x00036E70).
// Member names below reuse ZH Mouse names where the slot mapping is proven
// (+0x126C/70/74 font triple, +0x127C delay time, +0x4FCC delay,
// +0x4FDC text color); the rest are honest offset names.
#include "unicode_string.h"
#include "ascii_string.h"
#include "mmsystem.h"

class Display;
extern Display *TheDisplay;
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
class GlobalData;
extern class GlobalData *TheWritableGlobalData;
class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;

struct RGBAColorInt
{
	int red;
	int green;
	int blue;
	int alpha;
};

typedef int BfmeColor;
inline BfmeColor BfmeGameMakeColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | (blue);
}

void Rva003807F3Move(float x, float y);
void Rva003807B7Hide();
void Rva003808F0Show(void *tipText, AsciiString *fontName, int fontSize, int fontBold, int color);

class Mouse
{
	char m_pad0000[0x126C];
	AsciiString m_tooltipFontName;	// +0x126C
	int m_tooltipFontSize;		// +0x1270
	unsigned char m_tooltipFontIsBold;	// +0x1274
	char m_pad1275[0x127C - 0x1275];
	int m_tooltipDelayTime;		// +0x127C
	char m_pad1280[0x1288 - 0x1280];
	unsigned char m_1288;		// +0x1288
	char m_pad1289[0x12F8 - 0x1289];
	UnicodeString m_12F8;		// +0x12F8 sent Apt text
	UnicodeString m_12FC;		// +0x12FC current request
	UnicodeString m_1300;		// +0x1300 shown mirror
	int m_1304;			// +0x1304 show/hide state
	unsigned char m_1308;		// +0x1308 shown flag
	char m_pad1309[0x4F0C - 0x1309];
	int m_4F0C;			// +0x4F0C move Y
	int m_4F10;			// +0x4F10 move X
	char m_pad4F14[0x4FCC - 0x4F14];
	int m_tooltipDelay;		// +0x4FCC
	int m_4FD0;			// +0x4FD0
	unsigned int m_4FD4;		// +0x4FD4
	unsigned int m_4FD8;		// +0x4FD8 still-time stamp
	RGBAColorInt m_tooltipTextColor;	// +0x4FDC
public:
	void drawTooltip();
};

// ?TheGlobalLanguageData triple and ScriptEngine/GlobalData bytes are read
// through TU-local views: only the used slots are modeled.
struct BfmeLangFontTriple
{
	char m_pad00[0xBC];
	AsciiString m_fontName;	// +0xBC
	int m_fontSize;		// +0xC0
	unsigned char m_fontIsBold;	// +0xC4
};

void Mouse::drawTooltip()
{
	unsigned int now = timeGetTime();
	if (m_12FC.compare(m_1300) != 0)
	{
		m_1300.set(m_12FC);
		m_4FD8 = now;
		m_1288 = 0;
	}
	int delay = m_tooltipDelayTime;
	if (m_tooltipDelay >= 0)
		delay = m_tooltipDelay;
	if (*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(TheWritableGlobalData) + 0x9C1))
		delay = 0;
	if (now - m_4FD8 >= (unsigned int)delay)
	{
		if (!m_1308)
		{
			m_4FD0 = 0;
			m_4FD4 = timeGetTime();
		}
		m_1308 = 1;
	}
	else
		m_1308 = 0;
	if (*reinterpret_cast<int *>(reinterpret_cast<char *>(TheScriptEngine) + 0x1A138) != 0)
		return;
	if (*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(TheWritableGlobalData) + 0x9BF)
		&& m_1308 && TheDisplay != 0 && !m_1288 && !m_12FC.isEmpty())
	{
		if (m_12F8.compare(m_12FC) != 0)
		{
			m_12F8.set(m_12FC);
			AsciiString font;
			// Retail stores this slot as a byte (mov [ebp-0x14],al) but pushes
			// it as a dword (push dword [ebp-0x14]): a typeless spill home, not
			// a widened byte local (which would movzx/setne at the push). The
			// union reproduces the typeless slot; the joined value is the
			// tooltip font-bold flag from either triple.
			union {
				int asInt;
				unsigned char asByte;
			} boldSlot;
			int size;
			if (TheGlobalLanguageData != 0
				&& !reinterpret_cast<BfmeLangFontTriple *>(TheGlobalLanguageData)->m_fontName.isEmpty())
			{
				font.setCopyInline(reinterpret_cast<BfmeLangFontTriple *>(TheGlobalLanguageData)->m_fontName);
				size = reinterpret_cast<BfmeLangFontTriple *>(TheGlobalLanguageData)->m_fontSize;
				boldSlot.asByte = reinterpret_cast<BfmeLangFontTriple *>(TheGlobalLanguageData)->m_fontIsBold;
			}
			else
			{
				font.setCopyInline(m_tooltipFontName);
				size = m_tooltipFontSize;
				boldSlot.asByte = m_tooltipFontIsBold;
			}
			int color = BfmeGameMakeColor((unsigned char)m_tooltipTextColor.red,
				(unsigned char)m_tooltipTextColor.green, (unsigned char)m_tooltipTextColor.blue,
				(unsigned char)m_tooltipTextColor.alpha);
			Rva003808F0Show(&m_12F8, &font, size, boldSlot.asInt, color);
			Rva003807F3Move((float)m_4F0C, (float)m_4F10);
		}
		m_1304 = 4;
		return;
	}
	if (m_12F8.isEmpty())
		return;
	if (--m_1304 > 0)
		return;
	Rva003807B7Hide();
	m_12F8.clear();
}
