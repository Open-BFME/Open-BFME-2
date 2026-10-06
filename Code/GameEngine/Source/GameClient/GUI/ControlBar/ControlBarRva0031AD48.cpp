// cl: /DNDEBUG /MD
// ?rva0031AD48@ControlBar@@QAEX_N@Z @ 0x0031AD48 18B: ControlBar window hide
// via +0xA4 with tail-jmp to rowed winHide. Evidence: gap between 0x0031AD14
// and 0x0031AE13 plus caller 0x00248278 plus rowed winHide 0x00313C64.
class GameWindow
{
public:
	int winHide(bool hide);
};

class ControlBar
{
public:
	void rva0031AD48(bool hide);

private:
	char m_pad00[0xa4];
	GameWindow *m_p00A4;
};

void ControlBar::rva0031AD48(bool hide)
{
	GameWindow *win = m_p00A4;
	if (win == 0)
		return;
	win->winHide(hide);
}
