// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Retail 0x0042970A (RVA 0x0042970A) size 103: find command button by override id 0x1c.
// Evidence: TheInGameUI vtable+0x12c then +0xfc Object then rva00290E67 AsciiString then g_bfmeWorldRV Rva0031D5F8 lookup to CommandSet then getCommandButton loop 0x20 with +0x14==0x18 and Overridable +0x44 +0x1c vs arg.
#include "ascii_string.h"

#include "../../../GameLogic/Object/object.h"

class BfmeWorldRV;
extern class ControlBar *TheControlBar;

#include "../../../../Include/Common/Rva0031D5F8.h"

class CommandButton;
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x1c];
	int m_id1c;
};

class CommandButton
{
public:
	char m_pad00[0x14];
	int m_type14;
	char m_pad18[0x44 - 0x18];
	Overridable *m_over44;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

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
			if (btn->m_type14 != 0x18) {
				continue;
			}
			const Overridable *ov = btn->m_over44->friend_getFinalOverride();
			if (ov->m_id1c == id) {
				return btn;
			}
		}
	}
	return 0;
}

// Member ABI: context evaluator42AABF loads its CommandTranslator receiver
// into ECX before passing power51. Receiver remains unused inside this body.
