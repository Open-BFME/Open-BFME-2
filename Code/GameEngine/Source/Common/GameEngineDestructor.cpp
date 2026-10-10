// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
//
// The vtable at 0x00BE7188 is installed by the GameEngine constructor and
// carries the frame-loop method at 0x00225DA9.  Its slot 0 is the 28-byte
// scalar deleting destructor at 0x00226333.  The complete destructor body is
// still held anonymously at 0x00225B9B; the symbols pin records that call
// target without claiming an unverified body here.
//
// MSVC emits the 28-byte wrapper when the class has an out-of-line virtual
// base destructor. The base is the native SubsystemInterface header (ctor
// 0x001B4E63 / dtor 0x001B4E74 rowed as ??0/??1SubsystemInterface, 14-slot
// vtable 0x00BD77A0), the same view GameEngineCompleteDestructor.cpp uses, so
// both units emit one GameEngine vtable and this one no longer emits a private
// SubsystemInterface vtable. Retail's GameEngine vtable has 40 slots; the 26
// GameEngine slots past the base are not modelled by either unit yet.
typedef bool Bool;
#include "subsystem_interface.h"

class GameEngine : public SubsystemInterface
{
public:
	virtual ~GameEngine();
	GameEngine(struct EmitVtableTag *);
};

// GameEngine::~GameEngine: defined in GameEngineCompleteDestructor.cpp (its row's unit).

// The dummy tag constructor only makes this TU emit the vtable (whose slot 0 is
// the scalar deleting wrapper). It carries no retail identity and emits no
// retail-named ctor COMDAT; the wrapper calls the rowed complete dtor.
// ?<GameEngine::GameEngine> absent-from-retail
GameEngine::GameEngine(struct EmitVtableTag *)
{
}
