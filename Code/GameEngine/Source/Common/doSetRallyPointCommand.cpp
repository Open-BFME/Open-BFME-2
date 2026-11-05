// cl: /MD
// ?doSetRallyPointCommand@@YAHPAXPAUICoord2D@@@Z @0x00431241 164B: free Emit building GameMessage 0x413 via InGameUI slot75 TacticalView screenToTerrain MessageStream createMessage plus Keyboard check. Evidence: unlock lane; globals TheInGameUI TheTacticalView TheMessageStream TheKeyboard; rowed appendObjectIDArgument 0x0030F979 appendLocationArgument 0x0030F9BB isShift 0x00232683 appendBooleanArgument 0x0030F963; caller 0x004317BB.
#include "../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../GameLogic/Object/object.h"
#include "../../Include/GameClient/Drawable.h"

#include "../../Include/Common/MessageStream.h"


extern MessageStream *TheMessageStream;

class TacticalView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual void s88(); virtual void s89();
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool clamp);
};

extern class View *TheTacticalView;

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

class Rva0025CEEFHost;
extern class Keyboard *TheKeyboard;

#include "../../Include/GameClient/KeyboardClass.h"

int __cdecl doSetRallyPointCommand(void *a, ICoord2D *b)
{
	if (a == 0 || b == 0)
		return 1;
	Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
	if (draw == 0)
		return 1;
	if (draw->getObject() == 0)
		return 1;
	Coord3D pos;
	((TacticalView *)TheTacticalView)->screenToTerrain(b, &pos, false);
	GameMessage *msg = TheMessageStream->appendMessage(0x413);
	msg->appendObjectIDArgument(draw->getObject()->getID());
	msg->appendLocationArgument(pos);
	bool active = TheKeyboard->isShift();
	msg->appendBooleanArgument(active);
	msg->appendObjectIDArgument(INVALID_OBJECT_ID);
	return 1;
}
