// cl: /O1 /DNDEBUG /MD /EHsc
// ?init@GameWindowManager@@UAEXXZ @0x002C0A0F 77B
// GameWindowManager::init (Zero Hour GameWindowManager.cpp, donor source):
// create TheTransitionHandler, load the window transitions, init it.
// Target evidence: WorldBuilder lead names 0x002C0A0F GameWindowManager::init;
// retail news a 0x6C-byte object (the size the matched
// GameWindowTransitionsHandler ctor 0x001DCBC3 / dtor 0x001DC6E4 lay out),
// constructs it, stores it in TheTransitionHandler (0x00DFDC14), then calls
// 0x001DC7E1 -- which ends by loading "Data\INI\WindowTransitions.ini", so it
// is GameWindowTransitionsHandler::load -- and virtual slot 1 (init).
// BFME 2 delta: no null test before the allocation (Zero Hour guards it).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_bfme04[8];
};

class GameWindowTransitionsHandler : public SubsystemInterface
{
public:
	GameWindowTransitionsHandler();
	void load();
	void init();
	void reset();
	void update();

private:
	unsigned char m_bfme0C[0x6C - 0x0C];
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class GameWindowManager
{
public:
	virtual ~GameWindowManager();
	virtual void init();
};

void GameWindowManager::init()
{
	TheTransitionHandler = new GameWindowTransitionsHandler;
	TheTransitionHandler->load();
	TheTransitionHandler->init();
}

// ?init@Rva008FCA3@@UAEXXZ @0x0008FF0D 5B: slot 1 of the device window
// manager's vtable 0x007C7C90 (??_7Rva008FCA3, the W3DGameWindowManager of
// W3DGameWindowManagerGadgets.cpp). Zero Hour's W3DGameWindowManager::init
// only extends GameWindowManager::init, here a tail jump to 0x002C0A0F.
class Rva008FCA3 : public GameWindowManager
{
public:
	virtual void init();
};

void Rva008FCA3::init()
{
	GameWindowManager::init();
}
