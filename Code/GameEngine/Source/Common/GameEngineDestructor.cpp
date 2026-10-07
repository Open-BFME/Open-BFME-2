// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
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
	GameEngineDeletingBase(struct EmitVtableTag *);
};

// GameEngineDeletingBase::~GameEngineDeletingBase: defined in GameEngineDeletingBaseDtor.cpp (its row's unit).

class GameEngine : public GameEngineDeletingBase
{
public:
	virtual ~GameEngine();
	GameEngine(struct EmitVtableTag *);
};

// GameEngine::~GameEngine: defined in GameEngineCompleteDestructor.cpp (its row's unit).

// Dummy tag constructors only make this TU emit the vtables (whose slot 0 is
// the scalar deleting wrapper). They carry no retail identity and emit no
// retail-named ctor COMDATs; the wrappers call the rowed complete dtors.
// ?<GameEngineDeletingBase::GameEngineDeletingBase> absent-from-retail
GameEngineDeletingBase::GameEngineDeletingBase(struct EmitVtableTag *)
{
}

// ?<GameEngine::GameEngine> absent-from-retail
GameEngine::GameEngine(struct EmitVtableTag *) : GameEngineDeletingBase((struct EmitVtableTag *)0)
{
}
