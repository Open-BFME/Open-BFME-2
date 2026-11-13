// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BBAD3Set@@YAXXZ @0x003BBAD3 99B unlock callers 0x003BD5AC 0x003BE5EC 0x003BE6FC 0x003CBF32 callees setInputEnabled setVisibility appendBooleanArgument rva00405AA7 clearFlags slots 0x48 0x110
// Evidence: InGameUI+Mouse disables then MessageStream 0x3EC boolean then InGameUI slot 0x110 and 0x8B0 clear then tail clearFlags.
#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
#include "../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
#include "../../../Include/Common/MessageStream.h"
extern class MessageStream *TheMessageStream;
struct BfmeWorldRV;
extern class ControlBar *TheControlBar;
#include "../../../Include/Common/Rva00405AA7.h"
class BfmeOwnVVD;
class LookAtTranslator; extern LookAtTranslator *TheLookAtTranslator;
#include "../../../Include/Common/Rva005B5440.h"
void Rva003BBAD3Set()
{
	TheInGameUI->setInputEnabled(false);
	TheMouse->setVisibility(false);
	GameMessage *gameMessage = TheMessageStream->appendMessage(GameMessage::MSG_DESTROY_SELECTED_GROUP);
	gameMessage->appendBooleanArgument(true);
	TheInGameUI->deselectAllDrawables();
	((char *)TheInGameUI)[0x8b0] = 0;
	((Rva00405AA7 *)(*(BfmeWorldRV **)&TheControlBar))->rva00405AA7();
	return ((Rva005B5440 *)((BfmeOwnVVD *)TheLookAtTranslator))->clearFlags();
}

#include "../../../Include/Common/Rva003BBAD3.h"

// ICF-folded twin of Rva003BBAD3Set above (same 99 bytes at 0x003BBAD3):
// the member spelling ignores its receiver, so with the same globals-only
// statements it compiles to the identical body, including the tail call.
void Rva003BBAD3::rva003BBAD3()
{
	TheInGameUI->setInputEnabled(false);
	TheMouse->setVisibility(false);
	GameMessage *gameMessage = TheMessageStream->appendMessage(GameMessage::MSG_DESTROY_SELECTED_GROUP);
	gameMessage->appendBooleanArgument(true);
	TheInGameUI->deselectAllDrawables();
	((char *)TheInGameUI)[0x8b0] = 0;
	((Rva00405AA7 *)(*(BfmeWorldRV **)&TheControlBar))->rva00405AA7();
	return ((Rva005B5440 *)((BfmeOwnVVD *)TheLookAtTranslator))->clearFlags();
}

// ?doEnableInput@ScriptActions@@QAEXXZ @0x003BBB36 27B leaf caller 0x003CBF3E globals TheInGameUI TheMouse callees setInputEnabled setVisibility
// Evidence: mov ecx,[TheInGameUI] push 1 call setInputEnabled mov ecx,[TheMouse] push 1 call setVisibility ret.
void ScriptActions::doEnableInput()
{
	TheInGameUI->setInputEnabled(true);
	TheMouse->setVisibility(true);
}
