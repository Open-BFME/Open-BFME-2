// cl: /DNDEBUG /MD /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
//
// GameEngine::~GameEngine, retail 0x00225B9B, 11 bytes.
// Dedicated TU so GameEngineDestructor.cpp's scalar deleting wrapper cannot
// see this body while emitting its deleting wrapper.
// Retail installs the GameEngine vtable then tail-jumps the
// SubsystemInterface destructor at 0x001B4E74, using its native header.

typedef bool Bool;
#include "subsystem_interface.h"

class GameEngine : public SubsystemInterface
{
public:
	virtual ~GameEngine();
};

GameEngine::~GameEngine()
{
}
