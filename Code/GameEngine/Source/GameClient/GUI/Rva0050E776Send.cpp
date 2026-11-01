// cl: /DNDEBUG /MD
// ?Rva0050E776Send@@YAHPAVGameWindow@@H@Z @0x0050E776
// (30B): sends 0x400D via TheWindowManager slot 58 winSendSystemMsg.
// Identity via TheWindowManager plus 0x400D plus slot 0xE8 (precedent
// GameWindowManager_winSetFocus) plus caller 0x0050F2A6; cdecl 2 args.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

#include "../../../Include/GameClient/Bfme2GameWindow.h"

class GameWindowManager {
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual void *winGetFocus();
#undef V
	virtual Int winSetFocus(GameWindow *window);
#define W(n) virtual void pad##n() = 0;
	W(50) W(51) W(52) W(53) W(54) W(55) W(56) W(57)
#undef W
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
};

extern GameWindowManager *TheWindowManager;

int __cdecl Rva0050E776Send(GameWindow *window, int data)
{
	return TheWindowManager->winSendSystemMsg(window, 0x400D, (WindowMsgData)data, 0);
}

// Native 50E794..50E7BB (39B): a file-static helper in cl 7.1's register
// convention (the slot in ECX, the player index on the stack, caller-cleaned):
// true when the slot is AI (rowed GameSlot::isAI 0x003FF127), when there is no
// TheNetwork (VA 0x00DFEA28), or when TheNetwork's virtual slot 51 (+0xCC)
// accepts the index. No call to it survives in the image; the anchor below
// only forces cl to emit it in that convention. Identity unproven.
typedef bool Bool;

class GameSlot
{
public:
	Bool isAI() const;
};

class Rva0050E794Network
{
public:
#define N(n) virtual void pad##n();
	N(0) N(1) N(2) N(3) N(4) N(5) N(6) N(7) N(8) N(9)
	N(10) N(11) N(12) N(13) N(14) N(15) N(16) N(17) N(18) N(19)
	N(20) N(21) N(22) N(23) N(24) N(25) N(26) N(27) N(28) N(29)
	N(30) N(31) N(32) N(33) N(34) N(35) N(36) N(37) N(38) N(39)
	N(40) N(41) N(42) N(43) N(44) N(45) N(46) N(47) N(48) N(49)
	N(50)
#undef N
	virtual Bool slot51(int index);	// +0xCC
};

class NetworkInterface;
extern NetworkInterface *TheNetwork;

static __declspec(noinline) Bool Rva0050E794(const GameSlot *slot, int index)
{
	if (slot->isAI())
		return true;
	if (TheNetwork && !((Rva0050E794Network *)TheNetwork)->slot51(index))
		return false;
	return true;
}

// ?Rva0050E794Anchor absent-from-retail
Bool Rva0050E794Anchor(const GameSlot *slot, int index)
{
	return Rva0050E794(slot, index);
}
