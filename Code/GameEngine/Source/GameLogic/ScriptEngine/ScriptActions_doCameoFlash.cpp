// cl: /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ?doCameoFlash@ScriptActions@@IAEXABVAsciiString@@H@Z @0x003BB556 64B chain via 0x0031BE3C caller 0x003CBAEC globals 0xE01CFC 0xDBA4E8
// Evidence: ControlBar::findCommandButton row 0x0031BE3C, g_bfmeWorldRV alias, FramesPerSecond BfmeClientFramesPerSecond, CommandButton+0xF8 store.
#include "../../../Include/GameClient/CommandButton.h"
#include "../../../Include/GameClient/ControlBar.h"
struct BfmeWorldRV;
extern class ControlBar *TheControlBar;
extern int BfmeClientFramesPerSecond;
class ScriptActions
{
protected:
	void doCameoFlash(const AsciiString &name, int v);
};

void ScriptActions::doCameoFlash(const AsciiString &name, int v)
{
	const CommandButton *btn = ((ControlBar *)(void *)(*(BfmeWorldRV **)&TheControlBar))->findCommandButton(name);
	if (btn) {
		int q = BfmeClientFramesPerSecond * v / 10;
		if (q % 2 == 1)
			++q;
		btn->setFlashCount(q);
	}
}
