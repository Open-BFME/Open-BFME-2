// cl: /O1 /DNDEBUG /MD
// GameWindowManager reset/update, winDestroy, mouse capture, window hiding and
// the modal stack. BFME1 donor GameWindowManager.cpp (6d943426) shapes; ZH
// names. Slots are the W3D window manager vtable at 0x00BC7C90: 9 reset, 10
// update, 35 winDestroy, 36 winDestroyAll, 40 windowHiding, 49 winSetFocus, 61
// winCapture, 62 winRelease, 64 winSetModal, 65 winUnsetModal. Members as in
// the rowed processDestroyList (0x002C08EF): destroy list +0x14, mouse region
// +0x18, mouse captor +0x1C, keyboard focus +0x20, modal head +0x24, grab
// window +0x28. The modal entry is the 12-byte class whose sole vtable slot is
// ??_GRva002C1283 (vtable 0x00BFE5B4). GameWindow: status +0x8 (destroyed
// 0x800), next/prev +0x1F8/+0x1FC, parent/child +0x200/+0x204, layout +0x210.

typedef int Int;
typedef unsigned int UnsignedInt;

enum
{
	WIN_ERR_OK = 0,
	WIN_ERR_GENERAL_FAILURE = -1,
	WIN_ERR_INVALID_WINDOW = -2,
	WIN_ERR_INVALID_PARAMETER = -3,
	WIN_ERR_MOUSE_CAPTURED = -4
};

enum
{
	WIN_STATUS_DESTROYED = 0x00000800
};

class GameWindow;

class WindowLayout
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6)
#undef V
	virtual void removeWindow(GameWindow *window) = 0;
};

class GameWindow
{
	friend class GameWindowManager;
public:
	GameWindow *winGetNext();
	GameWindow *winGetChild();
private:
	unsigned char m_pad00[0x8];
	UnsignedInt m_status;
	unsigned char m_pad0C[0x1F8 - 0xC];
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
	unsigned char m_pad208[0x210 - 0x208];
	WindowLayout *m_layout;
};

// Zero Hour's ModalWindow: a heap entry on the window manager's modal stack.
class Rva002C1283
{
public:
	virtual ~Rva002C1283() {}
	GameWindow *window;
	Rva002C1283 *next;
};

class GameWindowTransitionsHandler
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
#undef V
	virtual void reset() = 0;
	virtual void update() = 0;
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
	virtual void reset();
	virtual void update();
	V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34)
	virtual Int winDestroy(GameWindow *window);
	virtual Int winDestroyAll() = 0;
	V(37) V(38) V(39)
	virtual void windowHiding(GameWindow *window);
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48)
	virtual Int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60)
	virtual Int winCapture(GameWindow *window);
	virtual Int winRelease(GameWindow *window);
	V(63)
	virtual Int winSetModal(GameWindow *window);
	virtual Int winUnsetModal(GameWindow *window);
#undef V

	void unlinkWindow(GameWindow *window);
	void unlinkChildWindow(GameWindow *window);

protected:
	void processDestroyList();

	unsigned char m_pad04[0x14 - 4];
	GameWindow *m_destroyList;
	GameWindow *m_currMouseRgn;
	GameWindow *m_mouseCaptor;
	GameWindow *m_keyboardFocus;
	Rva002C1283 *m_modalHead;
	GameWindow *m_grabWindow;
};

void GameWindowManager::reset()
{
	// destroy all windows left
	winDestroyAll();

	if (TheTransitionHandler)
		TheTransitionHandler->reset();
}

void GameWindowManager::update()
{
	// destroy all windows queued for deletion
	processDestroyList();

	if (TheTransitionHandler)
		TheTransitionHandler->update();
}

Int GameWindowManager::winDestroy(GameWindow *window)
{
	GameWindow *child, *next;

	if (window == 0)
		return WIN_ERR_INVALID_WINDOW;

	if (window->m_status & WIN_STATUS_DESTROYED)
		return WIN_ERR_OK;

	window->m_status |= WIN_STATUS_DESTROYED;

	// release capture
	if (m_mouseCaptor == window)
		winRelease(window);

	// clear focus
	if (m_keyboardFocus == window)
		winSetFocus(0);

	// if this is the modal head, unset it
	if (m_modalHead && window == m_modalHead->window)
		winUnsetModal(m_modalHead->window);

	// if this window is the mouse "in" region, clear it
	if (m_currMouseRgn == window)
		m_currMouseRgn = 0;

	// if this window is the grab window, clear it
	if (m_grabWindow == window)
		m_grabWindow = 0;

	// destroy all children
	for (child = window->m_child; child; child = next)
	{
		next = child->m_next;
		winDestroy(child);
	}

	// remove the window from its list
	if (window->m_parent == 0)
		unlinkWindow(window);
	else
		unlinkChildWindow(window);

	// add to head of the destroy list
	window->m_prev = 0;
	window->m_next = m_destroyList;
	m_destroyList = window;

	// remove the window from the layout it belongs to
	if (window->m_layout)
		window->m_layout->removeWindow(window);

	return WIN_ERR_OK;
}

void GameWindowManager::windowHiding(GameWindow *window)
{
	// if this window has keyboard focus remove it
	if (m_keyboardFocus == window)
		m_keyboardFocus = 0;

	// if this is the modal head, unset it
	if (m_modalHead && m_modalHead->window == window)
		winUnsetModal(window);

	// if this is the captor, it shall no longer be
	if (m_mouseCaptor == window)
		winCapture(0);

	// hiding a parent hides its children, so each child gets the same pass
	GameWindow *child;
	for (child = window->winGetChild(); child; child = child->winGetNext())
		windowHiding(child);
}

Int GameWindowManager::winCapture(GameWindow *window)
{
	if (m_mouseCaptor != 0)
		return WIN_ERR_MOUSE_CAPTURED;

	m_mouseCaptor = window;

	return WIN_ERR_OK;
}

Int GameWindowManager::winRelease(GameWindow *window)
{
	if (window == m_mouseCaptor)
		m_mouseCaptor = 0;

	return WIN_ERR_OK;
}

Int GameWindowManager::winUnsetModal(GameWindow *window)
{
	Rva002C1283 *next;

	if (window == 0)
		return WIN_ERR_INVALID_WINDOW;

	// verify entry is at top of list
	if (m_modalHead == 0 || m_modalHead->window != window)
		return WIN_ERR_GENERAL_FAILURE;

	// remove from top of list
	next = m_modalHead->next;
	::delete m_modalHead;
	m_modalHead = next;

	return WIN_ERR_OK;
}

Int GameWindowManager::winSetModal(GameWindow *window)
{
	Rva002C1283 *modal;

	if (window == 0)
		return WIN_ERR_INVALID_WINDOW;

	// verify requesting window is a root window
	if (window->m_parent != 0)
		return WIN_ERR_INVALID_PARAMETER;

	// allocate a new modal entry
	modal = new Rva002C1283;
	if (modal == 0)
		return WIN_ERR_GENERAL_FAILURE;

	// push window onto stack
	modal->window = window;
	modal->next = m_modalHead;
	m_modalHead = modal;

	return WIN_ERR_OK;
}
