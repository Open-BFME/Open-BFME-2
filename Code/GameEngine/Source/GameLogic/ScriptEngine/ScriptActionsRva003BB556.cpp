// cl: /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ?Rva003BB556Set@@YGXABVAsciiString@@H@Z @0x003BB556 64B chain via 0x0031BE3C caller 0x003CBAEC globals 0xE01CFC 0xDBA4E8
// Evidence: ControlBar::findCommandButton row 0x0031BE3C, g_bfmeWorldRV alias, FramesPerSecond g_00DBA4E8, CommandButton+0xF8 store.
class CommandButton
{
public:
	unsigned char m_pad[0xF8];
	int m_00F8;
};
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};
struct BfmeWorldRV;
extern struct BfmeWorldRV *g_bfmeWorldRV;
extern int g_009BA4E8;
void __stdcall Rva003BB556Set(const AsciiString &name, int v)
{
	const CommandButton *btn = ((ControlBar *)(void *)g_bfmeWorldRV)->findCommandButton(name);
	if (btn) {
		int q = g_009BA4E8 * v / 10;
		if (q % 2 == 1)
			++q;
		((CommandButton *)btn)->m_00F8 = q;
	}
}
