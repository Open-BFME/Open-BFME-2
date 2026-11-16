// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Retail 0x0042970A (RVA 0x0042970A) size 103: find command button by override id 0x1c.
// Evidence: TheInGameUI vtable+0x12c then +0xfc Object then rva00290E67 AsciiString then g_bfmeWorldRV Rva0031D5F8 lookup to CommandSet then getCommandButton loop 0x20 with +0x14==0x18 and the special power +0x44, whose final override +0x1c is compared with arg.
#include "ascii_string.h"

#include "../../../GameLogic/Object/object.h"

class BfmeWorldRV;
extern class ControlBar *TheControlBar;

#include "../../../../Include/Common/Rva0031D5F8.h"

#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/GameClient/CommandButton.h"
#include "../../../../Include/GameClient/CommandSet.h"
#include "../../../../Include/Common/SpecialPower.h"

#include "../../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

struct InGameRet
{
	char m_pad[0xfc];
	Object *m_obj;
};

#include "../../../../Include/GameClient/CommandTranslator.h"
const CommandButton *CommandTranslator::rva0042970A(int id)
{
	int i;
	const CommandButton *btn;
	CommandSet *set;
	InGameRet *inGameRet = (InGameRet *)((InGameUI *)TheInGameUI)->getFirstSelectedDrawable();
	Object *obj = inGameRet->m_obj;
	const AsciiString *name = obj->rva00290E67();
	set = (CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(name);
	if (set != 0) {
		for (i = 0; i < 0x20; i++) {
			btn = set->getCommandButton(i);
			if (btn == 0) {
				continue;
			}
			if (btn->m_command != 0x18) {
				continue;
			}
			const SpecialPowerTemplate *sp = btn->m_specialPower->getFO();
			if (sp->m_type == id) {
				return btn;
			}
		}
	}
	return 0;
}

// Member ABI: context evaluator42AABF loads its CommandTranslator receiver
// into ECX before passing power51. Receiver remains unused inside this body.
