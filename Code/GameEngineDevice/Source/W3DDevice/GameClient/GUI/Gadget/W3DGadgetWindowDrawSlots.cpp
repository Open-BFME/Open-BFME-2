// cl: /O1 /DNDEBUG /MD
//
// Slot 3 of seventeen BFME2 gadget window vtables (all sharing slot 0, the
// scalar deleting destructor 0x0008FFC4): each hands the window and the
// instance data to its W3DGadget*Draw function (cdecl, (GameWindow *,
// WinInstanceData *)) and returns 1. That BFME2's gadgets are GameWindow
// subclasses whose slot 3 draws is inferred from these bodies and their
// matched callees (W3DGadgetListBoxDraw and the rest); the classes are named
// after their slot bodies and the unnamed draw functions after their
// addresses.
//
//   slot body   vtable      draw function

typedef int Int;

class WinInstanceData;

class GameWindow
{
public:
	virtual ~GameWindow();
	virtual void slot1();
	virtual void slot2();
	virtual Int draw(WinInstanceData *instData);
};
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
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A1CFBWindow::draw(WinInstanceData *instData)
{
	Rva000A166ADraw(this, instData);
	return 1;
}

class Rva000A3131Window : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A3131Window::draw(WinInstanceData *instData)
{
	W3DGadgetListBoxDraw(this, instData);
	return 1;
}

class Rva000A6097Window : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A6097Window::draw(WinInstanceData *instData)
{
	W3DGadgetPushButtonImageDraw(this, instData);
	return 1;
}

class Rva000A086DWindow : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A086DWindow::draw(WinInstanceData *instData)
{
	Rva000A03BFDraw(this, instData);
	return 1;
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
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A0C42Window::draw(WinInstanceData *instData)
{
	W3DGadgetStaticTextDraw(this, instData);
	return 1;
}

class Rva000A12E6Window : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A12E6Window::draw(WinInstanceData *instData)
{
	Rva000A0D5EDraw(this, instData);
	return 1;
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
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A260AWindow::draw(WinInstanceData *instData)
{
	W3DGadgetComboBoxDraw(this, instData);
	return 1;
}

class Rva000A3DA8Window : public GameWindow
{
public:
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A3DA8Window::draw(WinInstanceData *instData)
{
	W3DGadgetTabControlDraw(this, instData);
	return 1;
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
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A4328Window::draw(WinInstanceData *instData)
{
	Rva000A3F61Draw(this, instData);
	return 1;
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
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A4783Window::draw(WinInstanceData *instData)
{
	Rva000A44D2Draw(this, instData);
	return 1;
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
	virtual Int draw(WinInstanceData *instData);
};

Int Rva000A6007Window::draw(WinInstanceData *instData)
{
	Rva000A53DEDraw(this, instData);
	return 1;
}
