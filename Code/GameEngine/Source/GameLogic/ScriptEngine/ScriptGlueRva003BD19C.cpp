// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// ?Rva003BD19CSet@ScriptActions@@QAEXPAXPAVParameter@@@Z @0x003BD19C 212B (dump range 18).
// Unit-named-plus-player-mask loop: resolves the unit through rowed
// ScriptEngine 0x003588E7 getUnitNamed, builds the player mask from the
// struct's +0x10 name through rowed 0x00357475, then walks rowed 0x002A7BC9.
// When the walked player is the list's +0x10 local player, notifies
// TheInGameUI (slot 0x110), emits message 0x3E9 (rowed appends
// 0x0030F963/0x0030F979) and routes the unit's drawable through TheInGameUI
// slot 0x108; every walked player also feeds the pinned 0x0023C924 GameLogic
// member with (unit, 1, 1 << index, 0).
#include "ascii_string.h"

class Parameter;
class Drawable;
#include "../Object/object.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/Common/Player.h"
#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../Include/Common/MessageStream.h"

extern class MessageStream *TheMessageStream;

#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

void ScriptActions::Rva003BD19CSet(void *p, Parameter *param)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	if (obj == 0)
		return;
	const AsciiString &name = *(const AsciiString *)((const char *)p + 0x10);
	int mask = TheScriptEngine->rva00357475(name, 0);
	if (mask == 0)
		return;
	Player *pl;
	do {
		pl = ThePlayerList->getEachPlayerFromMask(mask);
		if (pl != 0) {
			if (pl == ThePlayerList->m_local) {
				TheInGameUI->deselectAllDrawables();
				GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_CREATE_SELECTED_GROUP);
				msg->appendBooleanArgument(true);
				msg->appendObjectIDArgument(obj->m_id);
				TheInGameUI->selectDrawable(obj->getDrawable());
			}
			TheGameLogic->selectObject((Object *)obj, true, 1 << pl->m_playerIndex, false);
		}
	} while (mask != 0);
}
