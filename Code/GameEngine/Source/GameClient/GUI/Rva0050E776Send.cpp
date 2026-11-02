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

#include "../../../Include/GameClient/GameWindowManager.h"

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

#include "../../../Include/GameNetwork/GameInfo.h"

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
