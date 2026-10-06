// cl: /DNDEBUG /MD
// ?rva0031AE01@ControlBar@@QAEXXZ @ 0x0031AE01 18B: ControlBar set +0x24 to 3
// then +0x48 window winHide(true). Evidence: gap between 0x0031AD48 and
// 0x0031AE13 sharing +0x24 layout plus caller 0x0031B99A plus rowed winHide.
class GameWindow
{
public:
	int winHide(bool hide);
};

class ControlBar
{
public:
	void rva0031AE01();

private:
	char m_pad00[0x24];
	int m_0024;
	char m_pad28[0x48 - 0x28];
	GameWindow *m_p0048;
};

void ControlBar::rva0031AE01()
{
	m_0024 = 3;
	m_p0048->winHide(true);
}
