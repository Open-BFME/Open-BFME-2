// cl: /DNDEBUG /MD /EHsc
// ?dumpWindow@GameWindowManager@@IAEXPAVGameWindow@@@Z @0x002C1148 43B
// GameWindowManager::dumpWindow; FINAL build strips DEBUG_LOG leaving only
// the child/sibling walk (m_child +0x204 m_next +0x1F8) with self recursion;
// donor Code/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp.

typedef int Int;
typedef unsigned int UnsignedInt;

class GameWindow;

class GameWindowManager
{
protected:
	void dumpWindow(GameWindow *window);
};

class GameWindow
{
public:
	unsigned char m_pad0[0x08];
	UnsignedInt m_status;
	unsigned char m_padC[0x1EC];
	GameWindow *m_next;
	unsigned char m_pad1FC[8];
	GameWindow *m_child;
};

void GameWindowManager::dumpWindow(GameWindow *window)
{
	if (!window)
		return;

	for (GameWindow *child = window->m_child; child; child = child->m_next)
		dumpWindow(child);
}
