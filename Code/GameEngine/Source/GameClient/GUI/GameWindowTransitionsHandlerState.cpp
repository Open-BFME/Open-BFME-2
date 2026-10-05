// cl: /O1 /DNDEBUG /MD /EHsc
// ?isFinished@GameWindowTransitionsHandler@@QAE_NXZ @0x001DBFEE 46B
//
// Zero Hour's GameWindowTransitionsHandler::isFinished (current group's
// isFinished, true when there is none) under BFME 2's critical section at
// +0x38. Callers 0x001DC07E and Shell 0x0035BE55 load the receiver from
// TheTransitionHandler (0x00DFDC14); the donor-sweep pin in symbols.csv names
// this address isFinished. Callee row ?rva001DBD83@Rva001DBDA4@@QBE_NXZ
// (TransitionGroup); offsets from retail lea/mov. The class is the one whose
// ctor 0x001DCBC3 installs vftable 0x00BDBC30; slots 9 and 12 follow.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);

class Rva001DBDA4
{
public:
	bool rva001DBD83() const;
	void rva001DBE17();
	void rva001DBE51();
};

struct AudioLock
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
	void rva001DBE6E();
	void rva001DBFD1();
private:
	char m_pad00[0x24];
	Rva001DBDA4 *m_24;
	Rva001DBDA4 *m_28;
	Rva001DBDA4 *m_2C;
	Rva001DBDA4 *m_30;
	char m_pad34[0x4];
	AudioLock m_38;
	char m_pad50[0x19];
	bool m_69;
};

bool GameWindowTransitionsHandler::isFinished()
{
	EnterCriticalSection(&m_38);
	bool b;
	if (m_24)
		b = m_24->rva001DBD83();
	else
		b = true;
	LeaveCriticalSection(&m_38);
	return b;
}

// Retail 0x001DBE6E 72B: GameWindowTransitionsHandler slot 9 release of four Rva001DBDA4 lists plus clear byte at +0x69.
// Evidence: vtable 0x007DBC30 slot 9 of the handler ctor; rowed rva001DBE17 callee; offsets +0x24 +0x28 +0x30 +0x2C +0x69; neighbours 0x001DBE51 and 0x001DBFEE.
void GameWindowTransitionsHandler::rva001DBE6E()
{
	if (m_24)
	{
		m_24->rva001DBE17();
		m_24 = 0;
	}
	if (m_28)
	{
		m_28->rva001DBE17();
		m_28 = 0;
	}
	if (m_30)
	{
		m_30->rva001DBE17();
		m_30 = 0;
	}
	if (m_2C)
	{
		m_2C->rva001DBE17();
		m_2C = 0;
	}
	m_69 = false;
}

// Retail 0x001DBFD1 29B: GameWindowTransitionsHandler slot 12 apply rva001DBE51 to lists at +0x30 then +0x2C.
// Evidence: vtable 0x007DBC30 slot 12 of the handler ctor; rowed rva001DBE51 callee; offsets +0x30 +0x2C.
void GameWindowTransitionsHandler::rva001DBFD1()
{
	if (m_30)
		m_30->rva001DBE51();
	if (m_2C)
		m_2C->rva001DBE51();
}
