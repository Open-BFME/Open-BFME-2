// cl: -O1 -arch:SSE -G7 -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva0042F9DAEmit@ScriptActions@@QAEXXZ, retail 0x0042F9DA, 39 bytes.
// Free emit of MSG 0x3EC with bool true then tail to InGameUI slot 0x110.
// Evidence: globals MessageStreamSubsystem TheInGameUI; rowed appendBooleanArgument 0x0030F963; slots 0x48 0x110 per ControlBarToggle0031AFDE precedent.
#include "../../Include/Common/MessageStream.h"


#include "../../Include/GameClient/InGameUI.h"

extern class MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;

void ScriptActions::Rva0042F9DAEmit()
{
	GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_DESTROY_SELECTED_GROUP);
	msg->appendBooleanArgument(true);
	TheInGameUI->deselectAllDrawables();
}

// SelectionXlat.cpp's free helper is separate from the script member in WB:
// 0x12AA0A0 (no this slot) versus 0x10194A0 (saved this at EBP-8).
// Parent 0x43003C calls the former twice; script case 506 calls the latter.
// Retail folds their complete bodies and relocations at 0x42F9DA.
void deselectAll()
{
	GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_DESTROY_SELECTED_GROUP);
	msg->appendBooleanArgument(true);
	TheInGameUI->deselectAllDrawables();
}
