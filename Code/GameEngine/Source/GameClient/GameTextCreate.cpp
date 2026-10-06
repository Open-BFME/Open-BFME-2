// cl: /O1 /MD /EHsc
// CreateGameTextInterface, native 0x002E651F..0x002E6551 (50B).
// Identity: GameEngine::init 0x0022E2E4 builds TheGameText through this
// factory (the pin is that recovered caller's REL32), and Zero Hour's
// GameText.cpp defines it as `return NEW GameTextManager;`.
// Target shape: plain operator new of 0x44 bytes, then the constructor at
// 0x002E63AA (it installs vftable 0x00C04FA8 over the subsystem base) under
// one EH state that frees the block if construction throws.

class GameTextInterface
{
public:
	virtual ~GameTextInterface();
};

class GameTextManager : public GameTextInterface
{
public:
	GameTextManager();

private:
	char m_unknown04[0x40];
};

GameTextInterface *CreateGameTextInterface(void)
{
	return new GameTextManager;
}
