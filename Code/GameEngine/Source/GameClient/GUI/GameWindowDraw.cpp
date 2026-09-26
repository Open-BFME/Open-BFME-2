// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?draw@GameWindow@@UAEHPAX@Z @0x0009DC05 29B
// Virtual slot 3 (offset 0xC) of vtable 0x0080BBCC (VA 0x00C0BBCC) shared by
// ??0GameWindow@@QAE@XZ and ??0BfmeAptScreenBase@@QAE@PAX@Z (ICF-folded identical vtables).
// Evidence: Code/GameEngine/Source/GameClient/GUI/GameWindowManager_drawWindow_Thunk.cpp
// declares virtual Int draw(void *instanceData) at slot 3 and calls window->draw
// checking !=1; caller at 0x0009DC32 calls this and checks ==1; retail loads
// [ecx+0x1E8] (m_draw, proven by GameWindow_DefaultConstructor and
// BfmeAptScreenBaseConstructor layouts) and forwards (this, data) returning 1/0.

class WinInstanceData
{
public:
	WinInstanceData();

private:
	char m_data[ 0x1A8 ];
};

class GameWindow;

class DrawSub
{
public:
	virtual void unused();
	virtual void draw( GameWindow *win, WinInstanceData *data );
};

class GameWindow
{
public:
	virtual ~GameWindow();
	virtual int slot1( unsigned int, unsigned int, unsigned int );
	virtual int slot2( unsigned int, unsigned int, unsigned int );
	virtual int draw( void *data );
	int rva0009DC32( WinInstanceData *instData );

private:
	void *m_bfmeAnchor;
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
	void *m_inputData;
	void *m_bfmeInputExtra;
	void *m_input;
	void *m_system;
	void (*m_draw)( GameWindow *, void * );
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
	void *m_editData;
	DrawSub m_drawSub;
};

int GameWindow::draw( void *data )
{
	if ( m_draw ) {
		m_draw( this, data );
		return 1;
	}
	return 0;
}

// ?rva0009DC32@GameWindow@@QAEHPAVWinInstanceData@@@Z @0x0009DC32 40B
// Default-draw dispatch BFME1 inlined out of line: tries draw (0x0009DC05),
// else draws through the sub-object at +0x218 (DrawSub slot 1, offset 0x4).
// Evidence: Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DGadgetTabControlDraw.cpp
// declares rva0009DC32 and documents this shape with five callers; retail
// lea ecx,[esi+0x218] plus call [eax+4] proves the embedded DrawSub.
int GameWindow::rva0009DC32( WinInstanceData *instData )
{
	if ( GameWindow::draw( instData ) == 1 )
		return 1;
	m_drawSub.draw( this, instData );
	return 1;
}
