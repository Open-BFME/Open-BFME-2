// cl: /O1 /DNDEBUG /MD
//
// GameEngine::~GameEngine, retail 0x00225B9B, 11 bytes.
// Dedicated TU so GameEngineDestructor.cpp's scalar deleting wrapper cannot
// see this body (that TU inlines the empty local base into a 7-byte ret).
// Retail installs the GameEngine vtable then tail-jumps the deleting-base
// destructor at 0x001B4E74.

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class GameEngine : public GameEngineDeletingBase
{
public:
	virtual ~GameEngine();
};

GameEngine::~GameEngine()
{
}
