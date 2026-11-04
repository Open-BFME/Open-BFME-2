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
class GameMessage
{
public:
	void appendBooleanArgument(bool v);
};
class MessageStream
{
public:
	virtual void m00();
	virtual void m01();
	virtual void m02();
	virtual void m03();
	virtual void m04();
	virtual void m05();
	virtual void m06();
	virtual void m07();
	virtual void m08();
	virtual void m09();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
	virtual GameMessage *m18(int v);
};
extern class MessageStream *TheMessageStream;
struct BfmeWorldRV;
extern class ControlBar *TheControlBar;
class Rva00405AA7
{
public:
	void rva00405AA7();
};
class BfmeOwnVVD;
class LookAtTranslator; extern LookAtTranslator *TheLookAtTranslator;
class Rva005B5440
{
public:
	void clearFlags();
};
void Rva003BBAD3Set()
{
	TheInGameUI->setInputEnabled(false);
	TheMouse->setVisibility(false);
	GameMessage *gameMessage = TheMessageStream->m18(0x3ec);
	gameMessage->appendBooleanArgument(true);
	TheInGameUI->deselectAllDrawables();
	((char *)TheInGameUI)[0x8b0] = 0;
	((Rva00405AA7 *)(*(BfmeWorldRV **)&TheControlBar))->rva00405AA7();
	return ((Rva005B5440 *)((BfmeOwnVVD *)TheLookAtTranslator))->clearFlags();
}

class Rva003BBAD3
{
public:
	void rva003BBAD3();
};

// ICF-folded twin of Rva003BBAD3Set above (same 99 bytes at 0x003BBAD3):
// the member spelling ignores its receiver, so with the same globals-only
// statements it compiles to the identical body, including the tail call.
void Rva003BBAD3::rva003BBAD3()
{
	TheInGameUI->setInputEnabled(false);
	TheMouse->setVisibility(false);
	GameMessage *gameMessage = TheMessageStream->m18(0x3ec);
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
