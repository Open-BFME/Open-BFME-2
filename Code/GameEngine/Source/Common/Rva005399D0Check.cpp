// cl: /MD
// ?rva005399D0Check@ControlBar@@QAEHPAVObject@@@Z @0x005399D0 67B:
// ControlBar member predicate over Object*: null check then isLocallyControlled
// then isSelectable then isStructure==0 then TheInGameUI slot 0x188 call,
// true (1) when all pass else false (0). Caller 0x0042AF97 pushes Object*.
// Evidence: rowed Object preds 0x0028B07A 0x0028D7FD plus int leaf 0x0028D481
// plus TheInGameUI global 0x009FEDF0 slot 98; ret 4 single dword arg.
// Native caller0042AF97 loads TheControlBar into ECX before this call;
// the member receiver is unused within the body. This corrects the earlier
// free-function ABI inference; the target name remains address-derived.
#include "../GameLogic/Object/object.h"

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

struct Rva00539997Sub
{
	char m_pad[0xFC];
	int m_FC;
};

enum CBCommandStatus { CBC_COMMAND_NOT_USED = 0, CBC_COMMAND_USED = 1 };
enum GadgetGameMessage { GGM_NONE = 0 };
class GameWindow;
class ControlBar
{
protected:
	CBCommandStatus processCommandTransitionUI(GameWindow *control, GadgetGameMessage gadgetMessage);
public:
	void switchToContext(int ctx, void *data);
	int rva005399D0Check(Object *);
private:
	char m_pad00[0x6C];
	Rva00539997Sub *m_6C;
	int m_70;
};

// ?processCommandTransitionUI@ControlBar@@IAE?AW4CBCommandStatus@@PAVGameWindow@@W4GadgetGameMessage@@@Z
// @0x00539997 (57B): Zero Hour's and BFME1's (0x004A6520) ControlBar::
// processCommandTransitionUI: with no source object outside multi-select,
// drop to the empty context and report the command unused.
CBCommandStatus ControlBar::processCommandTransitionUI(GameWindow *, GadgetGameMessage)
{
	int ctx = m_70;
	if (ctx == 7 || (m_6C && m_6C->m_FC != 0))
		return CBC_COMMAND_USED;
	if (ctx != 0 && ctx != 8 && ctx != 9)
		switchToContext(0, 0);
	return CBC_COMMAND_NOT_USED;
}

int ControlBar::rva005399D0Check(Object *obj)
{
	if (obj == 0)
		return 0;
	if (!obj->isLocallyControlled())
		return 0;
	if (!obj->isSelectable())
		return 0;
	if ((unsigned char)obj->isStructure() == 0)
	{
		TheInGameUI->selectMatchingAcrossScreen();
		return 1;
	}
	return 0;
}
