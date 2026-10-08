// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?setControlCommand@ControlBar@@QAEXABVAsciiString@@PAVGameWindow@@PBVCommandButton@@@Z
// @0x0031BA47 57B: Zero Hour's ControlBar::setControlCommand by window name
// (ControlBar.cpp): looks the button up under the parent through
// TheNameKeyGenerator and TheWindowManager (slot 60) and, when found, hands
// it to the window overload, rowed at its address 0x0031B641. The donor's
// debug assert is gone.
#include "ascii_string.h"

class GameWindow;
class CommandButton;

enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
#define CB_SLOT(n) virtual void slot##n();
	CB_SLOT(00) CB_SLOT(01) CB_SLOT(02) CB_SLOT(03) CB_SLOT(04) CB_SLOT(05) CB_SLOT(06) CB_SLOT(07) CB_SLOT(08) CB_SLOT(09)
	CB_SLOT(10) CB_SLOT(11) CB_SLOT(12) CB_SLOT(13) CB_SLOT(14) CB_SLOT(15) CB_SLOT(16) CB_SLOT(17) CB_SLOT(18) CB_SLOT(19)
	CB_SLOT(20) CB_SLOT(21) CB_SLOT(22) CB_SLOT(23) CB_SLOT(24) CB_SLOT(25) CB_SLOT(26) CB_SLOT(27) CB_SLOT(28) CB_SLOT(29)
	CB_SLOT(30) CB_SLOT(31) CB_SLOT(32) CB_SLOT(33) CB_SLOT(34) CB_SLOT(35) CB_SLOT(36) CB_SLOT(37) CB_SLOT(38) CB_SLOT(39)
	CB_SLOT(40) CB_SLOT(41) CB_SLOT(42) CB_SLOT(43) CB_SLOT(44) CB_SLOT(45) CB_SLOT(46) CB_SLOT(47) CB_SLOT(48) CB_SLOT(49)
	CB_SLOT(50) CB_SLOT(51) CB_SLOT(52) CB_SLOT(53) CB_SLOT(54) CB_SLOT(55) CB_SLOT(56) CB_SLOT(57) CB_SLOT(58) CB_SLOT(59)
#undef CB_SLOT
	virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);	// slot 60
};
extern GameWindowManager *TheWindowManager;

class ControlBar
{
public:
	void setControlCommand(const AsciiString &buttonWindowName, GameWindow *parent, const CommandButton *commandButton);
	void rva0031B641(GameWindow *button, const CommandButton *commandButton);	// setControlCommand(GameWindow *, ...)
};

void ControlBar::setControlCommand(const AsciiString &buttonWindowName, GameWindow *parent, const CommandButton *commandButton)
{
	int winID = TheNameKeyGenerator->nameToKey(buttonWindowName);
	GameWindow *win = TheWindowManager->winGetWindowFromId(parent, winID);
	if (win == 0)
		return;
	rva0031B641(win, commandButton);
}
