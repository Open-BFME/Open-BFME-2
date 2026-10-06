// cl: /DNDEBUG /MD /EHsc
//
// ?rva0035BE55@Shell@@QAE_NXZ @0x0035BE55 58B: honest-address Shell predicate.
// Evidence: neighbors Shell +0x60 in ShellTop.cpp; callees rowed GameWindowTransitionsHandler::isFinished 0x001DBFEE and global 0x00DFDC14 (TheTransitionHandler) plus TheWritableGlobalData +0xB00; callers 0x0050D145 0x0050D162; returns bool.
// Zero Hour's Shell::isAnimFinished has this shape (transition handler first,
// then the animate-window flag and the animate manager).

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
};

// Target DIR32 is 0x00DFDC14; TheAudio is the distinct pointer at 0x00DFE6E8.
extern GameWindowTransitionsHandler *TheTransitionHandler;

class GlobalData
{
public:
	unsigned char m_pad[0xB00];
	bool m_animateWindows;
};

extern GlobalData *TheWritableGlobalData;

struct AnimateState
{
	unsigned char m_pad[0x14];
	unsigned char m_14;
};

class Shell
{
public:
	bool rva0035BE55();

private:
	char m_pad[0x60];
	AnimateState *m_60;
};

bool Shell::rva0035BE55()
{
	if (!TheTransitionHandler->isFinished())
		return false;
	if (m_60 == 0)
		return true;
	if (TheWritableGlobalData->m_animateWindows)
		return m_60->m_14 == 0;
	return true;
}
