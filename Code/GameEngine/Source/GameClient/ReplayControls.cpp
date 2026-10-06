// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// InGameUI replay-control helpers at retail 0x0029A39C (show), 0x0029A3BC
// (hide) and 0x0029A3CE (toggle).
//
// Basis. Zero Hour (InGameUI.cpp) has the same three free functions over
// m_replayWindow: show hides the window unless TheGameLogic->isInReplayGame(),
// hide always hides, toggle shows only when in a replay and currently hidden.
// Retail agrees on every branch. Target-established: the window global at
// 0x00DFEDF4, TheGameLogic at 0x00DFE78C, the game mode compared against 3 at
// GameLogic+0x110 (Zero Hour's GameLogic puts it at +0x94, so this TU carries
// a shim of just that field), winHide at 0x313C64, winIsHidden at 0x313CD9.
// The value 3 as "replay game" is carried from the ZH GameMode enum.
//
// InGameUI.cpp still carries the unledgered ZH copies of these names; it
// compiles the ZH GameLogic layout (mode at +0x94), which cannot reproduce
// retail's +0x110. /O1 was chosen by probe: /O2 puts the setne result in dl
// where retail uses al.

class GameWindow
{
public:
	int winHide(bool hide);
	bool winIsHidden();
};

class GameLogic
{
public:
	bool isInReplayGame() { return m_gameMode == 3; }

private:
	char m_pad[0x110];
	int m_gameMode;
};

extern GameLogic *TheGameLogic;
extern GameWindow *m_replayWindow;

void showReplayControls(void)
{
	if (m_replayWindow)
	{
		m_replayWindow->winHide(!TheGameLogic->isInReplayGame());
	}
}

void hideReplayControls(void)
{
	if (m_replayWindow)
	{
		m_replayWindow->winHide(true);
	}
}

void toggleReplayControls(void)
{
	if (m_replayWindow)
	{
		bool show = TheGameLogic->isInReplayGame() && m_replayWindow->winIsHidden();
		m_replayWindow->winHide(!show);
	}
}
