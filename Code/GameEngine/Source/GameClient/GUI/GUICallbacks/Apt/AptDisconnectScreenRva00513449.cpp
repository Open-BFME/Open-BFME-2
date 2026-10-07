// cl: /DNDEBUG /MD /O1 /Oy- /arch:SSE /G7
// Target 0x00513449 is a 78-byte AptDisconnectScreen handler. The adjacent
// 0x00513382 callback reads the same +0x280 chat-entry field that this handler
// compares against wParam, then is called with a null string for message
// 0x4031 when lParam is zero. Its original method name remains unknown.

class GameWindow;
class UnicodeString;

class _bfme_AptGameWindow
{
public:
	int rva0051274F(int message, unsigned int wParam, unsigned int lParam);
};

class AptDisconnectScreen
{
public:
	void Kick(const char *slot);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void Quit(const char *unused);
	void OnBttnEnterText(const char *unused);
	int rva00513449(int message, unsigned int wParam, unsigned int lParam);
	void PlayerColor(int slot, char *result, bool skip);
	void rva005130E2(UnicodeString text);

private:
	unsigned char m_pad000[0x27C];
	GameWindow *m_chatBox;
	GameWindow *m_chatEntry;
	unsigned char m_pad284[0x285 - 0x284];
	bool m_quit;
};

// Ghidra boundary 0x00513449 / 78B. The address-derived method delegates to
// the pinned base handler at 0x0051274F, answers the two handled messages, and
// calls the matched AptDisconnectScreen callback at 0x00513382 only when the
// target message points at the +0x280 chat entry and has zero lParam.
int AptDisconnectScreen::rva00513449(int message, unsigned int wParam, unsigned int lParam)
{
	int result = ((_bfme_AptGameWindow *)this)->rva0051274F(message, wParam, lParam);
	if (result == 1)
		return 1;
	switch (message)
	{
	case 0x4008:
		return 1;
	case 0x4031:
		if (wParam == (unsigned int)m_chatEntry && lParam == 0)
			OnBttnEnterText(0);
		return 1;
	default:
		return 0;
	}
}
