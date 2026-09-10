// cl: /O1
//
// GameWindow::winGetUserData, retail 0x005C4ACD, 4 bytes.
// Shim GameWindow.h places m_userData at +0x2C; retail is mov eax,[ecx+2Ch]; ret.

class GameWindow
{
	unsigned char _M_layout[0x2C];
	void *m_userData;

public:
	void *winGetUserData();
};

void *GameWindow::winGetUserData()
{
	return m_userData;
}
