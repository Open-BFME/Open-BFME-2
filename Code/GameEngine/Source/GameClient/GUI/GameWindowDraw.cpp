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

class GameWindow
{
public:
	virtual ~GameWindow();
	virtual int slot1( unsigned int, unsigned int, unsigned int );
	virtual int slot2( unsigned int, unsigned int, unsigned int );
	virtual int draw( void *data );

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
};

int GameWindow::draw( void *data )
{
	if ( m_draw ) {
		m_draw( this, data );
		return 1;
	}
	return 0;
}
