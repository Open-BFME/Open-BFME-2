// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE
//
// The vtable at 0x00BE7188 is installed by the GameEngine constructor and
// carries the frame-loop method at 0x00225DA9.  Its slot 0 is the 28-byte
// scalar deleting destructor at 0x00226333.  The complete destructor body is
// still held anonymously at 0x00225B9B; the symbols pin records that call
// target without claiming an unverified body here.
//
// MSVC emits the 28-byte wrapper when the class has an out-of-line virtual
// base destructor.  The small base declaration models that emission shape;
// it does not make a semantic claim about the still-unrecovered base class.

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

GameEngineDeletingBase::~GameEngineDeletingBase() {}

class GameEngine : public GameEngineDeletingBase
{
public:
	virtual ~GameEngine();
};

GameEngine::~GameEngine() {}

// A construction use makes MSVC emit GameEngine's scalar deleting wrapper in
// this translation unit.  The helper itself is intentionally not a ledger
// claim; it only keeps the compiler's COMDAT alive for byte verification.
GameEngine *bfme_emitGameEngineDeletingDestructor(void)
{
	return new GameEngine;
}
