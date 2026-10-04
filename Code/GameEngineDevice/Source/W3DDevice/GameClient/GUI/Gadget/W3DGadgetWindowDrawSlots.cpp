// cl: /O1 /DNDEBUG /MD
//
// Slots 1 and 2 forward the window and the message to the gadget's input
// and system callbacks (cdecl (GameWindow *, msg, mData1, mData2)); slot 3
// of seventeen BFME2 gadget window vtables (all sharing slot 0, the
// scalar deleting destructor 0x0008FFC4): each hands the window and the
// instance data to its W3DGadget*Draw function (cdecl, (GameWindow *,
// WinInstanceData *)) and returns 1. That BFME2's gadgets are GameWindow
// subclasses whose slot 3 draws is inferred from these bodies and their
// matched callees (W3DGadgetListBoxDraw and the rest); the classes are named
// after their slot bodies and the unnamed draw functions after their
// addresses.
//
//   slot body   vtable      draw function
//   0x000A1CFB  0x00BC8D5C#3  Rva000A166ADraw
//   0x000A3131  0x00BC904C#3  W3DGadgetListBoxDraw
//   0x000A6097  0x00BC7DC8#3  W3DGadgetPushButtonImageDraw
//   0x000A086D  0x00BC8C54#3  Rva000A03BFDraw
//   0x000A087F  0x00BC8C80#3  Rva000A0581Draw
//   0x000A0C42  0x00BC8CAC#3  W3DGadgetStaticTextDraw
//   0x000A12E6  0x00BC8D04#3  Rva000A0D5EDraw
//   0x000A15EC  0x00BC8D88#3  Rva000A136ADraw
//   0x000A1D0D  0x00BC8DE0#3  Rva000A1747Draw
//   0x000A260A  0x00BC8FF4#3  W3DGadgetComboBoxDraw
//   0x000A3DA8  0x00BC90FC#3  W3DGadgetTabControlDraw
//   0x000A3DBA  0x00BC9128#3  W3DGadgetTabControlImageDraw
//   0x000A4328  0x00BC9154#3  Rva000A3F61Draw
//   0x000A433A  0x00BC9180#3  Rva000A4139Draw
//   0x000A4783  0x00BC91AC#3  Rva000A44D2Draw
//   0x000A4795  0x00BC91D8#3  Rva000A46B7Draw
//   0x000A6007  0x00BC9204#3  Rva000A53DEDraw

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class WinInstanceData;

class GameWindow;

typedef WindowMsgHandledType (*GameWinInputFunc)(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData);
typedef void (*GameWinTooltipFunc)(GameWindow *, WinInstanceData *, UnsignedInt);
typedef void (*Rva0009FD78Func)(GameWindow *);

// GameWindow's own versions of slots 1, 3, 4 and 5 (shared by the window
// tables that do not override them; slot counts in the comments): input
// calls the window's input callback (+0x1E0, winSetInputFunc's field), draw
// does nothing but answer 1, slot 4 calls the tooltip callback (+0x1EC,
// winSetTooltipFunc's field) and slot 5 the callback at +0x1F0, each
// answering whether there was one. Slot names follow the callbacks they call
// (inferred).
class GameWindow
{
public:
	virtual ~GameWindow();
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);	// 0x000A0CFF (4 tables)
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);									// 0x000A12F8 (23 tables)
	virtual Int tooltip(WinInstanceData *instData, UnsignedInt mouse);				// 0x0008FF56 (29 tables)
	virtual Int rva0009FD78();														// 0x0009FD78 (24 tables)

private:
	unsigned char m_unmodelled_04[0x1E0 - 0x04];
	GameWinInputFunc m_inputFunc;				// +0x1E0
	unsigned char m_unmodelled_1E4[0x1EC - 0x1E4];
	GameWinTooltipFunc m_tooltipFunc;			// +0x1EC
	Rva0009FD78Func m_bfmeFunc1F0;				// +0x1F0, unnamed
};

WindowMsgHandledType GameWindow::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	if (m_inputFunc)
		return m_inputFunc(this, msg, mData1, mData2);
	return MSG_IGNORED;
}

Int GameWindow::draw(WinInstanceData *instData)
{
	return 1;
}

Int GameWindow::tooltip(WinInstanceData *instData, UnsignedInt mouse)
{
	if (m_tooltipFunc)
	{
		m_tooltipFunc(this, instData, mouse);
		return 1;
	}
	return 0;
}

// Slot 5 (0x0009FD78) calls the +0x1F0 callback the same way, but retail's
// null path jumps into the three bytes after it (0x0009FD8A, xor eax, eax;
// ret), which the ledger rows as their own zero getter; it is recorded
// blocked rather than defined here (reverse/re_attempts.log).

WindowMsgHandledType GadgetCheckBoxInput(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetCheckBoxSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetComboBoxSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetListBoxSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetProgressBarSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetPushButtonInput(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetPushButtonSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetRadioButtonInput(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetRadioButtonSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetStaticTextInput(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetStaticTextSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetTabControlInput(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType GadgetTabControlSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva003207F5System(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva00320DA9Input(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva00321620Input(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva003218B0System(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva00321B50Input(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva00321E5CSystem(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva00322C25Input(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva00324E92Input(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
WindowMsgHandledType Rva003285D4Input(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
void Rva000A03BFDraw(GameWindow *window, WinInstanceData *instData);
void Rva000A0581Draw(GameWindow *window, WinInstanceData *instData);
void Rva000A0D5EDraw(GameWindow *window, WinInstanceData *instData);
void Rva000A136ADraw(GameWindow *window, WinInstanceData *instData);
void Rva000A166ADraw(GameWindow *window, WinInstanceData *instData);
void Rva000A1747Draw(GameWindow *window, WinInstanceData *instData);
void Rva000A3F61Draw(GameWindow *window, WinInstanceData *instData);
void Rva000A4139Draw(GameWindow *window, WinInstanceData *instData);
void Rva000A44D2Draw(GameWindow *window, WinInstanceData *instData);
void Rva000A46B7Draw(GameWindow *window, WinInstanceData *instData);
void Rva000A53DEDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetComboBoxDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetListBoxDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetPushButtonImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetStaticTextDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetTabControlDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetTabControlImageDraw(GameWindow *window, WinInstanceData *instData);

class Rva000A1CFBWindow : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A1CFBWindow::draw(WinInstanceData *instData)
{
	Rva000A166ADraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A1CFBWindow::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva00321620Input(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A1CFBWindow::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva003218B0System(this, msg, mData1, mData2);
}

class Rva000A3131Window : public GameWindow
{
public:
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A3131Window::draw(WinInstanceData *instData)
{
	W3DGadgetListBoxDraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A3131Window::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetListBoxSystem(this, msg, mData1, mData2);
}

class Rva000A6097Window : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A6097Window::draw(WinInstanceData *instData)
{
	W3DGadgetPushButtonImageDraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A6097Window::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva003285D4Input(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A6097Window::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetPushButtonSystem(this, msg, mData1, mData2);
}

class Rva000A086DWindow : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A086DWindow::draw(WinInstanceData *instData)
{
	Rva000A03BFDraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A086DWindow::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva00320DA9Input(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A086DWindow::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva003207F5System(this, msg, mData1, mData2);
}

class Rva000A087FWindow : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A087FWindow::draw(WinInstanceData *instData)
{
	Rva000A0581Draw(this, instData);
	return 1;
}

class Rva000A0C42Window : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A0C42Window::draw(WinInstanceData *instData)
{
	W3DGadgetStaticTextDraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A0C42Window::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetStaticTextInput(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A0C42Window::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetStaticTextSystem(this, msg, mData1, mData2);
}

class Rva000A12E6Window : public GameWindow
{
public:
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A12E6Window::draw(WinInstanceData *instData)
{
	Rva000A0D5EDraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A12E6Window::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetProgressBarSystem(this, msg, mData1, mData2);
}

class Rva000A15ECWindow : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A15ECWindow::draw(WinInstanceData *instData)
{
	Rva000A136ADraw(this, instData);
	return 1;
}

class Rva000A1D0DWindow : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A1D0DWindow::draw(WinInstanceData *instData)
{
	Rva000A1747Draw(this, instData);
	return 1;
}

class Rva000A260AWindow : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A260AWindow::draw(WinInstanceData *instData)
{
	W3DGadgetComboBoxDraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A260AWindow::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva00322C25Input(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A260AWindow::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetComboBoxSystem(this, msg, mData1, mData2);
}

class Rva000A3DA8Window : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A3DA8Window::draw(WinInstanceData *instData)
{
	W3DGadgetTabControlDraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A3DA8Window::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetTabControlInput(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A3DA8Window::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetTabControlSystem(this, msg, mData1, mData2);
}

class Rva000A3DBAWindow : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A3DBAWindow::draw(WinInstanceData *instData)
{
	W3DGadgetTabControlImageDraw(this, instData);
	return 1;
}

class Rva000A4328Window : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A4328Window::draw(WinInstanceData *instData)
{
	Rva000A3F61Draw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A4328Window::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetRadioButtonInput(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A4328Window::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetRadioButtonSystem(this, msg, mData1, mData2);
}

class Rva000A433AWindow : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A433AWindow::draw(WinInstanceData *instData)
{
	Rva000A4139Draw(this, instData);
	return 1;
}

class Rva000A4783Window : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A4783Window::draw(WinInstanceData *instData)
{
	Rva000A44D2Draw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A4783Window::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetCheckBoxInput(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A4783Window::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetCheckBoxSystem(this, msg, mData1, mData2);
}

class Rva000A4795Window : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A4795Window::draw(WinInstanceData *instData)
{
	Rva000A46B7Draw(this, instData);
	return 1;
}

class Rva000A6007Window : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A6007Window::draw(WinInstanceData *instData)
{
	Rva000A53DEDraw(this, instData);
	return 1;
}

WindowMsgHandledType Rva000A6007Window::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return GadgetPushButtonInput(this, msg, mData1, mData2);
}

class Rva000A1616Window : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
	virtual WindowMsgHandledType system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
};

WindowMsgHandledType Rva000A1616Window::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva00321B50Input(this, msg, mData1, mData2);
}

WindowMsgHandledType Rva000A1616Window::system(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva00321E5CSystem(this, msg, mData1, mData2);
}

class Rva000A26DFWindow : public GameWindow
{
public:
	virtual WindowMsgHandledType input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2);
};

WindowMsgHandledType Rva000A26DFWindow::input(UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2)
{
	return Rva00324E92Input(this, msg, mData1, mData2);
}

// Image variants that keep their text sibling's input and system slots and
// override only the draw (vtables 0x00BC8CD8, 0x00BC9020 and 0x00BC90D0/
// 0x00BC90A4, slot 3), so they are modelled as subclasses of those classes.
void W3DGadgetStaticTextImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetComboBoxImageDraw(GameWindow *window, WinInstanceData *instData);
void W3DGadgetListBoxImageDraw(GameWindow *window, WinInstanceData *instData);

class Rva000A0C54Window : public Rva000A0C42Window
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A0C54Window::draw(WinInstanceData *instData)
{
	W3DGadgetStaticTextImageDraw(this, instData);
	return 1;
}

class Rva000A261CWindow : public Rva000A260AWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A261CWindow::draw(WinInstanceData *instData)
{
	W3DGadgetComboBoxImageDraw(this, instData);
	return 1;
}

class Rva000A3143Window : public Rva000A26DFWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A3143Window::draw(WinInstanceData *instData)
{
	W3DGadgetListBoxImageDraw(this, instData);
	return 1;
}

// Slot 5 of the push-button tables 0x00BC9204, 0x00BC9230 and 0x00BC7DC8
// (0x000A495E): hands the window to 0x00328700 and answers 1 instead of
// calling the +0x1F0 callback. Modelled on the class of the first two.
int Rva00328700(GameWindow *window);

class Rva000A495EWindow : public Rva000A6007Window
{
public:
	virtual Int rva0009FD78();
};

Int Rva000A495EWindow::rva0009FD78()
{
	Rva00328700(this);
	return 1;
}
