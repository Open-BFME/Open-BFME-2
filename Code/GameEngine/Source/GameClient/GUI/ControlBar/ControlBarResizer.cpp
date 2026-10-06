// cl: /DNDEBUG /MD

// ResizerWindow constructor, retail 0x001DB6FD (31B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarResizer.cpp
// (BFME1 0x004AAED0). Member order follows the ZH header (name, defaultSize,
// defaultPos, altSize, altPos); AsciiString default-constructs inline to a
// null handle, which is the leading [eax] store. Each pair is written y then
// x: retail folds the chained `x = y = 0` y-first, so the stores are spelled
// out to hold that order.

struct AsciiString
{
	AsciiString() : m_data(0) {}
	char *m_data;
};

struct ICoord2D
{
	int x;
	int y;
};

class ResizerWindow
{
public:
	ResizerWindow(void);

private:
	AsciiString m_name;
	ICoord2D m_defaultSize;
	ICoord2D m_defaultPos;
	ICoord2D m_altSize;
	ICoord2D m_altPos;
};

// ??0ResizerWindow@@QAE@XZ, retail 0x001DB6FD (31B).
ResizerWindow::ResizerWindow(void)
{
	m_defaultPos.y = 0;
	m_defaultPos.x = 0;
	m_defaultSize.y = 0;
	m_defaultSize.x = 0;
	m_altSize.y = 0;
	m_altSize.x = 0;
	m_altPos.y = 0;
	m_altPos.x = 0;
}
