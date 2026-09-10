// cl: /O1 /DNDEBUG /MD
//
// GadgetListBoxReset, retail 0x003247E5, 34 bytes.
// Dedicated TU so GameWindowManager.cpp bodies cannot see this wrapper.
// Null-checks the listbox then GLM_DEL_ALL (0x4013) through vtable +0xE8.

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual int winSendSystemMsg(GameWindow *window, unsigned msg, int mData1, int mData2) = 0;
};

GameWindowManager *TheWindowManager;

void GadgetListBoxReset(GameWindow *listbox)
{
	if (listbox == 0)
		return;
	TheWindowManager->winSendSystemMsg(listbox, 0x4013, 0, 0);
}
