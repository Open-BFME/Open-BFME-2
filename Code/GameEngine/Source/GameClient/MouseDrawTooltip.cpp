// cl: /FIzh_ascii.h /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/shims/sweep
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#define __SUBSYSTEMINTERFACE_H_
class SubsystemInterfaceList;
#include "PreRTS.h"
#include "../../../../reference/shims/bfme2_mouse/GameClient/Mouse.h"
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


typedef int BfmeColor;
inline BfmeColor BfmeGameMakeColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | (blue);
}

class AptGuiFX
{
public:
	static void MoveToolTip(float x, float y);
public:
	static void ShowToolTip(void *tipText, AsciiString *fontName, int fontSize, int fontBold, int color);
};
void HideToolTip();



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
	if (m_tooltipString.compare(m_str1300) != 0)
	{
		m_str1300.set(m_tooltipString);
		m_stillTime = now;
		m_buttonActivity = 0;
	}
	int delay = m_tooltipDelayTime;
	if (m_tooltipDelay >= 0)
		delay = m_tooltipDelay;
	if (*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(TheWritableGlobalData) + 0x9C1))
		delay = 0;
	if (now - m_stillTime >= (unsigned int)delay)
	{
		if (!m_displayTooltip)
		{
			m_highlightPos = 0;
			m_highlightUpdateStart = timeGetTime();
		}
		m_displayTooltip = 1;
	}
	else
		m_displayTooltip = 0;
	if (*reinterpret_cast<int *>(reinterpret_cast<char *>(TheScriptEngine) + 0x1A138) != 0)
		return;
	if (*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(TheWritableGlobalData) + 0x9BF)
		&& m_displayTooltip && TheDisplay != 0 && !m_buttonActivity && !m_tooltipString.isEmpty())
	{
		if (m_str12F8.compare(m_tooltipString) != 0)
		{
			m_str12F8.set(m_tooltipString);
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
			AptGuiFX::ShowToolTip(&m_str12F8, &font, size, boldSlot.asInt, color);
			AptGuiFX::MoveToolTip((float)m_currMouse.pos.x, (float)m_currMouse.pos.y);
		}
		reinterpret_cast<int &>(m_tooltipDisplayString) = 4;
		return;
	}
	if (m_str12F8.isEmpty())
		return;
	if (--reinterpret_cast<int &>(m_tooltipDisplayString) > 0)
		return;
	HideToolTip();
	m_str12F8.clear();
}
