// cl: /DNDEBUG /MD /EHsc
// Native global 0x00DFDC14 is TheTransitionHandler, defined in WinMain.
// Canonical TheAudio uses 0x00DFE6E8.
// ?rva001DC07E@GameWindowTransitionsHandler@@QAEXXZ @0x001DC07E 73B: wait loop on TheTransitionHandler->isFinished with WindowManager Display setFPMode Sleep. Evidence: caller at 0x001DC618; callees rowed isFinished 0x001DBFEE setFPMode plus pins.

class GameWindowManager
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void unk28();
};

class Display
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void unk30();
};

extern GameWindowManager *TheWindowManager;
class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;
extern Display *TheDisplay;
void __cdecl setFPMode();
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

struct CRITICAL_SECTION
{
	unsigned char m_data[0x1c];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

#pragma optimize("t", on)
class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(int lock) : m_lock(lock)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_lock);
	}

	int m_lock;
};
#pragma optimize("", on)

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
	void rva001DC07E();
	void rva001DC5EC();
private:
	unsigned char m_pad00[0x38];
	CRITICAL_SECTION m_cs;
	unsigned char m_pad54[0x10];
	unsigned long m_64;
	unsigned char m_68;
};

void GameWindowTransitionsHandler::rva001DC07E()
{
	while (!TheTransitionHandler->isFinished()) {
		TheWindowManager->unk28();
		if (TheTransitionHandler->isFinished())
			continue;
		TheDisplay->unk30();
		setFPMode();
		Sleep(m_64);
	}
}

// ?rva001DC5EC@GameWindowTransitionsHandler@@QAEXXZ @0x001DC5EC 74B: guarded wait-loop call under lock at +0x38 with reentrancy flag at +0x68. Evidence: same this as callee 0x001DC07E; lock offset matches neighbour 0x001DC57C.
void GameWindowTransitionsHandler::rva001DC5EC()
{
	CriticalSectionLock lock((int)&m_cs);
	if (m_68 == 0) {
		m_68 = 1;
		rva001DC07E();
		m_68 = 0;
	}
}
