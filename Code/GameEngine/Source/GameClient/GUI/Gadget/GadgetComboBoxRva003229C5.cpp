// cl: /DNDEBUG /MD
// ?Rva003229C5Hide@@YAXPAVGameWindow@@@Z @0x003229C5 132B.
// ZH/BFME1 donor GadgetComboBox.cpp HideListBox: null listBox guard then
// winIsHidden then winHide TRUE then entry size and combo size then
// winSetSize(newSize.x winSize.y). BFME2 adds loneWindow focus release.
// Retail calls 0x002C0315 listBox +0x2c rowed as bfmeGo925A then winIsHidden
// 0x313CD9 winHide 0x313C64 then 0x002C032C entry +0x28 rowed as GetListBox
// then winGetSize 0x313BC6 twice winSetSize 0x313B87 then manager 0xD4 get
// 0xD0 set; 5 callers include 0x00322BB8 0x00322FF5.
typedef int Int;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

struct ICoord2D
{
	Int x;
	Int y;
};

class GameWindow;
class BfmeKeyLC;

void *bfmeGo925A(BfmeKeyLC *k);
GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);

class GameWindow
{
public:
	Bool winIsHidden();
	Int winHide(Bool hide);
	Int winGetSize(Int *width, Int *height);
	Int winSetSize(Int width, Int height);
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41)
#undef V
	virtual void winNextTab(GameWindow *window);
	virtual void winPrevTab(GameWindow *window);
#define W(n) virtual void pad##n() = 0;
	W(44) W(45) W(46) W(47) W(48)
#undef W
	virtual Int winSetFocus(GameWindow *window);
#define X(n) virtual void pad##n() = 0;
	X(50) X(51)
#undef X
	virtual void winSetLoneWindow(GameWindow *window);
	virtual GameWindow *winGetLoneWindow();
};

extern GameWindowManager *TheWindowManager;

void Rva003229C5Hide(GameWindow *window)
{
	ICoord2D winSize;
	ICoord2D newSize;
	GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)window);
	if (!listBox)
		return;
	if (!listBox->winIsHidden())
	{
		listBox->winHide(true);
		GameWindow *editBox = GadgetComboBoxGetListBox(window);
		editBox->winGetSize(&winSize.x, &winSize.y);
		window->winGetSize(&newSize.x, &newSize.y);
		window->winSetSize(newSize.x, winSize.y);
		if (TheWindowManager->winGetLoneWindow() == window)
			TheWindowManager->winSetLoneWindow(NULL);
	}
}
