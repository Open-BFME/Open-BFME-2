// cl: /O1 /G7 /DNDEBUG /MD

// The BFME1 GameWindowFields.cpp donor assigns m_tooltip and returns OK.
// Retail at 0x0031416D confirms the field at +0x1EC and this 15B setter.
// The callback type follows the donor declaration; the field offset is target
// evidence from the retail store.

class GameWindow;
class WinInstanceData;

typedef void (*GameWinTooltipFunc)(
	GameWindow *window, WinInstanceData *data, unsigned int flags);

class GameWindow
{
public:
	int winSetTooltipFunc(GameWinTooltipFunc tooltip);

private:
	char m_unmodelled[0x1EC];
	GameWinTooltipFunc m_tooltip;
};

int GameWindow::winSetTooltipFunc(GameWinTooltipFunc tooltip)
{
	m_tooltip = tooltip;
	return 0;
}
