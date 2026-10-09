// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?GadgetButtonSetText@@YAXPAVGameWindow@@VUnicodeString@@@Z @0x003283F7 71B
// GadgetButtonSetText; BFME1 donor GadgetPushButton.cpp GadgetButtonSetText verbatim shape
// (winSendSystemMsg GGM_SET_LABEL 0x4001 with &text and 0); TheWindowManager at
// 0x9FEF1C slot 58 0xE8; UnicodeString by-value param destroyed via
// StringBase-G releaseBuffer 0x36E70; null-guarded like donor; adjacent to
// getNewPushButtonData 0x32843E as in donor; callers pass UnicodeString via G copy
// ctor (0x002C19A3 0x0029D79A 0x00303B59 0x00303B96).

typedef unsigned short wchar_t;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class UnicodeString;
class AsciiString;

#include "unicode_string.h"


class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	virtual void windowHiding(GameWindow *window) = 0;
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual GameWindow *winGetFocus() = 0;
	virtual Int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
};

extern GameWindowManager *TheWindowManager;

void GadgetButtonSetText(GameWindow *g, UnicodeString text)
{
	if (g == 0)
		return;
	TheWindowManager->winSendSystemMsg(g, 0x4001, (WindowMsgData)&text, 0);
}

// ?Rva003278F1Set@@YAXPAVGameWindow@@VUnicodeString@@@Z @0x003278F1 71B:
// Same shape as GadgetButtonSetText above: null-guarded winSendSystemMsg
// GGM_SET_LABEL 0x4001 with &text and 0 via TheWindowManager slot 58 0xE8;
// UnicodeString by-value destroyed via releaseBuffer. Callers 0x002C1B42
// 0x00316293 unclaimed. Honest address name; verb Set from 0x4001 msg.
void Rva003278F1Set(GameWindow *g, UnicodeString text)
{
	if (g == 0)
		return;
	TheWindowManager->winSendSystemMsg(g, 0x4001, (WindowMsgData)&text, 0);
}

// Target WB1122270 and native328354..3283F7: update a push-button's cached
// production query through the selected drawable's owner and command data.
class GameWindow {public:void *winGetUserData();};
class Object {public:void *rva0028BC58(Int);};
struct ButtonSelectedDrawable {char pad[0xFC];Object *object;};
class ButtonGameUI
{
public:
#define V(n) virtual void ui##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
 V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
 V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
 V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
 V(70) V(71) V(72) V(73) V(74)
#undef V
 virtual ButtonSelectedDrawable *selectedDrawable();
};
class InGameUI;
extern InGameUI *TheInGameUI;
struct BfmeFixedStorage128 {unsigned m_bits[32];};
class Rva0035B513 {public:BfmeFixedStorage128 *rva0035B513(BfmeFixedStorage128 *);};
namespace _STL {
 template<unsigned N> class _Base_bitset {
 public: bool _M_is_any()const; unsigned m_bits[N];
 };
}
class ThingTemplate;
class CommandButton {public:const ThingTemplate *rva0035B570()const;};
void *GadgetButtonGetData(GameWindow *);
class ButtonProductionQuery
{
public:
#define V(n) virtual void query##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
 V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
#undef V
 virtual Int templateValue(const ThingTemplate*);
 virtual void query19();
 virtual Int maskValue(const BfmeFixedStorage128*);
};
struct ButtonBuildCostData {char pad[0x2c];Int cost;};
void Rva00328354Update(GameWindow *window)
{
 if(!window)return;
 ButtonBuildCostData *data=(ButtonBuildCostData*)window->winGetUserData();
 if(!data)return;
 data->cost=0;
 ButtonSelectedDrawable *selected=((ButtonGameUI*)TheInGameUI)->selectedDrawable();
 if(!selected || !selected->object)return;
 ButtonProductionQuery *production=(ButtonProductionQuery*)selected->object->rva0028BC58(0);
 if(!production)return;
 CommandButton *button=(CommandButton*)GadgetButtonGetData(window);
 if(!button)return;
 const ThingTemplate *tt=button->rva0035B570();
 if(!tt)return;
 BfmeFixedStorage128 mask;
 ((Rva0035B513*)button)->rva0035B513(&mask);
 if(((_STL::_Base_bitset<32>*)&mask)->_M_is_any()) data->cost=production->maskValue(&mask);
 else data->cost=production->templateValue(tt);
}
