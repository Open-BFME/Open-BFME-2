// cl: /DNDEBUG /MD

// GameWindow draw-data setters. BFME1's GameWindow.cpp marks this family
// present-unmatched and names this TU as the BFME-layout home: ZH headers
// put m_instData at +0x2c, BFME at +0x30, so ZH-shaped TUs store one
// WinDrawData member (4B) early. Retail proves +0x30: the image store folds
// this+72 as (index+6)*12 (72 = 6*12, divisible, so MSVC merges it into the
// index), while the color store at this+76 keeps base+index*12 form (76 is
// not stride-divisible). Both are m_instData.m_enabledDrawData[index] at
// instData+0x18 with 12B {image, color, borderColor} elements. The
// DEBUG_LOG/assert failure arms compile out; retail keeps only the
// bounds check (0 <= index < MAX_DRAW_DATA = 9) returning -3, else 0.

class Image;

struct WinDrawData
{
	const Image *image;
	int color;
	int borderColor;
};

struct WinInstanceData
{
	char m_pad[24];
	WinDrawData m_enabledDrawData[9];
	WinDrawData m_disabledDrawData[9];
	WinDrawData m_hiliteDrawData[9];
};

class GameWindow
{
public:
	int winSetEnabledImage(int index, const Image *image);
	int winSetEnabledColor(int index, int color);
	int winSetEnabledBorderColor(int index, int color);
	int winSetDisabledImage(int index, const Image *image);
	int winSetDisabledColor(int index, int color);
	int winSetDisabledBorderColor(int index, int color);
	int winSetHiliteImage(int index, const Image *image);
	int winSetHiliteColor(int index, int color);
	int winSetHiliteBorderColor(int index, int color);
	void setRva003144FD(int value);
	int getRva0031450A();

private:
	char m_pad[48];
	WinInstanceData m_instData;
	char m_pad2[136];
	int m_unk214;
};

int GameWindow::winSetEnabledImage(int index, const Image *image)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_enabledDrawData[index].image = image;
	return 0;
}

int GameWindow::winSetEnabledColor(int index, int color)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_enabledDrawData[index].color = color;
	return 0;
}

int GameWindow::winSetEnabledBorderColor(int index, int color)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_enabledDrawData[index].borderColor = color;
	return 0;
}

int GameWindow::winSetDisabledImage(int index, const Image *image)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_disabledDrawData[index].image = image;
	return 0;
}

int GameWindow::winSetDisabledColor(int index, int color)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_disabledDrawData[index].color = color;
	return 0;
}

int GameWindow::winSetDisabledBorderColor(int index, int color)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_disabledDrawData[index].borderColor = color;
	return 0;
}

int GameWindow::winSetHiliteImage(int index, const Image *image)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_hiliteDrawData[index].image = image;
	return 0;
}

int GameWindow::winSetHiliteColor(int index, int color)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_hiliteDrawData[index].color = color;
	return 0;
}

int GameWindow::winSetHiliteBorderColor(int index, int color)
{
	if (index < 0 || index >= 9)
		return -3;
	m_instData.m_hiliteDrawData[index].borderColor = color;
	return 0;
}

void GameWindow::setRva003144FD(int value)
{
	m_unk214 = value;
}

int GameWindow::getRva0031450A()
{
	return m_unk214;
}
