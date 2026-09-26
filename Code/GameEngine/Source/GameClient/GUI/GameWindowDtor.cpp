// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1GameWindow@@MAE@XZ @0x00314A0C 184B
// GameWindow dtor: vtable 0x0080BBCC slot0 deleting dtor at 0x00314AC4 calls here.
// Evidence: BFME1 GameWindowDestructorThunk donor (global check, inputData/editData deletes,
// anchor with lock), page 00314xxx sibling of GameWindow ctor 0x003145F0 (same vtable),
// callers at 0x00104E33/0x0051273C (derived dtors), callees rowed 0x31468C/0x2FD60/0x11F520/0x120F50/0x3222B8.

class WinInstanceData
{
public:
	WinInstanceData();
	virtual ~WinInstanceData();
private:
	char m_pad[ 0x1A8 - 4 ];
};

class Rva0031468C
{
public:
	~Rva0031468C();
private:
	char m_data[ 0x10 ];
};

class GameWindowInputData
{
};

class GameWindowAnchor
{
public:
	virtual void a00() = 0;
	virtual void a04() = 0;
	virtual void a08() = 0;
	virtual void a0C() = 0;
	virtual void a10() = 0;
	virtual void *a14( int x ) = 0;
};

class GameWindow;

// The global read at 0x00DFE728 is TheIMEManager (WinMain WndProc reads it as
// such); the other GUI bodies put TheWindowManager at 0x00DFEF1C. Generals
// ~GameWindow likewise detaches the IME manager when it owns this window.
// Slot names stay offset placeholders.
class IMEManager
{
public:
	virtual void m00() = 0;
	virtual void m04() = 0;
	virtual void m08() = 0;
	virtual void m0C() = 0;
	virtual void m10() = 0;
	virtual void m14() = 0;
	virtual void m18() = 0;
	virtual void m1C() = 0;
	virtual void m20() = 0;
	virtual void m24() = 0;
	virtual void m28() = 0;
	virtual void m2C() = 0;
	virtual void m30() = 0;
	virtual void m34() = 0;
	virtual void m38() = 0;
	virtual void m3C() = 0;
	virtual void m40() = 0;
	virtual void m44() = 0;
	virtual void m48() = 0;
	virtual void m4C() = 0;
	virtual GameWindow *m50() = 0;
};

extern IMEManager *TheIMEManager;

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	GameWindowAnchor *m_anchor;
	int m_status;
	int m_sizeX;
	int m_sizeY;
	int m_regionLoX;
	int m_regionLoY;
	int m_regionHiX;
	int m_regionHiY;
	int m_cursorX;
	int m_cursorY;
	void *m_userData;
	WinInstanceData m_instData;
	GameWindowInputData *m_inputData;
	void *m_bfmeInputExtra;
	void *m_input;
	void *m_system;
	void *m_draw;
	void *m_tooltip;
	void *m_bfmeCallbackExtra;
	int m_bfmeCallbackExtra2;
	void *m_next;
	void *m_prev;
	void *m_parent;
	void *m_child;
	void *m_nextLayout;
	void *m_prevLayout;
	void *m_layout;
	Rva0031468C *m_editData;
};

GameWindow::~GameWindow()
{
	if ( TheIMEManager && TheIMEManager->m50() == this )
		TheIMEManager->m3C();

	if ( m_inputData )
		delete m_inputData;
	m_inputData = 0;

	if ( m_editData )
		delete m_editData;
	m_editData = 0;

	if ( m_anchor )
	{
		BFMEDX8DeviceLock guard;
		void *p = m_anchor ? m_anchor->a14( 0 ) : 0;
		delete p;
	}
}
